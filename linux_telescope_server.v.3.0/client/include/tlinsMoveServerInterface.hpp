#ifndef __tlinsMoveServerInterface_hpp__
#define __tlinsMoveServerInterface_hpp__

#include <atomic>
#include <condition_variable>
#include <device.grpc.pb.h>
#include <grpc++/channel.h>
#include <map>
#include <mutex>
#include <string>
#include <thread>
#include <tlinsBacktrace.hpp>
#include <tlinsInterfaceException.hpp>
#include <tlins_utils.hpp>
#include <vector>

//
// ----------------------------------------------------
// Potwierdzenia
// ----------------------------------------------------
//


class tlinsMoveServerLimitsInterfaceCallBack {
  private:
	long id;

  public:
	virtual void process(const tlins::tlinsRpcConfirmationStatus &status) = 0;
	virtual bool release()                                                = 0;

	virtual ~tlinsMoveServerLimitsInterfaceCallBack() = default;
};



//
// Abstrakcyjny interfejs potwierdzenb
//
class tlinsMoveServerInterfaceCallBack {
  private:
	long id;

  public:
	virtual void process(const tlins::tlinsRpcConfirmationStatus &status) = 0;
	virtual bool release()                                                = 0;
	void         setId(const long id_)
	{
		id = id_;
	};

	long getId() const
	{
		return id;
	};

	virtual ~tlinsMoveServerInterfaceCallBack() = default;
};

//
// Manager potwierdzen
//
// Obiekt klasy wyamaga aby przed jego utworzeniem klient zarejestrowal sie
// na potwierdzenia.
// Obiekt klasy w momencie gdy jest powolywany tworzy watek odpowiedzialny za
// Przetwarzanie potwierdzen asynchronicznych
//
class tlinsMoveServerInterfaceConfirmation {
  private:
	std::unique_ptr<grpc::ClientReader<tlins::tlinsRpcConfirmationStatus>> reader;

	// Stub polaczenia
	std::unique_ptr<tlins::tlinsRpcConfirmationService::Stub> connectionStub;

	// Mutex kontrolujay dostep do mapy
	std::mutex mtx;

	// Potwierdzenia sa skladowane per id potwierdzenia i typ potwierdzenia
	std::map<long, std::shared_ptr<tlinsMoveServerInterfaceCallBack>> confirmationsCallbacksMap;

	std::string confirmId;

	// Watek przetwarzajacy potwierdzenia od serwera
	std::atomic<bool> end;
	std::thread       thread;

	grpc::ClientContext context;
	bool                ctxSet;

  public:
	long registerCallback(std::shared_ptr<tlinsMoveServerInterfaceCallBack> cb);

	// Petla glowna realizujaca przetwarzanie potwierdzen
	void operator()();

	void flush();

	// Konstruktor klasy
	tlinsMoveServerInterfaceConfirmation(std::shared_ptr<grpc::Channel> &channel, const std::string &id);

	// Destruktor klasy
	virtual ~tlinsMoveServerInterfaceConfirmation();
};

class tlinsMoveServerInterfaceLimitsConfirmation {
  private:
	std::unique_ptr<grpc::ClientReader<tlins::tlinsRpcConfirmationStatus>> reader;

	// Stub polaczenia
	std::unique_ptr<tlins::tlinsRpcConfirmationService::Stub> connectionStub;

	// Mutex kontrolujay dostep do mapy
	std::mutex mtx;

	// Potwierdzenia sa skladowane per id potwierdzenia i typ potwierdzenia
	std::map<std::string, std::vector<std::shared_ptr<tlinsMoveServerLimitsInterfaceCallBack>>> confirmationsCallbacksMap;

	std::string confirmId;

	// Watek przetwarzajacy potwierdzenia od serwera
	std::atomic<bool> end;
	std::thread       thread;

	grpc::ClientContext context;
	bool                ctxSet;

  public:
	bool registerCallback(const std::string &devName, std::shared_ptr<tlinsMoveServerLimitsInterfaceCallBack> cb);

	// Petla glowna realizujaca przetwarzanie potwierdzen
	void operator()();

	void flush();

	// Konstruktor klasy
	tlinsMoveServerInterfaceLimitsConfirmation(std::shared_ptr<grpc::Channel> &channel, const std::string &id);

	// Destruktor klasy
	virtual ~tlinsMoveServerInterfaceLimitsConfirmation();
};

//
// ----------------------------------------------------
// ----------------------------------------------------
// ----------------------------------------------------
//
class tlinsMoveServerInterface {
  private:
	// tlinsSynchronusChannel &synchronusChannel;
	std::unique_ptr<tlins::tlinsRpcService::Stub> connectionStub;
	std::string                                   confirmationID;


