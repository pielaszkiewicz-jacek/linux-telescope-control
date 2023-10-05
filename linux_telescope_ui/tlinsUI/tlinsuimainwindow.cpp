#include "tlinsuimainwindow.h"
#include "tlinsconfiguration.h"
#include "tlinsconnection.h"
#include "tlinseditdatabaseobject.h"
#include "tlinsserverstatusinfo.h"
#include "tlinsstatusicons.h"
#include "tlinswastrodatabaseobject.h"
#include "tlinswastrodatabasesearch3.h"
#include "tlinswcoordinatedeclination.h"
#include "tlinswcoordinatedegris.h"
#include "tlinswcoordinatehourangle.h"
#include "tlinswdatabasesearchmain.h"
#include "tlinswtrackingcontrol.h"
#include "ui_tlinsuimainwindow.h"
#include <QDebug>
#include <QLayout>
#include <QVBoxLayout>
#include <stdio.h>
#include <time.h>
#include <tlinsBacktrace.hpp>
#include <tlinsLogger.hpp>
#include <tlinsinfowidget.h>

#include <tlinstoolsbasewidget.h>

#include <tlinstoolbarbutton.h>

void tlinsUIMainWindow::popupStatusSlot(const std::string& str)
{
    QMessageBox msgBox;
    msgBox.setText(QString::fromStdString(str));
    msgBox.exec();
}

void tlinsUIMainWindow::devInStepsSlot(bool)
{
}

extern tlinsUIMainWindow* getMainWindowInstance();

class tlinsDevelSetPosition : public TlinsAstroBase::tlinsCommunicationThreadRequest {
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
        }
    }

    virtual bool isAsynchronuus()
    {
        return false;
    }

    virtual std::string name()
    {
        return "tlinsDevelSetPosition";
    }

    tlinsDevelSetPosition(const long x_, const long y_)
        : x { x_ }
        , y { y_ }
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

    virtual ~tlinsDevelSetPosition()
    {
    }
};

void tlinsUIMainWindow::devSetPositionSlot()
{
}

void tlinsUIMainWindow::updatePositionSlot(const long x, const long y, const double ra, const double dec)
{
    ui->statusWidget->setPos(x, y);
    ui->statusWidget->setPos(ra, dec);
}

void tlinsUIMainWindow::logInstallEventSlot(const QString line)
{
    auto t = time(nullptr);
    struct tm* tt = gmtime(&t);

    char text[1024];
    sprintf(text, "[%4d.%02d.%02d %02d:%02d:%02d] ", 1900 + tt->tm_year, tt->tm_mon, tt->tm_mday, tt->tm_hour, tt->tm_min, tt->tm_sec);
    pilotStatusWidget.setInstallText(text + line);
}

void tlinsUIMainWindow::logEventSlot(const QString line)
{
    auto t = time(nullptr);
    struct tm* tt = gmtime(&t);

    char text[1024];
    sprintf(text, "[%4d.%02d.%02d %02d:%02d:%02d] ", 1900 + tt->tm_year, tt->tm_mon, tt->tm_mday, tt->tm_hour, tt->tm_min, tt->tm_sec);

    pilotStatusWidget.setText(text + line);
}

void tlinsUIMainWindow::actionConnect()
{
    actionConnectDef();
}

