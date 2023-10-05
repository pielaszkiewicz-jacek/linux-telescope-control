#include "tlins_math.hpp"
#include <tlinsBacktrace.hpp>
#include <tlinsLogger.hpp>
#include <tlinsSerialDevice.hpp>
#include <tlinsSerialServer.hpp>

#include "limits.hpp"
#include "tlinAttitudeUtilsClass.hpp"

#include <algorithm>
#include <chrono>
#include <condition_variable>
#include <string>
#include <time.h>

#include <chrono>
#include <set>

//
// ----------------------------------------------------------------------------------------
// Implementacja monitora kolizji
// ----------------------------------------------------------------------------------------
//
std::pair<Eigen::Vector3d, Eigen::Vector3d> MainDeviceLimit::positionLimitGetPosition(const double alfa,
                                                                                      const double beta)
{
	return limits::tlinsLimitsMath::kinematicsPositionGemetric2(
	    alfa, beta, deviceLimitConfiguration.r1, deviceLimitConfiguration.r2, deviceLimitConfiguration.dx,
	    deviceLimitConfiguration.dz, deviceLimitConfiguration.h, deviceLimitConfiguration.deviceMountAngles);
}

bool MainDeviceLimit::checkColision(const Eigen::Vector3d &position)
{
	// Pozycja w ukladzie sferycznym
	Eigen::Vector2d outPos;
	attitude::tlinAttitudeUtilsClass::toSpeherical(position, outPos);

	auto devicePosition = limits::tlinsLimitsMath::kinematicsPositionGemetric2(
	    outPos(0), outPos(1), deviceLimitConfiguration.r1, deviceLimitConfiguration.r2, deviceLimitConfiguration.dx,
	    deviceLimitConfiguration.dz, deviceLimitConfiguration.h, deviceLimitConfiguration.deviceMountAngles);

	// Detekcja kolizji z montazem teleskopu
	limits::tlinsLimitsMount limitsMountCalculator{
	    deviceLimitConfiguration.legs,        deviceLimitConfiguration.legRadius,
	    deviceLimitConfiguration.legsZOffset, deviceLimitConfiguration.legsStartAngle,
	    deviceLimitConfiguration.legsAngle,   deviceLimitConfiguration.baseRadius,
	    deviceLimitConfiguration.baseLength};

	// Sprawdzenie kolizji dla obu stron tubusa
	auto result1 = limitsMountCalculator.checkColistion(devicePosition.first);
	auto result2 = limitsMountCalculator.checkColistion(devicePosition.second);

	if (result1.first != limits::tlinsLimitsMount::colistionType::COLISTION_NONE ||
	    result1.first != limits::tlinsLimitsMount::colistionType::COLISTION_NONE) {
		return false;
	}
	return true;
}

void MainDeviceLimit::startMonitoring()
{
	TLINS_LOG_WARNING("Limiuts has been started");
	enableTrackPosition.store(true);
	threadTrackPositionLimitCtrlCv.notify_all();
}
void MainDeviceLimit::stopMonitoring()
{
	TLINS_LOG_WARNING("Limiuts has been stoped");
	enableTrackPosition.store(false);
}

struct __positionInfo__ {
	std::string axisName;
	long        pos;
	long        encPos;
	long        rawPos;
	long        rawEncPos;
	long        encoderResoultion;
	long        deviceResoultion;

	__positionInfo__ &operator=(const __positionInfo__ &v) = default;

	__positionInfo__(const std::string &axisName_, const long &pos_, const long &encPos_, const long &rawPos_,
	                 const long &rawEncPos_, const long &encoderResoultion_, const long &deviceResoultion_);
	__positionInfo__(const __positionInfo__ &v) = default;
	__positionInfo__()                          = default;
	virtual ~__positionInfo__()                 = default;
};

__positionInfo__::__positionInfo__(const std::string &axisName_, const long &pos_, const long &encPos_,
                                   const long &rawPos_, const long &rawEncPos_, const long &encoderResoultion_,
                                   const long &deviceResoultion_)
    : axisName{axisName_},
      pos{pos_},
      encPos{encPos_},
      rawPos{rawPos_},
      rawEncPos{rawEncPos_},
      encoderResoultion{encoderResoultion_},
      deviceResoultion{deviceResoultion_}
{
}

void MainDeviceLimit::addLimitDefinition(const Eigen::Vector3d &v1, const Eigen::Vector3d &v2)
{
	// TODO
	// TODO: implement
	// TODO
	// deviceLimitDefinition.addLimit(v1, v2);
}

void MainDeviceLimit::endTrack(void)
{
	endTrackPositionLimit.store(true);
	threadTrackPositionLimitCtrlCv.notify_all();
}

void MainDeviceLimit::join()
{
	if (threadTrackPositionLimit.joinable()) {
		threadTrackPositionLimit.join();
	}
}

void MainDeviceLimit::registerConfirmation(const std::string &id)
{
	std::unique_lock<std::mutex> lock(confirmationsMtx);
	confirmations.insert(id);
}

MainDeviceLimit::MainDeviceLimit(const std::shared_ptr<MainDeviceMoreRequestsThread> &mainDeviceThread_,
                                 const DeviceLimitDeviceDefinition                   &limitConf)
    : deviceLimitConfiguration{limitConf},
      mainDevice{mainDeviceThread_->getMainDevice()},
      mainDeviceThread{mainDeviceThread_}
{
	auto sleep_ = [](const long frequency) {
		std::chrono::milliseconds timespan(frequency);
		std::this_thread::sleep_for(timespan);
	};

	endTrackPositionLimit.store(false);

	// Odczy pozycji osi
	auto readPosition = [this](std::map<std::string, __positionInfo__> &position) {
		for (const auto &devIter : *mainDevice) {
			auto             dev = devIter.second;
			__positionInfo__ pos{};
			dev->getActualPosition(pos.pos, pos.encPos, pos.rawPos, pos.rawEncPos);
			pos.encoderResoultion = dev->get_default_CFG_ENC_PULS_MAX();
			pos.deviceResoultion  = dev->get_default_CFG_PULS_MAX();

			pos.axisName = devIter.first;
			std::transform(pos.axisName.begin(), pos.axisName.end(), pos.axisName.begin(), ::toupper);
			position[devIter.first] = pos;
		}
	};

	// Okreslenie kata obrotu osi
	auto getAngles = [](std::map<std::string, __positionInfo__, std::less<>> &position, double &alfa, double &beta) {
		if (position.count("X") != 0) {
			alfa = tlinsMath::PI_2 * static_cast<double>(position["X"].pos) /
			       static_cast<double>(position["X"].deviceResoultion);
		}
		if (position.count("Y") != 0) {
			beta = tlinsMath::PI_2 * static_cast<double>(position["Y"].pos) /
			       static_cast<double>(position["Y"].deviceResoultion);
		}
	};

	auto sendNoti = [this](tlins::tlinsDeviceStatus stat) {
		auto &confMgr = tlinsSerialServerConfirmationManager::getInstance();
		for (auto &confirmationId : confirmations) {

			//  Limit pozycji
			std::unique_ptr<tlins::tlinsRpcConfirmationStatus> confData =
			    std::make_unique<tlins::tlinsRpcConfirmationStatus>();
			confData->set_type(tlins::tlinsSerialDeviceConfirmationType::_CONF_POSITION_LIMITS);
			confData->set_userrequestid(-1);

			auto confDetails = confData->mutable_positionlimit();

			// Nazwa urzadzenia
			confDetails->set_devicename(mainDevice->getSerialDeviceName());
			confDetails->set_status(stat);

			// Wyslanie potwierdzenia
			confMgr.enqueue(confirmationId, confData);
		}
	};

	// Lambda implementujaca logike watku sledzacego aktualna pozycję
	auto threadFunction = [this, sleep_, readPosition, getAngles, sendNoti]() {
		while (!endTrackPositionLimit.load()) {
			if (!enableTrackPosition.load()) {
				// Wyslanie notyfikacji ze limity zostaly wstrzymane
				sendNoti(tlins::tlinsDeviceStatus::_CONF_DEVICE_LIMITS_SUSPENDED);

				// Oczekiwanie na wznowienie
				std::unique_lock<std::mutex> lock(threadTrackPositionLimitCtrlMtx);
				threadTrackPositionLimitCtrlCv.wait(lock);

				// Wyslanie notyfikacji o tym że limity zostaly wznowione
				sendNoti(tlins::tlinsDeviceStatus::_CONF_DEVICE_LIMITS_REASUMED);
			}

			// Odczyt aktualnej pozycji urządzenia
			std::map<std::string, __positionInfo__> position{};
			readPosition(position);

			if (position.size() == 2) {
				double alfa{0.0};
				double beta{0.0};

				for (auto &iter : position) {
					auto &name = iter.first;
					auto &pos  = iter.second;

					auto dev = mainDevice->find(name);
					if (dev == mainDevice->end()) {
						continue;
					}
					if (name == "X") {
						alfa =
						    static_cast<double>(pos.pos) / static_cast<double>(dev->second->get_default_CFG_PULS_MAX());
					} else if (name == "Y") {
						beta =
						    static_cast<double>(pos.pos) / static_cast<double>(dev->second->get_default_CFG_PULS_MAX());
					}
				}

				// Wyznaczenie pozycji
				auto devicePosition = limits::tlinsLimitsMath::kinematicsPositionGemetric2(
				    alfa, beta, deviceLimitConfiguration.r1, deviceLimitConfiguration.r2, deviceLimitConfiguration.dx,
				    deviceLimitConfiguration.dz, deviceLimitConfiguration.h,
				    deviceLimitConfiguration.deviceMountAngles);

				TLINS_LOG_WARNING(
				    std::string{"Limiuts thread loop : ["} + std::to_string(devicePosition.first(0)) + "; " +
				    std::to_string(devicePosition.first(1)) + "; " + std::to_string(devicePosition.first(2)) + "][" +
				    std::to_string(devicePosition.second(0)) + "; " + std::to_string(devicePosition.second(1)) + "; " +
				    std::to_string(devicePosition.second(2)) + "]");


				// Sprawdzenie czy tuba teleskopu nie jest w kolizji z montazem
				limits::tlinsLimitsMount moutLimit{
				    deviceLimitConfiguration.legs,        deviceLimitConfiguration.legRadius,
				    deviceLimitConfiguration.legsZOffset, deviceLimitConfiguration.legsStartAngle,
				    deviceLimitConfiguration.legsAngle,   deviceLimitConfiguration.baseRadius,
				    deviceLimitConfiguration.baseLength};

				// Sprawdzenie kolzji dla obu koncow tubusa montazu
				std::pair<limits::tlinsLimitsMount::colistionType, int> moutColistionResult1 =
				    moutLimit.checkColistion(devicePosition.first);
				std::pair<limits::tlinsLimitsMount::colistionType, int> moutColistionResult2 =
				    moutLimit.checkColistion(devicePosition.second);

				if (moutColistionResult1.first != limits::tlinsLimitsMount::colistionType::COLISTION_NONE ||
				    moutColistionResult2.first != limits::tlinsLimitsMount::colistionType::COLISTION_NONE) {
					// Mamy do czynienia z kolizją

					TLINS_LOG_WARNING("Kolizja z montazem - urzadzenie bedzie zatrzymane");
					// Zatrzymanie urzadzenia i wyslanie notyfikacji
					long A{0L};
					long D{0L};
					for (const auto &iter : *mainDevice) {
						A = iter.second->get_default_RAMP_A();
						D = iter.second->get_default_RAMP_D();
						break;
					}

					// Nowe rzadanie
					auto req = std::make_shared<tlinsSerialDeviceMoveRequest>(tlinsSerialMoveType::ABORT,
					                                                          tlinsSerialMoveInterpolationType::LINEAR,
					                                                          tlinsSerialMoveModeRelAbs::ABS, A, D, 0L);

					// Dodanie do rzadania poszczegolnych skladowych osi
					for (const auto &iter : *mainDevice) {
						tlinsSerialDevicePositionRequestAxis reqItem(iter.second->get_default_RAMP_A(),
						                                             iter.second->get_default_RAMP_D(), 0L,
						                                             tlinsSerialDirection::RIGHT, 0L);
						req->append(iter.first, reqItem);
					}

					// Wstawienie nowego rzadania do kolejski
					mainDeviceThread->enqueRequest(req);

					// Wyslanie potwierdzen ze os zostala zatrzymana
					sendNoti(tlins::tlinsDeviceStatus::_CONF_DEVICE_IN_LIMIT);
				}
			}
			sleep_(deviceLimitConfiguration.frequency);
		}
	};

	// Uruchomienie watku
	threadTrackPositionLimit = std::thread(threadFunction);
}

