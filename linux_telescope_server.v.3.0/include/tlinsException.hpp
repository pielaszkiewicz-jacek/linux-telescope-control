#ifndef _tlinsException_hpp_
#define _tlinsException_hpp_


#include <string>

using namespace std;

class tlinsException {
  public:
	static const int SUCCESS              = 0;
	static const int ERROR                = -1;
	static const int ERROR_OUT_OFF_MEMORY = -10000;

  private:
	string errorMessage;
	string excReportError;
	int    errorID;

  public:
	string &reportErrorMessage(void);
	string &getErrorMessage(void);
	int     getErrorID(void);

	tlinsException(const std::string &errorMessage_, const int errorID_);
	~tlinsException(void) = default;
};

#endif