void tlinsUIMainWindow::actionConnectDef()
{
    //
    // Odczyt konfiguracji
    //
    auto& cfgInstance = TlinsAstroBase::tlinsConfiguration::getInstance();

    std::string urlDev = "localhost:20001";
    std::string urlDevAsync = "localhost:20003";
    std::string urlAstro = "localhost:20000";

    if (cfgInstance.hasKey(TlinsAstroBase::tlinsConfiguration::CONNECTION_PARAMETER_GROUP,
            TlinsAstroBase::tlinsConfiguration::CONNECTION_PARAMETER_URL_DEVICE_ENGINE)) {
        urlDev = cfgInstance.getString(TlinsAstroBase::tlinsConfiguration::CONNECTION_PARAMETER_GROUP,
            TlinsAstroBase::tlinsConfiguration::CONNECTION_PARAMETER_URL_DEVICE_ENGINE);
    }

    if (cfgInstance.hasKey(TlinsAstroBase::tlinsConfiguration::CONNECTION_PARAMETER_GROUP,
            TlinsAstroBase::tlinsConfiguration::CONNECTION_PARAMETER_URL_DEVICE_ENGINE_ASYNCH)) {
        urlDevAsync = cfgInstance.getString(TlinsAstroBase::tlinsConfiguration::CONNECTION_PARAMETER_GROUP,
            TlinsAstroBase::tlinsConfiguration::CONNECTION_PARAMETER_URL_DEVICE_ENGINE_ASYNCH);
    }

    if (cfgInstance.hasKey(TlinsAstroBase::tlinsConfiguration::CONNECTION_PARAMETER_GROUP,
            TlinsAstroBase::tlinsConfiguration::CONNECTION_PARAMETER_URL_ASTRO_ENGINE)) {
        urlAstro = cfgInstance.getString(TlinsAstroBase::tlinsConfiguration::CONNECTION_PARAMETER_GROUP,
            TlinsAstroBase::tlinsConfiguration::CONNECTION_PARAMETER_URL_ASTRO_ENGINE);
    }

    auto& mgr = TlinsAstroBase::tlinsConnectionsManager::getInstance();

    try {
        mgr.setConnection(std::string { TLINS_CONNECTION_DEFAULT },
            urlDev.c_str(),
            urlDevAsync.c_str(),
            urlAstro.c_str());
    } catch (tlinsInterfaceException& exc) {
        QMessageBox msgBox;

        auto& bt = tlinsBacktrace::instance();
        msgBox.setText(QString(exc.getErrorMessage().c_str()) + ". Error (" + QString::number(exc.getErrorID()) + ")" + "\n" + bt.getStackInfo().c_str());
        emit this->logEvent(QString(exc.getErrorMessage().c_str()) + ". Error (" + QString::number(exc.getErrorID()) + ")" + "\n" + bt.getStackInfo().c_str());
        msgBox.exec();
        return;
    } catch (...) {
        QMessageBox msgBox;
        msgBox.setText("Error connect");
        emit this->logEvent("Error connect");

        msgBox.exec();
        return;
    }

    //
    // Polacxzenie z monitorem systemu w celu obslugi klawiatury i jostika
    //
    QString bValue = QString::fromStdString(cfgInstance.getString(TlinsAstroBase::tlinsConfiguration::CONNECTION_PARAMETER_GROUP,
        TlinsAstroBase::tlinsConfiguration::CONNECTION_PARAMETER_CONNECT_SYSTEM_EVENT_MONITOR));
    if (bValue.toLower() == "true") {
        // Laczenie automatyczne
        pilotManager.reset(new tlinsAstroPilot::tlinsPilot { TLINS_CONNECTION_DEFAULT });
    }

    ui->statusWidget->setConnectionStatus(true);

    //
    // Pobranie statusu kontrolera osi
    //
    auto& statusInfo = TlinsAstroBase::tlinsServerStatusInfo::getInstance();
    statusInfo.update();

    // Status kalibracji
    auto& cStatus = statusInfo.getCalibrarionState();
    switch (cStatus.get_engineState()) {
    case tlinsAstroEngineInterface::tlinsEngineStateValue::STATE_CALIBRATION:
    case tlinsAstroEngineInterface::tlinsEngineStateValue::STATE_CALIBRATION_VELOCITY:
        ui->statusWidget->setCalibrationState(tlinsStatusIcons::CalibrationStatus::UNDER_CALIBRATION);
        break;

    case tlinsAstroEngineInterface::tlinsEngineStateValue::STATE_REGULAR:
        ui->statusWidget->setCalibrationState(tlinsStatusIcons::CalibrationStatus::REGULAR);
        break;
    }

    QMessageBox msgBox;
    msgBox.setText("Channels created.");
    msgBox.exec();

    emit this->logEvent("Connected to the device");

    // Odblokowanie akcji rozlaczajacej polaczenie
    //    ui -> actionDisconnect->setEnabled(true);
    //    ui -> actionConnect->setEnabled(false);

    connectButton->setEnabled(false);
    disconnectButton->setEnabled(true);
}

void tlinsUIMainWindow::actionDisconnect()
{
    actionDisconnectDef();
}