MainDeviceLimit::~MainDeviceLimit()
{
	endTrackPositionLimit.store(true);
	if (threadTrackPositionLimit.joinable()) {
		threadTrackPositionLimit.join();
	}
}

//
// ----------------------------------------------------------------------------------------
//
void MainDeviveLimitManager::addDevicesLimit(const std::string &devName, const std::shared_ptr<MainDeviceLimit> &devLim)
{
	devicesMap[devName] = devLim;
}

std::map<std::string, std::shared_ptr<MainDeviceLimit>>::iterator MainDeviveLimitManager::find(const std::string &name)
{
	return devicesMap.find(name);
}

std::map<std::string, std::shared_ptr<MainDeviceLimit>>::iterator MainDeviveLimitManager::begin()
{
	return devicesMap.begin();
}

std::map<std::string, std::shared_ptr<MainDeviceLimit>>::iterator MainDeviveLimitManager::end()
{
	return devicesMap.end();
}

MainDeviveLimitManager &MainDeviveLimitManager::getInstance()
{
	static MainDeviveLimitManager instance{};
	return instance;
}

//
// ----------------------------------------------------------------------------------------
//
static void __setStatus__(tlins::tlinsRpcStatus *status, const tlins::ErrorCodes errorStatus, const int errorCode,
                          const std::string &desc)
{
	status->set_status(errorStatus);
	status->set_errorcode(errorCode);
	status->set_errordescription(desc);
}

//
// ----------------------------------------------------------------------------------------
//
void tlinsSerialConfirmationQueue::enqueue(std::unique_ptr<tlins::tlinsRpcConfirmationStatus> &conf)
{
	{
		std::unique_lock<std::mutex> lock(mtx);

		if (queue.size() >= maxLen) {
			// Usuniecie komunikatu z poczatku kolejki. Zabespieczenie przed systuacja gdy klient nie odczytuje
			// potwierdzen
			queue.pop_front();
		}
		queue.push_back(std::move(conf));
	}
	cv.notify_all();
}

bool tlinsSerialConfirmationQueue::dequeue(std::unique_ptr<tlins::tlinsRpcConfirmationStatus> &conf)
{
	std::unique_lock<std::mutex> lock(mtx);
	auto                         whereLabda = [this]() { return this->queue.size() != 0 || this->end; };
	cv.wait(lock, whereLabda);

	if (end) {
		return false;
	}

	conf = std::move(queue.front());
	queue.pop_front();

	return true;
}

void tlinsSerialConfirmationQueue::setEnd()
{
	end = true;
	cv.notify_all();
}

tlinsSerialConfirmationQueue::tlinsSerialConfirmationQueue(const int maxLen_) : maxLen{maxLen_}
{
}

//
// ----------------------------------------------------------------------------------------
//
tlinsSerialServerConfirmationManager &tlinsSerialServerConfirmationManager::getInstance()
{
	static tlinsSerialServerConfirmationManager instance{};
	return instance;
}

std::string tlinsSerialServerConfirmationManager::getId()
{
	std::unique_lock<std::mutex> lock(idMtx);
	id++;
	return std::string{"__ID__("} + std::to_string(id) + std::string{")"};
}

std::string tlinsSerialServerConfirmationManager::newConfInstance()
{
	std::string id = getId();

	// Tworzenie instancji kolejko potwierdzen
	{
		std::unique_lock<std::recursive_mutex> lock(mtx);
		streams[id];
	}
	return id;
}

bool tlinsSerialServerConfirmationManager::stop(const std::string &id)
{
	std::unique_lock<std::recursive_mutex> lock(mtx);
	auto                                   iter = streams.find(id);
	if (iter == streams.end()) {
		TLINS_LOG_WARNING("No confiramtion context :" + id);
		return false;
	}

	// Zatrzymanie potwierdzen
	iter->second.setEnd();
	return true;
}

bool tlinsSerialServerConfirmationManager::exists(const std::string &id)
{
	std::unique_lock<std::recursive_mutex> lock(mtx);
	auto                                   iter = streams.find(id);
	if (iter == streams.end()) {
		return false;
	}
	return true;
}

bool tlinsSerialServerConfirmationManager::enqueue(const std::string                                  &id,
                                                   std::unique_ptr<tlins::tlinsRpcConfirmationStatus> &conf)
{
	std::unique_lock<std::recursive_mutex> lock(mtx);
	auto                                   iter = streams.find(id);
	if (iter == streams.end()) {
		TLINS_LOG_WARNING("No confiramtion context :" + id);
		return false;
	}

	// Wstawienie potwierdzenia
	iter->second.enqueue(conf);
	return true;
}

bool tlinsSerialServerConfirmationManager::dequeue(const std::string                                  &id,
                                                   std::unique_ptr<tlins::tlinsRpcConfirmationStatus> &status)
{
	std::map<std::string, tlinsSerialConfirmationQueue>::iterator iter{};
	{
		std::unique_lock<std::recursive_mutex> lock(mtx);
		iter = streams.find(id);
		if (iter == streams.end()) {
			TLINS_LOG_WARNING("No confiramtion context :" + id);
			return false;
		}
	}

	// Wstawienie potwierdzenia
	return iter->second.dequeue(status);
}

//
// ----------------------------------------------------------------------------------------
//

grpc::Status tlinsRpcConfirmationServer::confirmation(grpc::ServerContext                                   *context,
                                                      const tlins::tlinsConfirmationHandler                 *request,
                                                      grpc::ServerWriter<tlins::tlinsRpcConfirmationStatus> *writer)
{
	// Pobranie idetyfikatora strumienia
	auto confirmId = request->handler();

	auto &mgrInstance = tlinsSerialServerConfirmationManager::getInstance();

	if (!mgrInstance.exists(confirmId)) {
		// Klient nie zarejestrował potwierdzenia
		return grpc::Status(grpc::StatusCode::INVALID_ARGUMENT, "Unknow confirmation ID: " + confirmId);
	}

	// Petla czytajaca potwierdzenia
	std::unique_ptr<tlins::tlinsRpcConfirmationStatus> confirmation;
	while (mgrInstance.dequeue(confirmId, confirmation)) {
		auto handle = confirmation->mutable_handler();
		handle->set_handler(confirmId);
		writer->Write(*confirmation);
	}
	return grpc::Status::OK;
}

//
// ----------------------------------------------------------------------------------------
// ----------------------------------------------------------------------------------------
//
// Metody implementujace limity
grpc::Status
tlinsRpcMoveControlServer::colistionsDetectionConfirmationCreate(grpc::ServerContext                   *context,
                                                                 const tlins::tlinsStringValue         *request,
                                                                 tlins::tlinsConfirmationHandlerResult *response)
{
	auto       &mgrInstance = tlinsSerialServerConfirmationManager::getInstance();
	auto        id          = mgrInstance.newConfInstance();
	std::string deviceName{request->value()};

	try {
		parent.colistionsDetectionRegisterConfirmation(deviceName, id);
	}
	catch (tlinsSerialDeviceException &exc) {

		mgrInstance.stop(id);
		__setStatus__(response->mutable_status(), tlins::ErrorCodes::_ERROR_CODE_ERROR,
		              static_cast<int>(tlinsServerErrorCodes::ERROR_INVALID_PARAMETER), exc.getErrorMessage());
		return grpc::Status::OK;
	}

	__setStatus__(response->mutable_status(), tlins::ErrorCodes::_ERROR_CODE_SUCCESS,
	              static_cast<int>(tlinsServerErrorCodes::SUCCESS), std::string{"SUCCESS"});

	// Identyfikator potwierdzen
	auto handler = response->mutable_handler();
	handler->set_handler(id);
	return grpc::Status::OK;
}

grpc::Status tlinsRpcMoveControlServer::colistionsDetectionSetLimits(grpc::ServerContext      *context,
                                                                     const tlins::tlinsLimits *request,
                                                                     tlins::tlinsRpcStatus    *response)
{
	std::string                                               deviceName{request->devicename().value()};
	std::vector<std::tuple<Eigen::Vector3d, Eigen::Vector3d>> allLimits{};

	for (int i = 0; i < request->limits_size(); i++) {
		auto &item = request->limits(i);

		if (!item.has_start() || !item.has_end()) {
			__setStatus__(response, tlins::ErrorCodes::_ERROR_CODE_ERROR,
			              static_cast<int>(tlinsServerErrorCodes::ERROR_INVALID_PARAMETER),
			              "Limity not defined correctly");
			return grpc::Status::OK;
		}

		Eigen::Vector3d v1{item.start().a1().value(), item.start().a2().value(), item.start().a3().value()};
		Eigen::Vector3d v2{item.end().a1().value(), item.end().a2().value(), item.end().a3().value()};

		std::tuple<Eigen::Vector3d, Eigen::Vector3d> value{v1, v2};
		allLimits.push_back(value);
	}
	for (auto &item : allLimits) {
		parent.addColistionDefinition(deviceName, std::get<0>(item), std::get<1>(item));
	}

	__setStatus__(response, tlins::ErrorCodes::_ERROR_CODE_SUCCESS,
	              static_cast<int32_t>(tlinsServerErrorCodes::SUCCESS), "SUCCESS");
	return grpc::Status::OK;
}


grpc::Status tlinsRpcMoveControlServer::colistionsDetectionGetLimits(grpc::ServerContext *context,
                                                                     const tlins::Void   *request,
                                                                     tlins::tlinsLimits  *response)
{
	// TODO
	return grpc::Status::OK;
}

grpc::Status tlinsRpcMoveControlServer::colistionsDetectionTest(grpc::ServerContext         *context,
                                                                const tlins::tlinsTestLimit *request,
                                                                tlins::tlinsTestLimitResult *response)
{
	std::string     deviceName{request->devicename().value()};
	Eigen::Vector3d position{request->position().a1().value(), request->position().a2().value(),
	                         request->position().a3().value()};

	bool result{false};
	try {
		result = parent.colistionsDetectionTest(deviceName, position);
	}
	catch (tlinsSerialDeviceException &exc) {
		__setStatus__(response->mutable_result(), tlins::ErrorCodes::_ERROR_CODE_ERROR,
		              static_cast<int>(tlinsServerErrorCodes::ERROR_INVALID_PARAMETER), exc.getErrorMessage());
		return grpc::Status::OK;
	}

	response->mutable_limitstatus()->set_value(result);
	__setStatus__(response->mutable_result(), tlins::ErrorCodes::_ERROR_CODE_SUCCESS,
	              static_cast<int32_t>(tlinsServerErrorCodes::SUCCESS), "SUCCESS");
	return grpc::Status::OK;
	return grpc::Status::OK;
}

grpc::Status tlinsRpcMoveControlServer::colistionsDetectionEnable(grpc::ServerContext           *context,
                                                                  const tlins::tlinsStringValue *request,
                                                                  tlins::tlinsRpcStatus         *response)
{
	std::string deviceName{request->value()};

	try {
		parent.enableColistionsDetection(deviceName);
	}
	catch (tlinsSerialDeviceException &exc) {
		__setStatus__(response, tlins::ErrorCodes::_ERROR_CODE_ERROR,
		              static_cast<int>(tlinsServerErrorCodes::ERROR_INVALID_PARAMETER), exc.getErrorMessage());
		return grpc::Status::OK;
	}

	__setStatus__(response, tlins::ErrorCodes::_ERROR_CODE_SUCCESS,
	              static_cast<int32_t>(tlinsServerErrorCodes::SUCCESS), "SUCCESS");
	return grpc::Status::OK;
}

