#include "tlins_driver.hpp"

#include <tlinsBacktrace.hpp>
#include <tlinsException.hpp>
#include <tlinsMoveServerInterface.hpp>
#include <tlinsastrouibase.h>
#include <tlinscommunicationthread.h>
#include <tlinsconfiguration.h>

#include <astro.pb.h>
#include <string>
#include <tlinsLogger.hpp>

#include <memory>

#undef LOG_ERROR
#include <tlinsLogger.hpp>


#define RA_AXIS     0
#define DEC_AXIS    1


std::string TlinsTelescope::STR_GUIDE_RATE = "GUIDE_RATE";
std::string TlinsTelescope::STR_MANUAL_CORRECTION_RATE = "MANUAL_CORRECTION_RATE";
std::string TlinsTelescope::STR_MOUNT_MODE = "MOUNT_MODE";
std::string TlinsTelescope::STR_TRACKING_STATE = "TRACKING_STATE";


//
// +++
//
TlinsTelescope::TlinsTelescope()
{
	DBG_SCOPE = static_cast<uint32_t>(INDI::Logger::getInstance().addDebugLevel("Scope Verbose", "SCOPE"));

	SetTelescopeCapability(	TELESCOPE_CAN_ABORT     | TELESCOPE_CAN_GOTO          | /*TELESCOPE_CAN_PARK |*/
							TELESCOPE_CAN_SYNC      | TELESCOPE_HAS_TIME          | TELESCOPE_HAS_LOCATION |
							TELESCOPE_HAS_PIER_SIDE | TELESCOPE_CAN_CONTROL_TRACK | TELESCOPE_HAS_TRACK_MODE, 4);
}

//
// +++
//
const char *TlinsTelescope::getDefaultName()
{
	return "Tlins mount";
}


//
// +++
//
bool TlinsTelescope::initProperties()
{
	// We must ALWAYS init the properties of the parent class first
	INDI::Telescope::initProperties();

	// DefaultDevice::initProperties();
	
	SetTelescopeCapability(
		TELESCOPE_CAN_ABORT |
		TELESCOPE_CAN_GOTO |
		/*TELESCOPE_CAN_PARK |*/
		TELESCOPE_CAN_SYNC |
	    TELESCOPE_HAS_TIME |
		TELESCOPE_HAS_LOCATION |
		TELESCOPE_HAS_PIER_SIDE |
		TELESCOPE_CAN_CONTROL_TRACK |
		TELESCOPE_HAS_TRACK_MODE,
	                       4);

	//
	// Guider - konfiguracja
	//
    IUFillNumber(&GuideRate[RA_AXIS], "GUIDER_RATE_RA", "RA Rate", "%g", 0, 1, 0.1, 0.5);
    IUFillNumber(&GuideRate[DEC_AXIS], "GUIDER_RATE_DEC", "DEC Rate", "%g", 0, 1, 0.1, 0.5);
    IUFillNumberVector(	&GuideRateNP, GuideRate, 2, getDeviceName(), TlinsTelescope::STR_GUIDE_RATE.c_str(), "Guiding Rate", GUIDE_TAB, IP_RW, 0, IPS_IDLE);

	//
	// Manualne korekty
	//
    IUFillNumber(&ManualCorrectionsRate[RA_AXIS], "MANUAL_CORRECTION_RA", "RA correction", "%g", 0, 1, 0.1, 0.0);
    IUFillNumber(&ManualCorrectionsRate[DEC_AXIS], "MANUAL_CORRECTION_DEC", "DEC correction", "%g", 0, 1, 0.1, 0.0);
    IUFillNumberVector(	&ManualCorrectionsRateNP, ManualCorrectionsRate, 2, getDeviceName(), "MANUAL_CORRECTION_RATE", "Manual corrections", GUIDE_TAB, IP_RW, 0, IPS_IDLE);

	//
	// Sposób sledzenia
	//
    IUFillSwitch(&Mode[MountMode::STANDARD], "MODE_STANDARD", "Standard and manual corrections mode", ISS_ON);
	IUFillSwitch(&Mode[MountMode::STEPS], "MODE_STEPS", "Step mode", ISS_OFF);
    IUFillSwitch(&Mode[MountMode::GUIDER], "MODE_GUIDER", "Guider mode", ISS_OFF);
    IUFillSwitchVector(&ModeSP, Mode, 3, getDeviceName(), TlinsTelescope::STR_MOUNT_MODE.c_str(), "Mount mode", MOTION_TAB, IP_RW, ISR_1OFMANY, 60, IPS_IDLE );

	//
	// Wlaczenie/wylaczenie sledzenia
	//
    IUFillSwitch(&TrackingState[TrackingCase::START], "TRACKING_START", "Tracking start", ISS_OFF);
    IUFillSwitch(&TrackingState[TrackingCase::STOP], "TRACKING_STOP", "Tracking stop", ISS_ON);
    IUFillSwitchVector(&TrackingStateSP, TrackingState, 2, getDeviceName(), "TRACKING_STATE", "Tracking state", MOTION_TAB, IP_RW, ISR_1OFMANY, 60, IPS_IDLE );

	//
	// Parametery polaczenia sieciowego
	//
    IUFillNumber(&CommunicationPorts[ASTRO],          "Astro engine port",        "Astro engine port",        "%g", 20000, 64000, 1, 20000);
    IUFillNumber(&CommunicationPorts[ASTRO_ASYNC],    "Astro engine async port",  "Astro engine async port",  "%g", 20000, 64000, 1, 20002);
	IUFillNumber(&CommunicationPorts[DEVICE_PORT],    "Device engine port",       "Device engine port",       "%g", 20000, 64000, 1, 20001);
	IUFillNumber(&CommunicationPorts[DEVICE_ASYNC],   "Device engine async port", "Device engine async port", "%g", 20000, 64000, 1, 20003);
	IUFillNumber(&CommunicationPorts[SYSTEM_SERVICE], "Systemservice",            "Systemservice",            "%g", 20000, 64000, 1, 20100);
    IUFillNumberVector(	&CommunicationPortsNP, CommunicationPorts, 5, getDeviceName(), "COMMUNICATION_PORTS", "Ports", CONNECTION_TAB, IP_RW, 0, IPS_IDLE);
	defineProperty(&CommunicationPortsNP);

	IUFillText(&ipAddress, "Address ip", "Address ip", "192.168.100");
	IUFillTextVector(&ipAddressSP, &ipAddress, 1, getDeviceName(), "IP_ADDRESS", "Address", CONNECTION_TAB, IP_RW, 60, IPS_IDLE);
	defineProperty(&ipAddressSP);

	return true;
}

