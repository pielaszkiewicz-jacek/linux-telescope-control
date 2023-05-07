#ifndef __tlinsJoystickMonitor_hpp__
#define __tlinsJoystickMonitor_hpp__

#include <tlinsBacktrace.hpp>
#include <tlinsMonitorInterface.hpp>
#include <tlinsSystemService.hpp>

#include <atomic>
#include <list>
#include <mutex>
#include <set>
#include <string>
#include <thread>
#include <unordered_map>

#define MAX_NUMBER 30
#define MAX_TYPES 10
#define MAX_HISTORY_LENGTH 20

class tlinsJoystickMonitor {
  private:
	std::atomic_bool isEnd;
	std::string      device;
	std::thread      th;
	int              fd;
	int              kfd;

	struct EventInfo {
		int type;
		int number;
		int value;

		EventInfo() = default;

		EventInfo(const int type_, const int number_, const int value_) : type{type_}, number{number_}, value{value_}
		{
		}
	};

	struct EventInfoExt {
		EventInfo value;
		EventInfo prev;

		EventInfoExt() : prev{-1, -1, -1}, value{-2, -2, -2}
		{
		}

		void makeEqual()
		{
			prev = value;
		}

		EventInfoExt &operator=(const EventInfo &v)
		{
			prev  = value;
			value = v;
			return *this;
		}

		bool test()
		{
			return prev.type == value.type && prev.number == value.number && prev.value == value.value;
		}

		void set(const EventInfo &v)
		{
			prev  = value;
			value = v;
		}
	};

	std::unordered_map<std::string, EventInfoExt> state;
	std::mutex                                    mtx;

  private:
	void openDevice();
	void stop();

	void sendEvents(const tlinsEventTypes type, const tlins::tlinsEventType grpcType, const int key, const int status);
	void sendEvents(const int value, const int type, const int number);

  public:
	void run();
	tlinsJoystickMonitor(const std::string &dev);
	virtual ~tlinsJoystickMonitor();
};

#endif