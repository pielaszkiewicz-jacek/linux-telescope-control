#ifndef __tlinsSerialDevice_hpp__
#define __tlinsSerialDevice_hpp__

#include <tlinsSerialDeviceException.hpp>
#include <tlinsSerialDeviceRequest.hpp>

#include <tlinsSerialGpio.hpp>

#include <modbus.h>
#include <poll.h>
#include <stdint.h>

#include <atomic>
#include <functional>
#include <map>
#include <memory>
#include <mutex>
#include <string>
#include <thread>
#include <utility>
#include <vector>


#define __GENERATE_CMD__(axis, cmd) ((1 << (axis)) | ((static_cast<unsigned int>(cmd)) << 4))

#define __SET_METHOD__(name, type)                                                                                     \
	void set_##name(const type &v)                                                                                     \
	{                                                                                                                  \
		name = v;                                                                                                      \
	}

#define __GET_METHOD__(name, type)                                                                                     \
	const type get_##name() const                                                                                      \
	{                                                                                                                  \
		return name;                                                                                                   \
	}

#define __WRITE_METHOD__(name, t, ref)                                                                                 \
	void set_dev_##name(const t &v)                                                                                    \
	{                                                                                                                  \
		if (!isInit_##name || v != last_##name) {                                                                      \
			isInit_##name = true;                                                                                      \
			last_##name   = v;                                                                                         \
			(ref).writreRegister(name, v);                                                                             \
		}                                                                                                              \
	}                                                                                                                  \
                                                                                                                       \
	void set_force_dev_##name(const t &v)                                                                              \
	{                                                                                                                  \
		isInit_##name = true;                                                                                          \
		last_##name   = v;                                                                                             \
		(ref).writreRegister(name, v);                                                                                 \
	}

#define __READ_METHOD__(name, t, ref)                                                                                  \
	void get_dev_##name(t &v)                                                                                          \
	{                                                                                                                  \
		(ref).readRegister(name, v);                                                                                   \
	}

#define __DECLARE__(type, name, s, ref, stype)                                                                         \
  private:                                                                                                             \
	type name;                                                                                                         \
	type default_##name;                                                                                               \
	type last_##name;                                                                                                  \
	bool isInit_##name{false};                                                                                         \
                                                                                                                       \
  public:                                                                                                              \
	void set_default_##name(const stype v)                                                                             \
	{                                                                                                                  \
		default_##name = v;                                                                                            \
	};                                                                                                                 \
                                                                                                                       \
	void set_dev_default_##name(const stype v)                                                                         \
	{                                                                                                                  \
		set_dev_##name(default_##name);                                                                                \
	};                                                                                                                 \
                                                                                                                       \
	const stype get_default_##name() const                                                                             \
	{                                                                                                                  \
		return default_##name;                                                                                         \
	};                                                                                                                 \
                                                                                                                       \
	__GET_METHOD__(name, type);                                                                                        \
                                                                                                                       \
	__SET_METHOD__(name, type);                                                                                        \
                                                                                                                       \
	__WRITE_METHOD__(name, s, ref);                                                                                    \
                                                                                                                       \
	__READ_METHOD__(name, s, ref);

enum class tlinsSerialParity {
	NONE = 0, // none
	EVEN = 1, // even
	ODD  = 2  // odd
};

enum class tlinsSerialMotorStatus : int {
	MOTOR_OFF                    = 0,
	MOTOR_ON                     = 1,
	MOTOR_SPEED_MODE             = 2,
	MOTOR_POSITION_MODE          = 3,
	MOTOR_REACHED_POSITION       = 4,
	MOTOR_ERROR_POSITION_ENCODER = 5,
	MOTOR_ERROR_HOME_MODE        = 6,
	MOTOR_CORRECTION_MODE        = 8
};

//
// ---------------------------------------------------------
// ---------------------------------------------------------
// ---------------------------------------------------------
//

class tlinsSerialUtils {
  public:
	// Zapis rejestrow
	static void writreRegister(std::mutex &mtx, modbus_t *modbusCtx, const int address, const int16_t value);
	static void writreRegister(std::mutex &mtx, modbus_t *modbusCtx, const int address, const int32_t value);

