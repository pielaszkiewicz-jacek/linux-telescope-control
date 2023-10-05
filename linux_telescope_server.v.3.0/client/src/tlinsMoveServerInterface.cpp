#include <tlinsBacktrace.hpp>
#include <tlinsInterfaceException.hpp>
#include <tlinsMoveServerInterface.hpp>

#include <grpc/impl/codegen/connectivity_state.h>

tlinsMoveServerInterface::tlinsDeviceAxisInfo &
tlinsMoveServerInterface::tlinsDeviceAxisInfo::operator=(const tlinsMoveServerInterface::tlinsDeviceAxisInfo &v)
{
	axisName          = v.axisName;
	encoderResolution = v.encoderResolution;
	deviceResolution  = v.deviceResolution;
	linearA           = v.linearA;
	linearD           = v.linearD;
	positionA         = v.positionA;
	positionD         = v.positionD;
	positionV         = v.positionV;
	speedA            = v.speedA;
	speedD            = v.speedD;
	speedV            = v.speedV;
	return *this;
}

tlinsMoveServerInterface::tlinsDeviceAxisInfo::tlinsDeviceAxisInfo(
    const tlinsMoveServerInterface::tlinsDeviceAxisInfo &v)
{
	axisName          = v.axisName;
	encoderResolution = v.encoderResolution;
	deviceResolution  = v.deviceResolution;
	linearA           = v.linearA;
	linearD           = v.linearD;
	positionA         = v.positionA;
	positionD         = v.positionD;
	positionV         = v.positionV;
	speedA            = v.speedA;
	speedD            = v.speedD;
	speedV            = v.speedV;
}

//
// ------
// ------
// ------
//
void tlinsMoveServerInterface::deviceConfiguration(const std::string                          &deviceName,
                                                   std::map<std::string, tlinsDeviceAxisInfo> &result)
{
	tlins::tlinsRpcMainDevicesName     request;
	tlins::tlinsRpcDeviceConfiguration response;
	grpc::ClientContext                context;

	request.set_devicename(deviceName);

	auto rc = connectionStub->getConfiguration(&context, request, &response);
	if (!rc.ok()) {
		// Blad rejestrowania potwierdzenia
		__THROW__(tlinsInterfaceException(std::string("Error read device configuration"),
		                                  tlinsInterfaceException::ERROR_RPC_ERROR));
	}

	if (response.status().status() != tlins::ErrorCodes::_ERROR_CODE_SUCCESS) {
		// Blad rejestrowania potwierdzenia
		__THROW__(tlinsInterfaceException(response.status().errordescription(),
		                                  tlinsInterfaceException::ERROR_REGISTER_CONFIRMATION));
	}

	// Poszczegolne skladowe rezultatu
	for (int i = 0; i < response.axies_size(); i++) {
		auto &ax = response.axies(i);

		tlinsDeviceAxisInfo axInfo;

		const auto &axName = ax.axisname();
		axInfo.set_axisName(axName);

		axInfo.set_encoderResolution(ax.encoderresolution().value());
		axInfo.set_deviceResolution(ax.stepsonresolution().value());
		axInfo.set_linearA(ax.lineara().value());
		axInfo.set_linearD(ax.lineard().value());
		axInfo.set_positionA(ax.positiona().value());
		axInfo.set_positionD(ax.positiond().value());
		axInfo.set_positionV(ax.positionv().value());
		axInfo.set_speedA(ax.speeda().value());
		axInfo.set_speedD(ax.speedd().value());
		axInfo.set_speedV(ax.speedv().value());

		// Add axies into result
		result[axName] = axInfo;
	}
}

