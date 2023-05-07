#include "tlinspluginresetcalibration.h"

#include "tlinspluginsstate.h"
#include <tlinsAstroEngineInterface.hpp>
#include <tlinsBacktrace.hpp>
#include <tlinsastrobaseutils.h>
#include <tlinsastrouibase.h>
#include <tlinscommunicationthread.h>
#include <tlinsconfiguration.h>
#include <tlinspluginsstate.h>
#include <tlinsserverstatusinfo.h>
#include <tlinsuiexception.h>

#include <QDebug>

namespace tlinsAstroPilot {

class tlinsPluginResetCalibrationRequest : public TlinsAstroBase ::tlinsCommunicationThreadRequest {
private:
    std ::shared_ptr<TlinsAstroBase ::tlinsConnectionContext> connection;

public:
    void confirm();

    virtual void operator()() noexcept;
    virtual bool isAsynchronuus();
    virtual std ::string name()
    {
        // TODO
        return "";
    }

    tlinsPluginResetCalibrationRequest();
    virtual ~tlinsPluginResetCalibrationRequest();
};

void tlinsPluginResetCalibrationRequest ::confirm()
{
    TlinsAstroBase ::tlinsCommunicationThreadRequest ::confirm();
}

void tlinsPluginResetCalibrationRequest ::operator()() noexcept
{
    try {
        // Zamkniecie kalibracji
        connection->getAstro()->resetCalibration(tlinsAstroEngineInterface::ReverseDevice::DEVICE_SETTINGS,
                                                 tlinsAstroEngineInterface::ReverseDevice::DEVICE_SETTINGS);
        qDebug() << "Calibrarion has been closed";
    } catch (const tlinsInterfaceException&) {
        // Mamy blad wywolania nie bedzie potwierdzenia asynchronicznego
        qDebug() << "Error close calibration";
    }
}

bool tlinsPluginResetCalibrationRequest ::isAsynchronuus()
{
    return false;
}

tlinsPluginResetCalibrationRequest ::tlinsPluginResetCalibrationRequest()
{
    // Pobranie polaczenia
    if (!TlinsAstroBase ::tlinsConnectionsManager ::getInstance().hasConnection(std::string { TLINS_CONNECTION_DEFAULT }))
        __THROW__(tlinsException(std ::string("No active connection: ") + std ::string(TLINS_CONNECTION_DEFAULT), -1));

    // Polaczenie
    connection = TlinsAstroBase ::tlinsConnectionsManager ::getInstance().getConnection(TLINS_CONNECTION_DEFAULT);
}

tlinsPluginResetCalibrationRequest ::~tlinsPluginResetCalibrationRequest()
{
    connection.reset();
}

// -------------------------------------

void tlinsPluginResetCalibration ::set()
{
    try {

        auto ptr = new tlinsPluginResetCalibrationRequest {};
        std ::unique_ptr<TlinsAstroBase ::tlinsCommunicationThreadRequest> req(ptr);
        TlinsAstroBase ::tlinsCommunicationThread ::getInstance().push(req);
    } catch (tlinsInterfaceException&) {
        qDebug() << "Error close calibration";
    }
}

//
// --- Joystick
//
void tlinsPluginResetCalibration ::callback(const std::list<TlinsAstroBase ::tlinsJoystick ::keyStatusInfo>&, const TlinsAstroBase ::tlinsJoystick ::keyStatusInfo&)
{
    set();
}

void tlinsPluginResetCalibration ::callbackRel(const std::list<TlinsAstroBase ::tlinsJoystick ::keyStatusInfo>&, const TlinsAstroBase ::tlinsJoystick ::keyStatusInfo&)
{
}

//
// --- Keyboard
//
void tlinsPluginResetCalibration ::callback()
{
    set();
}

void tlinsPluginResetCalibration ::release()
{
}

tlinsPluginResetCalibration ::tlinsPluginResetCalibration(const std ::string& name_,
    const std ::vector<int>& keys_,
    const std ::string& cfg_)
    : name { name_ }
    , keys { keys_ }
    , cfg { cfg_ }
{
}

tlinsPluginResetCalibration ::~tlinsPluginResetCalibration()
{
}

//
// -----
//
std ::shared_ptr<tlinsShortCutInterface> tlinsPluginResetCalibrationFactory ::createInstance(const TlinsAstroBase ::tlinsKeysSortcutType,
    const TlinsAstroBase ::tlinsKeysSortcutSubType,
    const std ::string name,
    const std ::string& cfg,
    const TlinsAstroBase ::tlinsPilotShortcutsDefinitionValidMode,
    const std ::vector<int>& keys_) noexcept
{
    return std ::shared_ptr<tlinsShortCutInterface> { new tlinsPluginResetCalibration { name, keys_, cfg } };
}

tlinsPluginResetCalibrationFactory ::~tlinsPluginResetCalibrationFactory()
{
}

//
// Rejestracja fabryki w menagerze
//
static tlinsShortcutsFactoryCreator<tlinsPluginResetCalibrationFactory> __creator__ { "start-reset-calibration" };

};
