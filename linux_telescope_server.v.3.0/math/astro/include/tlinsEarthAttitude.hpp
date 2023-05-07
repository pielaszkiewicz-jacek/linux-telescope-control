#ifndef __tlinsEarthAttitude_hpp__
#define __tlinsEarthAttitude_hpp__

#include <Eigen/Dense>
#include <Eigen/Geometry>
#include <vector>

class tlinsEarthAttitude {
  public:
	enum class AttitudeType {
		IAU_2000A_CIO_BASED                       = 1,
		IAU_2000A_EQUINOX_BASED                   = 2,
		IAU_2006_2000A_CIO_BASED                  = 3,
		IAU_2006_2000A_CIO_BASED_USING_X_Y_SERIES = 4
	};

	struct EarthAttitudeInfo {
		AttitudeType type;

		Eigen::Matrix3d  celestialToTerrestrialMatrixNoPolar;
		Eigen ::Matrix3d celestialToTerrestrialMatrix;
		Eigen ::Matrix3d NPBMatrix;
		double           X;
		double           Y;
		double           s;

		EarthAttitudeInfo()                     = default;
		EarthAttitudeInfo(EarthAttitudeInfo &v) = default;
		EarthAttitudeInfo &operator=(EarthAttitudeInfo &&v) = default;

		EarthAttitudeInfo(const EarthAttitudeInfo &v) = default;
		EarthAttitudeInfo &operator=(const EarthAttitudeInfo &v) = default;
		virtual ~EarthAttitudeInfo()                             = default;
	};

  public:
	// dateTime - UTC
	// result - rezultat
	static int calculateAttitude(const unsigned int year, const unsigned int month, const unsigned int day,
	                             const unsigned int hour, const unsigned int minutes, const double seconds,
	                             std ::vector<EarthAttitudeInfo> &result);
};

#endif