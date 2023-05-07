#include "tlinsSystemService.hpp"
#include <tlinsSystemMonitorConfiguration.hpp>

#include <tlinsBacktrace.hpp>
#include <tlinsKeybordMonitor.hpp>
#include <tlinsLogger.hpp>
#include <tlinsMonitorInterface.hpp>
#include <unistd.h>

#include <grpc++/security/server_credentials.h>
#include <grpc++/server.h>
#include <grpc++/server_builder.h>
#include <grpc++/server_context.h>
#include <grpc/grpc.h>

class GrpcSystemService {
  private:
	tlinsRpcSystemServiceRecipient rpcService;
	std::unique_ptr<grpc::Server>  server;
	grpc::ServerBuilder            builder;
	std::string                    serverAddress;

  public:
	void stop()
	{
		server->Shutdown();
	}

	void operator()()
	{
		builder.AddListeningPort(serverAddress, grpc::InsecureServerCredentials());

		// Register service
		builder.RegisterService(&rpcService);
		server = std::unique_ptr<grpc::Server>{builder.BuildAndStart()};

		// Oczekiwanie na zakonczenie serwera
		server->Wait();
	};

	GrpcSystemService(const std::string &serverAddress_) : serverAddress{serverAddress_} {};

	virtual ~GrpcSystemService(){};
};


std::string logDir;

void sedLogFile()
{
	struct timeval tv;
	if (::gettimeofday(&tv, nullptr) < 0) {
		return;
	}

	struct tm *tmPtr = localtime(&tv.tv_sec);
	char       fileName[1024];
	sprintf(fileName, "tlinsSystemService-%d%0d%0d%0d.log", tmPtr->tm_year + 1900, tmPtr->tm_mon + 1, tmPtr->tm_mday,
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
		// Set standard output
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

	// Path to configuration file
	std::string path;

	switch (argc) {
	case 1:
		path   = "./configuration.xml";
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

	loggerInstance.logInfo("");
	loggerInstance.logInfo("-------------------------------------------------------------");
	loggerInstance.logInfo("");
	loggerInstance.logInfo("Jacek Pielaszkiewicz");
	loggerInstance.logInfo("Krasnik 2017/2018");
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
		loggerInstance.logInfo("  -> Configuration file");
		tlinsSystemMonitorConfiguration configuration(path);
		configuration.parse();

		loggerInstance.logInfo("  -> Build service based on configuration");
		configuration.buildConfiguration();

		loggerInstance.logInfo("  -> Start grpc");

		// Adresy serverow
		std::string rpcUrl{"0.0.0.0:30100"};
		configuration.getCommonParameters().getParameterValue("url", rpcUrl);

		// Watek odpowiedzialny za potwierdzenia
		GrpcSystemService grpcService{rpcUrl};
		std::thread       grpcServiceThread{std::ref(grpcService)};
		grpcServiceThread.detach();

		loggerInstance.logInfo("  -> Enter into main loop");
		while (true)
			::sleep(1);
	}
	catch (...) {
		// Obsluga bledow
		loggerInstance.logError("Error start system events monitor");
		tlinsBacktrace::instance().printStack(tlinsLogger::LOG_LEVEL_DEBUG);
		return 1;
	}
	return 0;
}