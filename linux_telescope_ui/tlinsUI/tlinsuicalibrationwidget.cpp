#include "tlinsuicalibrationwidget.h"
#include "ui_tlinsuicalibrationwidget.h"

#include "tlinsAstroEngineInterface.hpp"
#include "tlinsastrobaseutils.h"
#include "tlinsastroobjectsviewmodel.h"
#include "tlinscommunicationthread.h"
#include "tlinsserverstatusinfo.h"
#include "tlinsuiconfgiurationitem.h"
#include "tlinsuidatabase.h"
#include "tlinsuidatabasedefinition.h"
#include "tlinsuimainwindow.h"

#include <tlinAttitudeUtilsClass.hpp>
#include <tlinsTimeInfo.hpp>
#include <tlins_math.hpp>
#include <tlinsastrouibase.h>

#include <QAction>
#include <QDebug>
#include <QFont>
#include <QMessageBox>
#include <QStyle>
#include <QtGui>
#include <qmessagebox.h>
#include <sofa.h>
#include <sofam.h>
#include <string>
#include <tlinsBacktrace.hpp>

#define _PI_ 3.141592653589793238462643

static void splitRA(const double in, tlinsAstroEngineInterface::tlinsCoordinate& ra)
{
    int h;
    int m;
    double s;
    bool sign;
    TlinsAstroBase::tlinsAstroBaseUtils::splitRA(in, h, m, s, sign);

    ra.set_sign(sign);
    ra.set_degris(h);
    ra.set_minutes(m);
    ra.set_seconds(s);
}

static void splitDC(const double in, tlinsAstroEngineInterface::tlinsCoordinate& dc)
{
    int d;
    int m;
    double s;
    bool sign;
    TlinsAstroBase::tlinsAstroBaseUtils::splitDegris(in, d, m, s, sign);

    dc.set_sign(sign);
    dc.set_degris(d);
    dc.set_minutes(m);
    dc.set_seconds(s);
}

static void splitDegris(const double in, tlinsAstroEngineInterface::tlinsCoordinate& deg)
{
    splitDC(in, deg);
}

static void setButtonAttrs(QPushButton* bt, const bool enable, const bool italic, const Qt::GlobalColor color)
{
    QAction q;

    bt->setEnabled(enable);

    QFont f { bt->font() };
    f.setItalic(italic);

    bt->setFont(f);

    auto pal = bt->palette();
    pal.setColor(bt->foregroundRole(), color);
    bt->setPalette(pal);
}

static void setTrackingModeAttrs(QLabel* lab, QRadioButton* rb1, QRadioButton* rb2, QRadioButton* rb3, QRadioButton* rb4, const bool enable, const bool italic, const Qt::GlobalColor color)
{
    QAction q;

    QFont f { lab->font() };
    f.setItalic(italic);
    lab->setFont(f);

    auto pal = lab->palette();
    pal.setColor(lab->foregroundRole(), Qt::GlobalColor::white);
    lab->setPalette(pal);

    std::list<QRadioButton*> rbList { rb1, rb2, rb3, rb4 };
    for (auto iter : rbList) {

        QFont f { iter->font() };
        f.setItalic(italic);
        iter->setFont(f);

        auto pal = iter->palette();
        pal.setColor(iter->foregroundRole(), color);
        iter->setPalette(pal);

        iter->setEnabled(enable);
    }
}

void tlinsUICalibrationWidget::checkBoxEnableDebugSlot()
{
    if (ui->checkBoxEnableDebug->isChecked()) {
        ui->groupBoxMatrix->setVisible(true);
    } else {
        ui->groupBoxMatrix->setVisible(false);
    }
}

tlinsUICalibrationWidget::tlinsUICalibrationWidget(QWidget* parent)
    : QWidget(parent)
    , searchWindow { this }
    , dataModel { this }
    , ui(new Ui::tlinsUICalibrationWidget)
{
    debugThreadBusy.store(false);

    ui->setupUi(this);

    // Domyslne ustawienie rodzaju kalibracji
    ui->tManual->setChecked(true);
    ui->tStandard->setChecked(false);
    ui->tSpeed->setChecked(false);
    ui->tGuider->setChecked(false);

    ui->chbXReverse->setChecked(false);
    ui->chbYReverse->setChecked(false);
    ui->axiesDirectionGroup->setChecked(false);

    // Domyślnie opcja debug jest zablokowana
    ui->groupBoxMatrix->setVisible(false);

    ui->referenceObjects->setModel(&dataModel);

    setWindowTitle("Calibration");
    QIcon icon { ":/icons/calibration-mark.svg" };
    setWindowIcon(icon);

    // Sposob rozciagania kolumn w widoku danych
    ui->referenceObjects->horizontalHeader()->resizeSections(QHeaderView::ResizeToContents);
    ui->referenceObjects->horizontalHeader()->setSectionResizeMode(QHeaderView::Interactive);
    ui->referenceObjects->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
    ui->referenceObjects->horizontalHeader()->setFixedHeight(30);

    // Sposob selekcji danych
    ui->referenceObjects->setSelectionMode(QAbstractItemView::MultiSelection);
    ui->referenceObjects->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->referenceObjects->setColumnHidden(dataModel.columnCount() - 1, true);

    // Wiazanie sygnalow
    connect(&searchWindow, SIGNAL(selectionAccepted()),
        this, SLOT(dataSelected()));

    connect(this, SIGNAL(updateRowStatus(const TlinsAstroBase::tlinsAstroCalibrationItem::calibrationStatus, int)),
        this, SLOT(updateRowStatusSlot(const TlinsAstroBase::tlinsAstroCalibrationItem::calibrationStatus, int)), Qt::BlockingQueuedConnection);

    connect(this, SIGNAL(calibrationStatus(std::string, uiChanges)),
        this, SLOT(calibrationStatusSlot(std::string, uiChanges)), Qt::BlockingQueuedConnection);

    //
    // Bledy
    //
    auto& inst = TlinsAstroBase::tlinsConfiguration::getInstance();
    if (inst.hasKey(TlinsAstroBase::tlinsConfiguration::OBSERVATION_ERRORS_GROUP,
            TlinsAstroBase::tlinsConfiguration::OBSERVATION_ERRORS_LONGITUDE)) {
        ui->errors->setLongitudeError(inst.getDouble(TlinsAstroBase::tlinsConfiguration::OBSERVATION_ERRORS_GROUP,
            TlinsAstroBase::tlinsConfiguration::OBSERVATION_ERRORS_LONGITUDE));
        ui->errors->setLatitudeError(inst.getDouble(TlinsAstroBase::tlinsConfiguration::OBSERVATION_ERRORS_GROUP,
            TlinsAstroBase::tlinsConfiguration::OBSERVATION_ERRORS_LATITUDE));
        ui->errors->setWeight(inst.getDouble(TlinsAstroBase::tlinsConfiguration::OBSERVATION_ERRORS_GROUP,
            TlinsAstroBase::tlinsConfiguration::OBSERVATION_ERRORS_WEIGHT));
    } else {
        ui->errors->setLongitudeError(0.0);
        ui->errors->setLatitudeError(0.0);
        ui->errors->setWeight(0.0);
    }

    ui->chbOverriteErrors->setChecked(false);
    ui->errors->hide();

    connect(ui->chbOverriteErrors, SIGNAL(clicked(bool)), this, SLOT(errorsStateChanged(bool)));
    searchWindow.singleRowSelectionMode();

    //
    // Inicialny stan przyciskow
    //
    setButtonAttrs(ui->btStartCalibration, true, false, Qt::GlobalColor::white);
    setButtonAttrs(ui->btSetReference, false, true, Qt::GlobalColor::white);
    setButtonAttrs(ui->btCloseCalibration, false, true, Qt::GlobalColor::white);
    ui->groupBoxTrackingMode->setEnabled(false);
    setTrackingModeAttrs(ui->label, ui->tGuider, ui->tManual, ui->tSpeed, ui->tStandard, false, true, Qt::GlobalColor::white);

    ui->checkAsDeferred->setChecked(false);
    ui->confirmDeferred->setEnabled(false);
}

