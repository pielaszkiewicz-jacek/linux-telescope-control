#include <QCoreApplication>
#include "tlinskeyboardeventhandler.h"
#include "tlinsjoystickeventhandler.h"
#include <tlinsconfiguration.h>
#include <QtDebug>

#include <grpc/grpc.h>
#include <grpc++/channel.h>
#include <grpc++/client_context.h>
#include <grpc++/create_channel.h>
#include <grpc++/security/credentials.h>

#include <tlinsBacktrace.hpp>
#include <tlinsconnection.h>
#include <tlinsserverstatusinfo.h>

//
// Funkcja iniciaslizuje polaczenie z  serwerem przemieszczenia i astro serwerem.
//
void connectMoveAndAstroService()
{
	//
	// Odczyt konfiguracji
	//

    auto &loggerInstance = tlinsLogger::instance();

    loggerInstance.setLoggerStd();
    loggerInstance.setLogLevel(tlinsLogger::LOG_LEVEL_DEBUG);

	auto &cfgInstance = TlinsAstroBase :: tlinsConfiguration :: getInstance();

	std :: string urlDev      = "localhost:20001";
	std :: string urlDevAsync = "localhost:20003";
	std :: string urlAstro    = "localhost:20000";

	if( cfgInstance.hasKey( TlinsAstroBase :: tlinsConfiguration :: CONNECTION_PARAMETER_GROUP,
	                        TlinsAstroBase :: tlinsConfiguration :: CONNECTION_PARAMETER_URL_DEVICE_ENGINE ) )
	{
		urlDev = cfgInstance.getString( TlinsAstroBase :: tlinsConfiguration :: CONNECTION_PARAMETER_GROUP,
		                                TlinsAstroBase :: tlinsConfiguration :: CONNECTION_PARAMETER_URL_DEVICE_ENGINE ).toStdString();
	}

	if( cfgInstance.hasKey( TlinsAstroBase :: tlinsConfiguration :: CONNECTION_PARAMETER_GROUP,
	                        TlinsAstroBase :: tlinsConfiguration :: CONNECTION_PARAMETER_URL_DEVICE_ENGINE_ASYNCH ) )
	{
		urlDevAsync = cfgInstance.getString( TlinsAstroBase :: tlinsConfiguration :: CONNECTION_PARAMETER_GROUP,
		                                     TlinsAstroBase :: tlinsConfiguration :: CONNECTION_PARAMETER_URL_DEVICE_ENGINE_ASYNCH ).toStdString();
	}

	if( cfgInstance.hasKey( TlinsAstroBase :: tlinsConfiguration :: CONNECTION_PARAMETER_GROUP,
	                        TlinsAstroBase :: tlinsConfiguration :: CONNECTION_PARAMETER_URL_ASTRO_ENGINE ) )
	{
		urlAstro = cfgInstance.getString( TlinsAstroBase :: tlinsConfiguration :: CONNECTION_PARAMETER_GROUP,
		                                  TlinsAstroBase :: tlinsConfiguration :: CONNECTION_PARAMETER_URL_ASTRO_ENGINE ).toStdString();
	}

	auto &mgr = TlinsAstroBase :: tlinsConnectionsManager :: getInstance();

	mgr.setConnection( QString{ TLINS_CONNECTION_DEFAULT },
	                   urlDev.c_str(),
	                   urlDevAsync.c_str(),
	                   urlAstro.c_str() );

	//
	// Pobranie statusu kontrolera osi
	//
	auto &statusInfo = TlinsAstroBase :: tlinsServerStatusInfo :: getInstance();
    // TODO
    // TODO
	statusInfo.update();
	// TODO
    // TODOsqssdffsswss
}

std ::shared_ptr<grpc ::Channel> connectService()
{
	auto &inst = TlinsAstroBase :: tlinsConfiguration :: getInstance();
	auto hasKey = inst.hasKey( TlinsAstroBase ::tlinsConfiguration ::CONNECTION_PARAMETER_GROUP,
	                           TlinsAstroBase ::tlinsConfiguration ::CONNECTION_PARAMETER_URL_SYSTEM_SERVICE );

	// Sopmyslny url
	QString url{ "localhost:20100" };
	if( hasKey )
	{
		url = inst.getString( TlinsAstroBase ::tlinsConfiguration ::CONNECTION_PARAMETER_GROUP,
		                      TlinsAstroBase ::tlinsConfiguration ::CONNECTION_PARAMETER_URL_SYSTEM_SERVICE );

		url = inst.getString( TlinsAstroBase ::tlinsConfiguration ::CONNECTION_PARAMETER_GROUP,
		                      TlinsAstroBase ::tlinsConfiguration ::CONNECTION_PARAMETER_URL_SYSTEM_SERVICE );
	}
	qDebug() << "URL: " << url;

	auto cred = grpc :: InsecureChannelCredentials();
	return  grpc :: CreateChannel( url.toStdString().c_str(), cred );
}


int main(int argc, char *argv[])
{
	QCoreApplication a(argc, argv);

	// Kanal ko
	std ::shared_ptr<grpc ::Channel> systemServiceChannel;

	// Laczenie do uslugi nasluchujacej zdarzen systemowych
	systemServiceChannel = connectService();

	// Podlaczenie sie do pozostalych usług
	connectMoveAndAstroService();

	// Utworzenie obiektu przetwarzajkacego zdarzenia
    tlinsKeyboardEventHandler lisenerKeyboard( systemServiceChannel );

    // Utworzenie obiektu przetwarzajkacego zdarzenia
    tlinsJoystickEventHandler lisenerJoystick( systemServiceChannel );

	return a.exec();
}
