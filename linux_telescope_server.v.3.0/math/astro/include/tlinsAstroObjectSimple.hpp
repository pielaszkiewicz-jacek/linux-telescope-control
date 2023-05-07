#ifndef __tlinsAstroObjectSimple_hpp__
#define __tlinsAstroObjectSimple_hpp__

#include <string>
#include <tlinsAstroException.hpp>
#include <tlinsCoordinate.hpp>

class tlinsAstroObjectSimple {
  private:
	// Deklinacja
	tlinsCoordinate declination;

	// Kat godzinowy
	tlinsCoordinate hourAngle;

	double hourAngleRad{0.0};
	double declinationRad{0.0};

	void calculate();

  public:
	tlinsAstroObjectSimple &operator=(const tlinsAstroObjectSimple &v) = default;

	void                   set(const tlinsCoordinate &ra, const tlinsCoordinate &dc);
	const tlinsCoordinate &getDeclination() const;
	const tlinsCoordinate &getHourAngle() const;

	double getDeclinationRad() const;
	double getHourAngleRad() const;

	tlinsAstroObjectSimple();
	tlinsAstroObjectSimple(const tlinsAstroObjectSimple &v) = default;
	tlinsAstroObjectSimple(const tlinsCoordinate &ra, const tlinsCoordinate &dc, const double rar, const double dar);
	virtual ~tlinsAstroObjectSimple() = default;
};

#endif
