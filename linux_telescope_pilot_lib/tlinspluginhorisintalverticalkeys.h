#ifndef TLINSPLUGINHORISINTALVERTICALKEYS_H
#define TLINSPLUGINHORISINTALVERTICALKEYS_H


#include <tlinscommunicationthread.h>
#include "tlinsshortcutsmanager.h"
#include <tlinsastrouibase.h>

#include <atomic>

namespace tlinsAstroPilot
{

class tlinsPluginHorisintalVerticalKeys : public tlinsShortCutInterface
{

public:
    enum class DIRECTION { LEFT = 1, RIGHT = 2 };
    enum class AXIS { X = 1, Y = 2 };

private:
    std :: string name;
    std :: vector<int> keys;
    std :: atomic<bool> speedModeRequestStoped;

    // Znaczniki czy osie sa w ruch czy nie
    // Jest to roztrzygane na podstawie stanu wcisniecia klawisza
    // Inicialnie mamy zalozenie ze onie osie sa zatrzymane
    bool xReleased;
    bool yReleased;

    DIRECTION direction;
    AXIS axis;

public:
    // Joistick
    virtual void callback(const std::list<TlinsAstroBase :: tlinsJoystick :: keyStatusInfo> &, const TlinsAstroBase :: tlinsJoystick :: keyStatusInfo &);
    virtual void callbackRel(const std::list<TlinsAstroBase :: tlinsJoystick :: keyStatusInfo> &, const TlinsAstroBase :: tlinsJoystick :: keyStatusInfo &);

    virtual void defaultEnter(const TlinsAstroBase :: tlinsJoystick :: keyStatusInfo &);
    virtual void defaultRelease(const TlinsAstroBase :: tlinsJoystick :: keyStatusInfo &);

    virtual void callback();
    virtual void release();

    virtual std :: string getName();

    virtual const std :: vector<int> &getKeys();

    tlinsPluginHorisintalVerticalKeys(const std :: string &name_,
                                      const std :: vector<int> &keys_,
                                      const std :: string &cfg );

    tlinsPluginHorisintalVerticalKeys &operator=(const tlinsPluginHorisintalVerticalKeys &v) = default;
    tlinsPluginHorisintalVerticalKeys() = delete;

    virtual ~tlinsPluginHorisintalVerticalKeys();
};

class tlinsPluginHorisintalVerticalKeysFactory : public tlinsShortCutFactoryInterface
{
public:
    virtual std :: shared_ptr<tlinsShortCutInterface> createInstance( const TlinsAstroBase ::tlinsKeysSortcutType type,
                                                                      const TlinsAstroBase :: tlinsKeysSortcutSubType subType,
                                                                      const std :: string name,
                                                                      const std :: string &cfg,
                                                                      const TlinsAstroBase :: tlinsPilotShortcutsDefinitionValidMode mode,
                                                                      const std :: vector<int> &keys_ ) noexcept;

    tlinsPluginHorisintalVerticalKeysFactory() = default;
    virtual ~tlinsPluginHorisintalVerticalKeysFactory();
};

};

#endif // TLINSPLUGINHORISINTALVERTICALKEYS_H
