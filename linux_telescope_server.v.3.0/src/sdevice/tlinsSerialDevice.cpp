#include <tlinsBacktrace.hpp>
#include <tlinsDeviceParametersList.hpp>
#include <tlinsLogger.hpp>
#include <tlinsSerialDevice.hpp>
#include <tlinsSerialServer.hpp>
#include <tlins_parameters.hpp>

#include <algorithm>
#include <cmath>
#include <errno.h>
#include <fcntl.h>
#include <modbus-rtu.h>
#include <modbus.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <vector>

#include <tlinsSerialGpio.hpp>

int tlinsSerialMainDevice::addCallback(confirmationFunctionExt fun)
{
	static int idx = 0;

	std::unique_lock<std::mutex> lock(mtxCbList);
	idx++;
	callbacksExt[idx] = fun;
	return idx;
}

int tlinsSerialMainDevice::addCallback(confirmationFunction fun)
{
	static int idx = 0;

	std::unique_lock<std::mutex> lock(mtxCbList);
	idx++;
	callbacks[idx] = fun;
	return idx;
}

void tlinsSerialMainDevice::removeCallback(int id)
{
	std::unique_lock<std::mutex> lock(mtxCbList);
	callbacks.erase(id);
}

void tlinsSerialMainDevice::removeCallbackExt(int id)
{
	std::unique_lock<std::mutex> lock(mtxCbList);
	callbacksExt.erase(id);
}

unsigned long tlinsSerialMainDevice::getNextConfId()
{
	std::unique_lock<std::mutex> lock(confIdCounterMtx);
	confIdCounter++;
	return confIdCounter;
}

void tlinsSerialMainDevice::confirmationsCallbackExt(tlinsSerialMainDevice &parent)
{
	while (!endConfirmations) {
		// Odczyt statusow
		std::map<std::string, int> statuses;
		drivesStatus(statuses);

		// Przejscie po liscie i wygenerowanie rezultatu
		std::vector<std::pair<std::string, ConfirmationInfo>> result;

		{
			std::unique_lock<std::mutex> lock(confIdCounterMtx);

			for (auto &item : statuses) {
				if (item.second != 1 && item.second != 4 && item.second != 5 && item.second != 8) {
					continue; // Status nie brany pod uwage
				}

				ConfirmationInfo statInfo;
				statInfo.confID = parent.confIdAxisMap[item.first];

				if (item.second == 5) {
					statInfo.confType = ConfirmationType::ERROR;
					std::pair<std::string, ConfirmationInfo> citem{item.first, statInfo};
					result.push_back(citem);
				} else {
					statInfo.confType = ConfirmationType::COMPLETED;
					std::pair<std::string, ConfirmationInfo> citem{item.first, statInfo};
					result.push_back(citem);
				}
			}
		}

		// Wywolanie callbackow
		{
			std::unique_lock<std::mutex> lock(mtxCbList);
			for (auto &fun : callbacksExt)
				fun.second(result);
		}

		// Sleep 5 ms
		std::this_thread::sleep_for(std::chrono::milliseconds{statusCheckInterval});
	}
}

void tlinsSerialMainDevice::setConfId(const std::string &a, unsigned long v)
{
	std::unique_lock<std::mutex> lock(confIdCounterMtx);
	confIdAxisMap[a] = v;
}

void tlinsSerialMainDevice::endConfirmation()
{
	endConfirmations = true;
}

void tlinsSerialMainDevice::drivesStatus(std::map<std::string, int> &statuses)
{
	for (auto &iter : devices) {
		int16_t status;
		iter.second->get_dev_M_STATUS(status);
		statuses[iter.first] = status;
	}
}

void tlinsSerialMainDevice::applayDefaultConfiguration()
{
	// Ustalenie typu danych
	setIntDataType();

	// Wlaczenie silnikow
	enableMotors((1 << 0) | (1 << 1));


	// Domyslne parametery rampy dla poszczegolnych osi urzadzenia
	for (auto &iterM : devices) {
		auto iter = iterM.second;

		iter->set_dev_POS_ACTUAL(0);
		iter->set_dev_POS_ACTUAL_ENCODER_SET(0);

		iter->set_dev_RAMP_A(iter->get_default_RAMP_A());
		iter->set_dev_RAMP_D(iter->get_default_RAMP_D());
		iter->set_dev_RAMP_V_MAX(iter->get_default_RAMP_V_MAX());

		iter->set_dev_LIN_RAMP_A(iter->get_default_LIN_RAMP_A());
		iter->set_dev_LIN_RAMP_D(iter->get_default_LIN_RAMP_D());
		iter->set_dev_LIN_RAMP_V_MAX(iter->get_default_LIN_RAMP_V_MAX());
	}

	disableSynchMode();
}

void tlinsSerialMainDevice::writreRegister(const int address, const int16_t value, const bool c)
{
	if (c) {
		tlinsSerialUtils::writreRegister(mtx, confModbusCtx.modbusCtx, address, value);
	} else {
		tlinsSerialUtils::writreRegister(mtx, mainModbusCtx.modbusCtx, address, value);
	}
}

void tlinsSerialMainDevice::writreRegister(const int address, const int32_t value, const bool c)
{
	if (c) {
		tlinsSerialUtils::writreRegister(mtx, confModbusCtx.modbusCtx, address, value);
	} else {
		tlinsSerialUtils::writreRegister(mtx, mainModbusCtx.modbusCtx, address, value);
	}
}

void tlinsSerialMainDevice::readRegister(const int address, int16_t &value, const bool c)
{
	if (c) {
		tlinsSerialUtils::readRegister(mtx, confModbusCtx.modbusCtx, address, value);
	} else {
		tlinsSerialUtils::readRegister(mtx, mainModbusCtx.modbusCtx, address, value);
	}
}

void tlinsSerialMainDevice::readRegister(const int address, int32_t &value, const bool c)
{
	if (c) {
		tlinsSerialUtils::readRegister(mtx, confModbusCtx.modbusCtx, address, value);
	} else {
		tlinsSerialUtils::readRegister(mtx, mainModbusCtx.modbusCtx, address, value);
	}
}

