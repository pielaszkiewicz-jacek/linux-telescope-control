#include <parameters/tlins_parameters.hpp>
#include <tlinAttitudeUtilsClass.hpp>
#include <tlinsAstroEnginConfiguration.hpp>
#include <tlinsAstroEngineExt.hpp>
#include <tlinsAstroParameters.hpp>
#include <tlinsBacktrace.hpp>
#include <tlinsIERSInfoManager.hpp>
#include <tlinsId.hpp>
#include <tlinsStarApparentPlaceCalculationSofa.hpp>
#include <tlinsTimeInfo.hpp>
#include <tlins_math.hpp>

#include <Eigen/Eigenvalues>
#include <Eigen/Geometry>
#include <chrono>
#include <condition_variable>
#include <sofa.h>
#include <sofam.h>
#include <sys/time.h>

#define _USE_MATH_DEFINES
#include <algorithm>
#include <cmath>

#include <fcntl.h>
#include <sys/stat.h>

/*
    Bardzo wazne:
    Kierunki obrotu i orientacja układu wspolrzednych

    W prawo (true)  - kierunek odpowiada malejacym wartosciom konta
    W lewo  (false) - odpowiada rosnacym wartosciomn przyrostu konta
*/

tlinsAstroEngine::TimeStatistics::TimeStatistics(const double processingTime_, const double processingTimeCalculation_,
                                                 const double processingTimeMoveRequest_)
    : processingTime{processingTime_},
      processingTimeCalculation{processingTimeCalculation_},
      processingTimeMoveRequest{processingTimeMoveRequest_} {};

tlinsAstroEngine::TimeStatistics::TimeStatistics()
    : processingTime{0.0}, processingTimeCalculation{0.0}, processingTimeMoveRequest{0.0} {};


tlinsAstroEngine::PositionRequestInfo::PositionRequestInfo(double delatMoveX_, double delatMoveY_,
                                                           std::chrono::duration<double, std::milli> &moveTime_)
    : delatMoveX{delatMoveX_}, delatMoveY{delatMoveY_}, moveTime{moveTime_} {};

tlinsAstroEngine::PositionRequestInfo::PositionRequestInfo() : delatMoveX{0.0}, delatMoveY{0.0}
{
}

//
// ----------------------------------------------------------------------
//

bool tlinsAstroEngine::isTrackingActive() const
{
	return !standardRunCtrl;
}

const tlinsAstroEngine::ENGINE_STATE tlinsAstroEngine::getState() const
{
	return state;
}

const int tlinsAstroEngine::iterationCount() const
{
	return attitudeProcess->size();
}

void tlinsAstroEngine::trackingStatusGet(bool &status, double &ra, double &dec) const
{
	status = trackIsActive;
	ra     = trackSpeedRa;
	dec    = trackSpeedDec;
}

void tlinsAstroEngine::addTimeStatistic(const double processingTime, const double processingTimeCalculation,
                                        const double processingTimeMoveRequest)
{
	std ::unique_lock<std::mutex> loc{timeStatisticsMtx};

	TimeStatistics statData{processingTime, processingTimeCalculation, processingTimeMoveRequest};

	if (timeStatistics.size() == 0) {
		timeStatistics.push_back(statData);

		// Dla pierwszego pomiaru wartosc srednia/min/max rowna sie temu pomiarowi
		timeStatisticsAvg.processingTime            = processingTime;
		timeStatisticsAvg.processingTimeCalculation = processingTimeCalculation;
		timeStatisticsAvg.processingTimeMoveRequest = processingTimeMoveRequest;

		timeStatisticsMax.processingTime            = processingTime;
		timeStatisticsMax.processingTimeCalculation = processingTimeCalculation;
		timeStatisticsMax.processingTimeMoveRequest = processingTimeMoveRequest;

		timeStatisticsMin.processingTime            = processingTime;
		timeStatisticsMin.processingTimeCalculation = processingTimeCalculation;
		timeStatisticsMin.processingTimeMoveRequest = processingTimeMoveRequest;

	} else {
		// Zapisanie wyniku do kolejki
		timeStatistics.push_back(statData);

		if (timeStatistics.size() > timeStatisticsMaxHistoryLenght) {
			TimeStatistics topValue = timeStatistics.front();
			timeStatistics.pop_front();

			timeStatisticsAvg.processingTime -= topValue.processingTime;
			timeStatisticsAvg.processingTimeCalculation -= topValue.processingTimeCalculation;
			timeStatisticsAvg.processingTimeMoveRequest -= topValue.processingTimeMoveRequest;
		}

		// Lista do wyznaczania sredniej
		timeStatisticsAvg.processingTime += processingTime;
		timeStatisticsAvg.processingTimeCalculation += processingTimeCalculation;
		timeStatisticsAvg.processingTimeMoveRequest += processingTimeMoveRequest;

		// Wartosci maksymalne
		if (processingTime > timeStatisticsMax.processingTime)
			timeStatisticsMax.processingTime = processingTime;

		if (processingTimeCalculation > timeStatisticsMax.processingTimeCalculation)
			timeStatisticsMax.processingTimeCalculation = processingTimeCalculation;

		if (processingTimeMoveRequest > timeStatisticsMax.processingTimeMoveRequest)
			timeStatisticsMax.processingTimeMoveRequest = processingTimeMoveRequest;

		// Wartosci minimalne
		if (processingTime < timeStatisticsMin.processingTime)
			timeStatisticsMin.processingTime = processingTime;

		if (processingTimeCalculation < timeStatisticsMin.processingTimeCalculation)
			timeStatisticsMin.processingTimeCalculation = processingTimeCalculation;

		if (processingTimeMoveRequest < timeStatisticsMin.processingTimeMoveRequest)
			timeStatisticsMin.processingTimeMoveRequest = processingTimeMoveRequest;
	}
}

void tlinsAstroEngine::getTimeStatisticAvg(double &processingTime, double &processingTimeCalculation,
                                           double &processingTimeMoveRequest) const
{
	if (timeStatistics.size() == 0) {
		processingTime            = 0.0;
		processingTimeCalculation = 0.0;
		processingTimeMoveRequest = 0.0;
	} else {
		double count              = static_cast<double>(timeStatistics.size());
		processingTime            = timeStatisticsAvg.processingTime / count;
		processingTimeCalculation = timeStatisticsAvg.processingTimeCalculation / count;
		processingTimeMoveRequest = timeStatisticsAvg.processingTimeMoveRequest / count;
	}
}

void tlinsAstroEngine::getTimeStatisticMax(double &processingTime, double &processingTimeCalculation,
                                           double &processingTimeMoveRequest) const
{
	processingTime            = timeStatisticsMax.processingTime;
	processingTimeCalculation = timeStatisticsMax.processingTimeCalculation;
	processingTimeMoveRequest = timeStatisticsMax.processingTimeMoveRequest;
}

void tlinsAstroEngine::getTimeStatisticMin(double &processingTime, double &processingTimeCalculation,
                                           double &processingTimeMoveRequest) const
{
	processingTime            = timeStatisticsMin.processingTime;
	processingTimeCalculation = timeStatisticsMin.processingTimeCalculation;
	processingTimeMoveRequest = timeStatisticsMin.processingTimeMoveRequest;
}

//
// --- Synchronizacja ----
//
// Metoda dla wspolrzednych astronomicznych tak modyfikuje aktualna pozycje
// montazu aby odpowiadala tym wspołrzednym
void tlinsAstroEngine::sync(const double ra, const double dec)
{
	//
	auto fromDegris = [](const double inVal, const double div, int &degris, int &minutes, double &seconds) {
		double val = inVal / tlinsMath::PI_2 * div;

		// Stopnie/godziny
		double degris_{0.0};
		double rest1 = ::modf(val, &degris_);
		rest1 *= 60;
		degris = static_cast<int>(degris_);

		//  Minuty
		double minutes_{0.0};
		seconds = ::modf(rest1, &minutes_);
		minutes = static_cast<int>(minutes_);

		// Sekundy
		seconds *= 60;
	};

	tlinsAstroObject                                             astroObject;
	std::map<tlinsStarApparentPlaceType, tlinsAstroObjectSimple> apparentResult;
	tlinsAstroObjectSimple                                       result;

	int    raH;
	int    raM;
	double raS;
	fromDegris(ra, 24.0, raH, raM, raS);
	tlinsCoordinate raC{ra < 0.0 ? true : false, raH, raM, raS};

	int    decD;
	int    decM;
	double decS;
	fromDegris(dec, 360.0, decD, decM, decS);
	tlinsCoordinate decC{dec < 0.0 ? true : false, decD, decM, decS};

	astroObject.set(raC, decC);

	// Wyznaczenie obserwowanej pozycji obiektu
	tlinsAstroEngine::apparentPosition(astroObject, apparentResult, result);

	Eigen::Vector2d deviceCoordinate;
	calculateDeviceCoordinate(result.getHourAngleRad(), result.getDeclinationRad(), deviceCoordinate);
	attitude::tlinAttitudeUtilsClass::normAngles(deviceCoordinate);

	// Zatrzymanie sledzenia
	suspendStandardRun();

	// Wstawienie nowego celu
	setTarget(astroObject, 0.0, 0.0);

	// Ustawinie wspolrzednych w urzadzeniue aby odpowiadaly pozycji
	std::map<std::string, tlinsMoveServerInterface::AxisPositionInfo> axiesPosition;

	{
		tlinsMoveServerInterface::AxisPositionInfo pos;
		auto posValue = static_cast<long>(::round(deviceCoordinate(0) * tlinsMath::PI_1_DIV_2 * xDResolution));
		pos.set_axisName(axisXName);
		pos.set_position(posValue);
		pos.set_positionEncoder(posValue);
		pos.set_rawPosition(posValue);
		pos.set_rawPositionEncoder(posValue);
		axiesPosition[axisXName] = pos;
	}

	{
		tlinsMoveServerInterface::AxisPositionInfo pos;
		auto posValue = static_cast<long>(::round(deviceCoordinate(1) * tlinsMath::PI_1_DIV_2 * yDResolution));
		pos.set_axisName(axisYName);
		pos.set_position(posValue);
		pos.set_positionEncoder(posValue);
		pos.set_rawPosition(posValue);
		pos.set_rawPositionEncoder(posValue);
		axiesPosition[axisYName] = pos;
	}
	moveService->setPosition(deviceName, axiesPosition);
}

//
// --- Obsluga mechanizmu sledzenia
//
void tlinsAstroEngine::trackingSet(const double ra, const double dec)
{
	trackSpeedRa  = ra;
	trackSpeedDec = dec;
}

bool tlinsAstroEngine::trackingStatusSet(const bool enable)
{
	if (enable) {
		// Lock targets list
		std::lock_guard<std::mutex> guard(actualTargetMtx);

		if (!actualTargetIsSet.load()) {
			// Sledzenie mozna wlaczuc tylko gdy wczesniej zostal ustalony obiekt
			return false;
		}

		// Get copy of iteration
		actualTarget.targetTrackBase     = actualTarget.target;
		actualTarget.targetTrackBaseTime = std::chrono::system_clock::now();

		// Zerowanie innych skladników = 0
		actualTarget.target.setParallax(0.0);
		actualTarget.target.setProperMotion(0.0, 0.0);
		actualTarget.target.setRadialVelocity(0.0);
		actualTarget.target.setCatalogType(std::string{""});

		trackIsActive.store(true);
	} else {
		trackIsActive.store(false);
	}
	return true;
}

//
// Metoda zaklada ze odpowiednia synchronizacja jest robiona wczesniej
//
void tlinsAstroEngine::trackProcess()
{
	if (!trackIsActive) {
		// Sledzenie jest wylaczone
		return;
	}

	// Lock targets list
	std::lock_guard<std::mutex> guard(actualTargetMtx);

	// 2. Okreslenie przyrostu czasu
	std::chrono::system_clock::time_point                           periodEnd = std::chrono::system_clock::now();
	std::chrono::duration<double, /*std::milli>*/ std::ratio<1, 1>> timeDistance =
	    periodEnd - actualTarget.targetTrackBaseTime;

	// 3. Przyrost wspólrzednych
	double raDistance  = trackSpeedRa * (timeDistance.count());
	double decDistance = trackSpeedDec * (timeDistance.count());

	// 4. Przejscie na radiany dla przyrostu pozycji
	double raDistanceRad  = raDistance / 3600.0 / 24.0 * tlinsMath::PI_2;
	double decDistanceRad = decDistance / 3600.0 / 360.0 * tlinsMath::PI_2;

	// 5. Bazowy sledzony cel w radianach
	double cRa  = actualTarget.targetTrackBase.getHourAngle().toRadiansRa();
	double cDec = actualTarget.targetTrackBase.getDeclination().toRadiansDec();

	// 7. Wyznaczenie nowej pozycji sledzenia
	double ra  = cRa + raDistanceRad;
	double dec = cDec + decDistanceRad;

	// 8. Normalizacja wspolrzednej
	// 8.1 Normalizacja osi RA
	attitude::tlinAttitudeUtilsClass::normAngles(ra, dec);

	// 9. Przejscie do wspólrzednych astronomicznych
	if (dec <= tlinsMath::PI_1_DIV_2) {
		// I cwiartka
		// Nic nie robimy
	} else if (dec > tlinsMath::PI_1_DIV_2 && dec <= tlinsMath::PI) {
		// II cwiartka
		dec = tlinsMath::PI - dec;
		ra += tlinsMath::PI;
	} else if (dec > tlinsMath::PI && dec <= (tlinsMath::PI + tlinsMath::PI_1_DIV_2)) {
		// III cwiartka
		ra += tlinsMath::PI;
		dec = dec - (tlinsMath::PI + tlinsMath::PI_1_DIV_2);
	} else {
		// IV cwiartka
		dec = dec - tlinsMath::PI_2;
	}

	attitude::tlinAttitudeUtilsClass::normAngles(ra);

	// 10. Modyfikacja aktualnego celu
	// 10.1 DEC
	char               signDEC;
	std::array<int, 4> iDEC;
	::iauA2af(7, dec, &signDEC, iDEC.data());
	tlinsCoordinate DEC{signDEC, iDEC[0], iDEC[1],
	                    static_cast<double>(iDEC[2]) + static_cast<double>(iDEC[3]) / 10000000.0};

	// 10.2 RA
	char               signRA;
	std::array<int, 4> iRA;
	::iauA2tf(7, ra, &signRA, iRA.data());
	tlinsCoordinate RA{signRA, iRA[0], iRA[1], static_cast<double>(iRA[2]) + static_cast<double>(iRA[3]) / 10000000.0};

	// 11. Modyfikacja celu
	actualTarget.target.set(RA, DEC);
}

bool tlinsAstroEngine::computeTargetForCurrentPosition(double &outRA, double &outDC, const bool notRotate)
{
	// Sprawdzenie aktualnego stanu silnika astro
	if (state != ENGINE_STATE::STATE_REGULAR) {
		return false;
	}

	// Odczyt aktualnej pozycji urzadzenia
	double x;
	double y;
	long   xOut;
	long   xOutRaw;
	long   yOut;
	long   yOutRaw;

	readPositionInfo(x, y, xOut, xOutRaw, yOut, yOutRaw);

	// Pozycja teleskopu w ukladzie XYZ
	Eigen::Vector3d telescopePositionXYZ;
	attitude::tlinAttitudeUtilsClass::toCartesian(x, y, telescopePositionXYZ);

	telescopePositionXYZ.normalize();

	// Wyznaczenie pozycji obiektu
	Eigen::Vector3d targetCoordinate = attitudeOptimalInverted * telescopePositionXYZ;

	// Kat obrotu ziemi
	auto &tInfo = tlinsTimeInfo::getInstance();
	tInfo.update();

	Eigen::Vector3d refCartRot;
	if (!notRotate) {

		// Dobieramy kat obrotu aby osiągnac gozine 00:00
		double earthAngle = ::iauEra00(tInfo.getD1(), tInfo.getD2());

		// Macierz obrotu wokol osi Z i obrot obiektu referencyjnego
		Eigen::Matrix3d zRot;
		attitude::tlinAttitudeUtilsClass::buildZRotaionMatrix(earthAngle, zRot);

		refCartRot = zRot * targetCoordinate;
	} else {
		refCartRot = targetCoordinate;
	}

	// 7. Przejscie z ukladu kartezjansgo na astro i zapisanie wyniku
	Eigen::Vector2d outRefSper;
	attitude::tlinAttitudeUtilsClass::toSpeherical(refCartRot, outRefSper);
	attitude::tlinAttitudeUtilsClass::normAngles(outRefSper, 0);

	outRA = outRefSper(0);
	outDC = outRefSper(1);
	return true;
}

bool tlinsAstroEngine::computeTargetForCurrentPosition(tlinsCoordinate &outRA, tlinsCoordinate &outDC)
{
	double ra{0.0};
	double dc{0.0};

	auto result = computeTargetForCurrentPosition(ra, dc);

	// RA
	char               signRA;
	std::array<int, 4> iRA;
	::iauA2tf(7, ra, &signRA, iRA.data());
	outRA.set(signRA == '-' ? true : false, iRA[0], iRA[1],
	          static_cast<double>(iRA[2]) + static_cast<double>(iRA[3]) / 10000000.0);

	// DC
	char               signDC;
	std::array<int, 4> iDC;
	::iauA2af(7, dc, &signDC, iDC.data());
	outDC.set(signDC == '-' ? true : false, iDC[0], iDC[1],
	          static_cast<double>(iDC[2]) + static_cast<double>(iDC[3]) / 10000000.0);

	return result;
}

bool tlinsAstroEngine::setTargetForCurrentPossition()
{
	try {
		tlinsCoordinate outRA;
		tlinsCoordinate outDC;
		if (!computeTargetForCurrentPosition(outRA, outDC)) {
			return false;
		}

		// Wstawienie celu
		tlinsAstroObject target;

		target.set(outRA, outDC);
		target.setProperMotion(0.0, 0.0);
		target.setRadialVelocity(0.0);
		target.setParallax(0.0);
		target.setCatalogType(std::string{""});

		{
			// Lock targets list
			std::lock_guard<std::mutex> guard(actualTargetMtx);

			// Zatrzymanie trakowania
			trackingStatusSet(false);

			// Wyczeszczenie listy
			actualTargetIsSet.store(false);
		}

		// Wstawienie nowego celu
		setTarget(target, 0.0, 0.0);
	}
	catch (tlinsAstroException &exc) {
		// Prawdopodobnie brak iteracji pomiarowej
		__THROW__(tlinsAstroException(std::string("error get measurements : ") + exc.getErrorMessage(),
		                              tlinsAstroException::ASTRO_ERROR_ENGINE_CALIBARTION));
	}
	catch (tlinmException &exc) {
		// Prawdopodobnie brak iteracji pomiarowej
		__THROW__(tlinsAstroException(std::string("error get measurements : ") + exc.getErrorDesc(),
		                              tlinsAstroException::ASTRO_ERROR_ENGINE_CALIBARTION));
	}
	catch (...) {
		// Prawdopodobnie brak iteracji pomiarowej
		__THROW__(tlinsAstroException(std::string("Other error."), tlinsAstroException::ASTRO_ERROR_OTHER));
	}
	return true;
}

