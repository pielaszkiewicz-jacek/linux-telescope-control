#ifndef TLINSUIEXCEPTION_H
#define TLINSUIEXCEPTION_H

#include <string>

namespace TlinsAstroBase {

class tlinsUIException {
private:
    std::string errorDescription;
    int errorId;

public:
    static const int SUCESS = 0;
    static const int WARNING = -1;
    static const int ERROR = -2;
    static const int ERROR_OUT_OF_INDEX_RANGE = -3;
    static const int ERROR_DB_OPEN = -4;
    static const int ERROR_DB_EXECUTE = -5;
    static const int ERROR_DB_PREPARE = -6;
    static const int ERROR_DB_QUERY = -7;
    static const int ERROR_INVALID_PARAMETER = -8;
    static const int ERROR_INVALID_FILE_PATH = -9;
    static const int ERROR_NO_FILE_PERMISIONS = -10;
    static const int ERROR_IO = -11;

public:
    const std::string getErrorDescription() const;
    int getErrorId() const;

    tlinsUIException(const int errorId_, const std::string errDesc_)
        : errorDescription(errDesc_)
        , errorId(errorId_)
    {
    }

    virtual ~tlinsUIException()
    {
    }

    tlinsUIException();
};

}

#endif // TLINSUIEXCEPTION_H