void tlinsUIMainWindow::actionDisconnectDef()
{
    std::string name { TLINS_CONNECTION_DEFAULT };

    TlinsAstroBase::tlinsConnectionsManager::getInstance().removeConnection(name);
    ui->statusWidget->setConnectionStatus(false);
    ui->statusWidget->setCalibrationState(tlinsStatusIcons::CalibrationStatus::UNDEFINED);

    //
    // Polacxzenie z monitorem systemu w celu obslugi klawiatury i jostika
    //
    auto& cfgInstance = TlinsAstroBase::tlinsConfiguration::getInstance();
    QString bValue = QString::fromStdString(cfgInstance.getString(TlinsAstroBase::tlinsConfiguration::CONNECTION_PARAMETER_GROUP,
        TlinsAstroBase::tlinsConfiguration::CONNECTION_PARAMETER_CONNECT_SYSTEM_EVENT_MONITOR));
    if (bValue.toLower() == "true") {
        // Laczenie automatyczne
        pilotManager.reset();
    }

    emit this->logEvent("Device disconnected");

    QMessageBox msgBox;
    msgBox.setText("Channels disconnected.");
    msgBox.exec();

    connectButton->setEnabled(true);
    disconnectButton->setEnabled(false);
}

void tlinsUIMainWindow::resizeEvent(QResizeEvent*)
{
    QSize s;

    // Rozmiary ikon
    //	s.setHeight( static_cast<int>( ui -> buttonExit -> size().height() * 0.60 ) );
    //	s.setWidth ( static_cast<int>( ui -> buttonExit -> size().width() * 0.60 ) );
    //	ui -> buttonExit -> setIconSize(s);

    //	s.setHeight( static_cast<int>( ui -> buttonConnect -> size().height() * 0.60 ) );
    //	s.setWidth ( static_cast<int>( ui -> buttonConnect -> size().width() * 0.60 ) );
    //	ui -> buttonConnect -> setIconSize(s);
}