void tlinsAstroEngine::resetEngine(const ReverseDevice &reverseX, const ReverseDevice &reverseY)
{
	// Zatrzymanie watku glownego
	endStandardRun();

	// Usniecie celi
	{
		std::lock_guard<std::mutex> guard(actualTargetMtx);
		actualTargetIsSet.store(false);
	}

	{
		// Wlaczenie trybu kalibracji
		mode.store(tlinsAstroEngine::ENGINE_MODE::MODE_STANDARD);
		state = tlinsAstroEngine::ENGINE_STATE::STATE_CALIBRATION;

		// Resetowanie macierzy transformacji
		attitudeOptimal         = Eigen::Matrix3d::Zero();
		attitudeOptimalInverted = Eigen::Matrix3d::Zero();

		// Reinicalizacja silnika budujacego macierz transformacji
		// Dlugosc historii do modyfikacji 1024
		attitudeProcess =
		    std::move(std::unique_ptr<attitude::tlinAttitudeProcess>(new attitude::tlinAttitudeProcess{}));
	}

	// Domyslnie watek jest zatrzymany
	suspendStandardRun();

	// Ponowne uruchomie watku glownego
	mainThread = std::thread(std::ref(*this));

	if (reverseX == ReverseDevice::DEVICE_REVERSE) {
		reversX = true;
	} else if (reverseX == ReverseDevice::DEVICE_NO_REVERSE) {
		reversX = false;
	}

	if (reverseY == ReverseDevice::DEVICE_REVERSE) {
		reversY = true;
	} else if (reverseX == ReverseDevice::DEVICE_NO_REVERSE) {
		reversY = false;
	}

	if (reversX || reversY) {
		//
		// Wymuszenie na sterowniku pozycji 0L, 0L gdy dla ktorejsc z osi kierunek obrotu jest przeciwnyt
		//
		// Mapa osi
		std::map<std::string, tlinsMoveServerInterface::AxisPositionInfo> axies;

		// Os X
		tlinsMoveServerInterface::AxisPositionInfo x;
		x.set_axisName(axisXName);
		x.set_position(0);
		x.set_positionEncoder(0);
		x.set_devStatus(tlinsMoveServerInterface::tlinsSerialMotorStatus::MOTOR_MAX);
		axies[axisXName] = x;

		// Os Y
		tlinsMoveServerInterface::AxisPositionInfo y;
		y.set_axisName(axisYName);
		y.set_position(0);
		y.set_positionEncoder(0);
		y.set_devStatus(tlinsMoveServerInterface::tlinsSerialMotorStatus::MOTOR_MAX);
		axies[axisYName] = y;

		try {
			moveService->setPosition(deviceName, axies);
		}
		catch (tlinsInterfaceException &exc) {
			__THROW__(tlinsAstroException(std::string("Error set initial position. Error: ") + exc.getErrorMessage(),
			                              tlinsAstroException::ASTRO_ERROR_MOVE_REQUEST));
		}
	}

	// Wymuszenie trybu asynchronicznego w kontrolerze silnikow
	try {
		moveService->setMoveMode(deviceName, tlinsMoveServerInterface::tlinsSerialDeviceMode::AXIS);
		moveEngineSetIntoAxisMode.store(__MOVE_ENGINE_STATE_ENFORE__::AXIS);
	}
	catch (tlinsInterfaceException &exc) {
		TLINS_LOG_ERROR("Error set device synchronus mode : " + exc.getErrorMessage());
	}
}

void tlinsAstroEngine::ConfirmationCallback::process(const tlins::tlinsRpcConfirmationStatus &status)
{
	// Oczekiwanie na ustawienie requestId
	waitForSet();

	if (!status.has_moverequest()) {
		// Niewlasciwy typ potwierdzenia - brak wymaganych danych
		return;
	}

	tlins::ErrorCodes errorStatus = tlins::ErrorCodes::_ERROR_CODE_SUCCESS;
	std::string       errorDescription;
	int               errorCode = 0;

	// Pobranie kodu bledu
	if (status.moverequest().has_status()) {
		errorDescription = status.moverequest().status().errordescription();
		errorStatus      = status.moverequest().status().status();
		errorCode        = status.moverequest().status().errorcode();
	}

	{
		// Przejecie blokady
		std::unique_lock<std::mutex> lk(engine.lastMoveRequestIdMutex);

		// Status potwierdzenia
		if (errorStatus != tlins::ErrorCodes::_ERROR_CODE_SUCCESS) {
			engine.lastMoveRequestFinalIsError = true;
		} else {
			engine.lastMoveRequestFinalIsError = false;
		}

		// Informacja o bledzie
		engine.lastMoveRequestFinalErrorCode        = errorCode;
		engine.lastMoveRequestFinalErrorDescription = errorDescription;

		reqConfirmed = true;

		// Znacznik potwierdzenia
		engine.lastMoveRequestConfirmed = true;
		engine.fistIteration            = false;
	}

	// Obudzenie watku
	engine.signal();
}

bool tlinsAstroEngine::ConfirmationCallback::release()
{
	std::unique_lock<std::mutex> lk(engine.lastMoveRequestIdMutex);
	if (engine.lastMoveRequestConfirmed) {
		// Jest potwierdzenie i odpowiada dokladnie requestowi ktory zostal zlecony

		// Powiadomienie obiektu nadrzednego ze zdanie zostalo potwierdzone
		engine.signal();
		return true;
	}
	return false;
}

tlinsAstroEngine::ConfirmationCallback::ConfirmationCallback(tlinsAstroEngine &engine_) : engine{engine_}
{
}

//
// --------------------------------------------------------------------
// --------------------------------------------------------------------
//
tlinsAstroEngine::tlinsSingleTarget::tlinsSingleTarget(const tlinsAstroObject &t, const double v, const double a)
    : target{t}, speed{v}, aceleration{a}
{
}

tlinsAstroEngine::tlinsSingleTarget::tlinsSingleTarget() : speed{0.0}, aceleration{0.0}
{
}

//
// --------------------------------------------------------------------
// --------------------------------------------------------------------
//
void tlinsAstroEngine::setRunFequency(const unsigned long m)
{
	runFequency = m;
}

const unsigned long tlinsAstroEngine::getRunFequency(void) const
{
	return runFequency;
}

void tlinsAstroEngine::setMode(const ENGINE_MODE m)
{
	mode.store(m);

	// Weryfikacja stanu kontrolera
	if (state != tlinsAstroEngine::ENGINE_STATE::STATE_REGULAR) {
		// Ustawienie trybu moze nastapic tylko w stanie po kalibracji
		__THROW__(tlinsAstroException("MODE can be set only in tlinsAstroEngine::ENGINE_STATE::STATE_REGULAR state.",
		                              tlinsAstroException::ASTRO_ERROR_ENGINE_STATE));
	}

	auto setStandardMode = [this]() {
		// Ustawienie kontrolera w tryb synchroniczny
		try {
			moveService->setMoveMode(deviceName, tlinsMoveServerInterface::tlinsSerialDeviceMode::SYNCHRONISED);
			moveEngineSetIntoAxisMode.store(__MOVE_ENGINE_STATE_ENFORE__::SYNCH);
			mode.store(ENGINE_MODE::MODE_STANDARD);
		}
		catch (tlinsInterfaceException &exc) {
			TLINS_LOG_ERROR("Error set device synchronus mode : " + exc.getErrorMessage());
			__THROW__(exc);
		}

		// Wejscie w petle glowna odpwoeidzialna za sledzenie
		signalStandardRun();
	};

	// Ustawienie trybu pracy
	switch (mode.load()) {
	case ENGINE_MODE::MODE_STANDARD:
		fistIteration = true;
		setStandardMode();
		break;

	case ENGINE_MODE::MODE_EXTERNAL_SUPPORT:
	case ENGINE_MODE::MODE_STANDARD_SPEED:
		/* W trybie zewnętrznego wsparcia i predkosci zawsze zaczynamy od trybu standardowego w celu dojechania do
		   wymaganej pozycji ktora zdefiniowana jest przez aktualny cel */
		desiredMode.store(mode.load());

		fistIteration = true;
		switchMode.store(true);
		setStandardMode();
		break;

	default:
		break;
	}
}

void tlinsAstroEngine::getNextTarget()
{
	// Lock targets list
	tlinsSingleTarget nextTarget;
	bool              newTargetToSet{false};

	{
		std::lock_guard<std::mutex> guard(actualTargetMtx);
		if (!pendingTargets.empty()) {
			nextTarget     = pendingTargets.front();
			newTargetToSet = true;
			pendingTargets.pop_front();
		}
	}

	if (newTargetToSet) {
		actualTargetIsSet.store(false);
		setTargetInternal(nextTarget.target, nextTarget.speed, nextTarget.aceleration);
	}
}

bool tlinsAstroEngine::getTarget(tlinsSingleTarget &target)
{
	std::lock_guard<std::mutex> guard(actualTargetMtx);
	if (!actualTargetIsSet.load()) {
		return false; // Nie ma celu
	}

	// Biezacy cel
	target = actualTarget;
	return true;
}

void tlinsAstroEngine::setTargetInternal(const tlinsAstroObject &t, const double v, const double a)
{
	// Zatrzymanie trakowania
	trackingStatusSet(false);

	// Zatrzymanie przetwarzania
	auto standardRunCtrlCurrent = standardRunCtrl.load();
	suspendStandardRun();

	// Ustawienie nowego celu
	actualTarget = tlinsSingleTarget{t, v, a};
	actualTargetIsSet.store(true);

	// Pozwalamy ze oczekiwanie na zakonczenie przemieszczenia bedzie dluzsze
	fistIteration = true;

	// Uwaga: Watek nie bedzie sygnalizowany. Przejscie do nowej pozycji
	//        nastapi w kolejnej iteracji.
	newTarget = true;
	if (mode.load() == ENGINE_MODE::MODE_STANDARD_SPEED) {
		// Wymuszamy przejscie urzadzenia do zadanej pozycji a nastepnie powracamy do sledzenie w trybie predkosci
		setMode(ENGINE_MODE::MODE_STANDARD_SPEED);
	} else if (mode.load() == ENGINE_MODE::MODE_EXTERNAL_SUPPORT) {
		// Wymuszamy przejscie urzadzenia do zadanej pozycji a nastepnie powracamy do sledzenie w trybie predkosci
		setMode(ENGINE_MODE::MODE_EXTERNAL_SUPPORT);
	}

	if (!standardRunCtrlCurrent) {
		reasumeStandardRun();
	}
}

void tlinsAstroEngine::setTarget(const tlinsAstroObject &t, const double v, const double a)
{
	if (state != tlinsAstroEngine::ENGINE_STATE::STATE_REGULAR) {
		// Metoda dostepna tylko w trybie regularny, po kalibracji
		__THROW__(tlinsAstroException(std::string("REGULAR state is mandatory."),
		                              tlinsAstroException::ASTRO_ERROR_ENGINE_STATE));
	}

	// Lock targets list
	std::lock_guard<std::mutex> guard(actualTargetMtx);

	if (switchMode.load()) {
		// Sterownik jest w trakcie osiagania zadanego celu
		pendingTargets.clear();
		pendingTargets.push_back(tlinsSingleTarget{t, v, a});
		return;
	}

	tlinsAstroEngine::setTargetInternal(t, v, a);
}

/*
 * Oczekiwanie na odebranie potwierdzenia o zakoczeniu przemieszczenia
 */
void tlinsAstroEngine::wait()
{
	std::unique_lock<std::mutex> lk(lastMoveRequestIdMutex);

	unsigned long runFequencyValue = 1000 / runFequency;
	if (runFequencyValue < 1)
		runFequencyValue = 1;

	// Oczekiwanie nie dluzej niz czestotliwosc korygowania pozycji
	bool status = lastMoveRequestIdCV.wait_for(lk, std::chrono::milliseconds(runFequencyValue), [this]() {
		bool v = this->lastMoveRequestConfirmed;
		return v;
	});
}

void tlinsAstroEngine::wait(const long lenth)
{
	std::unique_lock<std::mutex> lk(lastMoveRequestIdMutex);

	// Oczekiwanie nie dluzej niz czestotliwosc korygowania pozycji
	bool status = lastMoveRequestIdCV.wait_for(lk, std::chrono::milliseconds(lenth), [this]() {
		bool v = this->lastMoveRequestConfirmed;
		return v;
	});
}

void tlinsAstroEngine::signal()
{
	std::unique_lock<std::mutex> lk(lastMoveRequestIdMutex);
	lastMoveRequestIdCV.notify_one();
}

#if 1

double tlinsAstroEngine::deltaMinimumPosition(const double currPos, const double newPos, bool &direction) const
{
	auto result = attitude::tlinAttitudeUtilsClass::deltaMinimumPosition(currPos, newPos);
	direction   = result.second;
	return result.first;
}

#else

double tlinsAstroEngine::deltaMinimumPosition(const double currPos, const double newPos, bool &direction) const
{
	double diff{0.0};
	double l1{newPos - currPos};
	double l2{0.0};

	if (newPos > currPos) {
		l2 = -1.0 * (D2PI - newPos + currPos);
	} else {
		l2 = (D2PI - currPos + newPos);
	}

	if (std::fabs(l1) < std::fabs(l2)) {
		diff = l1;
	} else {
		diff = l2;
	}

	direction = false;
	if (diff < 0) {
		direction = true;
	}

	return std::fabs(diff);
}

#endif

extern std::string mainGetLogDir();

template <typename T, typename... Args> std::string tlinsAstroEngine::buildContent(T v, Args... args) const
{
	return buildContent(v) + ";" + buildContent(args...);
}

static std::string buildContentTimeStamp(const struct timeval &tv)
{
	struct tm   tmResult;
	struct tm  *tmTime = ::localtime_r(&tv.tv_sec, &tmResult);
	char        timeStr[100];
	std::string strLevel;

	::sprintf(timeStr, "T[%04d.%02d.%02d %02d:%02d:%02d.%06ld] => ", tmTime->tm_year + 1900, tmTime->tm_mon + 1,
	          tmTime->tm_mday, tmTime->tm_hour, tmTime->tm_min, tmTime->tm_sec, tv.tv_usec);
	return std::string{timeStr};
}

template <typename T, typename... Args> void tlinsAstroEngine::reportPositionInfo(T v, Args... args)
{
	struct timeval tv;
	if (::gettimeofday(&tv, nullptr) < 0) {
		__THROW__(tlinsAstroException(std::string("Error get time"), tlinsAstroException::ASTRO_ERROR_DATE_GET_TIME));
	}
	auto reportLine = buildContentTimeStamp(tv) + buildContent(v) + ";" + buildContent(args...) + "\n";

	// Zapis do pliku raportu
	std::string tracePositionFilePath = mainGetLogDir() + "/" + "trace_position.log";
	int         fileId                = ::open(tracePositionFilePath.c_str(), O_APPEND | O_CREAT | O_WRONLY);
	if (fileId < 0) {
		return;
	}
	::write(fileId, reportLine.c_str(), reportLine.length());
	::close(fileId);
}

std::string tlinsAstroEngine::buildContent(std::string v) const
{
	return v;
}

//
// Metoda zaklada ze wartosci predkosci przyspieszenia, hamowania w radianach na sekunde
//
void tlinsAstroEngine::sendMoveRequest(const long xRaw_, const long yRaw_, const long dX_, const long dY_)
{
	long xRaw = xRaw_;
	long yRaw = yRaw_;
	long dX   = dX_;
	long dY   = dY_;

	// Konwersja pozycji do ukladu urzadzenia
	reversePostion(dX, dY, xRaw, yRaw);

	if (moveEngineSetIntoAxisMode.load() != __MOVE_ENGINE_STATE_ENFORE__::SYNCH) {
		// Wymuszenie trybu synchronicznego na kontrolerze
		try {
			moveService->setMoveMode(deviceName, tlinsMoveServerInterface::tlinsSerialDeviceMode::SYNCHRONISED);
			moveEngineSetIntoAxisMode.store(__MOVE_ENGINE_STATE_ENFORE__::SYNCH);
		}
		catch (tlinsInterfaceException &exc) {
			TLINS_LOG_ERROR("Error set device synchronus mode : " + exc.getErrorMessage());
		}
	}

	// Init request ID
	lastMoveRequestFinalIsError = false;
	lastMoveRequestConfirmed    = false;

	double t = 0.0;
	t        = 1.0 / static_cast<double>(runFequency);

	try {
		tlinsMoveServerInterface::MoveRequestDevice request;
		tlinsMoveServerInterface::Status            status;
		long                                        _vx_{0};
		long                                        _vy_{0};
		long                                        _vxO_{0};
		long                                        _vyO_{0};
		long                                        vXSteps{0L};

		// 1. Os X
		{
			tlinsMoveServerInterface::MoveRequestItem data;

			_vx_ = ::round(static_cast<double>(dX) / t) * (100.0 + static_cast<double>(trackingSpeedIncrease)) / 100.0;
			vXSteps = static_cast<long>(::round(vX * tlinsMath::PI_1_DIV_2 * xDResolution));
			if (_vx_ > vXSteps) {
				_vx_ = vXSteps;
			}

			// Predkosc Przemieszczenia
			data.set_distance(xRaw);
			data.set_V(_vx_);

			// - Przyspieszenie i hamowanie. Przeliczenie A i D na kroki
			data.set_A(static_cast<long>(::round(aX * tlinsMath::PI_1_DIV_2 * xDResolution)));
			data.set_D(static_cast<long>(::round(dX * tlinsMath::PI_1_DIV_2 * xDResolution)));

			// - Kierunek - jest nie istotny - przemieszczenie w trybie absolutnym
			data.set_direction(tlinsMoveServerInterface::RequestDirection::RIGHT);
			request.getRequestItems()[axisXName] = data;
		}

		// 2. Os Y
		{
			tlinsMoveServerInterface::MoveRequestItem data;

			_vy_ = ::round(static_cast<double>(dY) / t) * (100.0 + static_cast<double>(trackingSpeedIncrease)) / 100.0;

			auto vYSteps = static_cast<long>(::round(vY * tlinsMath::PI_1_DIV_2 * xDResolution));
			if (_vy_ > vYSteps) {
				_vy_ = vYSteps;
			}

			data.set_distance(yRaw);
			data.set_V(_vy_);

			data.set_direction(tlinsMoveServerInterface::RequestDirection::RIGHT);
			request.getRequestItems()[axisYName] = data;
		}

		// 2. Parametery rzadania
		{
			request.set_moveType(tlinsMoveServerInterface::MoveType::MOVE);
			request.set_interpolationType(tlinsMoveServerInterface::InterpolationType::LINEAR);
			request.set_relAbs(tlinsMoveServerInterface::ModeRelAbs::ABS);
		}

		// 3. Parametery rampy w trybie interpolowanym
		{
			// Predkosc
			auto V = static_cast<long>(::round(::sqrt(static_cast<double>(_vx_) * static_cast<double>(_vx_) +
			                                          static_cast<double>(_vy_) * static_cast<double>(_vy_))));
			V      = V * (100 + trackingSpeedIncrease) / 100;
			if (V > vXSteps) {
				V = vXSteps;
			}
			request.set_V(V);

			// Przyspieszenie i hamowanie. Przeliczenie na kroki odbywa sie na podstawie maksymanlej rozdzielczosci osi
			// X
			request.set_A(static_cast<long>(::round(A * tlinsMath::PI_1_DIV_2 * xDResolution)));
			request.set_D(static_cast<long>(::round(D * tlinsMath::PI_1_DIV_2 * xDResolution)));
		}

		// Tworzeni callbacka potwierdzenia
		if (!lastMoveRequestCb) {
			lastMoveRequestCb = std::make_shared<ConfirmationCallback>(*this);
		}

		// Wyslanie rzadania
		moveService->moveRequest(deviceName, request, lastMoveRequestCb);
	}
	catch (tlinsInterfaceException &exc) {
		__THROW__(tlinsAstroException(std::string("Error send move request. Error: ") + exc.getErrorMessage(),
		                              tlinsAstroException::ASTRO_ERROR_MOVE_REQUEST));
	}
}

void tlinsAstroEngine::readPositionInfo(long &xOut, long &xOutRaw, long &yOut, long &yOutRaw) const
{
	// Urzadzenia
	std::map<std::string, tlinsMoveServerInterface::AxisPositionInfo> result;

	try {
		moveService->positionInfo(deviceName, result);
	}
	catch (tlinsInterfaceException &exc) {
		__THROW__(tlinsAstroException(std::string("Error read device position. Error: ") + exc.getErrorMessage(),
		                              tlinsAstroException::ASTRO_ERROR_READ_DEVICE_POSITION));
	}

	//
	// Weryfikacja rezultatu
	//
	// - Os X
	auto xInfoIter = result.find(axisXName);
	if (xInfoIter == result.end()) {
		__THROW__(tlinsAstroException(std::string("Error read device position - no X axis info "),
		                              tlinsAstroException::ASTRO_ERROR_READ_DEVICE_POSITION));
	}

	// - Os Y
	auto yInfoIter = result.find(axisYName);
	if (yInfoIter == result.end()) {
		__THROW__(tlinsAstroException(std::string("Error read device position - no Y axis info "),
		                              tlinsAstroException::ASTRO_ERROR_READ_DEVICE_POSITION));
	}

	auto xInfo = xInfoIter->second;
	auto yInfo = yInfoIter->second;

	xOut    = xInfo.get_position();
	xOutRaw = xInfo.get_rawPosition();
	yOut    = yInfo.get_position();
	yOutRaw = yInfo.get_rawPosition();
}

