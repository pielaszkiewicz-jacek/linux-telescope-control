/*
 * tlins_log.cpp
 *
 *  Created on: 12-05-2012
 *      Author: jacek
 */

#include <tlinsLogger.hpp>

int          tlinsLogger::logLevel = tlinsLogger::LOG_LEVEL_INFO;
int          tlinsLogger::stream   = tlinsLogger::LOG_STREAM_NONE;
std::string  tlinsLogger::logFileName;
std::fstream tlinsLogger::logStream;
