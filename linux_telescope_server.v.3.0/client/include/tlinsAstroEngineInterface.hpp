#ifndef __tlinsAstroEngineInterface_hpp__
#define __tlinsAstroEngineInterface_hpp__

#include <astro.grpc.pb.h>
#include <tlinsBacktrace.hpp>
#include <tlinsInterfaceException.hpp>
#include <tlins_utils.hpp>

#include <array>
#include <cstring>
#include <memory>
#include <string>
#include <vector>

#include <grpc++/channel.h>

class tlinsAstroEngineInterface {
  private:
	std::unique_ptr<tlins::tlinsRpcAstroService::Stub> connectionStub;
	std::string                                        confirmationID;

  public:
	class tlinsCoordinate {
		__ITEM__(bool, sign);
		__ITEM__(int, degris);
		__ITEM__(int, minutes);
		__ITEM__(double, seconds);

	  public:
		tlinsCoordinate &operator=(const tlinsCoordinate &v) = default;
		tlinsCoordinate(const tlinsCoordinate &v)            = default;

		__DEF_CONSTRUCTOR__(tlinsCoordinate);
		__DEF_DESTRUCTOR__(tlinsCoordinate)
	};

	class tlinsAstroObject {
		// Deklinacja
		__ITEM__(tlinsCoordinate, declination);

		// Kat godzinowy
		__ITEM__(tlinsCoordinate, hourAngle);

		// Ruch wlasny
		__ITEM__(double, properMotionRA);
		__ITEM__(double, properMotionDC);

		// Paralaxa
		__ITEM__(double, parallax);

		// Predkosc radialna
		__ITEM__(double, radialVelocity);

		// Nawa katalogu
		__ITEM__(std::string, catalogType);

	  public:
		tlinsAstroObject &operator=(const tlinsAstroObject &v) = default;
		tlinsAstroObject(const tlinsAstroObject &v)            = default;

		__DEF_CONSTRUCTOR__(tlinsAstroObject);
		__DEF_DESTRUCTOR__(tlinsAstroObject)
	};

	enum class tlinsEngineMode { MODE_NONE = 0, MODE_STANDARD = 1, MODE_EXTERNAL_SUPPORT = 2, MODE_STANDARD_SPEED = 3 };

	enum class tlinsEngineStateValue { STATE_CALIBRATION = 0, STATE_CALIBRATION_VELOCITY = 1, STATE_REGULAR = 2 };

	enum class tlinsMultipleModeFinall { SWITCH_TO_STANDARD = 0, SWITCH_TO_EXTERNAL = 1 };

	class tlinsTarget {
		__ITEM__(tlinsAstroObject, object);
		__ITEM__(long, delta);
		__ITEM__(double, speed);
		__ITEM__(double, aceleration);

	  public:
		tlinsTarget &operator=(const tlinsTarget &v) = default;
		tlinsTarget(const tlinsTarget &v)            = default;

		__DEF_CONSTRUCTOR__(tlinsTarget);
		__DEF_DESTRUCTOR__(tlinsTarget)
	};

	class tlinsDevicePosition {
		__ITEM__(long, x);
		__ITEM__(long, xRaw);
		__ITEM__(long, y);
		__ITEM__(long, yRaw);
		__ITEM__(long, xEncoder);
		__ITEM__(long, xEncoderRaw);
		__ITEM__(long, yEncoder);
		__ITEM__(long, yEncoderRaw);

	  public:
		tlinsDevicePosition &operator=(const tlinsDevicePosition &v) = default;
		tlinsDevicePosition(const tlinsDevicePosition &v)            = default;

		__DEF_CONSTRUCTOR__(tlinsDevicePosition);
		__DEF_DESTRUCTOR__(tlinsDevicePosition)
	};

	struct tlinsEngineStateInfo {
	  public:
		using d23array = std::array<std::array<double, 3>, 3>;
		__ITEM__(d23array, attitude);

		// Informacja o pozycji urzadzenia
		__ITEM__(tlinsDevicePosition, devicePosition);

		// Aktualny cel
		__ITEM__(tlinsTarget, currentTarget);

		// Aktualny tryb urzadzenia
		__ITEM__(tlinsEngineMode, mode);

		// Stan urzadzenia
		__ITEM__(tlinsEngineStateValue, state);

		// Tryb multiple
		__ITEM__(tlinsMultipleModeFinall, multipleFinal);

		__ITEM__(bool, xReverse);
		__ITEM__(bool, yReverse);

