#include "tlins_driver.hpp"

#include <tlinsBacktrace.hpp>
#include <tlinsException.hpp>
#include <tlinsastrouibase.h>
#include <tlinscommunicationthread.h>
#include <tlinsconfiguration.h>

#include <astro.pb.h>
#include <string>
#include <tlinsLogger.hpp>

#include <memory>

#undef LOG_ERROR
#include <tlinsLogger.hpp>

TlinsTelescope::TlinsTelescope()
{
}
/**************************************************************************************
** Client is asking us to establish connection to the device
***************************************************************************************/
bool TlinsTelescope::Connect()
{
	std::string urlDev      = "localhost:20001";
	std::string urlDevAsync = "localhost:20003";
	std::string urlAstro    = "localhost:20000";

	//
	// Parametery polaczenia
	//
	auto &cfgInstance = TlinsAstroBase::tlinsConfiguration::getInstance();
	if (cfgInstance.hasKey(TlinsAstroBase::tlinsConfiguration::CONNECTION_PARAMETER_GROUP,
	                       TlinsAstroBase::tlinsConfiguration::CONNECTION_PARAMETER_URL_DEVICE_ENGINE)) {
		urlDev = cfgInstance.getString(TlinsAstroBase::tlinsConfiguration::CONNECTION_PARAMETER_GROUP,
		                               TlinsAstroBase::tlinsConfiguration::CONNECTION_PARAMETER_URL_DEVICE_ENGINE);
	}

	if (cfgInstance.hasKey(TlinsAstroBase::tlinsConfiguration::CONNECTION_PARAMETER_GROUP,
	                       TlinsAstroBase::tlinsConfiguration::CONNECTION_PARAMETER_URL_DEVICE_ENGINE_ASYNCH)) {
		urlDevAsync =
		    cfgInstance.getString(TlinsAstroBase::tlinsConfiguration::CONNECTION_PARAMETER_GROUP,
		                          TlinsAstroBase::tlinsConfiguration::CONNECTION_PARAMETER_URL_DEVICE_ENGINE_ASYNCH);
	}

	if (cfgInstance.hasKey(TlinsAstroBase::tlinsConfiguration::CONNECTION_PARAMETER_GROUP,
	                       TlinsAstroBase::tlinsConfiguration::CONNECTION_PARAMETER_URL_ASTRO_ENGINE)) {
		urlAstro = cfgInstance.getString(TlinsAstroBase::tlinsConfiguration::CONNECTION_PARAMETER_GROUP,
		                                 TlinsAstroBase::tlinsConfiguration::CONNECTION_PARAMETER_URL_ASTRO_ENGINE);
	}

	// Instancja polaczenia
	auto &mgr = TlinsAstroBase::tlinsConnectionsManager::getInstance();

	// Tworzenie polaczenia
	try {
		mgr.setConnection(std::string{TLINS_CONNECTION_DEFAULT}, urlDev.c_str(), urlDevAsync.c_str(), urlAstro.c_str());
	}
	catch (...) {
		DEBUG(INDI::Logger::DBG_ERROR, "TLINS device connected error!");
		return false;
	}
	DEBUG(INDI::Logger::DBG_DEBUG, "TLINS device connected successfully!");
	system("echo OK >> /tmp/status.txt");
	return true;
}
/**************************************************************************************
** Client is asking us to terminate connection to the device
***************************************************************************************/
bool TlinsTelescope::Disconnect()
{
	TlinsAstroBase::tlinsConnectionsManager::getInstance().removeConnection({TLINS_CONNECTION_DEFAULT});
	DEBUG(INDI::Logger::DBG_SESSION, "TLINS device disconnected successfully!");
	return true;
}
/**************************************************************************************
** INDI is asking us for our default device name
***************************************************************************************/
const char *TlinsTelescope::getDefaultName()
{
	return "TLINS mount";
}

//
// --- Konstruktor
// -----------------------------------------------
//
// TlinsTelescope::TlinsTelescope()
// {
// 	DBG_SCOPE = INDI::Logger::getInstance().addDebugLevel("Scope Verbose", "SCOPE");

// 	SetTelescopeCapability(
// 	    // TELESCOPE_CAN_PARK |
// 	    TELESCOPE_CAN_SYNC | TELESCOPE_CAN_GOTO | TELESCOPE_CAN_ABORT |
// 	        // TELESCOPE_HAS_PIER_SIDE_SIMULATION |
// 	        TELESCOPE_HAS_TIME | TELESCOPE_HAS_LOCATION | TELESCOPE_HAS_TRACK_MODE | TELESCOPE_CAN_CONTROL_TRACK |
// 	        TELESCOPE_HAS_TRACK_RATE,
// 	    4);
// }

// //
// // --- Destruktor
// // -----------------------------------------------
// //
// TlinsTelescope::~TlinsTelescope()
// {
// }

// //
// // --- Nazwa urzadzenia
// // -----------------------------------------------
// //
// const char *TlinsTelescope::getDefaultName()
// {
// 	return "TLINS mount";
// }

// //
// // --- Inicializacja wlasciwosci
// // -----------------------------------------------
// //
// bool TlinsTelescope::initProperties()
// {
// 	// Parametery klasy bazowej
// 	INDI::Telescope::initProperties();

// 	// Tryby sledzenia
// 	AddTrackMode("TRACK_SIDEREAL", "Sidereal", true);
// 	AddTrackMode("TRACK_CUSTOM", "Custom");

// 	// Status
// 	trackState = INDI::Telescope::TelescopeStatus::SCOPE_IDLE;

// 	// Sposób prezentacji danch o parkowaniu teleskou - nic nie bedzie pokazywane
// 	SetParkDataType(INDI::Telescope::TelescopeParkData::PARK_NONE);

// 	// Gider - miejsce prrezentacji guidera w UI'u
// 	// initGuiderProperties(getDeviceName(), MOTION_TAB);

// 	// // Dodanie kontrolowania debugowania
// 	// addDebugControl();

// 	// Okreslenie interfejsów wspieranych przez sterownik
// 	// setDriverInterface(getDriverInterface() | INDI::BaseDevice::DRIVER_INTERFACE::GUIDER_INTERFACE |
// 	//                    INDI::BaseDevice::DRIVER_INTERFACE::TELESCOPE_INTERFACE);

// 	// setDefaultPollingPeriod(250);
// 	return true;
// }

// //
// // --- Pobranie wlasciwosci
// // -----------------------------------------------
// //
// void TlinsTelescope::ISGetProperties(const char *dev)
// {
// 	// TODO - aktualnie nie implementowana
// 	INDI::Telescope::ISGetProperties(dev);
// }

// //
// // --- Uaktualnienie parameterow
// // -----------------------------------------------
// //
// bool TlinsTelescope::updateProperties()
// {
// 	// TODO - aktualnie nie implementowana
// 	auto ret = INDI::Telescope::updateProperties();
// 	return ret;
// }

// //
// // --- Podlaczenie do urzadzenia
// // -----------------------------------------------
// //
// bool TlinsTelescope::Connect()
// {
// 	return true;
// 	std::string urlDev      = "localhost:20001";
// 	std::string urlDevAsync = "localhost:20003";
// 	std::string urlAstro    = "localhost:20000";

