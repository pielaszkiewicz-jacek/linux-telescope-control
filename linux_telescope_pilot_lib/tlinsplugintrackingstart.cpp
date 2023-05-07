#include "tlinsplugintrackingstart.h"
#include "tlinscommunicationthread.h"
#include "tlinsastrouibase.h"
#include <tlinsBacktrace.hpp>

namespace tlinsAstroPilot
{

void tlinsPluginTrackingStart :: callback(const std::list<TlinsAstroBase :: tlinsJoystick :: keyStatusInfo> &, const TlinsAstroBase :: tlinsJoystick :: keyStatusInfo &)
{
    callback();
}

void tlinsPluginTrackingStart :: callbackRel(const std::list<TlinsAstroBase :: tlinsJoystick :: keyStatusInfo> &, const TlinsAstroBase :: tlinsJoystick :: keyStatusInfo &)
{
}

void tlinsPluginTrackingStart :: callback()
{
    bool isAstro = false;
    bool isTrackingEnabled = false;
    TlinsAstroBase ::tlinsAstroBase::getAstroStaetInfo(isAstro, isTrackingEnabled);

    if(isAstro) {
        TlinsAstroBase :: tlinsAstroBase :: trackingSart(false);
	}
}

void tlinsPluginTrackingStart :: release()
{
}


tlinsPluginTrackingStart :: tlinsPluginTrackingStart(const std :: string &name_,
                                                     const std :: vector<int> &keys_ ) : name{ name_ }, keys{ keys_ }
{
}


//
// --------------------------------------------------------
// --------------------------------------------------------
//

std :: shared_ptr<tlinsShortCutInterface> tlinsPluginTrackingStartFactory :: createInstance( const TlinsAstroBase ::tlinsKeysSortcutType,
                                                                      const TlinsAstroBase :: tlinsKeysSortcutSubType,
                                                                      const std :: string name,
                                                                      const std :: string &,
                                                                      const TlinsAstroBase :: tlinsPilotShortcutsDefinitionValidMode,
                                                                      const std :: vector<int> &keys_ ) noexcept
{
    return std :: shared_ptr<tlinsShortCutInterface>{ new tlinsPluginTrackingStart{ name, keys_} };
}

tlinsPluginTrackingStartFactory :: ~tlinsPluginTrackingStartFactory()
{
}

static tlinsShortcutsFactoryCreator<tlinsPluginTrackingStartFactory> __creator__{"tracking-start"};

};
