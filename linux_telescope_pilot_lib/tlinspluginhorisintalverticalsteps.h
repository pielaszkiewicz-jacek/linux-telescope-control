#ifndef TLINSPLUGINHORISINTALVERTICALSTEPS_H
#define TLINSPLUGINHORISINTALVERTICALSTEPS_H

#include <tlinscommunicationthread.h>
#include "tlinsshortcutsmanager.h"
#include <tlinsastrouibase.h>

namespace tlinsAstroPilot
{

class tlinsPluginHorisintalVerticalSteps : public tlinsShortCutInterface
{
private:
    // Tryb przemieszczenia
    TlinsAstroBase :: tlinsAstroBase :: Mode mode;

    // Oso obrotu
    bool aX;
    bool aY;

    bool leftX;
    bool leftY;

    std :: string name;
    std :: vector<int> keys;

public:

    virtual void callback(const std::list<TlinsAstroBase :: tlinsJoystick :: keyStatusInfo> &, const TlinsAstroBase :: tlinsJoystick :: keyStatusInfo &);
    virtual void callbackRel(const std::list<TlinsAstroBase :: tlinsJoystick :: keyStatusInfo> &, const TlinsAstroBase :: tlinsJoystick :: keyStatusInfo &);

    virtual void defaultEnter(const TlinsAstroBase :: tlinsJoystick :: keyStatusInfo &);
    virtual void defaultRelease(const TlinsAstroBase :: tlinsJoystick :: keyStatusInfo &);

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

    tlinsPluginHorisintalVerticalSteps() = delete;
    tlinsPluginHorisintalVerticalSteps( const std :: string &name_,
                                        const std :: vector<int> &keys_,
                                        const std :: string &cfg );

    tlinsPluginHorisintalVerticalSteps &operator=( const tlinsPluginHorisintalVerticalSteps &v ) = default;

    virtual ~tlinsPluginHorisintalVerticalSteps() = default;
};


class tlinsPluginHorisintalVerticalStepsFactory : public tlinsShortCutFactoryInterface
{
public:
    virtual std :: shared_ptr<tlinsShortCutInterface> createInstance( const TlinsAstroBase ::tlinsKeysSortcutType type,
                                                                      const TlinsAstroBase :: tlinsKeysSortcutSubType subType,
                                                                      const std :: string name,
                                                                      const std :: string &cfg,
                                                                      const TlinsAstroBase :: tlinsPilotShortcutsDefinitionValidMode mode,
                                                                      const std :: vector<int> &keys_ ) noexcept;

    tlinsPluginHorisintalVerticalStepsFactory() = default;
    virtual ~tlinsPluginHorisintalVerticalStepsFactory();
};

};

#endif // TLINSPLUGINHORISINTALVERTICALSTEPS_H
