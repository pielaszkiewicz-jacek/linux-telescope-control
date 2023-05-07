#include <tlinsAstroEnginConfiguration.hpp>
#include <tlinsAstroEngineExt.hpp>
#include <tlinsBacktrace.hpp>
#include <tlinsLogger.hpp>
#include <tlinsMoveServerInterface.hpp>

#include <grpc++/channel.h>
#include <grpc++/client_context.h>
#include <grpc++/create_channel.h>
#include <grpc++/security/credentials.h>

#include <grpc++/security/server_credentials.h>
#include <grpc++/server.h>
#include <grpc++/server_builder.h>
#include <grpc++/server_context.h>

#include <memory>
#include <unistd.h>

class GrpcServerAstroThread {
  private:
	std::unique_ptr<grpc::Server> server;
	tlinsRpcAstroEngine           rpcAstro;
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
		builder.RegisterService(&rpcAstro);

		server = std::unique_ptr<grpc::Server>{builder.BuildAndStart()};

		// Oczekiwanie na zakonczenie serwera
		server->Wait();
	};

	GrpcServerAstroThread(const std::string &serverAddress_, tlinsAstroEngine &srv)
	    : serverAddress{serverAddress_}, rpcAstro{srv} {};

	virtual ~GrpcServerAstroThread(){};
};

std::string logDir;

std::string mainGetLogDir()
{
	return logDir;
}

void sedLogFile()
{
	struct timeval tv;
	if (::gettimeofday(&tv, nullptr) < 0) {
		return;
	}

	struct tm *tmPtr = localtime(&tv.tv_sec);
	char       fileName[1024];
	sprintf(fileName, "tlinsAstro-%d%0d%0d%0d.log", tmPtr->tm_year + 1900, tmPtr->tm_mon + 1, tmPtr->tm_mday,
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

int main(int argc, char *argv[])
{
	// Parametery loggera
	auto &loggerInstance = tlinsLogger::instance();
	loggerInstance.setLoggerStd();
	loggerInstance.setLogLevel(tlinsLogger::LOG_LEVEL_DEBUG);

	// Sciezka do konfiguracji
	std::string path;

	switch (argc) {
	case 1:
		path   = "./configuration-astro.xml";
		logDir = ".";
		break;

	case 2:
		path   = argv[1];
		logDir = ".";
		break;

	default:
		path   = argv[1];
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
	loggerInstance.logInfo("Jacek Pielaszkiewicz");
	loggerInstance.logInfo("Krasnik 2016/2017");
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

	try {
		// Odczyt konfiguracji
		loggerInstance.logInfo("  -> Configuration file");
		tlinsAstroEnginConfiguration configuration(path);
		configuration.parse();

		// Ustawienie poziomu logowania na podstawie pliku konfiguracyjnego
		loggerInstance.setLogLevel(configuration.logLevel);

		loggerInstance.logInfo("  -> Create communication channels");
		// Konfiguracja kanalow komunikacyjnych
		auto channelReqest =
		    grpc::CreateChannel(configuration.connUrlRequestResponse, grpc::InsecureChannelCredentials());

		auto channelConfirmation =
		    grpc::CreateChannel(configuration.connUrlNotifications, grpc::InsecureChannelCredentials());

		loggerInstance.logInfo("  -> Create Server API service");
		auto rpcService = std::make_shared<tlinsMoveServerInterface>(channelReqest, channelConfirmation);

		// Uruchomienie watku odpowiedzialnego za cykliczny odczyt danych referencyjnych z sieci
		loggerInstance.logInfo("  -> Start thread to read astronomical reference data");
		loggerInstance.logInfo("  -> TODO");

		// Start astroo engine
		loggerInstance.logInfo("  -> Start server");
		tlinsAstroEngine astroEngine(rpcService, configuration);

		// Uruchomienie RPC serwujacego API
		loggerInstance.logInfo("  -> Start API service");
		GrpcServerAstroThread grpcAstro(configuration.connUrlClient, astroEngine);
		std::thread           grpcAstroThread{std::ref(grpcAstro)};
		grpcAstroThread.detach();

		loggerInstance.logInfo("  -> Enter into main loop");
		while (true) {
			::sleep(1);
		}
	}
	catch (tlinsAstroException &exc) {
		// Obsluga bledow
		loggerInstance.logError(exc.getErrorMessage());
		tlinsBacktrace::instance().printStack(tlinsLogger::LOG_LEVEL_DEBUG);
		return 1;
	}
	return 0;
}