class tlinsCalibrationSetDateTime : public TlinsAstroBase::tlinsCommunicationThreadRequest {
private:
    std::shared_ptr<TlinsAstroBase::tlinsConnectionContext> connection;
    tlinsUICalibrationWidget* parent;
    int year;
    int month;
    int day;
    int hour;
    int minute;
    int second;

public:
    void operator()() noexcept
    {
        try {
            // Nie przekazujemy wejscia z kontrolera
            connection->getDevice()->setDateTime(year, month, day, hour, minute, second);
        } catch (tlinsInterfaceException& exc) {
            auto msg = std::string { "Error set date time: " } + exc.getErrorMessage();
            emit getMainWindowInstance()->logEvent(QString::fromStdString(msg));
            parent->calibrationStatusEmit(msg, tlinsUICalibrationWidget::uiChanges::NO_CHANGES);
            return;
        }
    }

    bool isAsynchronuus()
    {
        return false;
    }

    std::string name()
    {
        return "tlinsCalibrationSetDateTime";
    }

    tlinsCalibrationSetDateTime(tlinsUICalibrationWidget* parent_,
        const int year_,
        const int month_,
        const int day_,
        const int hour_,
        const int minute_,
        const int second_)
        : parent { parent_ }
        , year { year_ }
        , month { month_ }
        , day { day_ }
        , hour { hour_ }
        , minute { minute_ }
        , second { second_ }
    {
        if (!TlinsAstroBase::tlinsConnectionsManager::getInstance().hasConnection(std::string { TLINS_CONNECTION_DEFAULT }))
            __THROW__(tlinsInterfaceException(std::string("No active connection: ") + std::string(TLINS_CONNECTION_DEFAULT), -1));

        // Polaczenie
        connection = TlinsAstroBase::tlinsConnectionsManager::getInstance().getConnection(TLINS_CONNECTION_DEFAULT);
    }

    virtual ~tlinsCalibrationSetDateTime()
    {
        connection.reset();
    }
};

class tlinsDebugSetPosition : public TlinsAstroBase::tlinsCommunicationThreadRequest {
private:
    std::shared_ptr<TlinsAstroBase::tlinsConnectionContext> connection;
    long x;
    long y;

public:
    virtual void operator()() noexcept
    {
        try {
            // Nazwa urzadzenia glownego
            std::string mainDeviceName { "main" };
            auto& cfg = TlinsAstroBase::tlinsConfiguration::getInstance();

            if (cfg.hasKey(TlinsAstroBase::tlinsConfiguration::COMMON_PARAMETER_GROUP,
                    TlinsAstroBase::tlinsConfiguration::COMMON_MAIN_DEVICE_NAME))
                mainDeviceName = cfg.getString(TlinsAstroBase::tlinsConfiguration::COMMON_PARAMETER_GROUP,
                    TlinsAstroBase::tlinsConfiguration::COMMON_MAIN_DEVICE_NAME);

            std::map<std::string, tlinsMoveServerInterface::AxisPositionInfo> axis;

            tlinsMoveServerInterface::AxisPositionInfo xx {};
            xx.set_axisName("X");
            xx.set_position(x);
            xx.set_positionEncoder(x);

            tlinsMoveServerInterface::AxisPositionInfo yy {};
            yy.set_axisName("Y");
            yy.set_position(y);
            yy.set_positionEncoder(y);

            axis["X"] = xx;
            axis["Y"] = yy;

            // Uruchomienie zapytania
            connection->getDevice()->setPosition(mainDeviceName, axis);

            emit getMainWindowInstance()->logEvent("Position set");
        } catch (tlinsInterfaceException& exc) {
            QString msg { "Error" };
            msg += exc.getErrorMessage().c_str();
            emit getMainWindowInstance()->logEvent(msg);
            emit getMainWindowInstance()->logEvent(msg);
        }
    }

    virtual bool isAsynchronuus()
    {
        return false;
    }

    virtual std::string name()
    {
        return "tlinsDebugSetPosition";
    }

    tlinsDebugSetPosition(const long x_, const long y_)
        : x { x_ }
        , y { y_ }
    {
        // Pobranie polaczenia
        if (!TlinsAstroBase::tlinsConnectionsManager::getInstance().hasConnection(std::string { TLINS_CONNECTION_DEFAULT }))
            __THROW__(tlinsException(std::string("No active connection: ") + std::string(TLINS_CONNECTION_DEFAULT), -1));

        // Polaczenie
        connection = TlinsAstroBase::tlinsConnectionsManager::getInstance().getConnection(TLINS_CONNECTION_DEFAULT);
    }

    virtual ~tlinsDebugSetPosition()
    {
    }
};

//
// ----------------------------------------------------
// Ustawienie obiektu referencyjnego
// ----------------------------------------------------
//
class tlinsCalibrationSetReferenceObject : public TlinsAstroBase::tlinsCommunicationThreadRequest {
private:
    std::shared_ptr<TlinsAstroBase::tlinsConnectionContext> connection;

private:
    tlinsAstroEngineInterface::tlinsMeserment meserment;
    tlinsUICalibrationWidget* parent;
    bool deferred;
    int row;

public:
    virtual void operator()() noexcept
    {
        try {
            // Nie przekazujemy wejscia z kontrolera
            if (!deferred)
                connection->getAstro()->registerMeserment(meserment, false);
            else
                connection->getAstro()->registerMesermentDefered(meserment);

            // Wygenerowanie potwierdzenia ze obiekt referencyjny zostal dodany
            parent->calibrationStatusEmit("Reference object set", tlinsUICalibrationWidget::uiChanges::SET_REFERENCE);
        } catch (tlinsInterfaceException& exc) {
            auto msg = std::string { "Error set reference object: " } + exc.getErrorMessage();
            emit getMainWindowInstance()->logEvent(QString::fromStdString(msg));
            parent->calibrationStatusEmit(msg, tlinsUICalibrationWidget::uiChanges::NO_CHANGES);
            return;
        }
    }

    virtual bool isAsynchronuus()
    {
        return false;
    }

    virtual std::string name()
    {
        return "tlinsCalibrationSetReferenceObject";
    }

    tlinsCalibrationSetReferenceObject(tlinsUICalibrationWidget* parent_,
        const tlinsAstroEngineInterface::tlinsMeserment& meserment_,
        const int row_,
        const bool deferred_)
        : meserment { meserment_ }
        , parent { parent_ }
        , deferred { deferred_ }
        , row { row_ }
    {
        if (!TlinsAstroBase::tlinsConnectionsManager::getInstance().hasConnection(std::string { TLINS_CONNECTION_DEFAULT })) {
            auto msg = std::string("No active connection: ") + std::string(TLINS_CONNECTION_DEFAULT);
            emit getMainWindowInstance()->logEvent(QString::fromStdString(msg));
            __THROW__(tlinsInterfaceException(std::string("No active connection: ") + std::string(TLINS_CONNECTION_DEFAULT), -1));
        }

        // Polaczenie
        connection = TlinsAstroBase::tlinsConnectionsManager::getInstance().getConnection(TLINS_CONNECTION_DEFAULT);
    }

