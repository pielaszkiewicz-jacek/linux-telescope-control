#include <parameters/tlinsConfigurationParser.hpp>
#include <parameters/tlinsDeviceParametersList.hpp>
#include <parameters/tlinsGlobalParametersList.hpp>
#include <parameters/tlinsRampGeneratorParameters.hpp>
#include <parameters/tlinsRampGeneratorParametersList.hpp>
#include <parameters/tlinsSystemParametersList.hpp>
#include <parameters/tlins_parameters.hpp>
#include <tlinsBacktrace.hpp>

#include <memory>

//
// ----------------------------------------------------------------
// ----------------------------------------------------------------
//
void tlinsConfigurationParser::parse(const std::string &file)
{
	std::string docName("Configuration");

	auto parser = std::make_shared<tlinsXMLParser>(docName, file);

	list<std::string> path_configuration;

	std::string paraName_configuration = "configuration";
	std::string paraName_parameters    = "parameters";
	std::string paraName_devices       = "devices";
	std::string paraName_system        = "system";

	// Parsowanie pliku wejsciowego
	parser->parseFile();

	path_configuration.push_back(paraName_configuration);

	// Pobranie wezla roota
	TiXmlElement *documentElement = tlinsXMLParser::getNode(parser->getDocument(), path_configuration);

	// Wezly podrzedne w stosunku do configuration
	list<TiXmlElement *> elements;
	tlinsXMLParser::getChildNodes(documentElement, elements);

	// Przejscie po elementach
	for (auto iter = elements.begin(); iter != elements.end(); iter++) {
		if (paraName_parameters.compare((*iter)->Value()) == 0)
			tlinsConfigurationParser::parsGlobalParameters(*iter);
		else if (paraName_devices.compare((*iter)->Value()) == 0)
			tlinsConfigurationParser::parsDevices(*iter);
		else if (paraName_system.compare((*iter)->Value()) == 0)
			tlinsConfigurationParser::parsSystemParameters(*iter);
		else {
			__THROW__(tlinsParametersException("Uknow configuration file section",
			                                   tlinsParametersException::XML_CONFIGURATION_UKNOW_SECTION,
			                                   (char *) (paraName_parameters.c_str())));
		}
	}
}

void tlinsConfigurationParser::parsGlobalParameters(TiXmlElement *element)
{
	tlinsXMLParser::parsParameters(element, tlinsGlobalParametersList::getParameters());
}

void tlinsConfigurationParser::parsSystemParameters(TiXmlElement *element)
{
	tlinsXMLParser::parsParameters(element, tlinsSystemParametersList::getParameters());
}