tlinsUIMainWindow::tlinsUIMainWindow(QWidget* parent)
    : QMainWindow(parent),
    editObject(this),
    ui(new Ui::tlinsUIMainWindow),
    pilotWidget { this },
    calibrationWidget { this },
    targetWidget { this },
    engineStateWidget { this },
    iersWidget { this },
    databaseWidget { this },
    environmentWidget { this },
    settingsWidget { this },
    observationPlaceWidget { this },
    pilotShortcutsWidget { this },
    dateTimeWidget { this },
    environmentSetWidget { this },
    colliostionWidget { this },
    currentToolWidget { nullptr }
{
    ui->setupUi(this);

    //
    // Sygnaly
    //
    connect(ui->actionObservationPlace, SIGNAL(triggered(bool)), this, SLOT(openPlaces()));

    connect(this, SIGNAL(logEvent(const QString)), this, SLOT(logEventSlot(const QString)), Qt::QueuedConnection);
    connect(this, SIGNAL(logInstallEvent(const QString)), this, SLOT(logInstallEventSlot(const QString)), Qt::QueuedConnection);

    connect(this, SIGNAL(updatePosition(const long, const long, const double, const double)), this, SLOT(updatePositionSlot(const long, const long, const double, const double)) /*, Qt::QueuedConnection*/);

    // Obsluga zakladki development
    connect(this, SIGNAL(popupStatus(const std::string)), this, SLOT(popupStatusSlot(const std::string)), Qt::BlockingQueuedConnection /*QueuedConnection*/);

    emit this->logEvent("");
    emit this->logEvent("TLINS UI");
    emit this->logEvent("Jacek Pielaszkiewicz");
    emit this->logEvent("--------------------------------------------------------------");
    emit this->logEvent("");
    //
    // Belka statusu
    //
    ui->statusWidget->setConnectionStatus(false);
    ui->statusWidget->setCalibrationState(tlinsStatusIcons::CalibrationStatus::UNDEFINED);

    //
    // Budowanie glownego toolbara
    //
    // 1. Pilot
    pilotWidgetButton = new tlinsToolBarButton(
        QString { ":/icons/remote-control.svg" },
        QString { "Pilot" },
        [this]() {
            ui->stackedWidget->setCurrentWidget(pilotWidgetBase);
        },
        this, ui->stackedWidget);
    ui->toolBar->addWidget(pilotWidgetButton);

    // 2. Kalibracja
    calibrationWidgetButton = new tlinsToolBarButton(
        QString { ":/icons/calibration-mark.svg" },
        QString { "Calibration" },
        [this]() {
            ui->stackedWidget->setCurrentWidget(calibrationWidgetBase);
        },
        this, ui->stackedWidget);
    ui->toolBar->addWidget(calibrationWidgetButton);

    // 4. Stan
    engineStateWidgetButton = new tlinsToolBarButton(
        QString { ":/icons/state.svg" },
        QString { "State and guider" },
        [this]() {
            ui->stackedWidget->setCurrentWidget(engineStateWidgetBase);
        },
        this, ui->stackedWidget);
    ui->toolBar->addWidget(engineStateWidgetButton);

    // 3. Obiekt docelowy
    targetWidgetButton = new tlinsToolBarButton(
        QString { ":/icons/target.svg" },
        QString { "Target" },
        [this]() {
            ui->stackedWidget->setCurrentWidget(targetWidgetBase);
        },
        this, ui->stackedWidget);
    ui->toolBar->addWidget(targetWidgetButton);

    // 12.Tracking
    trackingControlButton = new tlinsToolBarButton(
        QString { ":/icons/delivery.svg" },
        QString { "Tracking" },
        [this]() {
            ui->stackedWidget->setCurrentWidget(trackingControlBase);
        },
        this, ui->stackedWidget);
    ui->toolBar->addWidget(trackingControlButton);

    // 4. IERS
    iersWidgetButton = new tlinsToolBarButton(
        QString { ":/icons/iers.svg" },
        QString { "IERS data" },
        [this]() {
            ui->stackedWidget->setCurrentWidget(iersWidgetBase);
        },
        this, ui->stackedWidget);
    ui->toolBar->addWidget(iersWidgetButton);

    // 5. Database
    databaseWidgetButton = new tlinsToolBarButton(
        QString { ":/icons/database.svg" },
        QString { "Database" },
        [this]() {
            ui->stackedWidget->setCurrentWidget(databaseWidgetBase);
        },
        this, ui->stackedWidget);
    ui->toolBar->addWidget(databaseWidgetButton);

    // 6. Applay environment
    environmentWidgetButton = new tlinsToolBarButton(
        QString { ":/icons/base_configuration.svg" },
        QString { "Base configuration" },
        [this]() {
            ui->stackedWidget->setCurrentWidget(environmentWidgetBase);
        },
        this, ui->stackedWidget);
    ui->toolBar->addWidget(environmentWidgetButton);

    // 7. Environment
    environmentSetWidgetButton = new tlinsToolBarButton(
        QString { ":/icons/environment.svg" },
        QString { "Environment" },
        [this]() {
            ui->stackedWidget->setCurrentWidget(environmentSetWidgetBase);
        },
        this, ui->stackedWidget);
    ui->toolBar->addWidget(environmentSetWidgetButton);

    // 8. Observation place
    observationPlaceButton = new tlinsToolBarButton(
        QString { ":/icons/observation-pace.svg" },
        QString { "Observation place" },
        [this]() {
            ui->stackedWidget->setCurrentWidget(observationPlaceWidgetBase);
        },
        this, ui->stackedWidget);
    ui->toolBar->addWidget(observationPlaceButton);

    // 9. Date time
    dateTimeWidgetButton = new tlinsToolBarButton(
        QString { ":/icons/calendar.svg" },
        QString { "Date time" },
        [this]() {
            ui->stackedWidget->setCurrentWidget(dateTimeWidgetBase);
        },
        this, ui->stackedWidget);
    ui->toolBar->addWidget(dateTimeWidgetButton);

    currentToolWidget = pilotWidgetButton;

    //
    // Przyciski po prawej stronie
    //
    {
        settingsWidgetButton = new tlinsToolBarButton(
            QString { ":/icons/settings.svg" },
            QString { "Settings" },
            [this]() {
                ui->stackedWidget->setCurrentWidget(settingsWidgetBase);
            },
            this, ui->stackedWidget);
        ui->toolBar_2->addWidget(settingsWidgetButton);
    }

    {
        pilotShortcutsWidgetButton = new tlinsToolBarButton(
            QString { ":/icons/shortcut.svg" },
            QString { "Pilot shortcuts" },
            [this]() {
                ui->stackedWidget->setCurrentWidget(pilotShortcutsWidgetBase);
            },
            this, ui->stackedWidget);
        ui->toolBar_2->addWidget(pilotShortcutsWidgetButton);
    }

    {
        pilotStatusWidgetButton = new tlinsToolBarButton(
            QString { ":/icons/status.svg" },
            QString { "Logs, pilot, update" },
            [this]() {
                ui->stackedWidget->setCurrentWidget(pilotStatusWidgetBase);
            },
            this, ui->stackedWidget);
        ui->toolBar_2->addWidget(pilotStatusWidgetButton);
    }

    {
        colliostionWidgetButton = new tlinsToolBarButton(
            QString { ":/icons/constraint.svg" },
            QString { "Collistions" },
            [this]() {
                ui->stackedWidget->setCurrentWidget(colliostionWidgetBase);
            },
            this, ui->stackedWidget);
        ui->toolBar_2->addWidget(colliostionWidgetButton);
    }


    {
        // Separator dla przcisku wyjscia
        placeholder = new QWidget(this);
        placeholderAction = new QAction(this);
        placeholderSizePolicy.setVerticalPolicy(QSizePolicy::Expanding);
        placeholder->setSizePolicy(placeholderSizePolicy);
        ui->toolBar_2->insertWidget(placeholderAction, placeholder);
    }

    {
        connectButton = new tlinsToolBarButton(
            QString { ":/icons/link-red.svg" },
            QString { "Connect" },
            [&]() {
                this->actionConnectDef();
            },
            this, ui->stackedWidget);
        ui->toolBar_2->addWidget(connectButton);
    }

    {
        disconnectButton = new tlinsToolBarButton(
            QString { ":/icons/disconnected-chains.svg" },
            QString { "Disconnect" },
            [&]() {
                this->actionDisconnectDef();
            },
            this, ui->stackedWidget);
        ui->toolBar_2->addWidget(disconnectButton);
    }

    connectButton->setEnabled(true);
    disconnectButton->setEnabled(false);

    {
        exitButton = new tlinsToolBarButton(
            QString { ":/icons/return.svg" },
            QString { "Exit" },
            [&]() {
                this->close();
            },
            this, ui->stackedWidget);
        ui->toolBar_2->addWidget(exitButton);
    }

    //
    // Dodanie widgetow
    //
    pilotWidgetBase = new tlinsToolsBaseWidget { &pilotWidget,
        "Pilot",
        ":/icons/remote-control.svg",
        ui->stackedWidget };
    ui->stackedWidget->addWidget(pilotWidgetBase);

    calibrationWidgetBase = new tlinsToolsBaseWidget { &calibrationWidget,
        "Calibration",
        ":/icons/calibration-mark.svg",
        ui->stackedWidget };
    ui->stackedWidget->addWidget(calibrationWidgetBase);

    targetWidgetBase = new tlinsToolsBaseWidget { &targetWidget,
        "Target object",
        ":/icons/target.svg",
        ui->stackedWidget };
    ui->stackedWidget->addWidget(targetWidgetBase);

    trackingControlBase = new tlinsToolsBaseWidget { &trackingControl,
        "Tracking",
        ":/icons/delivery.svg",
        ui->stackedWidget };
    ui->stackedWidget->addWidget(trackingControlBase);

    engineStateWidgetBase = new tlinsToolsBaseWidget { &engineStateWidget,
        "Mount calibration and guider/manual correction managment",
        ":/icons/state.svg",
        ui->stackedWidget };
    ui->stackedWidget->addWidget(engineStateWidgetBase);

    iersWidgetBase = new tlinsToolsBaseWidget { &iersWidget,
        "IERS",
        ":/icons/iers.svg",
        ui->stackedWidget };
    ui->stackedWidget->addWidget(iersWidgetBase);

    databaseWidgetBase = new tlinsToolsBaseWidget { &databaseWidget,
        "Database",
        ":/icons/database.svg",
        ui->stackedWidget };
    ui->stackedWidget->addWidget(databaseWidgetBase);

    environmentWidgetBase = new tlinsToolsBaseWidget { &environmentWidget,
        "Applay base configuration",
        ":/icons/base_configuration.svg",
        ui->stackedWidget };
    ui->stackedWidget->addWidget(environmentWidgetBase);

    observationPlaceWidgetBase = new tlinsToolsBaseWidget { &observationPlaceWidget,
        "Observation place",
        ":/icons/observation-pace.svg",
        ui->stackedWidget };
    ui->stackedWidget->addWidget(observationPlaceWidgetBase);

    dateTimeWidgetBase = new tlinsToolsBaseWidget { &dateTimeWidget,
        "Date time",
        ":/icons/calendar.svg",
        ui->stackedWidget };
    ui->stackedWidget->addWidget(dateTimeWidgetBase);

    pilotShortcutsWidgetBase = new tlinsToolsBaseWidget { &pilotShortcutsWidget,
        "Pilot shortcuts",
        ":/icons/shortcut.svg",
        ui->stackedWidget };
    ui->stackedWidget->addWidget(pilotShortcutsWidgetBase);

    settingsWidgetBase = new tlinsToolsBaseWidget { &settingsWidget,
        "Application Settings",
        ":/icons/settings.svg",
        ui->stackedWidget };
    ui->stackedWidget->addWidget(settingsWidgetBase);

    environmentSetWidgetBase = new tlinsToolsBaseWidget { &environmentSetWidget,
        "Environment",
        ":/icons/environment.svg",
        ui->stackedWidget };
    ui->stackedWidget->addWidget(environmentSetWidgetBase);

    pilotStatusWidgetBase = new tlinsToolsBaseWidget { &pilotStatusWidget,
        "Logs, position info, pilot status and update",
        ":/icons/status.svg",
        ui->stackedWidget };
    ui->stackedWidget->addWidget(pilotStatusWidgetBase);

    colliostionWidgetBase = new tlinsToolsBaseWidget { &colliostionWidget,
        "Collistion detection managment",
        ":/icons/status.svg",
        ui->stackedWidget };
    ui->stackedWidget->addWidget(colliostionWidgetBase);

    ui->stackedWidget->setCurrentWidget(pilotWidgetBase);

    currentToolWidget->setChecked(false);
    currentToolWidget->setChecked(true);

    tEnd = false;
    auto threadFun = [this]() {
        while (!(this->tEnd)) {
            if (TlinsAstroBase::tlinsConnectionsManager::getInstance().hasConnection(std::string { TLINS_CONNECTION_DEFAULT })) {
                std::unique_ptr<TlinsAstroBase::tlinsCommunicationThreadRequest> req { new tlinsPositionInfoRequest { this } };
                TlinsAstroBase::tlinsCommunicationThread::getInstance().push(req);
            }

            // Odswiezanie co jedną sekunde
            std::this_thread::sleep_for(std::chrono::milliseconds { 1000 });
        }
    };

    positionThread = std::thread { threadFun };
}