    virtual ~tlinsCalibrationSetReferenceObject()
    {
        connection.reset();
    }
};

void tlinsUICalibrationWidget::on_btSetReference_clicked()
{
    setReferenceObject2();
}

//
// ----------------------------------------------------
// Zamkniecie kalibracji
// ----------------------------------------------------
//

class tlinsCalibrationClose : public TlinsAstroBase::tlinsCommunicationThreadRequest {
private:
    std::shared_ptr<TlinsAstroBase::tlinsConnectionContext> connection;
    tlinsUICalibrationWidget* parent;
    bool setStandard;
    bool setSpeed;
    bool setGuider;

public:
    virtual void operator()() noexcept
    {
        try {
            //
            // Zamkniecie kalibracji
            //
            connection->getAstro()->closeCalibration();

            //
            // Pobranie aktualnego statusu
            //
            auto& statusInfo = TlinsAstroBase::tlinsServerStatusInfo::getInstance();
            statusInfo.update(connection);

            //
            // Uruchomienie sledzenia
            //
            tlinsAstroEngineInterface::tlinsEngineMode mode { tlinsAstroEngineInterface::tlinsEngineMode::MODE_NONE };

            auto mw = getMainWindowInstance();

            if (setStandard) {
                mode = tlinsAstroEngineInterface::tlinsEngineMode::MODE_STANDARD;
                emit mw->logEvent("Tracking set to STANDARD mode");
            } else if (setSpeed) {
                mode = tlinsAstroEngineInterface::tlinsEngineMode::MODE_STANDARD_SPEED;
                emit mw->logEvent("Tracking set to SPEED mode - speed and manual corrections");
            } else if (setGuider) {
                mode = tlinsAstroEngineInterface::tlinsEngineMode::MODE_EXTERNAL_SUPPORT;
                emit mw->logEvent("Tracking set to GUIDER mode");
            }

            if (setStandard || setSpeed || setGuider) {
                // Ustawienie zadanego trybu pracy
                connection->getAstro()->setMode(mode);

                // Uruchomienie sledzenie
                connection->getAstro()->startTracking();

                emit mw->logEvent("Tracking started");
            }

            //
            // Aktualizacja statusu wiersza nie jest potrzebna
            // Wygenerowanie potwierdzenia ze obiekt referencyjny zostal dodany
            parent->calibrationStatusEmit("Measurment ended and/or started tracking", tlinsUICalibrationWidget::uiChanges::CLOSE_CALIBRATION);
            emit mw->logEvent("Measurment ended");

        } catch (const tlinsInterfaceException&) {
            // Mamy blad wywolania nie bedzie potwierdzenia asynchronicznego
            emit getMainWindowInstance()->logEvent(QString::fromStdString("Error close calibration"));
            parent->calibrationStatusEmit("Error close calibration", tlinsUICalibrationWidget::uiChanges::NO_CHANGES);
        }
    }

    virtual bool isAsynchronuus()
    {
        return false;
    }

    virtual std::string name()
    {
        return "tlinsCalibrationClose";
    }

    tlinsCalibrationClose(tlinsUICalibrationWidget* parent_, const bool setStandard_, const bool setSpeed_, const bool setGuider_)
        : parent { parent_ }
        , setStandard { setStandard_ }
        , setSpeed { setSpeed_ }
        , setGuider { setGuider_ }
    {
        // Pobranie polaczenia
        if (!TlinsAstroBase::tlinsConnectionsManager::getInstance().hasConnection(std::string { TLINS_CONNECTION_DEFAULT })) {
            auto msg = std::string("No active connection: ") + std::string(TLINS_CONNECTION_DEFAULT);
            emit getMainWindowInstance()->logEvent(QString::fromStdString(msg));
            __THROW__(tlinsException(std::string("No active connection: ") + std::string(TLINS_CONNECTION_DEFAULT), -1));
        }

        // Polaczenie
        connection = TlinsAstroBase::tlinsConnectionsManager::getInstance().getConnection(TLINS_CONNECTION_DEFAULT);
    }

    virtual ~tlinsCalibrationClose()
    {
        connection.reset();
    }
};

void tlinsUICalibrationWidget::closeCalibration()
{
    try {
        auto ptr = new tlinsCalibrationClose { this, ui->tStandard->isChecked(), ui->tSpeed->isChecked(), ui->tGuider->isChecked() };
        std::unique_ptr<TlinsAstroBase::tlinsCommunicationThreadRequest> req(ptr);
        oCount = 0;

        TlinsAstroBase::tlinsCommunicationThread::getInstance().push(req);
    } catch (tlinsInterfaceException& exc) {
        std::string m { "Error start/reset calibration. " };
        m += exc.getErrorMessage().c_str();
        emit getMainWindowInstance()->logEvent(QString::fromStdString(m));
        calibrationStatusEmit(m, tlinsUICalibrationWidget::uiChanges::NO_CHANGES);
    }
}

void createSendMoveRequest(const double x,
    const double y,
    const long vX,
    const long vY,
    const long aX,
    const long aY,
    const double xDResolution,
    const double yDResolution,
    tlinsMoveServerInterface::MoveRequestDevice& request)
{
    // Os X
    {
        tlinsMoveServerInterface::MoveRequestItem data;

        // - Odleglosc
        double xDistanceD = ::round(x * tlinsMath::PI_1_DIV_2 * xDResolution);
        long xDistance = static_cast<long>(xDistanceD);
        data.set_distance(xDistance);

        // Predkosc przemieszczenia
        data.set_V(vX);

        // - Przyspieszenie i hamowanie. Przeliczenie A i D na kroki
        data.set_A(aX);
        data.set_D(aX);

        // - Kierunek
        data.set_direction(tlinsMoveServerInterface::RequestDirection::RIGHT);
        request.getRequestItems()["X"] = data;
        TLINS_LOG_DEBUG("xDistance = " + std::to_string(xDistance));
    }

    // Os Y
    {
        tlinsMoveServerInterface::MoveRequestItem data;

        // - Odleglosc
        double yDistanceD = ::round(y * tlinsMath::PI_1_DIV_2 * yDResolution);
        long yDistance = static_cast<long>(yDistanceD);
        data.set_distance(yDistance);

        // - Predkosc
        data.set_V(vY);

        // - Przyspieszenie i hamowanie. Przeliczenie A i D na kroki
        data.set_A(aY);
        data.set_D(aY);

        // - Kierunek
        data.set_direction(tlinsMoveServerInterface::RequestDirection::RIGHT);
        request.getRequestItems()["Y"] = data;
        TLINS_LOG_DEBUG("yDistance = " + std::to_string(yDistance));
    }

    // Parametery rzadania
    {
        request.set_moveType(tlinsMoveServerInterface::MoveType::MOVE);
        request.set_interpolationType(tlinsMoveServerInterface::InterpolationType::LINEAR);
        request.set_relAbs(tlinsMoveServerInterface::ModeRelAbs::ABS);
    }

    // Parametery rampy w trybie interpolowanym
    {
        request.set_A(aX);
        request.set_D(aX);
        request.set_V(vX);
    }
}

