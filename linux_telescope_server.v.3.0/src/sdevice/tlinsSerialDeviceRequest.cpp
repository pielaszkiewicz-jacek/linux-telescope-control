#include <tlinsBacktrace.hpp>
#include <tlinsSerialDeviceRequest.hpp>

unsigned long tlinsSerialDeviceBaseRequest::requestsCount = 0;
std::mutex    tlinsSerialDeviceBaseRequest::requestIdMutex;

unsigned long tlinsSerialDeviceBaseRequest::getRequestID() const
{
	return requestID;
}

unsigned long tlinsSerialDeviceBaseRequest::getNextRequestId()
{
	std::lock_guard<std::mutex> guard(tlinsSerialDeviceBaseRequest::requestIdMutex);
	tlinsSerialDeviceBaseRequest::requestsCount++;
	return tlinsSerialDeviceBaseRequest::requestsCount;
}

tlinsSerialDeviceBaseRequest &tlinsSerialDeviceBaseRequest::operator=(const tlinsSerialDeviceBaseRequest &v)
{
	requestID = v.requestID;
	return *this;
}

tlinsSerialDeviceBaseRequest::tlinsSerialDeviceBaseRequest()
{
	requestID = tlinsSerialDeviceBaseRequest::getNextRequestId();
}

//
// ---------------------------------------------------------
// ---------------------------------------------------------
//

unsigned long tlinsSerialDevicePositionRequestAxis::getA() const
{
	return A;
}

unsigned long tlinsSerialDevicePositionRequestAxis::getD() const
{
	return D;
}

unsigned long tlinsSerialDevicePositionRequestAxis::getV() const
{
	return V;
}

tlinsSerialDirection tlinsSerialDevicePositionRequestAxis::getDirection() const
{
	return direction;
}

unsigned long tlinsSerialDevicePositionRequestAxis::getDistance() const
{
	return distance;
}

tlinsSerialDevicePositionRequestAxis &
tlinsSerialDevicePositionRequestAxis::operator=(const tlinsSerialDevicePositionRequestAxis &v)
{
	A         = v.A;
	D         = v.D;
	V         = v.V;
	direction = v.direction;
	distance  = v.distance;
	return *this;
}

tlinsSerialDevicePositionRequestAxis::tlinsSerialDevicePositionRequestAxis()
{
	A         = 0;
	D         = 0;
	V         = 0;
	distance  = 0;
	direction = tlinsSerialDirection::LAST;
}

tlinsSerialDevicePositionRequestAxis::tlinsSerialDevicePositionRequestAxis(const unsigned long        A_,
                                                                           const unsigned long        D_,
                                                                           const unsigned long        V_,
                                                                           const tlinsSerialDirection direction_,
                                                                           const unsigned long        move_)
{
	V         = V_;
	A         = A_;
	D         = D_;
	distance  = move_;
	direction = direction_;
}

tlinsSerialDevicePositionRequestAxis::tlinsSerialDevicePositionRequestAxis(
    const tlinsSerialDevicePositionRequestAxis &v)
{
	*this = v;
}

//
// ---------------------------------------------------------
// ---------------------------------------------------------
//

void tlinsSerialDeviceMoveRequest::append(const std::string &axis, const tlinsSerialDevicePositionRequestAxis &v)
{
	requestDetails[axis] = v;
}

int tlinsSerialDeviceMoveRequest::getSize() const
{
	return requestDetails.size();
}

tlinsSerialDevicePositionRequestAxis &tlinsSerialDeviceMoveRequest::operator[](const std::string &idx)
{
	if (requestDetails.find(idx) == requestDetails.end()) {
		__THROW__(tlinsSerialDeviceException("No object", tlinsSerialDeviceException::ERROR_OUT_OF_INDEX_RANGE));
	}
	return requestDetails[idx];
}

tlinsSerialMoveType tlinsSerialDeviceMoveRequest::getMode() const
{
	return mode;
}

tlinsSerialMoveInterpolationType tlinsSerialDeviceMoveRequest::getInterpolationType() const
{
	return interpolationType;
}

unsigned long tlinsSerialDeviceMoveRequest::getA() const
{
	return A;
}

unsigned long tlinsSerialDeviceMoveRequest::getD() const
{
	return D;
}

unsigned long tlinsSerialDeviceMoveRequest::getV() const
{
	return V;
}

const std::string &tlinsSerialDeviceMoveRequest::getMainDevice() const
{
	return mainDeviceName;
}