//
// TODO/+++
//
bool TlinsTelescope::ReadScopeStatus()
{
	DEBUG(INDI::Logger::DBG_SESSION, "TLINS device - TlinsTelescope::ReadScopeStatus()");

	if (!isConnected())
        return false;

	return true;
}

bool TlinsTelescope::getDeviceState(tlinsAstroEngineInterface::tlinsCalibrarionStateInfo &calibrarionState)
{
	// Polaczenie
	auto connection = getConnection();
	if (!connection) {
		DEBUG(INDI::Logger::DBG_ERROR, "No active connection");
		return false;
	}

	try {
		// Stan kalibracji
		connection->getAstro()->getCalibrationState(calibrarionState);
	}
	catch (tlinsInterfaceException &exc) {
		DEBUG(INDI::Logger::DBG_ERROR, (std::string{"Error id : "} + std::to_string(exc.getErrorID()) +
		                                std::string{"Error message : "} + exc.getErrorMessage())
		                                   .c_str());
		return false;
	}
	return true;
}

std::shared_ptr<TlinsAstroBase::tlinsConnectionContext> TlinsTelescope::getConnection()
{
	if (!TlinsAstroBase::tlinsConnectionsManager::getInstance().hasConnection(std::string{TLINS_CONNECTION_DEFAULT})) {
		DEBUG(INDI::Logger::DBG_ERROR, "No active connection");
		return std::shared_ptr<TlinsAstroBase::tlinsConnectionContext>(nullptr);
	}
	return TlinsAstroBase::tlinsConnectionsManager::getInstance().getConnection(TLINS_CONNECTION_DEFAULT);
}

IPState TlinsTelescope::__guder_process_request(std::function<tlinsAstroEngineInterface::GuiderStatus()> fun)
{
	try {
		switch(fun())
		{
		case tlinsAstroEngineInterface::GuiderStatus::IN_PROGRESS:
			return IPState::IPS_BUSY;

		case tlinsAstroEngineInterface::GuiderStatus::NO_TARGET:
		case tlinsAstroEngineInterface::GuiderStatus::ERROR:
			return IPState::IPS_BUSY ;

		case tlinsAstroEngineInterface::GuiderStatus::SET:
		return IPState::IPS_OK;
		}
	}
	catch(tlinsInterfaceException &exc) {
		auto reportErrMessage = exc.reportErrorMessage();
		auto erroMessage = exc.reportErrorMessage();
		auto errCode = exc.getErrorID();

		std::string msg = "ERROR = " + std::to_string(errCode) + "Report error message: " + reportErrMessage + "; Error message: " + erroMessage;
		DEBUG(INDI::Logger::DBG_ERROR, msg.c_str());
	}
	return IPState::IPS_ALERT;
}

/*
 * ---------------------------------------------------
 * Guiding - polnoc
 * ---------------------------------------------------
 */
IPState TlinsTelescope::GuideNorth(uint32_t ms)
{
	DEBUG(INDI::Logger::DBG_SESSION, "TLINS device - TlinsTelescope::GuideNorth()");

	// Polaczenie
	auto connection = getConnection();
	if (!connection) {
		DEBUG(INDI::Logger::DBG_ERROR, "No active connection");
		return IPState::IPS_OK;
	}

	// Weryfikacja statusu urzadzenia
	tlinsAstroEngineInterface::tlinsCalibrarionStateInfo calibrarionState;
	if (!getDeviceState(calibrarionState) ||
	    calibrarionState.get_engineState() != tlinsAstroEngineInterface::tlinsEngineStateValue::STATE_REGULAR) {
		TLINS_LOG_ERROR("Calibration has not been complted.");
		return IPState::IPS_ALERT;
	}

	return __guder_process_request([ms, connection]() {
		return connection -> getAstro() -> guideNorth(ms);
	});
}