	std::string                                   confirmationIDLimits;

	// Obiekt odpowiedzialny za przetwarzanie potwierdzen
	std::unique_ptr<tlinsMoveServerInterfaceConfirmation> confirmationCallbacks;

	// Callback potwierdzen limitow
	std::shared_ptr<tlinsMoveServerInterfaceLimitsConfirmation> limitsConfirmationCallbacks;

  public:
	enum class StatusCode : int { SUCCESS = 0, WARNING = 1, ERROR = 2 };

	struct Status {
		StatusCode  status;
		int         errorCode;
		std::string errorDescription;

		Status &operator=(const Status &v)
		{
			status           = v.status;
			errorCode        = v.errorCode;
			errorDescription = v.errorDescription;
			return *this;
		}

		Status(const Status &v)
		{
			*this = v;
		}

		Status()
		{
			status           = StatusCode::SUCCESS;
			errorCode        = 0;
			errorDescription = std::string("OK");
		}
	};

  public:
	//
	// Rzadanie przemieszczenia
	//
	enum class RequestDirection { LEFT = 1, RIGHT = 2 };

	enum class MoveType { MOVE = 1, SPEED = 2, STOP = 3, ABORT = 4 };

	enum class InterpolationType { NONE = 1, LINEAR = 2 };

	enum class ModeRelAbs { REL = 1, ABS = 2 };

	enum class RequestCtrl {
		CTRL_REQUEST                  = 1,
		CTRL_ABORT                    = 2,
		CTRL_ERASE_ALL_QUEUES         = 3,
		CTRL_ERASE_REQUEST_QUEUE      = 4,
		CTRL_ERASE_REQUEST_CTRL_QUEUE = 5,
		CTRL_END                      = 6
	};

	class MoveRequestItem {
	  private:
		long             V;
		long             distance;
		long             A;
		long             D;
		RequestDirection direction;

	  public:
		__GET__(long, V);
		__GET__(long, distance);
		__GET__(long, A);
		__GET__(long, D);
		__GET__(RequestDirection, direction);

		__SET__(long, V);
		__SET__(long, distance);
		__SET__(long, A);
		__SET__(long, D);
		__SET__(RequestDirection, direction);

		MoveRequestItem &operator=(const MoveRequestItem &v);

		MoveRequestItem(const MoveRequestItem &v);
		MoveRequestItem();
		virtual ~MoveRequestItem();
	};

	class MoveRequestDevice {
	  private:
		long V;
		long distance;
		long A;
		long D;

		MoveType                               moveType;
		InterpolationType                      interpolationType;
		ModeRelAbs                             relAbs;
		std::map<std::string, MoveRequestItem> requestItems;

	  public:
		__GET__(long, V);
		__GET__(long, distance);
		__GET__(long, A);
		__GET__(long, D);
		__GET__(MoveType, moveType);
		__GET__(InterpolationType, interpolationType);
		__GET__(ModeRelAbs, relAbs);

		__SET__(long, V);
		__SET__(long, distance);
		__SET__(long, A);
		__SET__(long, D);
		__SET__(MoveType, moveType);
		__SET__(InterpolationType, interpolationType);
		__SET__(ModeRelAbs, relAbs);

		std::map<std::string, MoveRequestItem> &getRequestItems()
		{
			return requestItems;
		}

		MoveRequestItem &add(const std::string &axis);

		MoveRequestDevice();
		virtual ~MoveRequestDevice();
	};

  public:
	class tlinsDeviceAxisInfo {
	  private:
		std::string axisName;
		long        encoderResolution;
		long        deviceResolution;

		long linearA;
		long linearD;
		long positionA;
		long positionD;
		long positionV;
		long speedA;
		long speedD;
		long speedV;

	  public:
		__GET__(std::string, axisName);
		__GET__(long, encoderResolution);
		__GET__(long, deviceResolution);

		__GET__(long, linearA);
		__GET__(long, linearD);
		__GET__(long, positionA);
		__GET__(long, positionD);
		__GET__(long, positionV);
		__GET__(long, speedA);
		__GET__(long, speedD);
		__GET__(long, speedV);

		__SET__(std::string, axisName);
		__SET__(long, encoderResolution);
		__SET__(long, deviceResolution);

		__SET__(long, linearA);
		__SET__(long, linearD);
		__SET__(long, positionA);
		__SET__(long, positionD);
		__SET__(long, positionV);
		__SET__(long, speedA);
		__SET__(long, speedD);
		__SET__(long, speedV);

