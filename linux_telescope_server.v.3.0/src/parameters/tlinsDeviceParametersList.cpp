#include <parameters/tlinsDeviceParametersList.hpp>
#include <tlinsBacktrace.hpp>

//
// ----------------------------------------------------------------
// ----------------------------------------------------------------
//

tlinsMainDeviceParameters &tlinsDeviceParametersList::create(const std::string &name, const bool t,
                                                             const std::string &sysDev, const std::string &sysDevConf)
{
	devices.insert(std::pair<std::string, tlinsMainDeviceParameters>(
	    name, tlinsMainDeviceParameters(name, t, sysDev, sysDevConf)));
	return devices.find(name)->second;
}

void tlinsDeviceParametersList::remove(const std::string &name)
{
	tlinsDeviceParametersList::devices.erase(name);
}

std::map<std::string, tlinsMainDeviceParameters> &tlinsDeviceParametersList::get()
{
	return tlinsDeviceParametersList::devices;
}

tlinsParametersList &tlinsDeviceParametersList::getParameters()
{
	return parameters;
}
