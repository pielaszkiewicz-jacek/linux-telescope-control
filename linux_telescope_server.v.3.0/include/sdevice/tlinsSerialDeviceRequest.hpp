#ifndef __tlinsSerialDeviceRequest_hpp__
#define __tlinsSerialDeviceRequest_hpp__

#include "tlinsBacktrace.hpp"
#include "tlinsSerialDeviceException.hpp"

#include <condition_variable>
#include <list>
#include <map>
#include <mutex>
#include <string>
#include <vector>

//
// ---------------------------------------------------------
// Abstrakcyjny interfejs typu przemieszczenie
// ---------------------------------------------------------
//

class tlinsSerialDeviceBaseRequest {
  private:
	// RequestID
	unsigned long requestID;

	static unsigned long requestsCount;
	static std::mutex    requestIdMutex;

	static unsigned long getNextRequestId();

  public:
	unsigned long                 getRequestID() const;
	tlinsSerialDeviceBaseRequest &operator=(const tlinsSerialDeviceBaseRequest &v);
	tlinsSerialDeviceBaseRequest();
	virtual ~tlinsSerialDeviceBaseRequest() = default;
};

//
// ---------------------------------------------------------
// Implementacja requestu typu przemieszczenie
// ---------------------------------------------------------
//
enum class tlinsSerialMoveType { SPEED = 1, POSITION, STOP, ABORT, STOP_CTRL, LAST };

enum class tlinsSerialMoveInterpolationType { LINEAR = 1, LAST };

enum class tlinsSerialMoveModeRelAbs { REL = 0, ABS = 1, LAST };

enum class tlinsSerialDirection { LEFT = 0, RIGHT = 1, LAST };

class tlinsSerialDevicePositionRequestAxis {
  private:
	// Przyspieszenie, hamowanie, predkosc
	unsigned long A;
	unsigned long D;
	unsigned long V;

	// Kierunek przemieszczenia
	tlinsSerialDirection direction;

	// Tablica pozycji
	unsigned long distance;

  public:
	// Przyspieszenie, hamowanie, predkosc
	unsigned long getA() const;
	unsigned long getD() const;
	unsigned long getV() const;
	void          setV(const unsigned long v)
	{
		V = v;
	}

	tlinsSerialDirection getDirection() const;

	// Wielkosc przemieszczenia
	unsigned long getDistance() const;

	tlinsSerialDevicePositionRequestAxis &operator=(const tlinsSerialDevicePositionRequestAxis &v);

	tlinsSerialDevicePositionRequestAxis();
	tlinsSerialDevicePositionRequestAxis(const tlinsSerialDevicePositionRequestAxis &v);
	tlinsSerialDevicePositionRequestAxis(const unsigned long A_, const unsigned long D_, const unsigned long V_,
	                                     const tlinsSerialDirection direction_, const unsigned long distance_);

	virtual ~tlinsSerialDevicePositionRequestAxis() = default;
};

class tlinsSerialDeviceMoveRequest : public tlinsSerialDeviceBaseRequest {
  private:
	// Skladowe przemieszczenia
	std::map<std::string, tlinsSerialDevicePositionRequestAxis> requestDetails;

	// Typ przemieszczenia
	tlinsSerialMoveType mode;

	// Rodzaj interpolacji ruchu
	tlinsSerialMoveInterpolationType interpolationType;

	// Rodzaj przemieszczenia - absolutne/relatywne
	tlinsSerialMoveModeRelAbs moveType;

	// Predkosc, przyspieszenie i hamowanie w trybie interpolacji ruchu
	unsigned long A;
	unsigned long D;
	unsigned long V;

	std::string mainDeviceName;

	std::string confirmationId;
	bool        hasConfirmation;

	long userRequestID;

  public:
	void setUserRequestID(const long userRequestID_)
	{
		userRequestID = userRequestID_;
	}

	long getUserRequestID() const
	{
		return userRequestID;
	}

	void setConfirmationId(const std::string &s);
	bool needConfirmation() const
	{
		return hasConfirmation;
	};

	std::string getConfirmationId() const
	{
		return confirmationId;
	};

	int getSize() const;

	// Wstawia nowa pozycje wektora przemieszczenia
	void append(const std::string &axis, const tlinsSerialDevicePositionRequestAxis &v);

