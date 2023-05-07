/*
 * tlins_main.cpp
 *
 *  Created on: 18-04-2012
 *      Author: jacek
 */

#include <stdio.h>

#define ___APP___

#include <parameters/tlinsConfigurationParser.hpp>
#include <parameters/tlinsDeviceParametersList.hpp>
#include <parameters/tlinsGlobalParametersList.hpp>
#include <parameters/tlins_parameters.hpp>

#include <tlinsXMLParser.hpp>

#include <soapH.h>
#include <tlinsLogger.hpp>
#include <tlins_main.hpp>

#include <tlinsBacktrace.hpp>

#include <tlinsSerialDevice.hpp>

#include <usdevice/tlinsUSPortGpioMgr.hpp>
#include <usdevice/tlinsUSPulsDeviceRequestInforManager.hpp>
#include <usdevice/tlinsUSPulsThreadRequest.hpp>
#include <usdevice/tlinsUSPulseDeviceControler.hpp>
#include <usdevice/tlinsUSPulseDeviceFileHandler.hpp>
#include <usdevice/tlinsUSPulseDeviceMgr.hpp>
#include <usdevice/tlinsUSUserMoveRequesItem.hpp>

#include <tlinsAsynchronusThreadChannel.hpp>
#include <tlinsMessageHandlerManager.hpp>
#include <tlinsRequestDeviceInfo.hpp>
#include <tlinsRequestMove.hpp>
#include <tlinsRequestPositionInfo.hpp>
#include <tlinsSynchronusThreadChannel.hpp>

#include <iostream>
#include <list>
#include <pthread.h>
#include <queue>
#include <string>
#include <thread>
#include <vector>

using namespace std;

/*
 * ----------------------------------------------------------
 *
 * Zmienne globalne
 *
 * ----------------------------------------------------------
 */

/*
 * Soap
 */
static struct soap tlinSoap;


/*
 * Watek realizujacy komunikacje za posrednictwem WebService
 */

/*
 * ---------------------------------------------------------------------------------
 *
 * Zestaw funkcji do obslugi SOAP
 *
 * ---------------------------------------------------------------------------------
 */

static std::string tlinsClientUrlInternal(TLINS_PARA_VAL_SYNCH_CLIEN_URL_INTERNAL);
static std::string tlinsSynchClientUrl(TLINS_PARA_VAL_SYNCH_CLIEN_URL);
static std::string tlinsAsynchClientUrl(TLINS_PARA_VAL_ASYNCH_CLIENT_URL);
static int         tlinsSynchClientThreads = TLINS_PARA_VAL_SYNCH_CLIEN_THREADS;

void tlins_zeromqThreadFunction(void *ptr)
{
	// Inicalizacja
	new tlinsSynchronusThreadChannel(tlinsSynchClientUrl, tlinsClientUrlInternal, tlinsSynchClientThreads);
}

// Wskaznik
static std::shared_ptr<std::thread> tlins_zeroMqThread;

void tlins_zeromqInit()
{
	//
	// Parametery ZEROMQ
	//
	std::string value;

	if (tlinsGlobalParametersList::getParameters().getParameterValue(std::string(TLINS_PARA_SYNCH_CLIEN_URL_INTERNAL),
	                                                                 value))
		tlinsClientUrlInternal = value;
	else
		tlinsLogger::logWarning("No " TLINS_PARA_SYNCH_CLIEN_URL_INTERNAL " parameter");

	if (tlinsGlobalParametersList::getParameters().getParameterValue(std::string(TLINS_PARA_SYNCH_CLIEN_URL), value))
		tlinsSynchClientUrl = value;
	else
		tlinsLogger::logWarning("No " TLINS_PARA_SYNCH_CLIEN_URL " parameter");

	if (tlinsGlobalParametersList::getParameters().getParameterValue(std::string(TLINS_PARA_ASYNCH_CLIENT_URL), value))
		tlinsAsynchClientUrl = value;
	else
		tlinsLogger::logWarning("No " TLINS_PARA_ASYNCH_CLIENT_URL " parameter");

	if (tlinsGlobalParametersList::getParameters().getParameterValue(std::string(TLINS_PARA_SYNCH_CLIEN_THREADS),
	                                                                 value))
		sscanf(value.c_str(), "%d", &tlinsSynchClientThreads);
	else
		tlinsLogger::logWarning("No " TLINS_PARA_SYNCH_CLIEN_THREADS " parameter");

	char str[256];

	sprintf(str, "tlinsClientUrlInternal  = %s", tlinsClientUrlInternal.c_str());
	tlinsLogger::logInfo(str);

	sprintf(str, "tlinsSynchClientUrl     = %s", tlinsSynchClientUrl.c_str());
	tlinsLogger::logInfo(str);

	sprintf(str, "tlinsAsynchClientUrl    = %s", tlinsAsynchClientUrl.c_str());
	tlinsLogger::logInfo(str);

	sprintf(str, "tlinsSynchClientThreads = %d", tlinsSynchClientThreads);
	tlinsLogger::logInfo(str);

	//
	// Rejestracja obiektów odpowiedzialnych za przetwarzanie
	//
	// - Rzadanie wykonania przemieszczenia
	tlinsMessageHandlerManager::registerHandler(
	    std::string("REQUEST::CMD:MOVE-REQUEST::1.0"),
	    std::shared_ptr<tlinsMessageHandlerFactory>(new tlinsRequestMoveFactory()));

	// - Informacja o urzadzeniu
	tlinsMessageHandlerManager::registerHandler(
	    std::string("REQUEST::CMD:DEVICE-INFO::1.0"),
	    std::shared_ptr<tlinsMessageHandlerFactory>(new tlinsRequestDeviceInfoFactory()));

	tlinsMessageHandlerManager::registerHandler(
	    std::string("REQUEST::CMD:POSITION-INFO::1.0"),
	    std::shared_ptr<tlinsMessageHandlerFactory>(new tlinsRequestPositionInfoFactory()));

	//
	// Uruchomienie watku odpowiedzialnego za przetwarzanie rzadan
	//
	tlins_zeroMqThread = std::shared_ptr<std::thread>(new std::thread(tlins_zeromqThreadFunction, nullptr));

	//
	// Inicializacja interfejsu powiadomien
	//
	new tlinsAsynchronusThreadChannel(tlinsAsynchClientUrl);
}

