#include <sofa.h>
#include <stdio.h>

/*

The site coordinates are:
Latitude and longitude = S 15 57' 42''.8; W 5 41' 54''.2

Height above the reference ellipsoid = 625m

Here are the catalog data for the test star:

    ICRS [α,δ] = 14h 34m 16s.81183 − 12 31′ 10'′.3965
    proper motions: μalfa = −354.45 mas/y, μdelta = +595.35 mas/y
    parallax = 0′′.16499
    radial velocity (recession speed) = 0 km/s

The date and time are:
    2013 April 2, 23h 15m 43s.55 UTC

The Earth orientation parameters are:
    polar motion: x = +50.995 mas, y = +376.723 mas

    UT1 − UTC = +155.0675 ms

and also:
    corrections to IAU 2000A CIP: dx = +0.269 mas, dy = −0.274 mas

The pressure value (952 HPa ≡ mB)

The temperature 18.5


*/

struct DegrisCorrdinate {
    char   sign;
    int    degris;
    int    minutes;
    double seconds;
};

struct TimeInfo {
    char * scale;
    int    year;
    int    month;
    int    day;
    int    hour;
    int    minute;
    double seconds;
};

void reprd(char *s, double ra, double dc)
{
    char pm;
    int  i[4];

    printf("%25s", s);
    iauA2tf(7, ra, &pm, i);
    printf(" %2.2d %2.2d %2.2d.%7.7d", i[0], i[1], i[2], i[3]);
    iauA2af(6, dc, &pm, i);
    printf(" %c%2.2d %2.2d %2.2d.%6.6d\n", pm, i[0], i[1], i[2], i[3]);
}

