#include <tlinsAstroEngineInterface.hpp>
#include "tlinspluginradcincrement.h"
#include <tlinsastrobaseutils.h>
#include <tlinspluginsstate.h>
#include <tlinsuiexception.h>
#include <tlinsastrouibase.h>
#include <tlinsBacktrace.hpp>
#include <tlinsserverstatusinfo.h>
#include <tlinsconfiguration.h>

#include <QJsonDocument>

namespace tlinsAstroPilot
{

class tlinsPluginRaDcIncrementMoveRequest : public TlinsAstroBase :: tlinsCommunicationThreadRequest
{
private:
	class moveCb : public tlinsMoveServerInterface :: tlinsMoveRequestConfirmation
	{
	public:
		void process(const tlins :: tlinsRpcConfirmationStatus &)
		{
		}

		bool release()
		{
            return false;
		}

		moveCb()
		{
			// Nicx nie robimy
		}

		virtual ~moveCb()
		{
		}
	};

	std :: shared_ptr<tlinsMoveServerInterface :: tlinsMoveRequestConfirmation> callback;
	std :: shared_ptr<TlinsAstroBase :: tlinsConnectionContext> connection;

	// Kireunek przemieszczenia
	tlinsPluginRaDcIncrement :: DIRECTION direction;
	tlinsPluginRaDcIncrement :: AXIS      axis;

public:
	virtual void operator()() noexcept;
	virtual bool isAsynchronuus();
    virtual std :: string name()
    {
        // TODO
        return "";
    }

