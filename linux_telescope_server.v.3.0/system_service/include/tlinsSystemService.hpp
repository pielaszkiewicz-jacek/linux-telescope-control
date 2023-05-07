#ifndef _tlinsSystemService_hpp_
#define _tlinsSystemService_hpp_

#include "system_service.grpc.pb.h"
#include "system_service.pb.h"

#include <condition_variable>
#include <list>
#include <map>
#include <memory>
#include <mutex>
#include <queue>
#include <set>
#include <string>

enum class tlinsEventTypes { KEBOARD = 1, JOYSTICK = 2 };

//
// Kolejka zdarzen. Zawiera zdarzenia gotowe do wyslania do wskazanego klienra
//
class tlinsSystemServiceEventQueue {
  private:
	// Koljka zdarzen
	std::queue<std::shared_ptr<tlins::tlinsEventInfo>> eventQueue;
	std::condition_variable                            cv;
	std::mutex                                         mtx;

  public:
	void enqueue(std::shared_ptr<tlins::tlinsEventInfo> &event);
	bool dequeue(std::shared_ptr<tlins::tlinsEventInfo> &event);

	tlinsSystemServiceEventQueue();
	virtual ~tlinsSystemServiceEventQueue();
};

class tlinsSystemServiceEventUserMap {
  private:
	std::map<std::string, std::set<tlinsEventTypes>> userEventMapByUser;
	std::map<tlinsEventTypes, std::set<std::string>> userEventMapByEventType;
	std::mutex                                       mtx;

  public:
	// Zarzadzanie uzytkownikami
	void addUser(const std::string &user, const std::vector<tlinsEventTypes> &events);
	void removeUser(const std::string &user);

	// Sprawdza czy uzytkownik ma zadeklarowany typ zdarzenia
	bool                  hasUserEvent(const std::string &id, const tlinsEventTypes event);
	std::set<std::string> getUsersForEvent(const tlinsEventTypes event);

	static tlinsSystemServiceEventUserMap &getInstance();

	virtual ~tlinsSystemServiceEventUserMap();

  private:
	tlinsSystemServiceEventUserMap();
};

class tlinsSystemServiceEventQueueManager {
  private:
	std::map<std::string, std::shared_ptr<tlinsSystemServiceEventQueue>> clientsQueues;
	std::mutex                                                           mtx;

  public:
	static tlinsSystemServiceEventQueueManager &getInstance();

	bool                                          removeQueue(const std::string &id);
	std::shared_ptr<tlinsSystemServiceEventQueue> getQueue(const std::string &id);

	virtual ~tlinsSystemServiceEventQueueManager();

  private:
	tlinsSystemServiceEventQueueManager();
};


//
// Usluga grpc
//
class tlinsRpcSystemServiceRecipient final : public tlins::tlinsRpcSystemServiceRecipient::Service {
  public:
	grpc::Status readEvents(grpc::ServerContext *context, const tlins::tlinsEventTypesList *request,
	                        grpc::ServerWriter<tlins::tlinsEventInfo> *writer);

	grpc::Status updateService(grpc::ServerContext* context,
							grpc::ServerReader<tlins::tlinsUpdateData>* reader,
							tlins::tlinsRpcStatus* response);

};

#endif