#ifndef __tlinsSystemParametersList_hpp__
#define __tlinsSystemParametersList_hpp__

#include <parameters/tlinsParametersList.hpp>

class tlinsSystemParametersList
{
private:
	static tlinsParametersList parameters;

public:
	static tlinsParametersList &getParameters();
};

#endif