void tlinsSerialDeviceMoveRequest::setConfirmationId(const std::string &s)
{
	confirmationId  = s;
	hasConfirmation = true;
}

tlinsSerialDeviceMoveRequest &tlinsSerialDeviceMoveRequest::operator=(const tlinsSerialDeviceMoveRequest &v)
{
	requestDetails.erase(requestDetails.begin(), requestDetails.end());

	requestDetails.clear();
	for (auto i = v.requestDetails.begin(); i != v.requestDetails.end(); i++) {
		requestDetails[i->first] = i->second;
	}

	confirmationId    = v.confirmationId;
	hasConfirmation   = v.hasConfirmation;
	mode              = v.mode;
	interpolationType = v.interpolationType;
	moveType          = v.moveType;
	A                 = v.A;
	D                 = v.D;
	V                 = v.V;

	return *this;
}

std::map<std::string, tlinsSerialDevicePositionRequestAxis>::iterator tlinsSerialDeviceMoveRequest::begin()
{
	return requestDetails.begin();
}

std::map<std::string, tlinsSerialDevicePositionRequestAxis>::iterator tlinsSerialDeviceMoveRequest::end()
{
	return requestDetails.end();
}

std::map<std::string, tlinsSerialDevicePositionRequestAxis>::iterator
tlinsSerialDeviceMoveRequest::find(const std::string &name)
{
	return requestDetails.find(name);
}

tlinsSerialDeviceMoveRequest::tlinsSerialDeviceMoveRequest(const tlinsSerialDeviceMoveRequest &v)
{
	*this = v;
}

tlinsSerialDeviceMoveRequest::tlinsSerialDeviceMoveRequest()
    : hasConfirmation{false},
      mode{tlinsSerialMoveType::LAST},
      interpolationType{tlinsSerialMoveInterpolationType::LAST},
      moveType{tlinsSerialMoveModeRelAbs::LAST},
      A{0},
      D{0},
      V{0}
{
}
			// std::shared_ptr<tlinsSerialDevice>(new tlinsSerialDevice(mainDevice));

tlinsSerialDeviceMoveRequest::tlinsSerialDeviceMoveRequest(const tlinsSerialMoveType              mode_,
                                                           const tlinsSerialMoveInterpolationType interpolationType_,
                                                           const tlinsSerialMoveModeRelAbs        moveType_,
                                                           const unsigned long A_, const unsigned long D_,
                                                           const unsigned long V_)
    : A{A_},
      D{D_},
      V{V_},
      mode{mode_},
      interpolationType{interpolationType_},
      moveType{moveType_},
      hasConfirmation{false}
{
}

tlinsSerialDeviceMoveRequest::~tlinsSerialDeviceMoveRequest()
{
}

//
// ---------------------------------------------------------
// ---------------------------------------------------------
//
const std::string &tlinsSerialDeviceCtrlRequest::getMainDeviceName() const
{
	return mainDeviceName;
}

const tlinsSerialDeviceCtrlRequestType tlinsSerialDeviceCtrlRequest::getCtrlReqType() const
{
	return ctrlReqType;
}

const std::string &tlinsSerialDeviceCtrlRequest::getDescription() const
{
	return description;
}

tlinsSerialDeviceCtrlRequest &tlinsSerialDeviceCtrlRequest::operator=(const tlinsSerialDeviceCtrlRequest &v)
{
	mainDeviceName = v.mainDeviceName;
	ctrlReqType    = v.ctrlReqType;
	description    = v.description;
	return *this;
}

tlinsSerialDeviceCtrlRequest::tlinsSerialDeviceCtrlRequest()
{
	ctrlReqType = tlinsSerialDeviceCtrlRequestType::CTRL_MAX;
}

tlinsSerialDeviceCtrlRequest::tlinsSerialDeviceCtrlRequest(const tlinsSerialDeviceCtrlRequestType ctrlReqType_,
                                                           const std::string &                    description_,
                                                           const std::string &                    mainDevName_,
                                                           const std::vector<std::string> &       axies_)
{
	mainDeviceName = mainDevName_;
	ctrlReqType    = ctrlReqType_;
	description    = description_;
}

tlinsSerialDeviceCtrlRequest::tlinsSerialDeviceCtrlRequest(const tlinsSerialDeviceCtrlRequest &v)
{
	*this = v;
}

tlinsSerialDeviceCtrlRequest::~tlinsSerialDeviceCtrlRequest()
{
}
