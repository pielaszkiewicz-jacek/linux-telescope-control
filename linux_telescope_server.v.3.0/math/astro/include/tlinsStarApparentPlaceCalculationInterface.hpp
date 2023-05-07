/*
 * tlinsCalculation.hpp
 *
 *  Created on: 5 kwi 2016
 *      Author: jacek
 */

#ifndef __tlinsStarApparentPlaceCalculationInterface_hpp__
#define __tlinsStarApparentPlaceCalculationInterface_hpp__

#include <tlinsAstroException.hpp>
#include <tlinsAstroObject.hpp>
#include <tlinsEnvironment.hpp>
#include <tlinsObservationPlace.hpp>
#include <tlinsPolarMotion.hpp>
#include <tlinsTimeInfo.hpp>

class tlinsStarApparentPlaceCalculationInterface {
  public:
	virtual void toApparent(const tlinsObservationPlace &op,  // Miejsce obserwacji
	                        const tlinsAstroObject      &ao,  // Katalogowe wspólrzedne obiektu
	                        const tlinsEnvironment      &env, // Warunki srodowiskowe
	                        const tlinsTimeInfo         &t,   // Czas
	                        const tlinsPolarMotion      &po,  // Polar motion
	                        tlinsAstroObject            &out_obj) = 0;

	virtual void toCatalog(const tlinsObservationPlace &op,      // Miejsce obserwacji
	                       const tlinsAstroObject      &aao,     // Obserwacyjne wspólrzedne obiektu
	                       const tlinsEnvironment      &env,     // Warunki srodowiskowe
	                       const tlinsTimeInfo         &t,       // Czas
	                       const tlinsPolarMotion      &po,      // Polar motion
	                       const std::string           &catalog, // Typ katalogu
	                       tlinsAstroObject            &out_obj) = 0;

	virtual ~tlinsStarApparentPlaceCalculationInterface()
	{
	}
};

#endif
