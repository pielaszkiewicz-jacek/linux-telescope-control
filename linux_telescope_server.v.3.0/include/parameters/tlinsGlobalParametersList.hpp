#ifndef __tlinsGlobalParametersList_hpp__
#define __tlinsGlobalParametersList_hpp__

#include <parameters/tlinsParametersList.hpp>

/*
 * ---------------------------------------------------------------------------
 * Globalne parametery
 * ---------------------------------------------------------------------------
 */
class tlinsGlobalParametersList {
  private:
	static tlinsParametersList parameters;

  public:
	static tlinsParametersList &getParameters();
};


#endif