/*
 * ---------------------------------------------------
 * Guiding - poludnie
 * ---------------------------------------------------
 */
IPState TlinsTelescope::GuideSouth(uint32_t ms)
{
	DEBUG(INDI::Logger::DBG_SESSION, "TLINS device - TlinsTelescope::GuideSouth()");

	// Polaczenie
	auto connection = getConnection();
	if (!connection) {
		DEBUG(INDI::Logger::DBG_ERROR, "No active connection");
		return IPState::IPS_OK;
	}

	// Weryfikacja statusu urzadzenia
	tlinsAstroEngineInterface::tlinsCalibrarionStateInfo calibrarionState;
	if (!getDeviceState(calibrarionState) ||
	    calibrarionState.get_engineState() != tlinsAstroEngineInterface::tlinsEngineStateValue::STATE_REGULAR) {
		TLINS_LOG_ERROR("Calibration has not been complted.");
		return IPState::IPS_ALERT;
	}

	return __guder_process_request([ms, connection]() {
		return connection -> getAstro() -> guideSounth(ms);
	});
}

/*
 * ---------------------------------------------------
 * Guiding - wschod
 * ---------------------------------------------------
 * */
IPState TlinsTelescope::GuideEast(uint32_t ms)
{
	DEBUG(INDI::Logger::DBG_SESSION, "TLINS device - TlinsTelescope::GuideEast()");

	// Polaczenie
	auto connection = getConnection();
	if (!connection) {
		DEBUG(INDI::Logger::DBG_ERROR, "No active connection");
		return IPState::IPS_OK;
	}

	// Weryfikacja statusu urzadzenia
	tlinsAstroEngineInterface::tlinsCalibrarionStateInfo calibrarionState;
	if (!getDeviceState(calibrarionState) ||
	    calibrarionState.get_engineState() != tlinsAstroEngineInterface::tlinsEngineStateValue::STATE_REGULAR) {
		TLINS_LOG_ERROR("Calibration has not been complted.");
		return IPState::IPS_ALERT;
	}

	return __guder_process_request([ms, connection]() {
		return connection -> getAstro() -> guideEst(ms);
	});
}

/*
 * ---------------------------------------------------
 * Guiding - zachod
 * ---------------------------------------------------
 */
IPState TlinsTelescope::GuideWest(uint32_t ms)
{
	DEBUG(INDI::Logger::DBG_SESSION, "TLINS device - TlinsTelescope::GuideWest()");

	// Polaczenie
	auto connection = getConnection();
	if (!connection) {
		DEBUG(INDI::Logger::DBG_ERROR, "No active connection");
		return IPState::IPS_OK;
	}

	// Weryfikacja statusu urzadzenia
	tlinsAstroEngineInterface::tlinsCalibrarionStateInfo calibrarionState;
	if (!getDeviceState(calibrarionState) ||
	    calibrarionState.get_engineState() != tlinsAstroEngineInterface::tlinsEngineStateValue::STATE_REGULAR) {
		TLINS_LOG_ERROR("Calibration has not been complted.");
		return IPState::IPS_ALERT;
	}

	return __guder_process_request([ms, connection]() {
		return connection -> getAstro() -> guideWest(ms);
	});
}

void GuideComplete(INDI_EQ_AXIS axis)
{
}

/*
 * ---------------------------------------------------
 * GOTO
 * ---------------------------------------------------
 */
