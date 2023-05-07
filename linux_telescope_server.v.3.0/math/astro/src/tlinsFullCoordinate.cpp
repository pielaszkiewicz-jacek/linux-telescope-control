#include <tlinsFullCoordinate.hpp>
#include <tlinsLogger.hpp>

#include <iostream>
#include <sofa.h>

void tlinsFullCoordinate::setLatitude(const tlinsCoordinate &v)
{
	latitude = v;
	calculate();
}

void tlinsFullCoordinate::setLongitude(const tlinsCoordinate &v)
{
	longitude = v;
	calculate();
}

void tlinsFullCoordinate::calculate()
{
	/* Site longitude, latitude (radians) and height above the geoid (m). */
	// Site longitude
	if (::iauAf2a(longitude.getSign(), longitude.getDegris(), longitude.getMinutes(), longitude.getSeconds(), &longitudeRad)) {
		__THROW__(tlinsAstroException(std::string("Error calculate position"), tlinsAstroException::ASTRO_ERROR_POSITION));
	}

	// Site latitude
	if (::iauAf2a(latitude.getSign(), latitude.getDegris(), latitude.getMinutes(), latitude.getSeconds(), &latitudeRad)) {
		__THROW__(tlinsAstroException(std::string("Error calculate position"), tlinsAstroException::ASTRO_ERROR_POSITION));
	}
}
