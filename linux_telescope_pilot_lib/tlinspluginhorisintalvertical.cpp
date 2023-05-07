#include "tlinspluginhorisintalvertical.h"

#include "tlinspluginhorisintalvertical.h"
#include <tlinsAstroEngineInterface.hpp>
#include <tlinsastrobaseutils.h>
#include <tlinspluginsstate.h>
#include <tlinsuiexception.h>
#include <tlinsastrouibase.h>
#include <tlinsBacktrace.hpp>
#include "tlinspluginsstate.h"
#include <tlinsconfiguration.h>
#include <tlinsserverstatusinfo.h>
#include <tlinsastrobaseutils.h>
#include <monitors/tlinsKeysDefinition.hpp>

#include <QJsonDocument>

namespace tlinsAstroPilot
{

// Joistick

void tlinsPluginHorisintalVertical :: defaultEnter(const TlinsAstroBase :: tlinsJoystick :: keyStatusInfo &event)
{
    std::list<TlinsAstroBase :: tlinsJoystick :: keyStatusInfo> dummyList{};
    callback(dummyList, event);
}

void tlinsPluginHorisintalVertical :: defaultRelease(const TlinsAstroBase :: tlinsJoystick :: keyStatusInfo &event)
{
    std::list<TlinsAstroBase :: tlinsJoystick :: keyStatusInfo> dummyList{};
    callbackRel(dummyList, event );
}


void tlinsPluginHorisintalVertical :: callback(const std::list<TlinsAstroBase :: tlinsJoystick :: keyStatusInfo> &, const TlinsAstroBase :: tlinsJoystick :: keyStatusInfo &event )
{
    int value     = event.value;
    int axis      = event.axis;
    long scaleMax = 32767;
    long scaleX   = 0;
    long scaleY   = 0;
    bool isLeft   = false;
    bool isLeftX  = false;
    bool isLeftY  = false;
    bool axisX    = false;
    bool axisY    = false;

    // Kierunek
    if(value < 0)
    {
        isLeft = true;
        value *= -1;
    }
    else
    {
        isLeft = false;
    }

    // Pelna inicializacja gdy obie osie  byly nieruchome
    bool fullInit = xReleased && yReleased;

    if(axis == tlinsKeysDefinition :: AXIS_X)
    {
        // Os pozioma
        axisX     = true;
        scaleX    = value;
        isLeftX   = isLeft;
        xReleased = false;
    }
    else if(axis == tlinsKeysDefinition :: AXIS_Y)
    {
        // Os piono1
        axisY     = true;
        scaleY    = value;
        isLeftY   = isLeft;
        yReleased = false;
    }
    else
    {
        // Nieznana os obrotu
        TLINS_LOG_WARNING( "Unsuported axis - event will be ignored. !!!" );
        return;
    }

    bool isAstro = false;
    bool isTrackingEnabled = false;

    // Okreslenie stanu kontrolera
    TlinsAstroBase ::tlinsAstroBase::getAstroStaetInfo(isAstro, isTrackingEnabled);

    TlinsAstroBase :: tlinsAstroBase :: speedRequestMove( axisX, axisY,
                            isLeftX, isLeftY,
                            scaleX, scaleMax,
                            scaleY, scaleMax,
                            isAstro, fullInit,
                            TlinsAstroBase :: tlinsAstroBase :: Mode :: DEGRIS,
                            isTrackingEnabled);
}

void tlinsPluginHorisintalVertical :: callbackRel(const std::list<TlinsAstroBase :: tlinsJoystick :: keyStatusInfo> &, const TlinsAstroBase :: tlinsJoystick :: keyStatusInfo &event )
{
    int axis   = event.axis;
    bool axisX = false;
    bool axisY = false;

    if(axis == tlinsKeysDefinition :: AXIS_X)
    {
        axisX     = true;  // Os pozioma
        xReleased = true;
    }
    else
    if(axis == tlinsKeysDefinition :: AXIS_Y)
    {
        axisY = true;  // Os pionowa
        yReleased = true;
    }
    else
    {
        // Nieznana os obrotu
        TLINS_LOG_WARNING( "Unsuported axis - event will be ignored. !!!" );
        return;
    }

    bool isAstro = false;
    bool isTrackingEnabled = false;

    // Okreslenie stanu kontrolera
    TlinsAstroBase ::tlinsAstroBase::getAstroStaetInfo(isAstro, isTrackingEnabled);

    // Pelne zatrzymanie gdy obie osoie sa zatrzymane
    bool completeStop = xReleased && yReleased;
    TlinsAstroBase :: tlinsAstroBase :: speedRequestMoveRelease( axisX, axisY,
                                                                   isAstro, completeStop,
                                                                   TlinsAstroBase :: tlinsAstroBase :: Mode :: DEGRIS,
                                                                   isTrackingEnabled);
}

void tlinsPluginHorisintalVertical :: callback()
{
}

void tlinsPluginHorisintalVertical :: release()
{
}

std :: string tlinsPluginHorisintalVertical :: getName()
{
	return name;
}

const std :: vector<int> &tlinsPluginHorisintalVertical :: getKeys()
{
	return keys;
}

tlinsPluginHorisintalVertical :: tlinsPluginHorisintalVertical( const std :: string &name_,
                                                                                  const std :: vector<int> &keys_,
																				  const std :: string & ) : name{name_},
																											keys{keys_},
																											speedModeRequestStoped{ true },
																											xReleased{true},
																											yReleased{true}
{
}

tlinsPluginHorisintalVertical :: ~tlinsPluginHorisintalVertical()
{
}

//
// ----
//
std :: shared_ptr<tlinsShortCutInterface> tlinsPluginHorisintalVerticalFactory :: createInstance( const TlinsAstroBase ::tlinsKeysSortcutType,
																										   const TlinsAstroBase :: tlinsKeysSortcutSubType,
                                                                                                           const std :: string name,
                                                                                                           const std :: string &cfg,
																										   const TlinsAstroBase :: tlinsPilotShortcutsDefinitionValidMode,
                                                                                                           const std :: vector<int> &keys ) noexcept
{
    return std :: shared_ptr<tlinsShortCutInterface>{ new tlinsPluginHorisintalVertical{ name, keys, cfg } };
}

tlinsPluginHorisintalVerticalFactory :: ~tlinsPluginHorisintalVerticalFactory()
{
}

//
// Rejestracja fabryki w menagerze
//
static tlinsShortcutsFactoryCreator<tlinsPluginHorisintalVerticalFactory> __creator__{"horisontal-vertical-move"};

};
