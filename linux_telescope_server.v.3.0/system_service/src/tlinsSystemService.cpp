#include "tlinsSystemService.hpp"
#include <tlinsBacktrace.hpp>

#include <tlinsLogger.hpp>

#include <chrono>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>


// using namespace std::chrono_literals;

void tlinsSystemServiceEventQueue::enqueue(std::shared_ptr<tlins::tlinsEventInfo> &event)
{
	std::unique_lock<std::mutex> lock(mtx);

	// Wstawienie zdarzenia do kolejuki
	eventQueue.push(event);

	// Powiadomienie watku o tym ze jest co do roboty
	cv.notify_one();
}

bool tlinsSystemServiceEventQueue::dequeue(std::shared_ptr<tlins::tlinsEventInfo> &event)
{
	// Oczekiwanie na dane wkolejce
	std::unique_lock<std::mutex> lock(mtx);
	cv.wait_for(lock, std::chrono::milliseconds{1000}, [this]() { return !eventQueue.empty(); });

	if (this->eventQueue.empty())
		return false;

	// Pobranie elementu listy
	event = std::move(eventQueue.front());
	eventQueue.pop();
	return true;
}

tlinsSystemServiceEventQueue::tlinsSystemServiceEventQueue()
{
}

tlinsSystemServiceEventQueue::~tlinsSystemServiceEventQueue()
{
}

//
// ---------------------------------
//
void tlinsSystemServiceEventUserMap::addUser(const std::string &user, const std::vector<tlinsEventTypes> &events)
{
	std::lock_guard<std::mutex> lock(mtx);
	for (auto &item : events) {
		userEventMapByUser[user].insert(item);
		userEventMapByEventType[item].insert(user);
	}
}

void tlinsSystemServiceEventUserMap::removeUser(const std::string &user)
{
	std::lock_guard<std::mutex> lock(mtx);
	userEventMapByUser.erase(user);

	for (auto &item : userEventMapByEventType)
		item.second.erase(user);
}

bool tlinsSystemServiceEventUserMap::hasUserEvent(const std::string &id, const tlinsEventTypes event)
{
	std::lock_guard<std::mutex> lock(mtx);

	if (userEventMapByUser.find(id) != userEventMapByUser.end())
		return userEventMapByUser[id].count(event) != 0;
	return false;
}

std::set<std::string> tlinsSystemServiceEventUserMap::getUsersForEvent(const tlinsEventTypes event)
{
	std::lock_guard<std::mutex> lock(mtx);
	return userEventMapByEventType[event];
}

tlinsSystemServiceEventUserMap &tlinsSystemServiceEventUserMap::getInstance()
{
	static tlinsSystemServiceEventUserMap instance{};
	return instance;
}

tlinsSystemServiceEventUserMap::~tlinsSystemServiceEventUserMap()
{
}

tlinsSystemServiceEventUserMap::tlinsSystemServiceEventUserMap()
{
}

//
// ---------------------------------
//
tlinsSystemServiceEventQueueManager &tlinsSystemServiceEventQueueManager::getInstance()
{
	static tlinsSystemServiceEventQueueManager instance{};
	return instance;
}

bool tlinsSystemServiceEventQueueManager::removeQueue(const std::string &id)
{
	std::unique_lock<std::mutex> lock(mtx);
	if (clientsQueues.count(id) == 0)
		return false;

	clientsQueues.erase(id);
	return true;
}

std::shared_ptr<tlinsSystemServiceEventQueue> tlinsSystemServiceEventQueueManager::getQueue(const std::string &id)
{
	std::unique_lock<std::mutex> lock(mtx);

	if (clientsQueues.count(id) == 0)
		clientsQueues[id] = std::make_shared<tlinsSystemServiceEventQueue>();

	return clientsQueues[id];
}

tlinsSystemServiceEventQueueManager::~tlinsSystemServiceEventQueueManager()
{
}

tlinsSystemServiceEventQueueManager::tlinsSystemServiceEventQueueManager()
{
}