	  public:
		tlinsEngineStateInfo &operator=(const tlinsEngineStateInfo &v) = default;
		tlinsEngineStateInfo(const tlinsEngineStateInfo &v)            = default;

		__DEF_CONSTRUCTOR__(tlinsEngineStateInfo);
		__DEF_DESTRUCTOR__(tlinsEngineStateInfo);
	};

	class tlinsFullCoordinate {
		__ITEM__(tlinsCoordinate, longitude);
		__ITEM__(tlinsCoordinate, latitude);

	  public:
		tlinsFullCoordinate &operator=(const tlinsFullCoordinate &v) = default;
		tlinsFullCoordinate(const tlinsFullCoordinate &v)            = default;

		__DEF_CONSTRUCTOR__(tlinsFullCoordinate);
		__DEF_DESTRUCTOR__(tlinsFullCoordinate);
	};

	class tlinsMeserment {
		__ITEM__(tlinsAstroObject, reference);

		// Input jest opcionalny. W sytuacji gdy nie jest przekazywany to
		// bedzie odczytywany z urzadzenia
		__ITEM__(tlinsFullCoordinate, input);
		__ITEM__(tlinsFullCoordinate, inputError);
		__ITEM__(double, w);

	  public:
		tlinsMeserment &operator=(const tlinsMeserment &v) = default;
		tlinsMeserment(const tlinsMeserment &v)            = default;

		__DEF_CONSTRUCTOR__(tlinsMeserment);
		__DEF_DESTRUCTOR__(tlinsMeserment);
	};

	class tlinsVelocityMeserment {
		__ITEM__(tlinsFullCoordinate, input);
		__ITEM__(tlinsFullCoordinate, inputError);
		__ITEM__(double, w);

	  public:
		tlinsVelocityMeserment &operator=(const tlinsVelocityMeserment &v) = default;

		tlinsVelocityMeserment(const tlinsVelocityMeserment &v) = default;

		__DEF_CONSTRUCTOR__(tlinsVelocityMeserment);
		__DEF_DESTRUCTOR__(tlinsVelocityMeserment);
	};

	class tlinsEnvironment {
		/* Ambient pressure (HPa), temperature (C) and rel. humidity (frac). */

		// Cisnienie atmosferyczne (HPa)
		__ITEM__(double, ambientPressure);

		// Temperatura
		__ITEM__(double, temperature);

		// Wilgotnosc
		__ITEM__(double, realHumidity);

		// Efektywny kolor
		__ITEM__(double, effectiveColor);

	  public:
		tlinsEnvironment &operator=(const tlinsEnvironment &v) = default;
		tlinsEnvironment(const tlinsEnvironment &v)            = default;

		__DEF_CONSTRUCTOR__(tlinsEnvironment);
		__DEF_DESTRUCTOR__(tlinsEnvironment);
	};

	class tlinsIERS {
		__ITEM__(long, year);
		__ITEM__(long, month);
		__ITEM__(long, day);

		// - Polar motion
		__ITEM__(double, pmX);
		__ITEM__(double, pmY);
		__ITEM__(double, pmXRad);
		__ITEM__(double, pmYRad);

		// - Roiznica czasu UT1-UTC
		__ITEM__(double, deltaUT);

		// - Nutacja
		__ITEM__(double, dPsi);
		__ITEM__(double, dEpsilon);
		__ITEM__(double, dx);
		__ITEM__(double, dy);
		__ITEM__(double, dxRad);
		__ITEM__(double, dyRad);

	  public:
		tlinsIERS &operator=(const tlinsIERS &v) = default;
		tlinsIERS(const tlinsIERS &v)            = default;

		__DEF_CONSTRUCTOR__(tlinsIERS);
		__DEF_DESTRUCTOR__(tlinsIERS);
	};

	class tlinsIERSListItems {
		__ITEM__(bool, localStore);
		__ITEM__(bool, overwrite);

	  private:
		std::vector<tlinsIERS> items;

	  public:
		std::vector<tlinsIERS>::const_iterator begin() const
		{
			return items.cbegin();
		}

		std::vector<tlinsIERS>::const_iterator end() const
		{
			return items.cend();
		}

		void insert(const tlinsIERS &v)
		{
			items.push_back(v);
		}

		std::vector<tlinsIERS> &get()
		{
			return items;
		}

		void add(const class tlinsIERS &v)
		{
			items.push_back(v);
		}

		__DEF_CONSTRUCTOR__(tlinsIERSListItems);
		__DEF_DESTRUCTOR__(tlinsIERSListItems);
	};