// 	//
// 	// Parametery polaczenia
// 	//
// 	auto &cfgInstance = TlinsAstroBase::tlinsConfiguration::getInstance();
// 	if (cfgInstance.hasKey(TlinsAstroBase::tlinsConfiguration::CONNECTION_PARAMETER_GROUP,
// 	                       TlinsAstroBase::tlinsConfiguration::CONNECTION_PARAMETER_URL_DEVICE_ENGINE)) {
// 		urlDev = cfgInstance.getString(TlinsAstroBase::tlinsConfiguration::CONNECTION_PARAMETER_GROUP,
// 		                               TlinsAstroBase::tlinsConfiguration::CONNECTION_PARAMETER_URL_DEVICE_ENGINE);
// 	}

// 	if (cfgInstance.hasKey(TlinsAstroBase::tlinsConfiguration::CONNECTION_PARAMETER_GROUP,
// 	                       TlinsAstroBase::tlinsConfiguration::CONNECTION_PARAMETER_URL_DEVICE_ENGINE_ASYNCH)) {
// 		urlDevAsync =
// 		    cfgInstance.getString(TlinsAstroBase::tlinsConfiguration::CONNECTION_PARAMETER_GROUP,
// 		                          TlinsAstroBase::tlinsConfiguration::CONNECTION_PARAMETER_URL_DEVICE_ENGINE_ASYNCH);
// 	}

// 	if (cfgInstance.hasKey(TlinsAstroBase::tlinsConfiguration::CONNECTION_PARAMETER_GROUP,
// 	                       TlinsAstroBase::tlinsConfiguration::CONNECTION_PARAMETER_URL_ASTRO_ENGINE)) {
// 		urlAstro = cfgInstance.getString(TlinsAstroBase::tlinsConfiguration::CONNECTION_PARAMETER_GROUP,
// 		                                 TlinsAstroBase::tlinsConfiguration::CONNECTION_PARAMETER_URL_ASTRO_ENGINE);
// 	}

// 	// Instancja polaczenia
// 	auto &mgr = TlinsAstroBase::tlinsConnectionsManager::getInstance();

// 	// Tworzenie polaczenia
// 	try {
// 		mgr.setConnection(std::string{TLINS_CONNECTION_DEFAULT}, urlDev.c_str(), urlDevAsync.c_str(), urlAstro.c_str());
// 	}
// 	catch (...) {
// 		return false;
// 	}
// 	return false;
// }

// //
// // --- Rozlaczenie
// // -----------------------------------------------
// //
// bool TlinsTelescope::Disconnect()
// {
// 	TlinsAstroBase::tlinsConnectionsManager::getInstance().removeConnection({TLINS_CONNECTION_DEFAULT});
// 	return true;
// }

// //
// // --- Odczyt stanu silnika
// // -----------------------------------------------
// //
// class tlinsStateDownload : public TlinsAstroBase::tlinsCommunicationThreadRequest {
//   private:
// 	std::shared_ptr<TlinsAstroBase::tlinsConnectionContext> connection;
// 	tlinsAstroEngineInterface::tlinsEngineStateInfo &       stateInfo;
// 	std::condition_variable &                               cv;
// 	bool &                                                  end;
// 	bool &                                                  isError;

//   public:
// 	void confirm()
// 	{
// 		TlinsAstroBase::tlinsCommunicationThreadRequest::confirm();
// 	}

// 	virtual void operator()() noexcept
// 	{
// 		isError = false;
// 		try {
// 			// Uruchomienie zapytania
// 			connection->getAstro()->getState(stateInfo);

// 			TlinsAstroBase::tlinsAstroEngineState state;

// 			state.setA11(stateInfo.get_attitude()[0][0]);
// 			state.setA12(stateInfo.get_attitude()[0][1]);
// 			state.setA13(stateInfo.get_attitude()[0][2]);

// 			state.setA21(stateInfo.get_attitude()[1][0]);
// 			state.setA22(stateInfo.get_attitude()[1][1]);
// 			state.setA23(stateInfo.get_attitude()[1][2]);

// 			state.setA31(stateInfo.get_attitude()[2][0]);
// 			state.setA32(stateInfo.get_attitude()[2][1]);
// 			state.setA33(stateInfo.get_attitude()[2][2]);

// 			state.setDeviceX(stateInfo.get_devicePosition().get_x());
// 			state.setDeviceY(stateInfo.get_devicePosition().get_y());
// 			state.setDeviceXEncoder(stateInfo.get_devicePosition().get_xEncoder());
// 			state.setDeviceYEncoder(stateInfo.get_devicePosition().get_yEncoder());

// 			switch (stateInfo.get_mode()) {
// 			case tlinsAstroEngineInterface::tlinsEngineMode ::MODE_EXTERNAL_SUPPORT:
// 				state.setMode(TlinsAstroBase::tlinsAstroEngineState::EngineMode::MODE_EXTERNAL_SUPPORT);
// 				break;

// 			case tlinsAstroEngineInterface::tlinsEngineMode ::MODE_STANDARD:
// 				state.setMode(TlinsAstroBase::tlinsAstroEngineState::EngineMode::MODE_STANDARD);
// 				break;

// 			case tlinsAstroEngineInterface::tlinsEngineMode ::MODE_NONE:
// 				state.setMode(TlinsAstroBase::tlinsAstroEngineState::EngineMode::MODE_NONE);
// 				break;
// 			}

// 			tlinsAstroEngineInterface::tlinsEngineStateValue sInfo;
// 			switch (stateInfo.get_state()) {
// 			case tlinsAstroEngineInterface::tlinsEngineStateValue::STATE_CALIBRATION:
// 				state.setState(TlinsAstroBase::tlinsAstroEngineState::EngineState ::STATE_CALIBRATION);
// 				sInfo = tlinsAstroEngineInterface::tlinsEngineStateValue ::STATE_CALIBRATION;
// 				break;

// 			case tlinsAstroEngineInterface::tlinsEngineStateValue::STATE_CALIBRATION_VELOCITY:
// 				state.setState(TlinsAstroBase::tlinsAstroEngineState::EngineState ::STATE_CALIBRATION_VELOCITY);
// 				sInfo = tlinsAstroEngineInterface::tlinsEngineStateValue::STATE_CALIBRATION_VELOCITY;
// 				break;

// 			case tlinsAstroEngineInterface::tlinsEngineStateValue::STATE_REGULAR:
// 				state.setState(TlinsAstroBase::tlinsAstroEngineState::EngineState ::STATE_REGULAR);
// 				sInfo = tlinsAstroEngineInterface::tlinsEngineStateValue::STATE_REGULAR;
// 				break;
// 			}

// 			state.setRadialVelocity(stateInfo.get_currentTarget().get_object().get_radialVelocity());
// 			state.setPmRA(stateInfo.get_currentTarget().get_object().get_properMotionRA());
// 			state.setPmDC(stateInfo.get_currentTarget().get_object().get_properMotionDC());

// 			{
// 				double h = static_cast<double>(stateInfo.get_currentTarget().get_object().get_hourAngle().get_degris());
// 				double m =
// 				    static_cast<double>(stateInfo.get_currentTarget().get_object().get_hourAngle().get_minutes());
// 				double s =
// 				    static_cast<double>(stateInfo.get_currentTarget().get_object().get_hourAngle().get_seconds());
// 				double hh = h + m / 60.0 + s / 3600.0;
// 				state.setRA(hh);
// 			}