void tlinsMoveServerInterface::setMoveMode(const std::string &deviceName, const tlinsSerialDeviceMode mode)
{
	tlins::tlinsRpcDeviceMode request;
	tlins::tlinsRpcStatus     response;
	grpc::ClientContext       context;

	// Nazwa urzadzenia
	request.mutable_devicename()->set_value(deviceName);

	switch (mode) {
	case tlinsSerialDeviceMode::SYNCHRONISED:
		request.mutable_mode()->set_value(tlins::tlinsSerialDeviceMode::_SYNCHRONISED);
		break;

	case tlinsSerialDeviceMode::AXIS:
		request.mutable_mode()->set_value(tlins::tlinsSerialDeviceMode::_AXIS);
		break;
	}

	auto rc = connectionStub->setMoveMode(&context, request, &response);
	if (!rc.ok()) {
		// Blad rejestrowania potwierdzenia
		__THROW__(tlinsInterfaceException(std::string("Error read device configuration"),
		                                  tlinsInterfaceException::ERROR_RPC_ERROR));
	}

	if (response.status() != tlins::ErrorCodes::_ERROR_CODE_SUCCESS) {
		// Blad rejestrowania potwierdzenia
		__THROW__(
		    tlinsInterfaceException(response.errordescription(), tlinsInterfaceException::ERROR_SET_POSITION_MODE));
	}
}

void tlinsMoveServerInterface::getMoveMode(const std::string &deviceName, tlinsSerialDeviceMode &mode)
{
	tlins::tlinsStringValue         request;
	tlins::tlinsRpcDeviceModeStatus response;
	grpc::ClientContext             context;

	request.set_value(deviceName);
	auto rc = connectionStub->getMoveMode(&context, request, &response);
	if (!rc.ok()) {
		// Blad rejestrowania potwierdzenia
		__THROW__(tlinsInterfaceException(std::string("Error read device configuration"),
		                                  tlinsInterfaceException::ERROR_RPC_ERROR));
	}

	if (response.status().status() != tlins::ErrorCodes::_ERROR_CODE_SUCCESS) {
		__THROW__(tlinsInterfaceException(response.status().errordescription(),
		                                  tlinsInterfaceException::ERROR_GET_POSITION_MODE));
	}

	switch (response.mode().value()) {
	case tlins::tlinsSerialDeviceMode::_AXIS:
		mode = tlinsSerialDeviceMode::AXIS;
		break;

	case tlins::tlinsSerialDeviceMode::_SYNCHRONISED:
		mode = tlinsSerialDeviceMode::SYNCHRONISED;
	}
}

void tlinsMoveServerInterface::setPosition(const std::string &deviceName,
                                           std::map<std::string, tlinsMoveServerInterface::AxisPositionInfo> &axies)
{
	tlins::tlinsRpcPosition request;
	tlins::tlinsRpcStatus   response;
	grpc::ClientContext     context;

	// Nazwa urzadzenia glownego
	request.mutable_devicename()->set_value(deviceName);
	for (auto &iter : axies) {
		auto &item = iter.second;

		// Nazwa osi
		std::string aName = item.get_axisName();

		auto outAxis = request.add_axies();
		outAxis->set_axisname(aName);
		outAxis->set_encoderpostion(item.get_positionEncoder());
		outAxis->set_motorpostion(item.get_position());
	}

	auto rc = connectionStub->setPosition(&context, request, &response);
	if (!rc.ok()) {
		// Blad rejestrowania potwierdzenia
		__THROW__(tlinsInterfaceException(std::string("Error set position"), tlinsInterfaceException::ERROR_RPC_ERROR));
	}

	if (response.status() != tlins::ErrorCodes::_ERROR_CODE_SUCCESS) {
		// Blad rejestrowania potwierdzenia
		__THROW__(
		    tlinsInterfaceException(response.errordescription(), tlinsInterfaceException::ERROR_REGISTER_CONFIRMATION));
	}
}

void tlinsMoveServerInterface::setDateTime(const int year, const int month, const int day, const int hour,
                                           const int minute, const int second)
{
	tlins::tlinsRpcDateTime request;
	tlins::tlinsRpcStatus   response;
	grpc::ClientContext     context;

	request.mutable_year()->set_value(year);
	request.mutable_month()->set_value(month);
	request.mutable_day()->set_value(day);
	request.mutable_hour()->set_value(hour);
	request.mutable_minute()->set_value(minute);
	request.mutable_second()->set_value(second);

	auto rc = connectionStub->setDateTime(&context, request, &response);
	if (!rc.ok()) {
		// Blad rejestrowania potwierdzenia
		__THROW__(
		    tlinsInterfaceException(std::string("Error set date/time"), tlinsInterfaceException::ERROR_RPC_ERROR));
	}

	if (response.status() != tlins::ErrorCodes::_ERROR_CODE_SUCCESS) {
		// Blad rejestrowania potwierdzenia
		__THROW__(tlinsInterfaceException(response.errordescription(), tlinsInterfaceException::ERROR_SET_DATE_TIME));
	}
}

