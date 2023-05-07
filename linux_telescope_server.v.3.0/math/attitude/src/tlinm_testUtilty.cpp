/*
 * tlinm_testUtilty.cpp
 *
 *  Created on: 15-10-2012
 *      Author: jacek
 */

// #include <tlinsAstroEngine.hpp>
// #include <tlinsAstroEngineInterface.hpp>
#include <tlinsAstroObject.hpp>
#include <tlinsAstroObjectSimple.hpp>
#include <tlinsCoordinate.hpp>
#include <tlinsIERSInfoManager.hpp>
#include <tlinsStarApparentPlaceCalculationSofa.hpp>

#include "tlinAttitudeUtilsClass.hpp"
#include <tlinmMeasurement.hpp>
#include <tlinmMeasurementBase.hpp>
#include <tlinmMeasurementVelocity.hpp>
#include <tlinmUtilsClass.hpp>
#include <tlinm_testUtilty.hpp>

#include <tlins_math.hpp>

#include <tlinsBacktrace.hpp>
#include <tlinsLogger.hpp>

#include <Eigen/Geometry>
#include <iostream>
#include <set>
#include <stdio.h>
#include <stdlib.h>
#include <sys/timeb.h>

#include <sofa.h>


void tlinmTestUtility::rotateVector(const Eigen::Vector3d &inVector, Eigen::Vector3d &outVector)
{
	outVector = zRotaionMatrix * inVector;
}

void tlinmTestUtility::addMeasurement(const Eigen::Vector3d &b, const Eigen::Vector3d &err, const Eigen::Vector3d &r, const double t, const double w)
{
	// Budowanie obiektu reprezentujacego pomiar
	try {
		tlinmMeasurement m(b(0), b(1), b(2), err(0), err(1), err(2), r(0), r(1), r(2), t, w);

		// Dodanie do wektora
		measurements.push_back(m);
	}
	catch (std::bad_alloc &exc) {
		throw tlinmException(tlinmException::TLINM_ERROR_ID_MEMORY_ALLOCATION, "tlinmTestUtility::addMeasurement() => memory allocation error.");
	}
}

static double toH(const int h, const int m, const double s)
{
	auto val = static_cast<double>(h) + static_cast<double>(m) / 60.0 + static_cast<double>(s) / 3600.0;
	LOG_DEBUG("VAL = " + std ::to_string(val));
	LOG_DEBUG("VAL = " + std ::to_string(val / 24.0 * 2.0 * 3.141592653589793238462643383279));
	return val;
}

static double toD(const int d, const int m, const double s, const bool sign)
{
	auto v = static_cast<double>(d) + static_cast<double>(m) / 60.0 + static_cast<double>(s) / 3600.0;
	if (sign)
		return -1.0 * v;
	return v;
}

void populatePrdefinedList(std::vector<tlinmTestUtility::Object> &refObjects, const std::set<int> &items)
{
	// -- Syriusz (1)
	if (items.count(1) != 0 || items.empty()) {
		tlinmTestUtility::Object obj{};
		obj.name = "Syriusz";
		obj.ra   = toH(6, 45, 08.917);
		obj.dc   = toD(16, 42, 58.02, true);

		obj.paraleks          = 0.37921;
		obj.radialVelocity    = -5.50;
		obj.radialVelocityErr = 0.0;
		obj.pmRa              = 546.0;
		obj.pmRaErr           = 0.0;
		obj.pmDc              = -1223.1;
		obj.pmDcErr           = 0.0;

		refObjects.push_back(obj);
	}

	// -- Betelgeza (2)
	if (items.count(2) != 0 || items.empty()) {
		tlinmTestUtility::Object obj{};
		obj.name              = "Betelgeza";
		obj.ra                = toH(5, 55, 10.30);
		obj.dc                = toD(7, 24, 25.43, false);
		obj.paraleks          = 0.00655;
		obj.radialVelocity    = -20.70;
		obj.radialVelocityErr = 0.40;
		obj.pmRa              = 24.95;
		obj.pmRaErr           = 0.08;
		obj.pmDc              = 9.56;
		obj.pmDcErr           = 0.15;

		refObjects.push_back(obj);
	}

	// -- Aldebaran (3)
	if (items.count(3) != 0 || items.empty()) {
		tlinmTestUtility::Object obj{};
		obj.name              = "Aldebaran";
		obj.ra                = toH(4, 35, 55.23);
		obj.dc                = toD(16, 30, 33.49, false);
		obj.paraleks          = 0.04894;
		obj.radialVelocity    = 54.26;
		obj.radialVelocityErr = 0.03;
		obj.pmRa              = 63.45;
		obj.pmRaErr           = 0.84;
		obj.pmDc              = -188.94;
		obj.pmDcErr           = 0.65;

		refObjects.push_back(obj);
	}

	// -- Kapella (4)
	if (items.count(4) != 0 || items.empty()) {
		tlinmTestUtility::Object obj{};
		obj.name              = "Kapella";
		obj.ra                = toH(5, 16, 41.35);
		obj.dc                = toD(45, 59, 52.77, false);
		obj.paraleks          = 0.07620;
		obj.radialVelocity    = 29.19;
		obj.radialVelocityErr = 0.07;
		obj.pmRa              = 75.25;
		obj.pmRaErr           = 0.54;
		obj.pmDc              = -426.89;
		obj.pmDcErr           = 0.07;

		refObjects.push_back(obj);
	}

	// -- Dubhe (5)
	if (items.count(5) != 0 || items.empty()) {
		tlinmTestUtility::Object obj{};
		obj.name              = "Dubhe";
		obj.ra                = toH(11, 3, 43.67);
		obj.dc                = toD(61, 45, 03.72, false);
		obj.paraleks          = 0.02638;
		obj.radialVelocity    = -9.40;
		obj.radialVelocityErr = 0.30;
		obj.pmRa              = -134.11;
		obj.pmRaErr           = 0.35;
		obj.pmDc              = -9.40;
		obj.pmDcErr           = 0.30;

		refObjects.push_back(obj);
	}

	// -- Szedar (6)
	if (items.count(6) != 0 || items.empty()) {
		tlinmTestUtility::Object obj{};
		obj.name              = "Szedar";
		obj.ra                = toH(0, 40, 30.44);
		obj.dc                = toD(56, 32, 14.39, false);
		obj.paraleks          = 0.01429;
		obj.radialVelocity    = -4.31;
		obj.radialVelocityErr = 0.11;
		obj.pmRa              = -32.13;
		obj.pmRaErr           = 0.10;
		obj.pmDc              = -4.31;
		obj.pmDcErr           = 0.02;

		refObjects.push_back(obj);
	}

	// -- Procjon (7)
	if (items.count(7) != 0 || items.empty()) {
		tlinmTestUtility::Object obj{};
		obj.name              = "Procjon";
		obj.ra                = toH(7, 39, 18.11);
		obj.dc                = toD(5, 13, 29.96, false);
		obj.paraleks          = 0.28593;
		obj.radialVelocity    = -3.20;
		obj.radialVelocityErr = 0.90;
		obj.pmRa              = -714.59;
		obj.pmRaErr           = 2.06;
		obj.pmDc              = -1036.80;
		obj.pmDcErr           = 0.90;

		refObjects.push_back(obj);
	}

	// -- Polluks (8)
	if (items.count(8) != 0 || items.empty()) {
		tlinmTestUtility::Object obj{};
		obj.name              = "Polluks";
		obj.ra                = toH(7, 45, 18.95);
		obj.dc                = toD(28, 1, 34.32, false);
		obj.paraleks          = 0.28593;
		obj.radialVelocity    = -3.23;
		obj.radialVelocityErr = 0.02;
		obj.pmRa              = -626.55;
		obj.pmRaErr           = 0.30;
		obj.pmDc              = -45.80;
		obj.pmDcErr           = 0.18;

		refObjects.push_back(obj);
	}

	// -- Regulus (9)
	if (items.count(9) != 0 || items.empty()) {
		tlinmTestUtility::Object obj{};
		obj.name              = "Regulus";
		obj.ra                = toH(10, 8, 22.31);
		obj.dc                = toD(11, 58, 1.95, false);
		obj.paraleks          = 0.0413;
		obj.radialVelocity    = 5.9;
		obj.radialVelocityErr = 2.00;
		obj.pmRa              = -248.73;
		obj.pmRaErr           = 0.35;
		obj.pmDc              = 5.59;
		obj.pmDcErr           = 0.21;

		refObjects.push_back(obj);
	}
}

