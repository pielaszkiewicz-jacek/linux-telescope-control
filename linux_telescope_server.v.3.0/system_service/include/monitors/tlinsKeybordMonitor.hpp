#ifndef __tlinsKeyboardMonitor_hpp__
#define __tlinsKeyboardMonitor_hpp__

#include <tlinsMonitorInterface.hpp>
#include <tlinsSystemService.hpp>

#include <atomic>
#include <set>
#include <string>
#include <thread>

class tlinsKeyboardMonitor {
  private:
	std::set<unsigned int> allowedKeys;
	std::atomic_bool       isEnd;
	std::string            device;
	std::thread            th;
	int                    fd;

  private:
	void openDevice();
	void stop();

	void sendEvents(const tlinsEventTypes type, const tlins::tlinsEventType grpcType, const int key, const int status);
	void sendEvents(const int value, const int type, const int number);


  public:
	void run();
	tlinsKeyboardMonitor(const std::string &dev, const std::set<unsigned int> keys);
	virtual ~tlinsKeyboardMonitor();
};

#endif