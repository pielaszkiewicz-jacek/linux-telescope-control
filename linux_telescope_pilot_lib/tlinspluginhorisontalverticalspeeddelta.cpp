#include "tlinspluginhorisontalverticalspeeddelta.h"

#include "tlinspluginsstate.h"
#include <tlinsuiexception.h>
#include <tlinsBacktrace.hpp>
#include <QJsonDocument>
#include <QDebug>

namespace tlinsAstroPilot
{

void tlinsPluginHorisontalVerticalSpeedDelta :: set()
{
    if( type == Type :: STEPS )
    {
        // Kroki
        if( axis == Axis :: H )
        {
            tlinsPluginsState :: getInstance().setXStepsSpeed( valueSteps );	// Poziomo
            qDebug() << "Update HORISONTAL steps delta. New value : " << tlinsPluginsState :: getInstance().getXStepsSpeed();
        }
        else
        {
            tlinsPluginsState :: getInstance().setYStepsSpeed( valueSteps );	// Pionowo
            qDebug() << "Update VERTICAL steps delta. New value : " << tlinsPluginsState :: getInstance().getYStepsSpeed();
        }
    }
    else
    {
        if( axis == Axis :: H )
        {
            tlinsPluginsState :: getInstance().setXDegrisSpeed( valueDegris );	// Poziomo
            qDebug() << "Update HORISONTAL delta. New value : " << tlinsPluginsState :: getInstance().getXDegrisSpeed();
        }
        else
        {
            tlinsPluginsState :: getInstance().setYDegrisSpeed( valueDegris );	// Pionowo
            qDebug() << "Update VERTICAL delta. New value : " << tlinsPluginsState :: getInstance().getYDegrisSpeed();
        }
    }
}

//
// --- Joystick
//
void tlinsPluginHorisontalVerticalSpeedDelta :: callback(const std::list<TlinsAstroBase :: tlinsJoystick :: keyStatusInfo> &, const TlinsAstroBase :: tlinsJoystick :: keyStatusInfo &)
{
    set();
}

void tlinsPluginHorisontalVerticalSpeedDelta :: callbackRel(const std::list<TlinsAstroBase :: tlinsJoystick :: keyStatusInfo> &, const TlinsAstroBase :: tlinsJoystick :: keyStatusInfo &)
{
}

//
// --- Keyboard
//
void tlinsPluginHorisontalVerticalSpeedDelta :: callback()
{
    set();
}

void tlinsPluginHorisontalVerticalSpeedDelta :: release()
{
	// Nic nie robimy
}

tlinsPluginHorisontalVerticalSpeedDelta :: tlinsPluginHorisontalVerticalSpeedDelta( const std :: string &name_,
                                                                                    const std :: vector<int> &keys_,
                                                                                    const std :: string &cfg_ ) : name{ name_ },
                                                                                                                  keys{ keys_ },
                                                                                                                  cfg{ cfg_ }
{
	//
	// Odczyt konfiguracji z jsona
	//
	QJsonDocument doc = QJsonDocument :: fromJson( QString :: fromStdString( cfg ).toUtf8() );

	{
		QJsonValue v = doc[QString("type")];
		if( !v.isString() )
		{
			// Przekazana wartosc nie jest typu double
			__THROW__( TlinsAstroBase :: tlinsUIException( TlinsAstroBase :: tlinsUIException :: ERROR_INVALID_PARAMETER, "Parameter value is not a string" ) );
		}

		if( v.toString().toUpper() != "STEPS" && v.toString().toUpper() != "DEGRIS" )
		{
			// Przekazana wartosc nie jest typu double
			__THROW__( TlinsAstroBase :: tlinsUIException( TlinsAstroBase :: tlinsUIException :: ERROR_INVALID_PARAMETER, "type must be equal \"degris\" or \"steps\"" ) );
		}

		if( v.toString().toUpper() == "STEPS" )
			type = Type :: STEPS;
		else
			type = Type :: DEGRIS;
	}

	{
		QJsonValue v = doc[QString("axis")];
		if( !v.isString() )
		{
			// Przekazana wartosc nie jest typu double
			__THROW__( TlinsAstroBase :: tlinsUIException( TlinsAstroBase :: tlinsUIException :: ERROR_INVALID_PARAMETER, "Parameter value is not a string" ) );
		}

		if( v.toString().toUpper() != "HORISONTAL" && v.toString().toUpper() != "VERTICAL" )
		{
			// Przekazana wartosc nie jest typu double
			__THROW__( TlinsAstroBase :: tlinsUIException( TlinsAstroBase :: tlinsUIException :: ERROR_INVALID_PARAMETER, "type must be equal \"horisontal\" or \"vertical\"" ) );
		}

		if( v.toString().toUpper() == "HORISONTAL" )
			axis = Axis :: H;
		else
			axis = Axis :: V;
	}

	//long valueSteps;
	//double valueDegris;

	{
		if( type == Type :: STEPS )
		{
			QJsonValue v = doc[QString("value-steps")];
			if( !v.isDouble() )
			{
				// Przekazana wartosc nie jest typu double
				__THROW__( TlinsAstroBase :: tlinsUIException( TlinsAstroBase :: tlinsUIException :: ERROR_INVALID_PARAMETER, "Parameter value is not double" ) );
			}
			valueSteps = static_cast<long>( v.toDouble() );
		}
		else
		{
			QJsonValue v = doc[QString("value-degris")];
			if( !v.isDouble() )
			{
				// Przekazana wartosc nie jest typu double
				__THROW__( TlinsAstroBase :: tlinsUIException( TlinsAstroBase :: tlinsUIException :: ERROR_INVALID_PARAMETER, "Parameter value is not double" ) );
			}
			valueDegris = static_cast<long>( v.toDouble() );
		}
	}
}

tlinsPluginHorisontalVerticalSpeedDelta :: ~tlinsPluginHorisontalVerticalSpeedDelta()
{
}

//
// -----
//
std :: shared_ptr<tlinsShortCutInterface> tlinsPluginHorisontalVerticalSpeedDeltaFactory :: createInstance( const TlinsAstroBase ::tlinsKeysSortcutType,
                                                                                                            const TlinsAstroBase :: tlinsKeysSortcutSubType,
                                                                                                            const std :: string name,
                                                                                                            const std :: string &cfg,
                                                                                                            const TlinsAstroBase :: tlinsPilotShortcutsDefinitionValidMode,
                                                                                                            const std :: vector<int> &keys_ ) noexcept
{
	return std :: shared_ptr<tlinsShortCutInterface>{ new tlinsPluginHorisontalVerticalSpeedDelta{ name, keys_, cfg } };
}

tlinsPluginHorisontalVerticalSpeedDeltaFactory :: ~tlinsPluginHorisontalVerticalSpeedDeltaFactory()
{
}

//
// Rejestracja fabryki w menagerze
//
static tlinsShortcutsFactoryCreator<tlinsPluginHorisontalVerticalSpeedDeltaFactory> __creator__{"horisontal-vertical-speed-delta"};

};