//
// +++
//
bool TlinsTelescope::Goto(double ra, double dc)
{
	DEBUG(INDI::Logger::DBG_SESSION, "TLINS device - TlinsTelescope::Goto()");

	// Polaczenie
	auto connection = getConnection();
	if (!connection) {
		DEBUG(INDI::Logger::DBG_ERROR, "No active connection");
		return false;
	}

	// Weryfikacja statusu urzadzenia
	tlinsAstroEngineInterface::tlinsCalibrarionStateInfo calibrarionState;
	if (!getDeviceState(calibrarionState) ||
	    calibrarionState.get_engineState() != tlinsAstroEngineInterface::tlinsEngineStateValue::STATE_REGULAR) {
		TLINS_LOG_ERROR("Calibration has not been complted.");
		return false;
	}

	// Odczyt konfiguracji - parametery rampy
	auto &cfgInst = TlinsAstroBase::tlinsConfiguration::getInstance();

	double raA{100.0};
	if (cfgInst.hasKey(TlinsAstroBase::tlinsConfiguration::RAMP_PARAMETER_GROUP,
	                   TlinsAstroBase::tlinsConfiguration::RAMP_PARAMETER_ASTRO_RA_A)) {
		raA = cfgInst.getDouble(TlinsAstroBase::tlinsConfiguration::RAMP_PARAMETER_GROUP,
		                        TlinsAstroBase::tlinsConfiguration::RAMP_PARAMETER_ASTRO_RA_A);
	}

	double vMaxRa{100.0};
	if (cfgInst.hasKey(TlinsAstroBase::tlinsConfiguration::RAMP_PARAMETER_GROUP,
	                   TlinsAstroBase::tlinsConfiguration::RAMP_PARAMETER_ASTRO_RA_V_MAX)) {
		vMaxRa = cfgInst.getDouble(TlinsAstroBase::tlinsConfiguration::RAMP_PARAMETER_GROUP,
		                           TlinsAstroBase::tlinsConfiguration::RAMP_PARAMETER_ASTRO_RA_V_MAX);
	}

	// Tworzenie rzadania
	tlinsAstroEngineInterface::tlinsTarget reqData;
	reqData.set_aceleration(raA);
	reqData.set_speed(vMaxRa);
	reqData.set_delta(0.0);

	tlinsAstroEngineInterface::tlinsAstroObject astroObject;
	astroObject.set_properMotionRA(0.0);
	astroObject.set_properMotionDC(0.0);
	astroObject.set_parallax(0.0);
	astroObject.set_radialVelocity(0.0);
	astroObject.set_catalogType({""}); // TODO - potenciualnie

	tlinsAstroEngineInterface::tlinsCoordinate ra_;
	{
		int    h;
		int    m;
		double s;
		bool   sign;
		TlinsAstroBase::tlinsAstroBaseUtils::splitRA(ra, h, m, s, sign);
		ra_.set_degris(h);
		ra_.set_minutes(m);
		ra_.set_seconds(s);
		ra_.set_sign(sign);
	}

	tlinsAstroEngineInterface::tlinsCoordinate dc_;
	{
		int    d;
		int    m;
		double s;
		bool   sign;
		TlinsAstroBase::tlinsAstroBaseUtils::splitDegris(dc, d, m, s, sign);
		dc_.set_degris(d);
		dc_.set_minutes(m);
		dc_.set_seconds(s);
		dc_.set_sign(sign);
	}

	astroObject.set_hourAngle(ra_);
	astroObject.set_declination(dc_);
	reqData.set_object(astroObject);

	// Wstawienie rzadania
	try {
		// Ustawienie nowego celu
		connection->getAstro()->setTarget(reqData, false);

		// Wznowienie sledzenia - ktore zostalo zatrzymane po pobraniu stanu urzadzenia
		// connection->getAstro()->startTracking();
	}
	catch (tlinsInterfaceException &exc) {
		DEBUG(INDI::Logger::DBG_ERROR,
		      (std::string{"Error set target position. Error"} + exc.getErrorMessage()).c_str());
		return false;
	}
	DEBUG(INDI::Logger::DBG_SESSION, "TLINS device - TlinsTelescope::Goto() - target has been set.");
	return true;
}

class MoveRequestConfirmationDummy : public tlinsMoveServerInterface::tlinsMoveRequestConfirmation {
  public:
	void         process(const tlins::tlinsRpcConfirmationStatus &){};
	virtual bool release(){};

	MoveRequestConfirmationDummy()          = default;
	virtual ~MoveRequestConfirmationDummy() = default;
};

static std::shared_ptr<tlinsMoveServerInterface::tlinsMoveRequestConfirmation> moveReqCallback{
    new MoveRequestConfirmationDummy{}};

static std::string getMainDeviceName()
{
	std::string mainDeviceName = "main";
	auto &      cfg            = TlinsAstroBase::tlinsConfiguration::getInstance();

	if (cfg.hasKey(TlinsAstroBase::tlinsConfiguration::COMMON_PARAMETER_GROUP,
	               TlinsAstroBase::tlinsConfiguration::COMMON_MAIN_DEVICE_NAME))
		mainDeviceName = cfg.getString(TlinsAstroBase::tlinsConfiguration::COMMON_PARAMETER_GROUP,
		                               TlinsAstroBase::tlinsConfiguration::COMMON_MAIN_DEVICE_NAME);

	return mainDeviceName;
}

/*
 * ---------------------------------------------------
 * Awaryjne zatrzymanie
 * ---------------------------------------------------
 * */
bool TlinsTelescope::Abort()
{
	DEBUG(INDI::Logger::DBG_SESSION, "TLINS device - TlinsTelescope::Abort()");

	tlinsAstroEngineInterface::tlinsCalibrarionStateInfo calibrarionState;
	if (!getDeviceState(calibrarionState)) {
		return false;
	}

	bool isAstro{false};
	if (calibrarionState.get_engineState() == tlinsAstroEngineInterface::tlinsEngineStateValue::STATE_REGULAR) {
		isAstro = true;
	}

	std::unique_ptr<tlinsMoveServerInterface::MoveRequestDevice> moveReq;
	TlinsAstroBase::tlinsAstroBase                               astroBase{};

	TlinsAstroBase::tlinsAstroBase::Mode mode =
	    isAstro ? TlinsAstroBase::tlinsAstroBase::Mode::ASTRO : TlinsAstroBase::tlinsAstroBase::Mode::DEGRIS;

	astroBase.createStopRequest(TlinsAstroBase::tlinsAstroBase::Axis::AxisXY, mode, moveReq, true);

	//
	// 1. Pobranie polaczenia
	if (!TlinsAstroBase::tlinsConnectionsManager::getInstance().hasConnection(std::string{TLINS_CONNECTION_DEFAULT})) {
		DEBUG(INDI::Logger::DBG_ERROR, "No active connection");
		return false;
	}
	auto connection = TlinsAstroBase::tlinsConnectionsManager::getInstance().getConnection(TLINS_CONNECTION_DEFAULT);

	// Zatrzymanie sledzenia
	connection->getAstro()->stopTracking();

	// Awaryjne zatrzymanie kontrolera osi
	connection->getDevice()->moveRequest(getMainDeviceName(), *moveReq, moveReqCallback);
	return true;
}

