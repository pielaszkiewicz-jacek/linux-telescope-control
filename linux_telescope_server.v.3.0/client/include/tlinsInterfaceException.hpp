#ifndef __tlinsInterfaceException_hpp__
#define __tlinsInterfaceException_hpp__

#include <tlinsException.hpp>

class tlinsInterfaceException : public tlinsException {
  public:
	static const int SUCCESS                     = 0;
	static const int ERROR_REGISTER_CONFIRMATION = -1;
	static const int ERROR_RPC_ERROR             = -2;


	static const int ERROR_CLIENT_CHANNEL_START           = -200000;
	static const int ERROR_CLIENT_ONLY_SERVER_CAN_PUBLISH = -200001;
	static const int ERROR_CLIENT_ONLY_CLIENT_CAN_CONSUME = -200002;
	static const int ERROR_CLIENT_SERIALISATION           = -200003;
	static const int ERROR_CLIENT_DESERIALISATION         = -200004;
	static const int ERROR_CLIENT_SEND_MESSAGE            = -200005;
	static const int ERROR_CLIENT_CHANNEL_NOT_READY       = -200006;
	static const int ERROR_CLIENT_MESSAGE_PARS_ERROR      = -200007;

	static const int ERROR_CLIENT_MESSAGE_SYNTAX_ERROR = -200008;

	static const int ERROR_CLIENT_MSG_SERIALISE           = -200009;
	static const int ERROR_CLIENT_MSG_DESERIALISE         = -200010;
	static const int ERROR_CLIENT_POLL_ERROR              = -200011;
	static const int ERROR_CLIENT_RECEIVE_ERROR           = -200012;
	static const int ERROR_CLIENT_NO_INPUT_MESSAGE        = -200013;
	static const int ERROR_CLIENT_INCORRECT_MESSAGE_TYPE  = -200014;
	static const int ERROR_CLIENT_INCORRECT_RESPONSE_SIZE = -200015;

	static const int ERROR_SET_POSITION_MODE = -200016;
	static const int ERROR_GET_POSITION_MODE = -200017;

	static const int ERROR_NOT_SUPPORTED = -200016;

	static const int ERROR_ASTRO_READ_DEVICE_STATUS           = -201000;
	static const int ERROR_ASTRO_INIT_ASTRO_ENGINE            = -201001;
	static const int ERROR_ASTRO_START_TRACKING               = -201002;
	static const int ERROR_ASTRO_STOP_TRACKING                = -201003;
	static const int ERROR_ASTRO_RESTORE_DEVICE_STATUS        = -201004;
	static const int ERROR_ASTRO_CLOSE_VELOCITY_MEASURMENT    = -201005;
	static const int ERROR_ASTRO_CLOSE_MEASURMENT             = -201006;
	static const int ERROR_ASTRO_CLOSE_CALIBRATION            = -201007;
	static const int ERROR_ASTRO_SET_ENGINE_MODE              = -201008;
	static const int ERROR_ASTRO_SET_TARGET                   = -201009;
	static const int ERROR_ASTRO_GET_TARGET                   = -201010;
	static const int ERROR_ASTRO_SET_CORRECTION               = -201011;
	static const int ERROR_ASTRO_REGISTER_MEASURMENT          = -201012;
	static const int ERROR_ASTRO_REGISTER_VELOCITY_MEASURMENT = -201013;
	static const int ERROR_ASTRO_SET_ENVIRONMENT              = -201014;
	static const int ERROR_ASTRO_SET_IERS_INFO                = -201015;
	static const int ERROR_ASTRO_SET_OBSERVATION_PLACE        = -201016;
	static const int ERROR_ASTRO_RESET_CALIBRATIUON           = -201017;

	static const int ERROR_ASTRO_TRACKING_SET   = -201018;
	static const int ERROR_ASTRO_TRACKING_STATE = -201019;

	static const int ERROR_ASTRO_GUIDER_REQUEST = -202000;

	static const int ERROR_SET_DATE_TIME = -202000;

  public:
	tlinsInterfaceException(const std::string &errorMessage_, int errorID_) : tlinsException(errorMessage_, errorID_)
	{
	}
};


#endif
