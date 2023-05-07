#ifndef __tlinsAstroException_hpp__
#define __tlinsAstroException_hpp__

#include <tlinsException.hpp>

class tlinsAstroException : public tlinsException {
  public:
	// Bledy zwiazane z wyliczaniem czasu
	static const int ASTRO_ERROR_OTHER     = -1100000;
	static const int ASTRO_ERROR_NO_TARGET = -1100001;

	static const int ASTRO_ERROR_DATE_UTC1_UTC2 = -1000000;
	static const int ASTRO_ERROR_DATE_TT        = -1000001;
	static const int ASTRO_ERROR_DATE_CATION    = -1000002;
	static const int ASTRO_ERROR_DATE_UT        = -1000003;
	static const int ASTRO_ERROR_DATE_TCG       = -1000004;
	static const int ASTRO_ERROR_DATE_TCB       = -1000005;
	static const int ASTRO_ERROR_DATE_JULIAN    = -1000006;
	static const int ASTRO_ERROR_DATE_GET_TIME  = -1000008;

	// Bledy zwiazane z wyznaczaniem pozycji
	static const int ASTRO_ERROR_POSITION          = -1001001;
	static const int ASTRO_ERROR_APPARANT_POSITION = -1001002;

	static const int ASTRO_ERROR_ENGINE_STATE       = -1002002;
	static const int ASTRO_ERROR_ENGINE_CALIBARTION = -1002003;
	static const int ASTRO_ERROR_ENGINE_MODE        = -1002004;

	static const int ASTRO_ERROR_READ_DEVICE_POSITION     = -1002005;
	static const int ASTRO_ERROR_NO_VELOCITY_MEASURMENTS  = -1002006;
	static const int ASTRO_ERROR_READ_CONFGIRATION        = -1002007;
	static const int ASTRO_ERROR_MOVE_REQUEST             = -1002008;
	static const int ASTRO_ERROR_ITERATION                = -1002009;
	static const int ASTRO_ERROR_READ_DEVICE_CONFGIRATION = -1002007;

	// Blad ustawienia trybu pracy
	static const int ASTRO_ERROR_INVALID_MODE = -1002008;

	static const int ASTRO_ERROR_READ_STATE    = -1002009;
	static const int ASTRO_ERROR_RESTORE_STATE = -1002010;

	static const int ASTRO_ERROR_INIT_ASTRO_ENGINE = -1002011;
	static const int ASTRO_ERROR_START_TRACKING    = -1002012;
	static const int ASTRO_ERROR_STOP_TRACKING     = -1002012;
	static const int ASTRO_ERROR_SET_TARGET        = -1002013;
	static const int ASTRO_ERROR_SET_ENVIRONMENT   = -1002014;

	static const int ASTRO_ERROR_SET_TRACKING_STATUS = -1002015;

	static const int ASTRO_ERROR_GUIDER_PENDING_CORRECTION = -1003000;

	tlinsAstroException(const char *errorMsg, const int errorId) : tlinsException(std::string(errorMsg), errorId)
	{
	}

	tlinsAstroException(const std::string &errorMsg, int const errorId) : tlinsException(errorMsg, errorId)
	{
	}
};

#endif
