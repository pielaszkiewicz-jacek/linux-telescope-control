/*
 * tlinsEnvironment.hpp
 *
 *  Created on: 5 kwi 2016
 *      Author: jacek
 */

#ifndef __tlinsEnvironment_hpp__
#define __tlinsEnvironment_hpp__

class tlinsEnvironment {
  private:
	/* Ambient pressure (HPa), temperature (C) and rel. humidity (frac). */

	// Cisnienie atmosferyczne (HPa)
	static double ambientPressure;

	// Temperatura
	static double temperature;

	// Wilgotnosc
	static double realHumidity;

	// Efektywny kolor
	static double effectiveColor;

  public:
	static double getAmbientPressure();
	static void   setAmbientPressure(double v);
	static double getRealHumidity();
	static void   setRealHumidity(double v);
	static double getTemperature();
	static void   setTemperature(double v);
	static double getEffectiveColor();
	static void   setEffectiveColor(double v);
};


#endif