// 			{
// 				double d =
// 				    static_cast<double>(stateInfo.get_currentTarget().get_object().get_declination().get_degris());
// 				double m =
// 				    static_cast<double>(stateInfo.get_currentTarget().get_object().get_declination().get_minutes());
// 				double s =
// 				    static_cast<double>(stateInfo.get_currentTarget().get_object().get_declination().get_seconds());
// 				bool   sign = stateInfo.get_currentTarget().get_object().get_declination().get_sign();
// 				double dd   = d + m / 60.0 + s / 3600.0;
// 				if (sign)
// 					dd *= -1.0;
// 				state.setDC(dd);
// 			}

// 			state.setParallex(stateInfo.get_currentTarget().get_object().get_parallax());
// 			state.setCatalogType(stateInfo.get_currentTarget().get_object().get_catalogType());

// 			state.setSpeed(stateInfo.get_currentTarget().get_speed());
// 			state.setAceleration(stateInfo.get_currentTarget().get_aceleration());
// 			state.setDelta(stateInfo.get_currentTarget().get_delta());

// 			struct timeval timeV;
// 			gettimeofday(&timeV, nullptr);

// 			struct tm * tmTime = localtime(&timeV.tv_sec);
// 			char        timeStr[400];
// 			std::string strLevel;

// 			sprintf(timeStr, "State[%04d.%02d.%02d %02d:%02d:%02d]", tmTime->tm_year + 1900, tmTime->tm_mon + 1,
// 			        tmTime->tm_mday, tmTime->tm_hour, tmTime->tm_min, tmTime->tm_sec);

// 			state.setName(std::string{timeStr});
// 		}
// 		catch (tlinsInterfaceException &exc) {
// 			isError = true;
// 		}

// 		// Obudzenie czekajacego watku
// 		cv.notify_one();

// 		// Oznaczenie zakonczenia
// 		end = true;
// 	}

// 	virtual bool isAsynchronuus()
// 	{
// 		return false;
// 	}

// 	virtual std::string name()
// 	{
// 		return "tlinsStateDownload";
// 	}

// 	tlinsStateDownload(tlinsAstroEngineInterface::tlinsEngineStateInfo &stateInfo_, std::condition_variable &cv_,
// 	                   bool &end_, bool &isError_)
// 	    : stateInfo{stateInfo_}, cv{cv_}, end{end_}, isError{isError_}
// 	{
// 		// Pobranie polaczenia
// 		if (!TlinsAstroBase::tlinsConnectionsManager::getInstance().hasConnection({TLINS_CONNECTION_DEFAULT}))
// 			__THROW__(
// 			    tlinsException(std::string("No active connection: ") + std::string(TLINS_CONNECTION_DEFAULT), -1));

// 		// Polaczenie
// 		connection = TlinsAstroBase::tlinsConnectionsManager::getInstance().getConnection(TLINS_CONNECTION_DEFAULT);
// 	}

// 	virtual ~tlinsStateDownload()
// 	{
// 		connection.reset();
// 	}
// };

// bool TlinsTelescope::ReadScopeStatus()
// {
// 	// 1. Pobranie aktualnego stanu urzadzenia
// 	//    Stan zawiera informacje o pozycji i aktualnych wspolrzednych
// 	tlinsAstroEngineInterface::tlinsEngineStateInfo stateInfo;
// 	std::condition_variable                         cv;
// 	std::mutex                                      mtx;
// 	bool                                            end{false};
// 	bool                                            isError{false};

// 	// Odczyt stanu
// 	try {
// 		std::unique_ptr<TlinsAstroBase::tlinsCommunicationThreadRequest> req(
// 		    new tlinsStateDownload{stateInfo, cv, end, isError});
// 		TlinsAstroBase::tlinsCommunicationThread::getInstance().push(req, true);

// 		// Oczekiwanbie na wqynik
// 		std::unique_lock<std::mutex> lock(mtx);
// 		cv.wait(lock, [&end] { return end; });
// 	}
// 	catch (tlinsException &exc) {
// 		TLINS_LOG_ERROR("Error: " + exc.getErrorMessage());
// 		return false;
// 	}

// 	// Odczyt RA i DC z przekazanych danych
// 	tlinsAstroEngineInterface::tlinsCoordinate oDec = stateInfo.get_currentTarget().get_object().get_declination();
// 	tlinsAstroEngineInterface::tlinsCoordinate oRa  = stateInfo.get_currentTarget().get_object().get_hourAngle();

// 	double ra = static_cast<double>(oRa.get_degris()) + static_cast<double>(oRa.get_minutes()) / 60.0 +
// 	            oRa.get_seconds() / 3600.0;
// 	if (oRa.get_sign())
// 		ra *= -1.0;

// 	double dec = static_cast<double>(oDec.get_degris()) + static_cast<double>(oDec.get_minutes()) / 60.0 +
// 	             oDec.get_seconds() / 3600.0;
// 	if (oDec.get_sign())
// 		dec *= -1.0;

// 	NewRaDec(ra, dec);
// 	return true;
// }

// //
// // --- GOTO
// // -----------------------------------------------
// //
// class TlinsTelescopeTarget : public TlinsAstroBase::tlinsCommunicationThreadRequest {
//   private:
// 	std::shared_ptr<TlinsAstroBase::tlinsConnectionContext> connection;
// 	std::condition_variable &                               cv;
// 	std::atomic<bool> &                                     end;
// 	std::atomic<bool> &                                     isError;

// 	tlins::tlinsTarget target;
// 	double             RA;
// 	double             DC;

//   public:
// 	void confirm()
// 	{
// 		TlinsAstroBase::tlinsCommunicationThreadRequest::confirm();
// 	}

// 	virtual void operator()() noexcept
// 	{
// 		isError = false;
// 		tlinsAstroEngineInterface::tlinsTarget reqData;

// 		//
// 		// Przyspieszenie bedzie brane z osi RA
// 		//
// 		auto &cfgInstance = TlinsAstroBase::tlinsConfiguration::getInstance();

// 		double aRA = 10.0;
// 		if (cfgInstance.hasKey(TlinsAstroBase::tlinsConfiguration::RAMP_PARAMETER_GROUP,
// 		                       TlinsAstroBase::tlinsConfiguration::RAMP_PARAMETER_ASTRO_RA_A)) {
// 			aRA = cfgInstance.getDouble(TlinsAstroBase::tlinsConfiguration::RAMP_PARAMETER_GROUP,
// 			                            TlinsAstroBase::tlinsConfiguration::RAMP_PARAMETER_ASTRO_RA_A);
// 		}

// 		double vRA = 10.0;
// 		if (cfgInstance.hasKey(TlinsAstroBase::tlinsConfiguration::RAMP_PARAMETER_GROUP,
// 		                       TlinsAstroBase::tlinsConfiguration::RAMP_PARAMETER_ASTRO_RA_V_MAX)) {
// 			vRA = cfgInstance.getDouble(TlinsAstroBase::tlinsConfiguration::RAMP_PARAMETER_GROUP,
// 			                            TlinsAstroBase::tlinsConfiguration::RAMP_PARAMETER_ASTRO_RA_V_MAX);
// 		}

