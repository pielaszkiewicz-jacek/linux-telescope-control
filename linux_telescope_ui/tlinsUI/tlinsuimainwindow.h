#ifndef TLINSUIMAINWINDOW_H
#define TLINSUIMAINWINDOW_H

#include "tlinsconfiguration.h"
#include "tlinseditdatabaseobject.h"
#include "tlinspilotwindow.h"
#include "tlinsstatusicons.h"
#include "tlinsuiastrodatabasemanagement.h"
#include "tlinswtrackingcontrol.h"
#include <tlinscommunicationthread.h>

#include <tlinsdatetimewidget.h>
#include <tlinsinfowidget.h>
#include <tlinssettingswidget.h>
#include <tlinstoolbarbutton.h>
#include <tlinstoolsbasewidget.h>
#include <tlinsuiastrodatabasemanagementwidget.h>
#include <tlinsuicalibrationwidget.h>
#include <tlinsuipolit4.h>
#include <tlinswapplayastroconfigurationwidget.h>
#include <tlinswenvironmentwidget.h>
#include <tlinswmanageenginestate.h>
#include <tlinswobservationplace.h>
#include <tlinswpilotshortcutsdefinitions.h>
#include <tlinswtarget.h>
#include <tlinswtimedateierssettings.h>
#include <tlinslimitsmanagment.h>
#include <tlinspilot.h>

#include <QMainWindow>

#include <atomic>
#include <memory>
#include <mutex>
#include <thread>

namespace Ui {
class tlinsUIMainWindow;
}

class tlinsUIMainWindow : public QMainWindow {
    Q_OBJECT

private:
    std::mutex positionMtx;
    std::unique_ptr<tlinsAstroPilot::tlinsPilot> pilotManager;

    std::atomic<bool> tEnd;
    std::thread positionThread;

    class tlinsPositionInfoRequest : public TlinsAstroBase::tlinsCommunicationThreadRequest {
    private:
        tlinsUIMainWindow* master;
        std::shared_ptr<TlinsAstroBase::tlinsConnectionContext> connection;

    public:
        virtual void operator()() noexcept;
        virtual bool isAsynchronuus();
        virtual std::string name();
        tlinsPositionInfoRequest(tlinsUIMainWindow* _ptr);
        virtual ~tlinsPositionInfoRequest() = default;
    };

public:
    void setCurrentWidget(tlinsToolBarButton* v)
    {
        setChecked(false);
        currentToolWidget = v;
        //        setChecked(true);
    }

    void setChecked(const bool v)
    {
        if (currentToolWidget != nullptr)
            currentToolWidget->setChecked(v);
    }

private:
    QWidget* placeholder;
    QSizePolicy placeholderSizePolicy;
    QAction* placeholderAction;

    tlinsToolBarButton* currentToolWidget;

    tlinsUiPolit4 pilotWidget;
    tlinsToolsBaseWidget* pilotWidgetBase;
    tlinsToolBarButton* pilotWidgetButton;

    tlinsUICalibrationWidget calibrationWidget;
    tlinsToolsBaseWidget* calibrationWidgetBase;
    tlinsToolBarButton* calibrationWidgetButton;

    tlinsWTarget targetWidget;
    tlinsToolsBaseWidget* targetWidgetBase;
    tlinsToolBarButton* targetWidgetButton;

    tlinsWManageEngineState engineStateWidget;
    tlinsToolsBaseWidget* engineStateWidgetBase;
    tlinsToolBarButton* engineStateWidgetButton;

    tlinsWTimeDateIERSSettings iersWidget;
    tlinsToolsBaseWidget* iersWidgetBase;
    tlinsToolBarButton* iersWidgetButton;

    tlinsUiAstroDatabaseManagementWidget databaseWidget;
    tlinsToolsBaseWidget* databaseWidgetBase;
    tlinsToolBarButton* databaseWidgetButton;

    tlinsWApplayAstroConfigurationWidget environmentWidget;
    tlinsToolsBaseWidget* environmentWidgetBase;
    tlinsToolBarButton* environmentWidgetButton;

    tlinsSettingsWidget settingsWidget;
    tlinsToolsBaseWidget* settingsWidgetBase;
    tlinsToolBarButton* settingsWidgetButton;

    tlinsWObservationPlace observationPlaceWidget;
    tlinsToolsBaseWidget* observationPlaceWidgetBase;
    tlinsToolBarButton* observationPlaceButton;

    tlinsWPilotShortcutsDefinitions pilotShortcutsWidget;
    tlinsToolsBaseWidget* pilotShortcutsWidgetBase;
    tlinsToolBarButton* pilotShortcutsWidgetButton;

    tlinsDateTimeWidget dateTimeWidget;
    tlinsToolsBaseWidget* dateTimeWidgetBase;
    tlinsToolBarButton* dateTimeWidgetButton;

    tlinsWEnvironmentWidget environmentSetWidget;
    tlinsToolsBaseWidget* environmentSetWidgetBase;
    tlinsToolBarButton* environmentSetWidgetButton;

    tlinsWTrackingControl trackingControl;
    tlinsToolsBaseWidget* trackingControlBase;
    tlinsToolBarButton* trackingControlButton;

    tlinsToolBarButton* logsWidgetButton;

    tlinsToolBarButton* connectButton;
    tlinsToolBarButton* disconnectButton;
    tlinsToolBarButton* exitButton;

    tlinsInfoWidget pilotStatusWidget;
    tlinsToolsBaseWidget* pilotStatusWidgetBase;
    tlinsToolBarButton* pilotStatusWidgetButton;

    tlinsLimitsManagmentWidget colliostionWidget;
    tlinsToolsBaseWidget* colliostionWidgetBase;
    tlinsToolBarButton* colliostionWidgetButton;

    void resizeEvent(QResizeEvent* event);

    void actionConnectDef();
    void actionDisconnectDef();

signals:
    void logEvent(const QString line);
    void logInstallEvent(const QString line);
    void updatePosition(const long x, const long y, const double ra, const double dec);
    void popupStatus(const std::string&);

public slots:
    void logEventSlot(const QString line);
    void logInstallEventSlot(const QString line);
    void updatePositionSlot(const long x, const long y, const double ra, const double dec);

    void devSetPositionSlot();
    void devInStepsSlot(bool v);

public slots:
    void popupStatusSlot(const std::string& str);
    void actionConnect();
    void actionDisconnect();

public:
    explicit tlinsUIMainWindow(QWidget* parent = nullptr);
    ~tlinsUIMainWindow();

private:
    tlinsEditDatabaseObject editObject;
    Ui::tlinsUIMainWindow* ui;
};

tlinsUIMainWindow* getMainWindowInstance();

#endif // TLINSUIMAINWINDOW_H
