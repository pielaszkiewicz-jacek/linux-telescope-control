#include "tlinspluginradcdelta.h"

#include "tlinspluginsstate.h"
#include <tlinsuiexception.h>
#include <tlinsBacktrace.hpp>
#include <QJsonDocument>
#include <QDebug>

#include <math.h>

namespace tlinsAstroPilot
{

void tlinsPluginRaDcDelta :: set()
{
    if( axis == Axis :: RA )
    {
        // RA
        tlinsPluginsState :: getInstance().setRaDelta( raValue );
        qDebug() << "Update RA delta. New value : " << tlinsPluginsState :: getInstance().getRaDelta();
    }
    else
    {
        // DC
        tlinsPluginsState :: getInstance().setDcDelta( dcValue );
        qDebug() << "Update DC delta. New value : " << tlinsPluginsState :: getInstance().getDcDelta();
    }
}

//
// --- Joystick
//
void tlinsPluginRaDcDelta :: callback(const std::list<TlinsAstroBase :: tlinsJoystick :: keyStatusInfo> &, const TlinsAstroBase :: tlinsJoystick :: keyStatusInfo &)
{
    set();
}

void tlinsPluginRaDcDelta :: callbackRel(const std::list<TlinsAstroBase :: tlinsJoystick :: keyStatusInfo> &, const TlinsAstroBase :: tlinsJoystick :: keyStatusInfo &)
{
}

//
// --- Keyboard
//
void tlinsPluginRaDcDelta :: callback()
{
    set();
}

void tlinsPluginRaDcDelta :: release()
{
}


tlinsPluginRaDcDelta :: tlinsPluginRaDcDelta( const std :: string &name_,
                                              const std :: vector<int> &keys_,
                                              const std :: string &cfg_ ) : name{ name_ },
                                                                            keys{ keys_ },
                                                                            cfg{ cfg_ }
{
	//
	// Odczyt konfiguracji z jsona
	//
	QJsonDocument doc = QJsonDocument :: fromJson( QString :: fromStdString( cfg ).toUtf8() );

	QJsonValue v = doc[QString("axis")];
	if( !v.isString() )
	{
		// Przekazana wartosc nie jest typu double
		__THROW__( TlinsAstroBase :: tlinsUIException( TlinsAstroBase :: tlinsUIException :: ERROR_INVALID_PARAMETER, "Parameter value is not a string" ) );
	}

	if( v.toString().toUpper() == "RA" )
	{
		// Os RA
		{
			QJsonValue v = doc[QString("value-ra")];
			if( !v.isDouble() )
			{
				// Przekazana wartosc nie jest typu double
				__THROW__( TlinsAstroBase :: tlinsUIException( TlinsAstroBase :: tlinsUIException :: ERROR_INVALID_PARAMETER, "Parameter value is not a string" ) );
			}
			raValue = :: fabs( v.toDouble() );
            if(raValue > 24.0)
                raValue = 24.0;
		}

		{
			QJsonValue v = doc[QString("negative-ra")];
			if( !v.isBool() )
			{
				// Przekazana wartosc nie jest typu double
				__THROW__( TlinsAstroBase :: tlinsUIException( TlinsAstroBase :: tlinsUIException :: ERROR_INVALID_PARAMETER, "Parameter value is not a bool" ) );
			}

			if( v.toBool() )
			{
				// Ujemna wartosc
				raValue *= -1;
			}
		}
	}
	else
	{
		// Os DC
		{
			QJsonValue v = doc[QString("value-dc")];
			if( !v.isDouble() )
			{
				// Przekazana wartosc nie jest typu double
				__THROW__( TlinsAstroBase :: tlinsUIException( TlinsAstroBase :: tlinsUIException :: ERROR_INVALID_PARAMETER, "Parameter value is not a string" ) );
			}
			dcValue = :: fabs( v.toDouble() );

            if(dcValue < -90.0) dcValue = -90.0;
            if(dcValue >  90.0) dcValue =  90.0;
		}
	}
}

tlinsPluginRaDcDelta :: ~tlinsPluginRaDcDelta()
{
}

//
// -----
//
std :: shared_ptr<tlinsShortCutInterface> tlinsPluginRaDcDeltaFactory :: createInstance( const TlinsAstroBase ::tlinsKeysSortcutType,
                                                                                         const TlinsAstroBase :: tlinsKeysSortcutSubType,
                                                                                         const std :: string name,
                                                                                         const std :: string &cfg,
                                                                                         const TlinsAstroBase :: tlinsPilotShortcutsDefinitionValidMode,
                                                                                         const std :: vector<int> &keys_ ) noexcept
{
	return std :: shared_ptr<tlinsShortCutInterface>{ new tlinsPluginRaDcDelta{ name, keys_, cfg } };
}

tlinsPluginRaDcDeltaFactory :: ~tlinsPluginRaDcDeltaFactory()
{
}

//
// Rejestracja fabryki w menagerze
//
static tlinsShortcutsFactoryCreator<tlinsPluginRaDcDeltaFactory> __creator__{"hour-amgle-declination-delta"};

};
