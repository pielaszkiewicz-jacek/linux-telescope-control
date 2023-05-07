#include <tlinsAstroObject.hpp>
#include <tlinsCoordinate.hpp>
#include <tlinsEnvironment.hpp>
#include <tlinsIERSInfo.hpp>
#include <tlinsIERSInfoManager.hpp>
#include <tlinsStarApparentPlaceCalculationSofa.hpp>
#include <tlinsTimeInfo.hpp>

#include <tlinsLogger.hpp>
#include <tlinsMoveServerInterface.hpp>
#include <tlinsObservationPlace.hpp>

//  Hello World client
#include <iostream>
#include <map>
#include <memory>
#include <stdio.h>
#include <string.h>
#include <string>
#include <thread>
#include <unistd.h>

#include <grpc++/channel.h>
#include <grpc++/client_context.h>
#include <grpc++/create_channel.h>
#include <grpc++/security/credentials.h>
#include <grpc/grpc.h>


// $$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$
// $$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$
// $$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$


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

static void reprd(char *s, double ra, double dc)
{
	char pm;
	int  i[4];

	printf("%25s", s);
	iauA2tf(7, ra, &pm, i);
	printf(" %2.2d %2.2d %2.2d.%7.7d", i[0], i[1], i[2], i[3]);
	iauA2af(6, dc, &pm, i);
	printf(" %c%2.2d %2.2d %2.2d.%6.6d\n", pm, i[0], i[1], i[2], i[3]);
}

int sofa_test100(void)
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
	    .scale = "UTC", .year = 2013, .month = 4, .day = 2, .hour = 23, .minute = 15, .seconds = 43.55};

	/* Site longitude, latitude (radians) and height above the geoid (m). */
	iauAf2a(longitude.sign, longitude.degris, longitude.minutes, longitude.seconds, &elong);
	iauAf2a(latitude.sign, latitude.degris, latitude.minutes, latitude.seconds, &phi);
	hm = 625.0;

	printf("#### elong = %f\n", elong);
	printf("#### phi   = %f\n", phi);

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

	printf("#### utc1  = %f\n", utc1);
	printf("#### utc2  = %f\n", utc2);


	/* TT date. */
	if (iauUtctai(utc1, utc2, &tai1, &tai2)) {
		return -1;
	}

	printf("#### tai1  = %f\n", tai1);
	printf("#### tai2  = %f\n", tai2);

	if (iauTaitt(tai1, tai2, &tt1, &tt2)) {
		return -1;
	}

	printf("#### tt1   = %f\n", tt1);
	printf("#### tt2   = %f\n", tt2);

	/* EOPs:  polar motion in radians, UT1-UTC in seconds. */
	xp   = 50.995e-3 * DAS2R;
	yp   = 376.723e-3 * DAS2R;
	dut1 = 155.0675e-3;

	printf("#### xp    = %f\n", xp);
	printf("#### yp    = %f\n", yp);
	printf("#### dut1  = %f\n", dut1);

	/* Corrections to IAU 2000A CIP (radians). */
	dx = 0.269e-3 * DAS2R;
	dy = -0.274e-3 * DAS2R;

	printf("#### dx    = %3.10f\n", dx);
	printf("#### dy    = %3.10f\n", dy);

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

	printf("#### pr    = %f\n", pr);
	printf("#### pd    = %f\n", pd);

	/* Parallax (arcsec) and recession speed (km/s). */
	px = 164.99e-3;
	rv = 0.0;

	printf("#### px    = %f\n", px);
	printf("#### rv    = %f\n", rv);

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


// $$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$
// $$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$
// $$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$


