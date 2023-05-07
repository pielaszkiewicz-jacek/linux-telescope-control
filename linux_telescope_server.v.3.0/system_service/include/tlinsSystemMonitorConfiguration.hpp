#ifndef _tlinsSystemMonitorConfiguration_hpp_
#define _tlinsSystemMonitorConfiguration_hpp_

#include <map>
#include <parameters/tlinsParametersList.hpp>
#include <string>
#include <tlinsAstroException.hpp>
#include <tlinsBacktrace.hpp>
#include <tlinsXMLParser.hpp>

#include <tlinsSystemService.hpp>

/*

<?xml version="1.0" encoding="UTF-8"?>
<configuration-system-service>
    <monitors>
        <parameters>
            <monitor type="keyboard">
                <parameter name="device">/dev/input/event1</parameter>
                <parameter name="krys"></parameter>
            </monitor>

            <monitor type="joystick">
                <parameter name="device">/dev/input/event1</parameter>
            </monitor>
        </parameters>
    </monitors>

    <parameters>
        <parameter name="device">/dev/input/event1</parameter>
    </parameters>

</configuration-system-service>

 */


class tlinsSystemMonitorConfiguration {
  public:
	struct Monitor {
		// Typ monitora
		tlinsEventTypes monitorType;

		// Parametery
		tlinsParametersList parameters;

		Monitor &operator=(const Monitor &v)
		{
			monitorType = v.monitorType;
			parameters  = v.parameters;
			return *this;
		}

		Monitor(const Monitor &v)
		{
			monitorType = v.monitorType;
			parameters  = v.parameters;
		}

		Monitor() = default;
	};

  private:
	// Konfiguracja osi
	std::map<tlinsEventTypes, Monitor> monitors;

	// Parametery
	tlinsParametersList commonParameters;

  private:
	std::string path;

	void parseMonitors(TiXmlElement *element);
	void parseParameters(TiXmlElement *element);
	void createKeyboardMonitor(Monitor &cfg);
	void createJoystickMonitor(Monitor &cfg);

  public:
	tlinsParametersList &getCommonParameters()
	{
		return commonParameters;
	}

	void buildConfiguration();
	void parse();

	tlinsSystemMonitorConfiguration(const std::string &path_);
	virtual ~tlinsSystemMonitorConfiguration();
};


#endif