#include "tlinstarget.h"

#include <tlinsBacktrace.hpp>

double tlinsTarget::getRA() const
{
    return RA;
}

double tlinsTarget::getDC() const
{
    return DC;
}

double tlinsTarget::getPmRA() const
{
    return pmRA;
}

double tlinsTarget::getPmDC() const
{
    return pmDC;
}

double tlinsTarget::getRadialVelocity() const
{
    return radialVelocity;
}

double tlinsTarget::getParallex() const
{
    return parallex;
}

std::string tlinsTarget::getCatalogType() const
{
    return catalogType;
}

std::string tlinsTarget::getObjectType() const
{
    return objectType;
}

std::string tlinsTarget::getConstelation() const
{
    return constelation;
}

std::string tlinsTarget::getObjectName() const
{
    return objectName;
}

double tlinsTarget::getMagnitutde() const
{
    return magnitutde;
}

double tlinsTarget::getSpeed() const
{
    return speed;
}

double tlinsTarget::getAceleration() const
{
    return aceleration;
}

long tlinsTarget::getDelta() const
{
    return delta;
}

void tlinsTarget::setRA(const double v)
{
    RA = v;
}

void tlinsTarget::setDC(const double v)
{
    DC = v;
}

void tlinsTarget::setPmRA(const double v)
{
    pmRA = v;
}

void tlinsTarget::setPmDC(const double v)
{
    pmDC = v;
}

void tlinsTarget::setRadialVelocity(const double v)
{
    radialVelocity = v;
}

void tlinsTarget::setParallex(const double v)
{
    parallex = v;
}

void tlinsTarget::setCatalogType(const std::string& v)
{
    catalogType = v;
}

void tlinsTarget::setObjectType(const std::string& v)
{
    objectType = v;
}

void tlinsTarget::setConstelation(const std::string& v)
{
    constelation = v;
}

void tlinsTarget::setObjectName(const std::string& v)
{
    objectName = v;
}

void tlinsTarget::setMagnitutde(const double v)
{
    magnitutde = v;
}

void tlinsTarget::setSpeed(const double v)
{
    speed = v;
}

void tlinsTarget::setAceleration(const double v)
{
    aceleration = v;
}

void tlinsTarget::setDelta(const long v)
{
    delta = v;
}

tlinsTarget& tlinsTarget::operator=(const tlinsTarget& v)
{
    RA = v.RA;
    DC = v.DC;
    pmRA = v.pmRA;
    pmDC = v.pmDC;
    radialVelocity = v.radialVelocity;
    parallex = v.parallex;
    catalogType = v.catalogType;
    objectType = v.objectType;
    constelation = v.constelation;
    objectName = v.objectName;
    magnitutde = v.magnitutde;
    speed = v.speed;
    aceleration = v.aceleration;
    delta = v.delta;
    return *this;
}
tlinsTarget::tlinsTarget(const tlinsTarget& v)
{
    RA = v.RA;
    DC = v.DC;
    pmRA = v.pmRA;
    pmDC = v.pmDC;
    radialVelocity = v.radialVelocity;
    parallex = v.parallex;
    catalogType = v.catalogType;
    objectType = v.objectType;
    constelation = v.constelation;
    objectName = v.objectName;
    magnitutde = v.magnitutde;
    speed = v.speed;
    aceleration = v.aceleration;
    delta = v.delta;
}

tlinsTarget::tlinsTarget()
{
}

tlinsTarget::~tlinsTarget()
{
}