//
// metoda zaklada że pozycja jesty w przedziale 0; 2 * PI
// Metoda przechodzi do ustalonego ukladu: lewo konty rosnace, prawo konty malejace
void tlinsAstroEngine::reversePostion(long &lx, long &ly, long &rawLx, long &rawLy)
{
	if (reversX) {
		lx = xResolution - lx;
		rawLx *= -1L;
	}

	if (reversY) {
		ly = yResolution - ly;
		rawLy *= -1L;
	}
}

void tlinsAstroEngine::reverseSpeed(bool &vxDir, bool &vyDir)
{
	if (reversX) {
		vxDir = !vxDir;
	}

	if (reversY) {
		vyDir = !vyDir;
	}
}

void tlinsAstroEngine::readPositionInfo(double &xout, double &yout, long &xlOut, long &xlOutRaw, long &ylOut,
                                        long &ylOutRaw)
{
	readPositionInfo(xlOut, xlOutRaw, ylOut, ylOutRaw);

	long xx = xlOut;
	long yy = ylOut;

	while (xx < 0) {
		xx += xResolution;
	}

	while (xx > xResolution) {
		xx -= xResolution;
	}

	while (yy < 0) {
		yy += yResolution;
	}

	while (yy > yResolution) {
		yy -= yResolution;
	}

	// Przejscie do ukladu referencyjnego zakladanego przez klase czyly w uklad w ktorym
	// 1. Obrót w lewo oznacza przyrost w spolrzednej
	// 2. Obrót w prawo oznacza zmniejszenie wspolrzednej
	reversePostion(xx, yy, xlOutRaw, ylOutRaw);

	xlOut = xx;
	ylOut = yy;

	xout = (static_cast<double>(xx) / static_cast<double>(xResolution)) * tlinsMath::PI_2;
	yout = (static_cast<double>(yy) / static_cast<double>(yResolution)) * tlinsMath::PI_2;
}

void tlinsAstroEngine::readConfiguration(long &maxX, long &maxY) const
{
	// Urzadzenia
	std::map<std::string, tlinsMoveServerInterface::tlinsDeviceAxisInfo> result;

	try {
		moveService->deviceConfiguration(deviceName, result);
	}
	catch (tlinsInterfaceException &exc) {
		__THROW__(tlinsAstroException(std::string("Error read device configuration. Error: ") + exc.getErrorMessage(),
		                              tlinsAstroException::ASTRO_ERROR_READ_DEVICE_CONFGIRATION));
	}

	//
	// Weryfikacja rezultatu
	//
	// - Os X
	auto xInfoIter = result.find(axisXName);
	if (xInfoIter == result.end()) {
		__THROW__(tlinsAstroException(std::string("Error read device configuration - no X axis info "),
		                              tlinsAstroException::ASTRO_ERROR_READ_DEVICE_CONFGIRATION));
	}

	// - Os Y
	auto yInfoIter = result.find(axisYName);
	if (yInfoIter == result.end()) {
		__THROW__(tlinsAstroException(std::string("Error read device configuration - no Y axis info "),
		                              tlinsAstroException::ASTRO_ERROR_READ_DEVICE_CONFGIRATION));
	}

	auto xInfo = xInfoIter->second;
	auto yInfo = yInfoIter->second;

	// W zaleznosci czy urzadzenie pracuje w zamknietej pteli wspolrzedna wyliczana
	// jest w rozny sposob
	maxX = xInfo.get_deviceResolution();
	maxY = yInfo.get_deviceResolution();
}

void tlinsAstroEngine::updateInternalPosition(double &currPosX, double &currPosY)
{
	try {
		if (fistIteration || trackingDeviceSynchronisationFrequency == 0 ||
		    synchDeviceCount % trackingDeviceSynchronisationFrequency == 0) {
			// Pobranie z urzadzeni aktualnej poizycji
			synchDeviceCount = 1;
			readPositionInfo(currPosX, currPosY, xPostionSteps, xPostionStepsRaw, yPostionSteps, yPostionStepsRaw);

			xPosition = currPosX;
			yPosition = currPosY;
		} else {
			synchDeviceCount++;
			currPosX = xPosition;
			currPosY = yPosition;
		}
	}
	catch (tlinsAstroException &exc) {
		__THROW__(exc);
	}
}

void tlinsAstroEngine::setInternalPosition(const double xnew, const double ynew, long &dX, long &dY)
{
	double xPosD = xnew * tlinsMath::PI_1_DIV_2 * xDResolution;
	double yPosD = ynew * tlinsMath::PI_1_DIV_2 * yDResolution;

	long xPostionStepsPrev = xPostionSteps;
	long yPostionStepsPrev = yPostionSteps;

	// Znormalizowana pozycja w krokach
	xPostionSteps = static_cast<long>(::round(xPosD));
	yPostionSteps = static_cast<long>(::round(yPosD));
	xPosition     = xnew;
	yPosition     = ynew;

	// Wyznaczenie przysrostu wspolrzednej aby przelkiczyc na wspolrzeddne urzadzenia
	auto getDelta = [](const long v1, const long v2, const long max) {
		long q = max;
		long l1{0L}; // Obrót w lewo
		long l2{0L}; // Obrot w prawo

		// Obrot w strone rosnacych wartosci kontow
		if (v1 < v2) {
			l1 = (v2 - v1);
			l2 = -1L * max - (v2 - v1);
		} else {
			l1 = max - (v1 - v2);
			l2 = -1L * (v1 - v2);
		}

		if (abs(l1) < abs(l2)) {
			return l1;
		}
		return l2;
	};

	dX = getDelta(xPostionStepsPrev, xPostionSteps, xResolution);
	dY = getDelta(yPostionStepsPrev, yPostionSteps, yResolution);

	xPostionStepsRaw += dX;
	yPostionStepsRaw += dY;
}

//
// Metoda generuje rzadanie typu SPEED
//
void tlinsAstroEngine::sendSpeedRequest(const double xV, const bool xDir_, const double yV, const bool yDir_)
{
	bool xDir = xDir_;
	bool yDir = yDir_;

	TLINS_LOG_DEBUG("XV = " + std::to_string(xV) + "; YV = " + std::to_string(yV));

	// Ewentualne odwrocenie kierunku predkosci
	reverseSpeed(xDir, yDir);

	if (moveEngineSetIntoAxisMode.load() != __MOVE_ENGINE_STATE_ENFORE__::AXIS) {
		// Wymuszenie trybu AXIS na kontrolerze
		try {
			moveService->setMoveMode(deviceName, tlinsMoveServerInterface::tlinsSerialDeviceMode::AXIS);
			moveEngineSetIntoAxisMode.store(__MOVE_ENGINE_STATE_ENFORE__::AXIS);
		}
		catch (tlinsInterfaceException &exc) {
			TLINS_LOG_ERROR("Error set device synchronus mode : " + exc.getErrorMessage());
		}
	}

	auto convert = [](const double v, double const res) {
		auto val = static_cast<long>(::round(::fabs(v) * tlinsMath::PI_1_DIV_2 * res));
		return val;
	};

	try {
		tlinsMoveServerInterface::MoveRequestDevice request;

		// Os X
		{
			tlinsMoveServerInterface::MoveRequestItem data;

			// Dystans
			data.set_distance(0L);
			// Predkosc
			data.set_V(convert(xV, xDResolution));

			// Przyspieszenie i hamowanie. Przeliczenie A i D na kroki
			data.set_A(convert(aX, xDResolution));
			data.set_D(convert(dX, xDResolution));

			// Kierunek
			// Obrot w lewo wewnetrznie jest w strone rosnacych wartosci kontow
			if (xDir) {
				data.set_direction(tlinsMoveServerInterface::RequestDirection::RIGHT);
			} else {
				data.set_direction(tlinsMoveServerInterface::RequestDirection::LEFT);
			}
			request.getRequestItems()[axisXName] = data;
		}

		// Os Y
		{
			tlinsMoveServerInterface::MoveRequestItem data;

			// Dusans
			data.set_distance(0L);

			// Predkosc
			data.set_V(convert(yV, yDResolution));

			// Przyspieszenie i hamowanie. Przeliczenie A i D na kroki
			data.set_A(convert(aY, xDResolution));
			data.set_D(convert(dX, xDResolution));

			// Kierunek
			if (yDir) {
				data.set_direction(tlinsMoveServerInterface::RequestDirection::RIGHT);
			} else {
				data.set_direction(tlinsMoveServerInterface::RequestDirection::LEFT);
			}

			request.getRequestItems()[axisYName] = data;
		}

		//
		// Parametery rzadania
		//
		request.set_moveType(tlinsMoveServerInterface::MoveType::SPEED);
		request.set_interpolationType(tlinsMoveServerInterface::InterpolationType::NONE);
		request.set_relAbs(tlinsMoveServerInterface::ModeRelAbs::ABS);

		//
		// Parametery rampy w trybie interpolowanym - ignorowane
		// Predkosc
		request.set_V(0L);

		// Przyspieszenie i hamowanie
		request.set_A(convert(aX, xDResolution));
		request.set_D(convert(dX, xDResolution));

		// Tworzeni callbacka potwierdzenia
		std::shared_ptr<tlinsMoveServerInterface::tlinsMoveRequestConfirmation> cb{nullptr};

		// Wyslanie rzadania
		moveService->moveRequest(deviceName, request, cb);
	}
	catch (tlinsInterfaceException &exc) {
		__THROW__(tlinsAstroException(std::string("Error send move request. Error: ") + exc.getErrorMessage(),
		                              tlinsAstroException::ASTRO_ERROR_MOVE_REQUEST));
	}
}

/*
 * Iteracja nie rwalizuje ruchu krokowo ale na zasadzie monitorowania predkosci przemieszczenia
 * Iteracja bedzie kontrolowana timerem
 * W regularnych odstepach czasu bedzie przeliczana predkosc
 */
bool tlinsAstroEngine::testIterationSpeed()
{
	// Uspienie watku na zadany okres
	wait(speedModeWaitIterval);

	if (fistIteration) {
		return true;
	}
	return false;
}

void tlinsAstroEngine::calculateDeviceCoordinate(const Eigen::Vector3d &apparentPositionXYZ,
                                                 const Eigen::Matrix3d &earthRot, Eigen::Vector2d &newCoordinate)
{
	// Wspolrzedna obiektu we wspolrzednych teleskopu
	Eigen::Vector3d deviceCoordinate = attitudeOptimal * earthRot * apparentPositionXYZ;
	attitude::tlinAttitudeUtilsClass::toSpeherical(deviceCoordinate, newCoordinate);

	if (tracePosition) {
		TLINS_LOG_DEBUG("TEST CORDINATES => [" + std::to_string(apparentPositionXYZ(0)) + "," +
		                std::to_string(apparentPositionXYZ(1)) + "," + std::to_string(apparentPositionXYZ(2)) + "][" +
		                std::to_string(deviceCoordinate(0)) + "," + std::to_string(deviceCoordinate(1)) + "," +
		                std::to_string(deviceCoordinate(2)) + "]");
	}

	attitude::tlinAttitudeUtilsClass::normAngles(newCoordinate);
}

void tlinsAstroEngine::calculateDeviceCoordinate(const double alfa, const double beta, Eigen::Vector2d &newCoordinate)
{
	Eigen::Vector3d apparentPositionXYZ;
	attitude::tlinAttitudeUtilsClass::toCartesian(alfa, beta, apparentPositionXYZ);

	// Wspolrzedna obiektu we wspolrzednych teleskopu
	Eigen::Vector3d deviceCoordinate = attitudeOptimal * apparentPositionXYZ;

	attitude::tlinAttitudeUtilsClass::toSpeherical(deviceCoordinate, newCoordinate);

	if (tracePosition) {
		TLINS_LOG_DEBUG("TEST CORDINATES => [" + std::to_string(apparentPositionXYZ(0)) + "," +
		                std::to_string(apparentPositionXYZ(1)) + "," + std::to_string(apparentPositionXYZ(2)) + "][" +
		                std::to_string(deviceCoordinate(0)) + "," + std::to_string(deviceCoordinate(1)) + "," +
		                std::to_string(deviceCoordinate(2)) + "]");
	}

	attitude::tlinAttitudeUtilsClass::normAngles(newCoordinate);
}

void tlinsAstroEngine::iterationSpeed()
{
	// 1. Aktualny czas
	struct timeval tv;
	if (::gettimeofday(&tv, nullptr) < 0) {
		__THROW__(tlinsAstroException(std::string("Error get time"), tlinsAstroException::ASTRO_ERROR_DATE_GET_TIME));
	}

	// 2. Pobranie biezacego celu
	tlinsSingleTarget currentTarget;
	if (!readCurrentTargetOrForceNew(currentTarget)) {
		__THROW__(tlinsAstroException(std::string("No target"), tlinsAstroException::ASTRO_ERROR_NO_TARGET));
	}

	//
	// 3. Wyznaczenie pozycji obserwowanej obiektu dla biezacej chwili
	std::map<tlinsStarApparentPlaceType, tlinsAstroObjectSimple> apparentResult;
	Eigen::Vector3d                                              apparentPosition;
	auto                                                         apparentPositionM =
	    tlinsAstroEngine::apparentPositionBase(currentTarget.target, apparentResult, apparentPosition, &tv);

	//
	// 3. Wyznaczenie pozycji obserwowanej obiektu dla chwili +1 sekunda
	std::map<tlinsStarApparentPlaceType, tlinsAstroObjectSimple> apparentResultNext;
	tv.tv_sec += 1L;
	Eigen::Vector3d apparentPositionNext;
	auto            apparentPositionNextM =
	    tlinsAstroEngine::apparentPositionBase(currentTarget.target, apparentResultNext, apparentPositionNext, &tv);

	auto calculateDevMoveV = [this](const Eigen::Vector3d &apparentPosition_, const Eigen::Matrix3d &earthRot,
	                                Eigen::Vector2d &newCoordinate) {
		calculateDeviceCoordinate(apparentPosition_, earthRot, newCoordinate);
	};

	Eigen::Vector2d newDeviceCoordinate;
	calculateDevMoveV(apparentPosition, apparentPositionM, newDeviceCoordinate);

	Eigen::Vector2d newDeviceCoordinateNext;
	calculateDevMoveV(apparentPositionNext, apparentPositionNextM, newDeviceCoordinateNext);

	// Wyznaczenie wielkosci przyrostu i kierunek
	bool   Xdirection;
	double Xdelata = deltaMinimumPosition(newDeviceCoordinate(0), newDeviceCoordinateNext(0), Xdirection);

	bool   Ydirection;
	double Ydelata = deltaMinimumPosition(newDeviceCoordinate(1), newDeviceCoordinateNext(1), Ydirection);

	// Okreslenie roznicy dystansu miedzy biezacą teoretyczną a rzeczywista
	if (!suspendSpeedCorrection) {
		double realX{0.0};
		double realY{0.0};
		long   xOut{0L};
		long   xOutRaw{0L};
		long   yOut{0L};
		long   yOutRaw{0L};

		readPositionInfo(realX, realY, xOut, xOutRaw, yOut, yOutRaw);

		bool   XdirectionCorr;
		double XdelataCorr = deltaMinimumPosition(realX, newDeviceCoordinate(0), XdirectionCorr);

		bool   YdirectionCorr;
		double YdelataCorr = deltaMinimumPosition(realY, newDeviceCoordinate(1), YdirectionCorr);

		bool   XdirectionCorrNext;
		double XdelataCorrNext = deltaMinimumPosition(realX, newDeviceCoordinateNext(0), XdirectionCorrNext);

		bool   YdirectionCorrNext;
		double YdelataCorrNext = deltaMinimumPosition(realY, newDeviceCoordinateNext(1), YdirectionCorrNext);

		auto speedErrorCorrection = [this](double valueIn, double corr, double corrNext, bool &dir, bool dirCorr,
		                                   bool dirCorrNext) {
			auto value = valueIn;
			if (dir == dirCorr && dir == dirCorrNext) {
				if (corr > minSpeedCorrection) {
					value += corr;
				}
			} else if (dir != dirCorr && dir == dirCorrNext) {
				if (corr > minSpeedCorrection) {
					value -= corr;
				}
			} else if (dir != dirCorr && dir != dirCorrNext) {
				if (reverseSpeedCorrection) {
					// Zmieniamy kierunek tylko wtedy gdy jest to dozwolne
					value = corrNext;
					dir   = dirCorrNext;
				} else {
					value = 0.0;
				}
			}
			double max = maxSpeedPercantage * valueIn;
			if (value > max) {
				value = max;
			}
			return value;
		};

		Xdelata =
		    speedErrorCorrection(Xdelata, XdelataCorr, XdelataCorrNext, Xdirection, XdirectionCorr, XdirectionCorrNext);
		Ydelata =
		    speedErrorCorrection(Ydelata, YdelataCorr, YdelataCorrNext, Ydirection, YdirectionCorr, YdirectionCorrNext);

		// Manulane korekty uzytkownika
		// Korekta uzytkownika jest z przediału <-1.0 * Xdelta, 1.0 * Xdelta> oraz <-1.0 * Ydelta, 1.0 * Ydelta>
		Xdelata += Xdelata * speedManualCorrectionX.load();
		Ydelata += Ydelata * speedManualCorrectionY.load();

		if (Xdelata < 0) {
			Xdelata = 0.0;
		}
		if (Ydelata < 0) {
			Ydelata = 0.0;
		}

		if (tracePosition) {
			// Raportowanie pozycji
			reportPositionInfo(std::string{"Speed correction"}, newDeviceCoordinate(0), newDeviceCoordinate(1),
			                   newDeviceCoordinateNext(0), newDeviceCoordinateNext(1), realX, realY, xOut, xOutRaw,
			                   yOut, yOutRaw, Xdelata, Ydelata, Xdirection, Ydirection);
		}
	} else {
		if (tracePosition) {
			// Raportowanie pozycji
			reportPositionInfo(std::string{"Speed"}, newDeviceCoordinate(0), newDeviceCoordinate(1),
			                   newDeviceCoordinateNext(0), newDeviceCoordinateNext(1), Xdirection, Ydirection);
		}
	}

	// Wslanie rzadania wykonania przemieszczenia
	sendSpeedRequest(Xdelata, Xdirection, Ydelata, Ydirection);
}

bool tlinsAstroEngine::testIterationStandard()
{
	auto          fistIterationCopy = fistIteration;
	unsigned long count             = 0;

	// Glowna petla oczekiwania na przekazanie odpowiedzi
	while (!standardRunEnd) {
		// Czekanie na przemieszczenie
		wait();

		// Przemieszczenie wykonane konczymy petle
		if (lastMoveRequestConfirmed) {
			break;
		}

		// Aktualizacja licznikow
		count++;

		// Detekcja bledu. Przekroczony zostal maksymalny czas oczekiwania na odpowiedz
		// Jesli switchMode jest ustawiony to bezwzglednie czekamy na osiagniecie celu bezwgledu na to jak dlugo trwa
		// przemieszczenie
		if (count > runFrequencyErrorCount && !fistIteration) {
			// Oproznienie kolejki
			moveService->flushCallbacks();

			// Znacznik pierwszego uruichomnienia jest ustawiany na prawde
			// aby dac czas napedowi osognieci pozycji
			fistIteration = true;

			// Przekazanie bledu
			TLINS_LOG_ERROR("No confirmation on request");
			__THROW__(tlinsAstroException(std::string("No confirmation on move request."),
			                              tlinsAstroException::ASTRO_ERROR_ITERATION));
		}
	}

	if (switchMode.load()) {
		// Bedzie wykonywana zmiana trybu
		mode.store(desiredMode.load());
		fistIteration = true;
		switchMode.store(false);
	}

	if (fistIterationCopy) {
		return true;
	}
	return false;
}

//
// --------------------------------------------------------------------
//
struct tlinsAstroEngine::__timer___ {
	// os dla ktorej bedzie realizowany timer
	__MOVE_ENGINE_STATE_ENFORE__ axis;
	long                         period;
	std::mutex                   mtx;
	std::condition_variable      cv;
	tlinsAstroEngine            &parent;

	void process();
	__timer___(tlinsAstroEngine &parent_, const long period_);
	__timer___()  = delete;
	~__timer___() = default;
};

void tlinsAstroEngine::__timer___::process()
{
	std::unique_lock<std::mutex> lock(mtx);
	cv.wait_for(lock, std::chrono::milliseconds(period), []() { return false; });

	// Usuniecie korekty
	{
		std::unique_lock<std::mutex> lock{parent.correctionSetMtx};
		parent.guiderXCorrection.store(0.0);
		parent.guiderYCorrection.store(0.0);
	}

	// Oznaczenie timera jako nieuzywany
	parent.guiderTimerInUse.store(false);
}