void tlinsMoveServerInterface::positionInfo(const std::string                       &deviceName,
                                            std::map<std::string, AxisPositionInfo> &result)
{
	tlins::tlinsRpcMainDevicesName request;
	tlins::tlinsRpcPositionInfo    response;
	grpc::ClientContext            context;

	request.set_devicename(deviceName);

	auto rc = connectionStub->getPosition(&context, request, &response);
	if (!rc.ok()) {
		// Blad rejestrowania potwierdzenia
		__THROW__(
		    tlinsInterfaceException(std::string("Error read position info"), tlinsInterfaceException::ERROR_RPC_ERROR));
	}

	if (response.status().status() != tlins::ErrorCodes::_ERROR_CODE_SUCCESS) {
		// Blad rejestrowania potwierdzenia
		__THROW__(tlinsInterfaceException(response.status().errordescription(),
		                                  tlinsInterfaceException::ERROR_REGISTER_CONFIRMATION));
	}

	// Poszczegolne skladowe rezultatu
	for (int i = 0; i < response.axies_size(); i++) {
		auto &ax = response.axies(i);

		AxisPositionInfo axInfo;
		auto             axName = ax.axisname();
		axInfo.set_axisName(axName);

		axInfo.set_positionEncoder(ax.encoderpostion());
		axInfo.set_position(ax.motorpostion());

		axInfo.set_rawPositionEncoder(ax.rawencoderpostion());
		axInfo.set_rawPosition(ax.rawmotorpostion());

		// axInfo.setdevStatus(static_cast<tlinsSerialMotorStatus>(ax.devicestatus()));

		// Add axies into result
		result[axName] = axInfo;
	}
}

std::string tlinsMoveServerInterface::registerConfirmation()
{
	tlins::tlinsConfirmationHandlerResult response;
	tlins::Void                           request;
	grpc::ClientContext                   context;

	auto result = connectionStub->createConfirmation(&context, request, &response);
	if (!result.ok()) {
		// Blad rejestrowania potwierdzenia
		__THROW__(tlinsInterfaceException(std::string("Error creating confirmation"),
		                                  tlinsInterfaceException::ERROR_RPC_ERROR));
	}

	// Status odpowiedzi
	auto errorCode        = response.status().errorcode();
	auto errorDescription = response.status().errordescription();
	auto status           = response.status().status();

	if (status != tlins::ErrorCodes::_ERROR_CODE_SUCCESS) {
		// Blad rejestrowania potwierdzenia
		__THROW__(tlinsInterfaceException(errorDescription, tlinsInterfaceException::ERROR_REGISTER_CONFIRMATION));
	}
	return response.handler().handler();
}

std::string tlinsMoveServerInterface::registerLimitConfirmation(const std::string &deviceName)
{
	tlins::tlinsConfirmationHandlerResult response;
	tlins::tlinsStringValue               request;
	grpc::ClientContext                   context;

	request.set_value(deviceName);
	auto result = connectionStub->colistionsDetectionConfirmationCreate(&context, request, &response);
	if (!result.ok()) {
		// Blad rejestrowania potwierdzenia
		__THROW__(tlinsInterfaceException(std::string("Error creating limit confirmation"),
		                                  tlinsInterfaceException::ERROR_RPC_ERROR));
	}

	// Status odpowiedzi
	auto errorCode        = response.status().errorcode();
	auto errorDescription = response.status().errordescription();
	auto status           = response.status().status();

	if (status != tlins::ErrorCodes::_ERROR_CODE_SUCCESS) {
		// Blad rejestrowania potwierdzenia
		__THROW__(tlinsInterfaceException(errorDescription, tlinsInterfaceException::ERROR_REGISTER_CONFIRMATION));
	}
	return response.handler().handler();
}