// 		reqData.set_aceleration(aRA);
// 		reqData.set_speed(vRA);
// 		reqData.set_delta(0);

// 		tlinsAstroEngineInterface::tlinsAstroObject astroObject;
// 		astroObject.set_properMotionRA(0.0);
// 		astroObject.set_properMotionDC(0.0);
// 		astroObject.set_parallax(0.0);
// 		astroObject.set_radialVelocity(0.0);
// 		astroObject.set_catalogType(std::string{""});

// 		tlinsAstroEngineInterface::tlinsCoordinate ra;
// 		{
// 			int    h;
// 			int    m;
// 			double s;
// 			bool   sign;
// 			TlinsAstroBase::tlinsAstroBaseUtils::splitRA(RA, h, m, s, sign);
// 			ra.set_degris(h);
// 			ra.set_minutes(m);
// 			ra.set_seconds(s);
// 			ra.set_sign(sign);
// 		}

// 		tlinsAstroEngineInterface::tlinsCoordinate dc;
// 		{
// 			int    d;
// 			int    m;
// 			double s;
// 			bool   sign;
// 			TlinsAstroBase::tlinsAstroBaseUtils::splitDegris(DC, d, m, s, sign);
// 			dc.set_degris(d);
// 			dc.set_minutes(m);
// 			dc.set_seconds(s);
// 			dc.set_sign(sign);
// 		}

// 		astroObject.set_hourAngle(ra);
// 		astroObject.set_declination(dc);

// 		reqData.set_object(astroObject);

// 		try {
// 			// Uruchomienie zapytania
// 			connection->getAstro()->setTarget(reqData, false);
// 		}
// 		catch (tlinsInterfaceException &exc) {
// 			isError = true;
// 			TLINS_LOG_ERROR("Error: " + exc.getErrorMessage());
// 		}
// 		cv.notify_one();
// 	}

// 	virtual bool isAsynchronuus()
// 	{
// 		return false;
// 	}

// 	virtual std::string name()
// 	{
// 		return "tlinsSetTarget";
// 	}

// 	TlinsTelescopeTarget(const double ra_, const double dc_, std::condition_variable &cv_, std::atomic<bool> &end_,
// 	                     std::atomic<bool> &isError_)
// 	    : RA{ra_}, DC{dc_}, cv{cv_}, end{end_}, isError{isError_}
// 	{
// 		// Pobranie polaczenia
// 		if (!TlinsAstroBase::tlinsConnectionsManager::getInstance().hasConnection({TLINS_CONNECTION_DEFAULT}))
// 			__THROW__(
// 			    tlinsException(std::string("No active connection: ") + std ::string(TLINS_CONNECTION_DEFAULT), -1));

// 		// Polaczenie
// 		connection = TlinsAstroBase::tlinsConnectionsManager::getInstance().getConnection(TLINS_CONNECTION_DEFAULT);
// 	}

// 	virtual ~TlinsTelescopeTarget()
// 	{
// 		connection.reset();
// 	}
// };

// bool TlinsTelescope::Goto(double ra, double dec)
// {
// 	std::condition_variable cv;
// 	std::mutex              mtx;
// 	std::atomic<bool>       end{false};
// 	std::atomic<bool>       isError{false};

// 	try {
// 		std::unique_ptr<TlinsAstroBase::tlinsCommunicationThreadRequest> req(
// 		    new TlinsTelescopeTarget{ra, dec, cv, end, isError});
// 		TlinsAstroBase::tlinsCommunicationThread::getInstance().push(req);

// 		// Oczekiwanbie na wqynik
// 		std::unique_lock<std::mutex> lock(mtx);
// 		cv.wait(lock, [&end] { return end.load(); });
// 	}
// 	catch (tlinsException &exc) {
// 		TLINS_LOG_ERROR("Error: " + exc.getErrorMessage());
// 		return false;
// 	}
// 	if (isError) {
// 		return false;
// 	}
// 	return true;
// }

// //
// // --- Ustawienie parameterow i kontrola sledzenia
// // -----------------------------------------------
// //
// class TlinsTrackRate : public TlinsAstroBase::tlinsCommunicationThreadRequest {
//   private:
// 	std ::shared_ptr<TlinsAstroBase ::tlinsConnectionContext> connection;
// 	std::condition_variable &                                 cv;
// 	std::atomic<bool> &                                       isError;
// 	std::atomic<bool> &                                       end;
// 	double                                                    RA;
// 	double                                                    DEC;

//   public:
// 	void confirm()
// 	{
// 		TlinsAstroBase ::tlinsCommunicationThreadRequest ::confirm();
// 	}

// 	virtual void operator()() noexcept
// 	{
// 		try {
// 			// Uruchomienie zapytania
// 			connection->getAstro()->setTracking(RA, DEC);
// 		}
// 		catch (tlinsInterfaceException &exc) {
// 			isError = true;
// 			TLINS_LOG_ERROR("Error: " + exc.getErrorMessage());
// 		}
// 		end.store(true);
// 		cv.notify_one();
// 	}

// 	virtual bool isAsynchronuus()
// 	{
// 		return false;
// 	}

// 	virtual std ::string name()
// 	{
// 		return "tlinsSetTarget";
// 	}

// 	TlinsTrackRate(const double ra_, const double dc_, std::condition_variable &cv_, std::atomic<bool> &end_,
// 	               std::atomic<bool> &isError_)
// 	    : RA{ra_}, DEC{dc_}, cv{cv_}, end{end_}, isError{isError_}
// 	{
// 		// Pobranie polaczenia
// 		if (!TlinsAstroBase ::tlinsConnectionsManager ::getInstance().hasConnection({TLINS_CONNECTION_DEFAULT}))
// 			__THROW__(
// 			    tlinsException(std ::string("No active connection: ") + std ::string(TLINS_CONNECTION_DEFAULT), -1));

// 		// Polaczenie
// 		connection = TlinsAstroBase ::tlinsConnectionsManager ::getInstance().getConnection(TLINS_CONNECTION_DEFAULT);
// 	}

// 	virtual ~TlinsTrackRate()
// 	{
// 		connection.reset();
// 	}
// };

// bool TlinsTelescope::SetTrackRate(double raRate, double dcRate)
// {
// 	std::condition_variable cv;
// 	std::mutex              mtx;
// 	std::atomic<bool>       end{false};
// 	std::atomic<bool>       isError{false};

// 	try {
// 		std ::unique_ptr<TlinsAstroBase ::tlinsCommunicationThreadRequest> req(
// 		    new TlinsTrackRate(raRate, dcRate, cv, end, isError));
// 		TlinsAstroBase ::tlinsCommunicationThread ::getInstance().push(req);

// 		// Oczekiwanbie na wqynik
// 		std::unique_lock<std::mutex> lock(mtx);
// 		cv.wait(lock, [&] { return end.load(); });
// 	}
// 	catch (tlinsException &exc) {
// 		TLINS_LOG_ERROR("Error: " + exc.getErrorMessage());
// 		return false;
// 	}
// 	if (isError) {
// 		return false;
// 	}

// 	return true;
// }