//
// --------------------------------------------
//
void getValueDegris(const double v, int &d, int &m, double &s, bool &sign)
{
	if (v < 0)
		sign = true;
	else
		sign = false;

	double inputAbs = fabs(v);
	double degrisf  = ::floor(inputAbs);
	d               = static_cast<int>(degrisf);

	double minutes  = (inputAbs - degrisf) * 60.0;
	double minutesf = floor(minutes);
	m               = static_cast<int>(minutesf);

	s = (minutes - minutesf) * 60.0;
}

void getValueHour(const double v, int &h, int &m, double &s)
{
	double hourf = floor(v);
	h            = static_cast<int>(hourf);

	double minutes  = (v - hourf) * 60.0;
	double minutesf = floor(minutes);
	m               = static_cast<int>(minutesf);

	double sec = (minutes - minutesf) * 60.0;
}
//
// --------------------------------------------
//

Eigen::Vector3d bIn;


//
// --------------------------------------
// --------------------------------------
// --------------------------------------
//
void tlinmTestUtility ::addMeasurement2(const Eigen::Vector3d &b, const Eigen::Vector3d &err, const Eigen::Vector3d &r,
                                        const Eigen::Vector3d &rOrg, const double t, const double w,
                                        const double baseTime, const double ax, const double ay, const double az)
{
	double                             pi = 3.14159265358979323846264338327950;
	attitude ::tlinAttitudeMeasurement item{};

	item.setObservationVector(b);
	item.setObservationVectorError(err);
	item.setReferenceVector(rOrg);
	item.setObservationTime(static_cast<unsigned long>(baseTime + t));
	// item.setDeltaTime(static_cast<unsigned long>(deltat));
	item.setWeight(w);
	item.setDeltaM(w);

	Eigen::Vector3d speed;
	speed(0) = 0.0;
	speed(1) = 0.0;
	speed(2) = 2 * pi / (24.0 * 3600.0);

	Eigen::Vector3d speedErr;
	speedErr(0) = 0.0;
	speedErr(1) = 0.0;
	speedErr(2) = 0.00001;

	item.setRotationSpeed(speed);
	item.setRotationSpeedError(speedErr);

	item.setAngleX(0.0);
	item.setAngleY(0.0);
	item.setAngleZ(0.0);
	item.setAngleX(ax);
	item.setAngleY(ay);
	item.setAngleZ(az);

	newMeasurements.push_back(item);
}