//
// ---------------------------------
//
grpc::Status tlinsRpcSystemServiceRecipient::updateService(	grpc::ServerContext* context,
															grpc::ServerReader<tlins::tlinsUpdateData>* reader,
															tlins::tlinsRpcStatus* response)
{
	tlins::tlinsUpdateData data;

	// Tworzenie unikalnej nazwy pliku
	char tmpTemplate[1024];
	::strcpy(tmpTemplate, "tlins_tmp_update_pkg_XXXXXX");

	if(::mkstemps(tmpTemplate, strlen(tmpTemplate)) < 0) {
		response -> set_status(tlins::ErrorCodes::_ERROR_CODE_ERROR);
		response -> set_errorcode(0);
		response -> set_errordescription("Erorr create temp file name");
		return grpc::Status::OK;
	}

	std::string tempFileName{std::string{"/tmp/"} + std::string{tmpTemplate} + std::string{".tgz"}};

	// Otwarcie pliku do zapisu
	int fd = ::open(tempFileName.c_str(), O_CREAT || O_WRONLY);
	if(fd < 0) {
		response -> set_status(tlins::ErrorCodes::_ERROR_CODE_ERROR);
		response -> set_errorcode(0);
		response -> set_errordescription("Erorr open output file");
		return grpc::Status::OK;
	}

	while (reader->Read(&data)) {
		std::string buf{std::move(data.data())};
		if(::write(fd, buf.data(), buf.length()) <= 0) {
			close(fd);
			response -> set_status(tlins::ErrorCodes::_ERROR_CODE_ERROR);
			response -> set_errorcode(0);
			response -> set_errordescription("Error write update package into file.");
			return grpc::Status::OK;
		}
	}
	close(fd);

	// Wykonanie aktualizacji
	// TODO
	// TODO
	// TODO

	// Run update

//   std::vector<RouteNote> received_notes;
//   RouteNote note;
// 	while (stream->Read(&note)) {
// 	for (const RouteNote& n : received_notes) {
//       if (n.location().latitude() == note.location().latitude() &&
//           n.location().longitude() == note.location().longitude()) {
//         stream->Write(n);
//       }
//     }
//     received_notes.push_back(note);
//   }
//   return Status::OK;
	// (void) context;
	// (void) reader;
	// (void) response;
	// return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");

	response -> set_status(tlins::ErrorCodes::_ERROR_CODE_SUCCESS);
	response -> set_errorcode(0);
	response -> set_errordescription("OK");
	return grpc::Status::OK;
}


grpc::Status tlinsRpcSystemServiceRecipient::readEvents(grpc::ServerContext *                      context,
                                                        const tlins::tlinsEventTypesList *         request,
                                                        grpc::ServerWriter<tlins::tlinsEventInfo> *writer)
{
	static unsigned long clientIdIdx = 0;
	static std::mutex    mtx;

	// Unikalny identyfikator klienta
	std::string userId{};
	{
		std::unique_lock<std::mutex> lock(mtx);
		clientIdIdx++;
		userId = std::to_string(clientIdIdx);
	}

	// Pobranie listy typow zdarzen ktore beda przekazywane
	std::vector<tlinsEventTypes> eventsTypes;
	for (int i = 0; i < request->types_size(); i++) {
		switch (request->types(i)) {
		case tlins::tlinsEventType::_KEYBOARD:
			eventsTypes.push_back(tlinsEventTypes::KEBOARD);
			break;

		case tlins::tlinsEventType::_JOYSTICK:
			eventsTypes.push_back(tlinsEventTypes::JOYSTICK);
			break;
		}
	}

	{
		// Rejestracja klienta
		auto &uMap = tlinsSystemServiceEventUserMap::getInstance();
		uMap.addUser(userId, eventsTypes);
	}

	// Petla przetwarzajaca potwierdzenia
	tlinsSystemServiceEventQueueManager &         qMgrInstance = tlinsSystemServiceEventQueueManager::getInstance();
	std::shared_ptr<tlinsSystemServiceEventQueue> queue        = qMgrInstance.getQueue(userId);

	while (true) {
		// Pobranie komunikatu z kolejki i wyslanie
		std::shared_ptr<tlins::tlinsEventInfo> event;
		if (queue->dequeue(event)) {
			if (!event) {
				TLINS_LOG_ERROR("NULL event");
			}

			if (event && !writer->Write(*event)) {
				// Prawdopodobnie klient sie rozaczyl
				break;
			}
		}
	}

	// Usuniecie kolejki
	qMgrInstance.removeQueue(userId);

	// Deaktywacja klienta po zakonczeniu
	{
		// Rejestracja klienta
		auto &uMap = tlinsSystemServiceEventUserMap::getInstance();
		uMap.removeUser(userId);
	}
	return grpc::Status::OK;
}
