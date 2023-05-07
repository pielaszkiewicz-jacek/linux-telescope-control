#include "tlinspluginclosevelocitymeasurment.h"

#include <tlinsAstroEngineInterface.hpp>
#include <tlinscommunicationthread.h>
#include <tlinsastrobaseutils.h>
#include <tlinspluginsstate.h>
#include <tlinsuiexception.h>
#include <tlinsastrouibase.h>
#include <tlinsBacktrace.hpp>
#include "tlinspluginsstate.h"
#include <tlinsconfiguration.h>
#include <tlinsserverstatusinfo.h>
#include <tlinsastrobaseutils.h>

#include <QDebug>

class tlinsPluginCloseVelocityMeasurmentRequest : public TlinsAstroBase :: tlinsCommunicationThreadRequest
{
private:
	std :: shared_ptr<TlinsAstroBase :: tlinsConnectionContext> connection;

public:
	void confirm();

	virtual void operator()() noexcept;
	virtual bool isAsynchronuus();
    virtual std :: string name()
    {
        // TODO
        return "";
    }

	tlinsPluginCloseVelocityMeasurmentRequest();
	virtual ~tlinsPluginCloseVelocityMeasurmentRequest();
};

void tlinsPluginCloseVelocityMeasurmentRequest :: confirm()
{
	TlinsAstroBase :: tlinsCommunicationThreadRequest :: confirm();
}

void tlinsPluginCloseVelocityMeasurmentRequest :: operator()() noexcept
{
	try
	{
		// Zamkniecie kalibracji
//		connection -> getAstro() -> closeVelocityMeserment();
		qDebug() << "Calibrarion has been closed";
	}
	catch( const tlinsInterfaceException & )
	{
		// Mamy blad wywolania nie bedzie potwierdzenia asynchronicznego
		qDebug() << "Error close calibration";
	}
}

bool tlinsPluginCloseVelocityMeasurmentRequest :: isAsynchronuus()
{
	return alse );
}

tlinsPluginCloseVelocityMeasurmentRequest :: tlinsPluginCloseVelocityMeasurmentRequest()
{
	// Pobranie polaczenia
	if( !TlinsAstroBase :: tlinsConnectionsManager :: getInstance().hasConnection( QString{ TLINS_CONNECTION_DEFAULT } ) )
		__THROW__( tlinsException( std :: string( "No active connection: " ) + std :: string( TLINS_CONNECTION_DEFAULT ), -1 ) );

	// Polaczenie
	connection = TlinsAstroBase :: tlinsConnectionsManager :: getInstance().getConnection( TLINS_CONNECTION_DEFAULT );
}

tlinsPluginCloseVelocityMeasurmentRequest :: ~tlinsPluginCloseVelocityMeasurmentRequest()
{
	connection.reset();
}

// -------------------------------------
void tlinsPluginCloseVelocityMeasurment :: callback(int, int, int)
{
}

void tlinsPluginCloseVelocityMeasurment :: callback()
{
	try
	{
		auto ptr = new tlinsPluginCloseVelocityMeasurmentRequest{};
		std :: unique_ptr<TlinsAstroBase :: tlinsCommunicationThreadRequest> req( ptr );
		TlinsAstroBase :: tlinsCommunicationThread :: getInstance().push( req );
	}
	catch( tlinsInterfaceException & )
	{
		qDebug() << "Error close calibration";
	}
}

void tlinsPluginCloseVelocityMeasurment :: release()
{
}

tlinsPluginCloseVelocityMeasurment :: tlinsPluginCloseVelocityMeasurment( const std :: string &name_,
                                                                          const std :: vector<int> &keys_,
                                                                          const std :: string &cfg_ ) : name{ name_ },
                                                                                                        keys{ keys_ },
                                                                                                        cfg{ cfg_ }
{
}

tlinsPluginCloseVelocityMeasurment :: ~tlinsPluginCloseVelocityMeasurment()
{
}

//
// -----
//
std :: shared_ptr<tlinsShortCutInterface> tlinsPluginCloseVelocityMeasurmentFactory :: createInstance( const TlinsAstroBase ::tlinsKeysSortcutType,
                                                                                                       const TlinsAstroBase :: tlinsKeysSortcutSubType,
                                                                                                       const std :: string name,
                                                                                                       const std :: string &cfg,
                                                                                                       const TlinsAstroBase :: tlinsPilotShortcutsDefinitionValidMode,
                                                                                                       const std :: vector<int> &keys_ ) noexcept
{
	return std :: shared_ptr<tlinsShortCutInterface>{ new tlinsPluginCloseVelocityMeasurment{ name, keys_, cfg } };
}

tlinsPluginCloseVelocityMeasurmentFactory :: ~tlinsPluginCloseVelocityMeasurmentFactory()
{
}

//
// Rejestracja fabryki w menagerze
//
static tlinsShortcutsFactoryCreator<tlinsPluginCloseVelocityMeasurmentFactory> __creator__{ "close-velocity-measurment" };

