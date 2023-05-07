#ifndef __tlinsSerialDeviceThread_hpp__
#define __tlinsSerialDeviceThread_hpp__

#include "tlinsSerialDeviceException.hpp"
#include <condition_variable>
#include <list>
#include <map>
#include <memory>
#include <mutex>
#include <thread>

struct tlinsSerialDeviceRequestHandlerFunction {
	virtual unsigned long operator()(std::unique_ptr<tlinsSerialDeviceBaseRequest> request) = 0;
};

class tlinsSerialDeviceThread {
  private:
	// Zmienna warunkowa do kontrolowania dostepu do listy rzadan
	std::condition_variable condVar;
	std::mutex              condMutex;

	// Mutex odpowiedzialny za synchronizacje operacji na kolejkach komunikatow
	std::mutex queueMutex;

	// Kolejka rzadan do watku
	std::list<std::unique_ptr<tlinsSerialDeviceBaseRequest>> requestsQueue;

	// Aktualnie przetwarzanie rzadanie
	std::unique_ptr<tlinsSerialDeviceBaseRequest> currentRequest;

  private:
	// Mapa handlerow
	static std::map<std::string, std::shared_ptr<tlinsSerialDeviceRequestHandlerFunction>> requestHandlerMap;

  public:
	static bool registerRequestHandler(const std::string &                                            name,
	                                   const std::shared_ptr<tlinsSerialDeviceRequestHandlerFunction> handler);

  private:
	unsigned long enqueueRequest(std::unique_ptr<tlinsSerialDeviceBaseRequest> request, bool highPriority);
	std::unique_ptr<tlinsSerialDeviceBaseRequest> dequeueRequest();

  public:
	unsigned long registerRequest(std::unique_ptr<tlinsSerialDeviceBaseRequest> request, bool highPriority = false);

	// Uruchomienie watku
	void spawnThread();

	// Glowna funkcja watku
	void operator()(void);

  public:
	tlinsSerialDeviceThread();
	virtual ~tlinsSerialDeviceThread();
};

#endif