/*
 * ---------------------------------------------------
 * Synchronizacja pozycji
 * ---------------------------------------------------
 */
//
// +++
//
bool TlinsTelescope::Sync(double ra, double dec)
{
	DEBUG(INDI::Logger::DBG_SESSION, "TLINS device - TlinsTelescope::Sync()");

	// Polaczenie
	auto connection = getConnection();
	if (!connection) {
		DEBUG(INDI::Logger::DBG_ERROR, "No active connection");
		return false;
	}

	// Weryfikacja statusu urzadzenia
	tlinsAstroEngineInterface::tlinsCalibrarionStateInfo calibrarionState;
	if (!getDeviceState(calibrarionState) ||
	    calibrarionState.get_engineState() != tlinsAstroEngineInterface::tlinsEngineStateValue::STATE_REGULAR) {
		TLINS_LOG_ERROR("Calibration has not been complted.");
		return false;
	}

	try {
		connection -> getAstro() -> sync(ra, dec);
		return true;
	}
	catch(tlinsInterfaceException &exc) {
		auto reportErrMessage = exc.reportErrorMessage();
		auto erroMessage = exc.reportErrorMessage();
		auto errCode = exc.getErrorID();

		std::string msg = "ERROR = " + std::to_string(errCode) + "Report error message: " + reportErrMessage + "; Error message: " + erroMessage;
		DEBUG(INDI::Logger::DBG_ERROR, msg.c_str());
	}
	return false;
}

/*
 * ---------------------------------------------------
 * Nawiazanie polaczenia z urzadzeniem
 * ---------------------------------------------------
 */
//
// ++
//
bool TlinsTelescope::Connect()
{
	// TODO
	// TODO - trzeba uwzglednic parametery przeslane z INDI
	// TODO

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
	DEBUG(INDI::Logger::DBG_SESSION, "TLINS device connected successfully!");
	return true;
}

/*
 * ---------------------------------------------------
 * Odlaczenie od kontrolera
 * ---------------------------------------------------
 */
//
// +++
//
bool TlinsTelescope::Disconnect()
{
	TlinsAstroBase::tlinsConnectionsManager::getInstance().removeConnection({TLINS_CONNECTION_DEFAULT});
	DEBUG(INDI::Logger::DBG_SESSION, "TLINS device disconnected successfully!");
	return true;
}

//
// ++
//
bool TlinsTelescope::updateProperties()
{
	// We must ALWAYS call the parent class updateProperties() first
	// DefaultDevice::updateProperties();
	INDI::Telescope::updateProperties();

	// If we are connected, we define the property to the client.
	if (isConnected()) {
		defineProperty(&GuideRateNP);
		defineProperty(&ManualCorrectionsRateNP);
		defineProperty(&ModeSP);
		defineProperty(&TrackingStateSP);
	} else {
        deleteProperty(GuideRateNP.name);
		deleteProperty(ManualCorrectionsRateNP.name);
		deleteProperty(ModeSP.name);
		deleteProperty(TrackingStateSP.name);
	}

	return true;
}


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
// 				double h =
// static_cast<double>(stateInfo.get_currentTarget().get_object().get_hourAngle().get_degris()); double m =
// static_cast<double>(stateInfo.get_currentTarget().get_object().get_hourAngle().get_minutes()); double s =
// static_cast<double>(stateInfo.get_currentTarget().get_object().get_hourAngle().get_seconds()); 				double
// hh
// =
// h
// + m / 60.0 + s / 3600.0; 				state.setRA(hh);
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
// 			    tlinsException(std ::string("No active connection: ") + std ::string(TLINS_CONNECTION_DEFAULT),
// -1));

// 		// Polaczenie
// 		connection = TlinsAstroBase ::tlinsConnectionsManager
// ::getInstance().getConnection(TLINS_CONNECTION_DEFAULT);
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
// 			    tlinsException(std ::string("No active connection: ") + std ::string(TLINS_CONNECTION_DEFAULT),
// -1));

// 		// Polaczenie
// 		connection = TlinsAstroBase ::tlinsConnectionsManager
// ::getInstance().getConnection(TLINS_CONNECTION_DEFAULT);
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
// 			    tlinsException(std ::string("No active connection: ") + std ::string(TLINS_CONNECTION_DEFAULT),
// -1));

