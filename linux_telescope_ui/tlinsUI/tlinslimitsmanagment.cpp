#include "tlinslimitsmanagment.h"
#include "tlinsconfiguration.h"
#include "ui_tlinslimitsmanagment.h"

#include "tlinsuimainwindow.h"

#include <Eigen/Geometry>

#include <tlinAttitudeUtilsClass.hpp>
#include <tlins_math.hpp>
#include <tlinscommunicationthread.h>

#include <QDebug>
#include <QMessageBox>

//
// Zapytanie pobierajace aktualne wspolrzedne teleksopu
//
class tlinsLimitsPositionInfoRequest : public TlinsAstroBase::tlinsCommunicationThreadRequest {
private:
    bool leftPositionInfo;
    tlinsLimitsManagmentWidget* master;
    std::shared_ptr<TlinsAstroBase::tlinsConnectionContext> connection;

public:
    virtual void operator()() noexcept;
    virtual bool isAsynchronuus();
    virtual std::string name();
    tlinsLimitsPositionInfoRequest(tlinsLimitsManagmentWidget* _ptr, const bool leftPositionInfo_);
    virtual ~tlinsLimitsPositionInfoRequest() = default;
};

void tlinsLimitsPositionInfoRequest::operator()() noexcept
{
    if (master == nullptr) {
        return;
    }

    // Nazwa urzadzenia glownego
    std::string mainDevName = "main";
    auto& cfg = TlinsAstroBase::tlinsConfiguration::getInstance();

    if (cfg.hasKey(TlinsAstroBase::tlinsConfiguration::COMMON_PARAMETER_GROUP, TlinsAstroBase::tlinsConfiguration::COMMON_MAIN_DEVICE_NAME))
        mainDevName = cfg.getString(TlinsAstroBase::tlinsConfiguration::COMMON_PARAMETER_GROUP, TlinsAstroBase::tlinsConfiguration::COMMON_MAIN_DEVICE_NAME);

    // Rezultat
    std::map<std::string, tlinsMoveServerInterface::AxisPositionInfo> result;
    std::map<std::string, tlinsMoveServerInterface::tlinsDeviceAxisInfo> resultInfo;

    // Pobranie pozycji
    try {
        connection->getDevice()->positionInfo(mainDevName, result);
        connection->getDevice()->deviceConfiguration(mainDevName, resultInfo);

    } catch (...) {
        // TODO
        // TODO
        return;
    }

    auto xItem = result.find("X");
    auto xItemInfo = resultInfo.find("X");
    if (xItem == result.end()) {
        return;
    }

    auto yItem = result.find("Y");
    auto yItemInfo = resultInfo.find("Y");
    if (yItem == result.end()) {
        return;
    }

    double alfa = tlinsMath::PI_2 * static_cast<double>(xItem->second.get_position()) / static_cast<double>(xItemInfo->second.get_deviceResolution());
    double beta = tlinsMath::PI_2 * static_cast<double>(yItem->second.get_position()) / static_cast<double>(yItemInfo->second.get_deviceResolution());

    // Pozycja w ukladzie cartezianskim
    auto cartesian = attitude::tlinAttitudeUtilsClass::toCartesianBase(alfa, beta);

    // Aktualizacja UI
    if (leftPositionInfo) {
        // Uaktualnienie lewej strony
        emit master->updateLeftPositionInfo(cartesian(0), cartesian(1), cartesian(2), alfa, beta);
    } else {
        // Uaktualnienie prawej strony
        emit master->updateRightPositionInfo(cartesian(0), cartesian(1), cartesian(2), alfa, beta);
    }
}

bool tlinsLimitsPositionInfoRequest::isAsynchronuus()
{
    return false;
}

std::string tlinsLimitsPositionInfoRequest::name()
{
    return "tlinsLimitsPositionInfoRequest";
}

tlinsLimitsPositionInfoRequest::tlinsLimitsPositionInfoRequest(tlinsLimitsManagmentWidget* _ptr, const bool leftPositionInfo_)
    : leftPositionInfo { leftPositionInfo_ }
    , master { _ptr }
{
    // Pobranie polaczenia
    if (!TlinsAstroBase::tlinsConnectionsManager::getInstance().hasConnection(std::string { TLINS_CONNECTION_DEFAULT }))
        __THROW__(tlinsException(std::string("No active connection: ") + std::string(TLINS_CONNECTION_DEFAULT), -1));

    // Polaczenie
    connection = TlinsAstroBase::tlinsConnectionsManager::getInstance().getConnection(TLINS_CONNECTION_DEFAULT);
}