	tlinsPluginRaDcIncrementMoveRequest( const tlinsPluginRaDcIncrement :: DIRECTION dir,
	                                     const tlinsPluginRaDcIncrement :: AXIS a );
	virtual ~tlinsPluginRaDcIncrementMoveRequest();
};

void tlinsPluginRaDcIncrementMoveRequest :: operator()() noexcept
{
	try
	{
		tlinsAstroEngineInterface :: tlinsEngineStateInfo response;

		// 1. Odczyt aktualnej informacji o stanie kontrolera ASTRO
		//    Odczyt jest nie spojny - nie wymuszamy zatrzymania silnika Astro.
		connection -> getAstro() ->	getState( response, false );

		if( response.get_state() != tlinsAstroEngineInterface :: tlinsEngineStateValue ::STATE_REGULAR )
		{
			// Urzadzenie nie jest w trakcie kalibracji
			return;
		}

		// Pobranie informacji o biezacym celu
		auto &target = response.get_currentTarget();
		auto &object = target.get_object();

		auto &ra = object.get_hourAngle();
		double vRa{ static_cast<double>(ra.get_degris()) +
			        static_cast<double>(ra.get_minutes()) / 60.0 +
			        static_cast<double>(ra.get_seconds()) / 3600.0 };
		if(ra.get_sign())
			vRa *= -1;

		auto &dc = object.get_declination();
		double vDc{ static_cast<double>(dc.get_degris()) +
			        static_cast<double>(dc.get_minutes()) / 60.0 +
			        static_cast<double>(dc.get_seconds()) / 3600.0 };
		if(dc.get_sign())
			vDc *= -1;

		// Pobranie aktualnej wartosci kroku
		auto &plugState = tlinsPluginsState ::getInstance();

		if( axis == tlinsPluginRaDcIncrement :: AXIS :: RA )
		{
			// RA
			auto raDelta = plugState.getRaDelta();
			switch(direction)
			{
			case tlinsPluginRaDcIncrement :: DIRECTION :: LEFT:
				vRa -= raDelta;
				break;

			case tlinsPluginRaDcIncrement :: DIRECTION :: RIGHT:
				vRa += raDelta;
				break;
			}
            while(vRa < 0.0)   vRa += 24.0;
            while(vRa >= 24.0) vRa -= 24.0;
		}
		else
		{
			// DC
			auto dcDelta = plugState.getDcDelta();
			switch(direction)
			{
			case tlinsPluginRaDcIncrement :: DIRECTION :: LEFT:
				vDc += dcDelta;
				if( vDc > 90.0 )
				{
					vDc =  180.0 - vDc;
					vRa += 12.0;
				}
				break;

			case tlinsPluginRaDcIncrement :: DIRECTION :: RIGHT:
				vDc -= dcDelta;
				if( vDc < -90.0 )
				{
					vDc = -180.0 - vDc;
					vRa += 12.0;
				}
				break;
			}

            while(vDc > 90.0)  vDc -= 90.0;
            while(vDc < -90.0) vDc += 90.0;
		}

		while( vRa < 0.0 )
			vRa += 24.0;

		while( vRa >= 24.0 )
			vRa -= 24.0;

		int ra_h;
		int ra_m;
		double ra_s;
		bool ra_sign;
		TlinsAstroBase :: tlinsAstroBaseUtils :: splitRA( vRa, ra_h, ra_m, ra_s, ra_sign );
		tlinsAstroEngineInterface :: tlinsCoordinate hourAngle;
		hourAngle.set_degris( ra_h );
		hourAngle.set_minutes( ra_m );
		hourAngle.set_seconds( ra_s );
		hourAngle.set_sign( ra_sign );

		int dc_d;
		int dc_m;
		double dc_s;
		bool dc_sign;
		TlinsAstroBase :: tlinsAstroBaseUtils :: splitDegris( vDc, dc_d, dc_m, dc_s, dc_sign );
		tlinsAstroEngineInterface :: tlinsCoordinate declination;
		declination.set_degris( dc_d );
		declination.set_minutes( dc_m );
		declination.set_seconds( dc_s );
		declination.set_sign( dc_sign );

		// Mamy nowy cel generujemy nowe rzadan
		tlinsAstroEngineInterface :: tlinsTarget request;

		request.set_delta( 0 );

		// Predkosc i przyspieszenie
		auto &cfg = TlinsAstroBase :: tlinsConfiguration :: getInstance();
		if( axis == tlinsPluginRaDcIncrement :: AXIS :: RA )
		{
			auto AxD = cfg.getDouble( TlinsAstroBase :: tlinsConfiguration :: RAMP_PARAMETER_GROUP, TlinsAstroBase :: tlinsConfiguration :: RAMP_PARAMETER_ASTRO_RA_A );
			request.set_speed( plugState.getRaSpeed() );
			request.set_aceleration( AxD );
		}
		else
		{
			auto AyD = cfg.getDouble( TlinsAstroBase :: tlinsConfiguration :: RAMP_PARAMETER_GROUP, TlinsAstroBase :: tlinsConfiguration :: RAMP_PARAMETER_ASTRO_DC_A );
			request.set_speed( plugState.getDcSpeed() );
			request.set_aceleration( AyD );
		}

		tlinsAstroEngineInterface :: tlinsAstroObject astroObject;
		astroObject.set_properMotionRA( 0.0 );
		astroObject.set_properMotionDC( 0.0 );
		astroObject.set_parallax( 0.0 );
		astroObject.set_radialVelocity( 0.0 );
		astroObject.set_catalogType( std::string{ "" } );

		astroObject.set_hourAngle( hourAngle );
		astroObject.set_declination( declination );

		request.set_object( astroObject );

		// Wyslanie rzadania ustawienia nowego celu
		connection -> getAstro() -> setTarget( request, false );
	}
	catch (...) {
        TLINS_LOG_ERROR( "ERROR set new target" );
	}
}

bool tlinsPluginRaDcIncrementMoveRequest :: isAsynchronuus()
{
	return false;
}

tlinsPluginRaDcIncrementMoveRequest :: tlinsPluginRaDcIncrementMoveRequest( const tlinsPluginRaDcIncrement ::DIRECTION dir,
                                                                            const tlinsPluginRaDcIncrement :: AXIS a ) : direction{ dir },
                                                                                                                         axis{a}
{
	// Pobranie polaczenia
if( !TlinsAstroBase :: tlinsConnectionsManager :: getInstance().hasConnection( std::string{ TLINS_CONNECTION_DEFAULT } ) )
		__THROW__( tlinsException( std :: string( "No active connection: " ) + std :: string( TLINS_CONNECTION_DEFAULT ), -1 ) );

	// Polaczenie
	connection = TlinsAstroBase :: tlinsConnectionsManager :: getInstance().getConnection( TLINS_CONNECTION_DEFAULT );

	// Obiekt potwierdzen
	callback.reset( new moveCb{} );
}

tlinsPluginRaDcIncrementMoveRequest :: ~tlinsPluginRaDcIncrementMoveRequest()
{
}

//
// ----
//

void tlinsPluginRaDcIncrement :: callback(const std::list<TlinsAstroBase :: tlinsJoystick :: keyStatusInfo> &, const TlinsAstroBase :: tlinsJoystick :: keyStatusInfo &)
{
}

void tlinsPluginRaDcIncrement :: callbackRel(const std::list<TlinsAstroBase :: tlinsJoystick :: keyStatusInfo> &, const TlinsAstroBase :: tlinsJoystick :: keyStatusInfo &)
{
}

void tlinsPluginRaDcIncrement :: callback()
{
	try {
		//
		// Weryfikacja stanu w ktorym znajduje sie silnik
		//
		auto &plugState = tlinsPluginsState :: getInstance();

		// Tryb prekosci lub krokow
		bool speedoMode = plugState.getSpeedMode();

		// Stan silnika astro.
		auto &statusInfo = TlinsAstroBase :: tlinsServerStatusInfo :: getInstance();
		auto &calibrationState = statusInfo.getCalibrarionState();
		bool isInAstroState = calibrationState.get_engineState() == tlinsAstroEngineInterface :: tlinsEngineStateValue :: STATE_REGULAR;

		if( !isInAstroState || speedoMode )
		{
			// Wtyczka nie jest uzywana poza rybem astro lub predkosci
			return;
		}

		std :: unique_ptr<TlinsAstroBase :: tlinsCommunicationThreadRequest> req( new tlinsPluginRaDcIncrementMoveRequest{ direction,
		                                                                                                                   axis } );
		TlinsAstroBase :: tlinsCommunicationThread :: getInstance().push( req );
	}
	catch(...)
	{
        TLINS_LOG_ERROR( "ERROR set new target" );
	}
}

void tlinsPluginRaDcIncrement :: release()
{
    TLINS_LOG_DEBUG( "Nic nie robimy" );
}

std :: string tlinsPluginRaDcIncrement :: getName()
{
	return name;
}

const std :: vector<int> &tlinsPluginRaDcIncrement :: getKeys()
{
	return keys;
}

tlinsPluginRaDcIncrement :: tlinsPluginRaDcIncrement( const std :: string &name_,
                                                      const std :: vector<int> &keys_,
                                                      const std :: string &cfg ) : name{name_},
                                                                                   keys{keys_},
                                                                                   cfg{cfg}
{
	QJsonDocument doc = QJsonDocument :: fromJson( QString :: fromStdString( cfg ).toUtf8() );

	{
		QJsonValue v = doc[QString("axis")];
		if( !v.isString() )
		{
			// Przekazana wartosc nie jest typu double
			__THROW__( TlinsAstroBase :: tlinsUIException( TlinsAstroBase :: tlinsUIException :: ERROR_INVALID_PARAMETER, "Parameter value is not string" ) );
		}
		QString val = v.toString();

		if( val.toUpper() != "RA" && val.toUpper() != "DC" )
		{
			__THROW__( TlinsAstroBase :: tlinsUIException( TlinsAstroBase :: tlinsUIException :: ERROR_INVALID_PARAMETER, "Parameter value must be equal left or right" ) );
		}

		if( val.toUpper() == "RA" )
			axis = tlinsPluginRaDcIncrement :: AXIS :: RA;	// W lewo
		else
			axis = tlinsPluginRaDcIncrement :: AXIS :: DC;	// W prawo
	}

	{
		QJsonValue v = doc[QString("direction")];
		if( !v.isString() )
		{
			// Przekazana wartosc nie jest typu double
			__THROW__( TlinsAstroBase :: tlinsUIException( TlinsAstroBase :: tlinsUIException :: ERROR_INVALID_PARAMETER, "Parameter value is not string" ) );
		}
		QString val = v.toString();

		if( val.toUpper() != "LEFT" && val.toUpper() != "RIGHT" )
		{
			__THROW__( TlinsAstroBase :: tlinsUIException( TlinsAstroBase :: tlinsUIException :: ERROR_INVALID_PARAMETER, "Parameter value must be equal left or right" ) );
		}

		if( val.toUpper() == "LEFT" )
			direction = tlinsPluginRaDcIncrement :: DIRECTION :: LEFT;	// W lewo
		else
			direction = tlinsPluginRaDcIncrement :: DIRECTION :: RIGHT;	// W prawo
	}
}

tlinsPluginRaDcIncrement :: ~tlinsPluginRaDcIncrement()
{
}

//
// ----
//

std :: shared_ptr<tlinsShortCutInterface> tlinsPluginRaDcIncrementFactory :: createInstance( const TlinsAstroBase ::tlinsKeysSortcutType,
                                                                                             const TlinsAstroBase :: tlinsKeysSortcutSubType,
                                                                                             const std :: string name,
                                                                                             const std :: string &cfg,
																							 const TlinsAstroBase :: tlinsPilotShortcutsDefinitionValidMode,
                                                                                             const std :: vector<int> &keys ) noexcept
{

	return std :: shared_ptr<tlinsShortCutInterface>{ new tlinsPluginRaDcIncrement{ name, keys, cfg } };
}

tlinsPluginRaDcIncrementFactory :: ~tlinsPluginRaDcIncrementFactory()
{
}

//
// Rejestracja fabryki w menagerze
//
static tlinsShortcutsFactoryCreator<tlinsPluginRaDcIncrementFactory> __creator__{"hour-amgle-declination-move-increment"};

};
