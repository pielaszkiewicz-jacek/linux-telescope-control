#ifndef __tlinsSerialGpioUtils_hpp__
#define __tlinsSerialGpioUtils_hpp__

#include <tlinsSerialDeviceException.hpp>

#include <poll.h>

#include <map>
#include <memory>
#include <mutex>
#include <string>
#include <thread>
#include <vector>

enum class GPIO_EDGE : int { NONE = 0, RISING = 1, FALLING = 2, BOTH = 3 };

class tlinsSerialGpioUtils {
  public:
	static void gpioExport(const unsigned int gpio);
	static void gpioUnExport(const unsigned int gpio);
	static void gpioSetDirection(const unsigned int gpio, const bool isIn);
	static void gpioSetEdge(const unsigned int gpio, const GPIO_EDGE edge);
	static int gpioOpenValueFile(const unsigned int gpio);
};

class tlinsSerialGpioCallBack {
  public:
	virtual void operator()(const char c) = 0;
	virtual ~tlinsSerialGpioCallBack(){};
};

/*
 * Klasa realizuje nasluchiwanie na wskazanych portach GPIO
 */
class tlinsSerialGpio {
  private:
	// Thread
	std::unique_ptr<std::thread> thread_;

	// Wektorow
	std::vector<struct pollfd> fds;

	std::map<int, GPIO_EDGE> gpioToEdge;

	// Mutex synchronizujacy dostep do mapy callbackow
	std::mutex mtx;

	// Mapa callbackow powiazanych z plikami
	std::map<int, std::vector<std::shared_ptr<tlinsSerialGpioCallBack>>> callbacks;
	std::map<int, int>                                                   gpioToFd;

	bool end;

  private:
	bool registerCallback(const int gpio, const GPIO_EDGE edge,
	                      const std::shared_ptr<tlinsSerialGpioCallBack> &function);

  public:
	static tlinsSerialGpio &getInstance();

	// Operator przetwarzajace otwarte deskryptory plikow
	void operator()();

	// Metoda rejestrujaca callbacki
	bool addCallback(const int gpio, const GPIO_EDGE edge, const std::shared_ptr<tlinsSerialGpioCallBack> &cb);

	// Konstruktor
	virtual ~tlinsSerialGpio();

	tlinsSerialGpio();
};

#endif