grpc::Status tlinsRpcMoveControlServer::colistionsDetectionDisable(grpc::ServerContext           *context,
                                                                   const tlins::tlinsStringValue *request,
                                                                   tlins::tlinsRpcStatus         *response)
{
	std::string deviceName{request->value()};

	try {
		parent.disableColistionsDetection(deviceName);
	}
	catch (tlinsSerialDeviceException &exc) {
		__setStatus__(response, tlins::ErrorCodes::_ERROR_CODE_ERROR,
		              static_cast<int>(tlinsServerErrorCodes::ERROR_INVALID_PARAMETER), exc.getErrorMessage());
		return grpc::Status::OK;
	}

	__setStatus__(response, tlins::ErrorCodes::_ERROR_CODE_SUCCESS,
	              static_cast<int32_t>(tlinsServerErrorCodes::SUCCESS), "SUCCESS");
	return grpc::Status::OK;
}


//
// ----------------------------------------------------------------------------------------
// ----------------------------------------------------------------------------------------
//

grpc::Status tlinsRpcMoveControlServer::createConfirmation(grpc::ServerContext *context, const tlins::Void *request,
                                                           tlins::tlinsConfirmationHandlerResult *response)
{
	// Tworzenie instancji potwierdzen
	auto &mgrInstance = tlinsSerialServerConfirmationManager::getInstance();
	auto  id          = mgrInstance.newConfInstance();

	// Rezultat
	// - Status
	__setStatus__(response->mutable_status(), tlins::ErrorCodes::_ERROR_CODE_SUCCESS,
	              static_cast<int>(tlinsServerErrorCodes::SUCCESS), std::string{"SUCCESS"});

	// - Identyfikator potwierdzen
	auto handler = response->mutable_handler();
	handler->set_handler(id);
	return grpc::Status::OK;
}

grpc::Status tlinsRpcMoveControlServer::setMoveMode(grpc::ServerContext             *context,
                                                    const tlins::tlinsRpcDeviceMode *request,
                                                    tlins::tlinsRpcStatus           *response)
{
	// Nazwa urzadzenia glownego
	std::string deviceName{};
	if (request->has_devicename()) {
		deviceName = request->devicename().value();
	} else {
		__setStatus__(response, tlins::ErrorCodes::_ERROR_CODE_ERROR,
		              static_cast<int>(tlinsServerErrorCodes::ERROR_INVALID_PARAMETER), std::string{"No device name"});
		return grpc::Status::OK;
	}

	// Tryb pracy kontrolera
	tlinsSerialServerMode mode;
	if (request->has_mode()) {
		switch (request->mode().value()) {
		case tlins::tlinsSerialDeviceMode::_AXIS:
			TLINS_LOG_DEBUG("tlins::tlinsSerialDeviceMode::_AXIS");
			mode = tlinsSerialServerMode::MODE_SEPARATE_AXIS;
			break;

		case tlins::tlinsSerialDeviceMode::_SYNCHRONISED:
			TLINS_LOG_DEBUG("tlins::tlinsSerialDeviceMode::_SYNCHRONISED");
			mode = tlinsSerialServerMode::MODE_SYNCHRONISED;
			break;
		}
	} else {
		__setStatus__(response, tlins::ErrorCodes::_ERROR_CODE_ERROR,
		              static_cast<int>(tlinsServerErrorCodes::ERROR_INVALID_PARAMETER), std::string{"No server mode"});
		return grpc::Status::OK;
	}

	// Ustawnie trybu pracy
	try {
		parent.setServerMode(deviceName, mode);
	}
	catch (tlinsSerialDeviceException &exc) {
		__setStatus__(response, tlins::ErrorCodes::_ERROR_CODE_ERROR,
		              static_cast<int>(tlinsServerErrorCodes::ERROR_INVALID_PARAMETER),
		              "Unknown mainn device name: " + deviceName);
		return grpc::Status::OK;
	}

	// Budowanie odpowiedzi
	__setStatus__(response, tlins::ErrorCodes::_ERROR_CODE_SUCCESS,
	              static_cast<int32_t>(tlinsServerErrorCodes::SUCCESS), "SUCCESS");
	return grpc::Status::OK;
}

grpc::Status tlinsRpcMoveControlServer::getMoveMode(grpc::ServerContext             *context,
                                                    const tlins::tlinsStringValue   *request,
                                                    tlins::tlinsRpcDeviceModeStatus *response)
{
	std::string deviceName{request->value()};

	tlinsSerialServerMode mode;
	try {
		mode = parent.getServerMode(deviceName);
	}
	catch (tlinsSerialDeviceException &exc) {
		__setStatus__(response->mutable_status(), tlins::ErrorCodes::_ERROR_CODE_ERROR,
		              static_cast<int>(tlinsServerErrorCodes::ERROR_INVALID_PARAMETER),
		              "Unknown mainn device name: " + deviceName);
		return grpc::Status::OK;
	}

	response->mutable_devicename()->set_value(deviceName);

	switch (mode) {
	case tlinsSerialServerMode::MODE_SYNCHRONISED:
		response->mutable_mode()->set_value(tlins::tlinsSerialDeviceMode::_SYNCHRONISED);
		break;

	case tlinsSerialServerMode::MODE_SEPARATE_AXIS:
		response->mutable_mode()->set_value(tlins::tlinsSerialDeviceMode::_AXIS);
		break;
	}

	__setStatus__(response->mutable_status(), tlins::ErrorCodes::_ERROR_CODE_SUCCESS,
	              static_cast<int>(tlinsServerErrorCodes::SUCCESS), std::string{"Success"});
	return grpc::Status::OK;
}

grpc::Status tlinsRpcMoveControlServer::setDateTime(grpc::ServerContext           *context,
                                                    const tlins::tlinsRpcDateTime *request,
                                                    tlins::tlinsRpcStatus         *response)
{
	struct tm tmData;
	::memset(reinterpret_cast<void *>(&tmData), 0, sizeof(struct tm));

	tmData.tm_sec  = request->second().value();      // Seconds (0-60)
	tmData.tm_min  = request->minute().value();      // Minutes (0-59)
	tmData.tm_hour = request->hour().value();        // Hours (0-23)
	tmData.tm_mday = request->day().value();         // Day of the month (1-31)
	tmData.tm_mon  = request->month().value() - 1;   // Month (0-11)
	tmData.tm_year = request->year().value() - 1900; // Year - 1900

	time_t dateTimeValue = ::mktime(&tmData);
	if (dateTimeValue < 0) {
		__setStatus__(response, tlins::ErrorCodes::_ERROR_CODE_ERROR,
		              static_cast<int>(tlinsServerErrorCodes::INVALID_PARAMETER),
		              std::string{"Invalid date/time info"});
		return grpc::Status::OK;
	}
	// Ustawienie czasu
	// if (stime(&dateTimeValue) < 0) {
	// 	__setStatus__(response, tlins::ErrorCodes::_ERROR_CODE_ERROR, static_cast<int>(tlinsServerErrorCodes::ERROR),
	// 	              std::string{"Invalid date/time info"});
	// 	return grpc::Status::OK;
	// }

	__setStatus__(response, tlins::ErrorCodes::_ERROR_CODE_SUCCESS, static_cast<int>(tlinsServerErrorCodes::SUCCESS),
	              std::string{"Success"});
	return grpc::Status::OK;
}

grpc::Status tlinsRpcMoveControlServer::getConfiguration(grpc::ServerContext                  *context,
                                                         const tlins::tlinsRpcMainDevicesName *request,
                                                         tlins::tlinsRpcDeviceConfiguration   *response)
{
	// Nazwa urzadzenia glownego
	std::string mainDeviceName{request->devicename()};

	// Pobranie urzadzenia glownego
	auto &devManagegInstance = tlinsSerialDeviceManager::getInstance();
	auto  deviceRef          = devManagegInstance.find(mainDeviceName);
	if (deviceRef == devManagegInstance.end()) {
		__setStatus__(response->mutable_status(), tlins::ErrorCodes::_ERROR_CODE_ERROR,
		              static_cast<int32_t>(tlinsServerErrorCodes::ERROR_INVALID_PARAMETER),
		              "Unknown mainn device name: " + mainDeviceName);
		return grpc::Status::OK;
	}

	// Budowanie odpowiedzi
	response->set_maindevicename(mainDeviceName);

	// Odczyt wspolrzednych urzadzenia
	auto mainDevice = deviceRef->second;

	try {
		for (auto &devIter : *mainDevice) {
			auto dev = devIter.second;

			// Nazwa osi
			auto axisName = devIter.first;

			// Dodanie informacji o osi do rezultatu
			auto ax = response->add_axies();
			ax->set_axisname(axisName);

			// Maksymalne wartosci pozycji
			ax->mutable_encoderresolution()->set_value(dev->get_default_CFG_ENC_PULS_MAX());
			ax->mutable_stepsonresolution()->set_value(dev->get_default_CFG_PULS_MAX());
		}
	}
	catch (tlinsSerialDeviceException &exc) {
		__setStatus__(response->mutable_status(), tlins::ErrorCodes::_ERROR_CODE_ERROR,
		              static_cast<int32_t>(tlinsServerErrorCodes::DEVICE_ERROR), "Error take device configuration");
		return grpc::Status::OK;
	}

	// Budowanie odpowiedzi
	__setStatus__(response->mutable_status(), tlins::ErrorCodes::_ERROR_CODE_SUCCESS,
	              static_cast<int32_t>(tlinsServerErrorCodes::SUCCESS), "SUCCESS");
	return grpc::Status::OK;
}

grpc::Status tlinsRpcMoveControlServer::getPosition(grpc::ServerContext                  *context,
                                                    const tlins::tlinsRpcMainDevicesName *request,
                                                    tlins::tlinsRpcPositionInfo          *response)
{
	// Nazwa urzadzenia glownego
	std::string mainDeviceName{request->devicename()};

	// Pobranie urzadzenia glownego
	auto &devManagegInstance = tlinsSerialDeviceManager::getInstance();
	auto  deviceRef          = devManagegInstance.find(mainDeviceName);
	if (deviceRef == devManagegInstance.end()) {
		__setStatus__(response->mutable_status(), tlins::ErrorCodes::_ERROR_CODE_ERROR,
		              static_cast<int32_t>(tlinsServerErrorCodes::ERROR_INVALID_PARAMETER),
		              "Unknown mainn device name: " + mainDeviceName);
		return grpc::Status::OK;
	}

	// Budowanie odpowiedzi
	response->mutable_devicename()->set_value(mainDeviceName);

	// Odczyt wspolrzednych urzadzenia
	auto mainDevice = deviceRef->second;

	try {
		for (auto &devIter : *mainDevice) {
			auto dev = devIter.second;

			// Nazwa osi
			auto axisName = devIter.first;

			// Pozycja
			long pos;
			long encPos;

			long rawPos;
			long rawEncPos;

			dev->getActualPosition(pos, encPos, rawPos, rawEncPos);

			// Dodanie informacji o osi do rezultatu
			auto ax = response->add_axies();
			ax->set_axisname(axisName);

			// Pozycja
			ax->set_motorpostion(pos);
			ax->set_encoderpostion(encPos);
			ax->set_rawmotorpostion(rawPos);
			ax->set_rawencoderpostion(rawEncPos);
		}
	}
	catch (tlinsSerialDeviceException &exc) {
		__setStatus__(response->mutable_status(), tlins::ErrorCodes::_ERROR_CODE_ERROR,
		              static_cast<int32_t>(tlinsServerErrorCodes::DEVICE_ERROR), "Error take device position");
		return grpc::Status::OK;
	}

	// Budowanie odpowiedzi
	__setStatus__(response->mutable_status(), tlins::ErrorCodes::_ERROR_CODE_SUCCESS,
	              static_cast<int32_t>(tlinsServerErrorCodes::SUCCESS), "SUCCESS");
	return grpc::Status::OK;
}

