#ifndef __tlinsAstroEnginConfiguration_hpp__
#define __tlinsAstroEnginConfiguration_hpp__

#include <map>
#include <parameters/tlinsParametersList.hpp>
#include <string>
#include <tlinsAstroException.hpp>
#include <tlinsBacktrace.hpp>
#include <tlinsXMLParser.hpp>

class tlinsAstroEnginConfiguration {
  private:
	struct Axis {
		tlinsParametersList parameters;
		Axis               &operator=(const Axis &v) = default;
		Axis(const Axis &v)                          = default;
		Axis()                                       = default;
	};

	// Konfiguracja osi
	std::map<std::string, Axis> axes;
	tlinsParametersList         parameters;
	std::string                 path;

	void parseAxes(TiXmlElement *element);
	void parseCommon(TiXmlElement *element);

  public:
	//
	enum class DeviceAngleDirection { SAME = 0, OPOSIT = 1 };

	struct AxisValues {
		double aceleration{0.0};
		double deceleration{0.0};
		double speed{0.0};
		double calibrarionError{0.0};
		bool   deviceReverse{false};

		AxisValues &operator=(const AxisValues &v) = default;
		AxisValues(const AxisValues &v)            = default;
		AxisValues()                               = default;
		virtual ~AxisValues()                      = default;
	};

	enum class AuthType { UNSECURE = 0, SSL = 1, GOOGLE_TOKEN = 2 };

	std::string deviceName;
	double      aceleration;
	double      deceleration;

	bool runStandardInterationWhenNoCorrections;

	unsigned long runFrequency;
	unsigned long firstRunFrequency;
	unsigned long runFrequencyErrorCount;

	unsigned long trackingDeviceSynchronisationFrequency;
	unsigned long trackingSpeedIncrease;

	double earthSpeedRotationErrorX;
	double earthSpeedRotationErrorY;
	double earthSpeedRotationErrorZ;

	double minSpeedPercantage;
	double maxSpeedPercantage;
	double minSpeedCorrection;
	bool   suspendSpeedCorrection;
	bool   reverseSpeedCorrection;
	long   speedModeWaitIterval;
	bool   tracePosition;

	double guiderXSpeed;
	double guiderYSpeed;
	bool   guiderUseRAspeedForDEC;
	bool   timeRotationSign = false; // true > 0, false < 0

	int logLevel;

	unsigned long stopTimeout;

	std::string STAR_APPARENT_PLACE_TYPE;

	std::string connUrlRequestResponse;
	std::string connUrlNotifications;
	std::string connUrlClient;

	std::map<std::string, AxisValues> axesValues;

	void parse();

	explicit tlinsAstroEnginConfiguration(const std::string &path_);
};

#endif
