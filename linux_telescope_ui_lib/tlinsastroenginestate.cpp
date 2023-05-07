#include "tlinsastroenginestate.h"
#include <tlinsBacktrace.hpp>

namespace TlinsAstroBase {

double tlinsAstroEngineState::getRA() const
{
    return RA;
}

double tlinsAstroEngineState::getDC() const
{
    return DC;
}

double tlinsAstroEngineState::getPmRA() const
{
    return pmRA;
}

double tlinsAstroEngineState::getPmDC() const
{
    return pmDC;
}

double tlinsAstroEngineState::getRadialVelocity() const
{
    return radialVelocity;
}

double tlinsAstroEngineState::getParallex() const
{
    return parallex;
}

std::string tlinsAstroEngineState::getCatalogType() const
{
    return catalogType;
}

double tlinsAstroEngineState::getA11() const
{
    return a11;
}

double tlinsAstroEngineState::getA12() const
{
    return a12;
}

double tlinsAstroEngineState::getA13() const
{
    return a13;
}

double tlinsAstroEngineState::getA21() const
{
    return a21;
}

double tlinsAstroEngineState::getA22() const
{
    return a22;
}

double tlinsAstroEngineState::getA23() const
{
    return a23;
}

double tlinsAstroEngineState::getA31() const
{
    return a31;
}

double tlinsAstroEngineState::getA32() const
{
    return a32;
}

double tlinsAstroEngineState::getA33() const
{
    return a33;
}

long tlinsAstroEngineState::getDeviceX() const
{
    return deviceX;
}

long tlinsAstroEngineState::getDeviceY() const
{
    return deviceY;
}

long tlinsAstroEngineState::getDeviceXEncoder() const
{
    return deviceXEncoder;
}

long tlinsAstroEngineState::getDeviceYEncoder() const
{
    return deviceYEncoder;
}

tlinsAstroEngineState::EngineMode tlinsAstroEngineState::getMode() const
{
    return mode;
}

tlinsAstroEngineState::EngineState tlinsAstroEngineState::getState() const
{
    return state;
}

void tlinsAstroEngineState::setRA(const double v)
{
    RA = v;
}

void tlinsAstroEngineState::setDC(const double v)
{
    DC = v;
}

void tlinsAstroEngineState::setPmRA(const double v)
{
    pmRA = v;
}

void tlinsAstroEngineState::setPmDC(const double v)
{
    pmDC = v;
}

void tlinsAstroEngineState::setRadialVelocity(const double v)
{
    radialVelocity = v;
}

void tlinsAstroEngineState::setParallex(const double v)
{
    parallex = v;
}

void tlinsAstroEngineState::setCatalogType(const std::string& v)
{
    catalogType = v;
}

void tlinsAstroEngineState::setA11(const double v)
{
    a11 = v;
}

void tlinsAstroEngineState::setA12(const double v)
{
    a12 = v;
}

void tlinsAstroEngineState::setA13(const double v)
{
    a13 = v;
}
void tlinsAstroEngineState::setA21(const double v)
{
    a21 = v;
}

void tlinsAstroEngineState::setA22(const double v)
{
    a22 = v;
}

void tlinsAstroEngineState::setA23(const double v)
{
    a23 = v;
}

void tlinsAstroEngineState::setA31(const double v)
{
    a31 = v;
}

void tlinsAstroEngineState::setA32(const double v)
{
    a32 = v;
}

void tlinsAstroEngineState::setA33(const double v)
{
    a33 = v;
}

void tlinsAstroEngineState::setDeviceX(const long v)
{
    deviceX = v;
}

void tlinsAstroEngineState::setDeviceY(const long v)
{
    deviceY = v;
}

void tlinsAstroEngineState::setDeviceXEncoder(const long v)
{
    deviceXEncoder = v;
}

void tlinsAstroEngineState::setDeviceYEncoder(const long v)
{
    deviceYEncoder = v;
}

void tlinsAstroEngineState::setMode(const EngineMode v)
{
    mode = v;
}

void tlinsAstroEngineState::setState(const EngineState v)
{
    state = v;
}

tlinsAstroEngineState& tlinsAstroEngineState::operator=(const tlinsAstroEngineState& v)
{
    RA = v.RA;
    DC = v.DC;
    pmRA = v.pmRA;
    pmDC = v.pmDC;
    radialVelocity = v.radialVelocity;
    parallex = v.parallex;
    catalogType = v.catalogType;
    a11 = v.a11;
    a12 = v.a12;
    a13 = v.a13;
    a21 = v.a21;
    a22 = v.a22;
    a23 = v.a23;
    a31 = v.a31;
    a32 = v.a32;
    a33 = v.a33;
    deviceX = v.deviceX;
    deviceY = v.deviceY;
    deviceXEncoder = v.deviceXEncoder;
    deviceYEncoder = v.deviceYEncoder;
    mode = v.mode;
    state = v.state;
    name = v.name;

    xReverse = v.xReverse;
    yReverse = v.yReverse;

    return *this;
}

tlinsAstroEngineState::tlinsAstroEngineState(const tlinsAstroEngineState& v)
{
    RA = v.RA;
    DC = v.DC;
    pmRA = v.pmRA;
    pmDC = v.pmDC;
    radialVelocity = v.radialVelocity;
    parallex = v.parallex;
    catalogType = v.catalogType;
    a11 = v.a11;
    a12 = v.a12;
    a13 = v.a13;
    a21 = v.a21;
    a22 = v.a22;
    a23 = v.a23;
    a31 = v.a31;
    a32 = v.a32;
    a33 = v.a33;
    deviceX = v.deviceX;
    deviceY = v.deviceY;
    deviceXEncoder = v.deviceXEncoder;
    deviceYEncoder = v.deviceYEncoder;
    mode = v.mode;
    state = v.state;
    name = v.name;

    xReverse = v.xReverse;
    yReverse = v.yReverse;
}

tlinsAstroEngineState::tlinsAstroEngineState()
{
}

}
