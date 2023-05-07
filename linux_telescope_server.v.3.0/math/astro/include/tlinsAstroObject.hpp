#ifndef __tlinsAstroObject_hpp__
#define __tlinsAstroObject_hpp__

#include <string>
#include <tlinsAstroException.hpp>
#include <tlinsCoordinate.hpp>

class tlinsAstroObject {
  private:
	// Deklinacja
	tlinsCoordinate declination;

	// Kat godzinowy
	tlinsCoordinate hourAngle;

	// Ruch wlasny
	double properMotionRA;
	double properMotionDC;

	// Paralaxa
	double parallax;

	// Predkosc radialna
	double radialVelocity{0.0};

	// Nawa katalogu
	std::string catalogType{""};

	double hourAngleRad{0.0};
	double declinationRad{0.0};
	double properMotionRARad{0.0};
	double properMotionDCRad{0.0};
	void   calculate();

  public:
	tlinsAstroObject &operator=(const tlinsAstroObject &v) = default;

	void               setCatalogType(const std::string &v);
	const std::string &getCatalogType() const;

	void                   set(const tlinsCoordinate &ra, const tlinsCoordinate &dc);
	const tlinsCoordinate &getDeclination() const;
	const tlinsCoordinate &getHourAngle() const;

	void   setParallax(const double v);
	double getParallax() const;

	void   setProperMotion(double ra, double dc);
	double getProperMotionRA() const;
	double getProperMotionDC() const;

	void   setRadialVelocity(const double v);
	double getRadialVelocity() const;

	double getDeclinationRad() const;
	double getHourAngleRad() const;
	double getProperMotionRARad() const;
	double getProperMotionDCRad() const;

	tlinsAstroObject()                          = default;
	tlinsAstroObject(const tlinsAstroObject &v) = default;
	virtual ~tlinsAstroObject()                 = default;
};

#endif