void tlins_zeromqStop()
{
}

/*
 * Funkcja watku odpowiedzialna za czytanie urzadzenia z notyfikacjami o
 * zakonczonym przetwarzaniu danego zlecenia przez modul jadra
 */
void tlins_deviceSignalFunction(void *ptr)
{
	// Petla glowna
	while (true) {
		tlinsUSPulsDeviceRequestInforManager::process();
	}
}

/*
 * ---------------------------------------------------------------------------------
 *
 * Funkcja main
 *
 * ---------------------------------------------------------------------------------
 */
int main(int argc, char *argv[])
{
	tlinsLogger::setLoggerStd();
	tlinsLogger::setLogLevel(tlinsLogger::LOG_LEVEL_DEBUG);

	tlinsLogger::logInfo("");
	tlinsLogger::logInfo("-------------------------------------------------------------");
	tlinsLogger::logInfo("");
	tlinsLogger::logInfo("Jacek Pielaszkiewicz");
	tlinsLogger::logInfo("Krasnik 2016");
	tlinsLogger::logInfo("");
	tlinsLogger::logInfo("-------------------------------------------------------------");
	tlinsLogger::logInfo("");

	// Domysla lokalizacja pliku konfiguracyjnego
	std::string fName;

	if (argc > 1) {
		fName = argv[1];
	} else {
		fName = "./configuration.xml";
	}

	try {
		tlinsLogger::logInfo("  -> Configuration file");
		tlinsConfigurationParser::parse(fName);

		tlinsLogger::logInfo("  -> Devices configuration");
		tlinsSerialDeviceManager::createDevices();
	}
	catch (tlinsParametersException &exc) {
		tlinsLogger::logError(exc.getErrorMessage());
		tlinsBacktrace::printStack(tlinsLogger::LOG_LEVEL_DEBUG);
	}
	catch (tlinsSerialDeviceException &exc) {
		tlinsLogger::logError(exc.getErrorMessage());
		tlinsBacktrace::printStack(tlinsLogger::LOG_LEVEL_DEBUG);
	}
	//
	// Pobranie urzadzenia glownego
	//

	tlinsLogger::logError(
	    "-------------------------------------------------------------------------------------------");
	tlinsLogger::logError(
	    "-------------------------------------------------------------------------------------------");

	auto iter = tlinsSerialDeviceManager::find("main");
	if (iter == tlinsSerialDeviceManager::end()) {
		tlinsLogger::logError("Nie ma urzadzenia main");
	}

	tlinsLogger::logError(
	    "-------------------------------------------------------------------------------------------");
	tlinsLogger::logError(
	    "-------------------------------------------------------------------------------------------");


	//
	// Interfejs oparty o ZEROMQ oraz PROTBUFFERS
	//
	tlinsLogger::logInfo("ZEROMQ based interface starting");
	tlins_zeromqInit();

	//
	// Petla glowna
	//
	tlinsLogger::logInfo("Service has started");
	while (true) {
		sleep(1);
	}

	//
	// Oczekiwanie na zakonczenie watku
	//
	tlins_zeromqStop();

	return 0;
}
