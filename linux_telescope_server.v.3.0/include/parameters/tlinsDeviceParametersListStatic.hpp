#ifndef __tlinsDeviceParametersListStatic_hpp__
#define __tlinsDeviceParametersListStatic_hpp__

#include <parameters/tlinsDeviceParametersList.hpp>

tlinsParametersList tlinsDeviceParametersList::parameters;
std::map<std::string, tlinsMainDeviceParameters> tlinsDeviceParametersList::devices;

#endif
