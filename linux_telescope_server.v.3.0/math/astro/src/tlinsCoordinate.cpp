#include <tlinsBacktrace.hpp>
#include <tlinsCoordinate.hpp>

void tlinsCoordinate::set(bool si, int d, int m, double s)
{
	sign    = si;
	degris  = d;
	minutes = m;
	seconds = s;
}

int tlinsCoordinate::getDegris() const
{
	return degris;
}

int tlinsCoordinate::getMinutes() const
{
	return minutes;
}

double tlinsCoordinate::getSeconds() const
{
	return seconds;
}

bool tlinsCoordinate::isSign() const
{
	return sign;
}

char tlinsCoordinate::getSign() const
{
	return sign ? '-' : '+';
}

tlinsCoordinate::tlinsCoordinate(const bool sign_, const int degris_, const int minutes_, const double seconds_)
    : sign{sign_}, degris{degris_}, minutes{minutes_}, seconds{seconds_}
{
}

tlinsCoordinate::tlinsCoordinate(const char sign_, const int degris_, const int minutes_, const double seconds_)
    : sign{sign_ == '-' ? true : false}, degris{degris_}, minutes{minutes_}, seconds{seconds_}
{
}