void tlinsSerialMainDevice::runLinearPosition(const long v)
{
	// Odpalenie przemieszczenia
	set_force_dev_LIN_V(v);
}

void tlinsSerialMainDevice::runLinearPositionAbsolute(const long v)
{
	// Odpalenie przemieszczenia
	set_force_dev_LIN_V_ABS(v);
}

void tlinsSerialMainDevice::enableSynchMode()
{
	syncMode = true;
	set_force_dev_AXIS_CTR_MODE(1);
}

void tlinsSerialMainDevice::disableSynchMode()
{
	syncMode = false;
	set_force_dev_AXIS_CTR_MODE(0);
}

void tlinsSerialMainDevice::triggerAbsVel()
{
	int16_t value = (1 << 0) | (1 << 1);
	set_force_dev_AXIS_VEL_ABS_TRIG(value);
}

void tlinsSerialMainDevice::triggerRelVel()
{
	int16_t value = (1 << 0) | (1 << 1);
	set_force_dev_AXIS_VEL_REL_TRIG(value);
}

void tlinsSerialMainDevice::triggerAbsPos()
{
	int16_t value = (1 << 0) | (1 << 1);
	set_force_dev_AXIS_POS_ABS_TRIG(value);
}

void tlinsSerialMainDevice::triggerRelPos()
{
	int16_t value = (1 << 0) | (1 << 1);
	set_force_dev_AXIS_POS_REL_TRIG(value);
}

void tlinsSerialMainDevice::setIntDataType()
{
	int16_t value = 1;
	set_force_dev_DATA_TYPE(value);
}

void tlinsSerialMainDevice::setRealDataType()
{
	int16_t value = 0;
	set_force_dev_DATA_TYPE(value);
}

void tlinsSerialMainDevice::enableMotors(int16_t motors)
{
	set_force_dev_M_ENABLE(motors);
}

void tlinsSerialMainDevice::disableMotors(int16_t motors)
{
	set_force_dev_M_DISABLE(motors);
}

//
// Operacje - nowe
//
void tlinsSerialMainDevice::abort()
{
	uint16_t mask = 0;
	for (const auto &iter : devices) {
		mask += 1 << iter.second->getDeviceID();
	}
	set_force_dev_STOP(mask);
}

void tlinsSerialMainDevice::setupConnection(ModbusCtx &ctx) const
{
	char _parity_ = '\0';
	switch (ctx.parity) {
	case tlinsSerialParity::NONE:
		_parity_ = 'N';
		break;

	case tlinsSerialParity::EVEN:
		_parity_ = 'E';
		break;

	case tlinsSerialParity::ODD:
		_parity_ = 'O';
		break;
	}

	// Tworzenie kontextu
	TLINS_LOG_DEBUG("SERIAL DEVICE = " + ctx.serialDeviceName);
	ctx.modbusCtx = ::modbus_new_rtu(ctx.serialDeviceName.c_str(), ctx.baundRate, _parity_, ctx.dataBit, ctx.stopBit);
	if (ctx.modbusCtx == nullptr) {
		__THROW__(tlinsSerialDeviceException("Error setup modbus context", tlinsSerialDeviceException::ERROR_MODBUSS));
	}

	modbus_set_debug(ctx.modbusCtx, FALSE);

	if (::modbus_rtu_set_serial_mode(ctx.modbusCtx, MODBUS_RTU_RS232) < 0) {
		__THROW__(tlinsSerialDeviceException("Error set serial mode", tlinsSerialDeviceException::ERROR_MODBUSS));
	}

	// Set adress to remote slave
	if (::modbus_set_slave(ctx.modbusCtx, ctx.serverId) < 0) {
		__THROW__(tlinsSerialDeviceException("Error set slave id", tlinsSerialDeviceException::ERROR_MODBUSS));
	}

	// Opoznienie polaczenia
	if (::modbus_rtu_set_rts_delay(ctx.modbusCtx, ctx.timeOut) < 0) {
		__THROW__(tlinsSerialDeviceException("Error set timeourt", tlinsSerialDeviceException::ERROR_MODBUSS));
	}

	// Laczenie sie z urzadzeniem
	if (::modbus_connect(ctx.modbusCtx) < 0) {
		TLINS_LOG_ERROR(std::string("Connexion failed: %s\n") + std::string(::modbus_strerror(errno)));
		__THROW__(tlinsSerialDeviceException("Error connect to modbus.", tlinsSerialDeviceException::ERROR_MODBUSS));
	}
}

void tlinsSerialMainDevice::setupConnection()
{
	//
	// Tworzenie polaczen
	//
	setupConnection(mainModbusCtx);
	setupConnection(confModbusCtx);

	//
	// Tworzenie watkow odpowiedzialnych za przetwarzanie potwierdzen
	//
	confCallbackThread =
	    std::move(std::unique_ptr<std::thread>{new std::thread{[this]() { this->confirmationsCallbackExt(*this); }}});
}

bool tlinsSerialMainDevice::addDevice(const std::shared_ptr<tlinsSerialDevice> &v)
{
	auto i = devices.find(v->getAxisId());
	if (i != devices.end()) {
		return false;
	}

	devices[v->getAxisId()] = v;

	// Przekazanie mutexa
	return true;
}

bool tlinsSerialMainDevice::getDevice(const std::string &device, std::shared_ptr<tlinsSerialDevice> &outDev)
{
	auto i = devices.find(device);
	if (i == devices.end()) {
		return false;
	}

	outDev = i->second;
	return true;
}

const std::string &tlinsSerialMainDevice::getSerialDeviceName() const
{
	return mainModbusCtx.serialDeviceName;
}

const std::string &tlinsSerialMainDevice::getSerialDeviceNameConf() const
{
	return confModbusCtx.serialDeviceName;
}

void tlinsSerialMainDevice::setSerialDeviceName(const std::string &v)
{
	mainModbusCtx.serialDeviceName = v;
}

void tlinsSerialMainDevice::setSerialDeviceNameConf(const std::string &v)
{
	confModbusCtx.serialDeviceName = v;
}

