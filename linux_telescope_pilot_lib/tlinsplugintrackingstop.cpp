#include "tlinsplugintrackingstop.h"
#include "tlinscommunicationthread.h"
#include "tlinsastrouibase.h"
#include <tlinsBacktrace.hpp>

namespace tlinsAstroPilot
{

void tlinsPluginTrackingStop :: callback(const std::list<TlinsAstroBase :: tlinsJoystick :: keyStatusInfo> &, const TlinsAstroBase :: tlinsJoystick :: keyStatusInfo &)
{
	callback();
}

void tlinsPluginTrackingStop :: callbackRel(const std::list<TlinsAstroBase :: tlinsJoystick :: keyStatusInfo> &, const TlinsAstroBase :: tlinsJoystick :: keyStatusInfo &)
{
}

void tlinsPluginTrackingStop :: callback()
{
    bool isAstro = false;
    bool isTrackingEnabled = false;

    // Okreslenie stanu kontrolera
    TlinsAstroBase ::tlinsAstroBase::getAstroStaetInfo(isAstro, isTrackingEnabled);
    if(isAstro) {
        TlinsAstroBase :: tlinsAstroBase :: trackingStop(true, true);
	}
}

void tlinsPluginTrackingStop :: release()
{
}

tlinsPluginTrackingStop :: tlinsPluginTrackingStop(const std :: string &name_,
                                                   const std :: vector<int> &keys_ ) : name{ name_ }, keys{ keys_ }
{
}

//
// --------------------------------------------------------
// --------------------------------------------------------
//

std :: shared_ptr<tlinsShortCutInterface> tlinsPluginTrackingStopFactory :: createInstance( const TlinsAstroBase ::tlinsKeysSortcutType,
                                                                      const TlinsAstroBase :: tlinsKeysSortcutSubType,
                                                                      const std :: string name,
                                                                      const std :: string &,
                                                                      const TlinsAstroBase :: tlinsPilotShortcutsDefinitionValidMode,
                                                                      const std :: vector<int> &keys_ ) noexcept
{
	return std :: shared_ptr<tlinsShortCutInterface>{ new tlinsPluginTrackingStop{ name, keys_} };
}

tlinsPluginTrackingStopFactory :: ~tlinsPluginTrackingStopFactory()
{
}

static tlinsShortcutsFactoryCreator<tlinsPluginTrackingStopFactory> __creator__{"tracking-stop"};

};