	enum class tlinsElipsoideType { WGS_84 = 0, GRS_80 = 1, WGS_72 = 2 };

	class tlinsObservationPlace {
		__ITEM__(tlinsCoordinate, longitude);
		__ITEM__(tlinsCoordinate, latitude);

		// height above the geoid
		__ITEM__(double, hm);
		__ITEM__(tlinsElipsoideType, epType);

	  public:
		tlinsObservationPlace &operator=(const tlinsObservationPlace &v) = default;
		tlinsObservationPlace(const tlinsObservationPlace &v)            = default;

		__DEF_CONSTRUCTOR__(tlinsObservationPlace);
		__DEF_DESTRUCTOR__(tlinsObservationPlace);
	};

	class tlinsCalibrarionStateInfo {
		__ITEM__(tlinsEngineStateValue, engineState);
		__ITEM__(int, iterationCount);
		__ITEM__(bool, isTrackingActive);

	  public:
		tlinsCalibrarionStateInfo(const tlinsCalibrarionStateInfo &v)
		{
			engineState    = v.engineState;
			iterationCount = v.iterationCount;
		};

		tlinsCalibrarionStateInfo &operator=(const tlinsCalibrarionStateInfo &v)
		{
			engineState    = v.engineState;
			iterationCount = v.iterationCount;
			return *this;
		};

		__DEF_CONSTRUCTOR__(tlinsCalibrarionStateInfo);
		__DEF_DESTRUCTOR__(tlinsCalibrarionStateInfo);
	};

  public:
	// Status kalibracli astro
	void getCalibrationState(tlinsCalibrarionStateInfo &response);

	void getState(tlinsEngineStateInfo &response, const bool suspend = true);

	void restoreState(const tlinsEngineStateInfo &request);

	void startTracking();

	void stopTracking();

	// Ustawienie/pobranie aktualnego obiektu docelowego
	void setTarget(const tlinsTarget &request, const bool isDelta = false);
	void getTarget(tlinsTarget &request);

	// Rejestracja pomiaru
	void registerMeserment(const tlinsMeserment &request, const bool hesInput = false);
	void registerMesermentDefered(const tlinsMeserment &request);
	void confirmDeferedMeserment();

	// Zamkniecie kalibracji
	void closeCalibration();

	// Parametery srodfowiska
	void setEnvironment(const tlinsEnvironment &request);

	// Parametery czasu
	void setIERSInfo(const tlinsIERSListItems &request);

	// Ustawienie miesca obserwacji
	void setObservationPlace(const tlinsObservationPlace &request);

	void setMode(const tlinsEngineMode request);

	// Resetowanie kalibracji
	enum class ReverseDevice { DEVICE_SETTINGS = 1, DEVICE_NO_REVERSE = 2, DEVICE_REVERSE = 3 };
	void resetCalibration(
	    const tlinsAstroEngineInterface::ReverseDevice x = tlinsAstroEngineInterface::ReverseDevice::DEVICE_SETTINGS,
	    const tlinsAstroEngineInterface::ReverseDevice y = tlinsAstroEngineInterface::ReverseDevice::DEVICE_SETTINGS);

	// Resetowanie kalibracji
	void setTargetForCurrentPosition(void);

	//
	// Obsluga sledzenia obiektów
	//

	// Ustawienie predkosci sledzenia
	void setTracking(const double ra, const double dec);

	// Zmiana statusu sledzenia
	void setTrackingState(const bool state);

	// Pobranie statusu sledzenia
	void getTrackingState(bool &state, double &ra, double &dec) const;


	// Guider interface
	enum class GuiderStatus { SET = 0, IN_PROGRESS = 1, NO_TARGET = 2, ERROR = 3 };

	GuiderStatus guideNorth(const long interval);
	GuiderStatus guideSounth(const long interval);
	GuiderStatus guideEst(const long interval);
	GuiderStatus guideWest(const long interval);

	void guiderRatioSet(const double ra, const double dec, const bool useRaForDec);
	void guiderRatioGet(double &ra, double &dec, bool &useRaForDec);

	void manualCorrection(double raCorrection, double decCorrection);
	void manualCorrectionReset();
	void manualCorrectionGet(double &raCorrection, double &decCorrection);

	void sync(const double ra, const double dec);

	//
	// Konstruktor destruktor klasy
	//
	tlinsAstroEngineInterface(std::shared_ptr<grpc::Channel> &channel);
	virtual ~tlinsAstroEngineInterface();
};

#endif
