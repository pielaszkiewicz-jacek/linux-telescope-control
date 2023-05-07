#include "tlinswtrackingcontrol.h"
#include "tlinsuimainwindow.h"
#include "ui_tlinswtrackingcontrol.h"
#include <tlinscommunicationthread.h>

#include <tlinsAstroEngineInterface.hpp>
#include <tlinsAstroObject.hpp>
#include <tlinsCoordinate.hpp>
#include <tlinsconfiguration.h>

#include <QDebug>
#include <tlinsastrouibase.h>

class tlinsTrackControlStart : public TlinsAstroBase::tlinsCommunicationThreadRequest {
private:
    std::shared_ptr<TlinsAstroBase::tlinsConnectionContext> connection;
    double RA;
    double DEC;

public:
    void confirm()
    {
        TlinsAstroBase::tlinsCommunicationThreadRequest::confirm();
    }

    virtual void operator()() noexcept
    {
        try {
            connection->getAstro()->setTracking(RA, DEC);
            connection->getAstro()->setTrackingState(true);

            getMainWindowInstance()->popupStatusSlot("Tracking enabled");
            getMainWindowInstance()->logEventSlot("Tracking enabled");
        } catch (tlinsInterfaceException&) {
            getMainWindowInstance()->popupStatusSlot("Error tracking enable");
            getMainWindowInstance()->logEventSlot("Error tracking enable");
            return;
        }
    }
    virtual bool isAsynchronuus()
    {
        return false;
    }

    virtual std::string name()
    {
        return "tlinsTrackingStart";
    }

    tlinsTrackControlStart(const double ra, const double dec)
    {
        // Pobranie polaczenia
        if (!TlinsAstroBase::tlinsConnectionsManager::getInstance().hasConnection(std::string { TLINS_CONNECTION_DEFAULT })) {
            getMainWindowInstance()->popupStatusSlot("Error tracking enable");
            getMainWindowInstance()->logEventSlot("Error tracking enable");
            __THROW__(tlinsException(std::string("No active connection: ") + std::string(TLINS_CONNECTION_DEFAULT), -1));
        }

        // Polaczenie
        connection = TlinsAstroBase::tlinsConnectionsManager::getInstance().getConnection(TLINS_CONNECTION_DEFAULT);

        RA = ra;
        DEC = dec;
    }

    virtual ~tlinsTrackControlStart()
    {
        connection.reset();
    }
};

void tlinsWTrackingControl::start()
{
    double RA = ui->ra->getValue();
    double DEC = ui->dec->getValue();

    auto& tInst = TlinsAstroBase::tlinsCommunicationThread::getInstance();
    auto ptr = std::unique_ptr<TlinsAstroBase::tlinsCommunicationThreadRequest>(new tlinsTrackControlStart(RA, DEC));
    tInst.push(ptr);
}

class tlinsTrackControlStop : public TlinsAstroBase::tlinsCommunicationThreadRequest {
private:
    std::shared_ptr<TlinsAstroBase::tlinsConnectionContext> connection;

public:
    void confirm()
    {
        TlinsAstroBase::tlinsCommunicationThreadRequest::confirm();
    }

    virtual void operator()() noexcept
    {
        try {
            connection->getAstro()->setTrackingState(false);

            getMainWindowInstance()->popupStatusSlot("Tracking stoped");
            getMainWindowInstance()->logEventSlot("Tracking stoped");
        } catch (tlinsInterfaceException&) {
            getMainWindowInstance()->popupStatusSlot("Error tracking start");
            getMainWindowInstance()->logEventSlot("Error tracking start");
            return;
        }
    }
    virtual bool isAsynchronuus()
    {
        return false;
    }

    virtual std::string name()
    {
        return "tlinsTrackingStart";
    }

    tlinsTrackControlStop()
    {
        // Pobranie polaczenia
        if (!TlinsAstroBase::tlinsConnectionsManager::getInstance().hasConnection(std::string { TLINS_CONNECTION_DEFAULT })) {
            getMainWindowInstance()->popupStatusSlot("Error tracking enable");
            getMainWindowInstance()->logEventSlot("Error tracking enable");
            __THROW__(tlinsException(std::string("No active connection: ") + std::string(TLINS_CONNECTION_DEFAULT), -1));
        }

        // Polaczenie
        connection = TlinsAstroBase::tlinsConnectionsManager::getInstance().getConnection(TLINS_CONNECTION_DEFAULT);
    }

    virtual ~tlinsTrackControlStop()
    {
        connection.reset();
    }
};

void tlinsWTrackingControl::stop()
{
    auto& tInst = TlinsAstroBase::tlinsCommunicationThread::getInstance();
    auto ptr = std::unique_ptr<TlinsAstroBase::tlinsCommunicationThreadRequest>(new tlinsTrackControlStop());
    tInst.push(ptr);
}

tlinsWTrackingControl::tlinsWTrackingControl(QWidget* parent)
    : QWidget(parent)
    , ui(new Ui::tlinsWTrackingControl)
{
    ui->setupUi(this);
}

tlinsWTrackingControl::~tlinsWTrackingControl()
{
    delete ui;
}