	static void writreRegister(std::mutex &mtx, modbus_t *modbusCtx, const int address,
	                           const std::vector<int32_t> &value);

	// Odczyt rejestrow
	static void readRegister(std::mutex &mtx, modbus_t *modbusCtx, const int address, int16_t &value);
	static void readRegister(std::mutex &mtx, modbus_t *modbusCtx, const int address, int32_t &value);

	static void readRegister(std::mutex &mtx, modbus_t *modbusCtx, const int address, std::vector<int32_t> &value,
	                         const int count);
};


//
// ---------------------------------------------------------
// ------------------------------------CFG_PROGRAM_SELECTION_ADDRESS

class tlinsSerialDevice;

class tlinsSerialMainDevice {
  private:
	// Muteks synchronizujacy operacje na urzadzeniu
	std::mutex mtx;

	long statusCheckInterval;

	std::atomic<bool> endMonitorThread;

  public:
	const long getStatusCheckInterval() const
	{
		return statusCheckInterval;
	};

	void setStatusCheckInterval(const long &v)
	{
		if (v <= 0)
			statusCheckInterval = 5; // Dumyslnie 5 milisekund
		else
			statusCheckInterval = v;
	}

  private:
	// Adres rejestru selekcji programu
	__DECLARE__(int, LIN_V, int32_t, *this, int);
	__DECLARE__(int, LIN_V_ABS, int32_t, *this, int);
	__DECLARE__(int, STOP, int16_t, *this, int);

	// Rejestery kontrolujace synchroniczne wykonywanie przemieszczenia
	__DECLARE__(int, AXIS_CTR_MODE, int16_t, *this, int);
	__DECLARE__(int, AXIS_VEL_ABS_TRIG, int16_t, *this, int);
	__DECLARE__(int, AXIS_VEL_REL_TRIG, int16_t, *this, int);
	__DECLARE__(int, AXIS_POS_ABS_TRIG, int16_t, *this, int);
	__DECLARE__(int, AXIS_POS_REL_TRIG, int16_t, *this, int);

	__DECLARE__(int, DATA_TYPE, int16_t, *this, int);
	__DECLARE__(int, M_ENABLE, int16_t, *this, int);
	__DECLARE__(int, M_DISABLE, int16_t, *this, int);

	// Adresy potwierdzen wykonanych przemieszczen
	__DECLARE__(int, REG_CONF_X, int16_t, *this, int);
	__DECLARE__(int, REG_CONF_Y, int16_t, *this, int);
	__DECLARE__(int, REG_CONF_XY, int16_t, *this, int);
	__DECLARE__(int, REG_CONF_ERROR, int16_t, *this, int);

  private:
	// Konfiguracja zwiazana z limitami
	double                                      limitsH;
	double                                      limitsR1;
	double                                      limitsR2;
	double                                      limitsDX;
	double                                      limitsDZ;
	long                                        limitsFrequency;
	std::vector<std::pair<std::string, double>> limitsAxisAngles;

  public:
	double                                      getLimitsH() const;
	double                                      getLimitsR1() const;
	double                                      getLimitsR2() const;
	double                                      getLimitsDX() const;
	double                                      getLimitsDZ() const;
	long                                        getLimitsFrequency() const;
	std::vector<std::pair<std::string, double>> getLimitsAxisAngles() const;

	void setLimitsH(const double v);
	void setLimitsR1(const double v);
	void setLimitsR2(const double v);
	void setLimitsDX(const double v);
	void setLimitsDZ(const double v);
	void setLimitsFrequency(const long v);
	void setLimitsAxisAngles(const std::string &a, const double v);

  private:
	std::map<std::string, std::shared_ptr<tlinsSerialDevice>> devices;

	struct ModbusCtx {
		modbus_t         *modbusCtx;
		std::string       serialDeviceName;
		tlinsSerialParity parity;
		int               baundRate;
		int               dataBit;
		int               stopBit;
		int               serverId;
		int               timeOut;
		bool              debugProtocol;
	};

	// Kontekst polaczenia modbus - glowne
	ModbusCtx mainModbusCtx;