void tlinmTestUtility::generateTestData2(const double inSpeed, const double inDT, const double inErrorLevel, const int inSpeedMeasurments, const std::vector<Object> &refObjects)
{
	double       pi = 3.14159265358979323846264338327950;
	struct timeb dTime;

	double t = 0.0;

	// Liczba obiektow
	int inCount = refObjects.size();

	double w = 1.0 / static_cast<double>(refObjects.size());

	// Wspolrzedne referencyjne obiektu
	double rAlfa;
	double rBeta;
	double rAlfaErr;
	double rBetaErr;

	printf("Error level = %f\n", inErrorLevel);

	Eigen::Vector3d r;    // Wspolrzedne referencyjne obiektu
	Eigen::Vector3d rErr; // Blad pomiarowy
	Eigen::Vector3d rRot; // Wspolrzedne obiektu referencyjnego z zaaplikowanym obrotem
	Eigen::Vector3d rErrRot;

	Eigen::Vector3d err;
	Eigen::Vector3d b; // Wspolrzedne obiektu w ukladzie urzadzenia
	Eigen::Vector3d bErr;

	Eigen::Vector3d errRot;
	Eigen::Vector3d bRot;
	Eigen::Vector3d bErrRot;

	// Inicializacja generatora licz losowych
	ftime(&dTime);
	srand48(dTime.time % dTime.millitm);

	// Czas bazowy
	struct timeval tv;
	gettimeofday(&tv, NULL);
	double baseTime = (double) (tv.tv_sec) + (double) (tv.tv_usec) / 1000000.0;
	printf("Base time = %f\n", baseTime);

	bool first = true;
	for (auto &item : refObjects) {
		int    dcD;
		int    dcM;
		double dcS;
		bool   dcSign;
		int    raH;
		int    raM;
		double raS;

		getValueDegris(item.dc, dcD, dcM, dcS, dcSign);
		getValueHour(item.ra, raH, raM, raS);

		tlinsCoordinate  corRa{false, raH, raM, raS};
		tlinsCoordinate  corDc{dcSign, dcD, dcM, dcS};
		tlinsAstroObject target;

		target.set(corRa, corDc);
		target.setParallax(item.paraleks);
		target.setRadialVelocity(item.radialVelocity);
		target.setCatalogType("");

		tlinsAstroObjectSimple apparentPosition;
		double                 rrAlfa;
		double                 rrBeta;

		//
		// 1. Aktaualizacj apozycji obiektu do pozycji obserwowanej
		//
		{
			/*
			// Aktualizacja czasu
			auto &tInfo = tlinsTimeInfo::getInstance();
			tInfo.update();

			// Pobranie aktualnych wartosci IERS
			tlinsIERSInfo iers;
			auto &        ins = tlinsIERSInfoManager::getInstance();
			if (!ins.get(tInfo.getYear(), tInfo.getMonth(), tInfo.getDay(), iers)) {
			    iers.setZero(tInfo.getYear(), tInfo.getMonth(), tInfo.getDay());
			}

			std::map<tlinsStarApparentPlaceType, tlinsAstroObjectSimple> apparentResult;
			tlinsStarApparentPlaceCalculationSofa::toApparent(target, iers, apparentResult);
			apparentPosition = apparentResult[tlinsStarApparentPlaceType::STAR_APPARENT_PLACE_TYPE_ICRS_TO_OBSERVED];

			rrAlfa = apparentPosition.getHourAngleRad();
			rrBeta = apparentPosition.getDeclinationRad();
			std::cout << "RRALFA = " << rrAlfa << "; RRBETA = " << rrBeta << std::endl;

			{
			    char pm;
			    int  i[4];

			    iauA2tf(7, rrAlfa, &pm, i);
			    printf("Obiekt referencyjny:  RR_RA = %2.2d:%2.2d:%2.2d.%7.7d; ", i[0], i[1], i[2], i[3]);

			    iauA2af(6, rrBeta, &pm, i);
			    printf("RR_DC = %c%2.2d:%2.2d:%2.2d.%6.6d\n", pm, i[0], i[1], i[2], i[3]);
			}
			*/
		}

		rAlfa = target.getHourAngleRad();
		rBeta = target.getDeclinationRad();


		printf("++++++++++++++++++++++++++++++++++++++ RA = %c%02d:%02d:%02.06f - DC = %c%02d:%02d:%02.06f\n",
		       target.getHourAngle().getSign(), target.getHourAngle().getDegris(), target.getHourAngle().getMinutes(),
		       target.getHourAngle().getSeconds(),

		       target.getDeclination().getSign(), target.getDeclination().getDegris(),
		       target.getDeclination().getMinutes(), target.getDeclination().getSeconds());


		printf("[0] ALFA   = %5.12f; BETA   = %5.12f\n", rAlfa, rBeta);
		std::cout << "[0] ALFA   = " << rAlfa << "; BETA   = " << rBeta << std::endl;

		//
		// 2. Wyznaczenie wspolrzednych obiektu referencyjnego
		//
		// RA w zakresie od 0 do 23:59:59
		// rAlfa = 2.0 * tlinmUtilsClass::pi * item.ra / 24.0;

		// DC w zakresie od -90 do +90
		// rBeta = 0.5 * tlinmUtilsClass::pi * item.dc / 90.0;

		// Jako bazowe obiekty bedzi ebrana wspolrzedna na moment obserwacji
		std::cout << "ALFA   = " << rAlfa << "; BETA   = " << rBeta << std::endl;
		{
			char pm;
			int  i[4];

			iauA2tf(7, rAlfa, &pm, i);
			printf("Obiekt referencyjny:     RA = %2.2d:%2.2d:%2.2d.%7.7d; ", i[0], i[1], i[2], i[3]);

			iauA2af(6, rBeta, &pm, i);
			printf("   DC = %c%2.2d:%2.2d:%2.2d.%6.6d\n", pm, i[0], i[1], i[2], i[3]);
		}


		// N pomiarow dla tego samego obiektu referencyjnego
		for (int idx = 0; idx < inSpeedMeasurments; idx++) {
			//
			// 3. Wyznaczenie bledu pomiarowego
			//    Blad ma wartosc absolutna
			//
			if (!tlinmUtilsClass::testEpsylon(inErrorLevel)) {
				rAlfaErr = drand48() / inErrorLevel;
				rBetaErr = drand48() / inErrorLevel;

				rAlfaErr = 0.00001;
				rBetaErr = 0.00001;

				printf("rAlfaErr = %f\n", rAlfaErr);
				printf("rBetaErr = %f\n", rBetaErr);

				tlinmUtilsClass::toCartesian(rAlfaErr, rBetaErr, rErr);
			} else {
				rErr(0) = 0.0;
				rErr(1) = 0.0;
				rErr(2) = 0.0;
			}

			Eigen::Vector3d ref;
			Eigen::Vector3d refRot;
			Eigen::Vector3d refErr;
			Eigen::Vector3d refRotErr;

			// Przejscie do ukladu wspolrzednych kartezianskich na biegunowe
			tlinmUtilsClass::toCartesian(rAlfa, rBeta, ref);
			tlinmUtilsClass::toCartesian(rAlfa + rAlfaErr, rBeta + rBetaErr, refErr);

			//
			// 4, Czas pomiaru oraz kat obrotu
			//
			// double mTime = baseTime + t;
			double mTime = t;
			double angle = 3.966235 + mTime / (24.0 * 3600.0) * 2 * pi;

			//
			// 5, Symulacja obrotu woko osi Z
			//
			{
				// Kat obrotu wynika z uplywu czasu
				zRotaionMatrix = buildZRotaionMatrix(angle);
				tlinmUtilsClass::printMatrix(zRotaionMatrix, "Time rotation matrix", "%15.9f");
				rotateVector(refErr, refRotErr);
				rotateVector(ref, refRot);

				PRINT_M(refRot, "RefRot    ", "%15.9f");
				PRINT_M(refErr, "RefErr    ", "%15.9f");
				PRINT_M(refRotErr, "refRotErr ", "%15.9f");
			}

			//
			// 6. Wyznaczenie wspolrzednych w ukladzie urzadzenia
			//
			Eigen::Vector3d obs;
			Eigen::Vector3d obs2;

			// Wspolrzedne w ukladzie urzedzenia z uwzglednionym bledem
			transformVector(refRotErr, obs);
			transformVector(refRot, obs2);

			PRINT_M(ref, "Ref    ", "%15.9f");
			PRINT_M(refErr, "RefErr ", "%15.9f");
			PRINT_M(obs, "Obs    ", "%15.9f");
			PRINT_M(obs2, "Obs2   ", "%15.9f");

			{
				Eigen::Vector2d out;
				tlinmUtilsClass::toSpeherical(obs, out);
				{
					char pm;
					int  i[4];

					iauA2af(6, out(0), &pm, i);
					printf("OBS X = %c%2.2d:%2.2d:%2.2d.%6.6d; ", pm, i[0], i[1], i[2], i[3]);

					iauA2af(6, out(1), &pm, i);
					printf("OBS Y = %c%2.2d:%2.2d:%2.2d.%6.6d\n", pm, i[0], i[1], i[2], i[3]);
				}
			}

			//
			// 7. Dodanie pomiaru
			//
			Eigen::Vector3d refOrg;
			tlinmUtilsClass::toCartesian(rAlfa, rBeta, refOrg);

			Eigen::Vector3d __err__{0.0001, 0.0001, 0.0001};
			addMeasurement2(obs, /*rErr*/ __err__, ref, refOrg, t, w, baseTime, 0.0, 0.0, angle);

			t += inDT;
		}

		// t += inDT;

		std::cout << "-------------------------------------------------------------------------------------"
		          << std::endl;
		std::cout << "-------------------------------------------------------------------------------------"
		          << std::endl;
		std::cout << "-------------------------------------------------------------------------------------"
		          << std::endl;
	}
}

