#ifndef __tlins_driver_hpp__
#define __tlins_driver_hpp__

#include <libindi/defaultdevice.h>
#include <libindi/indiguiderinterface.h>
#include <libindi/inditelescope.h>
#include <tlinsastrobaseutils.h>
#include <tlinsastroenginestate.h>
#include <tlinsastrouibase.h>
#include <tlinsconnection.h>


class TlinsTelescope : /*public INDI::Telescope, public INDI::GuiderInterface, */ public INDI::DefaultDevice {
  public:
	TlinsTelescope();

  protected:
	bool        Connect();
	bool        Disconnect();
	const char *getDefaultName();
	//   public:
	// 	virtual bool initProperties() override;
	// 	virtual void ISGetProperties(const char *dev) override;
	// 	virtual bool updateProperties() override;
	// 	virtual bool ReadScopeStatus() override;
	// 	virtual bool Goto(double, double) override;
	// 	virtual bool Sync(double ra, double dec) override;


	// 	virtual bool Abort();

	// 	virtual bool Park() override;
	// 	virtual bool UnPark() override;

	// 	// Konstruktor/destruktor klasy
	// 	TlinsTelescope();
	// 	virtual ~TlinsTelescope();

	//   protected:
	// 	virtual bool Connect() override;
	// 	virtual bool Disconnect() override;
	// 	const char * getDefaultName();


	//   private:
	// 	unsigned int                     DBG_SCOPE{0};
	// 	INDI::Telescope::TelescopeStatus trackState;

	//
	// -----------------------------------
	// ---      Reszta - nie uzyta     ---
	// -----------------------------------
	//

	// virtual bool Disconnect() override;

	//   public:
	// 	virtual bool ISNewNumber(const char *dev, const char *name, double values[], char *names[], int n) override;
	// 	virtual bool ISNewSwitch(const char *dev, const char *name, ISState *states, char *names[], int n) override;
	// 	virtual bool ISNewText(const char *dev, const char *name, char *texts[], char *names[], int n);

	//   protected:
	// 	virtual bool MoveNS(INDI_DIR_NS dir, TelescopeMotionCommand command) override;
	// 	virtual bool MoveWE(INDI_DIR_WE dir, TelescopeMotionCommand command) override;

	// 	virtual IPState GuideNorth(uint32_t ms) override;
	// 	virtual IPState GuideSouth(uint32_t ms) override;
	// 	virtual IPState GuideEast(uint32_t ms) override;
	// 	virtual IPState GuideWest(uint32_t ms) override;

	// 	virtual bool SetTrackMode(uint8_t mode) override;
	// 	virtual bool SetTrackEnabled(bool enabled) override;
	// 	virtual bool SetTrackRate(double raRate, double deRate) override;


	// 	// Parking
	// 	virtual bool SetCurrentPark() override;
	// 	virtual bool SetDefaultPark() override;

	//   private:
	// 	double currentRA{0};
	// 	double currentDEC{90};
	// 	double targetRA{0};
	// 	double targetDEC{0};

	// 	/// used by GoTo and Park
	// 	void StartSlew(double ra, double dec, TelescopeStatus status);

	// 	bool forceMeridianFlip{false};

	// 	double guiderEWTarget[2];
	// 	double guiderNSTarget[2];

	// 	INumber               GuideRateN[2];
	// 	INumberVectorProperty GuideRateNP;

	// #ifdef USE_EQUATORIAL_PE
	// 	INumberVectorProperty EqPENV;
	// 	INumber               EqPEN[2];

	// 	ISwitch               PEErrNSS[2];
	// 	ISwitchVectorProperty PEErrNSSP;

	// 	ISwitch               PEErrWES[2];
	// 	ISwitchVectorProperty PEErrWESP;
	// #endif
};


// namespace tlins
// {

// class TlinsTelescope : public INDI::Telescope {
//   public:
// 	static const int CFG_DEV_URL       = 0;
// 	static const int CFG_DEV_ASYNC_URL = 1;
// 	static const int CFG_ASTRO_URL     = 2;

//   private:
// 	std::string urlDev;
// 	std::string urlDevAsync;
// 	std::string urlAstro;

// 	// Bledy pomiarowe
// 	double longnitudeError;
// 	double latitudeError;
// 	double weightError;

// 	// Parametery rampy w poszczegolnych trybach pracy
// 	// Standardowe przemieszczenie - teleskop nieskalibrowany
// 	double DEG_A_X;
// 	double DEG_D_X;
// 	double DEG_V_X;
// 	double DEG_A_Y;
// 	double DEG_D_Y;
// 	double DEG_V_Y;

// 	// Przemieszczenie w trybie Astro
// 	double ASTRO_A_RA;
// 	double ASTRO_D_RA;
// 	double ASTRO_V_RA;
// 	double ASTRO_A_DC;
// 	double ASTRO_D_DC;
// 	double ASTRO_V_DC;

// 	// Przemieszczenie w trybie Guidera
// 	double GUIDER_A_RA;
// 	double GUIDER_D_RA;
// 	double GUIDER_V_RA;
// 	double GUIDER_A_DC;
// 	double GUIDER_D_DC;
// 	double GUIDER_V_DC;

// 	// Parametery srodowiskowe
// 	double envAmbientPreasure;
// 	double envTemperature;
// 	double envRealHumidity;
// 	double envEfectiveColor;

// 	// Miejsce obserwacji
// 	double      posLongnitude;
// 	double      posLatitude;
// 	double      posHeight;
// 	std::string posElipsoideType;

//   public:
// 	TlinsTelescope();

//   public:
// 	virtual bool updateProperties();
// 	virtual bool Handshake();
// 	virtual void TimerHit();

// 	virtual bool Connect();
// 	// virtual bool Disconnect();

// 	virtual bool ISNewNumber(const char *dev, const char *name, double values[], char *names[], int n);

// 	virtual bool ISNewSwitch(const char *dev, const char *name, ISState *states, char *names[], int n);
// 	virtual void ISGetProperties(const char *dev);
// 	virtual bool ISSnoopDevice(XMLEle *root);

// 	virtual bool saveConfigItems(FILE *fp);
// 	virtual bool Sync(double ra, double dec);
// 	virtual bool MoveNS(INDI_DIR_NS dir, TelescopeMotionCommand command);
// 	virtual bool MoveWE(INDI_DIR_WE dir, TelescopeMotionCommand command);
// 	virtual bool SetTrackMode(uint8_t mode);
// 	// virtual bool SetTrackRate(double raRate, double deRate);
// 	virtual int  AddTrackMode(const char *name, const char *label, bool isDefault = false);
// 	virtual bool SetTrackEnabled(bool enabled);
// 	virtual bool updateTime(ln_date *utc, double utc_offset);
// 	virtual bool updateLocation(double latitude, double longitude, double elevation);
// 	virtual bool SetParkPosition(double Axis1Value, double Axis2Value);
// 	virtual bool SetCurrentPark();
// 	virtual bool SetDefaultPark();
// 	virtual bool SetSlewRate(int index);
// };

// }; // namespace tlins


#endif