// 		// Polaczenie
// 		connection = TlinsAstroBase ::tlinsConnectionsManager
// ::getInstance().getConnection(TLINS_CONNECTION_DEFAULT);

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
// // 		                                    TlinsAstroBase ::tlinsConfiguration
// ::RAMP_PARAMETER_GUIDING_RA_V_MAX);

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
// // 		                                    TlinsAstroBase ::tlinsConfiguration
// ::RAMP_PARAMETER_GUIDING_DC_V_MAX);
// // }

void TlinsTelescope::ISGetProperties(const char *dev)
{
	// If we are connected, we define the property to the client.
	if (isConnected()) {
		defineProperty(&GuideRateNP);
		defineProperty(&ManualCorrectionsRateNP);
		defineProperty(&ModeSP);
		defineProperty(&TrackingStateSP);
	} else {
        deleteProperty(GuideRateNP.name);
		deleteProperty(ManualCorrectionsRateNP.name);
		deleteProperty(ModeSP.name);
		deleteProperty(TrackingStateSP.name);
	}

	Telescope::ISGetProperties(dev);
}

bool TlinsTelescope::processModeChangeRequest(ISState *states, char *names[], int n)
{
	// Sprawdzenie czy urzadzenie jest polaczone
	if (!isConnected()) {
		DEBUG(INDI::Logger::DBG_SESSION, "Device is not connected");
		return false;
	}

	// Weryfikacja statusu urzadzenia
	tlinsAstroEngineInterface::tlinsCalibrarionStateInfo calibrarionState;
	if (!getDeviceState(calibrarionState) ||
	    calibrarionState.get_engineState() != tlinsAstroEngineInterface::tlinsEngineStateValue::STATE_REGULAR) {
		TLINS_LOG_ERROR("Calibration has not been complted.");
		return false;
	}

	// Polaczenie
	auto connection = getConnection();
	if (!connection) {
		DEBUG(INDI::Logger::DBG_ERROR, "No active connection");
		return IPState::IPS_OK;
	}

	auto setState = [this, connection](tlinsAstroEngineInterface::tlinsEngineMode mode) {
        try {
			// Zatrzymanie sledzenia
			connection->getAstro()->stopTracking();

            // Ustawienie zadanego trybu pracy
            connection->getAstro()->setMode(mode);

			// Modyfikacja UI'a
			IDSetSwitch(&TrackingStateSP, nullptr);
        } catch (tlinsInterfaceException& exc) {
			return false;
        }
		return true;
	};

	for(int i = 0; i < n; i ++) {
		std::string iName{names[i]};

		DEBUG(INDI::Logger::DBG_SESSION, names[i]);

		if(iName == "MODE_STANDARD") {
			// Tryb standardowy
			return setState(tlinsAstroEngineInterface::tlinsEngineMode::MODE_STANDARD);

		} else if(iName == "MODE_STEPS") {
			// Tryb predkosci z korekta manualna
			return setState(tlinsAstroEngineInterface::tlinsEngineMode::MODE_STANDARD_SPEED);

		} else if(iName == "MODE_GUIDER") {
			// Tryb guider
			return setState(tlinsAstroEngineInterface::tlinsEngineMode::MODE_EXTERNAL_SUPPORT);
		}
	}
	return false;
}

bool TlinsTelescope::processTrackingStatusChangeRequest(ISState *states, char *names[], int n)
{
	// Sprawdzenie czy urzadzenie jest polaczone
	if (!isConnected()) {
		DEBUG(INDI::Logger::DBG_SESSION, "Device is not connected");
		return false;
	}

	// Weryfikacja statusu urzadzenia
	tlinsAstroEngineInterface::tlinsCalibrarionStateInfo calibrarionState;
	if (!getDeviceState(calibrarionState) ||
	    calibrarionState.get_engineState() != tlinsAstroEngineInterface::tlinsEngineStateValue::STATE_REGULAR) {
		TLINS_LOG_ERROR("Calibration has not been complted.");
		return false;
	}

	// Polaczenie
	auto connection = getConnection();
	if (!connection) {
		DEBUG(INDI::Logger::DBG_ERROR, "No active connection");
		return IPState::IPS_OK;
	}

	auto setState = [connection](bool state) {
        try {
			// Zatrzymanie sledzenia
			if(!state) {
				connection->getAstro()->stopTracking();
			} else {
				connection->getAstro()->startTracking();
			}

        } catch (tlinsInterfaceException& exc) {
			return false;
        }
		return true;
	};

	for(int i = 0; i < n; i ++) {
		std::string iName{names[i]};

		DEBUG(INDI::Logger::DBG_SESSION, names[i]);

		if(iName == "TRACKING_START") {
			// Tryb standardowy
			return setState(true);
		} else if(iName == "TRACKING_STOP") {
			// Tryb predkosci z korekta manualna
			return setState(false);
		}
	}
	return false;
}

