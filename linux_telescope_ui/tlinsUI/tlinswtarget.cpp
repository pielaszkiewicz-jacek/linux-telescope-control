#include "tlinswtarget.h"
#include "tlinsastrobaseutils.h"
#include "tlinscommunicationthread.h"
#include "tlinsserverstatusinfo.h"
#include "tlinsuimainwindow.h"
#include "ui_tlinswtarget.h"

#include <tlinsBacktrace.hpp>

#include <algorithm>
#include <cmath>
#include <iomanip>
#include <iostream>
#include <limits>
#include <type_traits>

void tlinsWTarget::setControls()
{
    ui->RA->setValue(target.getRA());

    ui->DC->setValue(target.getDC());
    ui->pmRA->setValue(target.getPmRA());
    ui->pmDC->setValue(target.getPmDC());
    ui->pmRA->disableButtons();
    ui->pmDC->disableButtons();
    ui->radialVelocity->setValue(target.getRadialVelocity());
    ui->parallex->setValue(target.getParallex());
    ui->catalogType->setCurrent(target.getCatalogType());
    ui->objectType->setCurrent(target.getObjectType());
    ui->objectConstelation->setCurrent(target.getConstelation());
    ui->objectName->setValue(target.getObjectName());
    ui->magnitude->setValue(target.getMagnitutde());
    ui->speed->setValue(0.0);
    ui->aceleration->setValue(0.0);
    ui->delta->setValue(0);
}

void tlinsWTarget::on_btClear_clicked()
{
    target = tlinsTarget {};
    setControls();
    isSet = false;
}

class tlinsSetTarget : public TlinsAstroBase::tlinsCommunicationThreadRequest {
private:
    std::shared_ptr<TlinsAstroBase::tlinsConnectionContext> connection;
    tlinsWTarget* parent;
    tlinsTarget target;

public:
    void confirm()
    {
        TlinsAstroBase::tlinsCommunicationThreadRequest::confirm();
    }

    virtual void operator()() noexcept
    {
        tlinsAstroEngineInterface::tlinsTarget reqData;

        reqData.set_aceleration(target.getAceleration());
        reqData.set_speed(target.getSpeed());
        reqData.set_delta(target.getDelta());

        tlinsAstroEngineInterface::tlinsAstroObject astroObject;
        astroObject.set_properMotionRA(target.getPmRA());
        astroObject.set_properMotionDC(target.getPmDC());
        astroObject.set_parallax(target.getParallex());
        astroObject.set_radialVelocity(target.getRadialVelocity());
        astroObject.set_catalogType(target.getCatalogType());

        tlinsAstroEngineInterface::tlinsCoordinate ra;
        {
            int h;
            int m;
            double s;
            bool sign;
            TlinsAstroBase::tlinsAstroBaseUtils::splitRA(target.getRA(), h, m, s, sign);
            ra.set_degris(h);
            ra.set_minutes(m);
            ra.set_seconds(s);
            ra.set_sign(sign);
        }

        tlinsAstroEngineInterface::tlinsCoordinate dc;
        {
            int d;
            int m;
            double s;
            bool sign;
            TlinsAstroBase::tlinsAstroBaseUtils::splitDegris(target.getDC(), d, m, s, sign);
            dc.set_degris(d);
            dc.set_minutes(m);
            dc.set_seconds(s);
            dc.set_sign(sign);
        }

        astroObject.set_hourAngle(ra);
        astroObject.set_declination(dc);

        reqData.set_object(astroObject);

        try {
            // Uruchomienie zapytania
            connection->getAstro()->setTarget(reqData, false);

            // Komunikowanie wprowadzonej zmiony
            auto mw = getMainWindowInstance();
            emit mw->logEvent("Target set.");
            emit parent->notiStatus("Target set.");
        } catch (tlinsInterfaceException& exc) {
            auto mw = getMainWindowInstance();
            emit mw->logEvent(QString::fromStdString(std::string { "Error set target: " } + exc.getErrorMessage()));
            emit parent->notiStatus("Error set target: " + exc.getErrorMessage());
        }
    }

    virtual bool isAsynchronuus()
    {
        return false;
    }

    virtual std::string name()
    {
        return "tlinsSetTarget";
    }

    tlinsSetTarget(tlinsWTarget* parent_,
        const tlinsTarget& target_)
        : parent { parent_ }
        , target { target_ }
    {
        // Pobranie polaczenia
        if (!TlinsAstroBase::tlinsConnectionsManager::getInstance().hasConnection(std::string { TLINS_CONNECTION_DEFAULT }))
            __THROW__(tlinsException(std::string("No active connection: ") + std::string(TLINS_CONNECTION_DEFAULT), -1));

        // Polaczenie
        connection = TlinsAstroBase::tlinsConnectionsManager::getInstance().getConnection(TLINS_CONNECTION_DEFAULT);
    }

    virtual ~tlinsSetTarget()
    {
        connection.reset();
    }
};