void tlinsMoveServerInterface::flushCallbacks()
{
	confirmationCallbacks->flush();
}

void tlinsMoveServerInterface::moveRequest(const std::string                             &deviceName,
                                           tlinsMoveServerInterface::MoveRequestDevice   &req,
                                           std::shared_ptr<tlinsMoveRequestConfirmation> &cb)
{
	tlins::tlinsRpcMoveRequest request;
	tlins::tlinsRpcMoveStatus  response;

	// Identyfikator potwierdzenias
	request.mutable_confirmationhandler()->set_handler(confirmationID);

	request.mutable_maindevicename()->set_value(deviceName);
	request.mutable_a()->set_value(__get__(req, A));
	request.mutable_d()->set_value(__get__(req, D));
	request.mutable_v()->set_value(__get__(req, V));

	// Typ przemieszczenia
	switch (__get__(req, moveType)) {
	case tlinsMoveServerInterface::MoveType::MOVE:
		request.mutable_mode()->set_value(tlins::tlinsSerialMoveType::_POSITION);
		break;

	case tlinsMoveServerInterface::MoveType::SPEED:
		request.mutable_mode()->set_value(tlins::tlinsSerialMoveType::_SPEED);
		break;

	case tlinsMoveServerInterface::MoveType::STOP:
		request.mutable_mode()->set_value(tlins::tlinsSerialMoveType::_STOP);
		break;

	case tlinsMoveServerInterface::MoveType::ABORT:
		request.mutable_mode()->set_value(tlins::tlinsSerialMoveType::_ABORT);
		break;
	}

	// Typ interpolacji
	switch (__get__(req, interpolationType)) {
	case tlinsMoveServerInterface::InterpolationType::NONE:
		request.mutable_interpolationtype()->set_value(tlins::tlinsSerialMoveInterpolationType::_NONE);
		break;

	case tlinsMoveServerInterface::InterpolationType::LINEAR:
		request.mutable_interpolationtype()->set_value(tlins::tlinsSerialMoveInterpolationType::_LINEAR);
		break;
	}

	// Przemieszczenie absolutne/realtywne
	switch (__get__(req, relAbs)) {
	case tlinsMoveServerInterface::ModeRelAbs::REL:
		request.mutable_movetype()->set_value(tlins::tlinsSerialMoveModeRelAbs::_REL);
		break;

	case tlinsMoveServerInterface::ModeRelAbs::ABS:
		request.mutable_movetype()->set_value(tlins::tlinsSerialMoveModeRelAbs::_ABS);
		break;
	}

	// Poszczegolne osie
	for (auto &item : req.getRequestItems()) {
		auto axis = request.add_requestdetails();

		axis->mutable_axisname()->set_value(item.first);
		axis->mutable_a()->set_value(__get__(item.second, A));
		axis->mutable_d()->set_value(__get__(item.second, D));
		axis->mutable_v()->set_value(__get__(item.second, V));

		switch (__get__(item.second, direction)) {
		case tlinsMoveServerInterface::RequestDirection::LEFT:
			axis->mutable_direction()->set_value(tlins::tlinsMoveDirection::_LEFT);
			break;

		case tlinsMoveServerInterface::RequestDirection::RIGHT:
			axis->mutable_direction()->set_value(tlins::tlinsMoveDirection::_RIGHT);
			break;
		}
		axis->mutable_distance()->set_value(__get__(item.second, distance));
	}

	// Rejestracja callback'a
	long rId = -1;
	if (cb) {
		rId = confirmationCallbacks->registerCallback(cb);
	}

	// Identyfikator rzadania uzytkownika
	request.set_userrequestid(rId);

	// Wyslanie rzadania
	grpc::ClientContext context;
	auto                result = connectionStub->setMoveRequest(&context, request, &response);
	if (!result.ok()) {
		// Blad rejestrowania potwierdzenia
		__THROW__(
		    tlinsInterfaceException(std::string("Error add move request"), tlinsInterfaceException::ERROR_RPC_ERROR));
	}
	if (cb) {
		cb->setRequestId(response.requestid());
	}

	if (response.status().status() != tlins::ErrorCodes::_ERROR_CODE_SUCCESS) {
		// Blad rejestrowania potwierdzenia
		__THROW__(tlinsInterfaceException(response.status().errordescription(),
		                                  tlinsInterfaceException::ERROR_REGISTER_CONFIRMATION));
	}
}