// //
// // --- Wlaczenie/wylaczenie sledzenia
// // -----------------------------------------------
// //
// class TlinsTrackEnable : public TlinsAstroBase ::tlinsCommunicationThreadRequest {
//   private:
// 	std ::shared_ptr<TlinsAstroBase ::tlinsConnectionContext> connection;
// 	std::condition_variable &                                 cv;
// 	std::atomic<bool> &                                       isError;
// 	std::atomic<bool> &                                       end;
// 	bool                                                      status;

//   public:
// 	void confirm()
// 	{
// 		TlinsAstroBase ::tlinsCommunicationThreadRequest ::confirm();
// 	}

// 	virtual void operator()() noexcept
// 	{
// 		try {
// 			// Uruchomienie zapytania
// 			connection->getAstro()->setTrackingState(status);
// 		}
// 		catch (tlinsInterfaceException &exc) {
// 			isError = true;
// 			TLINS_LOG_ERROR("Error: " + exc.getErrorMessage());
// 		}
// 		end.store(true);
// 		cv.notify_one();
// 	}

// 	virtual bool isAsynchronuus()
// 	{
// 		return false;
// 	}

// 	virtual std ::string name()
// 	{
// 		return "tlinsSetTarget";
// 	}

// 	TlinsTrackEnable(const bool status_, std::condition_variable &cv_, std::atomic<bool> &end_,
// 	                 std::atomic<bool> &isError_)
// 	    : status{status_}, cv{cv_}, end{end_}, isError{isError_}
// 	{
// 		// Pobranie polaczenia
// 		if (!TlinsAstroBase ::tlinsConnectionsManager ::getInstance().hasConnection({TLINS_CONNECTION_DEFAULT}))
// 			__THROW__(
// 			    tlinsException(std ::string("No active connection: ") + std ::string(TLINS_CONNECTION_DEFAULT), -1));

// 		// Polaczenie
// 		connection = TlinsAstroBase ::tlinsConnectionsManager ::getInstance().getConnection(TLINS_CONNECTION_DEFAULT);
// 	}

// 	virtual ~TlinsTrackEnable()
// 	{
// 		connection.reset();
// 	}
// };

// bool TlinsTelescope::SetTrackEnabled(bool enabled)
// {
// 	std::condition_variable cv;
// 	std::mutex              mtx;
// 	std::atomic<bool>       end{false};
// 	std::atomic<bool>       isError{false};

// 	try {
// 		std ::unique_ptr<TlinsAstroBase ::tlinsCommunicationThreadRequest> req(
// 		    new TlinsTrackEnable(enabled, cv, end, isError));
// 		TlinsAstroBase ::tlinsCommunicationThread ::getInstance().push(req);

// 		// Oczekiwanbie na wqynik
// 		std::unique_lock<std::mutex> lock(mtx);
// 		cv.wait(lock, [&] { return end.load(); });
// 	}
// 	catch (tlinsException &exc) {
// 		TLINS_LOG_ERROR("Error: " + exc.getErrorMessage());
// 		return false;
// 	}
// 	if (isError) {
// 		return false;
// 	}

// 	return true;
// }

// //
// // --- Zatrzymanie awaryjne
// // -----------------------------------------------
// //
// class tlinsMoveRequestProcesor : public TlinsAstroBase ::tlinsCommunicationThreadRequest {
//   private:
// 	class moveCb : public tlinsMoveServerInterface ::tlinsMoveRequestConfirmation {
// 	  private:
// 		tlinsMoveRequestProcesor &parent;

// 	  public:
// 		void process(const tlins ::tlinsRpcConfirmationStatus &status)
// 		{
// 			parent.confirm();
// 		}

// 		bool release()
// 		{
// 			return true;
// 		}

// 		moveCb(tlinsMoveRequestProcesor &parent_) : parent{parent_}
// 		{
// 		}

// 		virtual ~moveCb()
// 		{
// 		}
// 	};

// 	std ::shared_ptr<tlinsMoveServerInterface ::tlinsMoveRequestConfirmation> callback;
// 	std ::shared_ptr<TlinsAstroBase ::tlinsConnectionContext>                 connection;

//   private:
// 	std ::unique_ptr<tlinsMoveServerInterface ::MoveRequestDevice> request;

//   public:
// 	void confirm()
// 	{
// 		TlinsAstroBase ::tlinsCommunicationThreadRequest ::confirm();
// 	}

// 	virtual void operator()() noexcept
// 	{
// 		try {
// 			// Nazwa urzadzenia glownego
// 			std ::string mainDeviceName = "main";
// 			auto &       cfg            = TlinsAstroBase ::tlinsConfiguration ::getInstance();

// 			if (cfg.hasKey(TlinsAstroBase ::tlinsConfiguration ::COMMON_PARAMETER_GROUP,
// 			               TlinsAstroBase ::tlinsConfiguration ::COMMON_MAIN_DEVICE_NAME))
// 				mainDeviceName = cfg.getString(TlinsAstroBase ::tlinsConfiguration ::COMMON_PARAMETER_GROUP,
// 				                               TlinsAstroBase ::tlinsConfiguration ::COMMON_MAIN_DEVICE_NAME);

// 			// Uruchomienie zapytania
// 			connection->getDevice()->moveRequest(mainDeviceName, *request, callback);
// 		}
// 		catch (tlinsInterfaceException &) {
// 			// Mamy blad wywolania nie bedzie potwierdzenia asynchronicznego
// 			confirm();
// 			return;
// 		}
// 	}

// 	virtual bool isAsynchronuus()
// 	{
// 		return true;
// 	}

// 	virtual std ::string name()
// 	{
// 		return "tlinsPilotMoveRequest";
// 	}

// 	tlinsMoveRequestProcesor(std ::unique_ptr<tlinsMoveServerInterface ::MoveRequestDevice> &ptr)
// 	{
// 		// Pobranie polaczenia
// 		if (!TlinsAstroBase ::tlinsConnectionsManager ::getInstance().hasConnection({TLINS_CONNECTION_DEFAULT}))
// 			__THROW__(
// 			    tlinsException(std ::string("No active connection: ") + std ::string(TLINS_CONNECTION_DEFAULT), -1));

// 		// Polaczenie
// 		connection = TlinsAstroBase ::tlinsConnectionsManager ::getInstance().getConnection(TLINS_CONNECTION_DEFAULT);

// 		// Obiekt potwierdzen
// 		callback.reset(new moveCb{*this});
// 	}

// 	virtual ~tlinsMoveRequestProcesor()
// 	{
// 		connection.reset();
// 	}
// };

// bool TlinsTelescope::Abort()
// {
// 	bool isAstro           = false;
// 	bool isTrackingEnabled = false;

// 	// Okreslenie stanu kontrolera
// 	TlinsAstroBase ::tlinsAstroBase::getAstroStaetInfo(isAstro, isTrackingEnabled);

// 	// Tworzenie rzadania
// 	std ::unique_ptr<tlinsMoveServerInterface ::MoveRequestDevice> moveReqest;
// 	TlinsAstroBase ::tlinsAstroBase                                astroUtilObj;
// 	TlinsAstroBase ::tlinsAstroBase ::Mode                         mode_;

// 	if (isAstro) {
// 		mode_ = TlinsAstroBase ::tlinsAstroBase ::Mode ::ASTRO;
// 	} else {
// 		mode_ = TlinsAstroBase ::tlinsAstroBase ::Mode ::DEGRIS;
// 	}

