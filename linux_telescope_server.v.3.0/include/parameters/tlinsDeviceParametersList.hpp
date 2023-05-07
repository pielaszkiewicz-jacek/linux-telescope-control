#ifndef __tlinsDeviceParametersList_hpp__
#define __tlinsDeviceParametersList_hpp__

#include <map>
#include <memory>
#include <string>

#include <parameters/tlinsMainDeviceParameters.hpp>
#include <parameters/tlinsParametersList.hpp>

class tlinsDeviceParametersList {
  private:
	static tlinsParametersList parameters;
	static std::map<std::string, tlinsMainDeviceParameters> devices;

  public:
	static std::string &        getSystemDeviceName();
	static tlinsParametersList &getParameters();

	static tlinsMainDeviceParameters &create(const std::string &name, const bool t, const std::string &sysDev,
	                                         const std::string &sysDevConf);
	static void remove(const std::string &name);

	static std::map<std::string, tlinsMainDeviceParameters> &get();
};

#endif