	// Kontekst polaczenia modbus - potwierdzenia
	ModbusCtx confModbusCtx;

	// Adresy rejestrow potwierdzen
	long regConfX;
	long regConfY;
	long regConfXY;
	long regConfError;

  public:
	enum class ConfirmationType {
		COMPLETED = 1,
		ERROR     = 2,
	};

	struct ConfirmationInfo {
		ConfirmationType confType;
		unsigned long    confID;
	};

	using confirmationFunction    = std::function<void(const std::vector<std::pair<std::string, ConfirmationType>> &)>;
	using confirmationFunctionExt = std::function<void(const std::vector<std::pair<std::string, ConfirmationInfo>> &)>;

	int           addCallback(confirmationFunction fun);
	int           addCallback(confirmationFunctionExt fun);
	void          removeCallback(int id);
	void          removeCallbackExt(int id);
	void          setConfId(const std::string &a, unsigned long v);
	unsigned long getNextConfId();

  private:
	// Zarzadzanie conf. ID
	unsigned long                        confIdCounter;
	std::mutex                           confIdCounterMtx;
	std::map<std::string, unsigned long> confIdAxisMap;

  private:
	void drivesStatus(std::map<std::string, int> &statuses);

	void confirmationsCallbackExt(tlinsSerialMainDevice &parent);
	void endConfirmation();

	std::map<int, confirmationFunction>    callbacks;
	std::map<int, confirmationFunctionExt> callbacksExt;

	std::atomic<bool>            endConfirmations;
	std::mutex                   mtxCbList;
	std::unique_ptr<std::thread> confCallbackThread;

  private:
	// Aktualne wartosci
	long curr_IN_LINER_V;

	bool syncMode;

  public:
	// Awaryjne zatrzymanie całoego urzadzenia
	void abort();

	void runLinearPosition(const long V);
	void runLinearPositionAbsolute(const long V);
	void setupConnection(ModbusCtx &ctx) const;

	void enableSynchMode();
	void disableSynchMode();

	void triggerAbsVel();
	void triggerRelVel();

	void triggerAbsPos();
	void triggerRelPos();

	void setIntDataType();
	void setRealDataType();
	void enableMotors(int16_t motors);
	void disableMotors(int16_t motors);

  public:
	//
	// KonfiguracjaDirection
	//
	void setupConnection();

	void applayDefaultConfiguration();

	std::map<std::string, std::shared_ptr<tlinsSerialDevice>>::iterator begin();
	std::map<std::string, std::shared_ptr<tlinsSerialDevice>>::iterator end();
	std::map<std::string, std::shared_ptr<tlinsSerialDevice>>::iterator find(const std::string &n);

	bool getDevice(const std::string &device, std::shared_ptr<tlinsSerialDevice> &outDev);
	bool addDevice(const std::shared_ptr<tlinsSerialDevice> &v);

	const long getRegConfX() const
	{
		return regConfX;
	};

	const long getRegConfY() const
	{
		return regConfY;
	};

	const long getRegConfXY() const
	{
		return regConfXY;
	};

	const long getRegConfError() const
	{
		return regConfError;
	};

	void setRegConfX(const long v)
	{
		regConfX = v;
	};

	void setRegConfY(const long v)
	{
		regConfY = v;
	};

	void setRegConfXY(const long v)
	{
		regConfXY = v;
	};

	void setRegConfError(const long v)
	{
		regConfError = v;
	};

	const std::string &getSerialDeviceName() const;
	const std::string &getSerialDeviceNameConf() const;
	void               setSerialDeviceName(const std::string &v);
	void               setSerialDeviceNameConf(const std::string &v);

	int  getBaundRate() const;
	int  getBaundRateConf() const;
	void setBaundRate(const int v);
	void setBaundRateConf(const int v);

	tlinsSerialParity getParity() const;
	tlinsSerialParity getParityConf() const;
	void              setParity(const tlinsSerialParity v);
	void              setParityConf(const tlinsSerialParity v);

	int  getDataBit() const;
	int  getDataBitConf() const;
	void setDataBit(const int v);
	void setDataBitConf(const int v);