//
// -------------------
// Obsluga limitow ---
// -------------------
//
// Wlaczenie wylaczenie limitow
void tlinsMoveServerInterface::colistionsDetectionEnable(const std::string &deviceName)
{
	tlins::tlinsRpcStatus   response;
	tlins::tlinsStringValue request;
	grpc::ClientContext     context;

	// Nazwa urzadzenia
	request.set_value(deviceName);

	// Wyslanie rzadania
	auto result = connectionStub->colistionsDetectionEnable(&context, request, &response);
	if (!result.ok()) {
		// Blad rejestrowania potwierdzenia
		__THROW__(tlinsInterfaceException(std::string("Error disable colltion engine"), tlinsInterfaceException::ERROR_RPC_ERROR));
	}

	if (response.status() != tlins::ErrorCodes::_ERROR_CODE_SUCCESS) {
		// Blad rejestrowania potwierdzenia
		__THROW__(tlinsInterfaceException(response.errordescription(), tlinsInterfaceException::ERROR_ENABLE_COLLITION_ENGINE));
	}
}

void tlinsMoveServerInterface::colistionsDetectionDisable(const std::string &deviceName)
{
	tlins::tlinsRpcStatus   response;
	tlins::tlinsStringValue request;
	grpc::ClientContext     context;

	// Nazwa urzadzenia
	request.set_value(deviceName);

	// Wyslanie rzadania
	auto result = connectionStub->colistionsDetectionDisable(&context, request, &response);
	if (!result.ok()) {
		// Blad rejestrowania potwierdzenia
		__THROW__(tlinsInterfaceException(std::string("Error disable colltion engine"), tlinsInterfaceException::ERROR_RPC_ERROR));
	}

	if (response.status() != tlins::ErrorCodes::_ERROR_CODE_SUCCESS) {
		// Blad rejestrowania potwierdzenia
		__THROW__(tlinsInterfaceException(response.errordescription(), tlinsInterfaceException::ERROR_DISABLE_COLLITION_ENGINE));
	}
}

void tlinsMoveServerInterface::colistionsDetectionSetLimits(const std::string &deviceName, const std::vector<std::pair<Eigen::Vector3d, Eigen::Vector3d>> &limits)
{
	tlins::tlinsRpcStatus response;
	tlins::tlinsLimits    request;
	grpc::ClientContext   context;

	// Nazwa urzadzenia
	request.mutable_devicename() -> set_value(deviceName);

	// Dodanie poszczegolnych limitow do rzadania
	for(auto &item: limits) {
		auto newItem = request.add_limits();
		auto start   = newItem -> mutable_start();
		auto end     = newItem -> mutable_end();

		start -> mutable_a1() -> set_value(item.first(0));
		start -> mutable_a2() -> set_value(item.first(1));
		start -> mutable_a3() -> set_value(item.first(2));
		end   -> mutable_a1() -> set_value(item.second(0));
		end   -> mutable_a2() -> set_value(item.second(1));
		end   -> mutable_a3() -> set_value(item.second(2));
	}

	// Wyslanie rzadania
	auto result = connectionStub->colistionsDetectionSetLimits(&context, request, &response);
	if (!result.ok()) {
		// Blad rejestrowania potwierdzenia
		__THROW__(tlinsInterfaceException(std::string("Error set collistion limits"), tlinsInterfaceException::ERROR_RPC_ERROR));
	}

	if (response.status() != tlins::ErrorCodes::_ERROR_CODE_SUCCESS) {
		// Blad rejestrowania potwierdzenia
		__THROW__(tlinsInterfaceException(response.errordescription(), tlinsInterfaceException::ERROR_SET_COLLITION_LIMITS));
	}
}