tlinsAstroEngine::__timer___::__timer___(tlinsAstroEngine &parent_, const long period_)
    : parent{parent_}, period{period_}
{
	parent.guiderTimerInUse.store(true);
}

// Implementacja guidera
void tlinsAstroEngine::guiderRequestHandling(const long period, const AXIS axis, const DIRECTION dir)
{
	// Sprawdzenie czy timer jest w uzyciu
	if (guiderTimerInUse.load()) {
		// Timer czyli biezaca korekta cały cxzas jest obslugiwana w  urzyciu przerywamy tworzenie
		__THROW__(tlinsAstroException(std::string("Pending correction "),
		                              tlinsAstroException::ASTRO_ERROR_GUIDER_PENDING_CORRECTION));
	}

	// Aktualny czas
	struct timeval tv;
	if (::gettimeofday(&tv, nullptr) < 0) {
		__THROW__(tlinsAstroException(std::string("Error get time"), tlinsAstroException::ASTRO_ERROR_DATE_GET_TIME));
	}

	//
	// Aktualny cel
	tlinsSingleTarget currentTarget;
	if (!readCurrentTargetOrForceNew(currentTarget)) {
		__THROW__(tlinsAstroException(std::string("No target"), tlinsAstroException::ASTRO_ERROR_NO_TARGET));
	}

	// Wyznaczenie pozycji obserwowanej obiektu dla biezacej chwili
	std::map<tlinsStarApparentPlaceType, tlinsAstroObjectSimple> apparentResult;
	tlinsAstroObjectSimple                                       apparentPosition;
	tlinsAstroEngine::apparentPosition(currentTarget.target, apparentResult, apparentPosition, true, &tv);

	// Wyznaczenie pozycji obserwowanej obiektu dla chwili +1 sekunda
	std::map<tlinsStarApparentPlaceType, tlinsAstroObjectSimple> apparentResultNext;
	tlinsAstroObjectSimple                                       apparentPositionNext;
	tv.tv_sec += 1L;
	tlinsAstroEngine::apparentPosition(currentTarget.target, apparentResultNext, apparentPositionNext, true, &tv);

	// Skladowe predkosci w ukladzie Astro
	bool   Xdirection;
	double Xdelata =
	    deltaMinimumPosition(apparentPosition.getHourAngleRad(), apparentPositionNext.getHourAngleRad(), Xdirection);

	bool   Ydirection;
	double Ydelata = deltaMinimumPosition(apparentPosition.getDeclinationRad(),
	                                      apparentPositionNext.getDeclinationRad(), Ydirection);

	// Określenie wektora kierunku obrotu
	Eigen::Vector2d rotVector{Eigen::Vector2d::Zero()};

	if (axis == AXIS::RA) {
		rotVector(0) = guiderXSpeed * Xdelata;
		rotVector(1) = 0.0;

		if (dir == DIRECTION::RIGHT)
			rotVector(0) = rotVector(0) * -1.0;
	} else if (axis == AXIS::DEC) {
		rotVector(0) = 0.0;
		rotVector(1) = guiderYSpeed * (guiderUseRAspeedForDEC ? Xdelata : Ydelata);

		if (dir == DIRECTION::DOWN)
			rotVector(1) = rotVector(1) * -1.0;
	}

	// Wyznaczenie predkosci obrotowej we wspolrzednych urzadzenia
	Eigen::Vector2d rotVectorRotatedNew;

	calculateDeviceCoordinate(rotVector(0), rotVector(1), rotVectorRotatedNew);

	// Finalna korekta
	Eigen::Vector2d speedCorrection = rotVectorRotatedNew;

	// Uruchomienie timera
	std::unique_lock<std::mutex> lock{guiderTimerMutex};
	guiderTimer.reset(new __timer___(*this, period));

	// Uruchomienie watku realizujacego timera
	guiderTimerThread = std::thread{std::move([this, speedCorrection]() {
		{
			// Zapisane korekt
			std::unique_lock<std::mutex> lock{correctionSetMtx};
			guiderXCorrection.store(speedCorrection(0));
			guiderYCorrection.store(speedCorrection(1));
		}
		guiderTimer->process();
	})};
	guiderTimerThread.detach();
}

void tlinsAstroEngine::manualCorrectionStatus(DIRECTION &raDir, double &raCorrection, DIRECTION &decDir,
                                              double &decCorrection) const
{
	raCorrection  = raManualCorrection;
	raDir         = raManualCorrectionDir;
	decCorrection = decManualCorrection;
	decDir        = decManualCorrectionDir;
}

void tlinsAstroEngine::manualCorrectionRequestHandlingReset()
{
	speedManualCorrectionX.store(0.0);
	speedManualCorrectionX.store(0.0);
}

void tlinsAstroEngine::manualCorrectionRequestHandling(const DIRECTION raDir, double raCorrection,
                                                       const DIRECTION decDir, double decCorrection)
{
	// Sprawdzenie czy timer jest w uzyciu
	if (guiderTimerInUse.load()) {
		// Timer czyli biezaca korekta cały cxzas jest obslugiwana w  urzyciu przerywamy tworzenie
		__THROW__(tlinsAstroException(std::string("Pending correction "),
		                              tlinsAstroException::ASTRO_ERROR_GUIDER_PENDING_CORRECTION));
	}

	// Aktualny czas
	struct timeval tv;
	if (::gettimeofday(&tv, nullptr) < 0) {
		__THROW__(tlinsAstroException(std::string("Error get time"), tlinsAstroException::ASTRO_ERROR_DATE_GET_TIME));
	}

	//
	// Aktualny cel
	tlinsSingleTarget currentTarget;
	if (!readCurrentTargetOrForceNew(currentTarget)) {
		__THROW__(tlinsAstroException(std::string("No target"), tlinsAstroException::ASTRO_ERROR_NO_TARGET));
	}

	// Wyznaczenie pozycji obserwowanej obiektu dla biezacej chwili
	std::map<tlinsStarApparentPlaceType, tlinsAstroObjectSimple> apparentResult;
	tlinsAstroObjectSimple                                       apparentPosition;
	tlinsAstroEngine::apparentPosition(currentTarget.target, apparentResult, apparentPosition, true, &tv);

	// Wyznaczenie pozycji obserwowanej obiektu dla chwili +1 sekunda
	std::map<tlinsStarApparentPlaceType, tlinsAstroObjectSimple> apparentResultNext;
	tlinsAstroObjectSimple                                       apparentPositionNext;
	tv.tv_sec += 1L;
	tlinsAstroEngine::apparentPosition(currentTarget.target, apparentResultNext, apparentPositionNext, true, &tv);

	// Skladowe predkosci w ukladzie Astro
	bool   Xdirection;
	double Xdelata =
	    deltaMinimumPosition(apparentPosition.getHourAngleRad(), apparentPositionNext.getHourAngleRad(), Xdirection);

	bool   Ydirection;
	double Ydelata = deltaMinimumPosition(apparentPosition.getDeclinationRad(),
	                                      apparentPositionNext.getDeclinationRad(), Ydirection);

	// Określenie wektora kierunku obrotu
	Eigen::Vector2d rotVector{Eigen::Vector2d::Zero()};

	// Wyznaczenie korekt w ukadzie astro
	{
		rotVector(0) = raCorrection * Xdelata;
		if (raDir == DIRECTION::RIGHT) {
			rotVector(0) = rotVector(0) * -1.0;
		}
	}

	{
		rotVector(1) = decCorrection * Ydelata;
		if (decDir == DIRECTION::DOWN) {
			rotVector(1) = rotVector(1) * -1.0;
		}
	}

	// Wyznaczenie predkosci obrotowej we wspolrzednych urzadzenia
	Eigen::Vector2d rotVectorRotatedNew;
	calculateDeviceCoordinate(rotVector(0), rotVector(1), rotVectorRotatedNew);

	// Finalna korekta
	Eigen::Vector2d speedCorrection = rotVectorRotatedNew;

	speedManualCorrectionX.store(speedCorrection(0));
	speedManualCorrectionX.store(speedCorrection(1));

	raManualCorrection     = raCorrection;
	raManualCorrectionDir  = raDir;
	decManualCorrection    = decCorrection;
	decManualCorrectionDir = decDir;
}

void tlinsAstroEngine::setGuiderConfiguration(const double ra, const double dec, const bool useRaForDec)
{
	guiderXCorrection.store(ra);
	guiderYCorrection.store(dec);
	guiderUseRAspeedForDEC = useRaForDec;
}

void tlinsAstroEngine::getGuiderConfiguration(double &ra, double &dec, bool &useRaForDec) const
{
	ra          = guiderXCorrection.load();
	dec         = guiderYCorrection.load();
	useRaForDec = guiderUseRAspeedForDEC;
}

void tlinsAstroEngine::iterationGuider()
{
	// Aktualny czas
	struct timeval tv;
	if (::gettimeofday(&tv, nullptr) < 0) {
		__THROW__(tlinsAstroException(std::string("Error get time"), tlinsAstroException::ASTRO_ERROR_DATE_GET_TIME));
	}

	// Biezacy cel
	tlinsSingleTarget currentTarget;
	if (!tlinsAstroEngine::readCurrentTargetOrForceNew(currentTarget)) {
		return;
	}

	// Wyznaczenie pozycji obserwowanej obiektu dla biezacej chwili
	std::map<tlinsStarApparentPlaceType, tlinsAstroObjectSimple> apparentResult;

	Eigen::Vector3d apparentPosition;
	auto apparentPositionRot = apparentPositionBase(currentTarget.target, apparentResult, apparentPosition, &tv);

	// Wyznaczenie pozycji obserwowanej obiektu dla chwili +1 sekunda
	std::map<tlinsStarApparentPlaceType, tlinsAstroObjectSimple> apparentResultNext;
	tv.tv_sec += 1L;

	Eigen::Vector3d apparentPositionNext;
	auto            apparentPositionNextRot =
	    apparentPositionBase(currentTarget.target, apparentResultNext, apparentPositionNext, &tv);

	auto calculateDevMoveV = [this](const Eigen::Vector3d &apparentPositionXYZ, const Eigen::Matrix3d &erot,
	                                Eigen::Vector2d &newCoordinate) {
		// Wspolrzedna obiektu we wspolrzednych teleskopu
		Eigen::Vector3d deviceCoordinate = attitudeOptimal * erot * apparentPositionXYZ;
		attitude::tlinAttitudeUtilsClass::toSpeherical(deviceCoordinate, newCoordinate);
		attitude::tlinAttitudeUtilsClass::normAngles(newCoordinate);
	};

	Eigen::Vector2d newDeviceCoordinate;
	calculateDevMoveV(apparentPosition, apparentPositionRot, newDeviceCoordinate);

	Eigen::Vector2d newDeviceCoordinateNext;
	calculateDevMoveV(apparentPositionNext, apparentPositionNextRot, newDeviceCoordinateNext);

	// Wyznaczenie wielkosci przyrostu i kierunek
	bool   Xdirection;
	double Xdelata = deltaMinimumPosition(newDeviceCoordinate(0), newDeviceCoordinateNext(0), Xdirection);

	bool   Ydirection;
	double Ydelata = deltaMinimumPosition(newDeviceCoordinate(1), newDeviceCoordinateNext(1), Ydirection);

	// Korekty guidera
	{
		std::unique_lock<std::mutex> lock{correctionSetMtx};
		Xdelata += guiderXCorrection.load();
		Ydelata += guiderYCorrection.load();

		Xdelata = ::fabs(Xdelata);
		Ydelata = ::fabs(Ydelata);
	}

	sendSpeedRequest(Xdelata, Xdirection, Ydelata, Ydirection);

	if (tracePosition) {
		// Raportowanie pozycji
		reportPositionInfo(std::string{"Guider"}, newDeviceCoordinate(0), newDeviceCoordinate(1),
		                   newDeviceCoordinateNext(0), newDeviceCoordinateNext(1), Xdelata, Ydelata, Xdirection,
		                   Ydirection);
	}
}

bool tlinsAstroEngine::testIterationGuider()
{
	// Uspienie watku na zadany okres
	wait(speedModeWaitIterval);

	if (fistIteration) {
		return true;
	}
	return false;
}

void tlinsAstroEngine::iterationStandard()
{
	// Pobranie biezacego celu
	tlinsSingleTarget currentTarget;
	if (!tlinsAstroEngine::readCurrentTargetOrForceNew(currentTarget)) {
		__THROW__(tlinsAstroException(std::string("No target"), tlinsAstroException::ASTRO_ERROR_NO_TARGET));
	}

	if (newTarget) {
		newTarget = false;
		stopDevice();
	}

	// Wyznaczenie pozycji obserwowanej obiektu docelowego
	std::map<tlinsStarApparentPlaceType, tlinsAstroObjectSimple> apparentResult;
	tlinsAstroObjectSimple                                       apparentPosition;

	tlinsAstroEngine::apparentPosition(currentTarget.target, apparentResult, apparentPosition);

	// Przeliczenie wspolrzednych obiektu na uklad wspolrzednych teleskopu
	// - Przejscie ze wspołrzednych biegunowych na X, Y, Z
	Eigen::Vector3d apparentPositionXYZ;
	const double    alfa = apparentPosition.getHourAngleRad();
	const double    beta = apparentPosition.getDeclinationRad();
	attitude::tlinAttitudeUtilsClass::toCartesian(alfa, beta, apparentPositionXYZ);

	// Wspolrzedna obiektu we wspolrzednych teleskopu
	Eigen::Vector3d deviceCoordinate = attitudeOptimal * apparentPositionXYZ;

	// Wspolrzedne kontrolera teleskopu
	double currPosX;
	double currPosY;
	updateInternalPosition(currPosX, currPosY);

	// Nowe wspolrzedne teleskopu w ukladzie sferycznym
	Eigen::Vector2d newDeviceCoordinate;
	attitude::tlinAttitudeUtilsClass::toSpeherical(deviceCoordinate, newDeviceCoordinate);
	attitude::tlinAttitudeUtilsClass::normAngles(newDeviceCoordinate);

	// Wyslanie rzadania i zapamietania identyfikatora rzadania
	try {
		long dX;
		long dY;
		// Aktualizacja estymowanej pozycji urzadzenia
		setInternalPosition(newDeviceCoordinate(0), newDeviceCoordinate(1), dX, dY);
		sendMoveRequest(xPostionStepsRaw, yPostionStepsRaw, ::abs(dX), abs(dY));

		if (tracePosition) {
			// Raportowanie pozycji
			reportPositionInfo(std::string{"Standard"}, apparentPosition.getHourAngleRad(),
			                   apparentPosition.getDeclinationRad(), currPosX, currPosY,
			                   static_cast<double>(xPostionSteps), static_cast<double>(yPostionSteps),
			                   static_cast<double>(xPostionStepsRaw), static_cast<double>(yPostionStepsRaw), xPosition,
			                   yPosition, xPostionSteps, yPostionSteps, dX, dY);
		}
	}
	catch (tlinsAstroException &exc) {
		// Przekazanie wyjatku
		__THROW__(exc);
	}
}

void tlinsAstroEngine::singleIteration()
{
	if (state != tlinsAstroEngine::ENGINE_STATE::STATE_REGULAR) {
		__THROW__(tlinsAstroException(std::string("Method is supported only in REGULAR state"),
		                              tlinsAstroException::ASTRO_ERROR_ENGINE_STATE));
	}

	// 0. Poczatek przetwarzania
	std::chrono::system_clock::time_point start = std::chrono::system_clock::now();
	std::chrono::system_clock::time_point startMoveRequest{};

	lastMoveRequestConfirmed = false;

	// 1. Sledzenie
	trackProcess();

	switch (mode.load()) {
	case tlinsAstroEngine::ENGINE_MODE::MODE_STANDARD:
		// Standardowy sposob nadozania za obiektem
		iterationStandard();
		startMoveRequest = std::chrono::system_clock::now();
		if (testIterationStandard()) {
			return;
		}
		break;

	case tlinsAstroEngine::ENGINE_MODE::MODE_STANDARD_SPEED:
		iterationSpeed();
		if (testIterationSpeed()) {
			return;
		}
		break;

	case tlinsAstroEngine::ENGINE_MODE::MODE_EXTERNAL_SUPPORT:
		iterationGuider();
		if (testIterationGuider()) {
			return;
		}
		break;

	default:
		__THROW__(tlinsAstroException(std::string("Unknown mode."), tlinsAstroException::ASTRO_ERROR_ENGINE_MODE));
		break;
	}

	// Poczatek przetwarzania
	std::chrono::system_clock::time_point     end                       = std::chrono::system_clock::now();
	std::chrono::duration<double, std::milli> processingTime            = (end - start);
	std::chrono::duration<double, std::milli> processingTimeCalculation = (startMoveRequest - start);
	std::chrono::duration<double, std::milli> processingTimeMoveRequest = (end - startMoveRequest);

	// Pobranie statystyk
	addTimeStatistic(processingTime.count() / 1000.0, processingTimeCalculation.count() / 1000.0,
	                 processingTimeMoveRequest.count() / 1000.0);

	avgProcessingTimeCount++;
	avgProcessingTime += processingTime.count();
}

void tlinsAstroEngine::endStandardRun()
{
	// Obudzenie watku jesli jest uspiony
	standardRunEnd = true;
	reasumeStandardRun();

	// Wyslanie sygnalu aby obudzic watek jesli czeka na
	signal();

	// Oczekiwanie na zakonczenie watku
	if (mainThread.joinable())
		mainThread.join();
}

void tlinsAstroEngine::waitStandardRun()
{
	std::unique_lock<std::mutex> lock(standardRunMtx);
	standardRunCV.wait(lock);
}

void tlinsAstroEngine::signalStandardRun()
{
	standardRunCV.notify_all();
}

void tlinsAstroEngine::waitStandardRunCtrl()
{
	std::unique_lock<std::mutex> lock(standardRunCtrlMtx);
	standardRunCtrlCV.wait(lock);
}

void tlinsAstroEngine::signalStandardRunCtrl()
{
	standardRunCtrlCV.notify_all();
}

void tlinsAstroEngine::startCustomTracking(double, double, unsigned long)
{
	// TODO
}

void tlinsAstroEngine::stopCustomTracking()
{
	// TODO
}


void tlinsAstroEngine::suspendStandardRun()
{
	// Wejscie w stan uspienia nastapi po zakonczeniu biezacego zlecenia
	// Niebedzie wymuszane wczesniejsze wejscie w stan uspeina
	standardRunCtrl = true;
	stopDevice();
}

void tlinsAstroEngine::reasumeStandardRun()
{
	standardRunCtrl = false;

	// W trybie predkosci przed rozpoczeciem przemieszczenia
	// wymuszamy osiagniecie przez urzadzenie zadanej pozycji
	if (mode.load() == ENGINE_MODE::MODE_STANDARD_SPEED) {
		setMode(ENGINE_MODE::MODE_STANDARD_SPEED);
	}

	// Obudzenie watku
	signalStandardRun();
	signalStandardRunCtrl();
}

void tlinsAstroEngine::standardRun()
{
	// Petla glowna standardowego trybu pracy
	standardRunEnd = false;

	// Oczekiwanie na wejscie do petli glownej trybu sledzenia biezacego obiektu
	waitStandardRun();

	while (!standardRunEnd) {
		// Kontrola pracy watku. Domyslnie watek jest zatrzymany
		if (standardRunCtrl) {
			// Oczekiwanie na sygnal ktory wznowi prace watku
			waitStandardRunCtrl();
		}

		// Wlasciwe przetwarzanie
		try {
			singleIteration();
		}
		catch (tlinsAstroException &exc) {
			TLINS_LOG_ERROR("Error : " + exc.getErrorMessage());
		}
	}
}