grpc::Status tlinsRpcMoveControlServer::setPosition(grpc::ServerContext           *context,
                                                    const tlins::tlinsRpcPosition *request,
                                                    tlins::tlinsRpcStatus         *response)
{
	try {
		auto deviceName = request->devicename().value();

		// Pobranie narzedzia glownego
		auto mainDevIter = tlinsSerialDeviceManager::getInstance().find(deviceName);
		if (mainDevIter == tlinsSerialDeviceManager::getInstance().end()) {
			__setStatus__(response, tlins::ErrorCodes::_ERROR_CODE_ERROR,
			              static_cast<int32_t>(tlinsServerErrorCodes::INVALID_PARAMETER), "Unknown main device name");
			return grpc::Status::OK;
		}

		// Urzadzenie glowne
		auto &mainDev = *(mainDevIter->second);

		// Testowanie nazw osi
		for (int i = 0; i < request->axies_size(); i++) {
			auto &axis  = request->axies(i);
			auto &aName = axis.axisname();

			if (mainDev.find(aName) == mainDev.end()) {
				__setStatus__(response, tlins::ErrorCodes::_ERROR_CODE_ERROR,
				              static_cast<int32_t>(tlinsServerErrorCodes::INVALID_PARAMETER),
				              "Unknown main device name");
				return grpc::Status::OK;
			}
		}

		for (int i = 0; i < request->axies_size(); i++) {
			auto &axis           = request->axies(i);
			auto &aName          = axis.axisname();
			long  encoderPostion = axis.encoderpostion();
			long  motorPostion   = axis.motorpostion();
			auto &axisDev        = *(mainDev.find(aName)->second);

			axisDev.setActualPosition(motorPostion, encoderPostion);
		}
	}
	catch (tlinsSerialDeviceException &exc) {
		__setStatus__(response, tlins::ErrorCodes::_ERROR_CODE_ERROR,
		              static_cast<int32_t>(tlinsServerErrorCodes::DEVICE_ERROR), "Error take device position");
		return grpc::Status::OK;
	}

	// Budowanie odpowiedzi
	__setStatus__(response, tlins::ErrorCodes::_ERROR_CODE_SUCCESS,
	              static_cast<int32_t>(tlinsServerErrorCodes::SUCCESS), "SUCCESS");
	return grpc::Status::OK;
}

grpc::Status tlinsRpcMoveControlServer::setMoveRequest(grpc::ServerContext              *context,
                                                       const tlins::tlinsRpcMoveRequest *request,
                                                       tlins::tlinsRpcMoveStatus        *response)
{
	// Read general requests data
	std::string mainDeviceName{""};
	if (request->has_maindevicename()) {
		mainDeviceName = request->maindevicename().value();
	}

	// Weryfikacja nazwy urzadzenia glownego
	auto &devManagegInstance = tlinsSerialDeviceManager::getInstance();
	auto  deviceRef          = devManagegInstance.find(mainDeviceName);
	if (deviceRef == devManagegInstance.end()) {
		response->set_requestid(-1);
		__setStatus__(response->mutable_status(), tlins::ErrorCodes::_ERROR_CODE_ERROR,
		              static_cast<int32_t>(tlinsServerErrorCodes::ERROR_INVALID_PARAMETER),
		              "Unknown mainn device name: " + mainDeviceName);
		return grpc::Status::OK;
	}

	// Identyfikator rzadania uzytkownika
	long userRequestID = request->userrequestid();

	// Identyfikatora potwierdzenia
	std::string confirmationId{""};
	bool        hasConfirmation = false;
	if (request->has_confirmationhandler()) {
		hasConfirmation = true;
		confirmationId  = request->confirmationhandler().handler();
	}

	long gA = 0L;
	if (request->has_a()) {
		gA = request->a().value();
	}

	long gD = 0L;
	if (request->has_d()) {
		gD = request->d().value();
	}

	long gV = 0L;
	if (request->has_v()) {
		gV = request->v().value();
	}

	// Weryfikacja requestu i ewentualne wymuszenie oczekiwanego trybu pracy
	tlinsSerialMoveType mode;
	auto                _serverMode_ = tlinsSerialServerMode::MODE_NONE;
	if (request->has_mode()) {
		switch (request->mode().value()) {
		case tlins::tlinsSerialMoveType::_SPEED:
			mode         = tlinsSerialMoveType::SPEED;
			_serverMode_ = tlinsSerialServerMode::MODE_SEPARATE_AXIS;
			break;

		case tlins::tlinsSerialMoveType::_POSITION:
			mode         = tlinsSerialMoveType::POSITION;
			_serverMode_ = tlinsSerialServerMode::MODE_SYNCHRONISED;
			break;

		case tlins::tlinsSerialMoveType::_STOP:
			mode         = tlinsSerialMoveType::STOP;
			_serverMode_ = tlinsSerialServerMode::MODE_NONE;
			break;

		case tlins::tlinsSerialMoveType::_ABORT:
			mode         = tlinsSerialMoveType::ABORT;
			_serverMode_ = tlinsSerialServerMode::MODE_NONE;
			break;
		}
	}
	/*
	    if (parent.getServerMode(mainDeviceName) == tlinsSerialServerMode::MODE_SYNCHRONISED &&
	        request->mode().value() == tlins::tlinsSerialMoveType::_SPEED) {
	        TLINS_LOG_ERROR("In synchronus mode SPEED mode is not avalible");

	        // Blasd rejestracji rzadania. W trybie synchronicznym tryb SPEED jest niedostępny
	        response->set_requestid(-1);
	        __setStatus__(response->mutable_status(), tlins::ErrorCodes::_ERROR_CODE_ERROR,
	                      static_cast<int32_t>(tlinsServerErrorCodes::INVALID_SERVER_MODE),
	                      "SPEED mode is not avalible in SYNCHRONUS MODE");
	        return grpc::Status::OK;
	    }
	*/
	tlinsSerialMoveInterpolationType interpolationType = tlinsSerialMoveInterpolationType::LAST;
	if (request->has_interpolationtype()) {
		if (request->interpolationtype().value() == tlins::tlinsSerialMoveInterpolationType::_LINEAR)
			interpolationType = ::tlinsSerialMoveInterpolationType::LINEAR;
	}

	tlinsSerialMoveModeRelAbs moveType = tlinsSerialMoveModeRelAbs::ABS;
	if (request->has_movetype()) {
		switch (request->movetype().value()) {
		case tlins::tlinsSerialMoveModeRelAbs::_REL:
			moveType = tlinsSerialMoveModeRelAbs::REL;
			break;

		case tlins::tlinsSerialMoveModeRelAbs::_ABS:
			moveType = tlinsSerialMoveModeRelAbs::ABS;
			break;
		}
	}

	// Build request
	auto req = std::make_shared<tlinsSerialDeviceMoveRequest>(mode, interpolationType, moveType, gA, gD, gV);

	// Identyfikator rzadania uzytkownika
	req->setUserRequestID(userRequestID);

	// Identyfikator rzadania
	if (hasConfirmation) {
		req->setConfirmationId(confirmationId);
	}

	for (int i = 0; i < request->requestdetails_size(); i++) {
		auto &item = request->requestdetails(i);

		std::string axisName;
		if (item.has_axisname())
			axisName = item.axisname().value();

		auto refA = deviceRef->second->find(axisName);
		if (refA == deviceRef->second->end()) {
			// Nieznana os
			response->set_requestid(-1);
			__setStatus__(response->mutable_status(), tlins::ErrorCodes::_ERROR_CODE_ERROR,
			              static_cast<int32_t>(tlinsServerErrorCodes::ERROR_INVALID_PARAMETER),
			              "Unknown axis name: " + axisName);
			return grpc::Status::OK;
		}

		long A = 0;
		if (item.has_a()) {
			A = item.a().value();
		}

		long D = 0;
		if (item.has_d()) {
			D = item.d().value();
		}

		long V = 0;
		if (item.has_v()) {
			V = item.v().value();
		}

		tlinsSerialDirection direction = tlinsSerialDirection::LEFT;
		if (item.has_direction()) {
			switch (item.direction().value()) {
			case tlins::tlinsMoveDirection::_LEFT:
				direction = tlinsSerialDirection::LEFT;
				break;

			case tlins::tlinsMoveDirection::_RIGHT:
				direction = tlinsSerialDirection::RIGHT;
				break;
			}
		}

		long distance = 0;
		if (item.has_distance()) {
			distance = item.distance().value();
		}
		TLINS_LOG_DEBUG(axisName + " = " + std::to_string(distance) + "; V =" + std::to_string(V));

		// Request item
		tlinsSerialDevicePositionRequestAxis reqItem(A, D, V, direction, distance);

		// Rejestracja pozycji rzadania - osi
		req->append(axisName, reqItem);
	}

	// Wstawienie rzadania do kolejki rzadan przemieszczenia
	try {
		parent.enqueRequest(mainDeviceName, req);
	}
	catch (tlinsSerialDeviceException &exc) {
		// Blasd rejestracji rzadania
		response->set_requestid(-1);
		__setStatus__(response->mutable_status(), tlins::ErrorCodes::_ERROR_CODE_ERROR,
		              static_cast<int32_t>(tlinsServerErrorCodes::ENQUEUE_REQUEST),
		              "Enqueue request: " + exc.getErrorMessage());
		return grpc::Status::OK;
	}

	// Budowanie odpowiedzi
	response->set_requestid(req->getRequestID());
	__setStatus__(response->mutable_status(), tlins::ErrorCodes::_ERROR_CODE_SUCCESS,
	              static_cast<int32_t>(tlinsServerErrorCodes::SUCCESS), "SUCCESS");
	return grpc::Status::OK;
}

tlinsRpcMoveControlServer::tlinsRpcMoveControlServer(tlinsSerialServer &parent_) : parent{parent_}
{
}

//
// ----------------------------------------------------------------------------------------
//          Implemanetacja klasy odpowiedzialny za obsluge urzadzenia glownego
// ----------------------------------------------------------------------------------------
//

void MainDeviceMoreRequestsThread::confirmMove(
    const std::vector<std::pair<std::string, tlinsSerialMainDevice::ConfirmationInfo>> &data)
{
	if (data.size() == 0) {
		return;
	}

	std::vector<std::pair<std::string, tlinsSerialRequestStatusResult>> statusInfo;

	for (auto &item : data) {
		// Weryfikacja identyfikatora osi
		if (mainDevice->find(item.first) == mainDevice->end()) {
			TLINS_LOG_ERROR("Unknow device: " + item.first);
			return;
		}

		// Sprawdzenie czy ID potwierdzenia pokrywa sie z ID aktualnego rzadania
		unsigned long id{};
		{
			std::unique_lock<std::recursive_mutex> lock(serverMtx);
			id = reqIdsMap[item.first];
		}

		if (id != item.second.confID) {
			continue;
		}

		tlinsSerialRequestStatusResult itemStatus = tlinsSerialRequestStatusResult::STATUS_NONE;
		if (item.second.confType == tlinsSerialMainDevice::ConfirmationType::COMPLETED) {
			itemStatus = tlinsSerialRequestStatusResult::STATUS_COMPLETED_SUCCESS;
		} else {
			TLINS_LOG_ERROR(">>> ERROR device <<<");
			itemStatus = tlinsSerialRequestStatusResult::STATUS_ERROR;
		}

		statusInfo.emplace_back(std::pair<std::string, tlinsSerialRequestStatusResult>(item.first, itemStatus));
	}
	confirmPosition(statusInfo, false);
}

