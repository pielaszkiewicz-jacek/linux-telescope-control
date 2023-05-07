#ifndef __tlinsFullCoordinate_hpp__
#define __tlinsFullCoordinate_hpp__

#include <tlinsAstroException.hpp>
#include <tlinsBacktrace.hpp>
#include <tlinsCoordinate.hpp>

class tlinsFullCoordinate {
  private:
	tlinsCoordinate longitude;
	tlinsCoordinate latitude;

	double longitudeRad;
	double latitudeRad;

  public:
	double getLatitudeRad() const
	{
		return latitudeRad;
	}

	double getLongitudeRad() const
	{
		return longitudeRad;
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

	tlinsFullCoordinate &operator=(const tlinsFullCoordinate &v) = default;
	tlinsFullCoordinate(const tlinsFullCoordinate &v)            = default;

	tlinsFullCoordinate(const tlinsCoordinate &lo_, const tlinsCoordinate &la_) : longitude{lo_}, latitude{la_}
	{
		calculate();
	}

	tlinsFullCoordinate() : longitude(false, 0, 0, 0.0), latitude(false, 0, 0, 0.0)
	{
	}

	virtual ~tlinsFullCoordinate() = default;
};

#endif
