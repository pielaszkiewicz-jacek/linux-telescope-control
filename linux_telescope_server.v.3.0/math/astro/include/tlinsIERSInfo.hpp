#ifndef __tlinsIERSInfo_hpp__
#define __tlinsIERSInfo_hpp__

#include <tlinsBacktrace.hpp>
#include <tlinsCoordinate.hpp>

class tlinsIERSInfo {
  private:
	// Data
	int year{0};
	int month{0};
	int day{0};

	// - Polar motion
	double pmX{0.0};
	double pmY{0.0};

	double pmXRad{0.0};
	double pmYRad{0.0};

	// - Roiznica czasu UT1-UTC
	double deltaUT{0.0};

	// - Nutacja
	double dPsi{0.0};

	double dEpsilon{0.0};

	double dx{0.0};
	double dy{0.0};

	double dxRad{0.0};
	double dyRad{0.0};

	void calculate();

  public:
	void           setZero(int y, int m, int d);
	tlinsIERSInfo &operator=(const tlinsIERSInfo &v) = default;
	tlinsIERSInfo(const tlinsIERSInfo &v)            = default;
	tlinsIERSInfo()                                  = default;
	~tlinsIERSInfo()                                 = default;
	tlinsIERSInfo(int year_, int month_, int day_, double pmX_, double pmY_, double deltaUT_, double dPsi_,
	              double dEpsilon_, double dx_, double dy_);

	double getDeltaUt() const;
	void   setDeltaUt(double v);

	double getDEpsilon() const;
	void   setDEpsilon(double v);

	double getDPsi() const;
	void   setDPsi(double v);

	double getDx() const;
	double getDy() const;
	double getDxRad() const;
	double getDyRad() const;
	void   setD(double x, double y);

	double getPmX() const;
	double getPmY() const;
	double getPmXRad() const;
	double getPmYRad() const;
	void   setPm(double x, double y);

	void setDate(int y, int m, int d);
	int  getYear() const;
	int  getMonth() const;
	int  getDay() const;
};

#endif