std::vector<std::pair<Eigen::Vector3d, Eigen::Vector3d>> tlinsMoveServerInterface::colistionsDetectionGetLimits(const std::string &deviceName)
{
	tlins::tlinsStringValue  request;
	tlins::tlinsLimitsResult response;
	grpc::ClientContext      context;

	// Nazwa urzadzenia
	request.set_value(deviceName);

	// Wyslanie rzadania
	auto result = connectionStub->colistionsDetectionGetLimits(&context, request, &response);
	if (!result.ok()) {
		// Blad rejestrowania potwierdzenia
		__THROW__(tlinsInterfaceException(std::string("Error set collistion limits"), tlinsInterfaceException::ERROR_RPC_ERROR));
	}

	if (response.result().status() != tlins::ErrorCodes::_ERROR_CODE_SUCCESS) {
		// Blad rejestrowania potwierdzenia
		__THROW__(tlinsInterfaceException(response.result().errordescription(), tlinsInterfaceException::ERROR_SET_COLLITION_LIMITS));
	}

	std::vector<std::pair<Eigen::Vector3d, Eigen::Vector3d>> ret{};
	for(int i = 0; i < response.limits_size(); i++) {
		Eigen::Vector3d start{
			response.limits(i).start().a1().value(),
			response.limits(i).start().a2().value(),
			response.limits(i).start().a2().value()};

		Eigen::Vector3d end{
			response.limits(i).end().a1().value(),
			response.limits(i).end().a2().value(),
			response.limits(i).end().a2().value()};

		ret.push_back(std::pair<Eigen::Vector3d, Eigen::Vector3d>{start, end});
	}
	return ret;
}

bool tlinsMoveServerInterface::colistionsDetectionTest(const std::string &deviceName, const Eigen::Vector3d &pos)
{
	tlins::tlinsTestLimit       request;
	tlins::tlinsTestLimitResult response;
	grpc::ClientContext         context;

	// Nazwa urzadzenia
	request.mutable_devicename() -> set_value(deviceName);

	auto rpos = request.mutable_position();
	rpos -> mutable_a1() -> set_value(pos(0));
	rpos -> mutable_a2() -> set_value(pos(1));
	rpos -> mutable_a3() -> set_value(pos(2));

	// Wyslanie rzadania
	auto result = connectionStub->colistionsDetectionTest(&context, request, &response);
	if (!result.ok()) {
		// Blad rejestrowania potwierdzenia
		__THROW__(tlinsInterfaceException(std::string("Error set collistion limits"), tlinsInterfaceException::ERROR_RPC_ERROR));
	}

	if (response.result().status() != tlins::ErrorCodes::_ERROR_CODE_SUCCESS) {
		// Blad rejestrowania potwierdzenia
		__THROW__(tlinsInterfaceException(response.result().errordescription(), tlinsInterfaceException::ERROR_SET_COLLITION_LIMITS));
	}
	return response.limitstatus().value();
}

void tlinsMoveServerInterface::colistionsRegisterAlarm(const std::string &deviceName, std::shared_ptr<tlinsMoveServerLimitsInterfaceCallBack> &cb)
{
	limitsConfirmationCallbacks -> registerCallback(deviceName, cb);

	// tlins::tlinsStringValue               request;
	// tlins::tlinsConfirmationHandlerResult response;

	// request.set_value(deviceName);

	// grpc::ClientContext context;
	// auto                result = connectionStub->colistionsDetectionConfirmationCreate(&context, request, &response);

	// if (!result.ok()) {
	// 	// Blad rejestrowania potwierdzenia
	// 	__THROW__(
	// 	    tlinsInterfaceException(std::string("Error add move request"), tlinsInterfaceException::ERROR_RPC_ERROR));
	// }

	// // Pobranie rezultatu
	// if (response.status().status() != tlins::ErrorCodes::_ERROR_CODE_SUCCESS) {
	// 	// Blad rejestrowania potwierdzenia
	// 	__THROW__(tlinsInterfaceException(response.status().errordescription(),
	// 	                                  tlinsInterfaceException::ERROR_REGISTER_CONFIRMATION));
	// }

	// // TODO
	// // TODO
	// // TODO
	// // TODO
	// // TODO
	// // TODO
	// // TODO
	// // TODO
	// // TODO
	// // TODO
}