tlinsUIMainWindow::~tlinsUIMainWindow()
{
    tEnd = true;
    if (positionThread.joinable()) {
        positionThread.join();
    }
    delete ui;
}

//
// ----------------------------------------------------------------------
//

void tlinsUIMainWindow::tlinsPositionInfoRequest::operator()() noexcept
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

    // Pobranie pozycji
    try {
        connection->getDevice()->positionInfo(mainDevName, result);
    } catch (...) {
        return;
    }

    // Pobranie pozycji astro
    tlinsAstroEngineInterface::tlinsTarget astroTarget;
    try {
        connection->getAstro()->getTarget(astroTarget);
    } catch (...) {
    }

    auto hh = astroTarget.get_object().get_hourAngle().get_degris();
    auto hm = astroTarget.get_object().get_hourAngle().get_minutes();
    auto hs = astroTarget.get_object().get_hourAngle().get_seconds();
    double h = hh + hm / 60.0 + hs / 3600;

    auto dsign = astroTarget.get_object().get_declination().get_sign();
    auto dd = astroTarget.get_object().get_declination().get_degris();
    auto dm = astroTarget.get_object().get_declination().get_minutes();
    auto ds = astroTarget.get_object().get_declination().get_seconds();
    double d = dd + dm / 60.0 + ds / 3600;
    d *= dsign ? -1.0 : 1.0;

    auto xItem = result.find("X");
    if (xItem == result.end()) {
        return;
    }

    auto yItem = result.find("Y");
    if (yItem == result.end()) {
        return;
    }

    qDebug() << "X = " << xItem->second.get_position() << "; Y = " << yItem->second.get_position() << "; RA = " << h << "; DEC = " << d;

    // Aktualizacja UI
    long X = xItem->second.get_position();
    long Y = yItem->second.get_position();
    double RA = h;
    double DEC = d;
    emit master->updatePosition(X, Y, RA, DEC);
}

bool tlinsUIMainWindow::tlinsPositionInfoRequest::isAsynchronuus()
{
    return false;
}

std::string tlinsUIMainWindow::tlinsPositionInfoRequest::name()
{
    return "tlinsPositionInfoRequest";
}

tlinsUIMainWindow::tlinsPositionInfoRequest::tlinsPositionInfoRequest(tlinsUIMainWindow* _ptr)
    : master { _ptr }
{
    // Pobranie polaczenia
    if (!TlinsAstroBase::tlinsConnectionsManager::getInstance().hasConnection(std::string { TLINS_CONNECTION_DEFAULT }))
        __THROW__(tlinsException(std::string("No active connection: ") + std::string(TLINS_CONNECTION_DEFAULT), -1));

    // Polaczenie
    connection = TlinsAstroBase::tlinsConnectionsManager::getInstance().getConnection(TLINS_CONNECTION_DEFAULT);
}