// ??????????????????????????????????????????????


void tlinmTestUtility::generateTestData(const double inSpeed, const double inDT, const double inErrorLevel,
                                        const int inSpeedMeasurments, const std::vector<Object> &refObjects)
{
	double       pi = 3.14159265358979323846264338327950;
	struct timeb dTime;

	double t = 0.0;

	// Liczba obiektow
	int inCount = refObjects.size();

	double w = 1.0 / static_cast<double>(refObjects.size());

	// Wspolrzedne referencyjne obiektu
	double rAlfa;
	double rBeta;
	double rAlfaErr;
	double rBetaErr;

	printf("Error level = %f\n", inErrorLevel);

	Eigen::Vector3d r;    // Wspolrzedne referencyjne obiektu
	Eigen::Vector3d rErr; // Wspolrzedne referencyjne obiektu zaaplikowanym bledem
	Eigen::Vector3d rRot; // Wspolrzedne obiektu referencyjnego z zaaplikowanym obrotem
	Eigen::Vector3d rErrRot;

	Eigen::Vector3d err;
	Eigen::Vector3d b; // Wspolrzedne obiektu w ukladzie urzadzenia
	Eigen::Vector3d bErr;

	Eigen::Vector3d errRot;
	Eigen::Vector3d bRot;
	Eigen::Vector3d bErrRot;

	// Inicializacja generatora licz losowych
	ftime(&dTime);
	srand48(dTime.time % dTime.millitm);

	bool first = true;
	for (auto &item : refObjects) {
		int    dcD;
		int    dcM;
		double dcS;
		bool   dcSign;
		int    raH;
		int    raM;
		double raS;

		getValueDegris(item.dc, dcD, dcM, dcS, dcSign);
		getValueHour(item.ra, raH, raM, raS);

		tlinsCoordinate corRa{false, raH, raM, raS};
		tlinsCoordinate corDc{dcSign, dcD, dcM, dcS};

		tlinsAstroObject target;

		target.set(corRa, corDc);
		target.setParallax(item.paraleks);
		target.setRadialVelocity(item.radialVelocity);
		target.setCatalogType("");

		tlinsAstroObjectSimple apparentPosition;
		double                 rrAlfa;
		double                 rrBeta;

		{
			// Aktualizacja czasu
			auto &tInfo = tlinsTimeInfo::getInstance();
			tInfo.update();

			// Pobranie aktualnych wartosci IERS
			tlinsIERSInfo iers;
			auto &        ins = tlinsIERSInfoManager::getInstance();
			if (!ins.get(tInfo.getYear(), tInfo.getMonth(), tInfo.getDay(), iers)) {
				iers.setZero(tInfo.getYear(), tInfo.getMonth(), tInfo.getDay());
			}

			std::map<tlinsStarApparentPlaceType, tlinsAstroObjectSimple> apparentResult;
			tlinsStarApparentPlaceCalculationSofa::toApparent(target, iers, apparentResult);
			apparentPosition = apparentResult[tlinsStarApparentPlaceType::STAR_APPARENT_PLACE_TYPE_ICRS_TO_OBSERVED];

			rrAlfa = apparentPosition.getHourAngleRad();
			rrBeta = apparentPosition.getDeclinationRad();
			std::cout << "RRALFA = " << rrAlfa << "; RRBETA = " << rrBeta << std::endl;

			{
				char pm;
				int  i[4];

				iauA2tf(7, rrAlfa, &pm, i);
				printf("Obiekt referencyjny:  RR_RA = %2.2d:%2.2d:%2.2d.%7.7d; ", i[0], i[1], i[2], i[3]);

				iauA2af(6, rrBeta, &pm, i);
				printf("RR_DC = %c%2.2d:%2.2d:%2.2d.%6.6d\n", pm, i[0], i[1], i[2], i[3]);
			}
		}

		//
		// Wyznaczenie wspolrzednych obiektu referencyjnego
		//
		// RA w zakresie od 0 do 23:59:59
		rAlfa = 2.0 * tlinmUtilsClass::pi * item.ra / 24.0;

		// DC w zakresie od -90 do +90
		rBeta = 0.5 * tlinmUtilsClass::pi * item.dc / 90.0;

		// Jako bazowe obiekty bedzi ebrana wspolrzedna na moment obserwacji
		// rAlfa = rrAlfa;
		// rBeta = rrBeta;

		std::cout << "ALFA   = " << rAlfa << "; BETA   = " << rBeta << std::endl;
		{
			char pm;
			int  i[4];

			iauA2tf(7, rAlfa, &pm, i);
			printf("Obiekt referencyjny:     RA = %2.2d:%2.2d:%2.2d.%7.7d; ", i[0], i[1], i[2], i[3]);

			iauA2af(6, rBeta, &pm, i);
			printf("   DC = %c%2.2d:%2.2d:%2.2d.%6.6d\n", pm, i[0], i[1], i[2], i[3]);
		}

		// Przejscie do ukladu wspolrzednych kartezianskich na biegunowe
		tlinmUtilsClass::toCartesian(rAlfa, rBeta, r);

		//
		// 2. Aplikowanie bledu do obiektu referencyjnego
		//
		if (!tlinmUtilsClass::testEpsylon(inErrorLevel)) {
			rAlfaErr = drand48() / inErrorLevel;
			rBetaErr = drand48() / inErrorLevel;

			if (drand48() < 0.5)
				rAlfaErr *= -1.0;

			if (drand48() < 0.5)
				rBetaErr *= -1.0;


			printf("rAlfaErr = %f\n", rAlfaErr);
			printf("rBetaErr = %f\n", rBetaErr);

			tlinmUtilsClass::toCartesian(/*rAlfa + */ rAlfaErr, /*rBeta + */ rBetaErr, rErr);
		} else {
			rErr = r; // Blad jest zerowy
		}

		//
		// Symulacja obrotu woko osi Z
		//
		// t += inDT;
		// if (!first)
		{
			buildZRotaionMatrix(inSpeed * t);

			Eigen::Vector3d tmpR = r;

			tlinmUtilsClass::printMatrix(r, "R.1 = ", "%15.9f");
			rotateVector(tmpR, r);
			tlinmUtilsClass::printMatrix(r, "R.2 = ", "%15.9f");

			// Eigen::Vector3d tmpRErr = rErr;

			// tlinmUtilsClass::printMatrix(rErr, "Rerr.1 = ", "%15.9f");
			// rotateVector(tmpRErr, rErr);
			// tlinmUtilsClass::printMatrix(rErr, "Rerr.2 = ", "%15.9f");
			tlinmUtilsClass::printMatrix(rErr, "rErr", "%15.9f");
		}

		//
		// 3. Wyznaczenie wspolrzednych w ukladzie urzadzenia
		//
		// Wspolrzedne w ukladzie kartezisanskim
		transformVector(r, bIn);

		tlinmUtilsClass::printMatrix(r, "RRR       = ", "%15.9f");
		tlinmUtilsClass::printMatrix(bIn, "BIN       = ", "%15.9f");

		tlinmUtilsClass::normaliseCartesian(bIn, b);
		tlinmUtilsClass::printMatrix(b, "BBB       = ", "%15.9f");


		//
		// 4. Wyznaczenie bledu
		//
		// transformVector(rErr, bErr);
		err = b - bErr;

		tlinmUtilsClass::printMatrix(bErr, "BERR      = ", "%15.9f");
		tlinmUtilsClass::printMatrix(err, "ERR       = ", "%15.9f");


		//
		// 5. Dodanie pomiaru
		//
		// addMeasurement(b, err, r, t, w);
		addMeasurement(b, rErr, r, t, w);

		tlinmUtilsClass::printMatrix(b, "B       = ", "%15.9f");
		{
			Eigen::Vector2d out;
			tlinmUtilsClass::toSpeherical(b, out);

			{
				char pm;
				int  i[4];

				iauA2af(6, out(0), &pm, i);
				printf("X = %c%2.2d:%2.2d:%2.2d.%6.6d; ", pm, i[0], i[1], i[2], i[3]);

				iauA2af(6, out(1), &pm, i);
				printf("Y = %c%2.2d:%2.2d:%2.2d.%6.6d\n", pm, i[0], i[1], i[2], i[3]);
			}
		}

		tlinmUtilsClass::printMatrix(err, "ERR     = ", "%15.9f");
		tlinmUtilsClass::printMatrix(r, "R       = ", "%15.9f");

		std::cout << "-------------------------------------------------------------------------------------"
		          << std::endl;

		try {
			// Wstawienie wektora pomiarowego dla prekosci
			vMeasurements.push_back(tlinmMeasurementsVelocity{});
		}
		catch (std::bad_alloc &exc) {
			throw tlinmException(tlinmException::TLINM_ERROR_ID_MEMORY_ALLOCATION,
			                     "tlinmTestUtility::generateTestData() => memory allocation error.");
		}

		tlinmMeasurementsVelocity &vm = vMeasurements[vMeasurements.size() - 1];

		//
		// 6. Wyznaczenie danych pomiarowych na potrzeby pomiaru prekosci
		//
		t += inDT;
		for (int j = 0; j < inSpeedMeasurments; j++) {
			std::cout << "T = " << t << std::endl;

			//
			// 6.1 Wyznaczenie macierzy obrotu w okol osi Z
			//
			// if (j != 0)
			buildZRotaionMatrix(inSpeed * t); // Macierz obrotu
			// else
			// 	zRotaionMatrix = Eigen::Matrix3d::Identity();

			//
			// 6.2. Aplikowanie bledu do obiektu referencyjnego
			//
			if (!tlinmUtilsClass::testEpsylon(inErrorLevel)) {
				rAlfaErr = drand48() / inErrorLevel;
				rBetaErr = drand48() / inErrorLevel;

				if (drand48() < 0.5)
					rAlfaErr *= -1.0;

				if (drand48() < 0.5)
					rBetaErr *= -1.0;

				printf("rAlfaErr = %f\n", rAlfaErr);
				printf("rBetaErr = %f\n", rBetaErr);

				tlinmUtilsClass::toCartesian(/*rAlfa + */ rAlfaErr, /*rBeta + */ rBetaErr, rErr);
			} else {
				rErr = r; // Blad jest zerowy
			}

			//
			// 6.3. Wykonanie obrotu wokol osi Z
			//
			rotateVector(r, rRot);

			rotateVector(rErr, rErrRot);

			// 6.4. Wspolrzedne w ukladzie kartezisanskim
			transformVector(rRot, bRot);       // Idelany pomiar
			transformVector(rErrRot, bErrRot); // Pomiar obarczony bledem

			{
				Eigen::Vector2d out;
				tlinmUtilsClass::toSpeherical(bRot, out);
				printf("XXXX >>>> %f\n", out(0));
				printf("YYYY >>>> %f\n", out(1));

				{
					char pm;
					int  i[4];

					iauA2af(6, out(0), &pm, i);
					printf("XX = %c%2.2d:%2.2d:%2.2d.%6.6d; ", pm, i[0], i[1], i[2], i[3]);

					iauA2af(6, out(1), &pm, i);
					printf("YY = %c%2.2d:%2.2d:%2.2d.%6.6d\n", pm, i[0], i[1], i[2], i[3]);
				}
			}

			//
			// 6.5. Blad wyznaczenia pomiaru prekosci
			//
			errRot = bErrRot - bRot;

			//
			// 6.6. Dodanie pomiaru prekosci
			//
			// addVMeasurement(bRot, errRot, t, w, vm);
			addVMeasurement(bRot, rErr, t, w, vm);

			tlinmUtilsClass::printMatrix(bRot, "BROT", "%15.9f");
			tlinmUtilsClass::printMatrix(errRot, "ERRROT", "%15.9f");
			tlinmUtilsClass::printMatrix(rRot, "RROT", "%15.9f");
			tlinmUtilsClass::printMatrix(rErrRot, "RERRROT", "%15.9f");
			tlinmUtilsClass::printMatrix(rErr, "rErr", "%15.9f");

			std::cout << "-------" << std::endl;

			//
			// 6.7. Kolejny kwant czasu
			//
			t += inDT;
		}
		std::cout << "-------------------------------------------------------------------------------------"
		          << std::endl;
		first = false;
	}
}


