#include "tlinsplace.h"

namespace TlinsAstroBase {

tlinsPlace& tlinsPlace::operator=(const tlinsPlace& v)
{
    longitude = v.longitude;
    latitude = v.latitude;
    hm = v.hm;
    epType = v.epType;
    isDefault_ = v.isDefault_;
    name = v.name;
    return *this;
}

tlinsPlace::tlinsPlace(const tlinsPlace& v)
{
    longitude = v.longitude;
    latitude = v.latitude;
    hm = v.hm;
    epType = v.epType;
    isDefault_ = v.isDefault_;
    name = v.name;
}

tlinsPlace::tlinsPlace()
{
}

tlinsPlace::~tlinsPlace()
{
}

}
