#include "tlinspluginutilsmoverequest.h"
#include "tlinspluginsstate.h"

#include <tlinsastrouibase.h>
#include <tlinsconfiguration.h>
#include <tlinsserverstatusinfo.h>

namespace tlinsAstroPilot {

void tlinsPluginUtilsMoveRequest ::moveCb ::process(const tlins ::tlinsRpcConfirmationStatus&)
{
    parent.confirm();
}

bool tlinsPluginUtilsMoveRequest ::moveCb ::release()
{
    return true;
}

void tlinsPluginUtilsMoveRequest ::confirm()
{
    TlinsAstroBase ::tlinsCommunicationThreadRequest ::confirm();
}

void tlinsPluginUtilsMoveRequest ::operator()() noexcept
{
    try {
        // Nazwa urzadzenia glownego
        std ::string mainDeviceName = "main";
        auto& cfg = TlinsAstroBase ::tlinsConfiguration ::getInstance();

        if (cfg.hasKey(TlinsAstroBase ::tlinsConfiguration ::COMMON_PARAMETER_GROUP,
                TlinsAstroBase ::tlinsConfiguration ::COMMON_MAIN_DEVICE_NAME))
            mainDeviceName = cfg.getString(TlinsAstroBase ::tlinsConfiguration ::COMMON_PARAMETER_GROUP,
                TlinsAstroBase ::tlinsConfiguration ::COMMON_MAIN_DEVICE_NAME);

        // Uruchomienie zapytania
        connection->getDevice()->moveRequest(mainDeviceName, *request, callback);
    } catch (tlinsInterfaceException&) {
        // Mamy blad wywolania nie bedzie potwierdzenia asynchronicznego
        confirm();
        return;
    }
}

bool tlinsPluginUtilsMoveRequest ::isAsynchronuus()
{
    return true;
}

tlinsPluginUtilsMoveRequest ::tlinsPluginUtilsMoveRequest(std ::unique_ptr<tlinsMoveServerInterface ::MoveRequestDevice>& ptr)
    : request { std ::move(ptr) }
{
    // Pobranie polaczenia
    if (!TlinsAstroBase ::tlinsConnectionsManager ::getInstance().hasConnection(std::string { TLINS_CONNECTION_DEFAULT }))
        __THROW__(tlinsException(std ::string("No active connection: ") + std ::string(TLINS_CONNECTION_DEFAULT), -1));

    // Polaczenie
    connection = TlinsAstroBase ::tlinsConnectionsManager ::getInstance().getConnection(TLINS_CONNECTION_DEFAULT);

    // Obiekt potwierdzen
    callback.reset(new moveCb { *this });
}

tlinsPluginUtilsMoveRequest ::~tlinsPluginUtilsMoveRequest()
{
    connection.reset();
}

//
// ------------------------------------------------------------
// ------------------------------------------------------------
// ------------------------------------------------------------
//

void tlinsPluginUtilsStopTracking ::confirm()
{
    TlinsAstroBase ::tlinsCommunicationThreadRequest ::confirm();
}

void tlinsPluginUtilsStopTracking ::operator()() noexcept
{
    try {
        connection->getAstro()->stopTracking();
    } catch (tlinsInterfaceException&) {
        // Mamy blad wywolania nie bedzie potwierdzenia asynchronicznego
        confirm();
        return;
    }
}

bool tlinsPluginUtilsStopTracking ::isAsynchronuus()
{
    return false;
}

tlinsPluginUtilsStopTracking ::tlinsPluginUtilsStopTracking()
{
    // Pobranie polaczenia
    if (!TlinsAstroBase ::tlinsConnectionsManager ::getInstance().hasConnection(std::string { TLINS_CONNECTION_DEFAULT }))
        __THROW__(tlinsException(std ::string("No active connection: ") + std ::string(TLINS_CONNECTION_DEFAULT), -1));

    // Polaczenie
    connection = TlinsAstroBase ::tlinsConnectionsManager ::getInstance().getConnection(TLINS_CONNECTION_DEFAULT);
}

tlinsPluginUtilsStopTracking ::~tlinsPluginUtilsStopTracking()
{
    connection.reset();
}

};