// 	if (!astroUtilObj.createStopRequest(TlinsAstroBase ::tlinsAstroBase ::Axis ::AxisXY, mode_, moveReqest, true)) {
// 		return false;
// 	}

// 	try {
// 		std ::unique_ptr<TlinsAstroBase ::tlinsCommunicationThreadRequest> req(
// 		    new tlinsMoveRequestProcesor{moveReqest});
// 		TlinsAstroBase ::tlinsCommunicationThread ::getInstance().push(req, true);
// 	}
// 	catch (tlinsException &exc) {
// 		TLINS_LOG_ERROR("Error: " + exc.getErrorMessage());
// 		return false;
// 	}
// 	return true;
// }

// // @@@@@@@@@@@@@@@@@@@@@@@@@@@@
// // @@@@@@@@@@@@@@@@@@@@@@@@@@@@
// // @@@@@@@@@@@@@@@@@@@@@@@@@@@@

// //
// // ---
// //

// bool TlinsTelescope::Sync(double ra, double dec)
// {
// 	auto ret = Goto(ra, dec);
// 	if (ret) {
// 		NewRaDec(ra, dec);
// 	}
// 	return ret;
// }

// bool TlinsTelescope::Park()
// {
// 	// Nie wspierane
// 	return false;
// }

// bool TlinsTelescope::UnPark()
// {
// 	// Nie wspierane
// 	return false;
// }

// //
// // ---
// //

// bool TlinsTelescope::ISNewNumber(const char *dev, const char *name_, double values[], char *names[], int n)
// {
// 	// if (dev != nullptr && strcmp(dev, getDeviceName()) == 0) {
// 	// if (strcmp(name, "GUIDE_RATE") == 0)
// 	// {
// 	//     IUUpdateNumber(&GuideRateNP, values, names, n);
// 	//     GuideRateNP.s = IPS_OK;
// 	//     IDSetNumber(&GuideRateNP, nullptr);
// 	//     return true;
// 	// }

// 	// 	if (strcmp(name_, GuideNSNP.name) == 0 || strcmp(name_, GuideWENP.name) == 0) {
// 	// 		processGuiderProperties(name_, values, names, n);
// 	// 		return true;
// 	// 	}
// 	// }

// 	return INDI::Telescope::ISNewNumber(dev, name_, values, names, n);
// }

// //
// // ###############################################
// // ###############################################
// // ###############################################
// //

// // namespace tlins
// // {

// // bool TlinsTelescope::Connect()
// // {
// // 	std::condition_variable cv;
// // 	std::mutex              mtx;
// // 	std::atomic<bool>       end{false};


// // 	// Instancja polaczenia
// // 	auto &mgr = TlinsAstroBase ::tlinsConnectionsManager ::getInstance();

// // 	// Tworzenie polaczenia
// // 	try {
// // 		mgr.setConnection({TLINS_CONNECTION_DEFAULT}, urlDev.c_str(), urlDevAsync.c_str(), urlAstro.c_str());
// // 	}
// // 	catch (...) {
// // 		return false;
// // 	}
// // 	return false;
// // }

// // TlinsTelescope::TlinsTelescope()
// // {
// // }


// // bool TlinsTelescope::updateProperties()
// // {
// // }

// // bool TlinsTelescope::Handshake()
// // {
// // }

// // void TlinsTelescope::TimerHit()
// // {
// // }

// // bool TlinsTelescope::ISNewNumber(const char *dev, const char *name, double values[], char *names[], int n)
// // {
// // 	auto &cfgInstance = TlinsAstroBase ::tlinsConfiguration ::getInstance();

// // 	//
// // 	// Konfiguracja polaczenia
// // 	//
// // 	urlDev           = std::string{"localhost:20001"};
// // 	urlDevAsync      = std::string{"localhost:20003"};
// // 	urlAstro         = std::string{"localhost:20000"};
// // 	posElipsoideType = std::string{"WGS_84"};

// // 	if (cfgInstance.hasKey(TlinsAstroBase ::tlinsConfiguration ::CONNECTION_PARAMETER_GROUP,
// // 	                       TlinsAstroBase ::tlinsConfiguration ::CONNECTION_PARAMETER_URL_DEVICE_ENGINE))
// // 		urlDev = cfgInstance.getString(TlinsAstroBase ::tlinsConfiguration ::CONNECTION_PARAMETER_GROUP,
// // 		                               TlinsAstroBase ::tlinsConfiguration
// ::CONNECTION_PARAMETER_URL_DEVICE_ENGINE);

// // 	if (cfgInstance.hasKey(TlinsAstroBase ::tlinsConfiguration ::CONNECTION_PARAMETER_GROUP,
// // 	                       TlinsAstroBase ::tlinsConfiguration ::CONNECTION_PARAMETER_URL_DEVICE_ENGINE_ASYNCH))
// // 		urlDevAsync =
// // 		    cfgInstance.getString(TlinsAstroBase ::tlinsConfiguration ::CONNECTION_PARAMETER_GROUP,
// // 		                          TlinsAstroBase ::tlinsConfiguration
// ::CONNECTION_PARAMETER_URL_DEVICE_ENGINE_ASYNCH);

// // 	if (cfgInstance.hasKey(TlinsAstroBase ::tlinsConfiguration ::CONNECTION_PARAMETER_GROUP,
// // 	                       TlinsAstroBase ::tlinsConfiguration ::CONNECTION_PARAMETER_URL_ASTRO_ENGINE))
// // 		urlAstro = cfgInstance.getString(TlinsAstroBase ::tlinsConfiguration ::CONNECTION_PARAMETER_GROUP,
// // 		                                 TlinsAstroBase ::tlinsConfiguration
// ::CONNECTION_PARAMETER_URL_ASTRO_ENGINE);

// // 	//
// // 	// Parametery rampy
// // 	//
// // 	if (cfgInstance.hasKey(TlinsAstroBase ::tlinsConfiguration ::RAMP_PARAMETER_GROUP,
// // 	                       TlinsAstroBase ::tlinsConfiguration ::RAMP_PARAMETER_DEGRIS_X_A))
// // 		DEG_A_X = cfgInstance.getDouble(TlinsAstroBase ::tlinsConfiguration ::RAMP_PARAMETER_GROUP,
// // 		                                TlinsAstroBase ::tlinsConfiguration ::RAMP_PARAMETER_DEGRIS_X_A);
// // 	if (cfgInstance.hasKey(TlinsAstroBase ::tlinsConfiguration ::RAMP_PARAMETER_GROUP,
// // 	                       TlinsAstroBase ::tlinsConfiguration ::RAMP_PARAMETER_DEGRIS_X_D))
// // 		DEG_D_X = cfgInstance.getDouble(TlinsAstroBase ::tlinsConfiguration ::RAMP_PARAMETER_GROUP,
// // 		                                TlinsAstroBase ::tlinsConfiguration ::RAMP_PARAMETER_DEGRIS_X_D);
// // 	if (cfgInstance.hasKey(TlinsAstroBase ::tlinsConfiguration ::RAMP_PARAMETER_GROUP,
// // 	                       TlinsAstroBase ::tlinsConfiguration ::RAMP_PARAMETER_DEGRIS_X_V_MAX))
// // 		DEG_V_X = cfgInstance.getDouble(TlinsAstroBase ::tlinsConfiguration ::RAMP_PARAMETER_GROUP,
// // 		                                TlinsAstroBase ::tlinsConfiguration ::RAMP_PARAMETER_DEGRIS_X_V_MAX);

