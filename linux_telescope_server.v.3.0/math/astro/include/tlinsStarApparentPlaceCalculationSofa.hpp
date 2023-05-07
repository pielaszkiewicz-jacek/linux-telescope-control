/*
 * tlinsCalculation.hpp
 *
 *  Created on: 5 kwi 2016
 *      Author: jacek
 */

#ifndef __tlinsStarApparentPlaceCalculationSofa_hpp__
#define __tlinsStarApparentPlaceCalculationSofa_hpp__

#include <tlinsAstroException.hpp>
#include <tlinsAstroObject.hpp>
#include <tlinsAstroObjectSimple.hpp>
#include <tlinsEnvironment.hpp>
#include <tlinsIERSInfo.hpp>
#include <tlinsObservationPlace.hpp>
#include <tlinsStarApparentPlaceCalculationInterface.hpp>

#include <map>
#include <memory>

void toSimpleObjet(const double ra, const double dc, tlinsCoordinate &rac, tlinsCoordinate &dcc);

enum class tlinsStarApparentPlaceType : int {
	STAR_APPARENT_PLACE_TYPE_ICRS_TO_J2000                        = 1,
	STAR_APPARENT_PLACE_TYPE_ICRS_TO_CIRS                         = 2,
	STAR_APPARENT_PLACE_TYPE_CIRS_TO_ICRS_ASTROMETRIC             = 3,
	STAR_APPARENT_PLACE_TYPE_ICRS_ASTRONMETRIC_TO_CIRS_GEOCENTRIC = 4,
	STAR_APPARENT_PLACE_TYPE_GEOCENTRIC_APPARENT                  = 5,
	STAR_APPARENT_PLACE_TYPE_CIRS_TO_TOPOCENTRIC                  = 6,
	STAR_APPARENT_PLACE_TYPE_CIRS_TO_OBSERVED                     = 7,
	STAR_APPARENT_PLACE_TYPE_ICRS_TO_OBSERVED                     = 8
};

class tlinsStarApparentPlaceCalculationSofa {
  public:
	static void toApparent(const tlinsAstroObject &ao, const tlinsIERSInfo &ieres,
	                       std::map<tlinsStarApparentPlaceType, tlinsAstroObjectSimple> &result);

	static void toApparent(const double ra, const double dec, const tlinsAstroObject &ao, const tlinsIERSInfo &ieres,
	                       std::map<tlinsStarApparentPlaceType, tlinsAstroObjectSimple> &result);

	virtual void toCatalog(const std::shared_ptr<tlinsObservationPlace> &op, const tlinsAstroObject &aao,
	                       const tlinsEnvironment &env, const tlinsTimeInfo &time,
	                       const std::shared_ptr<tlinsIERSInfo> &ieres, const std::string &catalog,
	                       tlinsAstroObject &out_obj);

	// Konstruktor i destruktor klasy
	tlinsStarApparentPlaceCalculationSofa() = default;

	virtual ~tlinsStarApparentPlaceCalculationSofa() = default;
};

#endif