tlinsSerialMainDevice &tlinsSerialMainDevice::operator=(const tlinsSerialMainDevice &v)
{
	devices.erase(devices.begin(), devices.end());
	for (auto i = v.devices.begin(); i != v.devices.end(); i++) {
		devices[i->first] = i->second;
	}

	mainModbusCtx.serialDeviceName = v.mainModbusCtx.serialDeviceName;
	mainModbusCtx.baundRate        = v.mainModbusCtx.baundRate;
	mainModbusCtx.serverId         = v.mainModbusCtx.serverId;
	mainModbusCtx.dataBit          = v.mainModbusCtx.dataBit;
	mainModbusCtx.stopBit          = v.mainModbusCtx.stopBit;
	mainModbusCtx.timeOut          = v.mainModbusCtx.timeOut;
	mainModbusCtx.parity           = v.mainModbusCtx.parity;

	confModbusCtx.serialDeviceName = v.confModbusCtx.serialDeviceName;
	confModbusCtx.baundRate        = v.confModbusCtx.baundRate;
	confModbusCtx.serverId         = v.confModbusCtx.serverId;
	confModbusCtx.dataBit          = v.confModbusCtx.dataBit;
	confModbusCtx.stopBit          = v.confModbusCtx.stopBit;
	confModbusCtx.timeOut          = v.confModbusCtx.timeOut;
	confModbusCtx.parity           = v.confModbusCtx.parity;

	STOP      = v.STOP;
	LIN_V     = v.LIN_V;
	LIN_V_ABS = v.LIN_V_ABS;

	AXIS_CTR_MODE     = v.AXIS_CTR_MODE;
	AXIS_VEL_ABS_TRIG = v.AXIS_VEL_ABS_TRIG;
	AXIS_VEL_REL_TRIG = v.AXIS_VEL_REL_TRIG;
	AXIS_POS_ABS_TRIG = v.AXIS_POS_ABS_TRIG;
	AXIS_POS_REL_TRIG = v.AXIS_POS_REL_TRIG;
	DATA_TYPE         = v.DATA_TYPE;
	M_ENABLE          = v.M_ENABLE;
	M_DISABLE         = v.M_DISABLE;
	REG_CONF_X        = v.REG_CONF_X;
	REG_CONF_Y        = v.REG_CONF_Y;
	REG_CONF_XY       = v.REG_CONF_XY;
	REG_CONF_ERROR    = v.REG_CONF_ERROR;

	limitsH  = v.limitsH;
	limitsR1 = v.limitsR1;
	limitsR2 = v.limitsR2;
	limitsDX = v.limitsDX;
	limitsDZ = v.limitsDZ;

	for (auto &item : v.limitsAxisAngles) {
		limitsAxisAngles.push_back(item);
	}


	return *this;
}

std::map<std::string, std::shared_ptr<tlinsSerialDevice>>::iterator tlinsSerialMainDevice::begin()
{
	return devices.begin();
}

std::map<std::string, std::shared_ptr<tlinsSerialDevice>>::iterator tlinsSerialMainDevice::end()
{
	return devices.end();
}

std::map<std::string, std::shared_ptr<tlinsSerialDevice>>::iterator tlinsSerialMainDevice::find(const std::string &n)
{
	return devices.find(n);
}

int tlinsSerialMainDevice::getBaundRate() const
{
	return mainModbusCtx.baundRate;
}

int tlinsSerialMainDevice::getBaundRateConf() const
{
	return confModbusCtx.baundRate;
}

void tlinsSerialMainDevice::setBaundRate(const int v)
{
	mainModbusCtx.baundRate = v;
}

void tlinsSerialMainDevice::setBaundRateConf(const int v)
{
	confModbusCtx.baundRate = v;
}

tlinsSerialParity tlinsSerialMainDevice::getParity() const
{
	return mainModbusCtx.parity;
}

tlinsSerialParity tlinsSerialMainDevice::getParityConf() const
{
	return confModbusCtx.parity;
}

void tlinsSerialMainDevice::setParity(const tlinsSerialParity v)
{
	mainModbusCtx.parity = v;
}

void tlinsSerialMainDevice::setParityConf(const tlinsSerialParity v)
{
	confModbusCtx.parity = v;
}

int tlinsSerialMainDevice::getDataBit() const
{
	return mainModbusCtx.dataBit;
}

int tlinsSerialMainDevice::getDataBitConf() const
{
	return confModbusCtx.dataBit;
}

void tlinsSerialMainDevice::setDataBit(const int v)
{
	mainModbusCtx.dataBit = v;
}

void tlinsSerialMainDevice::setDataBitConf(const int v)
{
	confModbusCtx.dataBit = v;
}

int tlinsSerialMainDevice::getStopBit() const
{
	return mainModbusCtx.stopBit;
}

int tlinsSerialMainDevice::getStopBitConf() const
{
	return confModbusCtx.stopBit;
}

void tlinsSerialMainDevice::setStopBit(const int v)
{
	mainModbusCtx.stopBit = v;
}

void tlinsSerialMainDevice::setStopBitConf(const int v)
{
	confModbusCtx.stopBit = v;
}

int tlinsSerialMainDevice::getServerId() const
{
	return mainModbusCtx.serverId;
}

int tlinsSerialMainDevice::getServerIdConf() const
{
	return confModbusCtx.serverId;
}

void tlinsSerialMainDevice::setServerId(const int v)
{
	mainModbusCtx.serverId = v;
}

void tlinsSerialMainDevice::setServerIdConf(const int v)
{
	confModbusCtx.serverId = v;
}

int tlinsSerialMainDevice::getTimeOut() const
{
	return mainModbusCtx.timeOut;
}

int tlinsSerialMainDevice::getTimeOutConf() const
{
	return confModbusCtx.timeOut;
}

void tlinsSerialMainDevice::setTimeOut(const int v)
{
	mainModbusCtx.timeOut = v;
}

void tlinsSerialMainDevice::setTimeOutConf(const int v)
{
	confModbusCtx.timeOut = v;
}

bool tlinsSerialMainDevice::isDebugProtocolEnabled() const
{
	return mainModbusCtx.debugProtocol;
}

bool tlinsSerialMainDevice::isDebugProtocolEnabledConf() const
{
	return confModbusCtx.debugProtocol;
}

