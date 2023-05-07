#include "tlinsJoystickMonitor.hpp"

#include "tlinsKeysDefinition.hpp"
#include <tlinsBacktrace.hpp>
#include <tlinsException.hpp>
#include <tlinsLogger.hpp>
#include <tlinsSystemService.hpp>

#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <thread>
#include <unistd.h>
#include <unordered_map>
#include <utility>


struct js_event {
	unsigned int  time;   /* event timestamp in milliseconds */
	short         value;  /* value */
	unsigned char type;   /* event type */
	unsigned char number; /* axis/button number */
};

#define JS_EVENT_BUTTON 0x01 /* button pressed/released */
#define JS_EVENT_AXIS 0x02   /* joystick moved */
#define JS_EVENT_INIT 0x80   /* initial state of device */

void tlinsJoystickMonitor::stop()
{
	isEnd = true;
}

void tlinsJoystickMonitor::sendEvents(const tlinsEventTypes type, const tlins::tlinsEventType grpcType, const int key,
                                      const int status)
{
	auto &userEventMapInstance = tlinsSystemServiceEventUserMap::getInstance();
	auto &queuesManager        = tlinsSystemServiceEventQueueManager::getInstance();

	auto userSet = userEventMapInstance.getUsersForEvent(type);

	if (!userSet.empty()) {
		auto event = std::make_shared<tlins::tlinsEventInfo>();
		event->set_eventtype(grpcType);

		auto key_ = event->mutable_keyboard();

		key_->mutable_keyid()->set_value(key);
		key_->mutable_keystatus()->set_value(status);

		// Przeslanie informacji do wszystkich aktywnych klientow
		for (auto &item : userSet) {
			std::shared_ptr<tlinsSystemServiceEventQueue> q{queuesManager.getQueue(item)};
			q->enqueue(event);
		}
	}
}

void tlinsJoystickMonitor::sendEvents(const int value, const int type, const int number)
{
	auto &userEventMapInstance = tlinsSystemServiceEventUserMap::getInstance();
	auto &queuesManager        = tlinsSystemServiceEventQueueManager::getInstance();

	auto userSet = userEventMapInstance.getUsersForEvent(tlinsEventTypes::JOYSTICK);

	if (!userSet.empty()) {
		auto event = std::make_shared<tlins::tlinsEventInfo>();
		event->set_eventtype(tlins::tlinsEventType::_JOYSTICK);

		auto joystik = event->mutable_joystick();

		joystik->mutable_value()->set_value(value);
		joystik->mutable_type()->set_value(type);
		joystik->mutable_number()->set_value(number);

		// Przeslanie informacji do wszystkich aktywnych klientow
		for (auto &item : userSet) {
			std::shared_ptr<tlinsSystemServiceEventQueue> q{queuesManager.getQueue(item)};
			q->enqueue(event);
		}
	}
}

static void getKey(const int a, const int b, std::string &txt)
{
	txt = std::to_string(a);
	txt += "::";
	txt += std::to_string(b);
}

// static std::unordered_map<int, bool> toIgnore{{26, true}, {25, true}, {24, true}, {23, true}, {19, true},
//                                               {18, true}, {17, true}, {16, true}, {15, true}, {13, true},
//                                               {12, true}, {14, true}, {10, true}, {8, true},  {9, true}};

static std::unordered_map<int, bool> toIgnore{{26, true}, {25, true}, {24, true}, {23, true}, {19, true},
                                              {18, true}, {17, true}, {16, true}, {15, true}, {13, true},
                                              {12, true}, {14, true}};


static std::unordered_map<std::string, bool> toIgnoreStr{{"2:5", true}, {"2:4", true}};

static std::unordered_map<std::string, std::pair<int, int>> toMapStr{
											 {"7:-32767", {1000,    JS_EVENT_BUTTON}}, // UP
											 {"7:32767",  {1001,  JS_EVENT_BUTTON}},   // DOWN
											 {"6:-32767", {1002,  JS_EVENT_BUTTON}},   // LEFT
											 {"6:32767",  {1003, JS_EVENT_BUTTON}} };  // RIGHT

