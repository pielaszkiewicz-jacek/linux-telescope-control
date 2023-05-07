/*
 * tlins_parameter.cpp
 *
 *  Created on: 22-04-2012
 *      Author: jacek
 */

#include <parameters/tlins_parameters.hpp>
#include <tlinsBacktrace.hpp>
#include <tlinsLogger.hpp>

#include "tlin_base.h"

#include <iostream>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#include <map>

//
// ----------------------------------------------------------------
// ----------------------------------------------------------------
//
int readIntValue(const char *element, const char *)
{
	return atoi(element);
}

long readLongValue(const char *element, const char *)
{
	return atol(element);
}

unsigned long readULongValue(const char *element, const char *)
{
	return (unsigned long) atol(element);
}

double readDoubleValue(const char *element, const char *)
{
	return atof(element);
}

bool readBoolValue(const char *element, const char *)
{
	if (strcmp(element, "true") == 0)
		return true;

	return false;
}