void tlinmTestUtility::generateTestData(const double inSpeed, const double inDT, const double inCount,
                                        const double inErrorLevel, const int inSpeedMeasurments)
{
	double       pi = 3.14159265358979323846264338327950;
	struct timeb dTime;

	double t = 0.0;

	double w = 1.0 / (double) inCount;

	// Wspolrzedne referencyjne obiektu
	double rAlfa;
	double rBeta;
	double rAlfaErr;
	double rBetaErr;

	Eigen::Vector3d r;    // Wspolrzedne referencyjne obiektu
	Eigen::Vector3d rErr; // Wspolrzedne referencyjne obiektu zaaplikowanym bledem
	Eigen::Vector3d rRot; // Wspolrzedne obiektu referencyjnego z zaaplikowanym obrotem
	Eigen::Vector3d rErrRot;

	Eigen::Vector3d err;
	Eigen::Vector3d b; // Wspolrzedne obiektu w ukladzie urzadzenia
	Eigen::Vector3d bErr;

	Eigen::Vector3d errRot;
	Eigen::Vector3d bRot;
	Eigen::Vector3d bErrRot;

	double eeeeeeeeeeeeerrr = 1.0 / inErrorLevel;

	// Inicializacja generatora licz losowych
	ftime(&dTime);
	srand48(dTime.time % dTime.millitm);

	for (int i = 0; i < inCount; i++) {
		//
		// Wyznaczenie wspolrzednych obiektu referencyjnego
		//
		rAlfa = 2.0 * tlinmUtilsClass::pi * drand48();
		rBeta = tlinmUtilsClass::pi / 2.0 * drand48() * (drand48() < 0.5 ? -1.0 : 1.0);

		std::cout << "ALFA = " << rAlfa << "; BETA = " << rBeta << std::endl;

		{
			char pm;
			int  i[4];

			// printf("%25s", s);
			iauA2tf(7, rAlfa, &pm, i);
			printf("Obiekt referencyjny:  RA = %2.2d:%2.2d:%2.2d.%7.7d; ", i[0], i[1], i[2], i[3]);

			iauA2af(6, rBeta, &pm, i);
			printf("DC = %c%2.2d:%2.2d:%2.2d.%6.6d\n", pm, i[0], i[1], i[2], i[3]);
		}

		// Przejscie do ukladu wspolrzednych kartezianskiX = +67:51:31.673636; Y = +75:21:39.668356we
		tlinmUtilsClass::toCartesian(rAlfa, rBeta, r);

		//
		// 2. Aplikowanie bledu do obiektu referencyjnego             |     0.000007959 |
		//
		if (!tlinmUtilsClass::testEpsylon(inErrorLevel)) {
			rAlfaErr = drand48() / inErrorLevel;
			rBetaErr = drand48() / inErrorLevel;

			if (drand48() < 0.5)
				rAlfaErr *= -1.0;

			if (drand48() < 0.5)
				rBetaErr *= -1.0;

			//			rAlfaErr = rBetaErr = eeeeeeeeeeeeerrr;
			tlinmUtilsClass::toCartesian(rAlfa + rAlfaErr, rBeta + rBetaErr, rErr);
		} else {
			rErr = r; // Blad jest zerowy
		}

		//
		// Symulacja obrotu woko osi Z
		//
		if (i != 0) {
			buildZRotaionMatrix(inSpeed * t);

			//			printf("T = %f\n", t);

			Eigen::Vector3d tmpR = r;

			tlinmUtilsClass::printMatrix(r, "R.1 = ", "%15.9f");
			rotateVector(tmpR, r);
			tlinmUtilsClass::printMatrix(r, "R.2 = ", "%15.9f");

			Eigen::Vector3d tmpRErr = rErr;

			tlinmUtilsClass::printMatrix(rErr, "Rerr.1 = ", "%15.9f");
			rotateVector(tmpRErr, rErr);
			tlinmUtilsClass::printMatrix(rErr, "Rerr.2 = ", "%15.9f");
		}

		//
		// 3. Wyznaczenie wspolrzednych w ukladzie urzadzenia
		//
		// Wspolrzedne w ukladzie kartezisanskim
		transformVector(r, b);
		transformVector(rErr, bErr);

		//
		// 4. Wyznaczenie bledu
		//
		err = b - bErr;

		//
		// 5. Dodanie pomiaru
		//
		addMeasurement(b, err, r, t, w);

		tlinmUtilsClass::printMatrix(b, "B       = ", "%15.9f");
		{
			Eigen::Vector2d out;
			tlinmUtilsClass::toSpeherical(b, out);

			{
				char pm;
				int  i[4];

				// printf("%25s", s);
				iauA2af(6, out(0), &pm, i);
				printf("X = %c%2.2d:%2.2d:%2.2d.%6.6d; ", pm, i[0], i[1], i[2], i[3]);

				iauA2af(6, out(1), &pm, i);
				printf("Y = %c%2.2d:%2.2d:%2.2d.%6.6d\n", pm, i[0], i[1], i[2], i[3]);
			}
		}

		tlinmUtilsClass::printMatrix(err, "ERR     = ", "%15.9f");
		tlinmUtilsClass::printMatrix(r, "R       = ", "%15.9f");

		std::cout << "-------------------------------------------------------------------------------------"
		          << std::endl;

		try {
			// Wstawienie wektora pomiarowego dla prekosci
			vMeasurements.push_back(tlinmMeasurementsVelocity{});
		}
		catch (std::bad_alloc &exc) {
			throw tlinmException(tlinmException::TLINM_ERROR_ID_MEMORY_ALLOCATION,
			                     "tlinmTestUtility::generateTestData() => memory allocation error.");
		}

		tlinmMeasurementsVelocity &vm = vMeasurements[vMeasurements.size() - 1];

		//
		// 6. Wyznaczenie danych pomiarowych na potrzeby pomiaru prekosci
		//

		//
		// Kolejny kwant czasu
		//
		t += inDT;

		for (int j = 0; j < inSpeedMeasurments; j++) {
			std::cout << "T = " << t << std::endl;

			//
			// 6.1 Wyznaczenie macierzy obrotu w okol osi Z
			//
			if (j != 0)
				buildZRotaionMatrix(inSpeed * t); // Macierz obrotu
			else
				zRotaionMatrix = Eigen::Matrix3d::Identity();

			//
			// 6.2. Aplikowanie bledu do obiektu referencyjnego
			//
			if (!tlinmUtilsClass::testEpsylon(inErrorLevel)) {
				rAlfaErr = drand48() / inErrorLevel;
				rBetaErr = drand48() / inErrorLevel;

				if (drand48() < 0.5)
					rAlfaErr *= -1.0;

				if (drand48() < 0.5)

					rBetaErr *= -1.0;

				//			rAlfaErr = rBetaErr = eeeeeeeeeeeeerrr;

				tlinmUtilsClass::toCartesian(rAlfa + rAlfaErr, rBeta + rBetaErr, rErr);
			} else {
				rErr = r; // Blad jest zerowy
			}

			//
			// 6.3. Wykonanie obrotu wokol osi Z
			//
			rotateVector(r, rRot);
			rotateVector(rErr, rErrRot);

			// 6.4. Wspolrzedne w ukladzie kartezisanskim
			transformVector(rRot, bRot);       // Idelany pomiar
			transformVector(rErrRot, bErrRot); // Pomiar obarczony bledem

			{
				Eigen::Vector2d out;
				tlinmUtilsClass::toSpeherical(bRot, out);

				{
					char pm;
					int  i[4];

					// printf("%25s", s);
					iauA2af(6, out(0), &pm, i);
					printf("X = %c%2.2d:%2.2d:%2.2d.%6.6d; ", pm, i[0], i[1], i[2], i[3]);

					iauA2af(6, out(1), &pm, i);
					printf("Y = %c%2.2d:%2.2d:%2.2d.%6.6d\n", pm, i[0], i[1], i[2], i[3]);
				}
			}

			//
			// 6.5. Blad wyznaczenia pomiaru prekosci
			//
			errRot = bErrRot - bRot;

			//
			// 6.6. Dodanie pomiaru prekosci
			//
			addVMeasurement(bRot, errRot, t, w, vm);

			tlinmUtilsClass::printMatrix(bRot, "BROT    = ", "%15.9f");
			tlinmUtilsClass::printMatrix(errRot, "ERRROT  = ", "%15.9f");
			tlinmUtilsClass::printMatrix(rRot, "RROT    = ", "%15.9f");
			tlinmUtilsClass::printMatrix(rErrRot, "RERRROT = ", "%15.9f");

			std::cout << "-------" << std::endl;

			//
			// 6.7. Kolejny kwant czasu
			//
			t += inDT;
		}
		std::cout << "-------------------------------------------------------------------------------------"
		          << std::endl;
	}
}

