#include "tlinsEarthAttitude.hpp"
#include <sofa.h>

static void copyMatrix(const double in[3][3], Eigen ::Matrix3d &out)
{
	out(0, 0) = in[0][0];
	out(0, 1) = in[0][1];
	out(0, 2) = in[0][2];

	out(1, 0) = in[1][0];
	out(1, 1) = in[1][1];
	out(1, 2) = in[1][2];

	out(2, 0) = in[2][0];
	out(2, 1) = in[2][1];
	out(2, 2) = in[2][2];
}

int tlinsEarthAttitude ::calculateAttitude(const unsigned int year, const unsigned int month, const unsigned int day,
                                           const unsigned int hour, const unsigned int minutes, const double seconds,
                                           std ::vector<EarthAttitudeInfo> &result)
{
	int    iy;
	int    im;
	int    id;
	int    ih;
	int    min;
	int    j;
	double sec;
	double xp;
	double yp;
	double dut1;
	double dx00;
	double dy00;
	double dx06;
	double dy06;
	double djmjd0;
	double date;
	double time;
	double utc;
	double dat;
	double tai;
	double tt;
	double tut;
	double ut1;
	double rp[3][3];
	double dpsi;
	double deps;
	double epsa;
	double rn[3][3];
	double rnpb[3][3];
	double ee;
	double gst;
	double rc2ti[3][3];
	double rpom[3][3];
	double rc2it[3][3];
	double x;
	double y;
	double s;
	double rc2i[3][3];
	double era;
	double dp00;
	double de00;
	double rb[3][3];
	double rpb[3][3];
	double v1[3];
	double v2[3];
	double ddp00;
	double dde00;

	/* UTC. */
	iy  = year;
	im  = month;
	id  = day;
	ih  = hour;
	min = minutes;
	sec = seconds;

	/* Polar motion (arcsec->radians). */
	xp = 0.0349282 * DAS2R;
	yp = 0.4833163 * DAS2R;

	/* UT1-UTC (s). */
	dut1 = -0.072073685;

	/* CIP offsets wrt IAU 2000A (mas->radians). */
	dx00 = 0.1725 * DMAS2R;
	dy00 = -0.2650 * DMAS2R;

	/* CIP offsets wrt IAU 2006/2000A (mas->radians). */
	dx06 = 0.1750 * DMAS2R;
	dy06 = -0.2259 * DMAS2R;

	/* TT (MJD). */
	j = ::iauCal2jd(iy, im, id, &djmjd0, &date);
	if (j < 0) {
		return j;
	}

	time = (60.0 * (double) (60 * ih + min) + sec) / DAYSEC;
	utc  = date + time;
	j    = ::iauDat(iy, im, id, time, &dat);
	if (j < 0) {
		return j;
	}

	tai = utc + dat / DAYSEC;
	tt  = tai + 32.184 / DAYSEC;

	/* UT1. */
	tut = time + dut1 / DAYSEC;
	ut1 = date + tut;

	/* ==================== */
	/* IAU 2000A, CIO based */
	/* ==================== */
	/* CIP and CIO, IAU 2000A. */
	::iauXys00a(djmjd0, tt, &x, &y, &s);

	/* Add CIP corrections. */
	x += dx00;
	y += dy00;

	/* GCRS to CIRS matrix. */
	::iauC2ixys(x, y, s, rc2i);

	/* Earth rotation angle. */
	era = ::iauEra00(djmjd0 + date, tut);

	/* Form celestial-terrestrial matrix (no polar motion yet). */
	::iauCr(rc2i, rc2ti);
	::iauRz(era, rc2ti);

	/* Polar motion matrix (TIRS->ITRS, IERS 2003). */
	::iauPom00(xp, yp, iauSp00(djmjd0, tt), rpom);

	/* Form celestial-terrestrial matrix (including polar motion). */
	::iauRxr(rpom, rc2ti, rc2it);

	{
		tlinsEarthAttitude ::EarthAttitudeInfo outData;

		copyMatrix(rc2ti, outData.celestialToTerrestrialMatrixNoPolar);
		copyMatrix(rc2it, outData.celestialToTerrestrialMatrix);
		copyMatrix(rc2i, outData.NPBMatrix);
		outData.X    = x;
		outData.Y    = y;
		outData.s    = s;
		outData.type = AttitudeType ::IAU_2000A_CIO_BASED;
		result.push_back(outData);
	}

	/*  ======================== */
	/*  IAU 2000A, equinox based */
	/*  ======================== */
	/* Nutation, IAU 2000A. */
	::iauNut00a(djmjd0, tt, &dp00, &de00);

	/* Precession-nutation quantities, IAU 2000. */
	::iauPn00(djmjd0, tt, dp00, de00, &epsa, rb, rp, rpb, rn, rnpb);

	/* Transform dX,dY corrections from GCRS to mean of date. */
	v1[0] = dx00;
	v1[1] = dy00;
	v1[2] = 0.0;

	::iauRxp(rnpb, v1, v2);
	ddp00 = v2[0] / sin(epsa);
	dde00 = v2[1];

	/* Corrected nutation. */
	dpsi = dp00 + ddp00;
	deps = de00 + dde00;

	/* Build the rotation matrix. */
	::iauNumat(epsa, dpsi, deps, rn);

	/* Combine the matrices:  PN = N x P. */
	::iauRxr(rn, rpb, rnpb);

	/* Greenwich apparent sidereal time (IAU 2000). */
	gst = ::iauAnp(iauGmst00(djmjd0 + date, tut, djmjd0, tt) + iauEe00(djmjd0, tt, epsa, dpsi));

	/* Form celestial-terrestrial matrix (no polar motion yet). */
	::iauCr(rnpb, rc2ti);
	::iauRz(gst, rc2ti);

	/* Polar motion matrix (TIRS->ITRS, IERS 2003). */
	::iauPom00(xp, yp, iauSp00(djmjd0, tt), rpom);

	/* Form celestial-terrestrial matrix (including polar motion). */
	::iauRxr(rpom, rc2ti, rc2it);

	{
		EarthAttitudeInfo outData;

		copyMatrix(rc2ti, outData.celestialToTerrestrialMatrixNoPolar);
		copyMatrix(rc2it, outData.celestialToTerrestrialMatrix);
		copyMatrix(rnpb, outData.NPBMatrix);
		outData.X    = x;
		outData.Y    = y;
		outData.s    = s;
		outData.type = AttitudeType ::IAU_2000A_EQUINOX_BASED;
		result.push_back(outData);
	}

	/* ========================= */
	/* IAU 2006/2000A, CIO based */
	/* ========================= */
	/* CIP and CIO, IAU 2006/2000A. */
	::iauXys06a(djmjd0, tt, &x, &y, &s);

	/* Add CIP corrections. */
	x += dx06;
	y += dy06;

	/* GCRS to CIRS matrix. */
	::iauC2ixys(x, y, s, rc2i);

	/* Earth rotation angle. */
	era = ::iauEra00(djmjd0 + date, tut);

	/* Form celestial-terrestrial matrix (no polar motion yet). */
	::iauCr(rc2i, rc2ti);
	::iauRz(era, rc2ti);

	/* Polar motion matrix (TIRS->ITRS, IERS 2003). */
	::iauPom00(xp, yp, iauSp00(djmjd0, tt), rpom);

	/* Form celestial-terrestrial matrix (including polar motion). */
	::iauRxr(rpom, rc2ti, rc2it);

	{
		EarthAttitudeInfo outData;

		copyMatrix(rc2ti, outData.celestialToTerrestrialMatrixNoPolar);
		copyMatrix(rc2it, outData.celestialToTerrestrialMatrix);
		copyMatrix(rc2i, outData.NPBMatrix);
		outData.X    = x;
		outData.Y    = y;
		outData.s    = s;
		outData.type = AttitudeType ::IAU_2006_2000A_CIO_BASED;
		result.push_back(outData);
	}

	/* =========================================== */
	/* IAU 2006/2000A, CIO based, using X,Y series */
	/* =========================================== */
	/* CIP and CIO, IAU 2006/2000A. */
	iauXy06(djmjd0, tt, &x, &y);
	s = iauS06(djmjd0, tt, x, y);

	/* Add CIP corrections. */
	x += dx06;
	y += dy06;

	/* GCRS to CIRS matrix. */
	iauC2ixys(x, y, s, rc2i);

	/* Earth rotation angle. */
	era = iauEra00(djmjd0 + date, tut);

	/* Form celestial-terrestrial matrix (no polar motion yet). */
	iauCr(rc2i, rc2ti);
	iauRz(era, rc2ti);

	/* Polar motion matrix (TIRS->ITRS, IERS 2003). */
	iauPom00(xp, yp, iauSp00(djmjd0, tt), rpom);

	/* Form celestial-terrestrial matrix (including polar motion). */
	iauRxr(rpom, rc2ti, rc2it);

	{
		EarthAttitudeInfo outData;

		copyMatrix(rc2ti, outData.celestialToTerrestrialMatrixNoPolar);
		copyMatrix(rc2it, outData.celestialToTerrestrialMatrix);
		copyMatrix(rc2i, outData.NPBMatrix);
		outData.X    = x;
		outData.Y    = y;
		outData.s    = s;
		outData.type = AttitudeType ::IAU_2006_2000A_CIO_BASED_USING_X_Y_SERIES;
		result.push_back(outData);
	}
}