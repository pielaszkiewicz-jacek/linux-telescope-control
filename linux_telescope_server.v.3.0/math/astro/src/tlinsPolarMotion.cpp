#include <tlinsBacktrace.hpp>
#include <tlinsPolarMotion.hpp>

double tlinsPolarMotion::getXDeg() const
{
	return xDeg;
}

double tlinsPolarMotion::getYDeg() const
{
	return yDeg;
}

const tlinsCoordinate &tlinsPolarMotion::getX() const
{
	return x;
}

const tlinsCoordinate &tlinsPolarMotion::getY() const
{
	return y;
}

tlinsPolarMotion::tlinsPolarMotion(const tlinsPolarMotion &v)
{
	*this = v;
}

tlinsPolarMotion::tlinsPolarMotion(const tlinsCoordinate &x_, const tlinsCoordinate &y_) :
	x{x_},
	y{y_}
{
	iauAf2a(x.sign, x.degris, x.minutes, x.seconds, &xDeg);
	iauAf2a(y.sign, y.degris, y.minutes, y.seconds, &yDeg);
}