// Metoda dodaje nowy pomiar. Dodatkowo wspolrzedne w ukladzie odniesienia sa przeksztalcane na wspolrzedne
// ukladu lokalnego
void tlinmTestUtility::addVMeasurement(const Eigen::Vector3d &m, const Eigen::Vector3d &mErr, const double t,
                                       const double w, tlinmMeasurementsVelocity &vec)
{
	try {
		tlinmUtilsClass ::printMatrix(m, "m", "%f");
		tlinmUtilsClass ::printMatrix(mErr, "mErr", "%f");
		tlinmMeasurementVelocity mV{m(0), m(1), m(2), mErr(0), mErr(1), mErr(2), t, w};
		vec.addMeasurement(mV);
	}
	catch (std::bad_alloc &exc) {
		throw tlinmException(tlinmException::TLINM_ERROR_ID_MEMORY_ALLOCATION,
		                     "tlinmTestUtility::addVMeasurement() => memory allocation error.");
	}
}

Eigen::Matrix3d &tlinmTestUtility::getRotaionMatrix()
{
	return rotaionMatrix;
}

void toDegris(double in, double &d, double &m, double &s)
{
	char minus = 0;

	if (in < 0) {
		in    = fabs(in);
		minus = 1;
	}

	d = floor(in);
	m = floor((in - d) * 60);

	s = ((in - d) * 60 - m) * 60;

	if (minus == 1)
		d = d * -1.0;
}

