
#include <tlinsAstroObjectSimple.hpp>
#include <tlinsBacktrace.hpp>

#include <iostream>
#include <sofa.h>

double tlinsAstroObjectSimple::getDeclinationRad() const
{
	return declinationRad;
}

double tlinsAstroObjectSimple::getHourAngleRad() const
{
	return hourAngleRad;
}

void tlinsAstroObjectSimple::calculate()
{
	if (::iauTf2a(hourAngle.getSign(), hourAngle.getDegris(), hourAngle.getMinutes(), hourAngle.getSeconds(),
	              &hourAngleRad)) {
		__THROW__(
		    tlinsAstroException(std::string("Error calculate hour angle"), tlinsAstroException::ASTRO_ERROR_POSITION));
	}

	if (::iauAf2a(declination.getSign(), declination.getDegris(), declination.getMinutes(), declination.getSeconds(),
	              &declinationRad)) {
		__THROW__(
		    tlinsAstroException(std::string("Error calculate declination"), tlinsAstroException::ASTRO_ERROR_POSITION));
	}
}

const tlinsCoordinate &tlinsAstroObjectSimple::getDeclination() const
{
	return declination;
}

const tlinsCoordinate &tlinsAstroObjectSimple::getHourAngle() const
{
	return hourAngle;
}

void tlinsAstroObjectSimple::set(const tlinsCoordinate &ra, const tlinsCoordinate &dc)
{
	hourAngle   = ra;
	declination = dc;
	calculate();
}

tlinsAstroObjectSimple::tlinsAstroObjectSimple() : declination(false, 0, 0, 0.0), hourAngle(false, 0, 0, 0.0)
{
}

tlinsAstroObjectSimple::tlinsAstroObjectSimple(const tlinsCoordinate &ra, const tlinsCoordinate &dc, const double rar,
                                               const double dcr)
    : declination{dc}, hourAngle{ra}, hourAngleRad{rar}, declinationRad{dcr}

{
}