	int  getStopBit() const;
	int  getStopBitConf() const;
	void setStopBit(const int v);
	void setStopBitConf(const int v);

	int  getServerId() const;
	int  getServerIdConf() const;
	void setServerId(const int v);
	void setServerIdConf(const int v);

	int  getTimeOut() const;
	int  getTimeOutConf() const;
	void setTimeOut(const int v);
	void setTimeOutConf(const int v);

	bool isDebugProtocolEnabled() const;
	bool isDebugProtocolEnabledConf() const;
	void setDebugProtocol(const bool v);
	void setDebugProtocolConf(const bool v);

  public:
	// Zapis rejestrow
	void writreRegister(const int address, const int16_t value, const bool c = false);
	void writreRegister(const int address, const int32_t value, const bool c = false);

	// Odczyt rejestrow
	void readRegister(const int address, int16_t &value, const bool c = false);
	void readRegister(const int address, int32_t &value, const bool c = false);

  public:
	tlinsSerialMainDevice &operator=(const tlinsSerialMainDevice &v);
	tlinsSerialMainDevice();

	tlinsSerialMainDevice(const tlinsSerialMainDevice &v);

	virtual ~tlinsSerialMainDevice();
};

//
// ---------------------------------------------------------------------------
// ---------------------------------------------------------------------------
// ---------------------------------------------------------------------------
//
enum class tlinsSerialCtrlMode {
	MODE_NONE     = 0,
	MODE_LINER    = 1,
	MODE_SPEED    = 2,
	MODE_POSITION = 4,
	MODE_STOP     = 6,
	MODE_ERROR    = 7
};

enum class tlinsSerialCfgUpdate : int { MODE_CFG_POSITION = 1, MODE_CFG_SPEED = 2, MODE_CFG_LINER = 3 };

enum class tlinsSerialModeSpeedPosition { MODE_DET_SPEED = 1, MODE_DET_POSITION = 2 };

enum class tlinsSerialModeStopAbort : int { MODE_DET_STOP = 1, MODE_DET_ABORT = 2 };

enum class tlinsSerialAbsRel { MODE_ABS = 1, MODE_REL = 2 };

enum class tlinsSerialErrors { ERROR_PENDING_TASK = 1, ERROR_LINER_REL_0_MOVE = 2, ERROR_LINER_ABS_0_MOVE = 3 };

class tlinsSerialDevice {
  public:
	static bool isDeviceIdle(int16_t aStatus)
	{
		return aStatus == 1 || aStatus == 4;
	};

  private:
	std::shared_ptr<tlinsSerialMainDevice> parent;

  private:
	//
	// Status silnika
	//
	// +++
	__DECLARE__(int, M_STATUS, int16_t, *parent, int);

	//
	// Aktualna pozycja i impulsy enkodera
	//
	// ++
	__DECLARE__(int, POS_ACTUAL, int32_t, *parent, long);
	__DECLARE__(int, POS_ACTUAL_ENCODER, int32_t, *parent, long);
	__DECLARE__(int, POS_ACTUAL_ENCODER_SET, int32_t, *parent, long);

	//
	// Konfiguracja
	//
	// 1. Parametery rampy dla trybu interpolowanego
	__DECLARE__(int, LIN_RAMP_A, int32_t, *parent, long);
	__DECLARE__(int, LIN_RAMP_D, int32_t, *parent, long);
	__DECLARE__(int, LIN_RAMP_V_MAX, int32_t, *parent, long);

	// 2. Parametery rampy dla standardowego przemieszczenia i trybu predkosci
	__DECLARE__(int, RAMP_A, int32_t, *parent, long);
	__DECLARE__(int, RAMP_D, int32_t, *parent, long);
	__DECLARE__(int, RAMP_V_MAX, int32_t, *parent, long);

	// Rejesty do zadania pozycji i prdkosci
	__DECLARE__(int, VEL_ABS, int32_t, *parent, long);
	__DECLARE__(int, VEL_REL, int32_t, *parent, long);
	__DECLARE__(int, POS_REL, int32_t, *parent, long);
	__DECLARE__(int, POS_ABS, int32_t, *parent, long);

