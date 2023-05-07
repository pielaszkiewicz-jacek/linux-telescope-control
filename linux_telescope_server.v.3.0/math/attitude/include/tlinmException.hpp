/*
 * tlinm_exception.hpp
 *
 *  Created on: 09-10-2012
 *      Author: jacek
 */

#ifndef __tlinmException_hpp__
#define __tlinmException_hpp__

#include <string>

class tlinmException {
  public:
	static int TLINM_ERROR_ID_MEMORY_ALLOCATION;
	static int TLINM_ERROR_ID_OUT_OF_TABLE_INDEX;
	static int TLINM_ERROR_ID_PROCESS_ITERATION_NO_SET;
	static int TLINM_ERROR_ID_UNKNOW_METHOD;
	static int TLINM_ERROR_NO_ATTITUDE;

  private:
	int         errorId;
	std::string errorDesc;

  public:
	int getErrorId(void) const
	{
		return errorId;
	}

	std::string &getErrorDesc(void)
	{
		return errorDesc;
	}

	tlinmException(int errId, const std::string &errDes) : errorId(errId), errorDesc(errDes)
	{
	}

	tlinmException(int errId, const char *errDes) : errorId(errId), errorDesc(errDes)
	{
	}
};

#endif
