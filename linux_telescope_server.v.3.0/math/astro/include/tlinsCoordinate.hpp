#ifndef __tlinsCoordinate_hpp__
#define __tlinsCoordinate_hpp__

#include <sofa.h>

class tlinsCoordinate {
  private:
	bool   sign{false};
	int    degris{0};
	int    minutes{0};
	double seconds{0.0};

  public:
	void   set(bool si, int d, int m, double s);
	int    getDegris() const;
	int    getMinutes() const;
	double getSeconds() const;
	bool   isSign() const;
	char   getSign() const;

	double toDegris() const
	{
		double val = 0.0;
		val        = static_cast<double>(degris) + static_cast<double>(minutes) / 60.0 + seconds / 3600.0;
		return sign ? val * -1 : val;
	}

	double toRadiansRa() const
	{
		double val;
		::iauTf2a(sign ? '-' : '+', degris, minutes, seconds, &val);
		return val;
	}

	double toRadiansDec() const
	{
		double val;
		::iauAf2a(sign ? '-' : '+', degris, minutes, seconds, &val);
		return val;
	}

	tlinsCoordinate &operator=(const tlinsCoordinate &v) = default;
	tlinsCoordinate()                                    = default;
	tlinsCoordinate(const tlinsCoordinate &v)            = default;
	tlinsCoordinate(const bool sign_, const int degris_, const int minutes_, const double seconds_);
	tlinsCoordinate(const char sign_, const int degris_, const int minutes_, const double seconds_);
	virtual ~tlinsCoordinate() = default;
};

#endif