// // 	if (cfgInstance.hasKey(TlinsAstroBase ::tlinsConfiguration ::RAMP_PARAMETER_GROUP,
// // 	                       TlinsAstroBase ::tlinsConfiguration ::RAMP_PARAMETER_DEGRIS_Y_A))
// // 		DEG_A_Y = cfgInstance.getDouble(TlinsAstroBase ::tlinsConfiguration ::RAMP_PARAMETER_GROUP,
// // 		                                TlinsAstroBase ::tlinsConfiguration ::RAMP_PARAMETER_DEGRIS_Y_A);
// // 	if (cfgInstance.hasKey(TlinsAstroBase ::tlinsConfiguration ::RAMP_PARAMETER_GROUP,
// // 	                       TlinsAstroBase ::tlinsConfiguration ::RAMP_PARAMETER_DEGRIS_Y_D))
// // 		DEG_D_Y = cfgInstance.getDouble(TlinsAstroBase ::tlinsConfiguration ::RAMP_PARAMETER_GROUP,
// // 		                                TlinsAstroBase ::tlinsConfiguration ::RAMP_PARAMETER_DEGRIS_Y_D);
// // 	if (cfgInstance.hasKey(TlinsAstroBase ::tlinsConfiguration ::RAMP_PARAMETER_GROUP,
// // 	                       TlinsAstroBase ::tlinsConfiguration ::RAMP_PARAMETER_DEGRIS_Y_V_MAX))
// // 		DEG_V_Y = cfgInstance.getDouble(TlinsAstroBase ::tlinsConfiguration ::RAMP_PARAMETER_GROUP,
// // 		                                TlinsAstroBase ::tlinsConfiguration ::RAMP_PARAMETER_DEGRIS_Y_V_MAX);

// // 	if (cfgInstance.hasKey(TlinsAstroBase ::tlinsConfiguration ::RAMP_PARAMETER_GROUP,
// // 	                       TlinsAstroBase ::tlinsConfiguration ::RAMP_PARAMETER_ASTRO_RA_A))
// // 		ASTRO_A_RA = cfgInstance.getDouble(TlinsAstroBase ::tlinsConfiguration ::RAMP_PARAMETER_GROUP,
// // 		                                   TlinsAstroBase ::tlinsConfiguration ::RAMP_PARAMETER_ASTRO_RA_A);
// // 	if (cfgInstance.hasKey(TlinsAstroBase ::tlinsConfiguration ::RAMP_PARAMETER_GROUP,
// // 	                       TlinsAstroBase ::tlinsConfiguration ::RAMP_PARAMETER_ASTRO_RA_D))
// // 		ASTRO_D_RA = cfgInstance.getDouble(TlinsAstroBase ::tlinsConfiguration ::RAMP_PARAMETER_GROUP,
// // 		                                   TlinsAstroBase ::tlinsConfiguration ::RAMP_PARAMETER_ASTRO_RA_D);
// // 	if (cfgInstance.hasKey(TlinsAstroBase ::tlinsConfiguration ::RAMP_PARAMETER_GROUP,
// // 	                       TlinsAstroBase ::tlinsConfiguration ::RAMP_PARAMETER_ASTRO_RA_V_MAX))
// // 		ASTRO_V_RA = cfgInstance.getDouble(TlinsAstroBase ::tlinsConfiguration ::RAMP_PARAMETER_GROUP,
// // 		                                   TlinsAstroBase ::tlinsConfiguration ::RAMP_PARAMETER_ASTRO_RA_V_MAX);

// // 	if (cfgInstance.hasKey(TlinsAstroBase ::tlinsConfiguration ::RAMP_PARAMETER_GROUP,
// // 	                       TlinsAstroBase ::tlinsConfiguration ::RAMP_PARAMETER_ASTRO_DC_A))
// // 		ASTRO_A_DC = cfgInstance.getDouble(TlinsAstroBase ::tlinsConfiguration ::RAMP_PARAMETER_GROUP,
// // 		                                   TlinsAstroBase ::tlinsConfiguration ::RAMP_PARAMETER_ASTRO_DC_A);
// // 	if (cfgInstance.hasKey(TlinsAstroBase ::tlinsConfiguration ::RAMP_PARAMETER_GROUP,
// // 	                       TlinsAstroBase ::tlinsConfiguration ::RAMP_PARAMETER_ASTRO_DC_D))
// // 		ASTRO_D_DC = cfgInstance.getDouble(TlinsAstroBase ::tlinsConfiguration ::RAMP_PARAMETER_GROUP,
// // 		                                   TlinsAstroBase ::tlinsConfiguration ::RAMP_PARAMETER_ASTRO_DC_D);
// // 	if (cfgInstance.hasKey(TlinsAstroBase ::tlinsConfiguration ::RAMP_PARAMETER_GROUP,
// // 	                       TlinsAstroBase ::tlinsConfiguration ::RAMP_PARAMETER_ASTRO_DC_V_MAX))
// // 		ASTRO_V_DC = cfgInstance.getDouble(TlinsAstroBase ::tlinsConfiguration ::RAMP_PARAMETER_GROUP,
// // 		                                   TlinsAstroBase ::tlinsConfiguration ::RAMP_PARAMETER_ASTRO_DC_V_MAX);

// // 	if (cfgInstance.hasKey(TlinsAstroBase ::tlinsConfiguration ::RAMP_PARAMETER_GROUP,
// // 	                       TlinsAstroBase ::tlinsConfiguration ::RAMP_PARAMETER_GUIDING_RA_A))
// // 		GUIDER_A_RA = cfgInstance.getDouble(TlinsAstroBase ::tlinsConfiguration ::RAMP_PARAMETER_GROUP,
// // 		                                    TlinsAstroBase ::tlinsConfiguration ::RAMP_PARAMETER_GUIDING_RA_A);
// // 	if (cfgInstance.hasKey(TlinsAstroBase ::tlinsConfiguration ::RAMP_PARAMETER_GROUP,
// // 	                       TlinsAstroBase ::tlinsConfiguration ::RAMP_PARAMETER_GUIDING_RA_D))
// // 		GUIDER_D_RA = cfgInstance.getDouble(TlinsAstroBase ::tlinsConfiguration ::RAMP_PARAMETER_GROUP,
// // 		                                    TlinsAstroBase ::tlinsConfiguration ::RAMP_PARAMETER_GUIDING_RA_D);
// // 	if (cfgInstance.hasKey(TlinsAstroBase ::tlinsConfiguration ::RAMP_PARAMETER_GROUP,
// // 	                       TlinsAstroBase ::tlinsConfiguration ::RAMP_PARAMETER_GUIDING_RA_V_MAX))
// // 		GUIDER_V_RA = cfgInstance.getDouble(TlinsAstroBase ::tlinsConfiguration ::RAMP_PARAMETER_GROUP,
// // 		                                    TlinsAstroBase ::tlinsConfiguration ::RAMP_PARAMETER_GUIDING_RA_V_MAX);

