#include <tlinsIERSInfo.hpp>

#include <sofa.h>

void tlinsIERSInfo::calculate()
{
	pmXRad = pmX * DAS2R;
	pmYRad = pmY * DAS2R;

	dxRad = dx * DAS2R;
	dyRad = dy * DAS2R;
}

void tlinsIERSInfo::setZero(int y, int m, int d)
{
	year     = y;
	month    = m;
	day      = d;
}

tlinsIERSInfo::tlinsIERSInfo(int year_, int month_, int day_, double pmX_, double pmY_, double deltaUT_, double dPsi_, double dEpsilon_, double dx_, double dy_) :
	year{year_},
	month{month_},
	day{day_},
	pmX{pmX_},
	pmY{pmY_},
	deltaUT{deltaUT_},
	dPsi{dPsi_},
	dEpsilon{dEpsilon_},
	dx{dx_},
	dy{dy_}
{
	calculate();
}

double tlinsIERSInfo::getDeltaUt() const
{
	return deltaUT;
}

void tlinsIERSInfo::setDeltaUt(double v)
{
	deltaUT = v;
}

double tlinsIERSInfo::getDEpsilon() const
{
	return dEpsilon;
}

void tlinsIERSInfo::setDEpsilon(double v)
{
	dEpsilon = v;
}

double tlinsIERSInfo::getDPsi() const
{
	return dPsi;
}

void tlinsIERSInfo::setDPsi(double v)
{
	dPsi = v;
}

double tlinsIERSInfo::getDx() const
{
	return dx;
}

double tlinsIERSInfo::getDy() const
{
	return dy;
}

double tlinsIERSInfo::getDxRad() const
{
	return dxRad;
}

double tlinsIERSInfo::getDyRad() const
{
	return dyRad;
}

void tlinsIERSInfo::setD(double x, double y)
{
	dx = x;
	dy = y;
}

double tlinsIERSInfo::getPmX() const
{
	return pmX;
}

double tlinsIERSInfo::getPmY() const
{
	return pmY;
}

double tlinsIERSInfo::getPmXRad() const
{
	return pmXRad;
}

double tlinsIERSInfo::getPmYRad() const
{
	return pmYRad;
}

void tlinsIERSInfo::setPm(double x, double y)
{
	pmX = x;
	pmY = y;

	calculate();
}

void tlinsIERSInfo::setDate(int y, int m, int d)
{
	year  = y;
	month = m;
	day   = d;
}

int tlinsIERSInfo::getDay() const
{
	return day;
}

int tlinsIERSInfo::getMonth() const
{
	return month;
}

int tlinsIERSInfo::getYear() const
{
	return year;
}
