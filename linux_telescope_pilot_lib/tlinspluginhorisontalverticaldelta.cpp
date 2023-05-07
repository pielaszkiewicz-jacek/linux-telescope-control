#include "tlinspluginhorisontalverticaldelta.h"

#include "tlinspluginsstate.h"
#include <tlinsuiexception.h>
#include <tlinsBacktrace.hpp>
#include <QJsonDocument>
#include <QDebug>

namespace tlinsAstroPilot
{

void tlinsPluginHorisontalVerticalDelta :: set()
{
    if( type == Type :: STEPS )
    {
        // Kroki
        if( axis == Axis :: H )
        {
            tlinsPluginsState :: getInstance().setXStepsDelta( valueSteps );	// Poziomo
            qDebug() << "Update HORISONTAL steps delta. New value : " << tlinsPluginsState :: getInstance().getXStepsDelta();
        }
        else
        {
            tlinsPluginsState :: getInstance().setYStepsDelta( valueSteps );	// Pionowo
            qDebug() << "Update VERTICAL steps delta. New value : " << tlinsPluginsState :: getInstance().getYStepsDelta();
        }
    }
    else
    {
        if( axis == Axis :: H )
        {
            tlinsPluginsState :: getInstance().setXDegrisDelta( valueDegris );	// Poziomo
            qDebug() << "Update HORISONTAL delta. New value : " << tlinsPluginsState :: getInstance().getXDegrisDelta();
        }
        else
        {
            tlinsPluginsState :: getInstance().setYDegrisDelta( valueDegris );	// Pionowo
            qDebug() << "Update VERTICAL delta. New value : " << tlinsPluginsState :: getInstance().getYDegrisDelta();
        }
    }
}

//
// --- Joystick
//
void tlinsPluginHorisontalVerticalDelta :: callback(const std::list<TlinsAstroBase :: tlinsJoystick :: keyStatusInfo> &, const TlinsAstroBase :: tlinsJoystick :: keyStatusInfo &)
{
    set();
}

void tlinsPluginHorisontalVerticalDelta :: callbackRel(const std::list<TlinsAstroBase :: tlinsJoystick :: keyStatusInfo> &, const TlinsAstroBase :: tlinsJoystick :: keyStatusInfo &)
{
}

//
// --- Keyboard
//
void tlinsPluginHorisontalVerticalDelta :: callback()
{
    set();
}

void tlinsPluginHorisontalVerticalDelta :: release()
{
	// Nic nie robimy
}

tlinsPluginHorisontalVerticalDelta :: tlinsPluginHorisontalVerticalDelta( const std :: string &name_,
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

tlinsPluginHorisontalVerticalDelta :: ~tlinsPluginHorisontalVerticalDelta()
{
}

//
// -----
//
std :: shared_ptr<tlinsShortCutInterface> tlinsPluginHorisontalVerticalDeltaFactory :: createInstance( const TlinsAstroBase ::tlinsKeysSortcutType,
                                                                                                       const TlinsAstroBase :: tlinsKeysSortcutSubType,
                                                                                                       const std :: string name,
                                                                                                       const std :: string &cfg,
                                                                                                       const TlinsAstroBase :: tlinsPilotShortcutsDefinitionValidMode,
                                                                                                       const std :: vector<int> &keys_ ) noexcept
{
	return std :: shared_ptr<tlinsShortCutInterface>{ new tlinsPluginHorisontalVerticalDelta{ name, keys_, cfg } };
}

tlinsPluginHorisontalVerticalDeltaFactory :: ~tlinsPluginHorisontalVerticalDeltaFactory()
{
}

//
// Rejestracja fabryki w menagerze
//
static tlinsShortcutsFactoryCreator<tlinsPluginHorisontalVerticalDeltaFactory> __creator__{"horisontal-vertical-delta"};

};