void MainDeviceMoreRequestsThread::confirmMove(
    const std::vector<std::pair<std::string, tlinsSerialMainDevice::ConfirmationType>> &data)
{
	if (data.size() == 0) {
		return;
	}

	std::vector<std::pair<std::string, tlinsSerialRequestStatusResult>> statusInfo;

	for (auto &item : data) {
		// Weryfikacja identyfikatora osi
		if (mainDevice->find(item.first) == mainDevice->end()) {
			TLINS_LOG_ERROR("Unknow device: " + item.first);
			return;
		}

		tlinsSerialRequestStatusResult itemStatus = tlinsSerialRequestStatusResult::STATUS_NONE;
		if (item.second == tlinsSerialMainDevice::ConfirmationType::COMPLETED) {
			itemStatus = tlinsSerialRequestStatusResult::STATUS_COMPLETED_SUCCESS;
		} else {
			TLINS_LOG_ERROR(">>> ERROR device <<<");
			itemStatus = tlinsSerialRequestStatusResult::STATUS_ERROR;
		}

		statusInfo.emplace_back(std::pair<std::string, tlinsSerialRequestStatusResult>(item.first, itemStatus));
	}
	confirmPosition(statusInfo, false);
}

// ---
// -------------------
// ---

void MainDeviceMoreRequestsThread::confirmRequest(const long id, const tlinsSerialRequestStatusResult stat)
{
	// Pobranie informacji o rzadaniu
	auto reqInfoIter = requestStatusInfo.find(id);
	if (reqInfoIter == requestStatusInfo.end()) {
		// Informacja o rzadaniu nie jest dostepna
		return;
	}

	// Informacja o pojedynczym rzadaniu
	auto reqInfo = reqInfoIter->second;
	if (!reqInfo->request->needConfirmation()) {
		// Rzadanie nie wymaga potwierdzenia
		return;
	}

	// Sprawdzenie czy istnieje kolejka potwierdzen o danym ID
	auto &confMgr = tlinsSerialServerConfirmationManager::getInstance();
	if (!confMgr.exists(reqInfo->request->getConfirmationId())) {
		// Rzadanie nie wymaga potwierdzenia
		return;
	}

	// Dane potwierdzenia
	std::unique_ptr<tlins::tlinsRpcConfirmationStatus> confData(new tlins::tlinsRpcConfirmationStatus());
	confData->set_type(tlins::tlinsSerialDeviceConfirmationType::_CONF_MOVE_REQUEST);

	// Potwierdzenie uzytkownika
	confData->set_userrequestid(reqInfo->request->getUserRequestID());

	// Potwierdzenie typu przemieszczenie
	auto axisDetails = confData->mutable_moverequest();

	// Identyfikator rzadania
	axisDetails->set_requestid(reqInfo->request->getRequestID());

	// Przejscie po skladowej i pobranie skladowych potwierdzen
	auto &statusMap = reqInfo->requestDetailStatus;
	for (auto iter = statusMap.begin(); iter != statusMap.end(); iter++) {
		auto axisId = iter->first;
		auto status = iter->second;
		auto item   = axisDetails->add_details();

		item->set_axisname(axisId);

		// Napisanie statusu osi statusem przekazanym
		if (stat != tlinsSerialRequestStatusResult::STATUS_NONE) {
			status = stat;
		}

		// Satatus zakonczenia
		switch (status) {
		case tlinsSerialRequestStatusResult::STATUS_WATING:
			item->set_status(tlins::tlinsRpcAxisRequestStatusResult::_STATUS_WATING);
			break;

		case tlinsSerialRequestStatusResult::STATUS_COMPLETED_SUCCESS:
			item->set_status(tlins::tlinsRpcAxisRequestStatusResult::_STATUS_COMPLETED_SUCCESS);
			break;

		case tlinsSerialRequestStatusResult::STATUS_REJECTED:
			item->set_status(tlins::tlinsRpcAxisRequestStatusResult::_STATUS_REJECTED);
			break;

		case tlinsSerialRequestStatusResult::STATUS_COMPLETED_INCMPLETE:
			item->set_status(tlins::tlinsRpcAxisRequestStatusResult::_STATUS_COMPLETED_INCMPLETE);
			break;

		case tlinsSerialRequestStatusResult::STATUS_ERROR:
			item->set_status(tlins::tlinsRpcAxisRequestStatusResult::_STATUS_ERROR);
			break;
		}
	}

	// Wstawienie potwierdzenia
	confMgr.enqueue(reqInfo->request->getConfirmationId(), confData);
}

void MainDeviceMoreRequestsThread::confirmRequest(const std::shared_ptr<tlinsSerialDeviceMoveRequest> &req,
                                                  const tlinsSerialRequestStatusResult                 stat)
{
	confirmRequest(req->getRequestID(), stat);
}

void MainDeviceMoreRequestsThread::signalThread()
{
	serverCv.notify_all();
}

const bool MainDeviceMoreRequestsThread::isEnd()
{
	return end;
}

void MainDeviceMoreRequestsThread::endThread()
{
	// Rozlaczenie petli glownej
	end = true;

	// Na wszelki wypadek budzimy watek
	signalThread();
}

void MainDeviceMoreRequestsThread::confirmPosition(
    const std::vector<std::pair<std::string, tlinsSerialRequestStatusResult>> &inAxis, const bool noNoti)
{
	std::lock_guard<std::recursive_mutex> lock(serverMtx);
	bool                                  anyCompleted   = false;
	bool                                  fullyCompleted = false;

	for (auto &info : inAxis) {
		std::string                    axis   = info.first;
		tlinsSerialRequestStatusResult status = info.second;

		// Sprawdzenie czy os wymaga potwierdzenia
		if (statusNeeded.find(axis) == statusNeeded.end()) {
			continue;
		}

		if (!statusNeeded[axis]) {
			continue;
		}

		if (!statusNeededStart[axis]) {
			continue;
		}

		// Pobranie aktualnej informacji o statusie
		auto it = axisToRequestStatus.find(axis);
		if (it == axisToRequestStatus.end()) {
			continue;
		}

		auto infoPtr = it->second;

		// Jesli os jest juz podwierdzona - nic nie robimy
		if (infoPtr->isConfirmed(axis)) {
			continue;
		}

		anyCompleted = true;

		// Aktualizacja globalnego licznika dla danego rzadania oraz modyfikacja statusu osi
		infoPtr->confirm(axis, status);

		// Kierunek obrotu - brak obrotu
		directions[axis] = tlinsServerDirectionInfo::IDLE;

		// Usuniecie potwierdzenia dla biezacej osi
		axisToRequestStatus.erase(axis);

		// Wszystkie skladowe zostaly potwierdzone
		if (infoPtr->isConfirmed()) {
			// Przeslanie potwierdzenia o zakonczeniu przetwarzania do klienta
			confirmRequest(infoPtr->request);

			// Rzadanie zostalo potwierdzone mozna zwolnic zaalokowane zasoby
			requestStatusInfo.erase(infoPtr->request->getRequestID());

			// Rzadanie w pelni potwierdzone
			fullyCompleted = true;
		}
	}

	// W trybie neizalneznych osi bierzemy kolejne rzadanie z kolejki jak tylko jedna os
	// jest gotowa do przetwarzania
	if (anyCompleted && !noNoti && serverMode == tlinsSerialServerMode::MODE_SEPARATE_AXIS) {
		// Powiadomienie watku glownego ze
		signalThread();
	} else
		// W trybie synchronicznym wszystkie osie potwierdzone nowe zadanie mozna przetwarzac
		if (fullyCompleted && !noNoti && serverMode == tlinsSerialServerMode::MODE_SYNCHRONISED) {
			// Powiadomienie watku ze rzadanie zostalo w calosci przetworzone i nalezy pobrac nowe
			signalThread();
		}
}

void MainDeviceMoreRequestsThread::enforceServerMode(const tlinsSerialServerMode mode)
{
	// Blokada
	std::lock_guard<std::recursive_mutex> lock(serverMtx);

	// Wysalnie potwierdzen do klientow ze rzadania zostaly odrzucone
	for (auto &req : requestStatusInfo) {
		// Potwierdzenie ze request zostal odrzucony
		confirmRequest(req.second->request, tlinsSerialRequestStatusResult::STATUS_REJECTED);
	}

	// Czyszczenie map i kolejek
	requestQueue.clear();
	axisRequests.clear();
	priorityRequestQueue.clear();

	for (auto iter = mainDevice->begin(); iter != mainDevice->end(); iter++) {
		directions[iter->first]        = tlinsServerDirectionInfo::IDLE;
		statusNeeded[iter->first]      = false;
		statusNeededStart[iter->first] = false;
	}

	// Nowy tryb
	serverMode = mode;

	switch (serverMode) {
	case tlinsSerialServerMode::MODE_SYNCHRONISED:
		// Wlaczenie synchronicznego sterowania przemieszczeniem na kontrolerze
		mainDevice->enableSynchMode();
		break;

	case tlinsSerialServerMode::MODE_SEPARATE_AXIS:
		// Wylaczenie synchronicznego sterowania przemieszczeniem na kontrolerze
		mainDevice->disableSynchMode();
		break;
	}

	requestStatusInfo.clear();
	axisToRequestStatus.clear();

	// Fizyczne awaryjne zatrzymanie calego urzadzenia
	try {
		mainDevice->abort();
		for (auto &iter : *mainDevice) {
			statusNeededStart[iter.first] = true;


			// Identyfikator potwierdzenia
			auto id = mainDevice->getNextConfId();
			mainDevice->setConfId(iter.first, id);
			reqIdsMap[iter.first] = id;
		}
	}
	catch (...) {
		TLINS_LOG_ERROR("Error abort device");
	}
}

void MainDeviceMoreRequestsThread::setServerMode(const tlinsSerialServerMode mode)
{
	std::lock_guard<std::recursive_mutex> lock(serverMtx);

	if (serverMode == mode) {
		return;
	}

	// Wysalnie potwierdzen do klientow ze rzadania zostaly odrzucone
	for (auto &req : requestStatusInfo) {
		// Potwierdzenie ze request zostal odrzucony
		confirmRequest(req.second->request, tlinsSerialRequestStatusResult::STATUS_REJECTED);
	}

	// Czyszczenie map i kolejek
	requestQueue.clear();
	axisRequests.clear();
	priorityRequestQueue.clear();

	directions.clear();
	statusNeeded.clear();
	statusNeededStart.clear();
	for (auto iter = mainDevice->begin(); iter != mainDevice->end(); iter++) {
		directions[iter->first]        = tlinsServerDirectionInfo::IDLE;
		statusNeeded[iter->first]      = false;
		statusNeededStart[iter->first] = false;
	}

	requestStatusInfo.clear();
	axisToRequestStatus.clear();

	// Nowy tryb
	serverMode = mode;

	switch (serverMode) {
	case tlinsSerialServerMode::MODE_SYNCHRONISED:
		// Wlaczenie synchronicznego sterowania przemieszczeniem na kontrolerze
		mainDevice->enableSynchMode();
		break;

	case tlinsSerialServerMode::MODE_SEPARATE_AXIS:
		// Wylaczenie synchronicznego sterowania przemieszczeniem na kontrolerze
		mainDevice->disableSynchMode();
		break;
	}

	// Tworzenie rzadania awaryjnego (ABORT) zatrzymania wszystkich osi
	auto ptr = std::make_shared<tlinsSerialDeviceMoveRequest>(
	    tlinsSerialMoveType::ABORT, tlinsSerialMoveInterpolationType::LAST, tlinsSerialMoveModeRelAbs::LAST, 0, 0, 0);

	// Wstawienie zadania pilnego
	priorityRequestQueue.enqueueFront(ptr);
}

