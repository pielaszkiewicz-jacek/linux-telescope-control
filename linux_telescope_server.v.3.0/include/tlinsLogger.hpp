/*
 * tlins_log.hpp
 *
 *  Created on: 12-05-2012
 *      Author: jacek
 */

#ifndef _TLINS_LOG_HPP_
#define _TLINS_LOG_HPP_

#include <fstream>
#include <iostream>
#include <mutex>

#include <sys/syscall.h>
#include <unistd.h>

#include <time.h>

#include <sys/syscall.h>
#include <sys/time.h>

static long gettid_()
{
	long tid = syscall(SYS_gettid);
	return tid;
}

class tlinsLogger {
  public:
	static tlinsLogger &instance()
	{
		static tlinsLogger inst;
		return inst;
	};

  public:
	static const int LOG_LEVEL_DEBUG   = 0;
	static const int LOG_LEVEL_INFO    = 1;
	static const int LOG_LEVEL_WARNING = 2;
	static const int LOG_LEVEL_ERROR   = 3;
	static const int LOG_LEVEL_FATAL   = 4;

  private:
	static const int LOG_STREAM_NONE = 0;
	static const int LOG_STREAM_FILE = 1;
	static const int LOG_STREAM_STD  = 2;
	static const int LOG_STREAM_ERR  = 3;

	// Plik logu.
	static std::fstream logStream;
	static std::string  logFileName;

	// Poziom logowania
	static int logLevel;

	// Identyfikator strumienia
	static int stream;

  private:
	bool report(int level, const std::string &message, bool) const
	{
		struct timeval timeV;
		gettimeofday(&timeV, nullptr);

		struct tm  *tmTime = localtime(&timeV.tv_sec);
		char        timeStr[100];
		std::string strLevel;

		::sprintf(timeStr, "T[%04d.%02d.%02d %02d:%02d:%02d.%06ld]", tmTime->tm_year + 1900, tmTime->tm_mon + 1,
		          tmTime->tm_mday, tmTime->tm_hour, tmTime->tm_min, tmTime->tm_sec, timeV.tv_usec);
		strLevel += timeStr;
		char line1[100];
		::sprintf(line1, " P[%5d: %5d]", static_cast<int>(getpid()), static_cast<int>(gettid_()));

		strLevel += line1;

		switch (level) {
		case tlinsLogger::LOG_LEVEL_INFO:
			strLevel += " \e[32m<I>\e[0m => ";
			break;

		case tlinsLogger::LOG_LEVEL_WARNING:
			strLevel += " \e[33m<W>\e[0m => ";
			break;

		case tlinsLogger::LOG_LEVEL_ERROR:
			strLevel += " \e[31m<E>\e[0m => ";
			break;

		case tlinsLogger::LOG_LEVEL_FATAL:
			strLevel += " <F> => ";
			break;

		case tlinsLogger::LOG_LEVEL_DEBUG:
			strLevel += " \e[36m<D>\e[0m => ";
			break;

		default:
			return false;
		}

		switch (stream) {
		case tlinsLogger::LOG_STREAM_NONE:
			return false;

		case tlinsLogger::LOG_STREAM_FILE:
			logStream << strLevel << message << std::endl;
			logStream.flush();
			break;

		case tlinsLogger::LOG_STREAM_ERR:
			std::cerr << strLevel << message << std::endl;
			std::cerr.flush();
			break;

		case tlinsLogger::LOG_STREAM_STD:
			std::cout << strLevel << message << std::endl;
			std::cout.flush();
			break;
		}

		return true;
	}

	std::mutex mux;

  public:
	int isStream(void) const
	{
		return stream;
	}

	void log(int level, const std::string &message, bool forceCout = false)
	{
		std::unique_lock<std::mutex> ml(mux);

		if (level >= getLogLevel())
			report(level, message, forceCout);
	}

	void log(int level, const char *msg, bool forceCout = false)
	{
		std::unique_lock<std::mutex> ml(mux);

		std::string message(msg);

		if (level >= getLogLevel())
			report(level, message, forceCout);
	}

	void logDebug(const char *message, bool forceCout = false)
	{
		log(tlinsLogger::LOG_LEVEL_DEBUG, message, forceCout);
	}

	void logDebug(const std::string &message, bool forceCout = false)
	{
		log(tlinsLogger::LOG_LEVEL_DEBUG, message, forceCout);
	}

	void logInfo(const char *message, bool forceCout = false)
	{
		log(tlinsLogger::LOG_LEVEL_INFO, message, forceCout);
	}

	void logInfo(const std::string &message, bool forceCout = false)
	{
		log(tlinsLogger::LOG_LEVEL_INFO, message, forceCout);
	}

	void logWarning(const char *message, bool forceCout = false)
	{
		log(tlinsLogger::LOG_LEVEL_WARNING, message, forceCout);
	}

	void logWarning(const std::string &message, bool forceCout = false)
	{
		log(tlinsLogger::LOG_LEVEL_WARNING, message, forceCout);
	}

	void logError(const char *message, bool forceCout = false)
	{
		log(tlinsLogger::LOG_LEVEL_ERROR, message, forceCout);
	}

