#ifndef TLINSPLUGINTRACKINGSTART_H
#define TLINSPLUGINTRACKINGSTART_H

#include "tlinsshortcutsmanager.h"

namespace tlinsAstroPilot
{

class tlinsPluginTrackingStart : public tlinsShortCutInterface
{
private:
    std :: string name;
    std :: vector<int> keys;

public:
    virtual void callback(const std::list<TlinsAstroBase :: tlinsJoystick :: keyStatusInfo> &, const TlinsAstroBase :: tlinsJoystick :: keyStatusInfo &);
    virtual void callbackRel(const std::list<TlinsAstroBase :: tlinsJoystick :: keyStatusInfo> &, const TlinsAstroBase :: tlinsJoystick :: keyStatusInfo &);

    virtual void callback();
    virtual void release();

    virtual std :: string getName()
    {
        return name;
    }

    virtual const std :: vector<int> &getKeys()
    {
        return keys;
    }

    tlinsPluginTrackingStart() = delete;
    tlinsPluginTrackingStart(const std :: string &name_,
                             const std :: vector<int> &keys_ );

    virtual ~tlinsPluginTrackingStart() = default;
};

class tlinsPluginTrackingStartFactory : public tlinsShortCutFactoryInterface
{
public:
    virtual std :: shared_ptr<tlinsShortCutInterface> createInstance( const TlinsAstroBase ::tlinsKeysSortcutType type,
                                                                      const TlinsAstroBase :: tlinsKeysSortcutSubType subType,
                                                                      const std :: string name,
                                                                      const std :: string &cfg,
                                                                      const TlinsAstroBase :: tlinsPilotShortcutsDefinitionValidMode mode,
                                                                      const std :: vector<int> &keys_ ) noexcept;

    tlinsPluginTrackingStartFactory() = default;
    virtual ~tlinsPluginTrackingStartFactory();
};

};

#endif // TLINSPLUGINTRACKINGSTART_H