void tlinmTestUtility::testResult(const Eigen::Matrix3d &in)
{
	auto   iter = getMeasurements().begin();
	double pi   = 3.14159265358979323846264338327950;

	for (int i = 0; iter != getMeasurements().end(); iter++, i++) {
		std::cout << std::endl << "Iteracja [" << i << "]" << std::endl;

		Eigen::Vector3d b1 = (*iter).getObservationVector();
		Eigen::Vector3d r  = (*iter).getReferenceVector();
		Eigen::Vector3d b2 = in * r;
		Eigen::Vector3d bd;

		//		tlinmUtilsClass::printMatrix(b1, "B1    ", "%15.9f");
		//		tlinmUtilsClass::printMatrix(b2, "B2    ", "%15.9f");

		Eigen::Vector2d b1S;
		Eigen::Vector2d b2S;
		Eigen::Vector2d bDS;
		tlinmUtilsClass::toSpeherical(b1, b1S);
		tlinmUtilsClass::toSpeherical(b2, b2S);

		b1S = b1S / 2.0 / pi * 360.0;
		b2S = b2S / 2.0 / pi * 360.0;
		//		bDS = bDS / 2.0 / pi * 360.0;

		bDS = b2S - b1S;


		double d1, m1, s1;
		double d2, m2, s2;

		toDegris(b1S(0), d1, m1, s1);
		toDegris(b1S(1), d2, m2, s2);
		printf("B1 => [%3.0f:%2.0f:%6.3f; %3.0f:%2.0f:%6.3f]\n", d1, m1, s1, d2, m2, s2);

		toDegris(b2S(0), d1, m1, s1);
		toDegris(b2S(1), d2, m2, s2);
		printf("B2 => [%3.0f:%2.0f:%6.3f; %3.0f:%2.0f:%6.3f]\n", d1, m1, s1, d2, m2, s2);

		toDegris(bDS(0), d1, m1, s1);
		toDegris(bDS(1), d2, m2, s2);
		printf("BD => [%3.0f:%2.0f:%6.3f; %3.0f:%2.0f:%6.3f] => [ %15.12f, %15.12f ]\n\n", d1, m1, s1, d2, m2, s2,
		       bDS(0), bDS(1));

		//		tlinmUtilsClass::printMatrix(b1S, "B1    ", "%15.9f");
		//		tlinmUtilsClass::printMatrix(b2S, "B2    ", "%15.9f");
		//		tlinmUtilsClass::printMatrix(bDS, "BDelta", "%15.9f");

		//		bd = b2 - b1;
		//		tlinmUtilsClass::printMatrix(bd, "BDelta", "%15.9f");
		//		tlinmUtilsClass::printMatrix(r,  "R     ", "%15.9f");
	}

	tlinmUtilsClass::printMatrix(getRotaionMatrix(), "Reference matrix", "%15.9f");
	tlinmUtilsClass::printMatrix(in, "Computed matrix ", "%15.9f");
	Eigen::Matrix3d delata = getRotaionMatrix() - in;
	tlinmUtilsClass::printMatrix(delata, "Delta           ", "%15.9f");
}

