#include <parameters/tlinsGlobalParametersList.hpp>
#include <parameters/tlinsSystemParametersList.hpp>
#include <tlinsBacktrace.hpp>


// ----------------------------------------------------------------
// ----------------------------------------------------------------

tlinsParametersList &tlinsGlobalParametersList::getParameters()
{
	return tlinsGlobalParametersList::parameters;
}

// ----------------------------------------------------------------
// ----------------------------------------------------------------

tlinsParametersList &tlinsSystemParametersList::getParameters()
{
	return tlinsSystemParametersList::parameters;
}
