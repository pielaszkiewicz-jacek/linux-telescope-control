#ifndef __tlinsParametersException_hpp__
#define __tlinsParametersException_hpp__

#include <string>

#include <tlinsException.hpp>

/*
 * ----------------------------------------------------------------
 *
 * Definicja klasy wyjatku zwiaznej z przetwarzaniem pliku konfiguracyjnego
 *
 * ----------------------------------------------------------------
 */
class tlinsParametersException : public tlinsException {
  private:
	std::string parameterName;
	std::string excParameterError;

  public:
	static const int XML_CONFIGURATION_UKNOW_SECTION                 = -20001;
	static const int XML_CONFIGURATION_NO_DEVICEFILE_PARAMETER       = -20002;
	static const int XML_CONFIGURATION_NO_VALUE                      = -20003;
	static const int XML_CONFIGURATION_NOTEXT_VALUE                  = -20004;
	static const int XML_CONFIGURATION_ERROR_CONVERT_TO_INT          = -20005;
	static const int XML_CONFIGURATION_ERROR_CONVERT_TO_UINT         = -20006;
	static const int XML_CONFIGURATION_ERROR_CONVERT_TO_LONG         = -20007;
	static const int XML_CONFIGURATION_ERROR_CONVERT_TO_ULONG        = -20008;
	static const int XML_CONFIGURATION_ERROR_CONVERT_TO_SHORT        = -20009;
	static const int XML_CONFIGURATION_ERROR_CONVERT_TO_USHORT       = -20010;
	static const int XML_CONFIGURATION_ERROR_CONVERT_TO_CHAR         = -20011;
	static const int XML_CONFIGURATION_ERROR_CONVERT_TO_UCHAR        = -20012;
	static const int XML_CONFIGURATION_ERROR_CONVERT_TO_DOUBLE       = -20013;
	static const int XML_CONFIGURATION_UKNOW_PARAMETER               = -20014;
	static const int XML_CONFIGURATION_DUPLICATED_DEVICE             = -20015;
	static const int XML_CONFIGURATION_OUT_OFF_INDEX_RANGE           = -20016;
	static const int XML_CONFIGURATION_UNKNOW_WAVE_TABLE_SOURCE      = -20018;
	static const int XML_CONFIGURATION_NO_MANDATORY_TAG              = -20019;
	static const int XML_CONFIGURATION_INCORRECT_WAVE_VALUES_COUNT   = -20020;
	static const int XML_CONFIGURATION_DUPLICATED_RAMP_CONFIGURATION = -20021;

  public:
	std::string &getParameterName(void);
	std::string &reportErrorMessage(void);
	tlinsParametersException(const std::string &errorMessage, const int errorID, const std::string &paraName);
};


#endif