static std::string sKey(int t, int n) {
	return std::to_string(t) + ":" + std::to_string(n);
}

void tlinsJoystickMonitor::run()
{
	auto &userEventMapInstance = tlinsSystemServiceEventUserMap::getInstance();
	auto &queuesManager        = tlinsSystemServiceEventQueueManager::getInstance();

	auto sender = [this]() {
		int i = 0;
		while (!isEnd) {
			i++;
			std::this_thread::sleep_for(std::chrono::milliseconds(80));

			for (auto &item : state) {
				std::unique_lock<std::mutex> lock{mtx};
				auto &                       key = item.first;
				auto &                       evL = item.second;

				if (!evL.test()) {
					sendEvents(evL.value.value, evL.value.type, evL.value.number);
					evL.makeEqual();
				}
			}

			// Testowe w celu ulatwienia wylaczenia klienta generowane raz na sekunde
			if (i % 10 == 0) {
				i = 0;
				sendEvents(-1, -1, -1);
			}
		}
	};
	std::thread th{sender};

	while (!isEnd) {
		// Czytanie urzadzenia wejsciowego
		struct js_event ev;

		auto res = ::read(this->fd, reinterpret_cast<void *>(&ev), sizeof(struct js_event));
		if (res <= 0) {
			// Przy bledzie odczytu proba otwarcia na nowo
			bool endOpen = false;
			while (!endOpen) {
				try {
					openDevice();
					endOpen = true;
				}
				catch (...) {
					::sleep(1);
				}
			}
			continue;
		}

		//
		// Wyslanie zdarzenia typu joystick
		//
		// if (toIgnore[static_cast<int>(ev.number)]) {
		if (toIgnoreStr[sKey(static_cast<int>(ev.type), static_cast<int>(ev.number))]) {
			continue;
		}
		std::string dbg{"KEY [A] = "};
		dbg += std::to_string(static_cast<int>(ev.number));
		dbg += "; VALUE = " + std::to_string(static_cast<int>(ev.value));
		dbg += "; TYPE = " + std::to_string(static_cast<int>(ev.type));
		tlinsLogger::instance().logDebug(dbg.c_str());


		// Dodatkowe maponie
		auto eNumber = static_cast<int>(ev.number);
		auto eValue  = static_cast<int>(ev.value);
		auto eType   = static_cast<int>(ev.type);

		std::string k = std::to_string(eNumber) + ":" + std::to_string(eValue);
		if(toMapStr.count(k) != 0) {
			auto vv = toMapStr[k];
			eNumber = vv.first;
			eType   = vv.second;
		}

		EventInfo evObj{eType, eNumber, eValue};

		// Obliczenie nowej wartosci srednej
		if (eType == JS_EVENT_AXIS || eType == JS_EVENT_BUTTON) {
			std::unique_lock<std::mutex> lock{mtx};
			int                          n = eNumber;
			int                          t = eType;

			// Get key
			std::string key;
			getKey(n, t, key);
			state[key] = evObj;
		}
	}

	if (th.joinable())
		th.join();
}

void tlinsJoystickMonitor::openDevice()
{
	// Sprawdzenie pliku urzadzenia
	struct stat buf;
	if (::stat(device.c_str(), &buf) < 0) {
		throw tlinsException(std::string{"Error open device : " + device}, -1);
	}

	fd = ::open(device.c_str(), O_RDONLY);
	if (fd < 0) {
		throw tlinsException(std::string{"Error open device : " + device}, -1);
	}
}

tlinsJoystickMonitor::tlinsJoystickMonitor(const std::string &dev) : isEnd{false}, device{dev}, fd{-1}
{
}

tlinsJoystickMonitor::~tlinsJoystickMonitor()
{
	stop();
	if (fd >= 0)
		::close(fd);
}