// // 	if (cfgInstance.hasKey(TlinsAstroBase ::tlinsConfiguration ::RAMP_PARAMETER_GROUP,
// // 	                       TlinsAstroBase ::tlinsConfiguration ::RAMP_PARAMETER_GUIDING_DC_A))
// // 		GUIDER_A_DC = cfgInstance.getDouble(TlinsAstroBase ::tlinsConfiguration ::RAMP_PARAMETER_GROUP,
// // 		                                    TlinsAstroBase ::tlinsConfiguration ::RAMP_PARAMETER_GUIDING_DC_A);
// // 	if (cfgInstance.hasKey(TlinsAstroBase ::tlinsConfiguration ::RAMP_PARAMETER_GROUP,
// // 	                       TlinsAstroBase ::tlinsConfiguration ::RAMP_PARAMETER_GUIDING_DC_D))
// // 		GUIDER_D_DC = cfgInstance.getDouble(TlinsAstroBase ::tlinsConfiguration ::RAMP_PARAMETER_GROUP,
// // 		                                    TlinsAstroBase ::tlinsConfiguration ::RAMP_PARAMETER_GUIDING_DC_D);
// // 	if (cfgInstance.hasKey(TlinsAstroBase ::tlinsConfiguration ::RAMP_PARAMETER_GROUP,
// // 	                       TlinsAstroBase ::tlinsConfiguration ::RAMP_PARAMETER_GUIDING_DC_V_MAX))
// // 		GUIDER_V_DC = cfgInstance.getDouble(TlinsAstroBase ::tlinsConfiguration ::RAMP_PARAMETER_GROUP,
// // 		                                    TlinsAstroBase ::tlinsConfiguration ::RAMP_PARAMETER_GUIDING_DC_V_MAX);
// // }

// bool TlinsTelescope::ISNewText(const char *dev, const char *name_, char *texts[], char *names[], int n)
// {
// 	return true;
// 	// std::string name{name_};
// 	// std::string value{};
// 	// bool        connChcnage = false;
// 	// bool        exists      = false;

// 	// if (n <= 0)
// 	// 	return false;

// 	// // Parametery polaczenia
// 	// if (name == TlinsAstroBase ::tlinsConfiguration ::CONNECTION_PARAMETER_URL_DEVICE_ENGINE) {
// 	// 	urlDev      = texts[0] != nullptr ? texts[0] : urlDev;
// 	// 	connChcnage = true;
// 	// 	exists      = true;
// 	// }

// 	// if (name == TlinsAstroBase ::tlinsConfiguration ::CONNECTION_PARAMETER_URL_DEVICE_ENGINE_ASYNCH) {
// 	// 	urlDevAsync = texts[0] != nullptr ? texts[0] : urlDevAsync;
// 	// 	connChcnage = true;
// 	// 	exists      = true;
// 	// }

// 	// if (name == TlinsAstroBase ::tlinsConfiguration ::CONNECTION_PARAMETER_URL_ASTRO_ENGINE) {
// 	// 	urlAstro    = texts[0] != nullptr ? texts[0] : urlAstro;
// 	// 	connChcnage = true;
// 	// 	exists      = true;
// 	// }

// 	// 	if (connChcnage) {
// 	// 		// Modyfikacja polaczenia
// 	// 		try {
// 	// 			auto &mgr = TlinsAstroBase ::tlinsConnectionsManager ::getInstance();
// 	// 			mgr.setConnection({TLINS_CONNECTION_DEFAULT}, urlDev.c_str(), urlDevAsync.c_str(), urlAstro.c_str());
// 	// 		}
// 	// 		catch (...) {
// 	// 			return false;
// 	// 		}
// 	// 	}

// 	// 	if (name == "POS_ELIPSOIDE") {
// 	// 		posElipsoideType = texts[0] != nullptr ? texts[0] : posElipsoideType;
// 	// 		exists           = true;
// 	// 	}
// 	// 	return exists;
// }

// bool TlinsTelescope::ISNewSwitch(const char *dev, const char *name, ISState *states, char *names[], int n)
// {
// 	return false;
// }

// // void TlinsTelescope::ISGetProperties(const char *dev)
// // {
// // }

// // bool TlinsTelescope::ISSnoopDevice(XMLEle *root)
// // {
// // }

// // bool TlinsTelescope::saveConfigItems(FILE *fp)
// // {
// // }

// // //
// // // --- GOTO - end ---
// // //

// // bool TlinsTelescope::Sync(double ra, double dec)
// // {
// // }

// bool TlinsTelescope::MoveNS(INDI_DIR_NS dir, TelescopeMotionCommand command)
// {
// }

// bool TlinsTelescope::MoveWE(INDI_DIR_WE dir, TelescopeMotionCommand command)
// {
// }

// bool TlinsTelescope::SetTrackMode(uint8_t mode)
// {
// }

// // int TlinsTelescope::AddTrackMode(const char *name, const char *label, bool isDefault)
// // {
// // }

// // bool TlinsTelescope::SetTrackEnabled(bool enabled)
// // {
// // }

// // bool TlinsTelescope::updateTime(ln_date *utc, double utc_offset)
// // {
// // }

// // bool TlinsTelescope::updateLocation(double latitude, double longitude, double elevation)
// // {
// // }

// // bool TlinsTelescope::SetParkPosition(double Axis1Value, double Axis2Value)
// // {
// // }

// bool TlinsTelescope::SetCurrentPark()
// {
// }

// bool TlinsTelescope::SetDefaultPark()
// {
// }

// IPState TlinsTelescope::GuideNorth(uint32_t ms)
// {
// }

// IPState TlinsTelescope::GuideSouth(uint32_t ms)
// {
// }

// IPState TlinsTelescope::GuideEast(uint32_t ms)
// {
// }

// IPState TlinsTelescope::GuideWest(uint32_t ms)
// {
// }


// // bool TlinsTelescope::SetSlewRate(int index)
// // {
// // }

// // }; // namespace tlins

static std::unique_ptr<TlinsTelescope> simpleDevice{new TlinsTelescope()};

void ISGetProperties(const char *dev)
{
	simpleDevice->ISGetProperties(dev);
}
/**************************************************************************************
** Process new switch from client
***************************************************************************************/
void ISNewSwitch(const char *dev, const char *name, ISState *states, char *names[], int n)
{
	simpleDevice->ISNewSwitch(dev, name, states, names, n);
}
/**************************************************************************************
** Process new text from client
***************************************************************************************/
void ISNewText(const char *dev, const char *name, char *texts[], char *names[], int n)
{
	simpleDevice->ISNewText(dev, name, texts, names, n);
}
/**************************************************************************************
** Process new number from client
***************************************************************************************/
void ISNewNumber(const char *dev, const char *name, double values[], char *names[], int n)
{
	simpleDevice->ISNewNumber(dev, name, values, names, n);
}
/**************************************************************************************
** Process new blob from client
***************************************************************************************/
void ISNewBLOB(const char *dev, const char *name, int sizes[], int blobsizes[], char *blobs[], char *formats[],
               char *names[], int n)
{
	simpleDevice->ISNewBLOB(dev, name, sizes, blobsizes, blobs, formats, names, n);
}
/**************************************************************************************
** Process snooped property from another driver
***************************************************************************************/
void ISSnoopDevice(XMLEle *root)
{
	INDI_UNUSED(root);
}