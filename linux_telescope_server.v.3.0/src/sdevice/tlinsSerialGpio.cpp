#include <tlinsBacktrace.hpp>
#include <tlinsSerialGpio.hpp>

#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>

void tlinsSerialGpioUtils::gpioExport(const unsigned int gpio)
{
	int fd = open("/sys/class/gpio/export", O_WRONLY);
	if (fd < 0)
		__THROW__(tlinsSerialDeviceException("Error open export GPIO file", tlinsSerialDeviceException::ERROR_GPIO));

	std::string str = std::to_string(gpio);
	if (write(fd, str.c_str(), str.size()) <= 0) {
		close(fd);
		__THROW__(
		    tlinsSerialDeviceException("Error write into export GPIO file", tlinsSerialDeviceException::ERROR_GPIO));
	}

	close(fd);
}

void tlinsSerialGpioUtils::gpioUnExport(const unsigned int gpio)
{
	int fd = open("/sys/class/gpio/unexport", O_WRONLY);
	if (fd < 0)
		__THROW__(tlinsSerialDeviceException("Error open unexport GPIO file", tlinsSerialDeviceException::ERROR_GPIO));

	std::string str = std::to_string(gpio);
	if (write(fd, str.c_str(), str.size()) <= 0) {
		close(fd);
		__THROW__(
		    tlinsSerialDeviceException("Error write into unexport GPIO file", tlinsSerialDeviceException::ERROR_GPIO));
	}

	close(fd);
}

void tlinsSerialGpioUtils::gpioSetDirection(const unsigned int gpio, const bool isIn)
{
	std::string direction = isIn ? (std::string("in")) : (std::string("out"));
	std::string fileName  = "/sys/class/gpio/gpio" + std::to_string(gpio) + "/direction";

	int fd = open(fileName.c_str(), O_WRONLY);
	if (fd < 0)
		__THROW__(
		    tlinsSerialDeviceException("Error open GPIO file => " + fileName, tlinsSerialDeviceException::ERROR_GPIO));

	if (write(fd, direction.c_str(), direction.size()) <= 0) {
		close(fd);
		__THROW__(
		    tlinsSerialDeviceException("Error write into direction GPIO file", tlinsSerialDeviceException::ERROR_GPIO));
	}

	close(fd);
}

void tlinsSerialGpioUtils::gpioSetEdge(const unsigned int gpio, const GPIO_EDGE edge)
{
	std::string edgeStr;
	switch (edge) {
	case GPIO_EDGE::NONE:
		edgeStr = "none";
		break;

	case GPIO_EDGE::RISING:
		edgeStr = "rising";
		break;

	case GPIO_EDGE::FALLING:
		edgeStr = "falling";
		break;

	case GPIO_EDGE::BOTH:
		edgeStr = "both";
		break;
	};

	std::string fileName = "/sys/class/gpio/gpio" + std::to_string(gpio) + "/edge";

	int fd = open(fileName.c_str(), O_WRONLY);
	if (fd < 0)
		__THROW__(
		    tlinsSerialDeviceException("Error open GPIO file => " + fileName, tlinsSerialDeviceException::ERROR_GPIO));

	if (write(fd, edgeStr.c_str(), edgeStr.size()) <= 0) {
		close(fd);
		__THROW__(
		    tlinsSerialDeviceException("Error write into edge GPIO file", tlinsSerialDeviceException::ERROR_GPIO));
	}

	close(fd);
}

int tlinsSerialGpioUtils::gpioOpenValueFile(const unsigned int gpio)
{
	std::string fileName = "/sys/class/gpio/gpio" + std::to_string(gpio) + "/value";

	int fd = open(fileName.c_str(), O_RDONLY | O_NONBLOCK);
	if (fd < 0)
		__THROW__(
		    tlinsSerialDeviceException("Error open GPIO file => " + fileName, tlinsSerialDeviceException::ERROR_GPIO));

	return fd;
}