void tlinsConfigurationParser::parsDevices(TiXmlElement *element)
{
	std::string paraName_mainDevice = "main-device";
	std::string paraName_device     = "device";
	std::string paraName_parameters = "parameters";

	// Wezly podrzedne w stosunku do configuration
	list<TiXmlElement *> eleDevs;
	tlinsXMLParser::getChildNodes(element, eleDevs);

	//
	// Pobranie nazwy urzadzenia systemowego z atrybutu
	//

	//
	// Przejscie po urzadzeniach glownuch
	//
	for (auto iterDevs = eleDevs.begin(); iterDevs != eleDevs.end(); iterDevs++) {
		if (!paraName_mainDevice.compare((*iterDevs)->Value())) {
			//
			// Urzadzenie glowne
			//

			// Nazwa urzadzenie systemowego
			std::string mainDeviceName;
			if (!tlinsXMLParser::readAttribueValue(*iterDevs, std::string("name"), mainDeviceName))
				__THROW__(tlinsParametersException(
				    "No name attribute", tlinsParametersException::XML_CONFIGURATION_NO_VALUE, std::string("name")));

			// Znacznik uruchamian w watku
			std::string thread_str;
			bool        thread;
			if (!tlinsXMLParser::readAttribueValue(*iterDevs, std::string("thread"), thread_str))
				__THROW__(tlinsParametersException("No system-device attribute",
				                                   tlinsParametersException::XML_CONFIGURATION_NO_VALUE,
				                                   std::string("thread")));

			thread = readBoolValue(thread_str.c_str(), std::string("thread").c_str());

			// Nazwa urzadzenia systemowego
			std::string devSysName;
			if (!tlinsXMLParser::readAttribueValue(*iterDevs, std::string("system-device"), devSysName))
				__THROW__(tlinsParametersException("No device name",
				                                   tlinsParametersException::XML_CONFIGURATION_NO_VALUE,
				                                   std::string("system-device")));

			std::string devSysNameConf;
			if (!tlinsXMLParser::readAttribueValue(*iterDevs, std::string("system-device-conf"), devSysNameConf))
				__THROW__(tlinsParametersException("No device name",
				                                   tlinsParametersException::XML_CONFIGURATION_NO_VALUE,
				                                   std::string("system-device")));

			TLINS_LOG_DEBUG_STR("Main device : %s", mainDeviceName.c_str());

			//
			// Tworzenie obiektu urzadzenia glownego
			//
			auto &mianDevPtr = tlinsDeviceParametersList::create(mainDeviceName, thread, devSysName, devSysNameConf);

			//
			// Przejscie po urzadzeniach
			//
			list<TiXmlElement *> eleMainDevs;
			tlinsXMLParser::getChildNodes(*iterDevs, eleMainDevs);

			for (auto iterMainDevs = eleMainDevs.begin(); iterMainDevs != eleMainDevs.end(); iterMainDevs++) {
				//
				// Urzadzenie
				//
				if (paraName_device.compare((*iterMainDevs)->Value()) == 0) {
					// Nazwa urzadzenie
					std::string deviceName;
					if (!tlinsXMLParser::readAttribueValue(*iterMainDevs, std::string("name"), deviceName)) {
						__THROW__(tlinsParametersException("No name attribute",
						                                   tlinsParametersException::XML_CONFIGURATION_NO_VALUE,
						                                   std::string("name")));
					}

					// Os sterownika
					std::string axis;
					if (!tlinsXMLParser::readAttribueValue(*iterMainDevs, std::string("axis"), axis)) {
						__THROW__(tlinsParametersException("No name attribute",
						                                   tlinsParametersException::XML_CONFIGURATION_NO_VALUE,
						                                   std::string("name")));
					}

					std::string  deviceIDStr;
					unsigned int deviceID;
					if (!tlinsXMLParser::readAttribueValue(*iterMainDevs, std::string("deviceID"), deviceIDStr)) {
						__THROW__(tlinsParametersException("No name attribute",
						                                   tlinsParametersException::XML_CONFIGURATION_NO_VALUE,
						                                   std::string("name")));
					}
					try {
						deviceID = std::stol(deviceIDStr);
					}
					catch (std::invalid_argument &exc) {
						__THROW__(tlinsParametersException(
						    "Attribute deviceID must be number",
						    tlinsParametersException::XML_CONFIGURATION_ERROR_CONVERT_TO_LONG, std::string("name")));
					}
					TLINS_LOG_DEBUG_STR("Device name : %s@%s", mainDeviceName.c_str(), deviceName.c_str());

					// Tworzenie instancji urzadzenia
					auto &device = mianDevPtr.create(deviceName, axis, deviceID);

					//
					// Przejscie po urzadzeniu
					//
					list<TiXmlElement *> eleDev;
					tlinsXMLParser::getChildNodes(*iterMainDevs, eleDev);

					for (auto iterDev = eleDev.begin(); iterDev != eleDev.end(); iterDev++) {
						if (!paraName_parameters.compare((*iterDev)->Value())) {
							// Parametery urzadzenia
							tlinsXMLParser::parsParameters(*iterDev, device.getParameters());
						} else {
							__THROW__(tlinsParametersException(
							    "Unknow parameter", tlinsParametersException::XML_CONFIGURATION_UKNOW_PARAMETER,
							    (char *) ((*iterDev)->Value())));
						}
					}
				} else if (paraName_parameters.compare((*iterMainDevs)->Value()) == 0) {
					// Parametery urzadzenia glownego
					tlinsXMLParser::parsParameters(*iterMainDevs, mianDevPtr.getParameters());
				} else {
					__THROW__(tlinsParametersException("Unknow parameter",
					                                   tlinsParametersException::XML_CONFIGURATION_UKNOW_PARAMETER,
					                                   (char *) ((*iterMainDevs)->Value())));
				}
			}
		} else {
			// Nieznay atrybut
			__THROW__(tlinsParametersException("Unknow parameter",
			                                   tlinsParametersException::XML_CONFIGURATION_UKNOW_PARAMETER,
			                                   (char *) ((*iterDevs)->Value())));
		}
	}
}