int sof_test2()
{
	try {
		std::cout << "D1" << std::endl;

		// Miejsce obserwacji
		auto &placeInstance = tlinsObservationPlace::getInstance();
		placeInstance.setEllipsoidType(tlinsObservationPlace::ElipsoideType::GRS_80);
		placeInstance.setLongitude(tlinsCoordinate(true, 5, 41, 54.2));
		placeInstance.setLatitude(tlinsCoordinate(true, 15, 57, 42.8));
		placeInstance.setHm(625.0);

		std::cout << "D4" << std::endl;

		// Srodowisko
		tlinsEnvironment::setAmbientPressure(952.0);
		tlinsEnvironment::setTemperature(18.5);
		tlinsEnvironment::setRealHumidity(0.83);
		tlinsEnvironment::setEffectiveColor(0.55);

		// Dane IERS
		// tlinsIERSInfoManager::add(tlinsIERSInfo(2013, 4, 2,
		//                                             50.995e-3, 376.723e-3,
		//                                             155.0675e-3,
		//                                             0.0, 0.0,
		//                                             0.269e-3, -0.274e-3((;

		// Czas obserwacji
		//		tlinsTimeInfo timeInfo(op, iers, tlinsTimeInfo::scale_utc, 2013, 4, 2, 23, 15, 43.55(;

		tlinsIERSInfo iers;
		// tlinsIERSInfoManager::get(2013, 4, 2, iers(;

		tlinsTimeInfo::setDateTime(2013, 4, 2, 23, 15, 32.55, tlinsTimeInfo::scale_utc);

		std::cout << "D5" << std::endl;
		std::cout << "D6" << std::endl;

		// Obiekt
		tlinsAstroObject ao;

		// Wspolrzedne
		ao.set(tlinsCoordinate(false, 14, 34, 16.81183), // RA
		       tlinsCoordinate(true, 12, 31, 10.39650)); // DC

		// Paralaksa
		ao.setParallax(164.99e-3);
		ao.setRadialVelocity(0.0);

		// Ruch wlasny
		ao.setProperMotion(-354.45e-3, 595.35e-3);

		std::cout << "D7" << std::endl;


		std::cout << "D8" << std::endl;

		tlinsAstroObject output_ao;

		tlinsStarApparentPlaceCalculationSofa                        cofaCalc;
		std::map<tlinsStarApparentPlaceType, tlinsAstroObjectSimple> outResult;
		cofaCalc.toApparent(ao, iers, outResult);

		std::cout << "D9" << std::endl;
	}
	catch (tlinsAstroException exc) {
		std::cout << "Error             : " << exc.getErrorID() << std::endl;
		std::cout << "Error description : " << exc.getErrorMessage() << std::endl;
	}

	//	exit(0);
	return 0;
}


