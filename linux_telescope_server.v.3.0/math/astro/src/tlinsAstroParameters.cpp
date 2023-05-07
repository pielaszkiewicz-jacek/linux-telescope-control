#include <tlinsAstroParameters.hpp>
#include <tlinsBacktrace.hpp>

#include <sstream>
#include <string>

std::string tlinsAstroParameters::STAR_APPARENT_PLACE_TYPE                  = "STAR_APPARENT_PLACE_TYPE";
std::string tlinsAstroParameters::STAR_APPARENT_OBJECT_TRACKING_SPEED       = "OBJECT_TRACKING_SPEEDE";
std::string tlinsAstroParameters::STAR_APPARENT_OBJECT_TRACKING_ACELERATION = "OBJECT_TRACKING_ACELERATION";

bool tlinsAstroParameters::setParameter(const std::string &name, const std::string &value, bool over)
{
	return tlinsAstroParameters::astroParameters.setParameter(name, value, over);
}

bool tlinsAstroParameters::getParameterValue(const std::string &name, std::string &val)
{
	return tlinsAstroParameters::astroParameters.getParameterValue(name, val);
}