	void logError(const std::string &message, bool forceCout = false)
	{
		log(tlinsLogger::LOG_LEVEL_ERROR, message, forceCout);
	}

	void logFatal(const char *message, bool forceCout = false)
	{
		log(tlinsLogger::LOG_LEVEL_FATAL, message, forceCout);
	}

	void logFatal(const std::string &message, bool forceCout = false)
	{
		log(tlinsLogger::LOG_LEVEL_FATAL, message, forceCout);
	}

	int getLogLevel(void) const
	{
		return logLevel;
	}

	void setLogLevel(int level)
	{
		logLevel = level;
	}

	int setLogger(const std::string &fileName)
	{
		logFileName = fileName;

		std::unique_lock<std::mutex> ml(mux);

		if (logStream.is_open()) {
			logStream.close();
		}

		logStream.open(fileName.c_str(), std::ios::out | std::ios::app);
		if (!logStream.is_open()) {

			stream = tlinsLogger::LOG_STREAM_ERR;
			std::cerr << "ERROR : Error opening log file " << fileName << std::endl;
			return -1;
		}

		stream = tlinsLogger::LOG_STREAM_FILE;
		return 0;
	}

	int setLoggerStd(void)
	{
		// Zamkniecie strumienia
		if (stream == tlinsLogger::LOG_STREAM_FILE)
			logStream.close();

		stream = tlinsLogger::LOG_STREAM_STD;
		return 0;
	}

	int setLoggerErr(void)
	{
		// Zamkniecie strumienia
		if (stream == tlinsLogger::LOG_STREAM_FILE)
			logStream.close();

		stream = tlinsLogger::LOG_STREAM_ERR;
		return 0;
	}
};

#define TLINS_LOG_ERROR(s)                                                                                             \
	do {                                                                                                               \
		char line[20];                                                                                                 \
		::sprintf(line, " [%d] => ", __LINE__);                                                                        \
		char line1[100];                                                                                               \
		::sprintf(line1, "[%d-%ld] ", getpid(), gettid_());                                                            \
		std::string f(__FILE__);                                                                                       \
		std::string msg(f.substr(f.rfind("/") + 1, f.size() - f.rfind("/") - 1));                                      \
		msg.append(line);                                                                                              \
		msg.append(/*__PRETTY_FUNCTION__*/ __FUNCTION__);                                                              \
		msg.append(": ");                                                                                              \
		msg.append(s);                                                                                                 \
		::tlinsLogger::instance().logError(msg);                                                                       \
	} while (false)


#define TLINS_LOG_WARNING(s)                                                                                           \
	do {                                                                                                               \
		char line[20];                                                                                                 \
		::sprintf(line, " [%d] => ", __LINE__);                                                                        \
		std::string f(__FILE__);                                                                                       \
		std::string msg(f.substr(f.rfind("/") + 1, f.size() - f.rfind("/") - 1));                                      \
		msg.append(line);                                                                                              \
		msg.append(__FUNCTION__);                                                                                      \
		msg.append(": ");                                                                                              \
		msg.append(s);                                                                                                 \
		::tlinsLogger::instance().logWarning(msg);                                                                     \
	} while (false)


#define TLINS_LOG_EXEPTION(s, exc)                                                                                     \
	do {                                                                                                               \
		TLINS_LOG_ERROR(s);                                                                                            \
		char msg[1024];                                                                                                \
		::sprintf(msg, "Error id (%d). Error message (%s).", exc.getErrorID(), exc.getErrorMessage().c_str());         \
		TLINS_LOG_ERROR(s);                                                                                            \
	} while (false)

#ifdef __DEBUG__

#define TLINS_LOG_DEBUG(s)                                                                                             \
	do {                                                                                                               \
		char line[20];                                                                                                 \
		::sprintf(line, " [%d] => ", __LINE__);                                                                        \
		std::string f(__FILE__);                                                                                       \
		std::string msg(f.substr(f.rfind("/") + 1, f.size() - f.rfind("/") - 1));                                      \
		msg.append(line);                                                                                              \
		msg.append(__FUNCTION__);                                                                                      \
		msg.append(": ");                                                                                              \
		msg.append(s);                                                                                                 \
		::tlinsLogger::instance().logDebug(msg);                                                                       \
	} while (false)

#define TLINS_LOG_DEBUG_STR(...)                                                                                       \
	do {                                                                                                               \
		char __tmp__[1024];                                                                                            \
		::sprintf(__tmp__, __VA_ARGS__);                                                                               \
		char line[20];                                                                                                 \
		::sprintf(line, " [%d] => ", __LINE__);                                                                        \
		std::string f(__FILE__);                                                                                       \
		std::string msg(f.substr(f.rfind("/") + 1, f.size() - f.rfind("/") - 1));                                      \
		msg.append(line);                                                                                              \
		msg.append(__FUNCTION__);                                                                                      \
		msg.append(": ");                                                                                              \
		msg.append(__tmp__);                                                                                           \
		::tlinsLogger::instance().logDebug(msg);                                                                       \
	} while (false)

#else
#define TLINS_LOG_DEBUG(s)
#define TLINS_LOG_DEBUG_STR(...)
#endif

#endif /* TLINS_LOG_HPP_ */