void tlinsAstroEngine::closeCalibration()
{
	TLINS_LOG_DEBUG("-----------------------------------");
	TLINS_LOG_DEBUG("--- Vectors angles info - START ---");
	TLINS_LOG_DEBUG("-----------------------------------");
	TLINS_LOG_DEBUG("");
	auto anglesInfo = attitudeProcess->getVctorsAngle();
	for (auto &item : anglesInfo) {

		TLINS_LOG_DEBUG("-------------------------------------");
		TLINS_LOG_DEBUG("Iterations = [" + std::to_string(item.iteration1) + ", " + std::to_string(item.iteration2) +
		                "]");
		PRINT_M(item.observationVector_1, "Observation vector 1           ", "%f");
		PRINT_M(item.observationVector_2, "Observation vector 2           ", "%f");
		TLINS_LOG_DEBUG("Observation vectors angle    = " + std::to_string(item.angleObs));

		PRINT_M(item.referenceVector_1, "Reference vector 1             ", "%f");
		PRINT_M(item.referenceVector_2, "Reference vector 2             ", "%f");
		TLINS_LOG_DEBUG("Reference vectors angle      = " + std::to_string(item.angleRef));

		PRINT_M(item.referenceVectorOrg_1, "Reference vector org 1         ", "%f");
		PRINT_M(item.referenceVectorOrg_2, "Reference vector org 2         ", "%f");
		TLINS_LOG_DEBUG("Org reference vectors angle  = " + std::to_string(item.angleRefOrg));
	}

	TLINS_LOG_DEBUG("");
	TLINS_LOG_DEBUG("---------------------------------");
	TLINS_LOG_DEBUG("--- Vectors angles info - END ---");
	TLINS_LOG_DEBUG("---------------------------------");
	TLINS_LOG_DEBUG("");


	try {
		TLINS_LOG_DEBUG("--------------------------------------------");
		TLINS_LOG_DEBUG("--- Attitude matrixes validation - START ---");
		TLINS_LOG_DEBUG("--------------------------------------------");
		TLINS_LOG_DEBUG("");

		auto validationResult = attitudeProcess->validate();

		for (auto item : validationResult) {
			auto vErr   = item.errorV;
			auto err    = item.error;
			auto att    = item.state->getAttitutude();
			auto attInv = item.state->getInvertedAttitutude();
			auto iterId = item.iteration->getSeqId();

			TLINS_LOG_DEBUG("-------------------------------------");
			TLINS_LOG_DEBUG("Processor       : " + item.processor + "\nIteration ID    : " + std::to_string(iterId) +
			                "\nError scalar    : " + std::to_string(err));
			PRINT_M(vErr, "Error             ", "%f");
			PRINT_M(att, "Attitude          ", "%f");
			PRINT_M(attInv, "Attitude inverted ", "%f");
		}

		TLINS_LOG_DEBUG("------------------------------------------");
		TLINS_LOG_DEBUG("--- Attitude matrixes validation - END ---");
		TLINS_LOG_DEBUG("------------------------------------------");
		TLINS_LOG_DEBUG("");

		if (validationResult.size() != 0) {
			// Wybierana jest najlepiej dopasowana macierz
			attitudeOptimal         = validationResult[0].state->getAttitutude();
			attitudeOptimalInverted = validationResult[0].state->getInvertedAttitutude();
		} else {
			attitudeOptimal         = Eigen::Matrix3d::Identity();
			attitudeOptimalInverted = Eigen::Matrix3d::Identity();
		}

		// Zmiana stanu
		state = tlinsAstroEngine::ENGINE_STATE::STATE_REGULAR;

		// Domyslne wartosci predkosci i przyspieszenia
		std::string val;
		tlinsAstroParameters::getParameterValue(tlinsAstroParameters::STAR_APPARENT_OBJECT_TRACKING_SPEED, val);
		double speed = readDoubleValue(val.c_str(), nullptr);

		tlinsAstroParameters::getParameterValue(tlinsAstroParameters::STAR_APPARENT_OBJECT_TRACKING_ACELERATION, val);
		double aceleration = readDoubleValue(val.c_str(), nullptr);

		// Biezacy cel to obiekt ktory jako ostatnio byl uzywany do kalibracji
		std::unique_lock<std::mutex> lk(actualTargetMtx);

		TLINS_LOG_DEBUG(
		    "REF RA = " + std::to_string(mesermenttroAstroObject.getHourAngle().getSign() == '-' ? true : false) +
		    std::to_string(mesermenttroAstroObject.getHourAngle().getDegris()) + ":" +
		    std::to_string(mesermenttroAstroObject.getHourAngle().getMinutes()) + ":" +
		    std::to_string(mesermenttroAstroObject.getHourAngle().getSeconds()));
		TLINS_LOG_DEBUG(
		    "REF DC = " + std::to_string(mesermenttroAstroObject.getDeclination().getSign() == '-' ? true : false) +
		    std::to_string(mesermenttroAstroObject.getDeclination().getDegris()) + ":" +
		    std::to_string(mesermenttroAstroObject.getDeclination().getMinutes()) + ":" +
		    std::to_string(mesermenttroAstroObject.getDeclination().getSeconds()));

		actualTarget = tlinsSingleTarget(mesermenttroAstroObject, speed, aceleration);
		actualTargetIsSet.store(true);

		// Wymuszenie trybu standardowego
		mode.store(tlinsAstroEngine::ENGINE_MODE::MODE_STANDARD);

		fistIteration = true;

		// Wymuszenie trybu synchronicznego kontrolera
		try {
			moveService->setMoveMode(deviceName, tlinsMoveServerInterface::tlinsSerialDeviceMode::SYNCHRONISED);
			moveEngineSetIntoAxisMode.store(__MOVE_ENGINE_STATE_ENFORE__::SYNCH);
		}
		catch (tlinsInterfaceException &exc) {
			TLINS_LOG_ERROR("Error set device synchronus mode : " + exc.getErrorMessage());
		}

		// Wejscie w petle glowna odpwoeidzialna za sledzenie
		signalStandardRun();
	}
	catch (tlinmException &exc) {
		// Prawdopodobnie brak iteracji pomiarowej
		__THROW__(tlinsAstroException(std::string("error get measurements : ") + exc.getErrorDesc(),
		                              tlinsAstroException::ASTRO_ERROR_ENGINE_CALIBARTION));
	}
	catch (...) {
		// Prawdopodobnie brak iteracji pomiarowej
		__THROW__(tlinsAstroException(std::string("Other error."), tlinsAstroException::ASTRO_ERROR_OTHER));
	}
}

void tlinsAstroEngine::apparentPosition(const tlinsAstroObject                                       &aobject,
                                        std::map<tlinsStarApparentPlaceType, tlinsAstroObjectSimple> &apparentResult,
                                        tlinsAstroObjectSimple &result, const bool rotate, struct timeval *tv) const
{
	// Aktualizacja czasu
	auto &tInfo = tlinsTimeInfo::getInstance();
	if (tv == nullptr) {
		tInfo.update();
	} else {
		tInfo.update(*tv);
	}

	// Pobranie aktualnych wartosci IERS
	tlinsIERSInfo iers;
	auto         &ins = tlinsIERSInfoManager::getInstance();
	if (!ins.get(tInfo.getYear(), tInfo.getMonth(), tInfo.getDay(), iers)) {
		iers.setZero(tInfo.getYear(), tInfo.getMonth(), tInfo.getDay());
	}

	// Wlasciwe wyznaczenie obserwowanej pozycji obiektu
	tlinsStarApparentPlaceCalculationSofa::toApparent(aobject, iers, apparentResult);

	// Wykonanie rotacji obiektu referencyjnego
	tlinsAstroObjectSimple appRef = apparentResult[apparentPlaceType];

	// Wspolrzedne obiektu w ukladzie cartezjanskim
	Eigen::Vector3d refCart;
	attitude::tlinAttitudeUtilsClass::toCartesian(appRef.getHourAngleRad(), appRef.getDeclinationRad(), refCart);

	Eigen::Vector3d refCartRot;
	if (rotate) {
		// Kat obrotu ziemi
		double earthAngle = (timeRotationSign ? 1.0 : -1.0) * ::iauEra00(tInfo.getD1(), tInfo.getD2());

		// Macierz obrotu wokol osi Z i obrot obiektu referencyjnego
		Eigen::Matrix3d zRot;
		attitude::tlinAttitudeUtilsClass::buildZRotaionMatrix(earthAngle, zRot);

		refCartRot = zRot * refCart;
	} else {
		refCartRot = refCart;
	}

	// Przejscie z ukladu kartezjansgo na astro i zapisanie wyniku
	Eigen::Vector2d outRefSper;
	attitude::tlinAttitudeUtilsClass::toSpeherical(refCartRot, outRefSper);
	attitude::tlinAttitudeUtilsClass::normAngles(outRefSper, 0);

	tlinsCoordinate rac_;
	tlinsCoordinate dcc_;
	toSimpleObjet(outRefSper(0), outRefSper(1), rac_, dcc_);
	result.set(rac_, dcc_);
}

Eigen::Matrix3d
tlinsAstroEngine::apparentPositionBase(const tlinsAstroObject                                       &aobject,
                                       std::map<tlinsStarApparentPlaceType, tlinsAstroObjectSimple> &apparentResult,
                                       Eigen::Vector3d &result, struct timeval *tv) const
{
	// Aktualizacja czasu
	auto &tInfo = tlinsTimeInfo::getInstance();
	if (tv == nullptr) {
		tInfo.update();
	} else {
		tInfo.update(*tv);
	}

	// Pobranie aktualnych wartosci IERS
	tlinsIERSInfo iers;
	auto         &ins = tlinsIERSInfoManager::getInstance();
	if (!ins.get(tInfo.getYear(), tInfo.getMonth(), tInfo.getDay(), iers)) {
		iers.setZero(tInfo.getYear(), tInfo.getMonth(), tInfo.getDay());
	}

	// Wlasciwe wyznaczenie obserwowanej pozycji obiektu
	tlinsStarApparentPlaceCalculationSofa::toApparent(aobject, iers, apparentResult);

	// Wykonanie rotacji obiektu referencyjnego
	tlinsAstroObjectSimple appRef = apparentResult[apparentPlaceType];

	// Wspolrzedne obiektu w ukladzie cartezjanskim
	Eigen::Vector3d refCart;
	attitude::tlinAttitudeUtilsClass::toCartesian(appRef.getHourAngleRad(), appRef.getDeclinationRad(), refCart);

	Eigen::Vector3d refCartRot;
	Eigen::Matrix3d rotRezult;

	// Kat obrotu ziemi
	double earthAngle = (timeRotationSign ? 1.0 : -1.0) * ::iauEra00(tInfo.getD1(), tInfo.getD2());

	// Macierz obrotu wokol osi Z i obrot obiektu referencyjnego
	attitude::tlinAttitudeUtilsClass::buildZRotaionMatrix(earthAngle, rotRezult);

	// Wynik
	result = refCart;

	// Przejscie z ukladu kartezjansgo na astro i zapisanie wyniku
	return rotRezult;
}

// Rejestracja pomiaru pozycji
void tlinsAstroEngine::registerMeserment(const tlinsFullCoordinate &inputErr, const tlinsAstroObject &reference,
                                         const double w)
{
	double xout;
	double yout;

	long xOut_;
	long xOutRaw_;
	long yOut_;
	long yOutRaw_;

	std::array<int, 4> idmsf_x;
	char               sign_x;
	std::array<int, 4> idmsf_y;
	char               sign_y;

	readPositionInfo(xout, yout, xOut_, xOutRaw_, yOut_, yOutRaw_);

	::iauA2af(9, xout, &sign_x, idmsf_x.data());
	::iauA2af(9, yout, &sign_y, idmsf_y.data());

	tlinsFullCoordinate input(
	    tlinsCoordinate(sign_x, idmsf_x[0], idmsf_x[1], (double) idmsf_x[2] + ((double) idmsf_x[3]) / 1000000000.0),
	    tlinsCoordinate(sign_y, idmsf_y[0], idmsf_y[1], (double) idmsf_y[2] + ((double) idmsf_y[3]) / 1000000000.0));

	registerMeserment(input, inputErr, reference, w);
}

void tlinsAstroEngine::registerMeserment(const tlinsFullCoordinate &input, const tlinsFullCoordinate &inputErr,
                                         const tlinsAstroObject &referenceInput, const double w)
{
	// Weryfikacja aktualnego stanu urzadzenia
	if (state != tlinsAstroEngine::ENGINE_STATE::STATE_CALIBRATION) {
		__THROW__(tlinsAstroException(std::string("Method is supported only in device calibration mode"),
		                              tlinsAstroException::ASTRO_ERROR_ENGINE_STATE));
	}

	// Zapamietanie pomiaru
	mesermenttroAstroObject = referenceInput;

	// Widoczna pozycja obiektu referencyjnego uwzgledniajaca rowniez rotacje ukladu
	std::map<tlinsStarApparentPlaceType, tlinsAstroObjectSimple> apparentResult;
	tlinsAstroObjectSimple                                       appReference;
	apparentPosition(referenceInput, apparentResult, appReference, false);

	// Obiekt referencyjny
	Eigen::Vector3d referenceVector;
	attitude::tlinAttitudeUtilsClass::toCartesian(appReference.getHourAngleRad(), appReference.getDeclinationRad(),
	                                              referenceVector);

	// Obserwacja
	Eigen::Vector3d observationVector;
	attitude::tlinAttitudeUtilsClass::toCartesian(input.getLongitudeRad(), input.getLatitudeRad(), observationVector);

	// Blad pomiaru
	Eigen::Vector3d observationError;
	attitude::tlinAttitudeUtilsClass::toCartesian(inputErr.getLongitudeRad(), inputErr.getLatitudeRad(),
	                                              observationError);

	// Pobranie czasu
	auto &timeInst = tlinsTimeInfo::getInstance();
	timeInst.update();

	// Koty obrotu
	double eRaZ = -1.0 * ::iauEra00(timeInst.getD1(), timeInst.getD2());
	TLINS_LOG_DEBUG("eRaZ = " + std ::to_string(eRaZ));
	TLINS_LOG_DEBUG("timeInst.getD1() = " + std ::to_string(timeInst.getD1()));
	TLINS_LOG_DEBUG("timeInst.getD2() = " + std ::to_string(timeInst.getD2()));

	// Dodanie pomiaru
	attitudeProcess->registerMeasurment(referenceVector, observationVector, observationError, erathRotationSpeedVector,
	                                    erathRotationSpeedVectorError, timeInst.getCurrentTimeSecends(),
	                                    /*w*/ 1.0,
	                                    /* const double detlaMk */ w, eRaZ);
}

//
// Operator uruchamiajacy przetwarzanie
//
void tlinsAstroEngine::operator()()
{
	standardRun();
}

tlinsAstroEngine::tlinsAstroEngine(std::shared_ptr<tlinsMoveServerInterface> &srv, tlinsAstroEnginConfiguration &cfg)
    : deviceName{cfg.deviceName},
      moveService{srv},
      attitudeProcess{new attitude::tlinAttitudeProcess{}},
      speedModeWaitIterval{cfg.speedModeWaitIterval},
      minSpeedPercantage{cfg.minSpeedPercantage},
      maxSpeedPercantage{cfg.maxSpeedPercantage},
      minSpeedCorrection{cfg.minSpeedCorrection},
      suspendSpeedCorrection{cfg.suspendSpeedCorrection},
      reverseSpeedCorrection{cfg.reverseSpeedCorrection},
      tracePosition{cfg.tracePosition},
      guiderXSpeed{cfg.guiderXSpeed},
      guiderYSpeed{cfg.guiderYSpeed},
      guiderUseRAspeedForDEC{cfg.guiderUseRAspeedForDEC},
      timeRotationSign{cfg.timeRotationSign}
{
	trackIsActive.store(false);
	switchMode.store(false);
	desiredMode.store(ENGINE_MODE::MODE_NONE);
	actualTargetIsSet.store(false);
	guiderTimerInUse.store(false);

	// Wymuszenie trybu asynchronicznego w kontrolerze osi
	try {
		moveService->setMoveMode(deviceName, tlinsMoveServerInterface::tlinsSerialDeviceMode::AXIS);
		moveEngineSetIntoAxisMode.store(__MOVE_ENGINE_STATE_ENFORE__::AXIS);
	}
	catch (tlinsInterfaceException &exc) {
		TLINS_LOG_ERROR("Error set device synchronus mode : " + exc.getErrorMessage());
	}

	// Wyznaczenie prekosci obrotwej ziemi w radianach na sekunde

	{
		auto &timeInst = tlinsTimeInfo::getInstance();

		timeInst.setDateTime(2010, 1, 1, 12, 0, 0.0, tlinsTimeInfo::getInstance().getScale());
		double angleStart = ::iauEra00(timeInst.getD1(), timeInst.getD2());

		timeInst.setDateTime(2010, 1, 1, 12, 0, 1.0, tlinsTimeInfo::getInstance().getScale());
		double angleEnd = ::iauEra00(timeInst.getD1(), timeInst.getD2());

		// Przywrucenie czasu
		timeInst.update();

		erathRotationSpeedVector(0) = 0.0;
		erathRotationSpeedVector(1) = 0.0;
		erathRotationSpeedVector(2) = -1.0 * ::fabs(angleEnd - angleStart);

		erathRotationSpeedVectorError(0) = cfg.earthSpeedRotationErrorX;
		erathRotationSpeedVectorError(1) = cfg.earthSpeedRotationErrorY;
		erathRotationSpeedVectorError(2) = cfg.earthSpeedRotationErrorZ;
	}

	state = ENGINE_STATE::STATE_CALIBRATION;

	// Weryfikacja konfiguracji
	auto axX = cfg.axesValues.find(axisXName);
	if (axX == cfg.axesValues.end()) {
		__THROW__(tlinsAstroException(std::string("No configuration for axies X."),
		                              tlinsAstroException::ASTRO_ERROR_READ_CONFGIRATION));
	}

	auto axY = cfg.axesValues.find(axisYName);
	if (axY == cfg.axesValues.end()) {
		__THROW__(tlinsAstroException(std::string("No configuration for axies X."),
		                              tlinsAstroException::ASTRO_ERROR_READ_CONFGIRATION));
	}

	auto &xCfg = axX->second;
	auto &yCfg = axY->second;

	// Kierunek obrotu osi urzadzeniach
	reversX = xCfg.deviceReverse;
	reversY = yCfg.deviceReverse;

	aX = xCfg.aceleration;
	aY = yCfg.aceleration;

	dX = xCfg.deceleration;
	dY = yCfg.deceleration;

	vX = xCfg.speed;
	vY = yCfg.speed;

	// Blad pomiaru
	xError = xCfg.calibrarionError;
	yError = yCfg.calibrarionError;

	// Parametery rampy dla interpolacji liniowej
	A = cfg.aceleration;
	D = cfg.deceleration;

	runFequency = cfg.runFrequency;

	runFequency                            = cfg.runFrequency;
	firstRunFrequency                      = cfg.firstRunFrequency;
	runFrequencyErrorCount                 = cfg.runFrequencyErrorCount;
	standardIterationWhenNoCorrections     = cfg.runStandardInterationWhenNoCorrections;
	stopTimeout                            = cfg.stopTimeout;
	trackingDeviceSynchronisationFrequency = cfg.trackingDeviceSynchronisationFrequency;
	trackingSpeedIncrease                  = cfg.trackingSpeedIncrease;

	//
	// Bledy pomiaru
	std::array<int, 4> idmsf_errorX;
	char               sign_errorX;

	std::array<int, 4> idmsf_errorY;
	char               sign_errorY;

	fistIteration = true;

	// Domyslnie czekamy na kolejna korekte
	standardIterationWhenNoCorrections = false;

	::iauA2af(9, xError, &sign_errorX, idmsf_errorX.data());
	::iauA2af(9, yError, &sign_errorY, idmsf_errorY.data());
	tlinsFullCoordinate devicePositionError_(
	    tlinsCoordinate(sign_errorX, idmsf_errorX[0], idmsf_errorX[1],
	                    (double) idmsf_errorX[2] + ((double) idmsf_errorX[3]) / 1000000000.0),
	    tlinsCoordinate(sign_errorY, idmsf_errorY[0], idmsf_errorY[1],
	                    (double) idmsf_errorY[2] + ((double) idmsf_errorY[3]) / 1000000000.0));
	devicePositionError = devicePositionError_;

	mode.store(tlinsAstroEngine::ENGINE_MODE::MODE_NONE);

	fistIteration = false;

	// Przemieszczenie abolutne
	absoluteMovment = true;

	// Maksymalne rozdzielczosci poszczegolnych osi oraz zancznik uzycia enkodera
	readConfiguration(xResolution, yResolution);
	xDResolution = static_cast<double>(xResolution);
	yDResolution = static_cast<double>(yResolution);

	// Czytanie parameterow
	if (cfg.STAR_APPARENT_PLACE_TYPE.compare("STAR_APPARENT_PLACE_TYPE_ICRS_TO_J2000") == 0) {
		apparentPlaceType = tlinsStarApparentPlaceType::STAR_APPARENT_PLACE_TYPE_ICRS_TO_J2000;
	} else if (cfg.STAR_APPARENT_PLACE_TYPE.compare("STAR_APPARENT_PLACE_TYPE_ICRS_TO_CIRS") == 0) {
		apparentPlaceType = tlinsStarApparentPlaceType::STAR_APPARENT_PLACE_TYPE_ICRS_TO_CIRS;
	} else if (cfg.STAR_APPARENT_PLACE_TYPE.compare("STAR_APPARENT_PLACE_TYPE_CIRS_TO_ICRS_ASTROMETRIC") == 0) {
		apparentPlaceType = tlinsStarApparentPlaceType::STAR_APPARENT_PLACE_TYPE_CIRS_TO_ICRS_ASTROMETRIC;
	} else if (cfg.STAR_APPARENT_PLACE_TYPE.compare("STAR_APPARENT_PLACE_TYPE_ICRS_ASTRONMETRIC_TO_CIRS_GEOCENTRIC") ==
	           0) {
		apparentPlaceType = tlinsStarApparentPlaceType::STAR_APPARENT_PLACE_TYPE_ICRS_ASTRONMETRIC_TO_CIRS_GEOCENTRIC;
	} else if (cfg.STAR_APPARENT_PLACE_TYPE.compare("STAR_APPARENT_PLACE_TYPE_GEOCENTRIC_APPARENT") == 0) {
		apparentPlaceType = tlinsStarApparentPlaceType::STAR_APPARENT_PLACE_TYPE_GEOCENTRIC_APPARENT;
	} else if (cfg.STAR_APPARENT_PLACE_TYPE.compare("STAR_APPARENT_PLACE_TYPE_CIRS_TO_TOPOCENTRIC") == 0) {
		apparentPlaceType = tlinsStarApparentPlaceType::STAR_APPARENT_PLACE_TYPE_CIRS_TO_TOPOCENTRIC;
	} else if (cfg.STAR_APPARENT_PLACE_TYPE.compare("STAR_APPARENT_PLACE_TYPE_CIRS_TO_OBSERVED") == 0) {
		apparentPlaceType = tlinsStarApparentPlaceType::STAR_APPARENT_PLACE_TYPE_CIRS_TO_OBSERVED;
	} else if (cfg.STAR_APPARENT_PLACE_TYPE.compare("STAR_APPARENT_PLACE_TYPE_ICRS_TO_OBSERVED") == 0) {
		apparentPlaceType = tlinsStarApparentPlaceType::STAR_APPARENT_PLACE_TYPE_ICRS_TO_OBSERVED;
	} else {
		apparentPlaceType = tlinsStarApparentPlaceType::STAR_APPARENT_PLACE_TYPE_ICRS_TO_OBSERVED;
	}

	// Glowny watek odpowiedzialny za przetwarzanie
	try {
		mainThread = std::thread(std::ref(*this));
	}
	catch (std::system_error &exc) {
		__THROW__(tlinsAstroException(std::string("Error create tracking thread."),
		                              tlinsAstroException::ASTRO_ERROR_INIT_ASTRO_ENGINE));
	}
}

