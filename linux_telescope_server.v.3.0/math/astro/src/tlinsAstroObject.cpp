
#include <tlinsAstroObject.hpp>
#include <tlinsBacktrace.hpp>

#include <iostream>
#include <sofa.h>

double tlinsAstroObject::getDeclinationRad() const
{
	return declinationRad;
}

double tlinsAstroObject::getHourAngleRad() const
{
	return hourAngleRad;
}

double tlinsAstroObject::getProperMotionRARad() const
{
	return properMotionRARad;
}

double tlinsAstroObject::getProperMotionDCRad() const
{
	return properMotionDCRad;
}

void tlinsAstroObject::calculate()
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

	properMotionRARad = properMotionRA * DAS2R;
	properMotionDCRad = properMotionDC * DAS2R;
}

const std::string &tlinsAstroObject::getCatalogType() const
{
	return catalogType;
}

void tlinsAstroObject::setCatalogType(const std::string &v)
{
	catalogType = v;
}

const tlinsCoordinate &tlinsAstroObject::getDeclination() const
{
	return declination;
}

const tlinsCoordinate &tlinsAstroObject::getHourAngle() const
{
	return hourAngle;
}

void tlinsAstroObject::set(const tlinsCoordinate &ra, const tlinsCoordinate &dc)
{
	hourAngle   = ra;
	declination = dc;
	calculate();
}

double tlinsAstroObject::getParallax() const
{
	return parallax;
}

void tlinsAstroObject::setParallax(const double v)
{
	parallax = v;
	calculate();
}

double tlinsAstroObject::getProperMotionRA() const
{
	return properMotionRA;
}

double tlinsAstroObject::getProperMotionDC() const
{
	return properMotionDC;
}

void tlinsAstroObject::setProperMotion(double ra, double dc)
{
	properMotionRA = ra;
	properMotionDC = dc;
	calculate();
}

double tlinsAstroObject::getRadialVelocity() const
{
	return radialVelocity;
}

void tlinsAstroObject::setRadialVelocity(const double v)
{
	radialVelocity = v;
}
