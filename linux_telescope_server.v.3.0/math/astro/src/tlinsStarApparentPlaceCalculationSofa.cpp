/*
 * tlinsCalculation.cpp
 *
 *  Created on: 5 kwi 2016
 *      Author: jacek
 */

#include <tlinsBacktrace.hpp>
#include <tlinsIERSInfo.hpp>
#include <tlinsStarApparentPlaceCalculationSofa.hpp>
#include <tlins_math.hpp>

#include <memory.h>
#include <sofa.h>
#include <stdio.h>
#include <string>

void toSimpleObjet(const double ra, const double dc, tlinsCoordinate &rac, tlinsCoordinate &dcc)
{
	bool   signra = false;
	double secra  = 0.0;
	char   pmra   = 0;
	int    ira[4];

	bool   signdc = false;
	double secdc  = 0.0;
	char   pmdc   = 0;
	int    idc[4];

	// RA
	::iauA2tf(9, ra, &pmra, ira);
	signra = (pmra == '-') ? true : false;
	secra  = (double) ira[2] + ((double) ira[3]) / 1000000000;

	// DC
	::iauA2af(9, dc, &pmdc, idc);
	signdc = (pmdc == '-') ? true : false;
	secdc  = (double) idc[2] + ((double) idc[3]) / 1000000000;

	rac.set(signra, ira[0], ira[1], secra);
	dcc.set(signdc, idc[0], idc[1], secdc);
}

double pmToRad(const double prMas)
{
	double sec = prMas / 1000.0;
	double rad = sec / 1296000.0 * tlinsMath ::PI_2;
	return rad;
}

double normaliseRh(const double rh)
{
	return rh / 100.0;
}

void tlinsStarApparentPlaceCalculationSofa::toApparent(
    const tlinsAstroObject &ao, const tlinsIERSInfo &ieres,
    std::map<tlinsStarApparentPlaceType, tlinsAstroObjectSimple> &result)
{
	// Mieksce obserwacji
	auto &placeInstance = tlinsObservationPlace::getInstance();

	double elong = placeInstance.getLongitudeRad();
	double phi   = placeInstance.getLatitudeRad();
	double hm    = placeInstance.getHm();

	// Warunki srodowiskowe
	double phpa = tlinsEnvironment::getAmbientPressure();
	double tc   = tlinsEnvironment::getTemperature();
	double rh   = normaliseRh(tlinsEnvironment::getRealHumidity());
	double wl   = tlinsEnvironment::getEffectiveColor();

	// polar motion in radians
	double xp   = ieres.getPmXRad();
	double yp   = ieres.getPmYRad();
	double dut1 = ieres.getDeltaUt();
	double utc1 = tlinsTimeInfo::getInstance().getUtc1();
	double utc2 = tlinsTimeInfo::getInstance().getUtc2();

	// Corrections to IAU
	double dx = ieres.getDxRad();
	double dy = ieres.getDyRad();

	// Star ICRS RA,Dec (radians).
	double rc = ao.getHourAngleRad();
	double dc = ao.getDeclinationRad();

	tlinsCoordinate rac__;
	tlinsCoordinate dcc__;

	toSimpleObjet(rc, dc, rac__, dcc__);

	result[tlinsStarApparentPlaceType::STAR_APPARENT_PLACE_TYPE_ICRS_TO_J2000] =
	    tlinsAstroObjectSimple(rac__, dcc__, rc, dc); // (toSimpleObjet(rc, dc));

	// Proper motion: RA/Dec derivatives, epoch J2000.0.

	double pr = ::atan2(ao.getProperMotionRA() * DAS2R / 1000.0,
	                    cos(dc));                        // double pr = atan2(ao.getProperMotionRARad(), cos(dc));
	double pd = ao.getProperMotionDC() * DAS2R / 1000.0; // double pd = ao.getProperMotionDCRad();

	// Parallax (arcsec) and recession speed (km/s).
	double px = ao.getParallax();
	double rv = ao.getRadialVelocity();

	// Czas
	double tt1 = tlinsTimeInfo::getInstance().getTt1();
	double tt2 = tlinsTimeInfo::getInstance().getTt2();

	// ICRS to CIRS (geocentric observer).
	double ri = 0.0;
	double di = 0.0;
	double eo = 0.0;
	::iauAtci13(rc, dc, pr, pd, px, rv, tt1, tt2, &ri, &di, &eo);

	toSimpleObjet(ri, di, rac__, dcc__);
	result[tlinsStarApparentPlaceType::STAR_APPARENT_PLACE_TYPE_ICRS_TO_CIRS] = tlinsAstroObjectSimple(rac__, dcc__, ri, di);

	// CIRS to ICRS (astrometric).
	double rca = 0.0;
	double dca = 0.0;
	::iauAtic13(ri, di, tt1, tt2, &rca, &dca, &eo);
	toSimpleObjet(rca, dca, rac__, dcc__);

	result[tlinsStarApparentPlaceType::STAR_APPARENT_PLACE_TYPE_CIRS_TO_ICRS_ASTROMETRIC] = tlinsAstroObjectSimple(rac__, dcc__, rca, dca);

	// ICRS (astrometric) to CIRS (geocentric observer).
	::iauAtci13(rca, dca, 0.0, 0.0, 0.0, 0.0, tt1, tt2, &ri, &di, &eo);

	toSimpleObjet(ri, di, rac__, dcc__);
	result[tlinsStarApparentPlaceType::STAR_APPARENT_PLACE_TYPE_ICRS_ASTRONMETRIC_TO_CIRS_GEOCENTRIC] = tlinsAstroObjectSimple(rac__, dcc__, ri, di);

	// Apparent place.
	double ra = ::iauAnp(ri - eo);
	double da = di;

	toSimpleObjet(ra, da, rac__, dcc__);
	result[tlinsStarApparentPlaceType::STAR_APPARENT_PLACE_TYPE_GEOCENTRIC_APPARENT] = tlinsAstroObjectSimple(rac__, dcc__, ra, da);

	/* CIRS to topocentric. */
	double aot = 0.0;
	double zot = 0.0;
	double hot = 0.0;
	double dot = 0.0;
	double rot = 0.0;

	if (::iauAtio13(ri, di, utc1, utc2, dut1, elong, phi, hm, xp, yp, 0.0, 0.0, 0.0, 0.0, &aot, &zot, &hot, &dot, &rot)) {
		__THROW__(tlinsAstroException(std::string("Error calculate apparant position"), tlinsAstroException::ASTRO_ERROR_APPARANT_POSITION));
	}

	double aob = 0.0;
	double zob = 0.0;
	double hob = 0.0;
	double dob = 0.0;
	double rob = 0.0;

	/* CIRS to observed. */
	if (::iauAtio13(ri, di, utc1, utc2, dut1, elong, phi, hm, xp, yp, phpa, tc, rh, wl, &aob, &zob, &hob, &dob, &rob)) {
		__THROW__(tlinsAstroException(std::string("Error calculate CIRS to observed"), tlinsAstroException::ASTRO_ERROR_APPARANT_POSITION));
	}
	toSimpleObjet(rob, dob, rac__, dcc__);

	result[tlinsStarApparentPlaceType::STAR_APPARENT_PLACE_TYPE_CIRS_TO_OBSERVED] = tlinsAstroObjectSimple(rac__, dcc__, rob, dob);

	// ICRS to observed.
	if (::iauAtco13(rc, dc, pr, pd, px, rv, utc1, utc2, dut1, elong, phi, hm, xp, yp, phpa, tc, rh, wl, &aob, &zob, &hob, &dob, &rob, &eo)) {
		__THROW__(tlinsAstroException(std::string("Error calculate ICRS to observed"), tlinsAstroException::ASTRO_ERROR_APPARANT_POSITION));
	}
	toSimpleObjet(rob, dob, rac__, dcc__);

	result[tlinsStarApparentPlaceType::STAR_APPARENT_PLACE_TYPE_ICRS_TO_OBSERVED] = tlinsAstroObjectSimple(rac__, dcc__, rob, dob);
}

