/*
 * tlins_backtrace.hpp
 *
 *  Created on: 14-05-2012
 *      Author: jacek
 */

#ifndef __tlinsBacktrace_hpp__
#define __tlinsBacktrace_hpp__

#include <list>
#include <string>

#include <map>
#include <mutex>
#include <stdio.h>
#include <string.h>

#define ___APP___
//#define _GNU_SOURCE
#include <sys/syscall.h>
#include <unistd.h>

#include <sys/types.h>
#include <tlinsLogger.hpp>

class tlinsBacktrace {
  private:
	class __item__ {
	  public:
		std::string type;
		std::string file;
		std::string name;
		std::string exc;
		char       *addr;
		int         line;
		int         thread;

		__item__(const __item__ &val)
		{
			type   = val.type;
			file   = val.file;
			name   = val.name;
			addr   = val.addr;
			line   = val.line;
			thread = val.thread;
			exc    = val.exc;
		}

		__item__(char *type_, char *file_, char *name_, char *addr_, int line_, int t)
		    : type(type_), file(file_), name(name_), addr(addr_), line(line_), thread(t){};
	};

	std::map<int, std::list<__item__>> stack_map;
	std::map<int, bool>                hasException;
	std::mutex                         mx;

  public:
	static tlinsBacktrace &instance()
	{
		static tlinsBacktrace ins;
		return ins;
	};

  public:
	void enterFun(char *file, char *name, char *addr, int line)
	{
		std::unique_lock<std::mutex> ml(mx);

		int th = (int) syscall(224);
		stack_map[th].push_back(__item__((char *) "F", file, name, addr, line, th));
	};

	void enterExc(char *file, char *name, char *addr, int line)
	{
		std::unique_lock<std::mutex> ml(mx);

		int th = (int) syscall(224);
		stack_map[th].push_back(__item__((char *) "E", file, name, addr, line, th));
	};

	void exitFun(void)
	{
		std::unique_lock<std::mutex> ml(mx);
		int                          th = (int) syscall(224);

		if (stack_map[th].empty()) {
			return;
		}

		stack_map[th].pop_back();
	};

	char *findFileName(char *str)
	{
		if (str == nullptr)
			return nullptr;

		char *ptr;
		for (ptr = str + strlen(str) - 1; ptr != str && (*ptr) != '/'; ptr--)
			;

		if (ptr == str)
			return str;

		return ptr + 1;
	}

	void printStack(int level)
	{
		char message[1024];

		std::unique_lock<std::mutex> ml(mx);

		auto &loggerInst = tlinsLogger::instance();

		loggerInst.log(level, "");
		loggerInst.log(level, "Print stack trace");
		loggerInst.log(level, "-------------------------------------------------------------------");

		std::map<int, std::list<__item__>>::iterator miter = stack_map.begin();
		for (; miter != stack_map.end(); miter++) {
			std::string tab("-> ");

			loggerInst.log(level, "");

			auto iter = miter->second.crbegin();

			sprintf(message, "Thread [%d], SIZE = %ld", miter->first, miter->second.size());
			loggerInst.log(level, message);

			sprintf(message, "--------------------------------------------------------------------");
			loggerInst.log(level, message);

			for (; iter != miter->second.crend(); iter++) {
				char *s1 = (char *) iter->type.c_str();
				char *s2 = (char *) tab.c_str();
				char *s3 = (char *) (iter->file.c_str());
				char *s4 = (char *) iter->name.c_str();

				sprintf(message, "[%s] %s%s, line:%4d : %s [0x%p]", s1, s2, findFileName(s3), iter->line, s4,
				        iter->addr);

				loggerInst.log(level, message);
				tab += "  ";
			}
			loggerInst.log(level, "");
		}
	};

	std::string getStackInfo()
	{
		std::string output;
		char        message[1024];

		std::unique_lock<std::mutex> ml(mx);

		output += "\n";
		output += "Stack trace\n";
		output += "-------------------------------------------------------------------\n";

		std::map<int, std::list<__item__>>::iterator miter = stack_map.begin();
		for (; miter != stack_map.end(); miter++) {
			std::string tab("-> ");

			output += "\n";

			auto iter = miter->second.crbegin();

			sprintf(message, "Thread [%d], SIZE = %ld\n", miter->first, miter->second.size());
			output += message;

			sprintf(message, "--------------------------------------------------------------------\n");
			output += message;

			for (; iter != miter->second.crend(); iter++) {
				char *s1 = (char *) iter->type.c_str();
				char *s2 = (char *) tab.c_str();
				char *s3 = (char *) (iter->file.c_str());
				char *s4 = (char *) iter->name.c_str();

				sprintf(message, "[%s] %s%s, line:%4d : %s [0x%p]\n", s1, s2, findFileName(s3), iter->line, s4,
				        iter->addr);

				output += message;
				tab += "  ";
			}
			output += "\n";
		}
		return output;
	};
};

#ifdef __DEBUG__

#define __TLINS_MSG_ENTER__                                                                                            \
	do {                                                                                                               \
		TLINS_LOG_DEBUG_STR("\033[0;32m >>> ENTER <<< \033[0m ");                                                      \
	} while (0)
#define __TLINS_MSG_EXIT__                                                                                             \
	do {                                                                                                               \
		TLINS_LOG_DEBUG_STR("\033[0;32m >>> EXIT  <<< \033[0m ");                                                      \
	} while (0)

#define TLINS_BKT_THROW()                                                                                              \
	do {                                                                                                               \
		TLINS_LOG_DEBUG_STR("THROW Exception.");                                                                       \
	} while (0)
#define TLINS_BKT_ENTER()                                                                                              \
	do {                                                                                                               \
		__TLINS_MSG_ENTER__;                                                                                           \
	} while (0)
#define TLINS_BKT_EXIT()                                                                                               \
	do {                                                                                                               \
		__TLINS_MSG_EXIT__;                                                                                            \
	} while (0)
#define TLINS_BKT_PRINT(level)                                                                                         \
	do {                                                                                                               \
		tlinsBacktrace::instance().printStack(level);                                                                  \
	} while (0)

#define __THROW__(exc)                                                                                                 \
	do {                                                                                                               \
		TLINS_BKT_THROW();                                                                                             \
		throw exc;                                                                                                     \
	} while (0)
#define __BEGIN__                                                                                                      \
	do {                                                                                                               \
		TLINS_BKT_ENTER();                                                                                             \
	} while (0)
#define __END__                                                                                                        \
	do {                                                                                                               \
		TLINS_BKT_EXIT();                                                                                              \
	} while (0)

#define __RETURN__(ret)                                                                                                \
	do {                                                                                                               \
		TLINS_BKT_EXIT();                                                                                              \
		return ret;                                                                                                    \
	} while (0)

#else
#define TLINS_BKT_ENTER()
#define TLINS_BKT_EXIT()
#define TLINS_BKT_PRINT(level)

#define __THROW__(exc)                                                                                                 \
	do {                                                                                                               \
		throw exc;                                                                                                     \
	} while (0)
#define __BEGIN__
#define __END__

#define __RETURN__(ret)                                                                                                \
	do {                                                                                                               \
		return ret;                                                                                                    \
	} while (0)

#endif

#endif /* TLINS_BACKTRACE_HPP_ */
