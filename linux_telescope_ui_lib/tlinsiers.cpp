#include "tlinsiers.h"

namespace TlinsAstroBase {

tlinsIERS::tlinsIERS(const tlinsIERS& v)
{
    year = v.year;
    month = v.month;
    day = v.day;
    pmx = v.pmx;
    pmy = v.pmy;
    deltaUt = v.deltaUt;
    dPsi = v.dPsi;
    dEpsilon = v.dEpsilon;
    dx = v.dx;
    dy = v.dy;
}

tlinsIERS::tlinsIERS()
{
}

tlinsIERS::~tlinsIERS()
{
}

tlinsIERS& tlinsIERS::operator=(const tlinsIERS& v)
{
    year = v.year;
    month = v.month;
    day = v.day;
    pmx = v.pmx;
    pmy = v.pmy;
    deltaUt = v.deltaUt;
    dPsi = v.dPsi;
    dEpsilon = v.dEpsilon;
    dx = v.dx;
    dy = v.dy;
    return *this;
}

int tlinsIERS::getYear() const
{
    return year;
}

int tlinsIERS::getMonth() const
{
    return month;
}

int tlinsIERS::getDay() const
{
    return day;
}

double tlinsIERS::getPmx() const
{
    return pmx;
}

double tlinsIERS::getPmy() const
{
    return pmy;
}

double tlinsIERS::getDeltaUt() const
{
    return deltaUt;
}

double tlinsIERS::getDPsi() const
{
    return dPsi;
}

double tlinsIERS::getDEpsilon() const
{
    return dEpsilon;
}

double tlinsIERS::getDx() const
{
    return dx;
}

double tlinsIERS::getDy() const
{
    return dy;
}

//
// SET
//
void tlinsIERS::setYear(int v)
{
    year = v;
}

void tlinsIERS::setMonth(int v)
{
    month = v;
}

void tlinsIERS::setDay(int v)
{
    day = v;
}

void tlinsIERS::setPmx(double v)
{
    pmx = v;
}

void tlinsIERS::setPmy(double v)
{
    pmy = v;
}

void tlinsIERS::setDeltaUt(double v)
{
    deltaUt = v;
}

void tlinsIERS::setDPsi(double v)
{
    dPsi = v;
}

void tlinsIERS::setDEpsilon(double v)
{
    dEpsilon = v;
}

void tlinsIERS::setDx(double v)
{
    dx = v;
}

void tlinsIERS::setDy(double v)
{
    dy = v;
}

}
