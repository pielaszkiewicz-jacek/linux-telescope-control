#ifndef __tlins_driver_hpp__
#define __tlins_driver_hpp__

#include <libindi/defaultdevice.h>
#include <libindi/indiguiderinterface.h>
#include <libindi/inditelescope.h>
#include <tlinsastrobaseutils.h>
#include <tlinsastroenginestate.h>
#include <tlinsastrouibase.h>
#include <tlinsconnection.h>



class TlinsTelescope
    : public INDI::Telescope, public INDI::GuiderInterface//, public INDI::DefaultDevice {
{
public:
	static std::string STR_GUIDE_RATE;
	static std::string STR_MANUAL_CORRECTION_RATE;
	static std::string STR_MOUNT_MODE;
	static std::string STR_TRACKING_STATE;

public:
	TlinsTelescope();

	// TODO - ???????
	// virtual void ISGetProperties(const char *dev) override;

private:
	bool getDeviceState(tlinsAstroEngineInterface::tlinsCalibrarionStateInfo &calibrarionState);
	std::shared_ptr<TlinsAstroBase::tlinsConnectionContext> getConnection();

	IPState __guder_process_request(std::function<tlinsAstroEngineInterface::GuiderStatus()> fun);

	// IText StatusT[1] = {};

	// Mount Info
	enum MountInfo { MI_FW_VERSION };

	// Parametery guidera
	INumber GuideRate[2];
	INumberVectorProperty GuideRateNP;

	INumber ManualCorrectionsRate[2];
	INumberVectorProperty ManualCorrectionsRateNP;

	// Tryb pracy - krokowy/predkosc/guider
	ISwitch Mode[3];
	ISwitchVectorProperty ModeSP;
	enum MountMode { STEPS, STANDARD, GUIDER };
  
	ISwitch TrackingState[2];
	ISwitchVectorProperty TrackingStateSP;
	enum TrackingCase { START, STOP};


	INumber CommunicationPorts[5];
	INumberVectorProperty CommunicationPortsNP;
	enum Ports { ASTRO, ASTRO_ASYNC, DEVICE_PORT, DEVICE_ASYNC, SYSTEM_SERVICE };

	IText ipAddress;//[1] = {};
	ITextVectorProperty ipAddressSP;

	unsigned int DBG_SCOPE { 0 };

	bool processGoToChangeRequest(double values[], char *names[], int n);
	bool processModeChangeRequest(ISState *states, char *names[], int n);
	bool processTrackingStatusChangeRequest(ISState *states, char *names[], int n);
	bool processGuiderConfigurationChangeRequest(double values[], char *names[], int n);
	bool processManualCorrectionConfigurationChangeRequest(double values[], char *names[], int n);

protected:
	bool        Connect();
	bool        Disconnect();
	const char *getDefaultName();

	bool         updateProperties() override;
	virtual bool initProperties() override;

	bool ReadScopeStatus() override;
	// DONE
	bool Goto(double, double) override;
	bool Abort() override;

	bool Sync(double ra, double dec) override;

	IPState GuideNorth(uint32_t ms);
	IPState GuideSouth(uint32_t ms);
	IPState GuideEast(uint32_t ms);
	IPState GuideWest(uint32_t ms);
	// void GuideComplete(INDI_EQ_AXIS axis);

public:
	virtual void ISGetProperties(const char *dev) override;
	virtual bool ISNewSwitch(const char *dev, const char *name, ISState *states, char *names[], int n) override;
	virtual bool ISNewText(const char *dev, const char *name, char *texts[], char *names[], int n) override;
	virtual bool ISNewNumber(const char *dev, const char *name, double values[], char *names[], int n) override;
	virtual bool ISNewBLOB(const char *dev, const char *name, int sizes[], int blobsizes[], char *blobs[], char *formats[], char *names[], int n);

};

#endif