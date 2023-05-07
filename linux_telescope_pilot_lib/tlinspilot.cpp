#include "tlinspilot.h"

#include "tlinsjoystickeventhandler.h"
#include "tlinskeyboardeventhandler.h"
#include <QtDebug>
#include <tlinsconfiguration.h>

#include <grpc++/channel.h>
#include <grpc++/client_context.h>
#include <grpc++/create_channel.h>
#include <grpc++/security/credentials.h>
#include <grpc/grpc.h>

#include <tlinsBacktrace.hpp>
#include <tlinsconnection.h>
#include <tlinsserverstatusinfo.h>

namespace tlinsAstroPilot {

//
// Funkcja iniciaslizuje polaczenie z  serwerem przemieszczenia i astro serwerem.
//
void tlinsPilot::connectMoveAndAstroService()
{
    //
    // Odczyt konfiguracji
    //
    auto& loggerInstance = tlinsLogger::instance();

    loggerInstance.setLoggerStd();
    loggerInstance.setLogLevel(tlinsLogger::LOG_LEVEL_DEBUG);

    auto& cfgInstance = TlinsAstroBase ::tlinsConfiguration ::getInstance();
    std ::string urlDev = "localhost:20001";
    std ::string urlDevAsync = "localhost:20003";
    std ::string urlAstro = "localhost:20000";

    if (cfgInstance.hasKey(TlinsAstroBase ::tlinsConfiguration ::CONNECTION_PARAMETER_GROUP,
            TlinsAstroBase ::tlinsConfiguration ::CONNECTION_PARAMETER_URL_DEVICE_ENGINE)) {
        urlDev = cfgInstance.getString(TlinsAstroBase ::tlinsConfiguration ::CONNECTION_PARAMETER_GROUP,
            TlinsAstroBase ::tlinsConfiguration ::CONNECTION_PARAMETER_URL_DEVICE_ENGINE);
    }

    if (cfgInstance.hasKey(TlinsAstroBase ::tlinsConfiguration ::CONNECTION_PARAMETER_GROUP,
            TlinsAstroBase ::tlinsConfiguration ::CONNECTION_PARAMETER_URL_DEVICE_ENGINE_ASYNCH)) {
        urlDevAsync = cfgInstance.getString(TlinsAstroBase ::tlinsConfiguration ::CONNECTION_PARAMETER_GROUP,
            TlinsAstroBase ::tlinsConfiguration ::CONNECTION_PARAMETER_URL_DEVICE_ENGINE_ASYNCH);
    }

    if (cfgInstance.hasKey(TlinsAstroBase ::tlinsConfiguration ::CONNECTION_PARAMETER_GROUP,
            TlinsAstroBase ::tlinsConfiguration ::CONNECTION_PARAMETER_URL_ASTRO_ENGINE)) {
        urlAstro = cfgInstance.getString(TlinsAstroBase ::tlinsConfiguration ::CONNECTION_PARAMETER_GROUP,
            TlinsAstroBase ::tlinsConfiguration ::CONNECTION_PARAMETER_URL_ASTRO_ENGINE);
    }

    auto& mgr = TlinsAstroBase ::tlinsConnectionsManager ::getInstance();
    mgr.setConnection(connectionName,
        urlDev.c_str(),
        urlDevAsync.c_str(),
        urlAstro.c_str());

    //
    // Pobranie statusu kontrolera osi
    //
    auto& statusInfo = TlinsAstroBase ::tlinsServerStatusInfo ::getInstance();
    statusInfo.update();
}

void tlinsPilot::connectService()
{
    auto& inst = TlinsAstroBase ::tlinsConfiguration ::getInstance();
    auto hasKey = inst.hasKey(TlinsAstroBase ::tlinsConfiguration ::CONNECTION_PARAMETER_GROUP,
        TlinsAstroBase ::tlinsConfiguration ::CONNECTION_PARAMETER_URL_SYSTEM_SERVICE);

    // Sopmyslny url
    std::string url { "localhost:20100" };
    if (hasKey) {
        url = inst.getString(TlinsAstroBase ::tlinsConfiguration ::CONNECTION_PARAMETER_GROUP,
            TlinsAstroBase ::tlinsConfiguration ::CONNECTION_PARAMETER_URL_SYSTEM_SERVICE);

        url = inst.getString(TlinsAstroBase ::tlinsConfiguration ::CONNECTION_PARAMETER_GROUP,
            TlinsAstroBase ::tlinsConfiguration ::CONNECTION_PARAMETER_URL_SYSTEM_SERVICE);
    }
    qDebug() << "URL: " << url.c_str();

    auto cred = grpc ::InsecureChannelCredentials();
    systemServiceChannel = grpc ::CreateChannel(url.c_str(), cred);
}

tlinsPilot::tlinsPilot(const std::string& connectionName_)
    : connectionName { connectionName_ }
{
    // Tworzenie polaczen
    connectService();
    connectMoveAndAstroService();

    // Tworzenie handlerow przetwarzajacych zadania
    lisenerKeyboard.reset(new tlinsKeyboardEventHandler { systemServiceChannel });
    lisenerJoystick.reset(new tlinsJoystickEventHandler { systemServiceChannel });
}

tlinsPilot ::~tlinsPilot()
{
    lisenerKeyboard.reset();
    lisenerJoystick.reset();
}

};