	// Rejestr stopu
	__DECLARE__(int, STOP, int16_t, *parent, int);

	// - Maksymalna wartosci pozycji enkodera i silnika
	__DECLARE__(int, CFG_PULS_MAX, int32_t, *parent, long);
	__DECLARE__(int, CFG_ENC_PULS_MAX, int32_t, *parent, long);

  private:
	long curr_RAMP_A;
	long curr_RAMP_D;
	long curr_RAMP_V_MAX;

	long curr_LIN_RAMP_A;
	long curr_LIN_RAMP_D;
	long curr_LIN_RAMP_V_MAX;

	long maxSpeed;

  public:
	void setMaxSpeed(const long v)
	{
		maxSpeed = v;
	}

	long getMaxSpeed() const
	{
		return maxSpeed;
	}

	// Parametery rampy dla trybu predkosci i standardowego przemieszczenia
	// ++
	void setRampParameters(const long A, const long D, const long V, const bool force = false);

	// Parametery rampy dla interpolacji liniowej
	// ++
	void setLinRampParameters(const long A, const long D, const long V_MAX, const bool force = false);

	// Operacje na urzadzeniu
	// - Przemieszczenie z zadana prdkoscia. V > 0 obrot w strone dodatnia
	//                                       V < 0 obrot w strone ujemna
	// ++
	void setSpeed(const long V, const tlinsSerialDirection dir);

	// - Przemieszczenie do zadanej pozycji. pos > 0 ruch w strone dodatnia
	//                                       pos < 0 ruch w strone ujrmnas
	void setPosition(const long pos, const tlinsSerialDirection dir);
	void setPosition(const long pos);

	// - Przemieszczenie do zadanej pozycji w trybie interpolacji liniowej
	// ++/
	void setLinearPosition(const long pos, const tlinsSerialDirection dir);
	void setLinearPosition(const long pos);

	// Zatrzymanie osi
	// ++
	void stop();

	// Odczyt pozyci silnika i enkodera
	void getActualPosition(long &pos, long &encPos);
	void getActualPosition(long &pos, long &encPos, long &rawPos, long &rawEncPos);

	// Ustawinie pozycji kontrolera
	void setActualPosition(const long pos, const long encPos);

	// Odczyt aktualnego stanu silnika
	void getStatus(tlinsSerialMotorStatus &stat);

  private:
	// Identyfikator urzadzenia w kontrolerze zewnetrznym
	unsigned int deviceID;

	// Nazwa osi
	std::string axisId;

	// Ilosc impulsow na obrotMotorStatus
	unsigned long encoderResolution;

	// Ilosc impulsow na obrot
	unsigned long stepsOnResolution;

  public:
	// Parametery ramopy dl aposzczegolnych truybow przemieszczebua
	void         setDeviceID(const unsigned int v);
	unsigned int getDeviceID() const;

	void        setAxisId(const std::string &v);
	std::string getAxisId() const;

  public:
	tlinsSerialDevice &operator=(const tlinsSerialDevice &v);

  public:
	tlinsSerialDevice(const tlinsSerialDevice &v);
	tlinsSerialDevice(std::shared_ptr<tlinsSerialMainDevice> &parent_);
	virtual ~tlinsSerialDevice() = default;
};

/*
 * Klasa realizuje nasluchiwanie na wskazanych portach GPIO
 */
class tlinsSerialDeviceManager {
  private:
	std::map<std::string, std::shared_ptr<tlinsSerialMainDevice>> devicesMap;

	tlinsSerialDeviceManager() = default;

  public:
	// Metoda na podstawie konfiguracji tworzy obiekty urzadzen
	void createDevices();

	// Zwraca kon urzadzenia
	std::map<std::string, std::shared_ptr<tlinsSerialMainDevice>>::iterator find(const std::string &name);
	std::map<std::string, std::shared_ptr<tlinsSerialMainDevice>>::iterator begin();
	std::map<std::string, std::shared_ptr<tlinsSerialMainDevice>>::iterator end();

  public:
	static tlinsSerialDeviceManager &getInstance();
};

#endif