void MainDeviceMoreRequestsThread::enqueRequest(const std::shared_ptr<tlinsSerialDeviceMoveRequest> &req,
                                                const tlinsSerialServerMode                          serverMode_)
{
	// Dostep do kolejki rzadan jest atomowy
	std::lock_guard<std::recursive_mutex> lock(serverMtx);

	// Weryfikacja rzadania - czy  przekazane osie sa poprawne
	for (auto i = req->begin(); i != req->end(); i++) {
		if (mainDevice->find(i->first) == mainDevice->end())
			__THROW__(
			    tlinsSerialDeviceException("Incorrect request", tlinsSerialDeviceException::ERROR_MOVE_REQUEST_DATA));

		// Sprawdzenie predkosci jesli przekracza maksymalna to ogranczenie
		std::shared_ptr<tlinsSerialDevice> dev;
		mainDevice->getDevice(i->first, dev);

		if (i->second.getV() > dev->getMaxSpeed()) {
			i->second.setV(static_cast<unsigned long>(dev->getMaxSpeed()));
		}
	}

	// Oczekiwany tryb pracy
	tlinsSerialServerMode expectedMode{tlinsSerialServerMode::MODE_NONE};
	switch (req->getMode()) {
	case tlinsSerialMoveType::SPEED:
		expectedMode = tlinsSerialServerMode::MODE_SEPARATE_AXIS;
		break;
	case tlinsSerialMoveType::POSITION:
		expectedMode = tlinsSerialServerMode::MODE_SYNCHRONISED;
		break;
	case tlinsSerialMoveType::STOP:
		expectedMode = tlinsSerialServerMode::MODE_NONE;
		break;
	case tlinsSerialMoveType::ABORT:
		expectedMode = tlinsSerialServerMode::MODE_NONE;
		break;
	case tlinsSerialMoveType::STOP_CTRL:
		expectedMode = tlinsSerialServerMode::MODE_NONE;
		break;
	case tlinsSerialMoveType::LAST:
		expectedMode = tlinsSerialServerMode::MODE_NONE;
		break;
	}

	if (serverMode != expectedMode && expectedMode != tlinsSerialServerMode::MODE_NONE) {
		TLINS_LOG_ERROR("------------------------- ZMIANA trybu pracy dpasowanego do przemieszczenia "
		                "-------------------------------------");
		enforceServerMode(expectedMode);
	}

	// Informacja o statusie rzadania
	auto statPtr = std::make_shared<RequestStatusInfo>(req);

	// Dodanie informacji o statusie
	requestStatusInfo[req->getRequestID()] = statPtr;

	// Tylko ABORT bedzie wstawiany do kolejki piorytetowej. Wszystkie inne beda wstawiuane do kolejki wejsciowej. STOP
	// i STOP_CTRL bedzie wstawiany na poczatek kolejki
	if (req->getMode() == tlinsSerialMoveType::ABORT) {
		// Rzadanie typu ABORT - wstawiane na poczatek kolejki piorytetowej
		priorityRequestQueue.enqueueFront(req);

		// Powiadomienie watku glowego o tym ze do kolejki/kolejek per os zostalo dodane nowe rzadanie
		signalThread();
		return;
	}

	if (serverMode == tlinsSerialServerMode::MODE_SEPARATE_AXIS) {
		for (auto i = req->begin(); i != req->end(); i++) {
			if (req->getMode() == tlinsSerialMoveType::STOP_CTRL || req->getMode() == tlinsSerialMoveType::STOP) {
				axisRequests[i->first].enqueueFront(req);
			} else {
				axisRequests[i->first].enqueue(req);
			}
		}
	} else {
		// Tryb tlinsSerialServerMode::MODE_SYNCHRONISED
		if (req->getMode() == tlinsSerialMoveType::STOP_CTRL || req->getMode() == tlinsSerialMoveType::STOP) {
			requestQueue.enqueueFront(req);
		} else {
			requestQueue.enqueue(req);
		}
	}

	// Powiadomienie watku glowego o tym ze do kolejki/kolejek per os zostalo dodane nowe rzadanie
	signalThread();
}

bool MainDeviceMoreRequestsThread::setNextRequestPriorityQueue()
{
	std::shared_ptr<tlinsSerialDeviceMoveRequest> inputRequest;

	if (!priorityRequestQueue.dequeue(inputRequest)) {
		return false;
	}

	// Lambda wysylajaca potwierdzenia o rzadanaich ktore zostaly odrzucone
	auto reqConfLambda = [this](std::shared_ptr<tlinsSerialDeviceMoveRequest> &req) {
		for (auto &ii : this->requestStatusInfo) {
			if (req->getRequestID() != ii.second->request->getRequestID()) {
				confirmRequest(ii.second->request, tlinsSerialRequestStatusResult::STATUS_REJECTED);
			}
		}
	};

	std::vector<std::string> toBeConfirmed{};

	if (inputRequest->getMode() == tlinsSerialMoveType::ABORT) {
		// Wyslanie potwierdzenia ze wszystkie zlecenia zostaly odrzucone
		reqConfLambda(inputRequest);

		// Wyczyszczenie wszystkich kolejek
		requestQueue.clear();
		axisRequests.clear();

		// Oproznienie kolejek i pol kontrolnych
		for (auto &iter : directions) {
			iter.second                   = tlinsServerDirectionInfo::IDLE;
			statusNeeded[iter.first]      = false;
			statusNeededStart[iter.first] = false;
		}

		// Przygotowanie informacji kontrolnej w celu potwierdzenia ze rzadanie
		// awaryjnego zatrzymania zostalo zrealizowane. W requestStatusInfo powinna
		// Znajdowac sie informacja o bierzacym rzadaniu
		auto aStatus = requestStatusInfo.find(inputRequest->getRequestID());
		if (aStatus != requestStatusInfo.end()) {
			// Inicializacja osi
			aStatus->second->reset();
			requestStatusInfo[aStatus->first] = aStatus->second;

			// Ustawienie statusow dla wszystkich osi
			for (auto iter = mainDevice->begin(); iter != mainDevice->end(); iter++) {
				auto axisName = iter->first;

				// Oznaczenie ze wymagamy potwierdzenia
				statusNeeded[axisName]      = inputRequest->needConfirmation();
				statusNeededStart[axisName] = false;
				toBeConfirmed.push_back(axisName);

				// Zapisanie statusu
				axisToRequestStatus[axisName] = aStatus->second;

				// Okreslenie ile osi ma byc potwierdzonych
				aStatus->second->addAxis(axisName);
			}
		}

		requestStatusInfo.clear();
		axisToRequestStatus.clear();

		// Fizyczne awaryjne zatrzymanie calego urzadzenia
		try {
			mainDevice->abort();
			for (auto &iter : toBeConfirmed) {
				statusNeededStart[iter] = true;

				// Identyfikator potwierdzenia
				auto id = mainDevice->getNextConfId();
				mainDevice->setConfId(iter, id);
				reqIdsMap[iter] = id;
			}
		}
		catch (...) {
			TLINS_LOG_ERROR("Error abort device");
		}
	}
	return true;
}

/*
 * Metoda odpowiedzialna jest za zatrzymanie wskazanej osi kontrolera
 * Zatrzymanie standardowe
 */
void MainDeviceMoreRequestsThread::stopSelectedAxis(const std::string                                   &a,
                                                    const std::shared_ptr<tlinsSerialDeviceMoveRequest> &req)
{
	// Usuniecie wszystkich zadan z kolejki dla danej osi i oznaczenie ze zostaly odrzucone
	// Biezace zadanie zostalo juz usuniete z kolejki
	auto &queue = axisRequests[a];
	do {
		// Odczyt kolejki
		std::shared_ptr<tlinsSerialDeviceMoveRequest> rmReq;
		bool                                          end = queue.dequeue(rmReq);
		if (!end) {
			break;
		}

		auto statPtr = requestStatusInfo[rmReq->getRequestID()];
		statPtr->confirm(a, tlinsSerialRequestStatusResult::STATUS_REJECTED);

		if (statPtr->isConfirmed()) {
			// Potwierdzenie rzadania
			confirmRequest(rmReq);

			// Usuniecie rzadania z mapy
			requestStatusInfo.erase(rmReq->getRequestID());
		}
	} while (true);

	// Jesli os jest w trakcie przetwarzania rzadania to bierzace rzadanie
	// zatrzymujemy
	if (directions[a] != tlinsServerDirectionInfo::IDLE) {
		// Biezaca os jest w trakcie przetwarzania
		// 1. Oznaczenie ze skladowa rzadania zostala przerwana
		{
			auto statusInfoCurr = axisToRequestStatus[a];

			statusInfoCurr->confirm(a, tlinsSerialRequestStatusResult::STATUS_REJECTED);
			statusNeeded[a]      = false;
			statusNeededStart[a] = false;

			// Usuniecie informacji o statusie
			axisToRequestStatus.erase(a);

			// Gdy wszystkie skladowe zostaly potwierdzone wyslanie potwierdzenia
			if (statusInfoCurr->isConfirmed()) {
				// Potwierdzenie rzadania
				auto ptrReq = statusInfoCurr->request;
				confirmRequest(ptrReq);

				// Usuniecie rzadania z mapy
				requestStatusInfo.erase(ptrReq->getRequestID());
			}
		}
	}

	// Nowe rzadanie w tym wyslanie polecenia do urzadzenia
	// 1. Informacja potrzebna do potwierdzenia zlecenia
	auto statusInfo        = requestStatusInfo[req->getRequestID()];
	axisToRequestStatus[a] = statusInfo;

	directions[a]        = tlinsServerDirectionInfo::ANY;
	statusNeeded[a]      = true;
	statusNeededStart[a] = false;

	// Wyslanie wlasciwego rzadania do urzadzenia. Zakladamy ze rzadanie zostalo wczesniej zwalidowane
	// Przekazana os musi byc poprawna
	auto aDevIter = mainDevice->find(a);
	auto aDev     = aDevIter->second;

	// Ustawienie parameterow rampy
	auto aReq = (*req)[a];
	aDev->setRampParameters(aReq.getA(), aReq.getD(), 0);

	// 2. Wygenerowanie rzadania stopu do kontrolera ruchu
	aDev->stop();
	statusNeededStart[a] = true;

	// Identyfikator potwierdzenia
	auto id = mainDevice->getNextConfId();
	mainDevice->setConfId(a, id);
	reqIdsMap[a] = id;
}

void MainDeviceMoreRequestsThread::speedSelectAxis(const std::string                                   &a,
                                                   const std::shared_ptr<tlinsSerialDeviceMoveRequest> &req)
{
	// Status osi
	axisToRequestStatus[a] = requestStatusInfo[req->getRequestID()];
	auto statusInfo        = axisToRequestStatus[a];
	statusNeeded[a]        = false;
	statusNeededStart[a]   = false;

	TLINS_LOG_DEBUG("DDDDDDDDDDD:1");

	// Kierunek obrotu
	auto aReq = (*req)[a];
	switch (aReq.getDirection()) {
	case tlinsSerialDirection::LEFT:
		TLINS_LOG_DEBUG("DDDDDDDDDDD:2");
		directions[a] = tlinsServerDirectionInfo::LEFT;
		break;

	case tlinsSerialDirection::RIGHT:
		TLINS_LOG_DEBUG("DDDDDDDDDDD:3");
		directions[a] = tlinsServerDirectionInfo::RIGHT;
		break;

	default:
		TLINS_LOG_DEBUG("DDDDDDDDDDD:4");
		// Bledne dane rzadania - przekazanie statusu
		statusInfo->confirm(a, tlinsSerialRequestStatusResult::STATUS_ERROR);
		statusNeeded[a]      = false;
		statusNeededStart[a] = false;
		if (statusInfo->isConfirmed()) {
			// Potwierdzenie rzadania
			auto ptrReq = statusInfo->request;
			confirmRequest(ptrReq);

			// Usuniecie rzadania z mapy
			requestStatusInfo.erase(req->getRequestID());
			axisToRequestStatus.erase(a);
		}
		return;
	}

	TLINS_LOG_DEBUG("DDDDDDDDDDD:5");

	TLINS_LOG_DEBUG(a + "; A = " + std::to_string(aReq.getA()) + "; D = " + std::to_string(aReq.getD()) +
	                "; V = " + std::to_string(aReq.getV()) + "; DIR = " + std::to_string((int) aReq.getDirection()));

	// Wyslanie wlasciwego rzadania do urzadzenia. Zakladamy ze rzadanie zostalo wczeniej potwierdzone
	// Urzadzeni enie bedzie weryfikowane
	auto aDevIter = mainDevice->find(a);
	TLINS_LOG_DEBUG("DDDDDDDDDDD:6");
	auto aDev = aDevIter->second;
	TLINS_LOG_DEBUG("DDDDDDDDDDD:7");
	// aDev->setRampParameters(aReq.getA(), aReq.getD(), aReq.getV());
	aDev->setRampParametersSpeed(aReq.getA(), aReq.getD());

	TLINS_LOG_DEBUG("DDDDDDDDDDD:8");
	aDev->setSpeed(aReq.getV(), aReq.getDirection());
	TLINS_LOG_DEBUG("DDDDDDDDDDD:9");
}

