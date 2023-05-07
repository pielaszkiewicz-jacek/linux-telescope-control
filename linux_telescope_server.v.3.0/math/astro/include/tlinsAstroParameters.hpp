#ifndef _tlinsAstroParameters_hpp_
#define _tlinsAstroParameters_hpp_

#include <string>
#include <tlinsParametersList.hpp>

class tlinsAstroParameters {
  public:
	static std::string STAR_APPARENT_PLACE_TYPE;
	static std::string STAR_APPARENT_OBJECT_TRACKING_SPEED;
	static std::string STAR_APPARENT_OBJECT_TRACKING_ACELERATION;

  private:
	static tlinsParametersList astroParameters;

  public:
	static bool setParameter(const std::string &name, const std::string &value, bool over = false);
	static bool getParameterValue(const std::string &name, std::string &val);
};

#endif