int sofa_test(void)
{
    iauASTROM astrom;
    iauLDBODY b[3];
    double    phi;
    double    elong;
    double    hm;
    double    phpa;
    double    tc;
    double    rh;
    double    wl;
    double    utc1;
    double    utc2;
    double    tai1;
    double    tai2;
    double    tt1;
    double    tt2;
    double    xp;
    double    yp;
    double    dut1;
    double    dx;
    double    dy;
    double    rc;
    double    dc;
    double    pr;
    double    pd;
    double    px;
    double    rv;
    double    eo;
    double    ri;
    double    di;
    double    rca;
    double    dca;
    double    ra;
    double    da;
    double    aot;
    double    zot;
    double    hot;
    double    dot;
    double    rot;
    double    aob;
    double    zob;
    double    hob;
    double    dob;
    double    rob;
    double    pvh[2][3];
    double    pvb[2][3];
    double    r[3][3];
    double    x;
    double    y;
    double    s;

    /* W 5 41' 54''.2 */
    struct DegrisCorrdinate longitude = {.sign = '-', .degris = 5, .minutes = 41, .seconds = 54.2};

    /* S 15 57' 42''.8 */
    struct DegrisCorrdinate latitude = {.sign = '-', .degris = 15, .minutes = 57, .seconds = 42.8};

    /* 2013 April 2, 23h 15m 43s.55 UTC */
    struct TimeInfo timeInfo = {
        .scale = "UTC", .year = 2013, .month = 4, .day = 2, .hour = 23, .minute = 15, .seconds = 43.55
    };

    /* Site longitude, latitude (radians) and height above the geoid (m). */
    iauAf2a(longitude.sign, longitude.degris, longitude.minutes, longitude.seconds, &elong);
    iauAf2a(latitude.sign, latitude.degris, latitude.minutes, latitude.seconds, &phi);
    hm = 625.0;

    /* Ambient pressure (HPa), temperature (C) and rel. humidity (frac). */
    phpa = 952.0;
    tc   = 18.5;
    rh   = 0.83;

    /* Effective color (microns). */
    wl = 0.55;

    /* UTC date. */
    if (iauDtf2d(timeInfo.scale, timeInfo.year, timeInfo.month, timeInfo.day, timeInfo.hour, timeInfo.minute,
                 timeInfo.seconds, &utc1, &utc2)) {
        return -1;
    }

    /* TT date. */
    if (iauUtctai(utc1, utc2, &tai1, &tai2)) {
        return -1;
    }

    if (iauTaitt(tai1, tai2, &tt1, &tt2)) {
        return -1;
    }

    /* EOPs:  polar motion in radians, UT1-UTC in seconds. */
    xp   = 50.995e-3 * DAS2R;
    yp   = 376.723e-3 * DAS2R;
    dut1 = 155.0675e-3;

    /* Corrections to IAU 2000A CIP (radians). */
    dx = 0.269e-3 * DAS2R;
    dy = -0.274e-3 * DAS2R;

    /* Star ICRS RA,Dec (radians). */
    if (iauTf2a(' ', 14, 34, 16.81183, &rc)) {
        return -1;
    }

    if (iauAf2a('-', 12, 31, 10.3965, &dc)) {
        return -1;
    }

    reprd("ICRS, epoch J2000.0:", rc, dc);

    /* Proper motion: RA/Dec derivatives, epoch J2000.0. */
    pr = atan2(-354.45e-3 * DAS2R, cos(dc));
    pd = 595.35e-3 * DAS2R;

    /* Parallax (arcsec) and recession speed (km/s). */
    px = 164.99e-3;
    rv = 0.0;

    /* ICRS to CIRS (geocentric observer). */
    iauAtci13(rc, dc, pr, pd, px, rv, tt1, tt2, &ri, &di, &eo);
    reprd("catalog -> CIRS:", ri, di);

    /* CIRS to ICRS (astrometric). */
    iauAtic13(ri, di, tt1, tt2, &rca, &dca, &eo);
    reprd("CIRS -> astrometric:", rca, dca);

    /* ICRS (astrometric) to CIRS (geocentric observer). */
    iauAtci13(rca, dca, 0.0, 0.0, 0.0, 0.0, tt1, tt2, &ri, &di, &eo);
    reprd("astrometric -> CIRS:", ri, di);


    /* Apparent place. */
    ra = iauAnp(ri - eo);
    da = di;
    reprd("geocentric apparent:", ra, da);

    /* CIRS to topocentric. */
    if (iauAtio13(ri, di, utc1, utc2, dut1, elong, phi, hm, xp, yp, 0.0, 0.0, 0.0, 0.0, &aot, &zot, &hot, &dot, &rot)) {
        return -1;
    }
    reprd("CIRS -> topocentric:", rot, dot);


    /* CIRS to observed. */
    if (iauAtio13(ri, di, utc1, utc2, dut1, elong, phi, hm, xp, yp, phpa, tc, rh, wl, &aob, &zob, &hob, &dob, &rob)) {
        return -1;
    }
    reprd("CIRS -> observed:", rob, dob);

    /* ICRS to observed. */ // <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
    if (iauAtco13(rc, dc, pr, pd, px, rv, utc1, utc2, dut1, elong, phi, hm, xp, yp, phpa, tc, rh, wl, &aob, &zob, &hob,
                  &dob, &rob, &eo)) {
        return -1;
    }
    reprd("ICRS -> observed:", rob, dob);

    /* ICRS to CIRS using some user-supplied parameters. */

    /* SOFA heliocentric Earth ephemeris. */
    if (iauEpv00(tt1, tt2, pvh, pvb)) {
        return -1;
    }

    /* JPL DE405 barycentric Earth ephemeris. */
    pvb[0][0] = -0.9741704366519668;
    pvb[0][1] = -0.2115201000882231;
    pvb[0][2] = -0.0917583114068277;
    pvb[1][0] = 0.0036436589347388;
    pvb[1][1] = -0.0154287318503146;
    pvb[1][2] = -0.0066892203821059;

    /* IAU 2000A CIP. */
    iauPnm00a(tt1, tt2, r);
    iauBpn2xy(r, &x, &y);

    /* Apply IERS corrections. */
    x += dx;
    y += dy;

    /* SOFA CIO locator. */
    s = iauS06(tt1, tt2, x, y);

    /* Populate the context. */
    iauApci(tt1, tt2, pvb, pvh[0], x, y, s, &astrom);

    /* Carry out the transformation and report the results. */
    iauAtciq(rc, dc, pr, pd, px, rv, &astrom, &ri, &di);
    reprd("ICRS -> CIRS (JPL, IERS):", ri, di);

    /* The same but with Saturn then Jupiter then Sun light deflection. */
    b[0].bm       = 0.00028574;
    b[0].dl       = 3e-10;
    b[0].pv[0][0] = -7.8101442680818964;
    b[0].pv[0][1] = -5.6095668114887358;
    b[0].pv[0][2] = -1.9807981923749924;
    b[0].pv[1][0] = 0.0030723248971152;
    b[0].pv[1][1] = -0.0040699547707598;
    b[0].pv[1][2] = -0.0018133584165345;

    b[1].bm       = 0.00095435;
    b[1].dl       = 3e-9;
    b[1].pv[0][0] = 0.7380987962351833;
    b[1].pv[0][1] = 4.6365869247538951;
    b[1].pv[0][2] = 1.9693136030111202;
    b[1].pv[1][0] = -0.0075581692172088;
    b[1].pv[1][1] = 0.0012691372216750;
    b[1].pv[1][2] = 0.0007279990012801;

    b[2].bm       = 1.0;
    b[2].dl       = 6e-6;
    b[2].pv[0][0] = -0.0007121743770509;
    b[2].pv[0][1] = -0.0023047830339257;
    b[2].pv[0][2] = -0.0010586596574639;
    b[2].pv[1][0] = 0.0000062923521264;
    b[2].pv[1][1] = -0.0000003308883872;
    b[2].pv[1][2] = -0.0000002964866231;

    iauAtciqn(rc, dc, pr, pd, px, rv, &astrom, 3, b, &ri, &di);
    reprd("ICRS -> CIRS (+ planets):", ri, di);

    /* CIRS to ICRS (astrometric). */
    iauAticqn(ri, di, &astrom, 3, b, &rca, &dca);
    reprd("CIRS -> astrometric:", rca, dca);
    return 0;
}