double tlinsSerialMainDevice::getLimitsH() const
{
	return limitsH;
}

long tlinsSerialMainDevice::getLimitsFrequency() const
{
	return limitsFrequency;
}

double tlinsSerialMainDevice::getLimitsR1() const
{
	return limitsR1;
}

double tlinsSerialMainDevice::getLimitsR2() const
{
	return limitsR2;
}

double tlinsSerialMainDevice::getLimitsDX() const
{
	return limitsDX;
}

double tlinsSerialMainDevice::getLimitsDZ() const
{
	return limitsDZ;
}

std::vector<std::pair<std::string, double>> tlinsSerialMainDevice::getLimitsAxisAngles() const
{
	return limitsAxisAngles;
}

void tlinsSerialMainDevice::setLimitsH(const double v)
{
	limitsH = v;
}

void tlinsSerialMainDevice::setLimitsFrequency(const long v)
{
	limitsFrequency = v;
}

void tlinsSerialMainDevice::setLimitsR1(const double v)
{
	limitsR1 = v;
}

void tlinsSerialMainDevice::setLimitsR2(const double v)
{
	limitsR2 = v;
}

void tlinsSerialMainDevice::setLimitsDX(const double v)
{
	limitsDX = v;
}

void tlinsSerialMainDevice::setLimitsDZ(const double v)
{
	limitsDZ = v;
}

void tlinsSerialMainDevice::setLimitsAxisAngles(const std::string &a, const double v)
{
	limitsAxisAngles.emplace_back(std::pair<std::string, double>{a, v});
}

void tlinsSerialMainDevice::setDebugProtocol(const bool v)
{
	std::lock_guard<std::mutex> lock(mtx);

	mainModbusCtx.debugProtocol = v;
	::modbus_set_debug(mainModbusCtx.modbusCtx, mainModbusCtx.debugProtocol ? TRUE : FALSE);
}

void tlinsSerialMainDevice::setDebugProtocolConf(const bool v)
{
	std::lock_guard<std::mutex> lock(mtx);

	confModbusCtx.debugProtocol = v;
	::modbus_set_debug(confModbusCtx.modbusCtx, confModbusCtx.debugProtocol ? TRUE : FALSE);
}

tlinsSerialMainDevice::tlinsSerialMainDevice()
{
	mainModbusCtx.modbusCtx = nullptr;
	confModbusCtx.modbusCtx = nullptr;
	endConfirmations        = false;

	// Watek monitorujacy stan programu
	endMonitorThread = false;
	syncMode         = false;
}

tlinsSerialMainDevice::tlinsSerialMainDevice(const tlinsSerialMainDevice &v)
{
	// Parametery urzadzenia
	*this            = v;
	endConfirmations = false;

	// Konfiguracja polaczenia
	setupConnection();
}

tlinsSerialMainDevice::~tlinsSerialMainDevice()
{
	// Zatrzymanie watykow
	endConfirmation();

	if (confCallbackThread) {
		if (confCallbackThread->joinable()) {
			confCallbackThread->join();
		}
	}

	// Zamkniecie polaczen
	if (mainModbusCtx.modbusCtx != nullptr) {
		modbus_close(mainModbusCtx.modbusCtx);
		modbus_free(mainModbusCtx.modbusCtx);
	}

	if (confModbusCtx.modbusCtx != nullptr) {
		modbus_close(confModbusCtx.modbusCtx);
		modbus_free(confModbusCtx.modbusCtx);
	}
}

//
// -----------------------------------------------------------
//
void tlinsSerialDevice::setRampParameters(const long A, const long D, const long V, const bool force)
{
	curr_RAMP_A = A;
	set_dev_RAMP_A(curr_RAMP_A);

	curr_RAMP_D = D;
	set_dev_RAMP_D(curr_RAMP_D);

	curr_RAMP_V_MAX = V;
	set_force_dev_RAMP_V_MAX(curr_RAMP_V_MAX);
}

void tlinsSerialDevice::setLinRampParameters(const long A, const long D, const long V_MAX, const bool force)
{
	curr_LIN_RAMP_A = A;
	set_dev_LIN_RAMP_A(curr_LIN_RAMP_A);

	curr_LIN_RAMP_D = D;
	set_dev_LIN_RAMP_D(curr_LIN_RAMP_D);

	curr_LIN_RAMP_V_MAX = V_MAX;
	set_force_dev_LIN_RAMP_V_MAX(curr_LIN_RAMP_V_MAX);
}

void tlinsSerialDevice::stop()
{
	set_force_dev_STOP(1 << deviceID);
}

void tlinsSerialDevice::setSpeed(const long V_, const tlinsSerialDirection dir)
{
	// Wartosc predkosci
	long V = ::abs(V_);

	if (dir == tlinsSerialDirection::RIGHT) {
		V *= -1L;
	}
	set_force_dev_VEL_ABS(static_cast<int32_t>(V));
}

void tlinsSerialDevice::setPosition(const long pos_, const tlinsSerialDirection dir)
{
	long pos = ::abs(pos_);
	if (dir == tlinsSerialDirection::RIGHT) {
		pos *= -1L;
	}
	set_force_dev_POS_REL(static_cast<int32_t>(pos));
}

void tlinsSerialDevice::setPosition(const long pos)
{
	set_force_dev_POS_ABS(static_cast<int32_t>(pos));
}

// Odczyt pozyci silnika i enkodera
void tlinsSerialDevice::getActualPosition(long &pos, long &encPos)
{
	int32_t value = 0;

	//
	// Odczyt pozycji silnika
	//
	get_dev_POS_ACTUAL(value);
	pos = static_cast<long>(value);

	// Normalizacja pozycji
	if (get_default_CFG_PULS_MAX() != 0) {
		while (pos < 0) {
			pos += get_default_CFG_PULS_MAX();
		}

		while (pos > get_default_CFG_PULS_MAX()) {
			pos -= get_default_CFG_PULS_MAX();
		}
	}

	//
	// Odczyt pozycji enkodera
	//
#if 1
	get_dev_POS_ACTUAL_ENCODER(value);
	encPos = static_cast<long>(value);

	if (get_default_CFG_PULS_MAX() != 0) {
		while (encPos < 0) {
			encPos += get_default_CFG_PULS_MAX();
		}

		while (encPos > get_default_CFG_PULS_MAX()) {
			encPos -= get_default_CFG_PULS_MAX();
		}
	}
#else
	encPos    = 0;
#endif
}

