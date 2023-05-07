#include "tlinspluginclosecalibration.h"

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

class tlinsPluginCloseCalibrationRequest : public TlinsAstroBase ::tlinsCommunicationThreadRequest {
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

    tlinsPluginCloseCalibrationRequest();
    virtual ~tlinsPluginCloseCalibrationRequest();
};

void tlinsPluginCloseCalibrationRequest ::confirm()
{
    TlinsAstroBase ::tlinsCommunicationThreadRequest ::confirm();
}

void tlinsPluginCloseCalibrationRequest ::operator()() noexcept
{
    try {
        // Zamkniecie kalibracji
        connection->getAstro()->closeCalibration();
        qDebug() << "Calibrarion has been closed";
    } catch (const tlinsInterfaceException&) {
        // Mamy blad wywolania nie bedzie potwierdzenia asynchronicznego
        qDebug() << "Error close calibration";
    }
}

bool tlinsPluginCloseCalibrationRequest ::isAsynchronuus()
{
    return false;
}

tlinsPluginCloseCalibrationRequest ::tlinsPluginCloseCalibrationRequest()
{
    // Pobranie polaczenia
    if (!TlinsAstroBase ::tlinsConnectionsManager ::getInstance().hasConnection(std::string { TLINS_CONNECTION_DEFAULT }))
        __THROW__(tlinsException(std ::string("No active connection: ") + std ::string(TLINS_CONNECTION_DEFAULT), -1));

    // Polaczenie
    connection = TlinsAstroBase ::tlinsConnectionsManager ::getInstance().getConnection(TLINS_CONNECTION_DEFAULT);
}

tlinsPluginCloseCalibrationRequest ::~tlinsPluginCloseCalibrationRequest()
{
    connection.reset();
}

// -------------------------------------

void tlinsPluginCloseCalibration ::set()
{
    try {
        auto ptr = new tlinsPluginCloseCalibrationRequest {};
        std ::unique_ptr<TlinsAstroBase ::tlinsCommunicationThreadRequest> req(ptr);
        TlinsAstroBase ::tlinsCommunicationThread ::getInstance().push(req);
    } catch (tlinsInterfaceException&) {
        qDebug() << "Error close calibration";
    }
}

//
// --- Joistick
//
void tlinsPluginCloseCalibration ::callback(const std::list<TlinsAstroBase ::tlinsJoystick ::keyStatusInfo>&, const TlinsAstroBase ::tlinsJoystick ::keyStatusInfo&)
{
    set();
}

void tlinsPluginCloseCalibration ::callbackRel(const std::list<TlinsAstroBase ::tlinsJoystick ::keyStatusInfo>&, const TlinsAstroBase ::tlinsJoystick ::keyStatusInfo&)
{
}

//
// -- Keboard
//
void tlinsPluginCloseCalibration ::callback()
{
    set();
}

void tlinsPluginCloseCalibration ::release()
{
}

tlinsPluginCloseCalibration ::tlinsPluginCloseCalibration(const std ::string& name_,
    const std ::vector<int>& keys_,
    const std ::string& cfg_)
    : name { name_ }
    , keys { keys_ }
    , cfg { cfg_ }
{
}

tlinsPluginCloseCalibration ::~tlinsPluginCloseCalibration()
{
}

//
// -----
//
std ::shared_ptr<tlinsShortCutInterface> tlinsPluginCloseCalibrationFactory ::createInstance(const TlinsAstroBase ::tlinsKeysSortcutType,
    const TlinsAstroBase ::tlinsKeysSortcutSubType,
    const std ::string name,
    const std ::string& cfg,
    const TlinsAstroBase ::tlinsPilotShortcutsDefinitionValidMode,
    const std ::vector<int>& keys_) noexcept
{
    return std ::shared_ptr<tlinsShortCutInterface> { new tlinsPluginCloseCalibration { name, keys_, cfg } };
}

tlinsPluginCloseCalibrationFactory ::~tlinsPluginCloseCalibrationFactory()
{
}

//
// Rejestracja fabryki w menagerze
//
static tlinsShortcutsFactoryCreator<tlinsPluginCloseCalibrationFactory> __creator__ { "close-calibration" };

};
