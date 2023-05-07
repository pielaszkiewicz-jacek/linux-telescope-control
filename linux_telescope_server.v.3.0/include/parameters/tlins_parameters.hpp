/*
 * tlins_parameters.hpp
 *
 *  Created on: 22-04-2012
 *      Author: jacek
 */

#ifndef TLINS_PARAMETERS_HPP_
#define TLINS_PARAMETERS_HPP_

#include <parameters/tlinsParametersException.hpp>
#include <tlinsException.hpp>
#include <tlinsXMLParser.hpp>

#include <list>
#include <map>
#include <memory>
#include <string>
#include <vector>

#define TLIN_IOCTL_PARA_LOCAL_NTC_FREQUENCY 10001
#define TLIN_IOCTL_PARA_LOCAL_BASE_STEP_ANGLE 10002
#define TLIN_IOCTL_PARA_LOCAL_STEP_ANGLE 10003
#define TLIN_IOCTL_PARA_LOCAL_MAX_STEP_ANGLE 10004
#define TLIN_IOCTL_PARA_LOCAL_MAX_ACELERATION 10005
#define TLIN_IOCTL_PARA_LOCAL_MAX_VELOCITY 10006
#define TLIN_IOCTL_PARA_LOCAL_SAFETY_FACTOR 10007

void readNumbersFromString(std::list<char *> &strValues, std::vector<unsigned int> &destValues, int destTableSize);
int readIntValue(const char *element, const char *name);
unsigned int readUIntValue(const char *element, const char *name);
long readLongValue(const char *element, const char *name);
unsigned long readULongValue(const char *element, const char *name);
short readShortValue(const char *element, const char *name);
unsigned short readUShortValue(const char *element, const char *name);
char readCharValue(const char *element, const char *name);
unsigned char readUCharValue(const char *element, const char *name);
double readDoubleValue(const char *element, const char *name);
bool readBoolValue(const char *element, const char *name);

#endif /* TLINS_PARAMETERS_HPP_ */