//
// Obiekt rzadania
//
class tlinsMoveRequest : public TlinsAstroBase::tlinsCommunicationThreadRequest {
private:
    class moveCb : public tlinsMoveServerInterface::tlinsMoveRequestConfirmation {
    private:
        std::condition_variable& cv;
        std::mutex& mtx;
        bool& confirmed;

        tlinsMoveRequest& parent;

    public:
        void process(const tlins::tlinsRpcConfirmationStatus& status);
        bool release();

        moveCb(tlinsMoveRequest& parent_, std::condition_variable& cv_, std::mutex& mtx_, bool& confirmed_)
            : cv { cv_ }
            , mtx { mtx_ }
            , confirmed { confirmed_ }
            , parent { parent_ }
        {
        }

        virtual ~moveCb()
        {
        }
    };

    std::shared_ptr<tlinsMoveServerInterface::tlinsMoveRequestConfirmation> callback;
    std::shared_ptr<TlinsAstroBase::tlinsConnectionContext> connection;

private:
    std::unique_ptr<tlinsMoveServerInterface::MoveRequestDevice> request;

    std::condition_variable& cv;
    std::mutex& mtx;
    bool& confirmed;

public:
    void confirm();

    virtual void operator()() noexcept;
    virtual bool isAsynchronuus();
    virtual std::string name()
    {
        return "tlinsMoveRequest";
    }

    tlinsMoveRequest(std::unique_ptr<tlinsMoveServerInterface::MoveRequestDevice>& ptr, std::condition_variable& cv_, std::mutex& mtx_, bool& confirmed_);
    virtual ~tlinsMoveRequest();
};

void tlinsMoveRequest::moveCb::process(const tlins::tlinsRpcConfirmationStatus&)
{
    // Ustawienie flagi
    {
        std::unique_lock<std::mutex> lk(mtx);
        confirmed = true;
    }

    // Notyfikowanie procesu
    cv.notify_all();
}

bool tlinsMoveRequest::moveCb::release()
{
    return true;
}

void tlinsMoveRequest::confirm()
{
    TlinsAstroBase::tlinsCommunicationThreadRequest::confirm();
}

void tlinsMoveRequest::operator()() noexcept
{
    try {
        // Nazwa urzadzenia glownego
        std::string mainDeviceName = "main";
        auto& cfg = TlinsAstroBase::tlinsConfiguration::getInstance();

        if (cfg.hasKey(TlinsAstroBase::tlinsConfiguration::COMMON_PARAMETER_GROUP,
                TlinsAstroBase::tlinsConfiguration::COMMON_MAIN_DEVICE_NAME))
            mainDeviceName = cfg.getString(TlinsAstroBase::tlinsConfiguration::COMMON_PARAMETER_GROUP,
                TlinsAstroBase::tlinsConfiguration::COMMON_MAIN_DEVICE_NAME);

        // Uruchomienie zapytania
        connection->getDevice()->moveRequest(mainDeviceName, *request, callback);
    } catch (tlinsInterfaceException&) {
        // Mamy blad wywolania nie bedzie potwierdzenia asynchronicznego
        emit getMainWindowInstance()->logEvent(QString::fromStdString("Error set move request"));
        confirm();
        return;
    }
}

bool tlinsMoveRequest::isAsynchronuus()
{
    return true;
}

tlinsMoveRequest::tlinsMoveRequest(std::unique_ptr<tlinsMoveServerInterface::MoveRequestDevice>& ptr,
    std::condition_variable& cv_,
    std::mutex& mtx_,
    bool& confirmed_)
    : request { std::move(ptr) }
    , cv { cv_ }
    , mtx { mtx_ }
    , confirmed { confirmed_ }
{
    // Pobranie polaczenia
    if (!TlinsAstroBase::tlinsConnectionsManager::getInstance().hasConnection(std::string { TLINS_CONNECTION_DEFAULT }))
        __THROW__(tlinsException(std::string("No active connection: ") + std::string(TLINS_CONNECTION_DEFAULT), -1));

    // Polaczenie
    connection = TlinsAstroBase::tlinsConnectionsManager::getInstance().getConnection(TLINS_CONNECTION_DEFAULT);

    // Obiekt potwierdzen
    callback.reset(new moveCb { *this, cv, mtx, confirmed });
}

tlinsMoveRequest::~tlinsMoveRequest()
{
    connection.reset();
}

double d2r(const double val)
{
    return val / 360.0 * 2.0 * _PI_;
}

double h2r(const double val)
{
    double v = 360.0 * val / 24.0;
    return d2r(v);
}