void tlinsSerialDevice::getActualPosition(long &pos, long &encPos, long &rawPos, long &rawEncPos)
{
	int32_t value = 0;

	//
	// Odczyt pozycji silnika
	//
	get_dev_POS_ACTUAL(value);
	pos    = static_cast<long>(value);
	rawPos = pos;

	// Normalizacja pozycji
	if (get_default_CFG_PULS_MAX() != 0) {
		while (pos < 0) {
			pos += get_default_CFG_PULS_MAX();
		}

		while (pos > get_default_CFG_PULS_MAX()) {
			pos -= get_default_CFG_PULS_MAX();
		}
	}

	//
	// Odczyt pozycji enkodera
	//
#if 1
	get_dev_POS_ACTUAL_ENCODER(value);
	encPos    = static_cast<long>(value);
	rawEncPos = encPos;

	if (get_default_CFG_PULS_MAX() != 0) {
		while (encPos < 0) {
			encPos += get_default_CFG_PULS_MAX();
		}

		while (encPos > get_default_CFG_PULS_MAX()) {
			encPos -= get_default_CFG_PULS_MAX();
		}
	}
#else
	encPos    = 0;
	rawEncPos = 0;
#endif
}

void tlinsSerialDevice::setActualPosition(const long pos, const long)
{
	// Odczyt pozycji silnika
	set_force_dev_POS_ACTUAL(static_cast<int32_t>(pos));

	auto   pos_ = static_cast<double>(pos);
	double posEnc_ =
	    pos_ * static_cast<double>(get_default_CFG_ENC_PULS_MAX()) / static_cast<double>(get_default_CFG_PULS_MAX());

	// Ustawienie pozycji enkodera
	// Ustawiamy w impulsach przeliczonych na impulsy napedu
	set_force_dev_POS_ACTUAL_ENCODER_SET(static_cast<int32_t>(posEnc_));
}

// Odczyt aktualnego stanu urzadzenia
void tlinsSerialDevice::getStatus(tlinsSerialMotorStatus &stat)
{
	int16_t status = 0;

	get_dev_M_STATUS(status);
	stat = static_cast<tlinsSerialMotorStatus>(status);
}

void tlinsSerialDevice::setDeviceID(const unsigned int v)
{
	deviceID = v;
}

unsigned int tlinsSerialDevice::getDeviceID() const
{
	return deviceID;
}

void tlinsSerialDevice::setAxisId(const std::string &v)
{
	axisId = v;
}

std::string tlinsSerialDevice::getAxisId() const
{
	return axisId;
}

tlinsSerialDevice &tlinsSerialDevice::operator=(const tlinsSerialDevice &v)
{
	deviceID                 = v.deviceID;
	axisId                   = v.axisId;
	parent                   = v.parent;
	RAMP_A                   = v.RAMP_A;
	RAMP_D                   = v.RAMP_D;
	RAMP_V_MAX               = v.RAMP_V_MAX;
	LIN_RAMP_A               = v.LIN_RAMP_A;
	LIN_RAMP_D               = v.LIN_RAMP_D;
	LIN_RAMP_V_MAX           = v.LIN_RAMP_V_MAX;
	curr_RAMP_A              = v.curr_RAMP_A;
	curr_RAMP_D              = v.curr_RAMP_D;
	curr_RAMP_V_MAX          = v.curr_RAMP_V_MAX;
	curr_LIN_RAMP_A          = v.curr_LIN_RAMP_A;
	curr_LIN_RAMP_D          = v.curr_LIN_RAMP_D;
	curr_LIN_RAMP_V_MAX      = v.curr_LIN_RAMP_V_MAX;
	M_STATUS                 = v.M_STATUS;
	POS_ACTUAL               = v.POS_ACTUAL;
	POS_ACTUAL_ENCODER       = v.POS_ACTUAL_ENCODER;
	POS_ACTUAL_ENCODER_SET   = v.POS_ACTUAL_ENCODER_SET;
	maxSpeed                 = v.maxSpeed;
	STOP                     = v.STOP;
	CFG_PULS_MAX             = v.CFG_PULS_MAX;
	CFG_ENC_PULS_MAX         = v.CFG_ENC_PULS_MAX;
	default_RAMP_A           = v.default_RAMP_A;
	default_RAMP_D           = v.default_RAMP_D;
	default_RAMP_V_MAX       = v.default_RAMP_V_MAX;
	default_LIN_RAMP_A       = v.default_LIN_RAMP_A;
	default_LIN_RAMP_D       = v.default_LIN_RAMP_D;
	default_LIN_RAMP_V_MAX   = v.default_LIN_RAMP_V_MAX;
	default_CFG_PULS_MAX     = v.default_CFG_PULS_MAX;
	default_CFG_ENC_PULS_MAX = v.default_CFG_ENC_PULS_MAX;
	return *this;
}

tlinsSerialDevice::tlinsSerialDevice(std::shared_ptr<tlinsSerialMainDevice> &parent_) : parent{parent_}
{
}

tlinsSerialDevice::tlinsSerialDevice(const tlinsSerialDevice &v)
{
	*this = v;
}

//
// -------------------------------------------------------------------
// -------------------------------------------------------------------
// -------------------------------------------------------------------
//
static const int maxNumberModbusRetrys = 32;

void tlinsSerialUtils::writreRegister(std::mutex &mtx, modbus_t *modbusCtx, const int address, const int16_t value)
{
	std::lock_guard<std::mutex> lock(mtx);

	if (modbusCtx == nullptr) {
		__THROW__(tlinsSerialDeviceException("Error write into register", tlinsSerialDeviceException::ERROR_MODBUSS));
	}

	int count = 0;
	while (true) {
		int rc = ::modbus_write_register(modbusCtx, address, static_cast<uint16_t>(value));
		if (rc < 0) {
			count++;
			if (count >= maxNumberModbusRetrys) {
				__THROW__(
				    tlinsSerialDeviceException("Error write into register", tlinsSerialDeviceException::ERROR_MODBUSS));
			}
		} else {
			break;
		}
	}
}

