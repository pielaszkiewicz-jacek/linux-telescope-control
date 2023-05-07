#include <parameters/tlinsMainDeviceParameters.hpp>
#include <tlinsBacktrace.hpp>

// ----------------------------------------------------------------
// ----------------------------------------------------------------
const std::string &tlinsMainDeviceParameters::getDeviceName() const
{
	return deviceName;
}

tlinsDeviceParameters &tlinsMainDeviceParameters::create(const std::string &name, const std::string &axis,
                                                         const unsigned int id)
{
	devices.insert(std::pair<std::string, tlinsDeviceParameters>(name, tlinsDeviceParameters(name, axis, id)));
	return devices.find(name)->second;
}

tlinsParametersList &tlinsMainDeviceParameters::getParameters()
{
	return parameters;
}

std::map<std::string, tlinsDeviceParameters> &tlinsMainDeviceParameters::getDevices()
{
	return devices;
}


const bool tlinsMainDeviceParameters::getThread() const
{
	return thread;
}

tlinsMainDeviceParameters::tlinsMainDeviceParameters(const std::string &deviceName_, const bool thread_,
                                                     const std::string &devName,
                                                     const std::string &systemDeviceNameConfirmation_)
    : systemDeviceNameConirmation{systemDeviceNameConfirmation_},
      systemDeviceName{devName},
      deviceName{deviceName_},
      thread{thread_}

{
}