bool TlinsTelescope::ISNewSwitch(const char *dev, const char *name_, ISState *states, char *names[], int n)
{
	if (dev != nullptr && strcmp(dev, getDeviceName()) == 0) {

		std::string name{name_ == nullptr ? "": name_};
		if(name == TlinsTelescope::STR_MOUNT_MODE) {
			return processModeChangeRequest(states, names, n);
		} else if(name == TlinsTelescope::STR_TRACKING_STATE) {
			return processTrackingStatusChangeRequest(states, names, n);
		}
	}
	return Telescope::ISNewSwitch(dev, name_, states, names, n);

}

bool TlinsTelescope::ISNewText(const char *dev, const char *name, char *texts[], char *names[], int n)
{
	return Telescope::ISNewText(dev, name, texts, names, n);
}

/*


	//
	// Guider - konfiguracja
	//
    IUFillNumber(&GuideRate[RA_AXIS], "Guider rate RA", "RA Rate", "%g", 0, 1, 0.1, 0.5);
    IUFillNumber(&GuideRate[DEC_AXIS], "Guider rate DEC", "DEC Rate", "%g", 0, 1, 0.1, 0.5);
    IUFillNumberVector(	&GuideRateNP, GuideRate, 2, getDeviceName(), "GUIDE_RATE", "Guiding Rate", GUIDE_TAB, IP_RW, 0, IPS_IDLE);

	//
	// Manualne korekty
	//
    IUFillNumber(&ManualCorrectionsRate[RA_AXIS], "Manual correction RA", "RA correction", "%g", 0, 1, 0.1, 0.0);
    IUFillNumber(&ManualCorrectionsRate[DEC_AXIS], "Manual correction DEC", "DEC correction", "%g", 0, 1, 0.1, 0.0);
    IUFillNumberVector(	&ManualCorrectionsRateNP, ManualCorrectionsRate, 2, getDeviceName(), "MANUAL_CORRECTION_RATE", "Manual corrections", GUIDE_TAB, IP_RW, 0, IPS_IDLE);

	//
	// Sposób sledzenia
	//
    IUFillSwitch(&Mode[MountMode::STANDARD], "MODE_STANDARD", "Standard and manual corrections mode", ISS_ON);
	IUFillSwitch(&Mode[MountMode::STEPS], "MODE_STEPS", "Step mode", ISS_OFF);
    IUFillSwitch(&Mode[MountMode::GUIDER], "MODE_GUIDER", "Guider mode", ISS_OFF);
    IUFillSwitchVector(&ModeSP, Mode, 3, getDeviceName(), "MOUNT_MODE", "Mount mode", MOTION_TAB, IP_RW, ISR_1OFMANY, 60, IPS_IDLE );

	//
	// Wlaczenie/wylaczenie sledzenia
	//
    IUFillSwitch(&TrackingState[TrackingCase::START], "TRACKING_START", "Tracking start", ISS_OFF);
    IUFillSwitch(&TrackingState[TrackingCase::STOP], "TRACKING_STOP", "Tracking stop", ISS_ON);
    IUFillSwitchVector(&TrackingStateSP, TrackingState, 2, getDeviceName(), "TRACKING_STATE", "Tracking state", MOTION_TAB, IP_RW, ISR_1OFMANY, 60, IPS_IDLE );

	//
	// Parametery polaczenia sieciowego
	//
    IUFillNumber(&CommunicationPorts[ASTRO],          "Astro engine port",        "Astro engine port",        "%g", 20000, 64000, 1, 20000);
    IUFillNumber(&CommunicationPorts[ASTRO_ASYNC],    "Astro engine async port",  "Astro engine async port",  "%g", 20000, 64000, 1, 20002);
	IUFillNumber(&CommunicationPorts[DEVICE_PORT],    "Device engine port",       "Device engine port",       "%g", 20000, 64000, 1, 20001);
	IUFillNumber(&CommunicationPorts[DEVICE_ASYNC],   "Dev	// Sprawdzenie czy urzadzenie jest polaczone
	if (!isConnected()) {
		DEBUG(INDI::Logger::DBG_SESSION, "Device is not connected");
		return false;
	}


	IUFillText(&ipAddress, "Address ip", "Address ip", "192.168.100");
	IUFillTextVector(&ipAddressSP, &ipAddress, 1, getDeviceName(), "IP_ADDRESS", "Address", CONNECTION_TAB, IP_RW, 60, IPS_IDLE);
	defineProperty(&ipAddressSP);
*/

bool TlinsTelescope::processManualCorrectionConfigurationChangeRequest(double values[], char *names[], int n)
{
	double raRate;
	double decRate;

	// Sprawdzenie czy urzadzenie jest polaczone
	if (!isConnected()) {
		DEBUG(INDI::Logger::DBG_SESSION, "Device is not connected");
		return false;
	}

	// Polaczenie
	auto connection = getConnection();
	if (!connection) {
		DEBUG(INDI::Logger::DBG_ERROR, "No active connection");
		return false;
	}

	// Odczy aktualnych wartości konfiguracyjnych
	try {
		connection -> astro -> manualCorrectionGet(raRate, decRate);
	}
	catch(tlinsInterfaceException exc) {
		DEBUG(INDI::Logger::DBG_SESSION, "Error read manual correction configuration from device");
		return false;
	}

	// Pobranie dostarczonej konfiguracji
	for(int i = 0; i < n; i ++) {
		std::string iName{names[i]};
		DEBUG(INDI::Logger::DBG_SESSION, names[i]);
		if(iName == std::string{"MANUAL_CORRECTION_RA"}) {
			raRate = values[i];
		} else if(iName == std::string{"MANUAL_CORRECTION_DEC"}) {
			decRate = values[i];
		}
	}

	// Zaaplikowanie konfiguracji
	try {
		connection -> astro -> manualCorrection(raRate, decRate);
		return true;
	}
	catch(tlinsInterfaceException exc) {
		DEBUG(INDI::Logger::DBG_SESSION, exc.getErrorMessage().c_str());
		DEBUG(INDI::Logger::DBG_SESSION, "Error set manual correction configuration on device");
		return false;
	}
}

