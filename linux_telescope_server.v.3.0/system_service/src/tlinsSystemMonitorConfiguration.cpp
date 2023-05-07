#include <tlinsException.hpp>
#include <tlinsJoystickMonitor.hpp>
#include <tlinsKeybordMonitor.hpp>
#include <tlinsLogger.hpp>
#include <tlinsMonitorInterface.hpp>
#include <tlinsSystemMonitorConfiguration.hpp>
#include <tlinsSystemService.hpp>

#include <regex>

void tlinsSystemMonitorConfiguration::parseMonitors(TiXmlElement *element)
{
	list<TiXmlElement *> ele;
	tlinsXMLParser::getChildNodes(element, ele);
	std::string paraName_monitor = "monitor";

	for (auto iter = ele.begin(); iter != ele.end(); iter++) {
		if (paraName_monitor.compare((*iter)->Value()) != 0) {
			__THROW__(tlinsAstroException(std::string("Uknow configuration file section"), -1));
		}

		// 1. Typ monitora
		std::string typeName;
		if (!tlinsXMLParser::readAttribueValue(*iter, std::string("type"), typeName)) {
			__THROW__(tlinsAstroException(std::string("Missing type"), -1));
		}

		Monitor monitor;
		tlinsXMLParser::parsParameters(*iter, monitor.parameters);

		if (typeName == std::string{"keyboard"}) {
			monitor.monitorType           = tlinsEventTypes::KEBOARD;
			monitors[monitor.monitorType] = monitor;
		} else if (typeName == std::string{"joystick"}) {
			monitor.monitorType           = tlinsEventTypes::JOYSTICK;
			monitors[monitor.monitorType] = monitor;
		} else {
			__THROW__(tlinsAstroException(std::string("Unknown monitor type"), -1));
		}
	}
}

void tlinsSystemMonitorConfiguration::parseParameters(TiXmlElement *element)
{
	tlinsXMLParser::parsParameters(element, commonParameters);
}

void tlinsSystemMonitorConfiguration::parse()
{
	std::string docName("configuration-system-service");

	std::shared_ptr<tlinsXMLParser> parser(new tlinsXMLParser(docName, path));

	std::list<std::string> path_configuration;
	std::string            paraName_monitors   = "monitors";
	std::string            paraName_monitor    = "monitor";
	std::string            paraName_parameters = "parameters";

	// Parsowanie pliku wejsciowego
	try {
		parser->parseFile();
	}
	catch (tlinsXMLParserException exc) {
		__THROW__(tlinsAstroException(exc.getErrorMessage(), tlinsAstroException::ASTRO_ERROR_READ_CONFGIRATION));
	}

	path_configuration.push_back(docName);

	// Pobranie wezla roota
	TiXmlElement *documentElement = tlinsXMLParser::getNode(parser->getDocument(), path_configuration);

	// Wezly podrzedne w stosunku do configuration
	list<TiXmlElement *> elements;
	tlinsXMLParser::getChildNodes(documentElement, elements);

	for (auto iter = elements.begin(); iter != elements.end(); iter++) {
		if (paraName_monitors.compare((*iter)->Value()) == 0) {
			parseMonitors(*iter);
		} else if (paraName_parameters.compare((*iter)->Value()) == 0) {
			parseParameters(*iter);
		} else {
			__THROW__(tlinsAstroException(std::string("Unknown option"), -1));
		}
	}
}

void tlinsSystemMonitorConfiguration::createKeyboardMonitor(Monitor &cfg)
{
	std::string deviceName;
	if (!cfg.parameters.getParameterValue("device", deviceName)) {
		__THROW__(tlinsException(std::string("Mising device parameter"), -1));
	}

	std::set<unsigned int> allowedKeys;
	std::string            keysStr;
	if (!cfg.parameters.getParameterValue("allowd-keys", keysStr)) {
		__THROW__(tlinsException(std::string("Mising device parameter"), -1));
	}

	std::regex separator{","};
	auto       wIter = std::sregex_token_iterator(keysStr.begin(), keysStr.end(), separator, -1);
	auto       wEnd  = std::sregex_token_iterator();
	int        count = 0;
	int        size  = 0;

	for (; wIter != wEnd; wIter++) {
		std::string kId = *wIter;
		if (kId.empty())
			continue;

		auto keyNum = std::stoi(kId);

		if (keyNum < 0xff && keyNum >= 0)
			allowedKeys.insert(static_cast<unsigned char>(keyNum));
	}

	// Dodanie monitora
	tlinsMonitorManager::add<tlinsKeyboardMonitor>(deviceName, allowedKeys);
}


// --------------
void tlinsSystemMonitorConfiguration::createJoystickMonitor(Monitor &cfg)
{
	std::string deviceName;
	if (!cfg.parameters.getParameterValue("device", deviceName)) {
		__THROW__(tlinsException(std::string("Mising device parameter"), -1));
	}

	// Dodanie monitora
	tlinsMonitorManager::add<tlinsJoystickMonitor>(deviceName);
}

// --------------

void tlinsSystemMonitorConfiguration::buildConfiguration()
{
	for (auto &item : monitors) {
		switch (item.first) {
		case tlinsEventTypes::KEBOARD:
			createKeyboardMonitor(item.second);
			break;

		case tlinsEventTypes::JOYSTICK:
			createJoystickMonitor(item.second);
			break;
		}
	}
}

tlinsSystemMonitorConfiguration::tlinsSystemMonitorConfiguration(const std::string &path_) : path{path_}
{
}

tlinsSystemMonitorConfiguration::~tlinsSystemMonitorConfiguration()
{
}