tlinsAstroEngine::~tlinsAstroEngine()
{
	try {
		endStandardRun();
	}
	catch (...) {
		// Catch anny exception
	}
}

Eigen::Matrix3d tlinsAstroEngine::getAttitudeOptimal() const
{
	return attitudeOptimal;
}

void tlinsAstroEngine::readCurrentTarget(tlinsSingleTarget &target, bool &isTarget)
{
	// Lock targets list
	std::lock_guard<std::mutex> guard(actualTargetMtx);

	// Jesli stan urzadzenia jest inny niz
	if (state != ENGINE_STATE::STATE_REGULAR) {
		__THROW__(tlinsAstroException(std::string("Device must be in REGULAR state."),
		                              tlinsAstroException::ASTRO_ERROR_READ_STATE));
	}

	// Aktualny cel
	isTarget = actualTargetIsSet.load();
	if (isTarget) {
		target = actualTarget;
	}
}

bool tlinsAstroEngine::readCurrentTarget(tlinsSingleTarget &target)
{
	bool isTarget;
	readCurrentTarget(target, isTarget);
	return isTarget;
}

bool tlinsAstroEngine::readCurrentTargetOrForceNew(tlinsSingleTarget &target)
{
	bool isTarget;

	// Obsluga oczekujacych celi
	getNextTarget();
	readCurrentTarget(target, isTarget);
	return isTarget;
}

void tlinsAstroEngine::readState(Eigen::Matrix3d &attitude, tlinsSingleTarget &target, bool &isTarget, long &xOut,
                                 long &xOutRaw, long &yOut, long &yOutRaw, ENGINE_MULTIPLE_MODE_FINALL &mulMode,
                                 ENGINE_STATE &state_, ENGINE_MODE &mode_, const bool suspendRun)
{
	// Jesli stan urzadzenia jest inny niz
	if (state != ENGINE_STATE::STATE_REGULAR) {
		__THROW__(tlinsAstroException(std::string("Device must be in REGULAR state."),
		                              tlinsAstroException::ASTRO_ERROR_READ_STATE));
	}

	// Zatrzymanie silnika astro
	if (suspendRun) {
		suspendStandardRun();

		// Zatrzymanie urzadzenia (obu osi)
		stopDevice();
	}

	// Bylo zatrzymanie musimy dojechac fo pozycji
	fistIteration = true;

	// Macierz transformacji pomiedzy ukaldem teleskopu i ukladem astronomicznym
	attitude(0, 0) = attitudeOptimal(0, 0);
	attitude(0, 1) = attitudeOptimal(0, 1);
	attitude(0, 2) = attitudeOptimal(0, 2);
	attitude(1, 0) = attitudeOptimal(1, 0);
	attitude(1, 1) = attitudeOptimal(1, 1);
	attitude(1, 2) = attitudeOptimal(1, 2);
	attitude(2, 0) = attitudeOptimal(2, 0);
	attitude(2, 1) = attitudeOptimal(2, 1);
	attitude(2, 2) = attitudeOptimal(2, 2);

	// Aktualny cel
	isTarget = actualTargetIsSet.load();
	if (isTarget) {
		target = actualTarget;
	}

	// Aktualna pozycja
	readPositionInfo(xOut, xOutRaw, yOut, yOutRaw);

	// Stan silnika astro
	state_ = state;
	mode_  = mode.load();
}

void tlinsAstroEngine::stopDevice()
{
	try {
		tlinsMoveServerInterface::MoveRequestDevice request;
		tlinsMoveServerInterface::Status            status;

		// Os X
		long vXSteps{0L};
		{
			tlinsMoveServerInterface::MoveRequestItem data;

			// - Predkosc
			vXSteps = static_cast<long>(::round(vX * tlinsMath::PI_1_DIV_2 * xDResolution));
			data.set_V(vXSteps);

			// - Przyspieszenie i hamowanie
			auto AA = static_cast<long>(::round(aX * tlinsMath::PI_1_DIV_2 * xDResolution));
			auto DD = static_cast<long>(::round(dX * tlinsMath::PI_1_DIV_2 * xDResolution));
			data.set_A(AA);
			data.set_D(DD);

			// - Kierunek - bez znaczenia
			data.set_direction(tlinsMoveServerInterface::RequestDirection::LEFT);

			// - Odleglosc
			data.set_distance(0L);
			request.getRequestItems()[axisXName] = data;
		}

		// Os Y
		long vYSteps{0L};
		{
			tlinsMoveServerInterface::MoveRequestItem data;

			// - Predkosc
			vYSteps = static_cast<long>(::round(vY * tlinsMath::PI_1_DIV_2 * yDResolution));
			data.set_V(vYSteps);

			// - Przyspieszenie i hamowanie
			auto AA = static_cast<long>(::round(aY * tlinsMath::PI_1_DIV_2 * yDResolution));
			auto DD = static_cast<long>(::round(dY * tlinsMath::PI_1_DIV_2 * yDResolution));
			data.set_A(AA);
			data.set_D(DD);

			// - Kierunek - bez znaczenia
			data.set_direction(tlinsMoveServerInterface::RequestDirection::LEFT);

			// - Odleglosc
			data.set_distance(0L);
			request.getRequestItems()[axisYName] = data;
		}

		// Parametery rzadania
		{
			request.set_moveType(tlinsMoveServerInterface::MoveType::STOP);
			request.set_interpolationType(tlinsMoveServerInterface::InterpolationType::LINEAR);

			if (absoluteMovment) {
				request.set_relAbs(tlinsMoveServerInterface::ModeRelAbs::ABS);
			} else {
				request.set_relAbs(tlinsMoveServerInterface::ModeRelAbs::REL);
			}
		}

		// Parametery rampy w trybie interpolowanym
		{
			// - Predkosc
			auto vx_ = vX * tlinsMath::PI_1_DIV_2 * xDResolution;
			auto vy_ = vX * tlinsMath::PI_1_DIV_2 * xDResolution;
			auto V   = static_cast<long>(::round(::sqrt(vx_ * vx_ + vy_ * vy_)));
			if (V > vXSteps) {
				V = vXSteps;
			}

			request.set_V(V);

			// - Przyspieszenie hamowanie
			request.set_A(static_cast<long>(::round(A * tlinsMath::PI_1_DIV_2 * xDResolution)));
			request.set_D(static_cast<long>(::round(D * tlinsMath::PI_1_DIV_2 * xDResolution)));
		}


		// Wyslanie rzadania
		std::shared_ptr<tlinsMoveServerInterface::tlinsMoveRequestConfirmation> cb{nullptr};
		moveService->moveRequest(deviceName, request, cb);

		// Init request ID
		lastMoveRequestFinalIsError = false;
		lastMoveRequestConfirmed    = true;
		fistIteration               = true;
	}
	catch (tlinsInterfaceException &exc) {
		__THROW__(tlinsAstroException(std::string("Error send stop request. Error: ") + exc.getErrorMessage(),
		                              tlinsAstroException::ASTRO_ERROR_MOVE_REQUEST));
	}
}

void tlinsAstroEngine::restoreState(const Eigen::Matrix3d &attitude, const tlinsSingleTarget &target,
                                    const bool isTarget, const unsigned long xOut, const unsigned long yOut,
                                    const unsigned long xOutEnc, const unsigned long yOutEnc,
                                    const ENGINE_MULTIPLE_MODE_FINALL, const ENGINE_STATE, const ENGINE_MODE mode_,
                                    const bool revX, const bool revY)
{
	if (mode_ == ENGINE_MODE::MODE_NONE) {
		__THROW__(tlinsAstroException(
		    std::string("Only supported modes are ENGINE_MODE::MODE_STANDARD and ENGINE_MODE::MODE_EXTERNAL_SUPPORT"),
		    tlinsAstroException::ASTRO_ERROR_RESTORE_STATE));
	}

	// Zatrzymanie silnika astro
	suspendStandardRun();

	// Zatrzymanie urzadzenia (obu osi)
	stopDevice();

	fistIteration = true;

	// Ustawinie stanu ktory wyklucza sledzenie i inne dzialani akontrolera
	state = ENGINE_STATE::STATE_REGULAR;
	setMode(ENGINE_MODE::MODE_NONE);

	// Przywracanie macierzy obrotu
	attitudeOptimal         = attitude;
	attitudeOptimalInverted = attitude.inverse();

	{
		// Wstawienie celu
		std::unique_lock<std::mutex> lk(actualTargetMtx);

		// Wstawienie celu
		if (isTarget) {
			actualTarget = target;
			actualTargetIsSet.store(isTarget);
		}
	}

	// Ustawinie docelowego trybu pracy kontrolera
	setMode(mode_);

	//
	// Odtworzenie pozycji na sterowniku
	//
	// Mapa osi
	std::map<std::string, tlinsMoveServerInterface::AxisPositionInfo> axies;

	// Os X
	tlinsMoveServerInterface::AxisPositionInfo x;
	x.set_axisName(axisXName);
	x.set_position(xOut);
	x.set_positionEncoder(xOutEnc);
	x.set_devStatus(tlinsMoveServerInterface::tlinsSerialMotorStatus::MOTOR_MAX);
	axies[axisXName] = x;

	// Os Y
	tlinsMoveServerInterface::AxisPositionInfo y;
	y.set_axisName(axisYName);
	y.set_position(yOut);
	y.set_positionEncoder(yOutEnc);
	y.set_devStatus(tlinsMoveServerInterface::tlinsSerialMotorStatus::MOTOR_MAX);
	axies[axisYName] = y;

	try {
		moveService->setPosition(deviceName, axies);
	}
	catch (tlinsInterfaceException &exc) {
		__THROW__(tlinsAstroException(std::string("Error set initial position. Error: ") + exc.getErrorMessage(),
		                              tlinsAstroException::ASTRO_ERROR_MOVE_REQUEST));
	}

	// Ustawienie stanu
	state = ENGINE_STATE::STATE_REGULAR;

	// Kierunki obrotow osi
	reversX = revX;
	reversY = revY;

	// Wejscie w petle glowna odpwoeidzialna za sledzenie
	signalStandardRun();
}

//
// -----------------------------------------------
// -----------------------------------------------
//

enum class _v_data_info_ { FULL_INFO = 1, ERROR_INFO = 2, NO_DATA = 3 };

static void __setStatus__(tlins::tlinsRpcStatus *status, const tlins::ErrorCodes errorStatus, const int errorCode,
                          const std::string &desc)
{
	status->set_status(errorStatus);
	status->set_errorcode(errorCode);
	status->set_errordescription(desc);
}

grpc::Status tlinsRpcAstroEngine::getState(grpc::ServerContext *context, const tlins::tlinsBoolValue *request,
                                           tlins::tlinsEngineStateInfo *response)
{
	Eigen::Matrix3d                               attitude;
	tlinsAstroEngine::tlinsSingleTarget           target;
	bool                                          isTarget;
	long                                          xOut;
	long                                          xOutRaw;
	long                                          yOut;
	long                                          yOutRaw;
	tlinsAstroEngine::ENGINE_MULTIPLE_MODE_FINALL mulMode;
	tlinsAstroEngine::ENGINE_STATE                state;
	tlinsAstroEngine::ENGINE_MODE                 mode;

	// Odczyt statusu kontrolera
	try {
		engine.readState(attitude, target, isTarget, xOut, xOutRaw, yOut, yOutRaw, mulMode, state, mode);
	}
	catch (tlinsAstroException &exc) {
		__setStatus__(response->mutable_status(), tlins::ErrorCodes::_ERROR_CODE_ERROR, exc.getErrorID(),
		              exc.getErrorMessage());
		return grpc::Status::OK;
	}

	auto retState = response->mutable_state();

	// Macierz transformacji
	auto retAttitude = retState->mutable_attitude();
	retAttitude->mutable_a00()->set_value(attitude(0, 0));
	retAttitude->mutable_a01()->set_value(attitude(0, 1));
	retAttitude->mutable_a02()->set_value(attitude(0, 2));

	retAttitude->mutable_a10()->set_value(attitude(1, 0));
	retAttitude->mutable_a11()->set_value(attitude(1, 1));
	retAttitude->mutable_a12()->set_value(attitude(1, 2));

	retAttitude->mutable_a20()->set_value(attitude(2, 0));
	retAttitude->mutable_a21()->set_value(attitude(2, 1));
	retAttitude->mutable_a22()->set_value(attitude(2, 2));

	// Pozycja teleskopu
	auto retPosition = retState->mutable_deviceposition();
	retPosition->mutable_x()->set_value(xOut);
	retPosition->mutable_y()->set_value(yOut);
	retPosition->mutable_xencoder()->set_value(0);
	retPosition->mutable_yencoder()->set_value(0);

	// Mode
	switch (mode) {
	case tlinsAstroEngine::ENGINE_MODE::MODE_NONE:
		retState->mutable_mode()->set_mode(tlins::tlinsEngineMode_::_MODE_NONE);
		break;

	case tlinsAstroEngine::ENGINE_MODE::MODE_STANDARD:
		retState->mutable_mode()->set_mode(tlins::tlinsEngineMode_::_MODE_STANDARD);
		break;

	case tlinsAstroEngine::ENGINE_MODE::MODE_EXTERNAL_SUPPORT:
		retState->mutable_mode()->set_mode(tlins::tlinsEngineMode_::_MODE_EXTERNAL_SUPPORT);
		break;
	}

	// State
	switch (state) {
	case tlinsAstroEngine::ENGINE_STATE::STATE_CALIBRATION:
		retState->mutable_state()->set_state(tlins::tlinsEngineStateValue_::_STATE_CALIBRATION);
		break;

	case tlinsAstroEngine::ENGINE_STATE::STATE_REGULAR:
		retState->mutable_state()->set_state(tlins::tlinsEngineStateValue_::_STATE_REGULAR);
		break;
	}

	// Multiple
	switch (mulMode) {
	case tlinsAstroEngine::ENGINE_MULTIPLE_MODE_FINALL::SWITCH_TO_STANDARD:
		retState->mutable_multiplefinal()->set_multiple(tlins::tlinsMultipleModeFinall_::_SWITCH_TO_STANDARD);
		break;

	case tlinsAstroEngine::ENGINE_MULTIPLE_MODE_FINALL::SWITCH_TO_EXTERNAL:
		retState->mutable_multiplefinal()->set_multiple(tlins::tlinsMultipleModeFinall_::_SWITCH_TO_EXTERNAL);
		break;
	}

	//
	// Kierunki obrotu osi
	//
	retState->mutable_xreverse()->set_value(engine.getReversX());
	retState->mutable_yreverse()->set_value(engine.getReversY());

	// Biezacy cel
	auto target__ = retState->mutable_currenttarget();
	if (isTarget) {
		auto curr_target = target__->mutable_target();
		auto object_     = curr_target->mutable_object();

		auto declination_ = object_->mutable_declination();
		declination_->mutable_sign()->set_value(target.target.getDeclination().getSign() == '-' ? true : false);
		declination_->mutable_degris()->set_value(target.target.getDeclination().getDegris());
		declination_->mutable_minutes()->set_value(target.target.getDeclination().getMinutes());
		declination_->mutable_seconds()->set_value(target.target.getDeclination().getSeconds());

		auto hourAngle_ = object_->mutable_hourangle();
		hourAngle_->mutable_sign()->set_value(target.target.getHourAngle().getSign() == '-' ? true : false);
		hourAngle_->mutable_degris()->set_value(target.target.getHourAngle().getDegris());
		hourAngle_->mutable_minutes()->set_value(target.target.getHourAngle().getMinutes());
		hourAngle_->mutable_seconds()->set_value(target.target.getHourAngle().getSeconds());

		auto properMotionRA_ = object_->mutable_propermotionra();
		properMotionRA_->set_value(target.target.getProperMotionRA());

		auto properMotionDC_ = object_->mutable_propermotiondc();
		properMotionDC_->set_value(target.target.getProperMotionDC());

		auto parallax_ = object_->mutable_parallax();
		parallax_->set_value(target.target.getParallax());

		auto radialVelocity_ = object_->mutable_radialvelocity();
		radialVelocity_->set_value(target.target.getRadialVelocity());

		auto catalogType_ = object_->mutable_catalogtype();
		catalogType_->set_value(target.target.getCatalogType());

		auto delta_ = curr_target->mutable_delta();
		delta_->set_value(/*target.targetDelta*/ 0.0);
		curr_target->mutable_speed()->set_value(target.speed);
		curr_target->mutable_aceleration()->set_value(target.aceleration);
	}

	__setStatus__(response->mutable_status(), tlins::ErrorCodes::_ERROR_CODE_SUCCESS, tlinsException::SUCCESS,
	              "SUCCESS");
	return grpc::Status::OK;
}