void tlinsWTarget::on_btSetTarget_clicked()
{
    setObject();

    auto& statusInfo = TlinsAstroBase::tlinsServerStatusInfo::getInstance();
    auto& cStatus = statusInfo.getCalibrarionState();

    switch (cStatus.get_engineState()) {
    case tlinsAstroEngineInterface::tlinsEngineStateValue::STATE_CALIBRATION:
    case tlinsAstroEngineInterface::tlinsEngineStateValue::STATE_CALIBRATION_VELOCITY: {
        QMessageBox msg;
        msg.setText("Engine is not started.");
        msg.exec();
        return;
    }
    case tlinsAstroEngineInterface::tlinsEngineStateValue::STATE_REGULAR:
        break;
    }

    try {
        std::unique_ptr<TlinsAstroBase::tlinsCommunicationThreadRequest> req(new tlinsSetTarget { this, target });
        TlinsAstroBase::tlinsCommunicationThread::getInstance().push(req);
    } catch (tlinsException& exc) {
        TLINS_LOG_ERROR("Error: " + exc.getErrorMessage());
        auto mw = getMainWindowInstance();
        emit mw->logEvent(QString::fromStdString("Error: " + exc.getErrorMessage()));

        QMessageBox msgBox;
        msgBox.setText(QString::fromStdString("Error: " + exc.getErrorMessage()));
        msgBox.exec();
    }
}

void tlinsWTarget::notiStatusSlot(std::string str)
{
    QMessageBox msgBox;
    msgBox.setText(QString::fromStdString(str));
    msgBox.exec();
}

void tlinsWTarget::on_btFind_clicked()
{
    searchWindow.show();
}

void tlinsWTarget::dataSelected()
{
    std::vector<int> records;
    TlinsAstroBase::tlinsAstroCatalogCollection result;
    searchWindow.getSelectedRows(records, result);

    for (int i = 0; i < result.count(); i++) {
        auto item = result.getItem(i);

        target.setObjectName(item.getName());
        target.setRA(item.getRA());
        target.setDC(item.getDC());
        target.setPmRA(item.getPmRA());
        target.setPmDC(item.getPmDC());
        target.setRadialVelocity(item.getRadialVelocity());
        target.setParallex(item.getParallex());

        target.setCatalogType(item.getCatalogType().label);
        target.setObjectType(item.getType().label);
        target.setConstelation(item.getConstelation().label);
        target.setObjectName(target.getObjectName());
        target.setMagnitutde(item.getMagnitude());

        target.setSpeed(0.0);
        target.setAceleration(0.0);
        target.setDelta(0);
        setControls();
        isSet = true;
        break;
    }
}

void tlinsWTarget::setObject()
{
    if (::fabs(target.getRA() - ui->RA->getValue()) > std::numeric_limits<double>::epsilon())
        target.setRA(ui->RA->getValue());

    if (::fabs(target.getDC() - ui->DC->getValue()) > std::numeric_limits<double>::epsilon())
        target.setDC(ui->DC->getValue());

    if (::fabs(target.getPmRA() - ui->pmRA->getValue()) > std::numeric_limits<double>::epsilon())
        target.setPmRA(ui->pmRA->getValue());

    if (::fabs(target.getPmDC() - ui->pmDC->getValue()) > std::numeric_limits<double>::epsilon())
        target.setPmDC(ui->pmDC->getValue());

    if (::fabs(target.getRadialVelocity() - ui->radialVelocity->getValue()) > std::numeric_limits<double>::epsilon())
        target.setRadialVelocity(ui->radialVelocity->getValue());

    if (::fabs(target.getParallex() - ui->parallex->getValue()) > std::numeric_limits<double>::epsilon())
        target.setParallex(ui->parallex->getValue());

    if (target.getCatalogType() != ui->catalogType->getType())
        target.setCatalogType(ui->catalogType->getType());

    if (target.getObjectType() != ui->objectType->getType())
        target.setObjectType(ui->objectType->getType());

    if (target.getConstelation() != ui->objectConstelation->getConstelation())
        target.setConstelation(ui->objectConstelation->getConstelation());

    if (target.getObjectName() != ui->objectName->getValue())
        target.setObjectName(ui->objectName->getValue());

    if (::fabs(target.getMagnitutde() - ui->magnitude->getValue()) > std::numeric_limits<double>::epsilon())
        target.setMagnitutde(ui->magnitude->getValue());

    if (::fabs(target.getSpeed() - ui->speed->getValue()) > std::numeric_limits<double>::epsilon())
        target.setSpeed(ui->speed->getValue());

    if (::fabs(target.getAceleration() - ui->aceleration->getValue()) > std::numeric_limits<double>::epsilon())
        target.setAceleration(ui->aceleration->getValue());

    if (::fabs(target.getDelta() - ui->delta->getValue()) > std::numeric_limits<double>::epsilon())
        target.setDelta(static_cast<long>(ui->delta->getValue()));
}

tlinsWTarget::tlinsWTarget(QWidget* parent)
    : QWidget { parent }
    , searchWindow { this }
    , ui { new Ui::tlinsWTarget }
{
    ui->setupUi(this);

    ui->magnitude->disableButtons();
    ui->magnitude->setDecimal(9);
    ui->radialVelocity->disableButtons();
    ui->radialVelocity->setDecimal(9);
    ui->parallex->disableButtons();
    ui->parallex->setDecimal(9);
    ui->speed->disableButtons();
    ui->speed->setDecimal(9);
    ui->aceleration->disableButtons();
    ui->aceleration->setDecimal(9);

    ui->delta->disableButtons();
    ui->delta->setDecimal(0);

    // Inicialna zawartosc kontrolek
    setControls();
    isSet = false;

    // Okno wyszukiwania pracuje w trybie pojedynczego wiersza
    searchWindow.singleRowSelectionMode();

    // Wizanie sygnalow
    connect(&searchWindow, SIGNAL(selectionAccepted()),
        this, SLOT(dataSelected()));

    connect(this, SIGNAL(notiStatus(std::string)),
        this, SLOT(notiStatusSlot(std::string)), Qt::BlockingQueuedConnection);
}

tlinsWTarget::~tlinsWTarget()
{
    delete ui;
}
