#ifndef TLINSPLACE_H
#define TLINSPLACE_H

#include <string>

namespace TlinsAstroBase {

class tlinsPlace {
public:
    enum class ElipsoideType {
        WGS_84 = 0,
        GRS_80 = 1,
        WGS_72 = 2
    };

private:
    double longitude;
    double latitude;
    double hm;
    ElipsoideType epType;
    bool isDefault_;
    std::string name;

public:
    std::string getName() const
    {
        return name;
    }

    bool isDefault() const
    {
        return isDefault_;
    }

    double getLongitude() const
    {
        return longitude;
    }

    double getLatitude() const
    {
        return latitude;
    }

    double getHm() const
    {
        return hm;
    }

    ElipsoideType getEpType() const
    {
        return epType;
    }

    void setName(const std::string& v)
    {
        name = v;
    }

    void setLongitude(const double v)
    {
        longitude = v;
    }

    void setLatitude(const double v)
    {
        latitude = v;
    }

    void setHm(const double v)
    {
        hm = v;
    }

    void setEpType(const ElipsoideType v)
    {
        epType = v;
    }

    void setDefault(const bool v)
    {
        isDefault_ = v;
    }

public:
    tlinsPlace& operator=(const tlinsPlace& v);
    tlinsPlace(const tlinsPlace& v);
    tlinsPlace();
    virtual ~tlinsPlace();
};

}

#endif // TLINSPLACE_H
