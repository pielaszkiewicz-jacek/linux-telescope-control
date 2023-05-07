#include "tlinsastrobaseutils.h"
#include <sofa.h>
#include <tlinsBacktrace.hpp>

namespace TlinsAstroBase {

void tlinsAstroBaseUtils::splitRA(const double in, int& h, int& m, double& s, bool& sign)
{
    int ihmsf[4];
    double radians = in / 24.0 * 360.0 * DD2R;

    char cSign;
    iauA2tf(9, radians, &cSign, ihmsf);
    sign = (cSign == '-' ? true : false);

    h = ihmsf[0];
    m = ihmsf[1];
    s = static_cast<double>(ihmsf[2]) + static_cast<double>(ihmsf[3]) / 1000000000.0;
}

void tlinsAstroBaseUtils::splitDegris(const double in, int& d, int& m, double& s, bool& sign)
{
    int idmsf[4];
    double radians = in * DD2R;
    char cSign;
    iauA2af(9, radians, &cSign, idmsf);
    sign = (cSign == '-' ? true : false);

    d = idmsf[0];
    m = idmsf[1];
    s = static_cast<double>(idmsf[2]) + static_cast<double>(idmsf[3]) / 1000000000.0;
}

}