void tlinsStarApparentPlaceCalculationSofa::toApparent(
    const double ra_, const double dec_, const tlinsAstroObject &ao, const tlinsIERSInfo &ieres,
    std::map<tlinsStarApparentPlaceType, tlinsAstroObjectSimple> &result)
{
	// Mieksce obserwacji
	auto &placeInstance = tlinsObservationPlace::getInstance();

	double elong = placeInstance.getLongitudeRad();
	double phi   = placeInstance.getLatitudeRad();
	double hm    = placeInstance.getHm();

	// Warunki srodowiskowe
	double phpa = tlinsEnvironment::getAmbientPressure();
	double tc   = tlinsEnvironment::getTemperature();
	double rh   = normaliseRh(tlinsEnvironment::getRealHumidity());
	double wl   = tlinsEnvironment::getEffectiveColor();

	// polar motion in radians
	double xp   = ieres.getPmXRad();
	double yp   = ieres.getPmYRad();
	double dut1 = ieres.getDeltaUt();
	double utc1 = tlinsTimeInfo::getInstance().getUtc1();
	double utc2 = tlinsTimeInfo::getInstance().getUtc2();

	// Corrections to IAU
	double dx = ieres.getDxRad();
	double dy = ieres.getDyRad();

	// Star ICRS RA,Dec (radians).
	double rc = ra_;
	double dc = dec_;

	tlinsCoordinate rac__;
	tlinsCoordinate dcc__;

	toSimpleObjet(rc, dc, rac__, dcc__);

	result[tlinsStarApparentPlaceType::STAR_APPARENT_PLACE_TYPE_ICRS_TO_J2000] = tlinsAstroObjectSimple(rac__, dcc__, rc, dc);

	// Proper motion: RA/Dec derivatives, epoch J2000.0.

	double pr = ::atan2(ao.getProperMotionRA() * DAS2R / 1000.0, cos(dc));
	double pd = ao.getProperMotionDC() * DAS2R / 1000.0;

	// Parallax (arcsec) and recession speed (km/s).
	double px = ao.getParallax();
	double rv = ao.getRadialVelocity();

	// Czas
	double tt1 = tlinsTimeInfo::getInstance().getTt1();
	double tt2 = tlinsTimeInfo::getInstance().getTt2();

	// ICRS to CIRS (geocentric observer).
	double ri = 0.0;
	double di = 0.0;
	double eo = 0.0;
	::iauAtci13(rc, dc, pr, pd, px, rv, tt1, tt2, &ri, &di, &eo);

	toSimpleObjet(ri, di, rac__, dcc__);
	result[tlinsStarApparentPlaceType::STAR_APPARENT_PLACE_TYPE_ICRS_TO_CIRS] = tlinsAstroObjectSimple(rac__, dcc__, ri, di);

	// CIRS to ICRS (astrometric).
	double rca = 0.0;
	double dca = 0.0;
	::iauAtic13(ri, di, tt1, tt2, &rca, &dca, &eo);
	toSimpleObjet(rca, dca, rac__, dcc__);

	result[tlinsStarApparentPlaceType::STAR_APPARENT_PLACE_TYPE_CIRS_TO_ICRS_ASTROMETRIC] = tlinsAstroObjectSimple(rac__, dcc__, rca, dca);

	// ICRS (astrometric) to CIRS (geocentric observer).
	::iauAtci13(rca, dca, 0.0, 0.0, 0.0, 0.0, tt1, tt2, &ri, &di, &eo);

	toSimpleObjet(ri, di, rac__, dcc__);
	result[tlinsStarApparentPlaceType::STAR_APPARENT_PLACE_TYPE_ICRS_ASTRONMETRIC_TO_CIRS_GEOCENTRIC] = tlinsAstroObjectSimple(rac__, dcc__, ri, di);

	// Apparent place.
	double ra = ::iauAnp(ri - eo);
	double da = di;

	toSimpleObjet(ra, da, rac__, dcc__);
	result[tlinsStarApparentPlaceType::STAR_APPARENT_PLACE_TYPE_GEOCENTRIC_APPARENT] = tlinsAstroObjectSimple(rac__, dcc__, ra, da);

	/* CIRS to topocentric. */
	double aot = 0.0;
	double zot = 0.0;
	double hot = 0.0;
	double dot = 0.0;
	double rot = 0.0;

	if (::iauAtio13(ri, di, utc1, utc2, dut1, elong, phi, hm, xp, yp, 0.0, 0.0, 0.0, 0.0, &aot, &zot, &hot, &dot, &rot)) {
		__THROW__(tlinsAstroException(std::string("Error calculate apparant position"), tlinsAstroException::ASTRO_ERROR_APPARANT_POSITION));
	}

	double aob = 0.0;
	double zob = 0.0;
	double hob = 0.0;
	double dob = 0.0;
	double rob = 0.0;

	/* CIRS to observed. */
	if (::iauAtio13(ri, di, utc1, utc2, dut1, elong, phi, hm, xp, yp, phpa, tc, rh, wl, &aob, &zob, &hob, &dob, &rob)) {
		__THROW__(tlinsAstroException(std::string("Error calculate CIRS to observed"), tlinsAstroException::ASTRO_ERROR_APPARANT_POSITION));
	}
	//	reprd("CIRS -> observed:", rob, dob);
	toSimpleObjet(rob, dob, rac__, dcc__);

	result[tlinsStarApparentPlaceType::STAR_APPARENT_PLACE_TYPE_CIRS_TO_OBSERVED] = tlinsAstroObjectSimple(rac__, dcc__, rob, dob);

	// ICRS to observed.
	if (::iauAtco13(rc, dc, pr, pd, px, rv, utc1, utc2, dut1, elong, phi, hm, xp, yp, phpa, tc, rh, wl, &aob, &zob, &hob, &dob, &rob, &eo)) {
		__THROW__(tlinsAstroException(std::string("Error calculate ICRS to observed"), tlinsAstroException::ASTRO_ERROR_APPARANT_POSITION));
	}

	toSimpleObjet(rob, dob, rac__, dcc__);

	result[tlinsStarApparentPlaceType::STAR_APPARENT_PLACE_TYPE_ICRS_TO_OBSERVED] = tlinsAstroObjectSimple(rac__, dcc__, rob, dob);
}

void tlinsStarApparentPlaceCalculationSofa::toCatalog(const std::shared_ptr<tlinsObservationPlace> &op,
                                                      const tlinsAstroObject &aao, const tlinsEnvironment &env,
                                                      const tlinsTimeInfo &                 time,
                                                      const std::shared_ptr<tlinsIERSInfo> &ieres,
                                                      const std::string &catalog, tlinsAstroObject &out_obj)
{
	// TODO
}
