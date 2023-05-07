
#include <parameters/tlinsParametersException.hpp>
#include <tlinsBacktrace.hpp>

//
// ---------------------------------
// ---------------------------------
//

tlinsParametersException::tlinsParametersException(const std::string &errorMessage, const int errorID,
                                                   const std::string &paraName)
    : tlinsException(errorMessage, errorID), parameterName(paraName)
{
}

std::string &tlinsParametersException::getParameterName(void)
{
	return parameterName;
}

std::string &tlinsParametersException::reportErrorMessage(void)
{
	char errIDStr[100];

	sprintf(errIDStr, "%d", getErrorID());

	excParameterError = "Error ID = ";
	excParameterError += errIDStr;
	excParameterError += "; Parameter name = ";
	excParameterError += parameterName;
	excParameterError += "; Error details = ";
	excParameterError += getErrorMessage();

	return excParameterError;
}