void tlinsUICalibrationWidget::setReferenceObject2(const int inrow)
{
    if (debugThreadBusy) {
        emit getMainWindowInstance()->popupStatusSlot("[DEBUG] Debug thread bussy - plase wait !!!!");
        return;
    }

    try {
        // Dane
        auto& data = dataModel.getCalibrationData();

        if (data.empty()) {
            QMessageBox msgBox;
            msgBox.setText("No calibration objects");
            msgBox.exec();
            return;
        }

        int row = 0;
        for (auto& item : data) {
            if (item.getStatus() == TlinsAstroBase::tlinsAstroCalibrationItem::calibrationStatus::COMPLETED) {
                // Obiekt jest juz wziety lub byl wziety
                row++;
                continue;
            }

            auto setMeasurment = [](tlinsUICalibrationWidget* parent, TlinsAstroBase::tlinsAstroCalibrationItem item, int row) {
                // Pomiar
                tlinsAstroEngineInterface::tlinsMeserment meserment;

                // Kat godzinowy
                tlinsAstroEngineInterface::tlinsCoordinate ra;
                splitRA(item.getRA(), ra);

                // Dekilnacja
                tlinsAstroEngineInterface::tlinsCoordinate dc;
                splitDC(item.getDC(), dc);

                // Bledy pomiaru
                double loErr_ = 0.0;
                double laErr_ = 0.0;
                double w_ = 0.0;

                if (parent->ui->chbOverriteErrors->isChecked()) {
                    // Bledy nadpisane
                    loErr_ = parent->ui->errors->getLongitudeError();
                    laErr_ = parent->ui->errors->getLatitudeError();
                    w_ = parent->ui->errors->getWeight();
                } else {
                    // Bledy z konfiguracji
                    auto& inst = TlinsAstroBase::tlinsConfiguration::getInstance();
                    if (inst.hasKey(TlinsAstroBase::tlinsConfiguration::OBSERVATION_ERRORS_GROUP,
                            TlinsAstroBase::tlinsConfiguration::OBSERVATION_ERRORS_LONGITUDE)) {
                        loErr_ = inst.getDouble(TlinsAstroBase::tlinsConfiguration::OBSERVATION_ERRORS_GROUP,
                            TlinsAstroBase::tlinsConfiguration::OBSERVATION_ERRORS_LONGITUDE);
                        laErr_ = inst.getDouble(TlinsAstroBase::tlinsConfiguration::OBSERVATION_ERRORS_GROUP,
                            TlinsAstroBase::tlinsConfiguration::OBSERVATION_ERRORS_LATITUDE);
                        w_ = inst.getDouble(TlinsAstroBase::tlinsConfiguration::OBSERVATION_ERRORS_GROUP,
                            TlinsAstroBase::tlinsConfiguration::OBSERVATION_ERRORS_WEIGHT);
                    }
                }

                tlinsAstroEngineInterface::tlinsCoordinate loErr;
                splitDegris(loErr_, loErr);

                tlinsAstroEngineInterface::tlinsCoordinate laErr;
                splitDegris(laErr_, laErr);

                // Obiekt referencyjny
                tlinsAstroEngineInterface::tlinsAstroObject referenceObj;

                // Wspolrzedne obiektu referencyjnego
                referenceObj.set_hourAngle(ra);
                referenceObj.set_declination(dc);

                // Ruch welasny
                referenceObj.set_properMotionRA(item.getPmRA());
                referenceObj.set_properMotionDC(item.getPmDC());

                // Predkosc radianla i paralaksa nie sa aktualnie podawane
                referenceObj.set_radialVelocity(item.getRadialVelocity());
                referenceObj.set_parallax(item.getParallex());

                // Typ catalogu
                referenceObj.set_catalogType(item.getCatalogType().label);

                //
                // Kompletny objet referencyjny
                //
                meserment.set_reference(referenceObj);

                // Blad pomiaru
                tlinsAstroEngineInterface::tlinsFullCoordinate inError;
                inError.set_longitude(loErr);
                inError.set_latitude(laErr);
                meserment.set_inputError(inError);

                // Waga
                meserment.set_w(w_);

                // Wstawienie rzadania
                parent->currentRefObjectRow = row;
                std::unique_ptr<TlinsAstroBase::tlinsCommunicationThreadRequest> req(new tlinsCalibrationSetReferenceObject { parent,
                    meserment,
                    row,
                    parent->ui->checkAsDeferred->isChecked() });
                TlinsAstroBase::tlinsCommunicationThread::getInstance().push(req);
            };

            // Przygotowanie pod debugowanie
            if (ui->checkBoxEnableDebug->isChecked()) {
                //
                // --- Wlaczone debagowanie
                //
                if (debugThread && debugThread->joinable())
                    debugThread->join();

                auto debugThread_ = [row, item, &setMeasurment](tlinsUICalibrationWidget* parent) {
                    parent->debugThreadBusy.store(true);

                    // Wspolrzedna obiektu referencyjnego w ukladzie kartezianskim
                    Eigen::Vector3d refCart;
                    attitude::tlinAttitudeUtilsClass::toCartesian(h2r(item.getRA()), d2r(item.getDC()), refCart);

                    Eigen::Matrix3d rotMatrix;
                    rotMatrix(0, 0) = parent->ui->a11->value();
                    rotMatrix(0, 1) = parent->ui->a12->value();
                    rotMatrix(0, 2) = parent->ui->a13->value();
                    rotMatrix(1, 0) = parent->ui->a21->value();
                    rotMatrix(1, 1) = parent->ui->a22->value();
                    rotMatrix(1, 2) = parent->ui->a23->value();
                    rotMatrix(2, 0) = parent->ui->a31->value();
                    rotMatrix(2, 1) = parent->ui->a32->value();
                    rotMatrix(2, 2) = parent->ui->a33->value();

                    int seq = 0;
                    do {
                        //
                        // Petla bedzie wykonana dwukrotnie
                        // Poniewaz potencialnie pierwsze przemieszczenie będzie dlugie
                        //

                        // Okreslenie kata obrotu ziemi
                        auto& tInfo = tlinsTimeInfo::getInstance();
                        tInfo.update();

                        double earthAngle = ::iauEra00(tInfo.getD1(), tInfo.getD2());
                        TLINS_LOG_DEBUG("earthAngle = " + std::to_string(earthAngle));
                        TLINS_LOG_DEBUG("tInfo.getD1() = " + std::to_string(tInfo.getD1()));
                        TLINS_LOG_DEBUG("tInfo.getD2() = " + std::to_string(tInfo.getD2()));

                        // Macierz obrotu wokol osi Z i obrot obiektu referencyjnego
                        Eigen::Matrix3d zRot;
                        attitude::tlinAttitudeUtilsClass::buildZRotaionMatrix(-1.0 * earthAngle, zRot);
                        TLINS_LOG_DEBUG("earthAngle = " + std::to_string(earthAngle));

                        // Obiekt referencyjny po wykonaniu obrotu
                        Eigen::Vector3d refCartRot;
                        refCartRot = zRot * refCart;
                        PRINT_M(refCart, "refCart       ", "%f");
                        PRINT_M(refCartRot, "refCartRot    ", "%f");
                        PRINT_M(zRot, "zRot          ", "%f");

                        //
                        // Wyzaczenie pozycji teleskopu
                        //

                        // Pozycja urzadzenia wukladzie kartezjanskim
                        Eigen::Vector3d devCart = rotMatrix.inverse() * refCartRot;
                        PRINT_M(rotMatrix, "rotMatrix          ", "%f");
                        PRINT_M(devCart, "devCart          ", "%f");

                        // Pozycja urzadzenia w ukladzie sferyznym
                        Eigen::Vector2d devOut;
                        attitude::tlinAttitudeUtilsClass::toSpeherical(devCart, devOut);
                        PRINT_M(devOut, "devOut          ", "%f");

                        while (devOut(0) < 0.0) {
                            devOut(0) += tlinsMath::PI_2;
                        }

                        while (devOut(0) > tlinsMath::PI_2) {
                            devOut(0) -= tlinsMath::PI_2;
                        }

                        while (devOut(1) < 0.0) {
                            devOut(1) += tlinsMath::PI_2;
                        }

                        while (devOut(1) > tlinsMath::PI_2) {
                            devOut(1) -= tlinsMath::PI_2;
                        }

                        if (parent->ui->axiesDirectionGroup->isChecked()) {
                            if (parent->ui->chbXReverse->isChecked()) {
                                devOut(0) = tlinsMath::PI_2 - devOut(0);
                            }
                            if (parent->ui->chbYReverse->isChecked()) {
                                devOut(1) = tlinsMath::PI_2 - devOut(1);
                            }
                        }

                        //
                        // Wslanie rzadania przemieszczenia do urzadzenia i czekanie na zakonczenie przemieszczenia
                        //

                        // Tworzenie rzadania przemieszczenia
                        // Parametery predkosci, przyspieszenia, ... zapisane na stale
                        std::unique_ptr<tlinsMoveServerInterface::MoveRequestDevice> reqPtr { new tlinsMoveServerInterface::MoveRequestDevice {} };
                        createSendMoveRequest(devOut(0),
                            devOut(1),
                            /*const long vX*/ 64000,
                            /*const long vY*/ 64000,
                            /*const long aX*/ 64000000,
                            /*const long aY*/ 64000000,
                            /*const double xDResolution*/ 13107200.0,
                            /*const double yDResolution*/ 13107200.0,
                            *(reqPtr.get()));

                        std::condition_variable cv;
                        std::mutex mtx;
                        bool confirmed { false };

                        // Wyslanie rzadania do sterownika w celu przemieszczenia
                        auto& tInst = TlinsAstroBase::tlinsCommunicationThread::getInstance();
                        auto ptr = std::unique_ptr<TlinsAstroBase::tlinsCommunicationThreadRequest>(new tlinsMoveRequest { reqPtr, cv, mtx, confirmed });
                        tInst.push(ptr);

                        // Oczekiwanie na potwierdzenie
                        std::unique_lock<std::mutex> lock(mtx);
                        cv.wait(lock, [&confirmed] { return confirmed; });

                        seq++;
                    } while (seq < 2);

                    // Wyslanie pomiaru
                    setMeasurment(parent, item, row);

                    parent->debugThreadBusy.store(false);
                };

                debugThread.reset(new std::thread { debugThread_, this });
            } else {
                setMeasurment(this, item, row);
            }
            break;
        }
    } catch (tlinsInterfaceException& exc) {
        std::string m { "Error set reference object. " };
        m += exc.getErrorMessage().c_str();

        emit getMainWindowInstance()->logEvent(QString::fromStdString(m));

        QMessageBox msgBox;
        msgBox.setText(QString::fromStdString(m));
        msgBox.exec();
    }
}

