#include "tlinspluginsetreferenceobject.h"

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

class tlinsPluginSetReferenceObjectRequest : public TlinsAstroBase ::tlinsCommunicationThreadRequest {
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

    tlinsPluginSetReferenceObjectRequest();
    virtual ~tlinsPluginSetReferenceObjectRequest();
};

void tlinsPluginSetReferenceObjectRequest ::confirm()
{
    TlinsAstroBase ::tlinsCommunicationThreadRequest ::confirm();
}

void tlinsPluginSetReferenceObjectRequest ::operator()() noexcept
{
    try {
        // Zamkniecie kalibracji
        connection->getAstro()->confirmDeferedMeserment();
        qDebug() << "ferred reference object has been confirmed.";
    } catch (const tlinsInterfaceException&) {
        // Mamy blad wywolania nie bedzie potwierdzenia asynchronicznego
        qDebug() << "Error close calibration";
    }
}

bool tlinsPluginSetReferenceObjectRequest ::isAsynchronuus()
{
    return false;
}

tlinsPluginSetReferenceObjectRequest ::tlinsPluginSetReferenceObjectRequest()
{
    // Pobranie polaczenia
    if (!TlinsAstroBase ::tlinsConnectionsManager ::getInstance().hasConnection(std::string { TLINS_CONNECTION_DEFAULT }))
        __THROW__(tlinsException(std ::string("No active connection: ") + std ::string(TLINS_CONNECTION_DEFAULT), -1));

    // Polaczenie
    connection = TlinsAstroBase ::tlinsConnectionsManager ::getInstance().getConnection(TLINS_CONNECTION_DEFAULT);
}

tlinsPluginSetReferenceObjectRequest ::~tlinsPluginSetReferenceObjectRequest()
{
    connection.reset();
}

// ------------------------------------

void tlinsPluginSetReferenceObject ::set()
{
    try {
        auto ptr = new tlinsPluginSetReferenceObjectRequest {};
        std ::unique_ptr<TlinsAstroBase ::tlinsCommunicationThreadRequest> req(ptr);
        TlinsAstroBase ::tlinsCommunicationThread ::getInstance().push(req);
    } catch (tlinsInterfaceException&) {
        qDebug() << "Error close calibration";
    }
}

//
// Joystick
//
void tlinsPluginSetReferenceObject ::callback(const std::list<TlinsAstroBase ::tlinsJoystick ::keyStatusInfo>&, const TlinsAstroBase ::tlinsJoystick ::keyStatusInfo&)
{
    set();
}

void tlinsPluginSetReferenceObject ::callbackRel(const std::list<TlinsAstroBase ::tlinsJoystick ::keyStatusInfo>&, const TlinsAstroBase ::tlinsJoystick ::keyStatusInfo&)
{
}

//
// Keyboard
//
void tlinsPluginSetReferenceObject ::callback()
{
    set();
}

void tlinsPluginSetReferenceObject ::release()
{
}

tlinsPluginSetReferenceObject ::tlinsPluginSetReferenceObject(const std ::string& name_,
    const std ::vector<int>& keys_,
    const std ::string& cfg_)
    : name { name_ }
    , keys { keys_ }
    , cfg { cfg_ }
{
}

tlinsPluginSetReferenceObject ::~tlinsPluginSetReferenceObject()
{
}

//
// -----
//
std ::shared_ptr<tlinsShortCutInterface> tlinsPluginSetReferenceObjectFactory ::createInstance(const TlinsAstroBase ::tlinsKeysSortcutType,
    const TlinsAstroBase ::tlinsKeysSortcutSubType,
    const std ::string name,
    const std ::string& cfg,
    const TlinsAstroBase ::tlinsPilotShortcutsDefinitionValidMode,
    const std ::vector<int>& keys_) noexcept
{
    return std ::shared_ptr<tlinsShortCutInterface> { new tlinsPluginSetReferenceObject { name, keys_, cfg } };
}

tlinsPluginSetReferenceObjectFactory ::~tlinsPluginSetReferenceObjectFactory()
{
}

//
// Rejestracja fabryki w menagerze
//
static tlinsShortcutsFactoryCreator<tlinsPluginSetReferenceObjectFactory> __creator__ { "set-reference-object" };

};
