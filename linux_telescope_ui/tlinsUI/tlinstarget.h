#ifndef TLINSTARGET_H
#define TLINSTARGET_H

#include <string>

class tlinsTarget {
private:
    double RA;
    double DC;
    double pmRA;
    double pmDC;
    double radialVelocity;
    double parallex;

    std::string catalogType;
    std::string objectType;
    std::string constelation;
    std::string objectName;

    double magnitutde;
    double speed;
    double aceleration;
    long delta;

public:
    //
    // GET
    //
    double getRA() const;
    double getDC() const;
    double getPmRA() const;
    double getPmDC() const;
    double getRadialVelocity() const;
    double getParallex() const;

    std::string getCatalogType() const;
    std::string getObjectType() const;
    std::string getConstelation() const;
    std::string getObjectName() const;

    double getMagnitutde() const;
    double getSpeed() const;
    double getAceleration() const;
    long getDelta() const;

    //
    // SET
    //
    void setRA(const double v);
    void setDC(const double v);
    void setPmRA(const double v);
    void setPmDC(const double v);
    void setRadialVelocity(const double v);
    void setParallex(const double v);

    void setCatalogType(const std::string& v);
    void setObjectType(const std::string& v);
    void setConstelation(const std::string& v);
    void setObjectName(const std::string& v);

    void setMagnitutde(const double v);
    void setSpeed(const double v);
    void setAceleration(const double v);
    void setDelta(const long v);

public:
    tlinsTarget& operator=(const tlinsTarget& v);
    tlinsTarget(const tlinsTarget& v);
    tlinsTarget();

    virtual ~tlinsTarget();
};

#endif // TLINSTARGET_H