// ??????????????????????????????????????????????????????
// ??????????????????????????????????????????????????????
// ??????????????????????????????????????????????????????

void tlinsUICalibrationWidget::on_btCloseCalibration_clicked()
{
    if (debugThreadBusy) {
        emit getMainWindowInstance()->popupStatusSlot("[DEBUG] Debug thread bussy - plase wait !!!!");
        return;
    }

    closeCalibration();
}

//
// ----------------------------------------------------
//

void tlinsUICalibrationWidget::on_pbGenerateMatrix_clicked()
{
    double alfa { ui->alfa->getValue() / 360.0 * tlinsMath::PI_2 };
    double beta { ui->beta->getValue() / 360.0 * tlinsMath::PI_2 };
    double gamma { ui->gamma->getValue() / 360.0 * tlinsMath::PI_2 };

    Eigen::Matrix3d outx;
    Eigen::Matrix3d outy;
    Eigen::Matrix3d outz;
    attitude::tlinAttitudeUtilsClass::buildXRotaionMatrix(alfa, outx);
    attitude::tlinAttitudeUtilsClass::buildYRotaionMatrix(beta, outy);
    attitude::tlinAttitudeUtilsClass::buildZRotaionMatrix(gamma, outz);

    Eigen::Matrix3d out = outx * outy * outz;

    ui->a11->setValue(out(0, 0));
    ui->a12->setValue(out(0, 1));
    ui->a13->setValue(out(0, 2));

    ui->a21->setValue(out(1, 0));
    ui->a22->setValue(out(1, 1));
    ui->a23->setValue(out(1, 2));

    ui->a31->setValue(out(2, 0));
    ui->a32->setValue(out(2, 1));
    ui->a33->setValue(out(2, 2));
}

//
// ----------------------------------------------------
// Start/restart kalibracji
// ----------------------------------------------------
//
class tlinsCalibrationStart : public TlinsAstroBase::tlinsCommunicationThreadRequest {
private:
    std::shared_ptr<TlinsAstroBase::tlinsConnectionContext> connection;
    tlinsUICalibrationWidget* parent;

    bool reverseGroupSelected;
    bool xReverseSelected;
    bool yReverseSelected;

private:
    std::unique_ptr<tlinsMoveServerInterface::MoveRequestDevice> request;

public:
    virtual void operator()() noexcept
    {
        try {
            //
            // Start kalibracji
            //
            tlinsAstroEngineInterface::ReverseDevice xR { tlinsAstroEngineInterface::ReverseDevice::DEVICE_SETTINGS };
            tlinsAstroEngineInterface::ReverseDevice yR { tlinsAstroEngineInterface::ReverseDevice::DEVICE_SETTINGS };

            if (reverseGroupSelected) {
                if (xReverseSelected) {
                    xR = tlinsAstroEngineInterface::ReverseDevice::DEVICE_REVERSE;
                } else {
                    xR = tlinsAstroEngineInterface::ReverseDevice::DEVICE_NO_REVERSE;
                }

                if (yReverseSelected) {
                    yR = tlinsAstroEngineInterface::ReverseDevice::DEVICE_REVERSE;
                } else {
                    yR = tlinsAstroEngineInterface::ReverseDevice::DEVICE_NO_REVERSE;
                }
            }

            connection->getAstro()->resetCalibration(xR, yR);
            parent->calibrationStatusEmit(std::string { "Calibration restarted" }, tlinsUICalibrationWidget::uiChanges::START_CALIBRATION);

            //
            // Odczy stanu kontrolera
            //
            auto& statusInfo = TlinsAstroBase::tlinsServerStatusInfo::getInstance();
            statusInfo.update();
        } catch (tlinsInterfaceException& exc) {
            std::string m { "Error start/reset calibration. Error: " };
            m += exc.getErrorMessage().c_str();
            emit getMainWindowInstance()->logEvent(QString::fromStdString(m));
            parent->calibrationStatusEmit(m, tlinsUICalibrationWidget::uiChanges::NO_CHANGES);
        }
    }

    virtual bool isAsynchronuus()
    {
        return false;
    }

    virtual std::string name()
    {
        return "tlinsCalibrationStart";
    }

    tlinsCalibrationStart(const tlinsCalibrationStart&)
    {
    }

    tlinsCalibrationStart() = default;

    tlinsCalibrationStart(tlinsUICalibrationWidget* parent_, const bool& reverseGroupSelected_, const bool& xReverseSelected_, const bool& yReverseSelected_)
        : parent { parent_ }
        , reverseGroupSelected { reverseGroupSelected_ }
        , xReverseSelected { xReverseSelected_ }
        , yReverseSelected { yReverseSelected_ }
    {
        // Pobranie polaczenia
        if (!TlinsAstroBase::tlinsConnectionsManager::getInstance().hasConnection(std::string { TLINS_CONNECTION_DEFAULT }))
            __THROW__(tlinsInterfaceException(std::string("No active connection "), -1));

        // Polaczenie
        connection = TlinsAstroBase::tlinsConnectionsManager::getInstance().getConnection(TLINS_CONNECTION_DEFAULT);
    }

    virtual ~tlinsCalibrationStart()
    {
        connection.reset();
    }
};

//
// Potwierdzenie kalibracji
//
class tlinsCalibrationConfirmed : public TlinsAstroBase::tlinsCommunicationThreadRequest {
private:
    std::shared_ptr<TlinsAstroBase::tlinsConnectionContext> connection;
    tlinsUICalibrationWidget* parent;

private:
    std::unique_ptr<tlinsMoveServerInterface::MoveRequestDevice> request;

public:
    virtual void operator()() noexcept
    {
        try {
            connection->getAstro()->confirmDeferedMeserment();
            parent->calibrationStatusEmit(std::string { "Calibration confirmed" }, tlinsUICalibrationWidget::uiChanges::CONFIRM_REFERENCE);
        } catch (tlinsInterfaceException& exc) {
            std::string m { "Error confirm deferred calibration. Error: " };
            m += exc.getErrorMessage().c_str();
            emit getMainWindowInstance()->logEvent(QString::fromStdString(m));
            parent->calibrationStatusEmit(m, tlinsUICalibrationWidget::uiChanges::NO_CHANGES);
        }
    }

    virtual bool isAsynchronuus()
    {
        return false;
    }

    virtual std::string name()
    {
        return "tlinsCalibrationConfirmed";
    }

    tlinsCalibrationConfirmed(const tlinsCalibrationConfirmed&)
    {
    }

    tlinsCalibrationConfirmed()
    {
    }

