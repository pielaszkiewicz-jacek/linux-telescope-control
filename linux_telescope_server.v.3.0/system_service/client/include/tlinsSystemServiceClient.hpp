#ifndef __tlinsSystemServiceClient_hpp__
#define __tlinsSystemServiceClient_hpp__

#include <atomic>
#include <functional>
#include <grpc++/channel.h>
#include <mutex>
#include <queue>
#include <system_service.grpc.pb.h>
#include <system_service.pb.h>
#include <thread>

class tlinsSystemServiceClient {
  public:
	enum class EventType { KEYBOARD = 0, JOYSTICK = 1 };

	struct EventKyeboard {
		int keyId;
		int keyStatus;

		virtual ~EventKyeboard();
		EventKyeboard();
		EventKyeboard(const EventKyeboard &v);
		EventKyeboard &operator=(const EventKyeboard &v);
	};

	struct EventJoystick {
		int value;
		int type;
		int number;

		virtual ~EventJoystick();
		EventJoystick();
		EventJoystick(const EventJoystick &v);
		EventJoystick &operator=(const EventJoystick &v);
	};

	struct Event : public EventKyeboard, public EventJoystick {
		EventType eventType;

		Event &operator=(const Event &v) = default;
		Event()                          = default;
		Event(const Event &v)            = default;

		virtual ~Event();
	};

  private:
	// Stub polaczenia
	std::unique_ptr<tlins::tlinsRpcSystemServiceRecipient::Stub> connectionStub;
	std::unique_ptr<grpc::ClientReader<tlins::tlinsEventInfo>>   reader;
	tlins::tlinsEventTypesList                                   enentsTypeList;
	grpc::ClientContext                                          context;

	// Watek przetwarzajacy potwierdzenia od serwera
	std::atomic<bool> serverEnded;
	std::atomic<bool> end;
	std::thread       thread;
	std::mutex        mtx;

	void readKeyboardEvent(const tlins::tlinsEventInfo &event, std::function<void(const Event &)> fun);
	void readJoystickEvent(const tlins::tlinsEventInfo &event, std::function<void(const Event &)> fun);

	std::function<void(const tlinsSystemServiceClient::Event &)> inFunction;

	void threadFun();

  public:
	void stop();

	// Konstruktor klasy
	tlinsSystemServiceClient(std::shared_ptr<grpc::Channel> &                             channel,
	                         const std::vector<tlinsSystemServiceClient::EventType> &     events,
	                         std::function<void(const tlinsSystemServiceClient::Event &)> fun);

	// Destruktor klasy
	virtual ~tlinsSystemServiceClient();
};

#endif
