#include "tlinsKeybordMonitor.hpp"
#include "tlinsJoystickMonitor.hpp"
#include "tlinsKeysDefinition.hpp"

#include <tlinsBacktrace.hpp>
#include <tlinsException.hpp>
#include <tlinsLogger.hpp>
#include <tlinsSystemService.hpp>

#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

struct input_event {
	struct timeval time;
	unsigned short type;
	unsigned short code;
	unsigned int   value;
};

#define EV_SYN 0x00
#define EV_KEY 0x01
#define EV_REL 0x02
#define EV_ABS 0x03
#define EV_MSC 0x04
#define EV_SW 0x05
#define EV_LED 0x11
#define EV_SND 0x12
#define EV_REP 0x14 // Otwarcie urzadzenia
#define EV_FF 0x15
#define EV_PWR 0x16
#define EV_FF_STATUS 0x17
#define EV_MAX 0x1f
#define EV_CNT (EV_MAX + 1)

void tlinsKeyboardMonitor::stop()
{
	isEnd = true;
}

//
// Bledne mapowanie
//
std::map<int, int> kmap{
    {17, tlinsKeysDefinition::KEY_UP},    // W
    {30, tlinsKeysDefinition::KEY_LEFT},  // A
    {45, tlinsKeysDefinition::KEY_OK},    // X
    {31, tlinsKeysDefinition::KEY_RIGHT}, // S
    {44, tlinsKeysDefinition::KEY_DOWN},  // Z
    {25, tlinsKeysDefinition::KEY_F01},   // P
    {24, tlinsKeysDefinition::KEY_F02},   // O
    {23, tlinsKeysDefinition::KEY_F11},   // I
    {20, tlinsKeysDefinition::KEY_F12},   // T
    {32, tlinsKeysDefinition::KEY_F13},   // D
    {46, tlinsKeysDefinition::KEY_F14},   // C
    {38, tlinsKeysDefinition::KEY_F21},   // L
    {37, tlinsKeysDefinition::KEY_F22},   // K
    {31, tlinsKeysDefinition::KEY_F23},   // ... TBD
    {36, tlinsKeysDefinition::KEY_F24},   // J
    {32, tlinsKeysDefinition::KEY_F31},   // D
    {33, tlinsKeysDefinition::KEY_F32},   // F
    {34, tlinsKeysDefinition::KEY_F33},   // G
    {35, tlinsKeysDefinition::KEY_F34},   // H
};

void tlinsKeyboardMonitor::sendEvents(const tlinsEventTypes type, const tlins::tlinsEventType grpcType, const int key, const int status)
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

void tlinsKeyboardMonitor::sendEvents(const int value, const int type, const int number)
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

void tlinsKeyboardMonitor::run()
{
	auto &userEventMapInstance = tlinsSystemServiceEventUserMap::getInstance();
	auto &queuesManager        = tlinsSystemServiceEventQueueManager::getInstance();

	auto sender = [this]() {
		while (!isEnd) {
			std::this_thread::sleep_for(std::chrono::milliseconds(1000));

			// Testowe w celu ulatwienia wylaczenia klienta generowane raz na sekunde
			sendEvents(tlinsEventTypes::KEBOARD, tlins::tlinsEventType::_KEYBOARD, -1, -1);
		}
	};
	std::thread th{sender};

	while (!isEnd) {
		// Czytanie urzadzenia wejsciowego
		struct input_event ev;
		auto               res = ::read(this->fd, reinterpret_cast<void *>(&ev), sizeof(struct input_event));
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

		// Tylko klawiatura. Inne zdarzenia beda ignorowane
		if (ev.type != EV_KEY)
			continue;

		if (!allowedKeys.empty() && allowedKeys.count(static_cast<unsigned int>(ev.code)) == 0) {
			continue;
		}

		// Status klawisza
		int keyStatus = static_cast<int>(ev.value);
		int keyCode   = static_cast<int>(ev.code);

		// Klawisze
		sendEvents(tlinsEventTypes::KEBOARD, tlins::tlinsEventType::_KEYBOARD, kmap[keyCode], keyStatus);

		// Klawisze jostika - emulacja
		sendEvents(ev.value, ev.type, static_cast<int>(ev.code));
	}
}

void tlinsKeyboardMonitor::openDevice()
{
	// Sprawdzenie pliku urzadzenia
	struct stat buf;
	if (::stat(device.c_str(), &buf) < 0) {
		__THROW__(tlinsException(std::string{"Error open device : " + device}, -1));
	}

	fd = ::open(device.c_str(), O_RDONLY);
	if (fd < 0) {
		__THROW__(tlinsException(std::string{"Error open device : " + device}, -1));
	}
}

tlinsKeyboardMonitor::tlinsKeyboardMonitor(const std::string &dev, const std::set<unsigned int> keys)
    : allowedKeys{keys}, isEnd{false}, device{dev}, fd{-1}
{
}

tlinsKeyboardMonitor::~tlinsKeyboardMonitor()
{
	stop();
	if (fd >= 0)
		::close(fd);
}