//
// ---------------------------------------------
// ---------------------------------------------
// ---------------------------------------------
//
bool tlinsSerialGpio::addCallback(const int gpio, const GPIO_EDGE edge,
                                  const std::shared_ptr<tlinsSerialGpioCallBack> &cb)
{
	std::lock_guard<std::mutex> lock(mtx);
	return registerCallback(gpio, edge, cb);
}

void tlinsSerialGpio::operator()()
{
	while (!end) {
		if (fds.size() == 0) {
			// 10 ms sleep
			::poll(NULL, 0, 10);
			continue;
		}
		int rc = ::ppoll(fds.data(), fds.size(), nullptr, nullptr);

		if (rc <= 0) {
			LOG_ERROR("ppoll error. Error code : ");
			continue;
		}

		// Zablokowanie mutexa
		std::lock_guard<std::mutex> lock(mtx);

		for (int i = 0; i < fds.size(); i++) {
			if ((fds[i].revents & POLLIN) != 0) {
				// Deskryptor pliku
				auto fd = fds[i].fd;

				// Przewiniecie na poczatek strumienia
				lseek(fd, 0, SEEK_SET);

				// Odczyt strumnienia
				char value;
				read(fd, &value, 1);

				// Uruchomienie zarejestrowanyc funkcji zwrotnych
				auto calls = callbacks.find(fd);
				if (calls != callbacks.end()) {
					// Wywolanie callbackow skojazonych z GPIO
					for (auto cc = calls->second.begin(); cc != calls->second.end(); cc++) {
						(*(cc->get()))(value);
					}
				}
			}
		}
	}
}

tlinsSerialGpio &tlinsSerialGpio::getInstance()
{
	static tlinsSerialGpio instance;
	return instance;
}

bool tlinsSerialGpio::registerCallback(const int gpio, const GPIO_EDGE edge,
                                       const std::shared_ptr<tlinsSerialGpioCallBack> &function)
{
	bool initGpio = true;
	auto iter     = gpioToEdge.find(gpio);
	if (iter != gpioToEdge.end()) {
		// Gpio jest juz zarejestrtowane
		if (iter->second != edge) {
			// Gdy typ zbocza jest rozny konczymy
			return false;
		}
		initGpio = false;
	}

	if (initGpio) {
		// Wlaczenie GPIO
		tlinsSerialGpioUtils::gpioExport(gpio);

		// Kierunek dzialania jako IN
		tlinsSerialGpioUtils::gpioSetDirection(gpio, true);

		// Ustawienie zbocza na ktore bedzie reagowalo GPIO
		tlinsSerialGpioUtils::gpioSetEdge(gpio, edge);

		// Otwarcie pliku
		int fd = tlinsSerialGpioUtils::gpioOpenValueFile(gpio);

		// Zapamaietanie nowego gpio
		gpioToEdge[gpio] = edge;

		// Wiazanie GPIO z FD
		gpioToFd[gpio] = fd;

		// Nowa pozycja w mapie wiazacej deskryptory plikow i wywolania zwrotne
		callbacks[fd];

		// Rejestrowanie deskryptor pliku dla poll
		struct pollfd item;
		item.fd     = fd;
		item.events = POLLIN;
		fds.push_back(item);
	}

	// Rejestracja nowej funkcji zwrotnej
	callbacks[gpioToFd[gpio]].push_back(function);

	return true;
}

tlinsSerialGpio::tlinsSerialGpio()
{
	// Watek dziala
	end = false;

	// Uruchomienie watka
	thread_.reset(new std::thread(std::ref(*this)));
}

tlinsSerialGpio::~tlinsSerialGpio()
{
	end = true;
	thread_->join();
	thread_.reset();

	for (auto i = fds.begin(); i != fds.end(); i++) {
		close(i->fd);
	}

	for (auto &i : gpioToFd) {
		try {
			tlinsSerialGpioUtils::gpioUnExport(i.first);
		}
		catch (...) {
		}
	}
}