//
// Zapytanie pobierajace aktualne wspolrzedne teleksopu
//
class tlinsLimitsEnableRequest : public TlinsAstroBase::tlinsCommunicationThreadRequest {
private:
    bool enable;
    tlinsLimitsManagmentWidget* master;
    std::shared_ptr<TlinsAstroBase::tlinsConnectionContext> connection;

public:
    virtual void operator()() noexcept;
    virtual bool isAsynchronuus();
    virtual std::string name();
    tlinsLimitsEnableRequest(tlinsLimitsManagmentWidget* _ptr, bool enable_);
    virtual ~tlinsLimitsEnableRequest() = default;
};

void tlinsLimitsEnableRequest::operator()() noexcept
{
    if (master == nullptr) {
        return;
    }

    // Nazwa urzadzenia glownego
    std::string mainDevName = "main";
    auto& cfg = TlinsAstroBase::tlinsConfiguration::getInstance();

    if (cfg.hasKey(TlinsAstroBase::tlinsConfiguration::COMMON_PARAMETER_GROUP, TlinsAstroBase::tlinsConfiguration::COMMON_MAIN_DEVICE_NAME))
        mainDevName = cfg.getString(TlinsAstroBase::tlinsConfiguration::COMMON_PARAMETER_GROUP, TlinsAstroBase::tlinsConfiguration::COMMON_MAIN_DEVICE_NAME);

    // Pobranie pozycji
    try {
        if (enable) {
            connection->getDevice()->colistionsDetectionEnable(mainDevName);
            emit master->status(QString { "Collistion detection has started." });
        } else {
            connection->getDevice()->colistionsDetectionDisable(mainDevName);
            emit master->status(QString { "Collistion detection has stoped." });
        }

    } catch (tlinsException& exc) {
        ;
        emit getMainWindowInstance()->logEvent(QString::fromStdString(exc.getErrorMessage()));
        if (enable) {
            emit master->status(QString { "Error start collistion detection." });
        } else {
            emit master->status(QString { "Error stop collistion detection." });
        }
    }
}

bool tlinsLimitsEnableRequest::isAsynchronuus()
{
    return false;
}

std::string tlinsLimitsEnableRequest::name()
{
    return "tlinsLimitsEnableRequest";
}

tlinsLimitsEnableRequest::tlinsLimitsEnableRequest(tlinsLimitsManagmentWidget* _ptr, bool enable_)
    : enable { enable_ }
    , master { _ptr }
{
    // Pobranie polaczenia
    if (!TlinsAstroBase::tlinsConnectionsManager::getInstance().hasConnection(std::string { TLINS_CONNECTION_DEFAULT }))
        __THROW__(tlinsException(std::string("No active connection: ") + std::string(TLINS_CONNECTION_DEFAULT), -1));

    // Polaczenie
    connection = TlinsAstroBase::tlinsConnectionsManager::getInstance().getConnection(TLINS_CONNECTION_DEFAULT);
}

//
// ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
void tlinsLimitsManagmentWidget::slotStatus(const QString msg)
{
    QMessageBox msgBox;
    msgBox.setText(msg);
    msgBox.exec();
}

void tlinsLimitsManagmentWidget::on_pbStart_clicked()
{
    try {
        // Wysalnie rzadania
        std::unique_ptr<TlinsAstroBase::tlinsCommunicationThreadRequest> req(new tlinsLimitsEnableRequest { this, true });
        TlinsAstroBase::tlinsCommunicationThread::getInstance().push(req);
    } catch (tlinsException& exc) {
        std::string m { "Error enable collition limit." };
        m += exc.getErrorMessage().c_str();
        emit getMainWindowInstance()->logEvent(QString::fromStdString(m));
        QMessageBox msgBox;
        msgBox.setText(QString::fromStdString(m));
        msgBox.exec();
    }
}

void tlinsLimitsManagmentWidget::on_pbStop_clicked()
{
    try {
        // Wysalnie rzadania
        std::unique_ptr<TlinsAstroBase::tlinsCommunicationThreadRequest> req(new tlinsLimitsEnableRequest { this, false });
        TlinsAstroBase::tlinsCommunicationThread::getInstance().push(req);
    } catch (tlinsException& exc) {
        std::string m { "Error disable collition limit." };
        m += exc.getErrorMessage().c_str();
        emit getMainWindowInstance()->logEvent(QString::fromStdString(m));
        QMessageBox msgBox;
        msgBox.setText(QString::fromStdString(m));
        msgBox.exec();
    }
}