void tlinsSerialUtils::writreRegister(std::mutex &mtx, modbus_t *modbusCtx, const int address, const int32_t value_)
{
	std::lock_guard<std::mutex> lock(mtx);


	if (modbusCtx == nullptr) {
		__THROW__(tlinsSerialDeviceException("Error write into register", tlinsSerialDeviceException::ERROR_MODBUSS));
	}

	int32_t value = value_;

	int count = 0;
	while (true) {
		int rc = ::modbus_write_registers(modbusCtx, address, 2, reinterpret_cast<uint16_t *>(&value));
		if (rc < 0) {
			count++;
			if (count >= maxNumberModbusRetrys) {
				__THROW__(
				    tlinsSerialDeviceException("Error write into register", tlinsSerialDeviceException::ERROR_MODBUSS));
			}
		} else {
			break;
		}
	}
}

void tlinsSerialUtils::writreRegister(std::mutex &mtx, modbus_t *modbusCtx, const int address,
                                      const std::vector<int32_t> &value)
{
	std::lock_guard<std::mutex> lock(mtx);

	if (modbusCtx == nullptr) {
		__THROW__(tlinsSerialDeviceException("Error write into register", tlinsSerialDeviceException::ERROR_MODBUSS));
	}

	std::unique_ptr<uint32_t> values_{new uint32_t[2 * value.size()]};

	uint32_t *ptr = values_.get();
	for (int i = 0; i < value.size(); i++) {
		ptr[i] = value[i];
	}

	int count = 0;
	while (true) {
		int rc =
		    ::modbus_write_registers(modbusCtx, address, 2 * value.size(), reinterpret_cast<uint16_t *>(values_.get()));
		if (rc < 0) {
			count++;
			if (count >= maxNumberModbusRetrys) {
				__THROW__(
				    tlinsSerialDeviceException("Error write into register", tlinsSerialDeviceException::ERROR_MODBUSS));
			}
		} else {
			break;
		}
	}
}

void tlinsSerialUtils::readRegister(std::mutex &mtx, modbus_t *modbusCtx, const int address, int16_t &value_)
{
	std::lock_guard<std::mutex> lock(mtx);
	uint16_t                    value;

	if (modbusCtx == nullptr) {
		__THROW__(tlinsSerialDeviceException("Error read register", tlinsSerialDeviceException::ERROR_MODBUSS));
	}

	int count = 0;
	while (true) {
		int rc = ::modbus_read_registers(modbusCtx, address, 1, static_cast<uint16_t *>(&value));
		if (rc < 0) {
			count++;
			if (count >= maxNumberModbusRetrys) {
				__THROW__(tlinsSerialDeviceException("Error read register", tlinsSerialDeviceException::ERROR_MODBUSS));
			}
		} else {
			break;
		}
	}
	value_ = value;
}

void tlinsSerialUtils::readRegister(std::mutex &mtx, modbus_t *modbusCtx, const int address, int32_t &value_)
{
	std::lock_guard<std::mutex> lock(mtx);
	uint32_t                    value;

	if (modbusCtx == nullptr) {
		__THROW__(tlinsSerialDeviceException("Error read register", tlinsSerialDeviceException::ERROR_MODBUSS));
	}

	int count = 0;
	while (true) {
		int rc = ::modbus_read_registers(modbusCtx, address, 2, reinterpret_cast<uint16_t *>(&value));
		if (rc < 0) {
			count++;
			if (count >= maxNumberModbusRetrys) {
				__THROW__(tlinsSerialDeviceException("Error read register", tlinsSerialDeviceException::ERROR_MODBUSS));
			}
		} else {
			break;
		}
	}
	value_ = value;
}

void tlinsSerialUtils::readRegister(std::mutex &mtx, modbus_t *modbusCtx, const int address,
                                    std::vector<int32_t> &value, const int count)
{
	std::lock_guard<std::mutex> lock(mtx);

	if (modbusCtx == nullptr) {
		__THROW__(tlinsSerialDeviceException("Error read register", tlinsSerialDeviceException::ERROR_MODBUSS));
	}

	std ::unique_ptr<uint16_t> values{new uint16_t[2 * count]};

	int tcount = 0;
	while (true) {
		int rc = ::modbus_read_registers(modbusCtx, address, 2 * count, values.get());
		if (rc < 0) {
			tcount++;
			if (tcount >= maxNumberModbusRetrys) {
				__THROW__(tlinsSerialDeviceException("Error read register", tlinsSerialDeviceException::ERROR_MODBUSS));
			}
		} else {
			break;
		}
	}

	int32_t *ptr = reinterpret_cast<int32_t *>(values.get());
	for (int i = 0; i < count; i++) {
		value[i] = ptr[i];
	}
}

//
// -------------------------------------------------------------------
// -------------------------------------------------------------------
//
tlinsSerialDeviceManager &tlinsSerialDeviceManager::getInstance()
{
	static tlinsSerialDeviceManager instance{};
	return instance;
}

std::map<std::string, std::shared_ptr<tlinsSerialMainDevice>>::iterator tlinsSerialDeviceManager::begin()
{
	return devicesMap.begin();
}

std::map<std::string, std::shared_ptr<tlinsSerialMainDevice>>::iterator tlinsSerialDeviceManager::end()
{
	return devicesMap.end();
}

static std::string getStringValue(const std::string &name, tlinsParametersList &para)
{
	std::string str_val;

	if (!para.getParameterValue(name, str_val)) {
		__THROW__(tlinsSerialDeviceException("No parameter value: " + name,
		                                     tlinsSerialDeviceException::ERROR_CONFIGURATION_ERROR));
	}
	return str_val;
}

static unsigned long getLongValue(const std::string &name, tlinsParametersList &para)
{
	std::string str_val;

	if (!para.getParameterValue(name, str_val)) {
		__THROW__(tlinsSerialDeviceException("No parameter value: " + name,
		                                     tlinsSerialDeviceException::ERROR_CONFIGURATION_ERROR));
	}

	try {
		return readLongValue(str_val.c_str(), "");
	}
	catch (...) {
		__THROW__(tlinsSerialDeviceException("The parameter value is not number: " + str_val,
		                                     tlinsSerialDeviceException::ERROR_CONFIGURATION_ERROR));
	}
}

