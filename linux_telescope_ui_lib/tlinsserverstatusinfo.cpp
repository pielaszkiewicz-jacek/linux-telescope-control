#include "tlinsserverstatusinfo.h"
#include "tlinscommunicationthread.h"
#include "tlinsconfiguration.h"
#include "tlinsupdatestatemanager.h"
#include <QDebug>
#include <tlinsBacktrace.hpp>
#include <tlinsLogger.hpp>

//
// ---------------
//
namespace TlinsAstroBase {

class tlinsStateInfoaCallback : public TlinsAstroBase::tlinsCommunicationThreadRequest {
private:
    tlinsServerStatusInfo* parent;
    std::shared_ptr<TlinsAstroBase::tlinsConnectionContext> connection;

public:
    void confirm();

    virtual void operator()() noexcept;
    virtual bool isAsynchronuus();

    virtual std::string name()
    {
        return "tlinsStateInfoaCallback";
    }

    tlinsStateInfoaCallback(tlinsServerStatusInfo* parent);
    virtual ~tlinsStateInfoaCallback();
};

void tlinsStateInfoaCallback::operator()() noexcept
{
    parent->update(connection);
}

bool tlinsStateInfoaCallback::isAsynchronuus()
{
    return false;
}

tlinsStateInfoaCallback::tlinsStateInfoaCallback(tlinsServerStatusInfo* p)
    : parent { p }
{
    // Pobranie polaczenia
    if (!TlinsAstroBase::tlinsConnectionsManager::getInstance().hasConnection(std::string { TLINS_CONNECTION_DEFAULT }))
        __THROW__(tlinsException(std::string("No active connection: ") + std::string(TLINS_CONNECTION_DEFAULT), -1));

    // Polaczenie
    connection = TlinsAstroBase::tlinsConnectionsManager::getInstance().getConnection(TLINS_CONNECTION_DEFAULT);
}

tlinsStateInfoaCallback::~tlinsStateInfoaCallback()
{
    connection.reset();
}

//
// ---------------
//

void tlinsServerStatusInfo::update(std::shared_ptr<TlinsAstroBase::tlinsConnectionContext> connection)
{
    // Tryb pracy napedow
    try {
        tlinsMoveServerInterface::tlinsSerialDeviceMode mode;
        connection->getDevice()->getMoveMode(getMainDeviceName(), mode);
        setDeviceMode(mode);
    } catch (tlinsInterfaceException& exc) {
        TLINS_LOG_ERROR("Error id : " + std::to_string(exc.getErrorID()) + ", Error message : " + exc.getErrorMessage());
        return;
    }

    // Konfiguracja osi
    try {
        std::map<std::string, tlinsMoveServerInterface::tlinsDeviceAxisInfo> result;
        connection->getDevice()->deviceConfiguration(getMainDeviceName(), result);
        setDeviceConfiguration(result);
    } catch (tlinsInterfaceException& exc) {
        TLINS_LOG_ERROR("Error id : " + std::to_string(exc.getErrorID()) + "Error message : " + exc.getErrorMessage());
        return;
    }

    // Tryb pracy astro
    try {
        // Stan kalibracji
        tlinsAstroEngineInterface::tlinsCalibrarionStateInfo calibrarionState;
        connection->getAstro()->getCalibrationState(calibrarionState);
        setCalibrarionState(calibrarionState);

        if (calibrarionState.get_engineState() == tlinsAstroEngineInterface::tlinsEngineStateValue::STATE_REGULAR) {
            // Szczegolowy stan kontrolera - zwracany po zakonczonej kalibracji
            tlinsAstroEngineInterface::tlinsEngineStateInfo state;
            connection->getAstro()->getState(state);
            setAstroDeviceState(state);
        }

        // Aktualizacja wszystkich skladowych ktorych zachowanie zalezy od stanu kontrolera astro
        auto& ins = tlinsUpdateStateManager<tlinsAstroEngineInterface::tlinsEngineStateValue>::getInstance();
        ins.update(UPDATE_CATEGORY_ASTRO_STATUS, calibrarionState.get_engineState());
    } catch (tlinsInterfaceException& exc) {
        TLINS_LOG_ERROR("Error id : " + std::to_string(exc.getErrorID()) + "Error message : " + exc.getErrorMessage());
    }
}

std::map<std::string, tlinsMoveServerInterface::tlinsDeviceAxisInfo>& tlinsServerStatusInfo::getDeviceConfiguration()
{
    return deviceConfiguration;
}

void tlinsServerStatusInfo::setDeviceConfiguration(const std::map<std::string, tlinsMoveServerInterface::tlinsDeviceAxisInfo>& v)
{
    deviceConfiguration = v;
}

void tlinsServerStatusInfo::setAstroDeviceState(const tlinsAstroEngineInterface::tlinsEngineStateInfo& v)
{
    std::lock_guard<std::mutex> lock(mtx);
    astroDeviceState = v;
}

tlinsAstroEngineInterface::tlinsEngineStateInfo& tlinsServerStatusInfo::getAstroDeviceState()
{
    return astroDeviceState;
}

void tlinsServerStatusInfo::setDeviceMode(const tlinsMoveServerInterface::tlinsSerialDeviceMode& v)
{
    std::lock_guard<std::mutex> lock(mtx);
    deviceMode = v;
}

tlinsMoveServerInterface::tlinsSerialDeviceMode tlinsServerStatusInfo::getDeviceMode()
{
    return deviceMode;
}

void tlinsServerStatusInfo::update()
{
    std::unique_ptr<TlinsAstroBase::tlinsCommunicationThreadRequest> ptr { new tlinsStateInfoaCallback { this } };
    TlinsAstroBase::tlinsCommunicationThread::getInstance().push(ptr);
}

tlinsServerStatusInfo& tlinsServerStatusInfo::operator()(const tlinsServerStatusInfo& v)
{
    astroDeviceState = v.astroDeviceState;
    deviceMode = v.deviceMode;
    return *this;
}

tlinsServerStatusInfo& tlinsServerStatusInfo::getInstance()
{
    auto getName = []() {
        auto& cfgIns = TlinsAstroBase::tlinsConfiguration::getInstance();

        if (cfgIns.hasKey(TlinsAstroBase::tlinsConfiguration::COMMON_PARAMETER_GROUP,
                TlinsAstroBase::tlinsConfiguration::COMMON_MAIN_DEVICE_NAME))
            return cfgIns.getString(TlinsAstroBase::tlinsConfiguration::COMMON_PARAMETER_GROUP,
                TlinsAstroBase::tlinsConfiguration::COMMON_MAIN_DEVICE_NAME);

        return std::string("main");
    };

    static tlinsServerStatusInfo instance { getName() };
    return instance;
}

tlinsServerStatusInfo::tlinsServerStatusInfo(const tlinsServerStatusInfo& v)
{
    astroDeviceState = v.astroDeviceState;
    deviceMode = v.deviceMode;
}

tlinsServerStatusInfo::tlinsServerStatusInfo(const std::string& devName)
    : mainDeviceName { devName }
{
}

tlinsServerStatusInfo::~tlinsServerStatusInfo()
{
}

}
