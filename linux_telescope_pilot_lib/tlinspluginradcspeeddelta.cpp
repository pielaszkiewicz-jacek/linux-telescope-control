#include "tlinspluginradcspeeddelta.h"

#include "tlinspluginsstate.h"
#include <tlinsuiexception.h>
#include <tlinsBacktrace.hpp>
#include <QJsonDocument>
#include <QDebug>
#include <math.h>

namespace tlinsAstroPilot
{

void tlinsPluginRaDcSpeedDelta :: set()
{
    if( axis == Axis :: RA )
    {
        // RA
        tlinsPluginsState :: getInstance().setRaSpeed( raValue );
        qDebug() << "Update RA speed delta. New value : " << tlinsPluginsState :: getInstance().getRaSpeed();
    }
    else
    {
        // DC
        tlinsPluginsState :: getInstance().setDcSpeed( dcValue );
        qDebug() << "Update DC speed delta. New value : " << tlinsPluginsState :: getInstance().getDcSpeed();
    }
}

//
// --- Joystick
//
void tlinsPluginRaDcSpeedDelta :: callback(const std::list<TlinsAstroBase :: tlinsJoystick :: keyStatusInfo> &, const TlinsAstroBase :: tlinsJoystick :: keyStatusInfo &)
{
    set();
}

void tlinsPluginRaDcSpeedDelta :: callbackRel(const std::list<TlinsAstroBase :: tlinsJoystick :: keyStatusInfo> &, const TlinsAstroBase :: tlinsJoystick :: keyStatusInfo &)
{
}

//
// --- Keyboard
//
void tlinsPluginRaDcSpeedDelta :: callback()
{
    set();
}

void tlinsPluginRaDcSpeedDelta :: release()
{
}


tlinsPluginRaDcSpeedDelta :: tlinsPluginRaDcSpeedDelta( const std :: string &name_,
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
		}
	}
}

tlinsPluginRaDcSpeedDelta :: ~tlinsPluginRaDcSpeedDelta()
{
}

//
// -----
//
std :: shared_ptr<tlinsShortCutInterface> tlinsPluginRaDcSpeedDeltaFactory :: createInstance( const TlinsAstroBase ::tlinsKeysSortcutType,
                                                                                              const TlinsAstroBase :: tlinsKeysSortcutSubType,
                                                                                              const std :: string name,
                                                                                              const std :: string &cfg,
                                                                                              const TlinsAstroBase :: tlinsPilotShortcutsDefinitionValidMode,
                                                                                              const std :: vector<int> &keys_ ) noexcept
{
	return std :: shared_ptr<tlinsShortCutInterface>{ new tlinsPluginRaDcSpeedDelta{ name, keys_, cfg } };
}

tlinsPluginRaDcSpeedDeltaFactory :: ~tlinsPluginRaDcSpeedDeltaFactory()
{
}

//
// Rejestracja fabryki w menagerze
//
static tlinsShortcutsFactoryCreator<tlinsPluginRaDcSpeedDeltaFactory> __creator__{"hour-amgle-declination-speed-delta"};

};