static int getIntValue(const std::string &name, tlinsParametersList &para)
{
	std::string str_val;

	if (!para.getParameterValue(name, str_val)) {
		__THROW__(tlinsSerialDeviceException("No parameter value: " + name,
		                                     tlinsSerialDeviceException::ERROR_CONFIGURATION_ERROR));
	}

	try {
		return readIntValue(str_val.c_str(), "");
	}
	catch (...) {
		__THROW__(tlinsSerialDeviceException("The parameter value is not number: " + str_val,
		                                     tlinsSerialDeviceException::ERROR_CONFIGURATION_ERROR));
	}
}

static double getDoubleValue(const std::string &name, tlinsParametersList &para)
{
	std::string str_val;

	if (!para.getParameterValue(name, str_val)) {
		__THROW__(tlinsSerialDeviceException("No parameter value: " + name,
		                                     tlinsSerialDeviceException::ERROR_CONFIGURATION_ERROR));
	}

	try {
		return readDoubleValue(str_val.c_str(), "");
	}
	catch (...) {
		__THROW__(tlinsSerialDeviceException("The parameter value is not number: " + str_val,
		                                     tlinsSerialDeviceException::ERROR_CONFIGURATION_ERROR));
	}
}

void tlinsSerialDeviceManager::createDevices()
{
	auto devsIter = tlinsDeviceParametersList::get().begin();
	for (; devsIter != tlinsDeviceParametersList::get().end(); devsIter++) {
		auto  mainDevName = devsIter->first;
		auto &mainDevPara = devsIter->second;

		// Sprawdzenie czy sa duplikaty
		auto iterf = tlinsSerialDeviceManager::devicesMap.find(mainDevName);
		if (iterf != tlinsSerialDeviceManager::devicesMap.end()) {
			__THROW__(tlinsSerialDeviceException("Duplicated main device",
			                                     tlinsSerialDeviceException::ERROR_CONFIGURATION_ERROR));
		}

		tlinsLogger::instance().logDebug("MAIN dev name ... " + mainDevName);

		// Urzadzenie glowne
		std::string       parityStr = getStringValue("parity", mainDevPara.getParameters());
		tlinsSerialParity parity_;
		if (parityStr.compare("even") == 0) {
			parity_ = tlinsSerialParity::EVEN;
		} else if (parityStr.compare("odd") == 0) {
			parity_ = tlinsSerialParity::ODD;
		} else if (parityStr.compare("none") == 0) {
			parity_ = tlinsSerialParity::NONE;
		} else {
			__THROW__(tlinsSerialDeviceException("Unknown parity type",
			                                     tlinsSerialDeviceException::ERROR_CONFIGURATION_ERROR));
		}

		std::string       parityStrConf = getStringValue("parity", mainDevPara.getParameters());
		tlinsSerialParity parityConf_;

		if (parityStrConf.compare("even") == 0) {
			parityConf_ = tlinsSerialParity::EVEN;
		} else if (parityStrConf.compare("odd") == 0) {
			parityConf_ = tlinsSerialParity::ODD;
		} else if (parityStrConf.compare("none") == 0) {
			parityConf_ = tlinsSerialParity::NONE;
		} else {
			__THROW__(tlinsSerialDeviceException("Unknown parity type",
			                                     tlinsSerialDeviceException::ERROR_CONFIGURATION_ERROR));
		}

		tlinsSerialMainDevice *ptr = new tlinsSerialMainDevice();

		ptr->setSerialDeviceName(mainDevPara.getSystemDeviceName());
		ptr->setBaundRate(getIntValue("baundRate", mainDevPara.getParameters()));
		ptr->setParity(parity_);
		ptr->setDataBit(getIntValue("dataBit", mainDevPara.getParameters()));
		ptr->setStopBit(getIntValue("stopBit", mainDevPara.getParameters()));
		ptr->setServerId(getIntValue("serverId", mainDevPara.getParameters()));
		ptr->setTimeOut(getIntValue("timeOut", mainDevPara.getParameters()));

		ptr->setStatusCheckInterval(getIntValue("statusCheckInterval", mainDevPara.getParameters()));

		ptr->setSerialDeviceNameConf(mainDevPara.getSystemDeviceNameConfirmation());
		ptr->setBaundRateConf(getIntValue("baundRateConf", mainDevPara.getParameters()));
		ptr->setParityConf(parityConf_);
		ptr->setDataBitConf(getIntValue("dataBitConf", mainDevPara.getParameters()));
		ptr->setStopBitConf(getIntValue("stopBitConf", mainDevPara.getParameters()));
		ptr->setServerIdConf(getIntValue("serverIdConf", mainDevPara.getParameters()));
		ptr->setTimeOutConf(getIntValue("timeOutConf", mainDevPara.getParameters()));
		ptr->setRegConfX(getLongValue("REG_CONF_X", mainDevPara.getParameters()));
		ptr->setRegConfY(getLongValue("REG_CONF_Y", mainDevPara.getParameters()));
		ptr->setRegConfXY(getLongValue("REG_CONF_XY", mainDevPara.getParameters()));
		ptr->setRegConfError(getLongValue("REG_CONF_ERROR", mainDevPara.getParameters()));
		ptr->set_STOP(getIntValue("STOP", mainDevPara.getParameters()));
		ptr->set_REG_CONF_X(getIntValue("REG_CONF_X", mainDevPara.getParameters()));
		ptr->set_REG_CONF_Y(getIntValue("REG_CONF_Y", mainDevPara.getParameters()));
		ptr->set_REG_CONF_XY(getIntValue("REG_CONF_XY", mainDevPara.getParameters()));
		ptr->set_REG_CONF_ERROR(getIntValue("REG_CONF_ERROR", mainDevPara.getParameters()));
		ptr->set_default_LIN_V(getLongValue("default_LIN_V", mainDevPara.getParameters()));
		ptr->set_default_LIN_V_ABS(getLongValue("default_LIN_V_ABS", mainDevPara.getParameters()));

		ptr->set_LIN_V(getIntValue("LIN_V", mainDevPara.getParameters()));
		ptr->set_LIN_V_ABS(getIntValue("LIN_V_ABS", mainDevPara.getParameters()));

		ptr->set_AXIS_CTR_MODE(getIntValue("AXIS_CTR_MODE", mainDevPara.getParameters()));
		ptr->set_AXIS_VEL_ABS_TRIG(getIntValue("AXIS_VEL_ABS_TRIG", mainDevPara.getParameters()));
		ptr->set_AXIS_VEL_REL_TRIG(getIntValue("AXIS_VEL_REL_TRIG", mainDevPara.getParameters()));
		ptr->set_AXIS_POS_ABS_TRIG(getIntValue("AXIS_POS_ABS_TRIG", mainDevPara.getParameters()));
		ptr->set_AXIS_POS_REL_TRIG(getIntValue("AXIS_POS_REL_TRIG", mainDevPara.getParameters()));

		ptr->set_DATA_TYPE(getIntValue("DATA_TYPE", mainDevPara.getParameters()));
		ptr->set_M_ENABLE(getIntValue("M_ENABLE", mainDevPara.getParameters()));
		ptr->set_M_DISABLE(getIntValue("M_DISABLE", mainDevPara.getParameters()));

		std::shared_ptr<tlinsSerialMainDevice> mainDevice(ptr);

		//
		// Konfiguracja limitow polozenia
		//
		ptr->setLimitsH(getDoubleValue("position-limit-h", mainDevPara.getParameters()));
		ptr->setLimitsR1(getDoubleValue("position-limit-r1", mainDevPara.getParameters()));
		ptr->setLimitsR2(getDoubleValue("position-limit-r2", mainDevPara.getParameters()));
		ptr->setLimitsDX(getDoubleValue("position-limit-dx", mainDevPara.getParameters()));
		ptr->setLimitsDZ(getDoubleValue("position-limit-dz", mainDevPara.getParameters()));
		double xv = getDoubleValue("position-limit-angle-X", mainDevPara.getParameters());
		ptr->setLimitsAxisAngles("X", xv);
		double yv = getDoubleValue("position-limit-angle-Y", mainDevPara.getParameters());
		ptr->setLimitsAxisAngles("Y", yv);
		double zv = getDoubleValue("position-limit-angle-Z", mainDevPara.getParameters());
		ptr->setLimitsAxisAngles("Z", zv);
		double freq = getIntValue("limit-frequency", mainDevPara.getParameters());
		ptr->setLimitsFrequency(freq);

		// Przejscie po urzadzeniach
		for (auto i = mainDevPara.getDevices().begin(); i != mainDevPara.getDevices().end(); i++) {
			auto  devName = i->first;
			auto &devPara = i->second;

			tlinsLogger::instance().logDebug("  MAIN sub dev name .. " + devName);
			tlinsLogger::instance().logDebug("   DEVICE ID ......... " + std::to_string(devPara.getDeviceID()));
			tlinsLogger::instance().logDebug("   AXIS ID ........... " + devPara.getAxis());

			auto sDevice = std::make_shared<tlinsSerialDevice>(mainDevice);

			unsigned int deviceID = devPara.getDeviceID();
			std::string  axisId   = devPara.getAxis();

			sDevice->setMaxSpeed(getIntValue("MAX_SPEED", devPara.getParameters()));
			sDevice->set_M_STATUS(getIntValue("M_STATUS", devPara.getParameters()));
			sDevice->set_POS_ACTUAL(getIntValue("POS_ACTUAL", devPara.getParameters()));
			sDevice->set_POS_ACTUAL_ENCODER(getIntValue("POS_ACTUAL_ENCODER", devPara.getParameters()));
			sDevice->set_POS_ACTUAL_ENCODER_SET(getIntValue("POS_ACTUAL_ENCODER_SET", devPara.getParameters()));
			sDevice->set_CFG_PULS_MAX(getIntValue("CFG_PULS_MAX", devPara.getParameters()));
			sDevice->set_CFG_ENC_PULS_MAX(getIntValue("CFG_ENC_PULS_MAX", devPara.getParameters()));
			sDevice->set_LIN_RAMP_A(getIntValue("LIN_RAMP_A", devPara.getParameters()));
			sDevice->set_LIN_RAMP_D(getIntValue("LIN_RAMP_D", devPara.getParameters()));
			sDevice->set_LIN_RAMP_V_MAX(getIntValue("LIN_RAMP_V_MAX", devPara.getParameters()));
			sDevice->set_RAMP_A(getIntValue("RAMP_A", devPara.getParameters()));
			sDevice->set_RAMP_D(getIntValue("RAMP_D", devPara.getParameters()));
			sDevice->set_RAMP_V_MAX(getIntValue("RAMP_V_MAX", devPara.getParameters()));
			sDevice->set_VEL_ABS(getIntValue("VEL_ABS", devPara.getParameters()));
			sDevice->set_POS_ABS(getIntValue("POS_ABS", devPara.getParameters()));
			sDevice->set_POS_REL(getIntValue("POS_REL", devPara.getParameters()));
			sDevice->set_STOP(getIntValue("STOP", devPara.getParameters()));
			sDevice->set_default_CFG_PULS_MAX(getLongValue("default_CFG_PULS_MAX", devPara.getParameters()));
			sDevice->set_default_CFG_ENC_PULS_MAX(getLongValue("default_CFG_ENC_PULS_MAX", devPara.getParameters()));

			sDevice->setDeviceID(deviceID);
			sDevice->setAxisId(axisId);

			if (!mainDevice->addDevice(sDevice)) {
				__THROW__(tlinsSerialDeviceException("Duplicated axis in device",
				                                     tlinsSerialDeviceException::ERROR_CONFIGURATION_ERROR));
			}
		}
		tlinsSerialDeviceManager::devicesMap[mainDevName] = mainDevice;
	}
}

std::map<std::string, std::shared_ptr<tlinsSerialMainDevice>>::iterator
tlinsSerialDeviceManager::find(const std::string &name)
{
	return devicesMap.find(name);
}