void MainDeviceMoreRequestsThread::positionSelectAxis(const std::string                                   &a,
                                                      const std::shared_ptr<tlinsSerialDeviceMoveRequest> &req)
{
	axisToRequestStatus[a] = requestStatusInfo[req->getRequestID()];
	auto statusInfo        = axisToRequestStatus[a];
	statusNeeded[a]        = true;
	statusNeededStart[a]   = false;

	// Kierunek obrotu
	auto aReq = (*req)[a];
	switch (aReq.getDirection()) {
	case tlinsSerialDirection::LEFT:
		directions[a] = tlinsServerDirectionInfo::LEFT;
		break;

	case tlinsSerialDirection::RIGHT:
		directions[a] = tlinsServerDirectionInfo::RIGHT;
		break;

	default:
		// Bledne dane rzadania - przekazanie statusu
		statusInfo->confirm(a, tlinsSerialRequestStatusResult::STATUS_ERROR);
		statusNeeded[a]      = false;
		statusNeededStart[a] = false;
		if (statusInfo->isConfirmed()) {
			// Potwierdzenie rzadania
			auto ptrReq = statusInfo->request;
			confirmRequest(ptrReq);

			// Usuniecie rzadania z mapy
			requestStatusInfo.erase(req->getRequestID());
			axisToRequestStatus.erase(a);
		}
		return;
	}

	// Wyslanie wlasciwego rzadania do urzadzenia
	auto aDevIter = mainDevice->find(a);
	auto aDev     = aDevIter->second;

	// Ustawienie parameterow rampy
	aDev->setRampParameters(aReq.getA(), aReq.getD(), aReq.getV());

	aDev->stop();
	if (req->getMoveType() == tlinsSerialMoveModeRelAbs::REL) {
		aDev->setPosition(aReq.getDistance(), aReq.getDirection());
	} else {
		aDev->setPosition(aReq.getDistance());
	}
	statusNeededStart[a] = true;

	// Identyfikator potwierdzenia
	auto id = mainDevice->getNextConfId();
	mainDevice->setConfId(a, id);
	reqIdsMap[a] = id;
}

std::shared_ptr<tlinsSerialDeviceMoveRequest>
MainDeviceMoreRequestsThread::createCtrlStopRequest(const std::vector<std::string> &axies)
{
	std::shared_ptr<tlinsSerialDeviceMoveRequest> resReq;
	auto ptr = new tlinsSerialDeviceMoveRequest(tlinsSerialMoveType::STOP_CTRL, tlinsSerialMoveInterpolationType::LAST,
	                                            tlinsSerialMoveModeRelAbs::LAST, 0L, 0L, 0L);

	for (auto &a : axies) {
		ptr->append(a, tlinsSerialDevicePositionRequestAxis(0L, 0L, 0L, tlinsSerialDirection::LAST, 0L));
	}
	return std::shared_ptr<tlinsSerialDeviceMoveRequest>(ptr);
}

void MainDeviceMoreRequestsThread::setNextStandardRequestAxis()
{
	// Sprawdzenie rodzaju zadania na poczatku kolejki
	for (auto &aiter : axisRequests) {
		// Przejscie po wszystkich kolejkach
		auto &queue = aiter.second;
		auto  aname = aiter.first;

		// Nastepna os jesli nie ma nic w kolejce wejsciowej
		if (queue.isEmpty()) {
			continue;
		}

		// Sprawdzenie czy komunikat w kolejce to zatrzymanie
		std::shared_ptr<tlinsSerialDeviceMoveRequest> req;
		queue.getFront(req);

		TLINS_LOG_ERROR("RRRR : 3");

		// Rodzaj przemieszczenuia oraz kierunek przemieszczenia
		auto rType = req->getMode();

		// tlinsServerDirectionInfo rDir = tlinsServerDirectionInfo::IDLE;
		switch ((*req)[aname].getDirection()) {
		case tlinsSerialDirection::LEFT:
			TLINS_LOG_ERROR("RRRR : 4");
			// rDir = tlinsServerDirectionInfo::LEFT;
			break;

		case tlinsSerialDirection::RIGHT:
			TLINS_LOG_ERROR("RRRR : 5");
			// rDir = tlinsServerDirectionInfo::RIGHT;
			break;
		}

		if (rType == tlinsSerialMoveType::STOP) {
			TLINS_LOG_ERROR("RRRR : 6");
			queue.popFront();
			stopSelectedAxis(aname, req);
			continue;
		} else {
			TLINS_LOG_ERROR("RRRR : 7");
			bool send = false;

			// Aktualny kierunek obrotu
			auto aDir = tlinsServerDirectionInfo::IDLE;
			if (directions.count(aname) == 0) {
				aDir = directions[aname];
			}
			if (aDir != tlinsServerDirectionInfo::IDLE) {
				TLINS_LOG_ERROR("RRRR : 8");
				// Typ aktualnego przemieszczenia
				auto aType = axisToRequestStatus[aname]->request->getMode();
				if (aType != tlinsSerialMoveType::SPEED) {
					TLINS_LOG_ERROR("RRRR : 9");
					// Czekamy na zakonczenie pracy biezacej osi
					continue;
				} else {
					TLINS_LOG_ERROR("RRRR : 10");
					send = true;
				}
			} else {
				TLINS_LOG_ERROR("RRRR : 11");
				// Os nie jest zajeta moze robic cos nowego
				send = true;
			}
			TLINS_LOG_ERROR("RRRR : 12");

			if (send) {
				TLINS_LOG_ERROR("RRRR : 13");
				queue.popFront();

				switch (rType) {
				case tlinsSerialMoveType::SPEED:
					TLINS_LOG_ERROR("RRRR : 14");
					speedSelectAxis(aname, req);
					break;

				case tlinsSerialMoveType::POSITION:
					TLINS_LOG_ERROR("RRRR : 15");
					positionSelectAxis(aname, req);
					break;
				}
			}
		}
	}
}

void MainDeviceMoreRequestsThread::stopRequestSynch(const std::shared_ptr<tlinsSerialDeviceMoveRequest> &req)
{
	// Sprawdzenie czy wszystkie skladowe rzadania sa potwierdzone
	for (auto item = directions.begin(); item != directions.end(); item++) {
		// Oznaczenie skladowej jako przerwana
		if (item->second != tlinsServerDirectionInfo::IDLE) {
			// Potwierdzenie dla biezacej osi
			auto aStatus = axisToRequestStatus[item->first];
			aStatus->confirm(item->first, tlinsSerialRequestStatusResult::STATUS_REJECTED);

			if (aStatus->isConfirmed()) {
				// Potwierdzenie rzadania
				auto ptrReq = aStatus->request;
				confirmRequest(ptrReq);

				// Usuniecie rzadania z mapy
				requestStatusInfo.erase(ptrReq->getRequestID());
			}
		}

		// Status nie jest wymagany
		statusNeeded[item->first]      = false;
		statusNeededStart[item->first] = false;
		item->second                   = tlinsServerDirectionInfo::IDLE;
	}

	// Wyczyszczenie statusu per os
	axisToRequestStatus.clear();

	// Czyszczenie kolejki wejsciowej
	std::shared_ptr<tlinsSerialDeviceMoveRequest> inReq;
	while (requestQueue.dequeue(inReq)) {
		// Wyslanie potwierdzenia ze zadanie zostalo odrzucone
		confirmRequest(inReq);

		// Usuniecie rzadania
		requestStatusInfo.erase(inReq->getRequestID());
	}

	// Informacja o bierzacym rzadaniu
	auto inRequestStatus = requestStatusInfo[req->getRequestID()];
	inRequestStatus->reset();

	// Wygenerowanie rzadania zatrzymania dla wszystkich osi oraz zapisanie statusu
	for (auto devIter = mainDevice->begin(); devIter != mainDevice->end(); devIter++) {
		// Nazwa osi
		auto axisName = devIter->first;

		// Oznaczenie ze potwierdzenie jest wymagane
		statusNeeded[axisName]      = true;
		statusNeededStart[axisName] = false;

		// Status przetwarzania
		axisToRequestStatus[axisName] = inRequestStatus;
		inRequestStatus->addAxis(axisName);

		// Kierunek obrotu
		directions[axisName] = tlinsServerDirectionInfo::ANY;
	}

	// Fizyczne zatrzymanie wszystkich osi
	for (auto devIter = mainDevice->begin(); devIter != mainDevice->end(); devIter++) {
		// Nazwa osi
		auto axisName = devIter->first;

		// Urzadzenie skladowe
		auto dev = devIter->second;

		// Fizyczne zatrzymanie osi
		dev->stop();

		statusNeededStart[axisName] = true;

		// Identyfikator potwierdzenia
		auto id = mainDevice->getNextConfId();
		mainDevice->setConfId(axisName, id);
		reqIdsMap[axisName] = id;
	}
}

void MainDeviceMoreRequestsThread::moveRequestSynch(const std::shared_ptr<tlinsSerialDeviceMoveRequest> &req)
{
	// Funkcja zakłada ze rzadanie zostalo wczesniej zweryfikowane
	auto reqStatus = requestStatusInfo[req->getRequestID()];

	reqStatus->reset();

	// Czyszczenie mapy potwierdzen
	axisToRequestStatus.clear();
	directions.clear();

	// Wygenerowanie przemieszczenia
	std::set<std::string> aInput{};

	for (auto item = req->begin(); item != req->end(); item++) {
		// Szczegoly rzadania
		auto axisName = item->first;
		auto reqAxis  = item->second;

		aInput.insert(axisName);

		// Licznik potwierdzen
		reqStatus->addAxis(axisName);

		// Oznaczenie kierunkru
		directions[axisName] = tlinsServerDirectionInfo::ANY;

		// Statusy
		statusNeeded[axisName]        = true;
		statusNeededStart[axisName]   = false;
		axisToRequestStatus[axisName] = reqStatus;

		// Ustawienie parameterow rampy
		// Parametery rampy sa identyczne dla wszystkich osi
		auto devIter = mainDevice->find(axisName);

		devIter->second->stop();

		devIter->second->setLinRampParameters(reqAxis.getA(), reqAxis.getD(), reqAxis.getV());

		// Pozycja docelowa
		if (req->getMoveType() == tlinsSerialMoveModeRelAbs::REL) {
			devIter->second->setPosition(reqAxis.getDistance(), reqAxis.getDirection());
		} else {
			devIter->second->setPosition(reqAxis.getDistance());
		}
	}

	// Gdy przemieszczenie relatywne dodajemy brakujace osie
	if (req->getMoveType() == tlinsSerialMoveModeRelAbs::REL) {
		for (auto devIter : *mainDevice) {
			if (aInput.count(devIter.first) == 0) {
				devIter.second->setPosition(0L, tlinsSerialDirection::LEFT);
			}
		}
	}

	for (auto &item : *req) {
		statusNeededStart[item.first] = true;

		// Identyfikator potwierdzenia
		auto id = mainDevice->getNextConfId();
		mainDevice->setConfId(item.first, id);
		reqIdsMap[item.first] = id;
	}

	// Uruchomienie przemieszczenia w trybie interpolacji
	if (req->getMoveType() == tlinsSerialMoveModeRelAbs::REL) {
		mainDevice->triggerRelPos();
	} else {
		mainDevice->triggerAbsPos();
	}
}

