#ifndef __tlinsObservationPlace_hpp__
#define __tlinsObservationPlace_hpp__

#include <tlinsAstroException.hpp>
#include <tlinsBacktrace.hpp>
#include <tlinsCoordinate.hpp>

class tlinsObservationPlace {
  private:
	tlinsCoordinate longitude;
	tlinsCoordinate latitude;

	// height above the geoid
	double hm{0.0};

	double longitudeRad{0.0};
	double latitudeRad{0.0};

	double u{0.0};
	double v{0.0};

  public:
	enum class ElipsoideType { WGS_84 = 1, GRS_80 = 2, WGS_72 = 3 };

  private:
	ElipsoideType elipsoidType{ElipsoideType::WGS_84};

	tlinsObservationPlace() = default;

  public:
	static tlinsObservationPlace &getInstance()
	{
		static tlinsObservationPlace instance;
		return instance;
	}

	double getU() const
	{
		return u;
	}

	double getV() const
	{
		return v;
	}

	ElipsoideType getEllipsoidType() const
	{
		return elipsoidType;
	}

	void setEllipsoidType(const ElipsoideType &v)
	{
		elipsoidType = v;
	}

	double getLatitudeRad() const
	{
		return latitudeRad;
	}

	double getLongitudeRad() const
	{
		return longitudeRad;
	}

	double getHm() const
	{
		return hm;
	}

	void setHm(const double &v)
	{
		hm = v;
	}

	tlinsCoordinate &getLatitude()
	{
		return latitude;
	}

	void setLatitude(const tlinsCoordinate &v);

	tlinsCoordinate &getLongitude()
	{
		return longitude;
	}

	void setLongitude(const tlinsCoordinate &v);
	void calculate();
};

#endif
