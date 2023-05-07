/*
 * tlins_main.cpp
 *
 *  Created on: 18-04-2012
 *      Author: jacek
 */
#include <parameters/tlinsConfigurationParser.hpp>
#include <parameters/tlinsDeviceParametersList.hpp>
#include <parameters/tlinsGlobalParametersList.hpp>
#include <parameters/tlins_parameters.hpp>
#include <sdevice/tlinsSerialServer.hpp>
#include <tlinsBacktrace.hpp>
#include <tlinsLogger.hpp>
#include <tlinsSerialDevice.hpp>
#include <tlinsXMLParser.hpp>
#include <tlins_main.hpp>

#include <algorithm>
#include <iostream>
#include <list>
#include <memory>
#include <pthread.h>
#include <queue>
#include <string>
#include <thread>
#include <vector>

#include <stdio.h>

#include <stdlib.h>
#include <time.h>

//
// ++++
//

#include <grpc++/security/server_credentials.h>
#include <grpc++/server.h>
#include <grpc++/server_builder.h>
#include <grpc++/server_context.h>
#include <grpc/grpc.h>

/*
 * ---------------------------------------------------------------------------------
 * Podlaczenie sie do zdefiniowanych urzadzen
 * ---------------------------------------------------------------------------------
 */
void connectDevices()
{
	auto &loggerInstance = tlinsLogger::instance();

	// Przejscie po urzadzeniach glownych
	auto &instance = tlinsSerialDeviceManager::getInstance();

	for (auto i = instance.begin(); i != instance.end(); i++) {
		loggerInstance.logInfo("     Connect to .......... " + i->first);

		// Pobranie urzadzenia
		auto &dev = i->second;

		// Polaczenie z urzdzeniem
		dev->setupConnection();

		// Srukowanie urzadzen skladowych
		for (auto &devIter : *dev) {
			devIter.first;
			loggerInstance.logInfo("         Sub device .......... " + i->first);
		}
	}
}

/*
 * ---------------------------------------------------------------------------------
 *
 * Inicializacja serwera GRPC
 *
 * ---------------------------------------------------------------------------------
 */
static std::mutex mainMtx;
static bool       _endMainLoop_ = false;

/*
 * ---------------------------------------------------------------------------------
 *
 * Watki realizujace polaczenie GRPC
 *
 * ---------------------------------------------------------------------------------
 */


class GrpcServerConfirmationThread {
  private:
	std::unique_ptr<grpc::Server> server;
	tlinsRpcConfirmationServer    rpc;
	grpc::ServerBuilder           builder;
	std::string                   serverAddress;

  public:
	void stop()
	{
		server->Shutdown();
	}

	void operator()()
	{
		builder.AddListeningPort(serverAddress, grpc::InsecureServerCredentials());

		// Register service
		builder.RegisterService(&rpc);
		server = std::unique_ptr<grpc::Server>{builder.BuildAndStart()};

		// Oczekiwanie na zakonczenie serwera
		server->Wait();
	};

	GrpcServerConfirmationThread(const std::string &serverAddress_) : serverAddress{serverAddress_} {};

	virtual ~GrpcServerConfirmationThread(){};
};

class GrpcServerMoveRequestThread {
  private:
	std::unique_ptr<grpc::Server> server;
	tlinsRpcMoveControlServer     rpcMove;
	grpc::ServerBuilder           builder;
	std::string                   serverAddress;

  public:
	void stop()
	{
		server->Shutdown();
	}

	void operator()()
	{
		builder.AddListeningPort(serverAddress, grpc::InsecureServerCredentials());

		// Register service
		builder.RegisterService(&rpcMove);
		server = std::unique_ptr<grpc::Server>{builder.BuildAndStart()};

		// Oczekiwanie na zakonczenie serwera
		server->Wait();
	};

	GrpcServerMoveRequestThread(const std::string &serverAddress_, tlinsSerialServer &srv)
	    : serverAddress{serverAddress_}, rpcMove{srv} {};

	virtual ~GrpcServerMoveRequestThread(){};
};

/*
 * ---------------------------------------------------------------------------------
 *
 * Funkcja main
 *
 * ---------------------------------------------------------------------------------
 */

std::string logDir;

void sedLogFile()
{
	struct timeval tv;
	if (::gettimeofday(&tv, nullptr) < 0) {
		return;
	}

	struct tm *tmPtr = localtime(&tv.tv_sec);
	char       fileName[1024];
	sprintf(fileName, "tlins-%d%0d%0d%0d.log", tmPtr->tm_year + 1900, tmPtr->tm_mon + 1, tmPtr->tm_mday,
	        tmPtr->tm_hour);

	std::string filePath{logDir};
	filePath += "/";
	filePath += fileName;

	try {
		tlinsLogger::instance().logInfo(filePath);
		// Ustawienie pliku
		tlinsLogger::instance().setLogger(filePath);
	}
	catch (...) {
		// Ustawienie standardowego wyjscia
		try {
			tlinsLogger::instance().setLoggerStd();
		}
		catch (...) {
		}
	}
}