grpc::Status tlinsRpcAstroEngine::restoreState(grpc::ServerContext *context, const tlins::tlinsEngineState *request,
                                               tlins::tlinsRpcStatus *response)
{
	Eigen::Matrix3d                                      attitude;
	std::unique_ptr<tlinsAstroEngine::tlinsSingleTarget> target{nullptr};
	bool                                                 isTarget{false};
	unsigned long                                        xOut{0};
	unsigned long                                        yOut{0};
	unsigned long                                        xOutEnc{0};
	unsigned long                                        yOutEnc{0};
	tlinsAstroEngine::ENGINE_MULTIPLE_MODE_FINALL        mulMode;
	tlinsAstroEngine::ENGINE_STATE                       state;
	tlinsAstroEngine::ENGINE_MODE                        mode;

	// Macierz transformacji
	attitude(0, 0) = request->attitude().a00().value();
	attitude(0, 1) = request->attitude().a01().value();
	attitude(0, 2) = request->attitude().a02().value();

	attitude(1, 0) = request->attitude().a10().value();
	attitude(1, 1) = request->attitude().a11().value();
	attitude(1, 2) = request->attitude().a12().value();

	attitude(2, 0) = request->attitude().a20().value();
	attitude(2, 1) = request->attitude().a21().value();
	attitude(2, 2) = request->attitude().a22().value();

	// // Pozycja teleskopu
	xOut = request->deviceposition().x().value();
	yOut = request->deviceposition().y().value();

	xOutEnc = request->deviceposition().xencoder().value();
	yOutEnc = request->deviceposition().yencoder().value();

	// Mode
	switch (request->mode().mode()) {
	case tlins::tlinsEngineMode_::_MODE_NONE:
		mode = tlinsAstroEngine::ENGINE_MODE::MODE_NONE;
		break;

	case tlins::tlinsEngineMode_::_MODE_STANDARD:
		mode = tlinsAstroEngine::ENGINE_MODE::MODE_STANDARD;
		break;

	case tlins::tlinsEngineMode_::_MODE_EXTERNAL_SUPPORT:
		mode = tlinsAstroEngine::ENGINE_MODE::MODE_EXTERNAL_SUPPORT;
		break;
	}

	// State
	switch (request->state().state()) {
	case tlins::tlinsEngineStateValue_::_STATE_CALIBRATION:
		state = tlinsAstroEngine::ENGINE_STATE::STATE_CALIBRATION;
		break;

	case tlins::tlinsEngineStateValue_::_STATE_REGULAR:
		state = tlinsAstroEngine::ENGINE_STATE::STATE_REGULAR;
		break;
	}

	// Multiple
	switch (request->multiplefinal().multiple()) {
	case tlins::tlinsMultipleModeFinall_::_SWITCH_TO_STANDARD:
		mulMode = tlinsAstroEngine::ENGINE_MULTIPLE_MODE_FINALL::SWITCH_TO_STANDARD;
		break;

	case tlins::tlinsMultipleModeFinall_::_SWITCH_TO_EXTERNAL:
		mulMode = tlinsAstroEngine::ENGINE_MULTIPLE_MODE_FINALL::SWITCH_TO_EXTERNAL;
		break;
	}

	// Target
	isTarget = true;
	if (request->currenttarget().has_target()) {
		isTarget = true;

		auto &currt = request->currenttarget().target();
		auto &objt_ = currt.object();

		// Obiekt
		tlinsAstroObject obj;

		tlinsCoordinate ra{objt_.hourangle().sign().value(), objt_.hourangle().degris().value(),
		                   objt_.hourangle().minutes().value(), objt_.hourangle().seconds().value()};
		tlinsCoordinate dc{objt_.declination().sign().value(), objt_.declination().degris().value(),
		                   objt_.declination().minutes().value(), objt_.declination().seconds().value()};
		obj.set(ra, dc);
		obj.setCatalogType(objt_.catalogtype().value());
		obj.setParallax(objt_.parallax().value());
		obj.setProperMotion(objt_.propermotionra().value(), objt_.propermotiondc().value());
		obj.setRadialVelocity(objt_.radialvelocity().value());
		target.reset(new tlinsAstroEngine::tlinsSingleTarget(obj, currt.speed().value(), currt.aceleration().value()));
	}

	// Ustawienie stanu
	try {
		engine.restoreState(attitude, *target, isTarget, xOut, yOut, xOutEnc, yOutEnc, mulMode, state, mode,
		                    request->xreverse().value(), request->yreverse().value());
	}
	catch (tlinsAstroException &exc) {
		__setStatus__(response, tlins::ErrorCodes::_ERROR_CODE_ERROR, exc.getErrorID(), exc.getErrorMessage());

		return grpc::Status::OK;
	}

	__setStatus__(response, tlins::ErrorCodes::_ERROR_CODE_SUCCESS, tlinsException::SUCCESS, "SUCCESS");
	return grpc::Status::OK;
}

grpc::Status tlinsRpcAstroEngine::getCalibrationState(grpc::ServerContext *context, const tlins::Void *request,
                                                      tlins::tlinsEngineCalibrarionStateInfo *response)
{
	// Aktualny stan kontrolera
	auto retState = response->mutable_state();

	// State
	switch (engine.getState()) {
	case tlinsAstroEngine::ENGINE_STATE::STATE_CALIBRATION:
		retState->mutable_state()->set_state(tlins::tlinsEngineStateValue_::_STATE_CALIBRATION);
		break;

	case tlinsAstroEngine::ENGINE_STATE::STATE_REGULAR:
		retState->mutable_state()->set_state(tlins::tlinsEngineStateValue_::_STATE_REGULAR);
		break;
	}

	// Licznik iteracji kalibracji
	auto retCount = retState->mutable_iterationcount();
	retCount->set_value(engine.iterationCount());

	// Status mechanizmu sledzenia
	response->mutable_istrackingenabled()->set_value(engine.isTrackingActive());

	// Sukces
	__setStatus__(response->mutable_status(), tlins::ErrorCodes::_ERROR_CODE_SUCCESS, tlinsException::SUCCESS,
	              "SUCCESS");

	return grpc::Status::OK;
}

grpc::Status tlinsRpcAstroEngine::startTracking(grpc::ServerContext *context, const tlins::Void *request,
                                                tlins::tlinsRpcStatus *response)
{
	// Uruchomienie watku
	engine.reasumeStandardRun();

	__setStatus__(response, tlins::ErrorCodes::_ERROR_CODE_SUCCESS, tlinsException::SUCCESS, "SUCCESS");
	return grpc::Status::OK;
}

grpc::Status tlinsRpcAstroEngine::stopTracking(grpc::ServerContext *context, const tlins::Void *request,
                                               tlins::tlinsRpcStatus *response)
{
	// Zatrzymnanie watku
	engine.suspendStandardRun();

	__setStatus__(response, tlins::ErrorCodes::_ERROR_CODE_SUCCESS, tlinsException::SUCCESS, "SUCCESS");
	return grpc::Status::OK;
}

grpc::Status tlinsRpcAstroEngine::getTarget(grpc::ServerContext *context, const tlins::Void *request,
                                            tlins::tlinsCurrentTargetInfo *response)
{
	tlinsAstroEngine::tlinsSingleTarget target;
	bool                                isTarget{false};

	// Odczyt aktualnego celu
	try {
		engine.readCurrentTarget(target, isTarget);
	}
	catch (tlinsAstroException &exc) {
		__setStatus__(response->mutable_status(), tlins::ErrorCodes::_ERROR_CODE_ERROR, exc.getErrorID(),
		              exc.getErrorMessage());
		return grpc::Status::OK;
	}

	// Biezacy cel
	auto curr_target = response->mutable_target();
	if (isTarget) {

		auto object_ = curr_target->mutable_object();

		auto declination_ = object_->mutable_declination();
		declination_->mutable_sign()->set_value(target.target.getDeclination().getSign() == '-' ? true : false);
		declination_->mutable_degris()->set_value(target.target.getDeclination().getDegris());
		declination_->mutable_minutes()->set_value(target.target.getDeclination().getMinutes());
		declination_->mutable_seconds()->set_value(target.target.getDeclination().getSeconds());

		auto hourAngle_ = object_->mutable_hourangle();
		hourAngle_->mutable_sign()->set_value(target.target.getHourAngle().getSign() == '-' ? true : false);
		hourAngle_->mutable_degris()->set_value(target.target.getHourAngle().getDegris());
		hourAngle_->mutable_minutes()->set_value(target.target.getHourAngle().getMinutes());
		hourAngle_->mutable_seconds()->set_value(target.target.getHourAngle().getSeconds());

		auto properMotionRA_ = object_->mutable_propermotionra();
		properMotionRA_->set_value(target.target.getProperMotionRA());

		auto properMotionDC_ = object_->mutable_propermotiondc();
		properMotionDC_->set_value(target.target.getProperMotionDC());

		auto parallax_ = object_->mutable_parallax();
		parallax_->set_value(target.target.getParallax());

		auto radialVelocity_ = object_->mutable_radialvelocity();
		radialVelocity_->set_value(target.target.getRadialVelocity());

		auto catalogType_ = object_->mutable_catalogtype();
		catalogType_->set_value(target.target.getCatalogType());

		auto delta_ = curr_target->mutable_delta();
		delta_->set_value(/*target.targetDelta*/ 0.0);

		curr_target->mutable_speed()->set_value(target.speed);

		curr_target->mutable_aceleration()->set_value(target.aceleration);
	}

	__setStatus__(response->mutable_status(), tlins::ErrorCodes::_ERROR_CODE_SUCCESS, tlinsException::SUCCESS,
	              "SUCCESS");
	return grpc::Status::OK;
}

grpc::Status tlinsRpcAstroEngine::setTarget(grpc::ServerContext *context, const tlins::tlinsTarget *request,
                                            tlins::tlinsRpcStatus *response)
{
	try {
		double        V{0.0};
		double        A{0.0};
		unsigned long delta{0L};
		bool          isIncrement = false;

		// Predkosc
		if (request->has_speed()) {
			V = request->speed().value();
		}

		// Przyspieszenie
		if (request->has_aceleration()) {
			A = request->aceleration().value();
		}

		if (request->has_isincrement()) {
			isIncrement = request->isincrement().value();
		}

		// Obiekt astronomiczny
		tlinsAstroObject object{};

		tlinsCoordinate ra{request->object().hourangle().sign().value(), request->object().hourangle().degris().value(),
		                   request->object().hourangle().minutes().value(),
		                   request->object().hourangle().seconds().value()};

		tlinsCoordinate dc{
		    request->object().declination().sign().value(), request->object().declination().degris().value(),
		    request->object().declination().minutes().value(), request->object().declination().seconds().value()};

		object.set(ra, dc);
		object.setParallax(request->object().parallax().value());
		object.setProperMotion(request->object().propermotionra().value(), request->object().propermotiondc().value());
		object.setRadialVelocity(request->object().radialvelocity().value());
		object.setCatalogType(request->object().catalogtype().value());

		if (isIncrement) {
			tlinsAstroEngine::tlinsSingleTarget currentTarget;

			while (engine.getTarget(currentTarget)) {
				object.setParallax(0.0);
				object.setProperMotion(0.0, 0.0);
				object.setRadialVelocity(0.0);
				object.setCatalogType("");

				// tf2a - godziny do radianow
				// af2a - stopnie do radianow

				double raRad = 0.0;
				double dcRad = 0.0;
				{
					auto rc = ::iauTf2a(request->object().hourangle().sign().value() ? '-' : '+',
					                    request->object().hourangle().degris().value(),
					                    request->object().hourangle().minutes().value(),
					                    request->object().hourangle().seconds().value(), &raRad);
				}

				{
					auto rc = ::iauAf2a(request->object().declination().sign().value() ? '-' : '+',
					                    request->object().declination().degris().value(),
					                    request->object().declination().minutes().value(),
					                    request->object().declination().seconds().value(), &dcRad);
				}

				double raRadT = 0.0;
				double dcRadT = 0.0;
				{
					auto rc = ::iauTf2a(currentTarget.target.getHourAngle().getSign(),
					                    currentTarget.target.getHourAngle().getDegris(),
					                    currentTarget.target.getHourAngle().getMinutes(),
					                    currentTarget.target.getHourAngle().getSeconds(), &raRadT);
				}

				{
					auto rc = ::iauAf2a(currentTarget.target.getDeclination().getSign(),
					                    currentTarget.target.getDeclination().getDegris(),
					                    currentTarget.target.getDeclination().getMinutes(),
					                    currentTarget.target.getDeclination().getSeconds(), &dcRadT);
				}

				// Obliczenie wynikowego celu
				raRadT += raRad;
				dcRadT += dcRad;

				// Normalizacja pozycji
				raRadT = ::iauAnp(raRadT);
				dcRadT = ::iauAnpm(dcRadT);

				char signRa;
				char signDc;

				std::array<int, 4> raTab;
				std::array<int, 4> dcTab;
				::iauA2tf(7, raRadT, &signRa, raTab.data());
				tlinsCoordinate ra{signRa, raTab[0], raTab[1],
				                   static_cast<double>(raTab[2]) + static_cast<double>(raTab[3]) / 10000000.0};

				::iauA2af(7, dcRadT, &signDc, dcTab.data());
				tlinsCoordinate dc{signDc, dcTab[0], dcTab[1],
				                   static_cast<double>(dcTab[2]) + static_cast<double>(dcTab[3]) / 10000000.0};

				// Ustawinie wspolrzednej na obiekcie
				object.set(ra, dc);

				// Zakonczenie petli
				break;
			}
		}

		// Ustawienie nowego celu
		engine.setTarget(object, V, A);

		// Sukces
		__setStatus__(response, tlins::ErrorCodes::_ERROR_CODE_SUCCESS, tlinsException::SUCCESS, "SUCCESS");
	}
	catch (tlinsAstroException &exc) {
		__setStatus__(response, tlins::ErrorCodes::_ERROR_CODE_ERROR, exc.getErrorID(), exc.getErrorMessage());
	}
	return grpc::Status::OK;
}

grpc::Status tlinsRpcAstroEngine::registerMesermentDefered(grpc::ServerContext         *context,
                                                           const tlins::tlinsMeserment *request,
                                                           tlins::tlinsRpcStatus       *response)
{
	try {
		tlinsCoordinate ra{
		    request->reference().hourangle().sign().value(), request->reference().hourangle().degris().value(),
		    request->reference().hourangle().minutes().value(), request->reference().hourangle().seconds().value()};

		tlinsCoordinate dc{
		    request->reference().declination().sign().value(), request->reference().declination().degris().value(),
		    request->reference().declination().minutes().value(), request->reference().declination().seconds().value()};

		deferedReferenceObject.set(ra, dc);
		deferedReferenceObject.setParallax(request->reference().parallax().value());
		deferedReferenceObject.setProperMotion(request->reference().propermotionra().value(),
		                                       request->reference().propermotiondc().value());
		deferedReferenceObject.setRadialVelocity(request->reference().radialvelocity().value());
		deferedReferenceObject.setCatalogType(request->reference().catalogtype().value());

		// Blad
		tlinsCoordinate inLongitudeErr{
		    request->inputerror().longitude().sign().value(), request->inputerror().longitude().degris().value(),
		    request->inputerror().longitude().minutes().value(), request->inputerror().longitude().seconds().value()};

		tlinsCoordinate inLatitudeErr{
		    request->inputerror().latitude().sign().value(), request->inputerror().latitude().degris().value(),
		    request->inputerror().latitude().minutes().value(), request->inputerror().latitude().seconds().value()};

		deferedReferenceObjectInputErr.setLongitude(inLongitudeErr);
		deferedReferenceObjectInputErr.setLatitude(inLatitudeErr);
		deferedReferenceObjectWeight = request->w().value();

		isReferenceObjectDefered        = true;
		referenceObjectDeferedConfirmed = false;

		// Sukces
		__setStatus__(response, tlins::ErrorCodes::_ERROR_CODE_SUCCESS, tlinsException::SUCCESS, "SUCCESS");
	}
	catch (tlinsAstroException &exc) {
		__setStatus__(response, tlins::ErrorCodes::_ERROR_CODE_ERROR, exc.getErrorID(), exc.getErrorMessage());
	}

	return grpc::Status::OK;
}

grpc::Status tlinsRpcAstroEngine::confirmDeferedMeserment(grpc::ServerContext *context, const tlins::Void *request,
                                                          tlins::tlinsRpcStatus *response)
{
	try {
		if (isReferenceObjectDefered && !referenceObjectDeferedConfirmed) {
			// Rejestracja pomiaru tylko w warincie braku inputa. Wspolrzedne urzadzenia beda
			// pobierane z kontrolera osi
			engine.registerMeserment(deferedReferenceObjectInputErr, deferedReferenceObject,
			                         deferedReferenceObjectWeight);

			referenceObjectDeferedConfirmed = true;

			// Sukces
			__setStatus__(response, tlins::ErrorCodes::_ERROR_CODE_SUCCESS, tlinsException::SUCCESS, "SUCCESS");
		} else {
			__setStatus__(response, tlins::ErrorCodes::_ERROR_CODE_ERROR, tlinsException::ERROR, "No deferred object.");
		}
	}
	catch (tlinsAstroException &exc) {
		__setStatus__(response, tlins::ErrorCodes::_ERROR_CODE_ERROR, exc.getErrorID(), exc.getErrorMessage());
	}

	return grpc::Status::OK;
}

grpc::Status tlinsRpcAstroEngine::registerMeserment(grpc::ServerContext *context, const tlins::tlinsMeserment *request,
                                                    tlins::tlinsRpcStatus *response)
{
	try {
		// Obiekt referencyjny
		tlinsAstroObject referenceObject{};

		tlinsCoordinate ra{
		    request->reference().hourangle().sign().value(), request->reference().hourangle().degris().value(),
		    request->reference().hourangle().minutes().value(), request->reference().hourangle().seconds().value()};

		tlinsCoordinate dc{
		    request->reference().declination().sign().value(), request->reference().declination().degris().value(),
		    request->reference().declination().minutes().value(), request->reference().declination().seconds().value()};

		referenceObject.set(ra, dc);
		referenceObject.setParallax(request->reference().parallax().value());
		referenceObject.setProperMotion(request->reference().propermotionra().value(),
		                                request->reference().propermotiondc().value());
		referenceObject.setRadialVelocity(request->reference().radialvelocity().value());
		referenceObject.setCatalogType(request->reference().catalogtype().value());

		// Blad
		tlinsCoordinate inLongitudeErr{
		    request->inputerror().longitude().sign().value(), request->inputerror().longitude().degris().value(),
		    request->inputerror().longitude().minutes().value(), request->inputerror().longitude().seconds().value()};

		tlinsCoordinate inLatitudeErr{
		    request->inputerror().latitude().sign().value(), request->inputerror().latitude().degris().value(),
		    request->inputerror().latitude().minutes().value(), request->inputerror().latitude().seconds().value()};

		tlinsFullCoordinate inputErr{inLongitudeErr, inLatitudeErr};

		if (request->has_input()) {
			tlinsCoordinate inLongitude{
			    request->input().longitude().sign().value(), request->input().longitude().degris().value(),
			    request->input().longitude().minutes().value(), request->input().longitude().seconds().value()};

			tlinsCoordinate inLatitude{
			    request->input().latitude().sign().value(), request->input().latitude().degris().value(),
			    request->input().latitude().minutes().value(), request->input().latitude().seconds().value()};

			tlinsFullCoordinate input{inLongitude, inLatitude};

			// Rejestracja pomiaru
			engine.registerMeserment(input, inputErr, referenceObject, request->w().value());
		} else {
			// Rejestracja pomiaru
			engine.registerMeserment(inputErr, referenceObject, request->w().value());
		}

		isReferenceObjectDefered        = false;
		referenceObjectDeferedConfirmed = false;

		// Sukces
		__setStatus__(response, tlins::ErrorCodes::_ERROR_CODE_SUCCESS, tlinsException::SUCCESS, "SUCCESS");
	}
	catch (tlinsAstroException &exc) {
		__setStatus__(response, tlins::ErrorCodes::_ERROR_CODE_ERROR, exc.getErrorID(), exc.getErrorMessage());
	}

	return grpc::Status::OK;
}

grpc::Status tlinsRpcAstroEngine::setEnvironment(grpc::ServerContext *context, const tlins::tlinsEnvironment *request,
                                                 tlins::tlinsRpcStatus *response)
{
	tlinsEnvironment::setAmbientPressure(request->ambientpressure().value());
	tlinsEnvironment::setRealHumidity(request->realhumidity().value());
	tlinsEnvironment::setTemperature(request->temperature().value());
	tlinsEnvironment::setEffectiveColor(request->effectivecolor().value());

	__setStatus__(response, tlins::ErrorCodes::_ERROR_CODE_SUCCESS, tlinsException::SUCCESS, "SUCCESS");
	return grpc::Status::OK;
}

