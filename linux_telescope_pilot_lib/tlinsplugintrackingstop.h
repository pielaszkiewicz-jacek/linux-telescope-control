#ifndef TLINSPLUGINTRACKINGSTOP_H
#define TLINSPLUGINTRACKINGSTOP_H

#include "tlinsshortcutsmanager.h"

namespace tlinsAstroPilot
{

class tlinsPluginTrackingStop : public tlinsShortCutInterface
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

    tlinsPluginTrackingStop() = delete;
    tlinsPluginTrackingStop(const std :: string &name_,
                             const std :: vector<int> &keys_ );

    virtual ~tlinsPluginTrackingStop() = default;
};

class tlinsPluginTrackingStopFactory : public tlinsShortCutFactoryInterface
{
public:
    virtual std :: shared_ptr<tlinsShortCutInterface> createInstance( const TlinsAstroBase ::tlinsKeysSortcutType type,
                                                                      const TlinsAstroBase :: tlinsKeysSortcutSubType subType,
                                                                      const std :: string name,
                                                                      const std :: string &cfg,
                                                                      const TlinsAstroBase :: tlinsPilotShortcutsDefinitionValidMode mode,
                                                                      const std :: vector<int> &keys_ ) noexcept;

    tlinsPluginTrackingStopFactory() = default;
    virtual ~tlinsPluginTrackingStopFactory();
};

};

#endif // TLINSPLUGINTRACKINGSTOP_H
