#ifndef __tlinsDeviceParameters_hpp__
#define __tlinsDeviceParameters_hpp__

#include <map>
#include <string>

#include <parameters/tlinsParametersList.hpp>
#include <tlinsBacktrace.hpp>

/*
 * ---------------------------------------------------------------------------
 * Statyczna klasa przechowujaca parametery urzadzenia
 * ---------------------------------------------------------------------------
 */
class tlinsDeviceParameters {
  private:
	std::string  deviceName;
	std::string  axis;
	unsigned int deviceID;

	// Parametery device
	tlinsParametersList parameters;

  public:
	tlinsParametersList &getParameters();

	const std::string &getDeviceName() const;
	const std::string &getAxis() const;
	const unsigned int getDeviceID() const;

	tlinsDeviceParameters(const std::string &name, const std::string &a, const unsigned int deviceID_);
	tlinsDeviceParameters(const tlinsDeviceParameters &v)
	{
		deviceName = v.deviceName;
		axis       = v.axis;
		deviceID   = v.deviceID;
	}
	virtual ~tlinsDeviceParameters() = default;
};

#endif