void MainDeviceMoreRequestsThread::setNextSynchronusRequest()
{
	// Jesli kolejka wejsciowa jest pusta nic nie robimy
	if (requestQueue.isEmpty()) {
		return;
	}

	// Pobranie komunikatu z kolejki
	std::shared_ptr<tlinsSerialDeviceMoveRequest> req;
	requestQueue.getFront(req);

	if (req->getMode() == tlinsSerialMoveType::STOP) {
		// Rzadanie typu stop - zatrzymujemy
		requestQueue.popFront();
		stopRequestSynch(req);
		return;
	}

	// Sprawdzenie czy wszystkie skladowe rzadania sa potwierdzone
	bool allConfirmed = true;
	for (auto &item : directions) {
		if (statusNeeded[item.first] && item.second != tlinsServerDirectionInfo::IDLE) {
			allConfirmed = false;
			break;
		}
	}

	if (!allConfirmed) {
		return;
	}

	// Zlecenie przemieszczenia
	requestQueue.popFront();
	moveRequestSynch(req);
}

void MainDeviceMoreRequestsThread::setNextRequest()
{
	std::lock_guard<std::recursive_mutex> lock(serverMtx);

	//
	// W pierwszej kolejnosci przetwarzamy kolejke piorytetowa
	// Kolejka piorytetowa jest wspolna dla obu trybow
	//
	if (!priorityRequestQueue.isEmpty()) {
		// Odczyt rzadania z kolejki
		setNextRequestPriorityQueue();

		// Powrot
		return;
	}

	if (serverMode == tlinsSerialServerMode::MODE_SEPARATE_AXIS) {
		// Kolejne rzadanie asynchroniczne
		setNextStandardRequestAxis();
	} else {
		// Kolejne rzadanie synchroniczne
		setNextSynchronusRequest();
	}
}

void MainDeviceMoreRequestsThread::operator()()
{
	// Petla glowna
	while (!isEnd()) {
		// Oczekiwanie na sygnal na zmiennej warunkowej
		{
			std::unique_lock<std::mutex> lock(serverMtxCv);
			auto wstat = serverCv.wait_for(lock, std::chrono::microseconds{1000}); // Czekami 1.0 ms
		}

		if (isEnd()) {
			//
			// Weryfikacja stanu napedu
			//
			std::vector<std::pair<std::string, tlinsSerialMainDevice::ConfirmationInfo>> data;
			for (auto &iter : *mainDevice) {
				int16_t aStatus;
				auto    aName = iter.first;

				if (statusNeeded.find(aName) == statusNeeded.end()) {
					continue;
				}

				if (!statusNeeded[aName]) {
					continue;
				}

				// Odczyt statusu
				iter.second->get_dev_M_STATUS(aStatus);
				if (aStatus == 1 || aStatus == 4 || aStatus == 8) {
					// Status npedu nie jest wlasciwy
					tlinsSerialMainDevice::ConfirmationInfo d;
					d.confType = tlinsSerialMainDevice::ConfirmationType::COMPLETED;
					d.confID   = 0;
					data.emplace_back(std::pair<std::string, tlinsSerialMainDevice::ConfirmationInfo>{aName, d});
				}
			}

			confirmMove(data);

			// Wyslanie potwierdzen o przerwanych rzadaniach oczekujacych w kolejce
			// 1. Rzadania synchroniczne
			std::shared_ptr<tlinsSerialDeviceMoveRequest> inReq;
			for (auto &item : requestStatusInfo) {
				// Wyslanie potwierdzenia ze zadanie zostalo odrzucone
				confirmRequest(item.second->request, tlinsSerialRequestStatusResult::STATUS_REJECTED);
			}
			// Wyczyszczenie listy
			requestStatusInfo.clear();

			// Koniec petli
			break;
		}

		// Przetwarzanie rzadania
		setNextRequest();
	}
}

void MainDeviceMoreRequestsThread::join()
{
	if (th->joinable()) {
		th->join();
	}
}

MainDeviceMoreRequestsThread::MainDeviceMoreRequestsThread(const std::shared_ptr<tlinsSerialMainDevice> &mainDevice_)
    : mainDevice{mainDevice_}
{
	auto thread_ = new std::thread(std::ref(*this));
	th           = std::unique_ptr<std::thread>(thread_);

	mainDevice->addCallback(
	    [this](const std::vector<std::pair<std::string, tlinsSerialMainDevice::ConfirmationInfo>> &s) {
		    this->confirmMove(s);
	    });

	for (auto &iter : *mainDevice) {
		directions[iter.first] = tlinsServerDirectionInfo::IDLE;
	}
}

MainDeviceMoreRequestsThread::~MainDeviceMoreRequestsThread()
{
	// Przerwanie petli glownej
	endThread();
}

//
// ----------------------------------------------------------------------------------------
// ----------------------------------------------------------------------------------------
//   Implemanetacja klasy serwera
// ----------------------------------------------------------------------------------------
// ----------------------------------------------------------------------------------------
//

void tlinsSerialServer::colistionsDetectionRegisterConfirmation(const std::string &devName, const std::string &id)
{
	std::unique_lock<std::mutex> lock(mtx);

	// Wyszukanie watku urzadzennia
	auto item = serverLimits.find(devName);
	if (item == serverLimits.end()) {
		__THROW__(tlinsSerialDeviceException("Uknown main device", tlinsSerialDeviceException::ERROR_UNKNOWN_DEVICE));
	}
	item->second->registerConfirmation(id);
}

void tlinsSerialServer::addColistionDefinition(const std::string &devName, const Eigen::Vector3d &v1,
                                               const Eigen::Vector3d &v2)
{
	std::unique_lock<std::mutex> lock(mtx);

	// Wyszukanie watku urzadzennia
	auto item = serverLimits.find(devName);
	if (item == serverLimits.end()) {
		__THROW__(tlinsSerialDeviceException("Uknown main device", tlinsSerialDeviceException::ERROR_UNKNOWN_DEVICE));
	}

	item->second->addLimitDefinition(v1, v2);
}


bool tlinsSerialServer::colistionsDetectionTest(const std::string &devName, const Eigen::Vector3d &position)
{
	std::unique_lock<std::mutex> lock(mtx);

	auto item = serverLimits.find(devName);
	if (item == serverLimits.end()) {
		__THROW__(tlinsSerialDeviceException("Uknown main device", tlinsSerialDeviceException::ERROR_UNKNOWN_DEVICE));
	}
	return item->second->checkColision(position);
}


void tlinsSerialServer::enableColistionsDetection(const std::string &devName)
{
	std::unique_lock<std::mutex> lock(mtx);

	// Wyszukanie watku urzadzennia
	auto item = serverLimits.find(devName);
	if (item == serverLimits.end()) {
		__THROW__(tlinsSerialDeviceException("Uknown main device", tlinsSerialDeviceException::ERROR_UNKNOWN_DEVICE));
	}
	return item->second->startMonitoring();
}

void tlinsSerialServer::disableColistionsDetection(const std::string &devName)
{
	std::unique_lock<std::mutex> lock(mtx);

	// Wyszukanie watku urzadzennia
	auto item = serverLimits.find(devName);
	if (item == serverLimits.end()) {
		__THROW__(tlinsSerialDeviceException("Uknown main device", tlinsSerialDeviceException::ERROR_UNKNOWN_DEVICE));
	}
	return item->second->stopMonitoring();
}


void tlinsSerialServer::setServerMode(const std::string &devName, const tlinsSerialServerMode mode)
{
	std::unique_lock<std::mutex> lock(mtx);

	// Wyszukanie watku urzadzennia
	auto item = serverThreads.find(devName);
	if (item == serverThreads.end()) {
		__THROW__(tlinsSerialDeviceException("Uknown main device", tlinsSerialDeviceException::ERROR_UNKNOWN_DEVICE));
	}
	item->second->setServerMode(mode);
}

tlinsSerialServerMode tlinsSerialServer::getServerMode(const std::string &devName)
{
	std::unique_lock<std::mutex> lock(mtx);

	// Wyszukanie watku urzadzennia
	auto item = serverThreads.find(devName);
	if (item == serverThreads.end()) {
		__THROW__(tlinsSerialDeviceException("Uknown main device", tlinsSerialDeviceException::ERROR_UNKNOWN_DEVICE));
	}
	return item->second->getServerMode();
}

bool tlinsSerialServer::registerDevice(const std::string &devName, const std::shared_ptr<tlinsSerialMainDevice> &dev)
{
	std::unique_lock<std::mutex> lock(mtx);

	if (serverThreads.find(devName) != serverThreads.end()) {
		return false;
	}

	// Rejestracja watku
	serverThreads[devName] = std::make_shared<MainDeviceMoreRequestsThread>(dev);

	return true;
}

bool tlinsSerialServer::registerDeviceLimit(const std::string                            &devName,
                                            const std::shared_ptr<tlinsSerialMainDevice> &dev)
{
	std::unique_lock<std::mutex> lock(mtx);

	if (serverLimits.find(devName) != serverLimits.end() || serverThreads.count(devName) == 0) {
		// Jesli limit jest juz zarejestrowany lub brak odpowiadajacego watku
		return false;
	}

	// Definicja limitu
	DeviceLimitDeviceDefinition limitsDef{};

	limitsDef.h         = dev->getLimitsH();
	limitsDef.r1        = dev->getLimitsR1();
	limitsDef.r2        = dev->getLimitsR2();
	limitsDef.dx        = dev->getLimitsDX();
	limitsDef.dz        = dev->getLimitsDZ();
	limitsDef.frequency = dev->getLimitsFrequency();

	// Parametery podstawy
	limitsDef.legs           = dev->getLimitsLegs();
	limitsDef.legRadius      = dev->getLimitsLegRadius();
	limitsDef.legsZOffset    = dev->getLimitsLegsZOffset();
	limitsDef.legsStartAngle = dev->getLimitsLegsSartAngle();
	limitsDef.legsAngle      = dev->getLimitsLegsAngle();
	limitsDef.tubeRadius     = dev->getLimitsTubeRadius();
	limitsDef.baseRadius     = dev->getLimitsBaseRadius();
	limitsDef.baseLength     = dev->getLimitsBaseLength();

	for (const auto &item : dev->getLimitsAxisAngles()) {
		limitsDef.addAngle(item.first, item.second);
	}

	// Wlasciwy obiekt analizujacy limity
	auto newLimit = std::make_shared<MainDeviceLimit>(serverThreads[devName], limitsDef);

	// Rejestracja managera limitow
	serverLimits[devName] = newLimit;
	return true;
}

void tlinsSerialServer::enqueRequest(const std::string                                   &devName,
                                     const std::shared_ptr<tlinsSerialDeviceMoveRequest> &req,
                                     const tlinsSerialServerMode                          serverMode_)
{
	std::unique_lock<std::mutex> lock(mtx);

	auto item = serverThreads.find(devName);
	if (item == serverThreads.end()) {
		__THROW__(tlinsSerialDeviceException("Uknown main device", tlinsSerialDeviceException::ERROR_UNKNOWN_DEVICE));
	}

	// Wstawienie rzadania do kolejki
	item->second->enqueRequest(req);
}

void tlinsSerialServer::end()
{
	std::unique_lock<std::mutex> lock(mtx);

	for (const auto &item : serverThreads) {
		item.second->endThread();
		item.second->join();
	}

	std::for_each(serverLimits.begin(), serverLimits.end(),
	              [&](const std::pair<std::string, std::shared_ptr<MainDeviceLimit>> &item) {
		              item.second->endTrack();
		              item.second->join();
	              });
}

tlinsSerialServer::~tlinsSerialServer()
{
	// Zakonczenie
	end();

	// Niszczenie watkow
	for (auto &item : serverThreads) {
		item.second.reset();
	}

	// Niszczenie watkow
	for (auto &item : serverLimits) {
		item.second.reset();
	}
}
