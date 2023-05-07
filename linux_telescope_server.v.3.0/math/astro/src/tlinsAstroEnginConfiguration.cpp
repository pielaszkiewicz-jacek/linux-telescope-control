#include <tlinsAstroEnginConfiguration.hpp>

#include <memory>
#include <tlins_parameters.hpp>

void tlinsAstroEnginConfiguration::parse()
{
	std::string docName("configuration-astro");

	auto parser = std::make_shared<tlinsXMLParser>(docName, path);

	std::list<std::string> path_configuration;
	std::string            paraName_configuration_astro = "configuration-astro";
	std::string            paraName_common              = "common";
	std::string            paraName_axes                = "axes";

	// Parsowanie pliku wejsciowego
	try {
		parser->parseFile();
	}
	catch (tlinsXMLParserException &exc) {
		__THROW__(tlinsAstroException(exc.getErrorMessage(), tlinsAstroException::ASTRO_ERROR_READ_CONFGIRATION));
	}

	path_configuration.push_back(paraName_configuration_astro);

	// Pobranie wezla roota
	TiXmlElement *documentElement = tlinsXMLParser::getNode(parser->getDocument(), path_configuration);

	// Get maion device name
	if (!tlinsXMLParser::readAttribueValue(documentElement, std::string("deviceName"), deviceName)) {
		__THROW__(tlinsAstroException(std::string("No main device name"),
		                              tlinsAstroException::ASTRO_ERROR_READ_CONFGIRATION));
	}

	// Wezly podrzedne w stosunku do configuration
	list<TiXmlElement *> elements;
	tlinsXMLParser::getChildNodes(documentElement, elements);

	for (auto iter = elements.begin(); iter != elements.end(); iter++) {
		if (paraName_axes.compare((*iter)->Value()) == 0)
			parseAxes(*iter);
		else if (paraName_common.compare((*iter)->Value()) == 0)
			parseCommon(*iter);
		else {
			__THROW__(
			    tlinsAstroException(std::string("Unknown option"), tlinsAstroException::ASTRO_ERROR_READ_CONFGIRATION));
		}
	}

	// Odczyt wartosci przeczytanych z pliku konfiguracyjnego
	// - Parametery dla poszczegolnych osi
	axesValues.clear();
	for (auto iter = axes.begin(); iter != axes.end(); iter++) {
		try {
			std::string name = iter->first;

			std::string value;
			if (!iter->second.parameters.getParameterValue(std::string("aceleration"), value)) {
				__THROW__(tlinsAstroException(std::string("No \"aceleration\" parameter for axis : ") + name,
				                              tlinsAstroException::ASTRO_ERROR_READ_CONFGIRATION));
			}
			double acelerationVal = readDoubleValue(value.c_str(), nullptr);

			if (!iter->second.parameters.getParameterValue(std::string("deceleration"), value)) {
				__THROW__(tlinsAstroException(std::string("No \"deceleration\" parameter for axis : ") + name,
				                              tlinsAstroException::ASTRO_ERROR_READ_CONFGIRATION));
			}
			double decelerationVal = readDoubleValue(value.c_str(), nullptr);

			if (!iter->second.parameters.getParameterValue(std::string("speed"), value)) {
				__THROW__(tlinsAstroException(std::string("No \"speed\" parameter for axis : ") + name,
				                              tlinsAstroException::ASTRO_ERROR_READ_CONFGIRATION));
			}
			double speed = readDoubleValue(value.c_str(), nullptr);

			if (!iter->second.parameters.getParameterValue(std::string("calibaration-error"), value)) {
				__THROW__(tlinsAstroException(std::string("No \"calibaration-error\" parameter for axis : ") + name,
				                              tlinsAstroException::ASTRO_ERROR_READ_CONFGIRATION));
			}
			double calibrationError = readDoubleValue(value.c_str(), nullptr);

			if (!iter->second.parameters.getParameterValue(std::string("device-reverse"), value)) {
				__THROW__(tlinsAstroException(std::string("No \"device-reverse\" parameter for axis : ") + name,
				                              tlinsAstroException::ASTRO_ERROR_READ_CONFGIRATION));
			}
			bool deviceReverse{false};
			if (value == "true") {
				deviceReverse = true;
			}

			// Wstawienie parameterow osi
			axesValues[name].aceleration      = acelerationVal;
			axesValues[name].deceleration     = decelerationVal;
			axesValues[name].speed            = speed;
			axesValues[name].calibrarionError = calibrationError;
			axesValues[name].deviceReverse    = deviceReverse;
		}
		catch (const tlinsAstroException &exc) {
			__THROW__(exc);
		}
		catch (const tlinsParametersException &) {
			__THROW__(tlinsAstroException(std::string("Incorrect value format"),
			                              tlinsAstroException::ASTRO_ERROR_READ_CONFGIRATION));
		}
		catch (const tlinsXMLParserException &) {
			__THROW__(tlinsAstroException(std::string("Incorrect value format"),
			                              tlinsAstroException::ASTRO_ERROR_READ_CONFGIRATION));
		}
	}

	try {
		auto _readParaStr = [&](const std::string &name) {
			std ::string val;
			if (!parameters.getParameterValue(name, val)) {
				__THROW__(tlinsAstroException(std::string("No \"" + name + "\" parameter."),
				                              tlinsAstroException::ASTRO_ERROR_READ_CONFGIRATION));
			}
			return val;
		};

		{
			std ::string val         = _readParaStr("earth-speed-rotation-error-x");
			earthSpeedRotationErrorX = readDoubleValue(val.c_str(), nullptr);
		}

		{
			std ::string val         = _readParaStr("earth-speed-rotation-error-y");
			earthSpeedRotationErrorY = readDoubleValue(val.c_str(), nullptr);
		}

		{
			std ::string val         = _readParaStr("earth-speed-rotation-error-z");
			earthSpeedRotationErrorZ = readDoubleValue(val.c_str(), nullptr);
		}

		// --------------------
		if (!parameters.getParameterValue(std::string("STAR_APPARENT_PLACE_TYPE"), STAR_APPARENT_PLACE_TYPE)) {
			__THROW__(tlinsAstroException(std::string("No \"STAR_APPARENT_PLACE_TYPE\" parameter."),
			                              tlinsAstroException::ASTRO_ERROR_READ_CONFGIRATION));
		}

		// - Parametery wspolne dla wszystkich osi
		std::string value = _readParaStr("stop-timeout");
		stopTimeout       = readLongValue(value.c_str(), nullptr);

		value = _readParaStr("time-rotation-sign");
		if (value == "true") {
			timeRotationSign = true;
		} else {
			timeRotationSign = false;
		}

		value       = _readParaStr("linear-aceleration");
		aceleration = readDoubleValue(value.c_str(), nullptr);

		value        = _readParaStr("linear-deceleration");
		deceleration = readDoubleValue(value.c_str(), nullptr);

		value        = _readParaStr("run-frequency");
		runFrequency = readULongValue(value.c_str(), nullptr);

		value             = _readParaStr("first-run-frequency");
		firstRunFrequency = readULongValue(value.c_str(), nullptr);

		value                  = _readParaStr("run-frequency-error-count");
		runFrequencyErrorCount = readULongValue(value.c_str(), nullptr);

		// Parametery korekty predkosci
		value              = _readParaStr("min-speed-percantage");
		minSpeedPercantage = readDoubleValue(value.c_str(), nullptr);

		value              = _readParaStr("max-speed-percantage");
		maxSpeedPercantage = readDoubleValue(value.c_str(), nullptr);

		value              = _readParaStr("min-speed-correction");
		minSpeedCorrection = readDoubleValue(value.c_str(), nullptr);

		value                  = _readParaStr("suspend-speed-correction");
		suspendSpeedCorrection = (value == "true" ? true : false);

		value                  = _readParaStr("reverse-speed-correction");
		reverseSpeedCorrection = (value == "true" ? true : false);

		value                = _readParaStr("speed-mode-wait-interval");
		speedModeWaitIterval = readULongValue(value.c_str(), nullptr);

		value         = _readParaStr("trace-position");
		tracePosition = (value == "true" ? true : false);

		// -----------------------------------
		// Konfiguracja gudera

		value        = _readParaStr("guider-ra-speed");
		guiderXSpeed = readDoubleValue(value.c_str(), nullptr);

		value        = _readParaStr("guider-dec-speed");
		guiderYSpeed = readDoubleValue(value.c_str(), nullptr);

		// -----------------------------------

		value                                  = _readParaStr("tracking-device-synchronisation-frequency");
		trackingDeviceSynchronisationFrequency = readULongValue(value.c_str(), nullptr);

		value                 = _readParaStr("tracking-speed-increase");
		trackingSpeedIncrease = readULongValue(value.c_str(), nullptr);

		// ------------------------------------

		connUrlRequestResponse = _readParaStr("conn-url-request-response");
		connUrlNotifications   = _readParaStr("conn-url-notifications");
		connUrlClient          = _readParaStr("conn-url-client");

		// Konfiguracja kontrolera w sytuacji braku korekt
		std::string boolStr = _readParaStr("run-standard-interation-wen-no-corrections");
		if (boolStr == "true")
			runStandardInterationWhenNoCorrections = true;
		else if (boolStr == "false")
			runStandardInterationWhenNoCorrections = false;
		else {
			__THROW__(tlinsAstroException(
			    std::string("\"run-standard-interation-wen-no-corrections\" acepts only true/false values"),
			    tlinsAstroException::ASTRO_ERROR_READ_CONFGIRATION));
		}

		// Poziom logowania
		std::string logLevel_;
		if (parameters.getParameterValue(std::string("log-level"), logLevel_)) {
			if (logLevel_ == "debug") {
				logLevel = tlinsLogger::LOG_LEVEL_DEBUG;
			} else if (logLevel_ == "info") {
				logLevel = tlinsLogger::LOG_LEVEL_INFO;
			} else if (logLevel_ == "warning") {
				logLevel = tlinsLogger::LOG_LEVEL_WARNING;
			} else if (logLevel_ == "error") {
				logLevel = tlinsLogger::LOG_LEVEL_ERROR;
			} else if (logLevel_ == "fatal") {
				logLevel = tlinsLogger::LOG_LEVEL_FATAL;
			}
		} else {
			logLevel = tlinsLogger::LOG_LEVEL_INFO;
		}
	}
	catch (const tlinsAstroException &exc) {
		__THROW__(exc);
	}
	catch (const tlinsParametersException &) {
		__THROW__(tlinsAstroException(std::string("Incorrect value format"),
		                              tlinsAstroException::ASTRO_ERROR_READ_CONFGIRATION));
	}
	catch (const tlinsXMLParserException &) {
		__THROW__(tlinsAstroException(std::string("Incorrect value format"),
		                              tlinsAstroException::ASTRO_ERROR_READ_CONFGIRATION));
	}
}

void tlinsAstroEnginConfiguration::parseAxes(TiXmlElement *element)
{
	list<TiXmlElement *> ele;
	tlinsXMLParser::getChildNodes(element, ele);
	std::string paraName_axis = "axis";

	for (auto iter = ele.begin(); iter != ele.end(); iter++) {
		if (paraName_axis.compare((*iter)->Value()) != 0) {
			__THROW__(tlinsAstroException(std::string("Uknow configuration file section"),
			                              tlinsAstroException::ASTRO_ERROR_READ_CONFGIRATION));
		}

		std::string axisName;
		if (!tlinsXMLParser::readAttribueValue(*iter, std::string("id"), axisName)) {
			__THROW__(tlinsAstroException(std::string("Missing axis ID"),
			                              tlinsAstroException::ASTRO_ERROR_READ_CONFGIRATION));
		}

		// Parsowanie parameterow osi
		tlinsXMLParser::parsParameters(*iter, axes[axisName].parameters);
	}
}
void tlinsAstroEnginConfiguration::parseCommon(TiXmlElement *element)
{
	tlinsXMLParser::parsParameters(element, parameters);
}

tlinsAstroEnginConfiguration::tlinsAstroEnginConfiguration(const std::string &path_) : path(path_)
{
}