    tlinsCalibrationConfirmed(tlinsUICalibrationWidget* parent_)
        : parent { parent_ }
    {
        // Pobranie polaczenia
        if (!TlinsAstroBase::tlinsConnectionsManager::getInstance().hasConnection(std::string { TLINS_CONNECTION_DEFAULT })) {
            auto msg = std::string("No active connection ");
            emit getMainWindowInstance()->logEvent(QString::fromStdString(msg));
            __THROW__(tlinsInterfaceException(msg, -1));
        }

        // Polaczenie
        connection = TlinsAstroBase::tlinsConnectionsManager::getInstance().getConnection(TLINS_CONNECTION_DEFAULT);
    }

    virtual ~tlinsCalibrationConfirmed()
    {
        connection.reset();
    }
};

void tlinsUICalibrationWidget::confirmDeferred_clicked()
{
    try {
        if (!ui->checkAsDeferred->isChecked()) {
            std::string m { "Reference object is not deferred. " };
            calibrationStatusEmit(m, tlinsUICalibrationWidget::uiChanges::NO_CHANGES);
            return;
        }

        auto ptr = new tlinsCalibrationConfirmed { this };
        std::unique_ptr<TlinsAstroBase::tlinsCommunicationThreadRequest> req(ptr);
        TlinsAstroBase::tlinsCommunicationThread::getInstance().push(req);
    } catch (tlinsInterfaceException& exc) {
        std::string m { "Error start/reset calibration. " };
        m += exc.getErrorMessage().c_str();
        emit getMainWindowInstance()->logEvent(QString::fromStdString(m));
        calibrationStatusEmit(m, tlinsUICalibrationWidget::uiChanges::NO_CHANGES);
    }
}

void tlinsUICalibrationWidget::asDeferredClicked()
{
    if (ui->checkAsDeferred->isChecked())
        ui->confirmDeferred->setEnabled(true);
    else
        ui->confirmDeferred->setEnabled(false);
}

void tlinsUICalibrationWidget::calibrationStatusEmit(std::string m, uiChanges uiCh)
{
    emit this->calibrationStatus(m, uiCh);
}

void tlinsUICalibrationWidget::updateRowStatusEmit(const TlinsAstroBase::tlinsAstroCalibrationItem::calibrationStatus status, int row)
{
    emit this->updateRowStatus(status, row);
}

void tlinsUICalibrationWidget::on_btStartCalibration_clicked()
{
    if (debugThreadBusy) {
        emit getMainWindowInstance()->popupStatusSlot("[DEBUG] Debug thread bussy - plase wait !!!!");
        return;
    }

    // Startowy koat obrotu
    auto& tInfo = tlinsTimeInfo::getInstance();
    tInfo.update();

    try {

        bool reverseGroupSelected = ui->axiesDirectionGroup->isChecked();
        bool xReverseSelected = ui->chbXReverse->isChecked();
        bool yReverseSelected = ui->chbYReverse->isChecked();

        // Ustawienie czasu
        auto ptr = new tlinsCalibrationStart { this, reverseGroupSelected, xReverseSelected, yReverseSelected };
        std::unique_ptr<TlinsAstroBase::tlinsCommunicationThreadRequest> req(ptr);
        oCount = 0;
        TlinsAstroBase::tlinsCommunicationThread::getInstance().push(req);
    } catch (tlinsInterfaceException& exc) {
        std::string m { "Error start/reset calibration. " };
        m += exc.getErrorMessage().c_str();
        emit getMainWindowInstance()->logEvent(QString::fromStdString(m));
        calibrationStatusEmit(m, tlinsUICalibrationWidget::uiChanges::NO_CHANGES);
    }
}

void tlinsUICalibrationWidget::on_btSave_clicked()
{
    // Odczyt recordow z modelu danych
    try {
        // Database
        TlinsAstroBase::tlinsUIDatabase db;
        TlinsAstroBase::tlinsUIDatabaseDefinition dbDef(db);
        dbDef.replaceAstroCalibrationObjects(dataModel.getCalibrationData());
    } catch (TlinsAstroBase::tlinsUIException&) {
        auto msg = "Error update database";
        calibrationStatusEmit(msg, tlinsUICalibrationWidget::uiChanges::NO_CHANGES);
        emit getMainWindowInstance()->logEvent(QString::fromStdString(msg));
        return;
    }
    QMessageBox msg;
    msg.setText(QString("Records saved"));
    msg.exec();
}

void tlinsUICalibrationWidget::on_btMoveUp_clicked()
{
    qDebug() << "Move up";

    QModelIndexList select = ui->referenceObjects->selectionModel()->selectedRows();
    if (select.count() == 0) {
        QMessageBox mbox;
        mbox.setText(QString("At least one row should be selected."));
        mbox.exec();
        return;
    }

    ui->referenceObjects->selectionModel()->clearSelection();
    for (int i = 0; i < select.count(); i++) {
        QModelIndex idx = select.at(i);
        int row = idx.row();
        dataModel.moveUp(row);

        row--;
        ui->referenceObjects->selectRow(row);
    }
}

void tlinsUICalibrationWidget::on_btMoveDown_clicked()
{
    qDebug() << "Move down";

    QModelIndexList select = ui->referenceObjects->selectionModel()->selectedRows();
    if (select.count() == 0) {
        QMessageBox mbox;
        mbox.setText(QString("At least one row should be selected."));
        mbox.exec();
        return;
    }

    ui->referenceObjects->selectionModel()->clearSelection();
    for (int i = 0; i < select.count(); i++) {
        QModelIndex idx = select.at(i);
        int row = idx.row();
        dataModel.moveDown(row);

        row++;
        ui->referenceObjects->selectRow(row);
    }
}

void tlinsUICalibrationWidget::dataSelected()
{
    qDebug() << "Data selected";

    std::vector<int> records;
    TlinsAstroBase::tlinsAstroCatalogCollection result;
    searchWindow.getSelectedRows(records, result);

    for (int i = 0; i < result.count(); i++) {
        auto item = result.getItem(i);
        TlinsAstroBase::tlinsAstroCalibrationItem cItem(item);
        dataModel.insertItem(cItem);
    }
    ui->referenceObjects->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
}

void tlinsUICalibrationWidget::on_btSearchObject_clicked()
{
    searchWindow.show();
}

void tlinsUICalibrationWidget::on_btRemoveObject_clicked()
{
    QModelIndexList select = ui->referenceObjects->selectionModel()->selectedRows();
    if (select.count() == 0) {
        QMessageBox mbox;
        mbox.setText(QString("At least one row should be selected."));
        mbox.exec();
        return;
    }

    for (int i = 0; i < select.count(); i++) {
        QModelIndex idx = select.at(i);
        int row = idx.row();
        dataModel.deleteItem(row);
    }
    ui->referenceObjects->selectionModel()->clearSelection();
}

void tlinsUICalibrationWidget::on_btLoad_clicked()
{
    // Odczyt recordow z modelu danych
    try {
        // Database
        TlinsAstroBase::tlinsUIDatabase db;
        TlinsAstroBase::tlinsUIDatabaseDefinition dbDef(db);

        std::vector<TlinsAstroBase::tlinsAstroCalibrationItem> cobjects;
        dbDef.selectAstroCalibrationObjects(cobjects);
        dataModel.clear();
        dataModel.setItems(cobjects);
    } catch (TlinsAstroBase::tlinsUIException&) {
        QMessageBox msg;
        msg.setText(QString("Error update database"));
        emit getMainWindowInstance()->logEvent(msg.text());
        msg.exec();
        return;
    }

    QMessageBox msg;
    msg.setText(QString("Data loaded"));
    msg.exec();
}

