/*
 * tlins_exception.cpp
 *
 *  Created on: 19-04-2012
 *      Author: jacek
 */

#include <stdio.h>
#include <tlinsException.hpp>

using namespace std;

string &tlinsException::getErrorMessage(void)
{
	return errorMessage;
}

int tlinsException::getErrorID(void)
{
	return errorID;
}

tlinsException::tlinsException(const std::string &errorMessage_, const int errorID_)
    : errorMessage(errorMessage_), errorID{errorID_}
{
}

string &tlinsException::reportErrorMessage(void)
{
	char errIDStr[100];

	sprintf(errIDStr, "%d", getErrorID());

	excReportError = "Error ID = ";
	excReportError += errIDStr;
	excReportError += "; Error details = ";
	excReportError += getErrorMessage();

	return excReportError;
}