	// Dostep do skladowych requestu
	tlinsSerialDevicePositionRequestAxis &operator[](const std::string &idx);

	std::map<std::string, tlinsSerialDevicePositionRequestAxis>::iterator begin();
	std::map<std::string, tlinsSerialDevicePositionRequestAxis>::iterator end();
	std::map<std::string, tlinsSerialDevicePositionRequestAxis>::iterator find(const std::string &name);

	// Typ rzadania
	tlinsSerialMoveType              getMode() const;
	tlinsSerialMoveInterpolationType getInterpolationType() const;
	tlinsSerialMoveModeRelAbs        getMoveType() const
	{
		return moveType;
	};

	const std::string &getMainDevice() const;

	unsigned long getA() const;
	unsigned long getD() const;
	unsigned long getV() const;

	tlinsSerialDeviceMoveRequest &operator=(const tlinsSerialDeviceMoveRequest &v);

	tlinsSerialDeviceMoveRequest();
	tlinsSerialDeviceMoveRequest(const tlinsSerialDeviceMoveRequest &v);
	tlinsSerialDeviceMoveRequest(const tlinsSerialMoveType              mode_,
	                             const tlinsSerialMoveInterpolationType interpolationType_,
	                             const tlinsSerialMoveModeRelAbs moveType_, const unsigned long A_,
	                             const unsigned long D_, const unsigned long V_);
	virtual ~tlinsSerialDeviceMoveRequest();
};


//
// ---------------------------
//
enum class tlinsSerialDeviceCtrlRequestType { CTRL_ABORT = 0, CTRL_RESTART = 2, CTRL_EXIT = 3, CTRL_MAX };

class tlinsSerialDeviceCtrlRequest : public tlinsSerialDeviceBaseRequest {
  private:
	tlinsSerialDeviceCtrlRequestType ctrlReqType;
	std::string                      description;

	// Urzadzenie glowne
	std::string mainDeviceName;

  public:
	const std::string &getMainDeviceName() const;

	const tlinsSerialDeviceCtrlRequestType getCtrlReqType() const;
	const std::string                     &getDescription() const;

	tlinsSerialDeviceCtrlRequest &operator=(const tlinsSerialDeviceCtrlRequest &v);

	tlinsSerialDeviceCtrlRequest();
	tlinsSerialDeviceCtrlRequest(const tlinsSerialDeviceCtrlRequestType ctrlReqType_, const std::string &description_,
	                             const std::string &mainDevName_, const std::vector<std::string> &axies_);
	tlinsSerialDeviceCtrlRequest(const tlinsSerialDeviceCtrlRequest &v);

	virtual ~tlinsSerialDeviceCtrlRequest();
};


//
// --------------------------------------
// --------------------------------------
// --------------------------------------
//

template <class T> class tlinsSerialQueue {
  private:
	std::list<std::shared_ptr<T>> queue;

	// Zmienna warunkowa
	std::mutex mtx;

  public:
	void enqueue(const std::shared_ptr<T> &v)
	{
		std::unique_lock<std::mutex> l(mtx);
		queue.push_back(v);
	};

	void enqueueFront(const std::shared_ptr<T> &v)
	{
		std::unique_lock<std::mutex> l(mtx);
		queue.push_front(v);
	};

	bool isEmpty()
	{
		return queue.empty();
	}

	// Metoda czeka i pobiera element z listy
	bool dequeue(std::shared_ptr<T> &v)
	{
		std::unique_lock<std::mutex> l(mtx);
		if (isEmpty())
			return false;

		v = queue.front();
		queue.pop_front();
		return true;
	};

	// Metoda pobiera element z wierzcholka listy
	bool getFront(std::shared_ptr<T> &v)
	{
		std::unique_lock<std::mutex> lock(mtx);
		if (isEmpty())
			return false;

		v = queue.front();
		return true;
	}

	void popFront()
	{
		std::unique_lock<std::mutex> lock(mtx);
		if (isEmpty())
			return;
		queue.pop_front();
	}

	void clear()
	{
		std::unique_lock<std::mutex> lock(mtx);
		queue.clear();
	};

	tlinsSerialQueue() = default;

	virtual ~tlinsSerialQueue()
	{
		clear();
	};
};

#endif
