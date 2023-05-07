#include <parameters/tlinsDeviceParameters.hpp>
#include <tlinsBacktrace.hpp>

//
// ----------------------------------------------------------------
// ----------------------------------------------------------------
//

tlinsParametersList &tlinsDeviceParameters::getParameters()
{
	return parameters;
}

const std::string &tlinsDeviceParameters::getDeviceName() const
{
	return deviceName;
}

const std::string &tlinsDeviceParameters::getAxis() const
{
	return axis;
}

const unsigned int tlinsDeviceParameters::getDeviceID() const
{
	return deviceID;
}

tlinsDeviceParameters::tlinsDeviceParameters(const std::string &name, const std::string &a,
                                             const unsigned int deviceID_)
    : deviceName(name), axis(a), deviceID(deviceID_)
{
}
