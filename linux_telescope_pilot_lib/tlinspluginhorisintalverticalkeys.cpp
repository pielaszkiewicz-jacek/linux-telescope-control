#include "tlinspluginhorisintalverticalkeys.h"
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

void tlinsPluginHorisintalVerticalKeys :: defaultEnter(const TlinsAstroBase :: tlinsJoystick :: keyStatusInfo &event)
{
    std::list<TlinsAstroBase :: tlinsJoystick :: keyStatusInfo> dummyList{};
    callback(dummyList, event);
}

void tlinsPluginHorisintalVerticalKeys :: defaultRelease(const TlinsAstroBase :: tlinsJoystick :: keyStatusInfo &event)
{
    std::list<TlinsAstroBase :: tlinsJoystick :: keyStatusInfo> dummyList{};
    callbackRel(dummyList, event );
}

void tlinsPluginHorisintalVerticalKeys :: callback(const std::list<TlinsAstroBase :: tlinsJoystick :: keyStatusInfo> &, const TlinsAstroBase :: tlinsJoystick :: keyStatusInfo &event )
{
    long scaleMax = 32767;
    long scaleX   = 0;
    long scaleY   = 0;
    bool isLeftX  = false;
    bool isLeftY  = false;
    bool axisX    = false;
    bool axisY    = false;

    // Instancja statusu
    auto &stateInst = tlinsPluginsState::getInstance();

    // Pelna inicializacja gdy obie osie  byly nieruchome
    bool fullInit = xReleased && yReleased;

    switch(this->axis) {
    case tlinsPluginHorisintalVerticalKeys::AXIS::X:
        axisX     = true;
        axisY     = false;
        scaleX    = stateInst.getXScale();
        xReleased = false;

        if(direction == DIRECTION::LEFT) {
            isLeftX = true;
        } else {
            isLeftX = false;
        }
        break;

    case tlinsPluginHorisintalVerticalKeys::AXIS::Y:
        axisX     = false;
        axisY     = true;
        scaleY    = stateInst.getYScale();
        yReleased = false;

        if(direction == DIRECTION::LEFT) {
            isLeftY = true;
        } else {
            isLeftY = false;
        }
        break;
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

void tlinsPluginHorisintalVerticalKeys :: callbackRel(const std::list<TlinsAstroBase :: tlinsJoystick :: keyStatusInfo> &, const TlinsAstroBase :: tlinsJoystick :: keyStatusInfo &event )
{
    bool axisX = false;
    bool axisY = false;

    switch(this->axis) {
    case tlinsPluginHorisintalVerticalKeys::AXIS::X:
        axisX     = true;  // Os pozioma
        xReleased = true;
        break;

    case tlinsPluginHorisintalVerticalKeys::AXIS::Y:
        axisY = true;  // Os pionowa
        yReleased = true;
        break;
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

void tlinsPluginHorisintalVerticalKeys :: callback()
{
}

void tlinsPluginHorisintalVerticalKeys :: release()
{
}

std :: string tlinsPluginHorisintalVerticalKeys :: getName()
{
    return name;
}

const std :: vector<int> &tlinsPluginHorisintalVerticalKeys :: getKeys()
{
    return keys;
}


//
// Konfiguracja
//

/*
  {
     "axis":"X",
     "direction":"left"|"right"
  }

 */

tlinsPluginHorisintalVerticalKeys :: tlinsPluginHorisintalVerticalKeys( const std :: string &name_,
                                                                                  const std :: vector<int> &keys_,
                                                                                  const std :: string &cfg ) :
    name{name_},
    keys{keys_},
    speedModeRequestStoped{ true },
    xReleased{true},
    yReleased{true}
{
    QJsonDocument doc = QJsonDocument :: fromJson( QString :: fromStdString( cfg ).toUtf8() );

    //
    // Os
    //
    {
        QJsonValue v = doc[QString("axis")];
        if( !v.isString() )
        {
            // Przekazana wartosc nie jest typu double
            __THROW__( TlinsAstroBase :: tlinsUIException( TlinsAstroBase :: tlinsUIException :: ERROR_INVALID_PARAMETER, "Parameter value is not a string" ) );
        }

        if(v.toString().toUpper() == "X")
            axis = AXIS::X;
        else if(v.toString().toUpper() == "Y")
            axis = AXIS::Y;
        else
        {
            // Niezanan nazwa osi
            __THROW__( TlinsAstroBase :: tlinsUIException( TlinsAstroBase :: tlinsUIException :: ERROR_INVALID_PARAMETER, "Unknown Axis" ) );
        }
    }

    //
    // Kierunek
    //
    {
        QJsonValue v = doc[QString("direction")];
        if( !v.isString() )
        {
            // Przekazana wartosc nie jest typu double
            __THROW__( TlinsAstroBase :: tlinsUIException( TlinsAstroBase :: tlinsUIException :: ERROR_INVALID_PARAMETER, "Parameter value is not a string" ) );
        }

        if(v.toString().toUpper() == "LEFT")
            direction = DIRECTION::LEFT;
        else if(v.toString().toUpper() == "RIGHT")
            direction = DIRECTION::RIGHT;
        else
        {
            // Niezanan nazwa osi
            __THROW__( TlinsAstroBase :: tlinsUIException( TlinsAstroBase :: tlinsUIException :: ERROR_INVALID_PARAMETER, "Unknown direction" ) );
        }
    }
}

tlinsPluginHorisintalVerticalKeys :: ~tlinsPluginHorisintalVerticalKeys()
{
}

//
// ----
//
std :: shared_ptr<tlinsShortCutInterface> tlinsPluginHorisintalVerticalKeysFactory :: createInstance( const TlinsAstroBase ::tlinsKeysSortcutType,
                                                                                                      const TlinsAstroBase :: tlinsKeysSortcutSubType,
                                                                                                      const std :: string name,
                                                                                                      const std :: string &cfg,
                                                                                                      const TlinsAstroBase :: tlinsPilotShortcutsDefinitionValidMode,
                                                                                                      const std :: vector<int> &keys ) noexcept
{
    return std :: shared_ptr<tlinsShortCutInterface>{ new tlinsPluginHorisintalVerticalKeys{ name, keys, cfg } };
}

tlinsPluginHorisintalVerticalKeysFactory :: ~tlinsPluginHorisintalVerticalKeysFactory()
{
}

//
// Rejestracja fabryki w menagerze
//
static tlinsShortcutsFactoryCreator<tlinsPluginHorisintalVerticalKeysFactory> __creator__{"horisontal-vertical-move-keys"};

};
