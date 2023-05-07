#ifndef __tlinsConfigurationParser_hpp__
#define __tlinsConfigurationParser_hpp__

#include <string>

#include <parameters/tlinsParametersException.hpp>
#include <parameters/tlinsParametersList.hpp>
#include <tlinsXMLParser.hpp>

/*
 * ---------------------------------------------------------------------------
 * Klasa parsera
 * ---------------------------------------------------------------------------
 */

class tlinsConfigurationParser {
  private:
	static void parsDevices(TiXmlElement *element);
	static void parsMapping(TiXmlElement *element);
	static void parsGlobalParameters(TiXmlElement *element);
	static void parsSystemParameters(TiXmlElement *element);

  public:
	static void parse(const std::string &file);
};


#endif