//
// -----------------
// -----------------
// -----------------
//

void tlinsMoveServerInterfaceConfirmation::flush()
{
	std::lock_guard<std::mutex> lock(mtx);
	confirmationsCallbacksMap.clear();
}

long tlinsMoveServerInterfaceConfirmation::registerCallback(std::shared_ptr<tlinsMoveServerInterfaceCallBack> cb)
{
	static long id = 0;

	std::lock_guard<std::mutex> lock(mtx);
	id++;

	cb->setId(id);
	// confirmationsCallbacks.push_back(cb);

	// ++ Nowa implementacja
	// Rejestracja potwierdzenia
	confirmationsCallbacksMap[id] = cb;

	return id;
}

// Petla glowna realizujaca przetwarzanie potwierdzen
void tlinsMoveServerInterfaceConfirmation::operator()()
{
	tlins::tlinsConfirmationHandler handler;

	// Wywolanie zdalnej metody
	handler.set_handler(confirmId);
	reader = std::move(connectionStub->confirmation(&context, handler));
	ctxSet = true;

	// Efektywnie petla nieskonczona
	while (!end) {
		// Czytanie informacji od serwera
		tlins::tlinsRpcConfirmationStatus cStat;

		if (!reader->Read(&cStat)) {
			// Przerwanie petli - serwer zakonczyl przetwazanie
			break;
		}

		{
			std::lock_guard<std::mutex>                                  lock(mtx);
			std::list<std::shared_ptr<tlinsMoveServerInterfaceCallBack>> toLeave;

			// Wywolanie callbacka
			auto id = cStat.userrequestid();

			auto iter = confirmationsCallbacksMap.find(id);
			if (iter == confirmationsCallbacksMap.end()) {
				// Nie ma zarejestrowanego callbacka
				continue;
			}

			// Przetwarzanie callbacka
			iter->second->process(cStat);

			// Usuniecie callbacka z mapy
			confirmationsCallbacksMap.erase(iter);
		}
	}

	// Status
	auto status = reader->Finish();
}

tlinsMoveServerInterfaceConfirmation::tlinsMoveServerInterfaceConfirmation(std::shared_ptr<grpc::Channel> &channel,
                                                                           const std::string              &id)
    : reader(nullptr),
      connectionStub(tlins::tlinsRpcConfirmationService::NewStub(channel)),
      confirmId(id),
      end(false),
      thread(std::ref(*this))
{
	ctxSet = false;
}

// Destruktor klasy
tlinsMoveServerInterfaceConfirmation::~tlinsMoveServerInterfaceConfirmation()
{
	end = true;

	if (ctxSet)
		context.TryCancel();

	if (thread.joinable())
		thread.join();

	if (reader != nullptr)
		reader.reset();
}

//
// Obsluga powiadomien dotyczacych limitow pzycji
//
bool tlinsMoveServerInterfaceLimitsConfirmation::registerCallback(const std::string &devName, std::shared_ptr<tlinsMoveServerLimitsInterfaceCallBack> cb)
{
	std::lock_guard<std::mutex> lock(mtx);

	confirmationsCallbacksMap[devName].push_back(cb);
	return true;
}

