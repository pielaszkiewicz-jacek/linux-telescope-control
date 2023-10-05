#include <tlinsLogger.hpp>
#include <tlinsObservationPlace.hpp>

#include <array>
#include <iostream>
#include <sofa.h>


void tlinsObservationPlace::setLatitude(const tlinsCoordinate &v)
{
	latitude = v;
	calculate();
}

void tlinsObservationPlace::setLongitude(const tlinsCoordinate &v)
{
	longitude = v;
	calculate();
}

void tlinsObservationPlace::calculate()
{
	/* Site longitude, latitude (radians) and height above the geoid (m). */
	// Site longitude
	if (::iauAf2a(longitude.getSign(), longitude.getDegris(), longitude.getMinutes(), longitude.getSeconds(),
	              &longitudeRad)) {
		__THROW__(
		    tlinsAstroException(std::string("Error calculate position"), tlinsAstroException::ASTRO_ERROR_POSITION));
	}

	// Site latitude
	if (::iauAf2a(latitude.getSign(), latitude.getDegris(), latitude.getMinutes(), latitude.getSeconds(),
	              &latitudeRad)) {
		__THROW__(
		    tlinsAstroException(std::string("Error calculate position"), tlinsAstroException::ASTRO_ERROR_POSITION));
	}

	std::array<double, 3> xyz;
	if (::iauGd2gc((int) elipsoidType, tlinsObservationPlace::longitudeRad, tlinsObservationPlace::latitudeRad,
	               tlinsObservationPlace::hm, xyz.data())) {
		__THROW__(
		    tlinsAstroException(std::string("Error calculate position"), tlinsAstroException::ASTRO_ERROR_POSITION));
	}

	u = ::sqrt(xyz[0] * xyz[0] + xyz[1] * xyz[1]);
	v = xyz[2];
}