void tlinsLimitsManagmentWidget::on_pbDevLeft_clicked()
{
    try {
        // Wysalnie rzadania
        std::unique_ptr<TlinsAstroBase::tlinsCommunicationThreadRequest> req(new tlinsLimitsPositionInfoRequest { this, true });
        TlinsAstroBase::tlinsCommunicationThread::getInstance().push(req);
    } catch (tlinsException& exc) {
        std::string m { "Error read postion info." };
        m += exc.getErrorMessage().c_str();
        emit getMainWindowInstance()->logEvent(QString::fromStdString(m));
        QMessageBox msgBox;
        msgBox.setText(QString::fromStdString(m));
        msgBox.exec();
    }
}

void tlinsLimitsManagmentWidget::on_pbDevRight_clicked()
{
    try {
        // Wysalnie rzadania
        std::unique_ptr<TlinsAstroBase::tlinsCommunicationThreadRequest> req(new tlinsLimitsPositionInfoRequest { this, false });
        TlinsAstroBase::tlinsCommunicationThread::getInstance().push(req);
    } catch (tlinsException& exc) {
        std::string m { "Error read postion info." };
        m += exc.getErrorMessage().c_str();
        emit getMainWindowInstance()->logEvent(QString::fromStdString(m));
        QMessageBox msgBox;
        msgBox.setText(QString::fromStdString(m));
        msgBox.exec();
    }
}

void tlinsLimitsManagmentWidget::newLimit()
{
}
void tlinsLimitsManagmentWidget::addLimit()
{
}
void tlinsLimitsManagmentWidget::removeLimit()
{
}
void tlinsLimitsManagmentWidget::storeLimit()
{
}
void tlinsLimitsManagmentWidget::loadLimit()
{
}

void tlinsLimitsManagmentWidget::slotUpdateLeftPositionInfo(const double x, const double y, const double z, const double alfa, const double beta)
{
    lX = x;
    lY = y;
    lY = z;
    lAlfa = alfa;
    lBeta = alfa;

    ui->lalfa->setValue(alfa);
    ui->lbeta->setValue(beta);
    ui->lx->setValue(x);
    ui->ly->setValue(y);
    ui->lz->setValue(z);
}

void tlinsLimitsManagmentWidget::slotUpdateRightPositionInfo(const double x, const double y, const double z, const double alfa, const double beta)
{
    rX = x;
    rY = y;
    rY = z;
    rAlfa = alfa;
    rBeta = alfa;

    ui->ralfa->setValue(alfa);
    ui->rbeta->setValue(beta);
    ui->rx->setValue(x);
    ui->ry->setValue(y);
    ui->rz->setValue(z);
}

tlinsLimitsManagmentWidget::tlinsLimitsManagmentWidget(QWidget* parent)
    : QWidget(parent)
    , ui(new Ui::tlinsLimitsManagmentWidget)
{
    ui->setupUi(this);

    connect(ui->pbDeviceRight, SIGNAL(clicked()), this, SLOT(on_pbDevRight_clicked()));
    connect(ui->pbDeviceLeft, SIGNAL(clicked()), this, SLOT(on_pbDevLeft_clicked()));

    connect(ui->pbLoad, SIGNAL(clicked()), this, SLOT(loadLimit()));
    connect(ui->pbStore, SIGNAL(clicked()), this, SLOT(storeLimit()));
    connect(ui->pbAdd, SIGNAL(clicked()), this, SLOT(addLimit()));
    connect(ui->pbNew, SIGNAL(clicked()), this, SLOT(newLimit()));
    connect(ui->pbRemove, SIGNAL(clicked()), this, SLOT(removeLimit()));
    connect(this, SIGNAL(status(QString)), this, SLOT(slotStatus(QString)));

    connect(this, SIGNAL(updateLeftPositionInfo(const double, const double, const double, const double, const double)), this, SLOT(slotUpdateLeftPositionInfo(const double, const double, const double, const double, const double)));
    connect(this, SIGNAL(updateRightPositionInfo(const double, const double, const double, const double, const double)), this, SLOT(slotUpdateRightPositionInfo(const double, const double, const double, const double, const double)));
}

tlinsLimitsManagmentWidget::~tlinsLimitsManagmentWidget()
{
    delete ui;
}