		tlinsDeviceAxisInfo &operator=(const tlinsDeviceAxisInfo &v);
		tlinsDeviceAxisInfo(const tlinsDeviceAxisInfo &v);
		tlinsDeviceAxisInfo()          = default;
		virtual ~tlinsDeviceAxisInfo() = default;
	};

  public:
	//
	// Tryb poizycjonowania
	//
	enum tlinsSerialDeviceMode { AXIS = 0, SYNCHRONISED = 1 };

	//
	// Informacja o pozycji pojedynczej osi
	//
	enum class tlinsSerialMotorStatus {
		MOTOR_OFF                    = 0,
		MOTOR_ON                     = 1,
		MOTOR_SPEED_MODE             = 2,
		MOTOR_POSITION_MODE          = 3,
		MOTOR_REACHED_POSITION       = 4,
		MOTOR_ERROR_POSITION_ENCODER = 5,
		MOTOR_ERROR_HOME_MODE        = 6,
		MOTOR_CORRECTION_MODE        = 8,
		MOTOR_MAX                    = 9
	};

	class AxisPositionInfo {
	  private:
		std::string axisName;

		long position;
		long positionEncoder;

		long                   rawPosition;
		long                   rawPositionEncoder;
		tlinsSerialMotorStatus devStatus;

	  public:
		__GET__(std::string, axisName);
		__GET__(long, position);
		__GET__(long, positionEncoder);

		__GET__(long, rawPosition);
		__GET__(long, rawPositionEncoder);

		__GET__(tlinsSerialMotorStatus, devStatus);

		__SET__(std::string, axisName);
		__SET__(long, position);
		__SET__(long, positionEncoder);

		__SET__(long, rawPosition);
		__SET__(long, rawPositionEncoder);

		__SET__(tlinsSerialMotorStatus, devStatus);

		AxisPositionInfo &operator=(const AxisPositionInfo &v) = default;
		AxisPositionInfo(const AxisPositionInfo &v)            = default;
		__DEF_CONSTRUCTOR__(AxisPositionInfo);

		virtual ~AxisPositionInfo() = default;
	};

  private:
	// ++
	std::string registerConfirmation();


	//
	std::string registerLimitConfirmation(const std::string &deviceName);

  public:
	//
	// Rzadanie przemieszczania
	//
	class tlinsMoveRequestConfirmation : public tlinsMoveServerInterfaceCallBack {
	  private:
		std::mutex              mtx;
		std::condition_variable cv;
		std::atomic<bool>       isSet{false};
		int                     requestId;

	  public:
		void setRequestId(const int v)
		{
			requestId = v;
			isSet     = true;
			cv.notify_all();
		}

		void waitForSet()
		{
			if (isSet)
				return;

			std::unique_lock<std::mutex> lock(mtx);
			cv.wait(lock);
		}

		int getRequestId() const
		{
			return requestId;
		}

		tlinsMoveRequestConfirmation()          = default;
		virtual ~tlinsMoveRequestConfirmation() = default;
	};

	//
	//
	//

	void flushCallbacks();

	void moveRequest(const std::string &deviceName, MoveRequestDevice &requests,
	                 std::shared_ptr<tlinsMoveRequestConfirmation> &cb);

	//
	// Informacja o pozycji urzadzenia
	//
	void positionInfo(const std::string &deviceName, std::map<std::string, AxisPositionInfo> &result);

	//
	// Konfiguracja urzadzenia
	//
	void deviceConfiguration(const std::string &deviceName, std::map<std::string, tlinsDeviceAxisInfo> &result);

	//
	// Ustawienie pozycji osi silnika
	//
	void setPosition(const std::string &deviceName, std::map<std::string, AxisPositionInfo> &axis);

	//
	// Ustawienie/pobranie sposobu pozycjonowania
	//
	void setMoveMode(const std::string &deviceName, const tlinsSerialDeviceMode mode);

	void getMoveMode(const std::string &deviceName, tlinsSerialDeviceMode &mode);

	//
	// Ustawinie czasu systemu
	//
	void setDateTime(const int year, const int month, const int day, const int hour, const int minute,
	                 const int second);

	//
	// Zestaw API do zarzadzania limitami pozycji
	//
	void registerLimitAlarm(const std::string &deviceName, std::shared_ptr<tlinsMoveServerLimitsInterfaceCallBack> &cb);

	//
	// Konstruktor destruktor klasy
	//
	tlinsMoveServerInterface() = default;
	tlinsMoveServerInterface(std::shared_ptr<grpc::Channel> &channel, std::shared_ptr<grpc::Channel> &channelConf);
	virtual ~tlinsMoveServerInterface();
};

#endif