/*


















void calculate(double rc,       // CIRS (α) rektascensja (radians)
                double dc,       // CIRS (δ) deklinacja (radians)
                double pr,       // RA proper motion (radians/year)
                double pd,       // DEC proper motion (radians/year)
                double px,       // Parallax (arcsec)
                double rv,       // Radial vcelocity (km/s, +ve if receding)



                double utc1,     // UTC as a 2-part
                double utc2,
                double dut1,
                double elong,
                double phi,
                double hm,
                double xp,
                double yp,
                double phpa,
                double tc,
                double rh,
                double wl,
                double *aob,
                double *zob,
                double *hob,
                double *dob,
                double *rob)
{
    double pco[3];
    double pob[3];
    double pmt;                  // proper motion time interval (SSB, Julian years)
    double date1;
    double date2;
    double ebpv[2][3];
    double ehp[3];

    double p[3];
    double q[3];
    double e[3];
    double dlim;
    double em
    double bm;
    double p1[3];

    iauLDBODY ldbody;
    iauASTROM astrom;

    // 0.
    iauApcg(date1, date2, ebpv, ehp, &astrom(;


    void iauApco(double date1, double date2,
                 double ebpv[2][3], double ehp[3],
                 double x, double y, double s, double theta,
                 double elong, double phi, double hm,
                 double xp, double yp, double sp,
                 double refa, double refb,
                 iauASTROM *astrom)


    // 1. Proper motion and parallax
    iauPmpx(rc, dc, pr, pd, px, rv, astrom.pmt, astrom.eb, pco);

    // 2. light deection and aberration
    iauLd(bm, p, q, e, astrom.em, dlim, p1(;

}




















int main()
{



    void iauAtci13(double rc, double dc,
                   double pr, double pd, double px, double rv,
                   double date1, double date2,
                   double *ri, double *di, double *eo);



    // 1.
    int iauDtf2d(const char *scale, int iy, int im, int id, int ihr, int imn, double sec, double *d1, double *d2);

    // 2.
    int iauAtio13(double ri, double di,
                  double utc1, double utc2, double dut1,
                  double elong, double phi, double hm, double xp, double yp,
                  double phpa, double tc, double rh, double wl,
                  double *aob, double *zob, double *hob,
                  double *dob, double *rob);

    // 1.
    void iauG2icrs (double dl, double db, double *dr, double *dd(;



    // ###########################################################

    // 1. space motion and parallax
    void iauPmpx(double rc,
                 double dc,
                 double pr,
                 double pd,
                 double px,
                 double rv,
                 double pmt,
                 double pob[3],
                 double pco[3]);

    // 2. light deection and aberration

    void iauLd(double bm,
               double p[3],
               double q[3],
               double e[3],
               double em,
               double dlim,
               double p1[3]);

    // 3. Aberacja
    void iauAb(double pnat[3],
               double v[3],
               double s,
               double bm1,
               double ppr[3]);

    // 4.

    void iauBpn2xy(double rbpn[3][3],
                   double *x,
                   double *y);
    void iauPfw06(double date1,
                  double date2,
                  double *gamb,
                  double *phib,
                  double *psib,
                  double *epsa);

    // - precesja
    void iauPmat06(double date1,
                   double date2,
                   double rbp[3][3]);

    double iauObl06(double date1,
                    double date2);

    // - butacja
    void iauNut06a(double date1,
                   double date2,
                   double *dpsi,
                   double *deps);

    void iauNum06a(double date1,
                   double date2,
                   double rmatn[3][3]);
}
*/
