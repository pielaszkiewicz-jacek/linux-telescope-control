#ifndef __tlinsMainDeviceParameters_hpp__
#define __tlinsMainDeviceParameters_hpp__

#include <map>
#include <memory>
#include <string>
#include <thread>

#include <parameters/tlinsDeviceParameters.hpp>
#include <parameters/tlinsParametersList.hpp>

class tlinsMainDeviceParameters {
  private:
	bool                thread;
	std::string         deviceName;
	std::string         systemDeviceName;
	std::string         systemDeviceNameConirmation;
	tlinsParametersList parameters;

	std::map<std::string, tlinsDeviceParameters> devices;

  public:
	const std::string &getSystemDeviceName() const
	{
		return systemDeviceName;
	}

	const std::string &getSystemDeviceNameConfirmation() const
	{
		return systemDeviceNameConirmation;
	}
	const std::string   &getDeviceName() const;
	tlinsParametersList &getParameters();
	const bool           getThread() const;

	std::map<std::string, tlinsDeviceParameters> &getDevices();

	tlinsDeviceParameters &create(const std::string &name, const std::string &axis, const unsigned int id);

	tlinsMainDeviceParameters(const std::string &deviceName_, const bool thread, const std::string &systemDeviceName_,
	                          const std::string &systemDeviceNameConfirmation_);
	tlinsMainDeviceParameters(const tlinsMainDeviceParameters &v)
	{
		thread                      = v.thread;
		deviceName                  = v.deviceName;
		systemDeviceName            = v.systemDeviceName;
		systemDeviceNameConirmation = v.systemDeviceNameConirmation;
	};
	virtual ~tlinsMainDeviceParameters() = default;
};

#endif