void tlinsMoveServerInterfaceLimitsConfirmation::operator()()
{
	tlins::tlinsConfirmationHandler handler;

	// Wywolanie zdalnej metody
	handler.set_handler(confirmId);
	reader = std::move(connectionStub->confirmation(&context, handler));
	ctxSet = true;

	// Efektywnie petla nieskonczona
	while (!end) {
		// Czytanie informacji od serwera
		tlins::tlinsRpcConfirmationStatus cStat;

		if (!reader->Read(&cStat)) {
			// Przerwanie petli - serwer zakonczyl przetwazanie
			break;
		}

		{
			if(cStat.type() != tlins::tlinsSerialDeviceConfirmationType::_CONF_POSITION_LIMITS) {
				continue;
			}

			// Pobranie nazwy urzadzenia
			if(!cStat.has_positionlimit()) {
				continue;
			}
			auto devName = cStat.positionlimit().devicename();

			if(confirmationsCallbacksMap.count(devName) != 0) {
				auto iter = confirmationsCallbacksMap.find(devName);
				for(auto iter2: iter->second) {
					if(iter2 != nullptr) {
						iter2->process(cStat);
					}
				}
			}
		}
	}

	// Status
	auto status = reader->Finish();
}

void tlinsMoveServerInterfaceLimitsConfirmation::flush()
{
	std::lock_guard<std::mutex> lock(mtx);
	confirmationsCallbacksMap.clear();
}

tlinsMoveServerInterfaceLimitsConfirmation::tlinsMoveServerInterfaceLimitsConfirmation(std::shared_ptr<grpc::Channel> &channel, const std::string &id):
	reader(nullptr),
    connectionStub(tlins::tlinsRpcConfirmationService::NewStub(channel)),
    confirmId(id),
    end(false),
    thread(std::ref(*this))
{
	ctxSet = false;
}

tlinsMoveServerInterfaceLimitsConfirmation::~tlinsMoveServerInterfaceLimitsConfirmation()
{
	end = true;

	if (ctxSet)
		context.TryCancel();

	if (thread.joinable())
		thread.join();

	if (reader != nullptr)
		reader.reset();
}

//
// -----------------
// -----------------
// -----------------
//
tlinsMoveServerInterface::MoveRequestItem &
tlinsMoveServerInterface::MoveRequestItem::operator=(const MoveRequestItem &v)
{
	V         = v.V;
	distance  = v.distance;
	A         = v.A;
	D         = v.D;
	direction = v.direction;
	return *this;
}

tlinsMoveServerInterface::MoveRequestItem::MoveRequestItem(const MoveRequestItem &v)
{
	V         = v.V;
	distance  = v.distance;
	A         = v.A;
	D         = v.D;
	direction = v.direction;
}
tlinsMoveServerInterface::MoveRequestItem::MoveRequestItem()
{
	V         = 0;
	distance  = 0;
	A         = 0;
	D         = 0;
	direction = tlinsMoveServerInterface::RequestDirection::LEFT;
}
tlinsMoveServerInterface::MoveRequestItem::~MoveRequestItem()
{
}

tlinsMoveServerInterface::MoveRequestItem &tlinsMoveServerInterface::MoveRequestDevice::add(const std::string &axis)
{
	return requestItems[axis];
}

tlinsMoveServerInterface::MoveRequestDevice::MoveRequestDevice()
{
}

tlinsMoveServerInterface::MoveRequestDevice::~MoveRequestDevice()
{
}

//
// -----------------
// -----------------
// -----------------
//
tlinsMoveServerInterface::tlinsMoveServerInterface(std::shared_ptr<grpc::Channel> &channel,
                                                   std::shared_ptr<grpc::Channel> &channelConf)
{
	connectionStub        = tlins::tlinsRpcService::NewStub(channel);
	confirmationID        = registerConfirmation();
	{
		auto ptr              = new tlinsMoveServerInterfaceConfirmation{channelConf, confirmationID};
		confirmationCallbacks = std::unique_ptr<tlinsMoveServerInterfaceConfirmation>(ptr);
	}

	// Potwierdzenia zwiazane z limitami polozenia
	try {
		confirmationIDLimits        = registerLimitConfirmation(std::string{"main"});
		{
			auto ptr = new tlinsMoveServerInterfaceLimitsConfirmation{channelConf, confirmationIDLimits};
			limitsConfirmationCallbacks = std::unique_ptr<tlinsMoveServerInterfaceLimitsConfirmation>{ptr};
		}
	}
	catch(...) {
	}
}

tlinsMoveServerInterface::~tlinsMoveServerInterface()
{
}