grpc::Status tlinsRpcAstroEngine::closeCalibration(grpc::ServerContext *context, const tlins::Void *request,
                                                   tlins::tlinsRpcStatus *response)
{
	try {
		engine.closeCalibration();

		isReferenceObjectDefered        = false;
		referenceObjectDeferedConfirmed = false;

		__setStatus__(response, tlins::ErrorCodes::_ERROR_CODE_SUCCESS, tlinsException::SUCCESS, "SUCCESS");
	}
	catch (tlinsAstroException &exc) {
		__setStatus__(response, tlins::ErrorCodes::_ERROR_CODE_ERROR, exc.getErrorID(), exc.getErrorMessage());
	}
	return grpc::Status::OK;
}

grpc::Status tlinsRpcAstroEngine::setObservationPlace(grpc::ServerContext                *context,
                                                      const tlins::tlinsObservationPlace *request,
                                                      tlins::tlinsRpcStatus              *response)
{
	try {
		auto &instance = tlinsObservationPlace::getInstance();

		tlinsCoordinate longitude(request->longitude().sign().value(), request->longitude().degris().value(),
		                          request->longitude().minutes().value(), request->longitude().seconds().value());

		tlinsCoordinate latitude(request->latitude().sign().value(), request->latitude().degris().value(),
		                         request->latitude().minutes().value(), request->latitude().seconds().value());

		instance.setLongitude(longitude);
		instance.setLatitude(latitude);

		instance.setHm(request->hm().value());

		if (request->has_eptype()) {
			switch (request->eptype().value()) {
			case tlins::tlinsElipsoideType::_WGS_84:
				instance.setEllipsoidType(tlinsObservationPlace::ElipsoideType::WGS_84);
				break;

			case tlins::tlinsElipsoideType::_GRS_80:
				instance.setEllipsoidType(tlinsObservationPlace::ElipsoideType::GRS_80);
				break;

			case tlins::tlinsElipsoideType::_WGS_72:
				instance.setEllipsoidType(tlinsObservationPlace::ElipsoideType::WGS_72);
				break;
			}
		}

		__setStatus__(response, tlins::ErrorCodes::_ERROR_CODE_SUCCESS, tlinsException::SUCCESS, "SUCCESS");
	}
	catch (tlinsAstroException &exc) {
		__setStatus__(response, tlins::ErrorCodes::_ERROR_CODE_ERROR, exc.getErrorID(), exc.getErrorMessage());
	}

	return grpc::Status::OK;
}

grpc::Status tlinsRpcAstroEngine::setIERSInfo(grpc::ServerContext *context, const tlins::tlinsIERSList *request,
                                              tlins::tlinsRpcStatus *response)
{
	// IOERS manager instance
	auto &inst = tlinsIERSInfoManager::getInstance();

	if (request->overwrite().value())
		inst.clear();

	for (int i = 0; i < request->items_size(); i++) {
		auto         &item = request->items(i);
		tlinsIERSInfo iers{item.year().value(), item.month().value(),   item.day().value(),  item.pmx().value(),
		                   item.pmy().value(),  item.deltaut().value(), item.dpsi().value(), item.depsilon().value(),
		                   item.dx().value(),   item.dy().value()};
		inst.add(iers);
	}

	// Wymuszenie zapisania zmian do pliku
	if (request->storelocaly().value())
		inst.storeIntoFile();

	__setStatus__(response, tlins::ErrorCodes::_ERROR_CODE_SUCCESS, tlinsException::SUCCESS, "SUCCESS");
	return grpc::Status::OK;
}

grpc::Status tlinsRpcAstroEngine::setMode(grpc::ServerContext *context, const tlins::tlinsEngineMode *request,
                                          tlins::tlinsRpcStatus *response)
{
	try {
		switch (request->mode()) {
		case tlins::tlinsEngineMode_::_MODE_NONE:

			__setStatus__(response, tlins::ErrorCodes::_ERROR_CODE_ERROR, tlinsAstroException::ASTRO_ERROR_INVALID_MODE,
			              "Invalid server mode.");
			return grpc::Status::OK;

		case tlins::tlinsEngineMode_::_MODE_STANDARD:
			engine.setMode(tlinsAstroEngine::ENGINE_MODE::MODE_STANDARD);
			break;

		case tlins::tlinsEngineMode_::_MODE_STANDARD_SPEED:
			engine.setMode(tlinsAstroEngine::ENGINE_MODE::MODE_STANDARD_SPEED);
			break;

		case tlins::tlinsEngineMode_::_MODE_EXTERNAL_SUPPORT:
			engine.setMode(tlinsAstroEngine::ENGINE_MODE::MODE_EXTERNAL_SUPPORT);
			break;
		}
		__setStatus__(response, tlins::ErrorCodes::_ERROR_CODE_SUCCESS, tlinsException::SUCCESS, "SUCCESS");
	}
	catch (tlinsAstroException &exc) {
		__setStatus__(response, tlins::ErrorCodes::_ERROR_CODE_ERROR, exc.getErrorID(), exc.getErrorMessage());
	}

	return grpc::Status::OK;
}

grpc::Status tlinsRpcAstroEngine::resetCalibration(grpc::ServerContext                *context,
                                                   const tlins::tlinsResetCalibration *request,
                                                   tlins::tlinsRpcStatus              *response)
{
	try {

		tlinsAstroEngine::ReverseDevice xValue{tlinsAstroEngine::ReverseDevice::DEVICE_SETTINGS};
		tlinsAstroEngine::ReverseDevice yValue{tlinsAstroEngine::ReverseDevice::DEVICE_SETTINGS};

		switch (request->reversedevicex().value()) {
		case tlins::BoolValueExtendCodes::_DERIVED:
			xValue = tlinsAstroEngine::ReverseDevice::DEVICE_SETTINGS;
			break;
		case tlins::BoolValueExtendCodes::_TRUE:
			xValue = tlinsAstroEngine::ReverseDevice::DEVICE_REVERSE;
			break;
		case tlins::BoolValueExtendCodes::_FALSE:
			xValue = tlinsAstroEngine::ReverseDevice::DEVICE_NO_REVERSE;
			break;
		}

		switch (request->reversedevicey().value()) {
		case tlins::BoolValueExtendCodes::_DERIVED:
			yValue = tlinsAstroEngine::ReverseDevice::DEVICE_SETTINGS;
			break;
		case tlins::BoolValueExtendCodes::_TRUE:
			yValue = tlinsAstroEngine::ReverseDevice::DEVICE_REVERSE;
			break;
		case tlins::BoolValueExtendCodes::_FALSE:
			yValue = tlinsAstroEngine::ReverseDevice::DEVICE_NO_REVERSE;
			break;
		}

		engine.resetEngine(xValue, yValue);
		__setStatus__(response, tlins::ErrorCodes::_ERROR_CODE_SUCCESS, tlinsException::SUCCESS, "SUCCESS");
	}
	catch (tlinsAstroException &exc) {
		__setStatus__(response, tlins::ErrorCodes::_ERROR_CODE_ERROR, exc.getErrorID(), exc.getErrorMessage());
	}
	return grpc::Status::OK;
}

grpc::Status tlinsRpcAstroEngine::setTargetForCurrentPosition(grpc::ServerContext *context, const tlins::Void *request,
                                                              tlins::tlinsRpcStatus *response)
{
	try {
		if (engine.setTargetForCurrentPossition()) {
			__setStatus__(response, tlins::ErrorCodes::_ERROR_CODE_SUCCESS, tlinsException::SUCCESS, "SUCCESS");
		} else {
			__setStatus__(response, tlins::ErrorCodes::_ERROR_CODE_ERROR, tlinsAstroException::ASTRO_ERROR_SET_TARGET,
			              "Error set target based on current device position.");
		}
	}
	catch (tlinsAstroException &exc) {
		__setStatus__(response, tlins::ErrorCodes::_ERROR_CODE_ERROR, exc.getErrorID(), exc.getErrorMessage());
	}
	return grpc::Status::OK;
}

grpc::Status tlinsRpcAstroEngine::setTracking(grpc::ServerContext *context, const tlins::tlinsTracking *request,
                                              tlins::tlinsRpcStatus *response)
{
	double ra  = request->ra().value();
	double dec = request->dec().value();

	engine.trackingSet(ra, dec);
	__setStatus__(response, tlins::ErrorCodes::_ERROR_CODE_SUCCESS, tlinsException::SUCCESS, "SUCCESS");
	return grpc::Status::OK;
}

grpc::Status tlinsRpcAstroEngine::setTrackingState(grpc::ServerContext *context, const tlins::tlinsBoolValue *request,
                                                   tlins::tlinsRpcStatus *response)
{
	bool status = request->value();

	if (engine.trackingStatusSet(status)) {
		__setStatus__(response, tlins::ErrorCodes::_ERROR_CODE_SUCCESS, tlinsException::SUCCESS, "SUCCESS");
	} else {
		__setStatus__(response, tlins::ErrorCodes::_ERROR_CODE_ERROR,
		              tlinsAstroException::ASTRO_ERROR_SET_TRACKING_STATUS, "Error enable tracking.");
	}
	return grpc::Status::OK;
}

grpc::Status tlinsRpcAstroEngine::getTrackingState(grpc::ServerContext *context, const tlins::Void *request,
                                                   tlins::tlinsTrackingStatus *response)
{
	bool   rstatus;
	double rra;
	double rdec;

	engine.trackingStatusGet(rstatus, rra, rdec);
	response->mutable_ra()->set_value(rra);
	response->mutable_dec()->set_value(rdec);
	response->mutable_trackingstatus()->set_value(rstatus);
	__setStatus__(response->mutable_status(), tlins::ErrorCodes::_ERROR_CODE_SUCCESS, tlinsException::SUCCESS,
	              "SUCCESS");
	return grpc::Status::OK;
}

grpc::Status tlinsRpcAstroEngine::sync(grpc::ServerContext *context, const tlins::tlinsSync *request,
                                       tlins::tlinsRpcStatus *response)
{
	try {
		double ra{request->ra().value()};
		double dec{request->dec().value()};
		engine.sync(ra, dec);
		__setStatus__(response, tlins::ErrorCodes::_ERROR_CODE_SUCCESS, tlinsException::SUCCESS, "SUCCESS");
	}

	catch (tlinsInterfaceException &exc) {
		__setStatus__(response, tlins::ErrorCodes::_ERROR_CODE_ERROR, exc.getErrorID(), exc.getErrorMessage());
	}
	return grpc::Status::OK;
}

grpc::Status tlinsRpcAstroEngine::guideNorth(grpc::ServerContext *context, const tlins::tlinsIntValue *request,
                                             tlins::tlinsGuiderStatus *response)
{
	try {
		engine.guiderRequestHandling(::abs(request->value()), tlinsAstroEngine::AXIS::DEC,
		                             tlinsAstroEngine::DIRECTION::UP);
		response->set_guiderstatus(tlins::tlinsGuiderStatus_::_GUIDER_SET);
		__setStatus__(response->mutable_status(), tlins::ErrorCodes::_ERROR_CODE_SUCCESS, tlinsException::SUCCESS,
		              "SUCCESS");
	}
	catch (tlinsException &exc) {
		switch (exc.getErrorID()) {
		case tlinsAstroException::ASTRO_ERROR_GUIDER_PENDING_CORRECTION:
			response->set_guiderstatus(tlins::tlinsGuiderStatus_::_GUIDER_IN_PROGRESS);
			break;
		case tlinsAstroException::ASTRO_ERROR_DATE_GET_TIME:
			response->set_guiderstatus(tlins::tlinsGuiderStatus_::_GUIDER_ERROR);
			break;
		case tlinsAstroException::ASTRO_ERROR_NO_TARGET:
		default:
			response->set_guiderstatus(tlins::tlinsGuiderStatus_::_GUIDER_ERROR);
			break;
		}
		__setStatus__(response->mutable_status(), tlins::ErrorCodes::_ERROR_CODE_ERROR, exc.getErrorID(),
		              exc.getErrorMessage());
	}
	return grpc::Status::OK;
}

grpc::Status tlinsRpcAstroEngine::guideSounth(grpc::ServerContext *context, const tlins::tlinsIntValue *request,
                                              tlins::tlinsGuiderStatus *response)
{
	try {
		engine.guiderRequestHandling(::abs(request->value()), tlinsAstroEngine::AXIS::DEC,
		                             tlinsAstroEngine::DIRECTION::DOWN);
		response->set_guiderstatus(tlins::tlinsGuiderStatus_::_GUIDER_SET);
		__setStatus__(response->mutable_status(), tlins::ErrorCodes::_ERROR_CODE_SUCCESS, tlinsException::SUCCESS,
		              "SUCCESS");
	}
	catch (tlinsException &exc) {
		switch (exc.getErrorID()) {
		case tlinsAstroException::ASTRO_ERROR_GUIDER_PENDING_CORRECTION:
			response->set_guiderstatus(tlins::tlinsGuiderStatus_::_GUIDER_IN_PROGRESS);
			break;
		case tlinsAstroException::ASTRO_ERROR_DATE_GET_TIME:
			response->set_guiderstatus(tlins::tlinsGuiderStatus_::_GUIDER_ERROR);
			break;
		case tlinsAstroException::ASTRO_ERROR_NO_TARGET:
		default:
			response->set_guiderstatus(tlins::tlinsGuiderStatus_::_GUIDER_ERROR);
			break;
		}
		__setStatus__(response->mutable_status(), tlins::ErrorCodes::_ERROR_CODE_ERROR, exc.getErrorID(),
		              exc.getErrorMessage());
	}
	return grpc::Status::OK;
}

grpc::Status tlinsRpcAstroEngine::guideEst(grpc::ServerContext *context, const tlins::tlinsIntValue *request,
                                           tlins::tlinsGuiderStatus *response)
{
	try {
		engine.guiderRequestHandling(::abs(request->value()), tlinsAstroEngine::AXIS::RA,
		                             tlinsAstroEngine::DIRECTION::RIGHT);
		response->set_guiderstatus(tlins::tlinsGuiderStatus_::_GUIDER_SET);
		__setStatus__(response->mutable_status(), tlins::ErrorCodes::_ERROR_CODE_SUCCESS, tlinsException::SUCCESS,
		              "SUCCESS");
	}
	catch (tlinsException &exc) {
		switch (exc.getErrorID()) {
		case tlinsAstroException::ASTRO_ERROR_GUIDER_PENDING_CORRECTION:
			response->set_guiderstatus(tlins::tlinsGuiderStatus_::_GUIDER_IN_PROGRESS);
			break;
		case tlinsAstroException::ASTRO_ERROR_DATE_GET_TIME:
			response->set_guiderstatus(tlins::tlinsGuiderStatus_::_GUIDER_ERROR);
			break;
		case tlinsAstroException::ASTRO_ERROR_NO_TARGET:
		default:
			response->set_guiderstatus(tlins::tlinsGuiderStatus_::_GUIDER_ERROR);
			break;
		}

		__setStatus__(response->mutable_status(), tlins::ErrorCodes::_ERROR_CODE_ERROR, exc.getErrorID(),
		              exc.getErrorMessage());
	}
	return grpc::Status::OK;
}

grpc::Status tlinsRpcAstroEngine::guideWest(grpc::ServerContext *context, const tlins::tlinsIntValue *request,
                                            tlins::tlinsGuiderStatus *response)
{
	try {
		engine.guiderRequestHandling(::abs(request->value()), tlinsAstroEngine::AXIS::RA,
		                             tlinsAstroEngine::DIRECTION::LEFT);
		response->set_guiderstatus(tlins::tlinsGuiderStatus_::_GUIDER_SET);
		__setStatus__(response->mutable_status(), tlins::ErrorCodes::_ERROR_CODE_SUCCESS, tlinsException::SUCCESS,
		              "SUCCESS");
	}
	catch (tlinsException &exc) {
		switch (exc.getErrorID()) {
		case tlinsAstroException::ASTRO_ERROR_GUIDER_PENDING_CORRECTION:
			response->set_guiderstatus(tlins::tlinsGuiderStatus_::_GUIDER_IN_PROGRESS);
			break;
		case tlinsAstroException::ASTRO_ERROR_DATE_GET_TIME:
			response->set_guiderstatus(tlins::tlinsGuiderStatus_::_GUIDER_ERROR);
			break;
		case tlinsAstroException::ASTRO_ERROR_NO_TARGET:
		default:
			response->set_guiderstatus(tlins::tlinsGuiderStatus_::_GUIDER_ERROR);
			break;
		}

		__setStatus__(response->mutable_status(), tlins::ErrorCodes::_ERROR_CODE_ERROR, exc.getErrorID(),
		              exc.getErrorMessage());
	}
	return grpc::Status::OK;
}

grpc::Status tlinsRpcAstroEngine::manualCorrection(grpc::ServerContext                *context,
                                                   const tlins::tlinsManualCorrection *request,
                                                   tlins::tlinsRpcStatus              *response)
{
	double raCorrection{request->ra().value()};
	double decCorrection{request->dec().value()};

	auto raDir  = raCorrection < 0.0 ? tlinsAstroEngine::DIRECTION::LEFT : tlinsAstroEngine::DIRECTION::RIGHT;
	auto decDir = decCorrection < 0.0 ? tlinsAstroEngine::DIRECTION::DOWN : tlinsAstroEngine::DIRECTION::UP;
	try {

		engine.manualCorrectionRequestHandling(raDir, ::fabs(raCorrection), decDir, ::fabs(decCorrection));
		__setStatus__(response, tlins::ErrorCodes::_ERROR_CODE_SUCCESS, tlinsException::SUCCESS, "SUCCESS");
	}
	catch (...) {
		__setStatus__(response, tlins::ErrorCodes::_ERROR_CODE_ERROR, tlinsException::ERROR,
		              "ERROR set manual correction");
	}
	return grpc::Status::OK;
}

grpc::Status tlinsRpcAstroEngine::manualCorrectionReset(grpc::ServerContext *context, const tlins::Void *request,
                                                        tlins::tlinsRpcStatus *response)
{
	engine.manualCorrectionRequestHandlingReset();
	__setStatus__(response, tlins::ErrorCodes::_ERROR_CODE_SUCCESS, tlinsException::SUCCESS, "SUCCESS");
	return grpc::Status::OK;
}

grpc::Status tlinsRpcAstroEngine::manualCorrectionGet(grpc::ServerContext *context, const tlins::Void *request,
                                                      tlins::tlinsManualCorrectionStatus *response)
{
	tlinsAstroEngine::DIRECTION raDir;
	double                      raCorrection;
	tlinsAstroEngine::DIRECTION decDir;
	double                      decCorrection;
	engine.manualCorrectionStatus(raDir, raCorrection, decDir, decCorrection);

	response->mutable_ra()->set_value(raDir == tlinsAstroEngine::DIRECTION::LEFT ? -1.0 * raCorrection : raCorrection);
	response->mutable_dec()->set_value(decDir == tlinsAstroEngine::DIRECTION::UP ? -1.0 * decCorrection
	                                                                             : decCorrection);

	__setStatus__(response->mutable_status(), tlins::ErrorCodes::_ERROR_CODE_SUCCESS, tlinsException::SUCCESS,
	              "SUCCESS");
	return grpc::Status::OK;
}

grpc::Status tlinsRpcAstroEngine::guiderRatioSet(grpc::ServerContext               *context,
                                                 const tlins::tlinsGuiderConfigSet *request,
                                                 tlins::tlinsRpcStatus             *response)
{

	double ra{request->raratio().value()};
	double dec{request->decratio().value()};
	bool   useRaForDec{request->userafordec().value()};

	engine.setGuiderConfiguration(ra, dec, useRaForDec);
	__setStatus__(response, tlins::ErrorCodes::_ERROR_CODE_SUCCESS, tlinsException::SUCCESS, "SUCCESS");
	return grpc::Status::OK;
}

grpc::Status tlinsRpcAstroEngine::guiderRatioGet(grpc::ServerContext *context, const tlins::Void *request,
                                                 tlins::tlinsGuiderConfigStatus *response)
{
	double ra;
	double dec;
	bool   useRaForDec;

	engine.getGuiderConfiguration(ra, dec, useRaForDec);
	response->mutable_raratio()->set_value(ra);
	response->mutable_decratio()->set_value(dec);
	response->mutable_userafordec()->set_value(useRaForDec);
	__setStatus__(response->mutable_status(), tlins::ErrorCodes::_ERROR_CODE_SUCCESS, tlinsException::SUCCESS,
	              "SUCCESS");
	return grpc::Status::OK;
}

tlinsRpcAstroEngine::tlinsRpcAstroEngine(tlinsAstroEngine &engine_) : engine{engine_}
{
}