bool TlinsTelescope::processGoToChangeRequest(double values[], char *names[], int n)
{
	double ra;
	double dec;

	// Sprawdzenie czy urzadzenie jest polaczone
	if (!isConnected()) {
		DEBUG(INDI::Logger::DBG_SESSION, "Device is not connected");
		return false;
	}

	// Polaczenie
	auto connection = getConnection();
	if (!connection) {
		DEBUG(INDI::Logger::DBG_ERROR, "No active connection");
		return false;
	}

	// Pobranie dostarczonej konfiguracji
	for(int i = 0; i < n; i ++) {
		std::string iName{names[i]};

		DEBUG(INDI::Logger::DBG_SESSION, names[i]);
		if(iName == std::string{"RA"}) {
			ra = values[i];
		} else if(iName == std::string{"DEC"}) {
			dec = values[i];
		}
	}

	return Goto(ra, dec);
}

bool TlinsTelescope::processGuiderConfigurationChangeRequest(double values[], char *names[], int n)
{
	double raRate;
	double decRate;
	bool useRaForDec;

	// Sprawdzenie czy urzadzenie jest polaczone
	if (!isConnected()) {
		DEBUG(INDI::Logger::DBG_SESSION, "Device is not connected");
		return false;
	}

	// Polaczenie
	auto connection = getConnection();
	if (!connection) {
		DEBUG(INDI::Logger::DBG_ERROR, "No active connection");
		return false;
	}

	// Odczy aktualnych wartości konfiguracyjnych
	try {
		connection -> astro -> guiderRatioGet(raRate, decRate, useRaForDec);
	}
	catch(tlinsInterfaceException exc) {
		DEBUG(INDI::Logger::DBG_SESSION, "Error read guider configuration from device");
		return false;
	}

	// Pobranie dostarczonej konfiguracjiTlinsTelescope::
	for(int i = 0; i < n; i ++) {
		std::string iName{names[i]};

		DEBUG(INDI::Logger::DBG_SESSION, names[i]);
		if(iName == std::string{"GUIDER_RATE_RA"}) {
			raRate = values[i];
		} else if(iName == std::string{"GUIDER_RATE_DEC"}) {
			decRate = values[i];
		}
	}

	// Zaaplikowanie konfiguracji
	try {
		connection -> astro -> guiderRatioSet(raRate, decRate, useRaForDec);
		return true;
	}
	catch(tlinsInterfaceException exc) {
		DEBUG(INDI::Logger::DBG_SESSION, "Error set guider configuration on device");
		return false;
	}
}

bool TlinsTelescope::ISNewNumber(const char *dev, const char *name_, double values[], char *names[], int n)
{
	DEBUG(INDI::Logger::DBG_SESSION, ">>>>>>>>>>>>>>>>>> ISNewNumber()");
	DEBUG(INDI::Logger::DBG_SESSION, name_);
	for(int i = 0; i < n; i ++) {
		DEBUG(INDI::Logger::DBG_SESSION, names[i]);
	}


	if (dev == nullptr || strcmp(dev, getDeviceName()) != 0) {
		return Telescope::ISNewNumber(dev, name_, values, names, n);
	}

	std::string name{name_ == nullptr ? "": name_};

	if(name == std::string{"EQUATORIAL_EOD_COORD"}) {

		return TlinsTelescope::processGoToChangeRequest(values, names, n);
	} else if(name == TlinsTelescope::STR_GUIDE_RATE) {

		IUUpdateNumber(&GuideRateNP, values, names, n);
		return processGuiderConfigurationChangeRequest(values, names, n);
	} else if(name == TlinsTelescope::STR_MANUAL_CORRECTION_RATE) {

		IUUpdateNumber(&ManualCorrectionsRateNP, values, names, n);
		return processManualCorrectionConfigurationChangeRequest(values, names, n);
	} else {
		// TODO
		// TODO - others
	}




	return true;	
}


bool TlinsTelescope::ISNewBLOB(const char *dev, const char *name, int sizes[], int blobsizes[], char *blobs[],
                               char *formats[], char *names[], int n)
{
	return DefaultDevice::ISNewBLOB(dev, name, sizes, blobsizes, blobs, formats, names, n);
}

// ----------------

static std::unique_ptr<TlinsTelescope> simpleDevice{new TlinsTelescope()};