/*
int main (void)
{
    sofa_test100();
    sof_test2();

    tlinsLogger::setLoggerStd();
    tlinsLogger::setLogLevel(tlinsLogger::LOG_LEVEL_DEBUG);

    tlinsMessageHandlerManager::registerHandler(std::string("NOTYFICATION::MOVE-REQUEST-END::1.0"),
                                                   std::shared_ptr<tlinsMessageHandlerFactory>(new
tlinsMessageHandlerFactoryTest()));


//	int rr = sofa_test();


    tlinsAsynchronusThreadChannelClient asyncChannel(std::string("tcp://localhost:5556"));
    tlinsSynchronusChannel channel;
    channel_ptr = &channel;

    // Otwarcie kanalu
//	try
//	{grpc::InsecureChannelCredentials()
        // Uruchomienie interfejsu asynchronicznego
//		tlinsAsynchronusThreadChannelClient::start(std::string("tcp://localhost:5556"));
        channel.startChannel(std::string("tcp://localhost:5555"));
//	}
//	catch(tlinsInterfaceException exc)
//	{
//		printf("Error = %s\n", exc.getErrorMessage().c_str());
//		exit(1);
//	}

    while(1)
    {
        tlinsMoveServerInterface moveSrv(channel);
        tlinsMoveServerInterface::MoveRequestDevice requests;

        auto &x = requests.add(std::string("X"));
        x.setaceleration(1.0);
        x.setdirection(tlinsMoveServerInterface::RequestDirection::LEFT);
        x.setspeed(2.5);
        x.setdistance(0.001);

        auto &y = requests.add(std::string("Y"));
        y.setaceleration(1.0);
        y.setdirection(tlinsMoveServerInterface::RequestDirection::RIGHT);
        y.setspeed(2.5);
        y.setdistance(0.001);

        requests.setctrl(tlinsMoveServerInterface::RequestCtrl::CTRL_REQUEST);
        requests.setmode(tlinsMoveServerInterface::RequestMode::MOVE);
4000);
        y -> mutable_v() -> set_value(40000);
        y -> mutable_direction() -> set_value(tlins::tlinsMoveDirection::_RIGHT);
        y -> mutable_distance() -> set_value(500000);

        // auto status = stub -> setMoveRequest(&context, &request, &response);
        auto status = stub -> setMoveReq
        tlinsMoveServerInterface::Status status;
        long requestId;

        moveSrv.moveRequest(std::string("main"), requests, requestId, status);

        printf("REQEST ID = %ld\n", requestId);
        printf("status.errorCode = %s\n", status.errorCode.c_str());
        printf("status.errorDescription = %s\n", status.errorDescription.c_str());
        printf("status.errorDescription = %d\n", status.status);

        sleep(1);
    }

    while(true)
    {
        sleep(1);
    }

    return 0;
}
*/

#include <device.grpc.pb.h>
#include <stdio.h>

class MoveRequestClient {
  private:
	std::unique_ptr<tlins::tlinsRpcService::Stub> stub;

  public:
	void testCall()
	{
		grpc::ClientContext context;

		tlins::tlinsRpcMoveRequest request;
		tlins::tlinsRpcMoveStatus  response;

		request.mutable_maindevicename()->set_value("main");
		request.mutable_a()->set_value(54000);
		request.mutable_d()->set_value(54000);
		request.mutable_v()->set_value(40000);
		request.mutable_mode()->set_value(tlins::tlinsSerialMoveType::_SPEED);
		request.mutable_interpolationtype()->set_value(tlins::tlinsSerialMoveInterpolationType::_NONE);
		request.mutable_movetype()->set_value(tlins::tlinsSerialMoveModeRelAbs::_REL);

		// auto status = stub -> setMoveRequest(&context, &request, &response);
		auto x = request.add_requestdetails();
		x->mutable_axisname()->set_value("X");
		x->mutable_a()->set_value(54000);
		x->mutable_d()->set_value(54000);
		x->mutable_v()->set_value(40000);
		x->mutable_direction()->set_value(tlins::tlinsMoveDirection::_LEFT);
		x->mutable_distance()->set_value(500000);

		// OS Y
		auto y = request.add_requestdetails();
		y->mutable_axisname()->set_value("Y");
		y->mutable_a()->set_value(54000);
		y->mutable_d()->set_value(54000);
		y->mutable_v()->set_value(40000);
		y->mutable_direction()->set_value(tlins::tlinsMoveDirection::_RIGHT);
		y->mutable_distance()->set_value(500000);

		// auto status = stub -> setMoveRequest(&context, &request, &response);
		auto status = stub->setMoveRequest(&context, request, &response);

		printf("ERROR CODE        = %d\n", response.status().errorcode());
		printf("ERROR DESCRIPTION = %s\n", response.status().errordescription().c_str());
		printf("REQUEST ID        = %d\n", response.requestid());
	};

	MoveRequestClient(std::shared_ptr<grpc::Channel> &channel) : stub{tlins::tlinsRpcService::NewStub(channel)} {};
};

int main(void)
{
	auto channel = grpc::CreateChannel("localhost:30000", grpc::InsecureChannelCredentials());

	MoveRequestClient move{channel};


	while (true) {
		move.testCall();

		sleep(10);
	}

	return 0;
}