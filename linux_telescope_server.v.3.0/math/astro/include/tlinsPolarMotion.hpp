#ifndef __tlinsPolarMotion_hpp__
#define __tlinsPolarMotion_hpp__

#include <tlinsCoordinate.hpp>

class tlinsPolarMotion {
  private:
	tlinsCoordinate x;
	double          xDeg;
	tlinsCoordinate y;
	double          yDeg;

  public:
	const tlinsCoordinate &getX() const;
	const tlinsCoordinate &getY() const;

	double getXDeg() const;
	double getYDeg() const;

	tlinsPolarMotion &operator=(const tlinsPolarMotion &v) = default;

	tlinsPolarMotion(const tlinsPolarMotion &v);
	tlinsPolarMotion(const tlinsCoordinate &x_, const tlinsCoordinate &y_);

	virtual ~tlinsPolarMotion() = default;
};

#endif
