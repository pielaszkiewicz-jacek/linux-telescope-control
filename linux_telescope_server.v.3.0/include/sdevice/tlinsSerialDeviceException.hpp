#ifndef __tlinsSerialDeviceException_hpp__
#define __tlinsSerialDeviceException_hpp__

#include <string>
#include <tlinsException.hpp>

class tlinsSerialDeviceException : public tlinsException {
  public:
	static const int ERROR                    = -100000;
	static const int ERROR_OUT_OF_INDEX_RANGE = -100001;

	static const int ERROR_CONFIGURATION_ERROR = -100002;

	static const int ERROR_MODBUSS = -100003;
	static const int ERROR_GPIO    = -100004;


	static const int ERROR_MOVE_REQUEST_DATA = -100100;
	static const int ERROR_UNKNOWN_DEVICE    = -100101;

  public:
	tlinsSerialDeviceException(const std::string &msg, int error) : tlinsException(msg, error){};
};

#endif