void tlinsUICalibrationWidget::calibrationStatusSlot(std::string str, uiChanges uiCh)
{
    auto& inst = TlinsAstroBase::tlinsConfiguration::getInstance();
    auto objMinMes = inst.getInt(TlinsAstroBase::tlinsConfiguration::CALIBRARION_GROUP, TlinsAstroBase::tlinsConfiguration::CALIBRARION_MIN_NUMBER_MEASURMENTS);

    switch (uiCh) {
    case uiChanges::NO_CHANGES:
        break;

    case uiChanges::START_CALIBRATION:
        //
        // Start calibracji
        //
        {
            // Ustawinie przyciskow
            // - Odroczony wlaczony zaleznie od znacznika
            if (ui->checkAsDeferred->isChecked())
                setButtonAttrs(ui->confirmDeferred, true, false, Qt::GlobalColor::red);
            else
                setButtonAttrs(ui->confirmDeferred, false, true, Qt::GlobalColor::white);

            // - zamkniecie kalibracji jest wylaczony
            setButtonAttrs(ui->btCloseCalibration, false, true, Qt::GlobalColor::white);

            // - ustawienie obiektu referencujmego jest aktywne
            setButtonAttrs(ui->btSetReference, true, false, Qt::GlobalColor::red);

            ui->groupBoxTrackingMode->setEnabled(false);
            setTrackingModeAttrs(ui->label, ui->tGuider, ui->tManual, ui->tSpeed, ui->tStandard, false, true, Qt::GlobalColor::white);

            // Wyczyszczenie statusów obiektów na liscie
            auto& data = dataModel.getCalibrationData();
            for (unsigned int row = 0; row < data.size(); row++) {
                dataModel.updateItemStatus(TlinsAstroBase::tlinsAstroCalibrationItem::calibrationStatus::NONE, static_cast<int>(row));
                ui->referenceObjects->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
            }

            // Liczba pomiarow dla pojedynczego obiektu
            ui->singleObjectMeasurments->setValue(objMinMes);

            // Odswierzenie statusu kontrolera
            //            auto& statusInfo = TlinsAstroBase::tlinsServerStatusInfo::getInstance();
            //            statusInfo.update();
        }
        break;

    case uiChanges::CONFIRM_REFERENCE:
    case uiChanges::SET_REFERENCE:
        //
        // Potwierdzenie obiektu referencyjnego
        //
        {
            // Sprawdzenie pozostalej liczby pomiarow
            auto val = ui->singleObjectMeasurments->value();
            val--;
            if (val <= 0) {
                // Wszystkie pomiary dla biezacego obiektu zostaly zrobione
                dataModel.updateItemStatus(TlinsAstroBase::tlinsAstroCalibrationItem::calibrationStatus::COMPLETED,
                    static_cast<int>(currentRefObjectRow));

                ui->singleObjectMeasurments->setValue(objMinMes);

                // Gdy wszystkie pomiary wykonane odblokowujemy przycisk zakonczenia kalibracji
                if ((currentRefObjectRow + 1) >= dataModel.getCalibrationData().size()) {
                    setButtonAttrs(ui->btCloseCalibration, true, false, Qt::GlobalColor::red);
                    setButtonAttrs(ui->btSetReference, false, true, Qt::GlobalColor::white);
                    setButtonAttrs(ui->confirmDeferred, false, true, Qt::GlobalColor::white);

                    ui->groupBoxTrackingMode->setEnabled(true);
                    setTrackingModeAttrs(ui->label, ui->tGuider, ui->tManual, ui->tSpeed, ui->tStandard, true, false, Qt::GlobalColor::red);
                }
            } else {
                // Kolejny pomiar
                dataModel.updateItemStatus(TlinsAstroBase::tlinsAstroCalibrationItem::calibrationStatus::SET_AS_BASE_OBJECT,
                    static_cast<int>(currentRefObjectRow));

                ui->singleObjectMeasurments->setValue(val);

                // Przycisk zamkniecia pomiaru nadal wylaczony
                setButtonAttrs(ui->btCloseCalibration, false, true, Qt::GlobalColor::white);
            }

            // Odswierzenie statusu kontrolera
            //            auto& statusInfo = TlinsAstroBase::tlinsServerStatusInfo::getInstance();
            //            statusInfo.update();
        }
        break;

    case uiChanges::CLOSE_CALIBRATION: {
        // Status po kalibracji jest odswiezany w wywolaniu do serwera
        // Wszystkie przyciski poza startem kalibracji sa nieaktywne
        setButtonAttrs(ui->btSetReference, false, true, Qt::GlobalColor::white);

        // Potwierdzenie odroczonego
        setButtonAttrs(ui->confirmDeferred, false, false, Qt::GlobalColor::white);

        // Zablokowanie przyciksu potwierdzenia
        setButtonAttrs(ui->btCloseCalibration, false, true, Qt::GlobalColor::white);

        setTrackingModeAttrs(ui->label, ui->tGuider, ui->tManual, ui->tSpeed, ui->tStandard, false, true, Qt::GlobalColor::white);
        ui->groupBoxTrackingMode->setEnabled(false);
    } break;
    }

    QMessageBox msgBox;
    //    msgBox.addButton(QMessageBox::Ok);
    //    QFont f = msgBox.button(QMessageBox::Ok)->font();
    //    f.setPointSize(15);
    //    msgBox.button(QMessageBox::Ok)->setFont(f);

    msgBox.setText(QString::fromStdString(str));
    msgBox.exec();
}

void tlinsUICalibrationWidget::updateRowStatusSlot(const TlinsAstroBase::tlinsAstroCalibrationItem::calibrationStatus status, int row)
{
    dataModel.updateItemStatus(status, row);
    ui->referenceObjects->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
}

void tlinsUICalibrationWidget::errorsStateChanged(bool v)
{
    if (!v) {
        ui->errors->hide();
    } else {
        auto& inst = TlinsAstroBase::tlinsConfiguration::getInstance();
        if (inst.hasKey(TlinsAstroBase::tlinsConfiguration::OBSERVATION_ERRORS_GROUP,
                TlinsAstroBase::tlinsConfiguration::OBSERVATION_ERRORS_LONGITUDE)) {
            ui->errors->setLongitudeError(inst.getDouble(TlinsAstroBase::tlinsConfiguration::OBSERVATION_ERRORS_GROUP,
                TlinsAstroBase::tlinsConfiguration::OBSERVATION_ERRORS_LONGITUDE));
            ui->errors->setLatitudeError(inst.getDouble(TlinsAstroBase::tlinsConfiguration::OBSERVATION_ERRORS_GROUP,
                TlinsAstroBase::tlinsConfiguration::OBSERVATION_ERRORS_LATITUDE));
            ui->errors->setWeight(inst.getDouble(TlinsAstroBase::tlinsConfiguration::OBSERVATION_ERRORS_GROUP,
                TlinsAstroBase::tlinsConfiguration::OBSERVATION_ERRORS_WEIGHT));
        } else {
            ui->errors->setLongitudeError(0.0);
            ui->errors->setLatitudeError(0.0);
            ui->errors->setWeight(0.0);
        }
        ui->errors->show();
    }
}

tlinsUICalibrationWidget::~tlinsUICalibrationWidget()
{
    delete ui;

    if (debugThread && debugThread->joinable())
        debugThread->join();
}