//
// Tworzenie instancji synchronicznego serwera
//
int main(int argc, char *argv[])
{
	tlinsSerialServer server;

	auto &loggerInstance = tlinsLogger::instance();
	loggerInstance.setLoggerStd();
	loggerInstance.setLogLevel(tlinsLogger::LOG_LEVEL_DEBUG);

	// 1. Okreslenie pliku konfiguracyjnego
	std::string fName;

	switch (argc) {
	case 1:
		fName  = "./configuration.xml";
		logDir = ".";
		break;

	case 2:
		fName  = argv[1];
		logDir = ".";
		break;

	default:
		fName  = argv[1];
		logDir = argv[2];
		break;
	}

	//
	// -- Ustawienie pliku logu
	//
	sedLogFile();

	loggerInstance.logInfo("");
	loggerInstance.logInfo("-------------------------------------------------------------");
	loggerInstance.logInfo("");
	loggerInstance.logInfo("Motors controler");
	loggerInstance.logInfo("");
	loggerInstance.logInfo("Jacek Pielaszkiewicz");
	loggerInstance.logInfo("Krasnik 2020");
	loggerInstance.logInfo("");
	loggerInstance.logInfo("-------------------------------------------------------------");
	loggerInstance.logInfo("");

	//
	// Watek odpowiedzialny za rotowanie logow
	//
	auto loggerFun = []() {
		while (true) {
			std::this_thread::sleep_for(std::chrono::seconds(60));

			// Testowe w celu ulatwienia wylaczenia klienta generowane raz na sekunde
			sedLogFile();
		}
	};
	std::thread logHandler{loggerFun};

	loggerInstance.logInfo("  -> Configuration file: " + fName);
	auto &devMgrInstance = tlinsSerialDeviceManager::getInstance();

	try {
		loggerInstance.logInfo("  -> Configuration file");
		tlinsConfigurationParser::parse(fName);

		loggerInstance.logInfo("  -> Devices configuration");
		devMgrInstance.createDevices();

		loggerInstance.logInfo("  -> Configure external communication");
		loggerInstance.logInfo("     TODO");

		loggerInstance.logInfo("  -> Connect to devices over serial");
		connectDevices();

		loggerInstance.logInfo("  -> Apply configuration into devices");
		std::for_each(devMgrInstance.begin(), devMgrInstance.end(),
		              [&](const std::pair<std::string, std::shared_ptr<tlinsSerialMainDevice>> &item) {
			              item.second->applayDefaultConfiguration();
		              });

		loggerInstance.logInfo("  -> Create device threads");
		std::for_each(devMgrInstance.begin(), devMgrInstance.end(),
		              [&](const std::pair<std::string, std::shared_ptr<tlinsSerialMainDevice>> &item) {
			              loggerInstance.logInfo("     Device for .... " + item.first);
			              server.registerDevice(item.first, item.second);
		              });

		loggerInstance.logInfo("  -> Create limits threads");
		std::for_each(devMgrInstance.begin(), devMgrInstance.end(),
		              [&](const std::pair<std::string, std::shared_ptr<tlinsSerialMainDevice>> &item) {
			              loggerInstance.logInfo("     Limit for .... " + item.first);
			              server.registerDeviceLimit(item.first, item.second);
		              });
	}
	catch (tlinsParametersException &exc) {
		loggerInstance.logError(exc.getErrorMessage());
		tlinsBacktrace::instance().printStack(tlinsLogger::LOG_LEVEL_DEBUG);
	}
	catch (tlinsSerialDeviceException &exc) {
		loggerInstance.logError(exc.getErrorMessage());
		tlinsBacktrace::instance().printStack(tlinsLogger::LOG_LEVEL_DEBUG);
	}

	loggerInstance.logDebug(
	    "-------------------------------------------------------------------------------------------");
	loggerInstance.logDebug("   Start server   ");
	loggerInstance.logDebug(
	    "-------------------------------------------------------------------------------------------");

	// Adresy serverow
	std::string rpcUrl{"0.0.0.0:30000"};
	std::string rpcUrlAsynch{"0.0.0.0:30001"};
	tlinsGlobalParametersList::getParameters().getParameterValue("url", rpcUrl);
	tlinsGlobalParametersList::getParameters().getParameterValue("urlAsynchronus", rpcUrlAsynch);

	// Watek odpowiedzialny za potwierdzenia
	GrpcServerConfirmationThread grpcConfirmation{rpcUrlAsynch};

	// Move requests thread
	GrpcServerMoveRequestThread grpcMoveRequest{rpcUrl, server};

	loggerInstance.logInfo("Start GRPC confirmation thread.");
	std::thread grpcConfirmationThread{std::ref(grpcConfirmation)};

	loggerInstance.logInfo("Start GRPC main thread.");
	std::thread grpcMoveRequestsThread{std::ref(grpcMoveRequest)};

	loggerInstance.logInfo("Detach confirmation and main rpc threads.");
	grpcConfirmationThread.detach();
	grpcMoveRequestsThread.detach();

	// Petla glowna
	loggerInstance.logInfo("Enter into main loop.");
	while (true) {
		::sleep(1);
	}

	loggerInstance.logInfo("Stop main devices");
	for (auto i = devMgrInstance.begin(); i != devMgrInstance.end(); i++) {
		i->second.reset();
	}

	loggerInstance.logInfo("Service has ended");
	return 0;
}
