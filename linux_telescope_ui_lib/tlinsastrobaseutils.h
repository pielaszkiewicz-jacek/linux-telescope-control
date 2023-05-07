#ifndef TLINSASTROBASEUTILS_H
#define TLINSASTROBASEUTILS_H

namespace TlinsAstroBase {

class tlinsAstroBaseUtils {
public:
    static void splitRA(const double in, int& h, int& m, double& s, bool& sign);
    static void splitDegris(const double in, int& d, int& m, double& s, bool& sign);
    tlinsAstroBaseUtils() = delete;
};

}

#endif // TLINSASTROBASEUTILS_H