Eigen::Matrix3d &tlinmTestUtility::buildZRotaionMatrix(const double angle)
{
	tlinmUtilsClass::buildZRotaionMatrix(angle, zRotaionMatrix);
	return zRotaionMatrix;
}

void tlinmTestUtility::transformVector(const Eigen::Vector3d &inVector, Eigen::Vector3d &outVector)
{
	// Wyznaczanie wektora w nowym ukladzie wspolrzednych
	tlinmUtilsClass::printMatrix(inVector, "IN Transfor matrix ", "%15.9f");
	tlinmUtilsClass::printMatrix(rotaionMatrix, "Transfor matrix   ", "%15.9f");
	outVector = rotaionMatrix * inVector;
	tlinmUtilsClass::printMatrix(outVector, "OUT Transfor matrix ", "%15.9f");
}

// Konstruktor klasy
tlinmTestUtility::tlinmTestUtility(const double nuatation, const double precesion, const double rotation)
{

	Eigen::Matrix3d x;
	Eigen::Matrix3d y;
	Eigen::Matrix3d z;

	// X
	x(0, 0) = 1.0;
	x(0, 1) = 0.0;
	x(0, 2) = 0.0;
	x(1, 0) = 0.0;
	x(1, 1) = 1.0 * cos(nuatation);
	x(1, 2) = -1.0 * sin(nuatation);
	x(2, 0) = 0.0;
	x(2, 1) = 1.0 * sin(nuatation);
	x(2, 2) = 1.0 * cos(nuatation);

	// Y
	y(0, 0) = 1.0 * cos(precesion);
	y(0, 1) = 0.0;
	y(0, 2) = 1.0 * sin(precesion);
	y(1, 0) = 0.0;
	y(1, 1) = 1.0;
	y(1, 2) = 0.0;
	y(2, 0) = -1.0 * sin(precesion);
	y(2, 1) = 0.0;
	y(2, 2) = 1.0 * cos(precesion);

	// Z
	z(0, 0) = 1.0 * cos(rotation);
	z(0, 1) = -1.0 * sin(rotation);
	z(0, 2) = 0.0;
	z(1, 0) = 1.0 * sin(rotation);
	z(1, 1) = 1.0 * cos(rotation);
	z(1, 2) = 0.0;
	z(2, 0) = 0.0;
	z(2, 1) = 0.0;
	z(2, 2) = 1.0;

	rotaionMatrix = x * y * z;

	tlinmUtilsClass::printMatrix(rotaionMatrix, "rotaionMatrix", "%15.9f");

	double dd = rotaionMatrix.determinant();
	std::cout << "Wyznacznik = " << dd << std::endl;
}

// Destruktor klasy
tlinmTestUtility::~tlinmTestUtility(void)
{
}
