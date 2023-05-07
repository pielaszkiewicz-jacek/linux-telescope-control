#ifndef TLINSSERVERSTATUSINFO_H
#define TLINSSERVERSTATUSINFO_H

#include "tlinsconnection.h"
#include <map>
#include <mutex>
#include <tlinsAstroEngineInterface.hpp>
#include <tlinsMoveServerInterface.hpp>

namespace TlinsAstroBase {

class tlinsServerStatusInfo {
private:
    // Stan kontrolera po kalibracji
    tlinsAstroEngineInterface::tlinsEngineStateInfo astroDeviceState;
    // Stan kontrolera podczas kalibracji
    tlinsAstroEngineInterface::tlinsCalibrarionStateInfo calibrarionState;

    // Status silnika kontrolujacego napedy
    tlinsMoveServerInterface::tlinsSerialDeviceMode deviceMode;
    std::map<std::string, tlinsMoveServerInterface::tlinsDeviceAxisInfo> deviceConfiguration;

    std::mutex mtx;
    std::string mainDeviceName;

public:
    std::map<std::string, tlinsMoveServerInterface::tlinsDeviceAxisInfo>& getDeviceConfiguration();
    void setDeviceConfiguration(const std::map<std::string, tlinsMoveServerInterface::tlinsDeviceAxisInfo>& v);

    std::string getMainDeviceName()
    {
        return mainDeviceName;
    }

    void setCalibrarionState(const tlinsAstroEngineInterface::tlinsCalibrarionStateInfo& state)
    {
        calibrarionState = state;
    }

    tlinsAstroEngineInterface::tlinsCalibrarionStateInfo& getCalibrarionState()
    {
        return calibrarionState;
    }

    void setAstroDeviceState(const tlinsAstroEngineInterface::tlinsEngineStateInfo& state);
    tlinsAstroEngineInterface::tlinsEngineStateInfo& getAstroDeviceState();

    void setDeviceMode(const tlinsMoveServerInterface::tlinsSerialDeviceMode& v);
    tlinsMoveServerInterface::tlinsSerialDeviceMode getDeviceMode();
    void update();
    void update(std::shared_ptr<TlinsAstroBase::tlinsConnectionContext> connection);

    static tlinsServerStatusInfo& getInstance();

private:
    tlinsServerStatusInfo(const std::string& devName);

public:
    tlinsServerStatusInfo() = delete;
    tlinsServerStatusInfo& operator()(const tlinsServerStatusInfo& v);
    tlinsServerStatusInfo(const tlinsServerStatusInfo& v);
    virtual ~tlinsServerStatusInfo();
};

}

#endif // TLINSSERVERSTATUSINFO_H
