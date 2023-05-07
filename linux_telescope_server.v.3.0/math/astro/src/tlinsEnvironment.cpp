#include <tlinsBacktrace.hpp>
#include <tlinsEnvironment.hpp>

// Cisnienie atmosferyczne (HPa)
double tlinsEnvironment::ambientPressure = 0.0;

// Temperatura
double tlinsEnvironment::temperature = 0.0;

// Wilgotnosc
double tlinsEnvironment::realHumidity = 0.0;

// Efektywny kolor
double tlinsEnvironment::effectiveColor = 0.0;

double tlinsEnvironment::getAmbientPressure()
{
	return ambientPressure;
}

void tlinsEnvironment::setAmbientPressure(double v)
{
	ambientPressure = v;
}

double tlinsEnvironment::getRealHumidity()
{
	return realHumidity;
}

void tlinsEnvironment::setRealHumidity(double v)
{
	realHumidity = v;
}

double tlinsEnvironment::getTemperature()
{
	return temperature;
}

void tlinsEnvironment::setTemperature(double v)
{
	temperature = v;
}

double tlinsEnvironment::getEffectiveColor()
{
	return effectiveColor;
}

void tlinsEnvironment::setEffectiveColor(double v)
{
	effectiveColor = v;
}
