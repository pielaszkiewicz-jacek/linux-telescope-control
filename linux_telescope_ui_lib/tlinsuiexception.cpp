#include "tlinsuiexception.h"

namespace TlinsAstroBase {

tlinsUIException::tlinsUIException()
{
    errorDescription = "SUCCESS";
    errorId = tlinsUIException::SUCESS;
}

const std::string tlinsUIException::getErrorDescription() const
{
    return errorDescription;
}

int tlinsUIException::getErrorId() const
{
    return errorId;
}

}
