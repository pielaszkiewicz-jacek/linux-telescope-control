#include "limits.hpp"
#include "tlinAttitudeUtilsClass.hpp"
#include "tlins_math.hpp"
#include <cmath>

namespace limits
{
/*
   Punkty referencyjne okreslone przez uzytkownika definiują stożek który jest fragmentem sfery który jest wykluczony.
   Obszar efektywnie ograniczony jest przez stozek wychodzacy z poczatku ukladu wspolrzednych ktorego powiuechnia
   boczna okreslna jest przez dwie proste
 */
double tlinsLimitsMath::straightLinesAngleDistance(const Eigen::Vector3d &p1, const Eigen::Vector3d &p2)
{
	// Okreslenie konta ktory stanowi limit
	return ::acos(p1.dot(p2) / (p1.norm() * p2.norm()));
}

std::pair<Eigen::Vector3d, Eigen::Vector3d>
tlinsLimitsMath::kinematicsPosition(const std::vector<tlinsLimitsDeviceInfo> &devInfo)
{
}

std::pair<Eigen::Vector3d, Eigen::Vector3d> tlinsLimitsMath::kinematicsPositionGemetric2(
	const double alfa,
	const double beta,
	const double r1,
	const double r2,
	const double dx,
	const double dz,
	const double h,
	const std::vector<std::pair<std::string, double>> &axis)
{

	auto buildMatrix = [](const double a, const double b) {
		Eigen::Matrix3d x;
		Eigen::Matrix3d z;
		attitude::tlinAttitudeUtilsClass::buildXRotaionMatrix(a, x);
		attitude::tlinAttitudeUtilsClass::buildZRotaionMatrix(b, z);
		return x * z;
	};

	Eigen::Matrix3d rotX = buildMatrix(alfa, 0.0);
	Eigen::Matrix3d rotZ = buildMatrix(0.0,  beta);

	Eigen::Matrix3d rotXYZ{Eigen::Matrix3d::Identity()};
	if (axis.size() > 0) {
		for (auto &item : axis) {
			if        (item.first == "X") {
				Eigen::Matrix3d out;
				attitude::tlinAttitudeUtilsClass::buildXRotaionMatrix(item.second, out);
				rotXYZ = rotXYZ * out;
			} else if (item.first == "Y") {
				Eigen::Matrix3d out;
				attitude::tlinAttitudeUtilsClass::buildYRotaionMatrix(item.second, out);
				rotXYZ = rotXYZ * out;
			} else if (item.first == "Z") {
				Eigen::Matrix3d out;
				attitude::tlinAttitudeUtilsClass::buildZRotaionMatrix(item.second, out);
				rotXYZ = rotXYZ * out;
			}
		}
	}

	Eigen::Vector3d vr1{0.0,        r1, 0.0};
	Eigen::Vector3d vr2{0.0, -1.0 * r2, 0.0};

	Eigen::Vector3d rm1{dx,  0.0, 0.0};
	Eigen::Vector3d rm2{0.0, 0.0,  dz};
	Eigen::Vector3d rm3{0.0, 0.0,   h};

	auto res1 = rotXYZ * ( rotZ * ( ( rotX * vr1 ) + rm1 ) + rm2 ) + rm3;
	auto res2 = rotXYZ * ( rotZ * ( ( rotX * vr2 ) + rm1 ) + rm2 ) + rm3;

	return std::pair<Eigen::Vector3d, Eigen::Vector3d>{res1, res2};
}

std::pair<Eigen::Vector3d, Eigen::Vector3d>
tlinsLimitsMath::kinematicsPositionGemetric(const double alfa, const double beta, const double h, const double r1,
                                            const double r2, const double r3,
                                            const std::vector<std::pair<std::string, double>> &axis)
{
	double xr1{0.0};
	double yr1{0.0};
	double zr1{0.0};

	double xr2{0.0};
	double yr2{0.0};
	double zr2{0.0};
	double xr3{0.0};
	double yr3{0.0};
	double zr3{0.0};

	double r2pgx{0.0};
	double r3pgx{0.0};
	double r2pgy{0.0};
	double r3pgy{0.0};

	auto q1 = [r1, r2, r3, beta](double &r2pgx, double &r3pgx, double &r2pgy, double &r3pgy) {
		r2pgx = r2 * ::cos(beta);
		r3pgx = r3 * ::cos(beta);
		r2pgy = r2 * ::cos(beta);
		r3pgy = r3 * ::cos(beta);
	};

	auto q2 = [r1, r2, r3, beta](double &r2pgx, double &r3pgx, double &r2pgy, double &r3pgy) {
		r2pgx = r2 * ::cos(beta - tlinsMath::PI / 2.0);
		r3pgx = r3 * ::cos(beta - tlinsMath::PI / 2.0);
		r2pgy = r2 * ::cos(beta - tlinsMath::PI / 2.0);
		r3pgy = r3 * ::cos(beta - tlinsMath::PI / 2.0);
	};

	auto q3 = [r1, r2, r3, beta](double &r2pgx, double &r3pgx, double &r2pgy, double &r3pgy) {
		r2pgx = r2 * ::cos(beta - tlinsMath::PI);
		r3pgx = r3 * ::cos(beta - tlinsMath::PI);
		r2pgy = r2 * ::cos(beta - tlinsMath::PI);
		r3pgy = r3 * ::cos(beta - tlinsMath::PI);
	};

	auto q4 = [r1, r2, r3, beta](double &r2pgx, double &r3pgx, double &r2pgy, double &r3pgy) {
		r2pgx = r2 * ::cos(2.0 * tlinsMath::PI - beta);
		r3pgx = r3 * ::cos(2.0 * tlinsMath::PI - beta);
		r2pgy = r2 * ::cos(2.0 * tlinsMath::PI - beta);
		r3pgy = r3 * ::cos(2.0 * tlinsMath::PI - beta);
	};

	auto cosq1_ = [](double alfa, double v) { return v * ::cos(tlinsMath::PI / 2.0 - alfa); };
	auto sinq1_ = [](double alfa, double v) { return v * ::sin(tlinsMath::PI / 2.0 - alfa); };

	auto cosq2_ = [](double alfa, double v) { return v * ::cos(alfa - tlinsMath::PI / 2.0); };
	auto sinq2_ = [](double alfa, double v) { return v * ::sin(alfa - tlinsMath::PI / 2.0); };

	auto cosq3_ = [](double alfa, double v) { return v * ::cos(alfa - tlinsMath::PI); };
	auto sinq3_ = [](double alfa, double v) { return v * ::sin(alfa - tlinsMath::PI); };

	auto cosq4_ = [](double alfa, double v) { return v * ::cos(2.0 * tlinsMath::PI - alfa); };
	auto sinq4_ = [](double alfa, double v) { return v * ::sin(2.0 * tlinsMath::PI - alfa); };

	auto sinbq1_ = [](double beta, double v) { return v * ::sin(beta); };
	auto sinbq2_ = [](double beta, double v) { return v * ::sin(beta - tlinsMath::PI / 2.0); };
	auto sinbq3_ = [](double beta, double v) { return v * ::sin(beta - tlinsMath::PI); };
	auto sinbq4_ = [](double beta, double v) { return v * ::sin(2.0 * tlinsMath::PI - beta); };

	if (alfa < (tlinsMath::PI / 2.0)) {
		xr1 = r1 * ::cos(alfa);
		yr1 = r1 * ::sin(alfa);
		zr1 = h;

		if (beta < (tlinsMath::PI / 2.0)) {
			q1(r2pgx, r3pgx, r2pgy, r3pgy);
			xr2 = xr1 + cosq1_(alfa, r2pgx);
			xr3 = xr1 - cosq1_(alfa, r3pgx);
			yr2 = yr1 - sinq1_(alfa, r2pgy);
			yr3 = yr1 + sinq1_(alfa, r3pgy);
			zr2 = zr1 + sinbq1_(beta, r2);
			zr3 = zr1 - sinbq1_(beta, r3);
		} else if (beta < tlinsMath::PI) {
			q2(r2pgx, r3pgx, r2pgy, r3pgy);
			xr2 = xr1 - cosq1_(alfa, r2pgx);
			xr3 = xr1 + cosq1_(alfa, r3pgx);
			yr2 = yr1 + sinq1_(alfa, r2pgy);
			yr3 = yr1 - sinq1_(alfa, r3pgy);
			zr2 = zr1 + sinbq2_(beta, r2);
			zr3 = zr1 - sinbq2_(beta, r3);
		} else if (beta < (3.0 / 2.0 * tlinsMath::PI)) {
			q3(r2pgx, r3pgx, r2pgy, r3pgy);
			xr2 = xr1 - cosq1_(alfa, r2pgx);
			xr3 = xr1 + cosq1_(alfa, r3pgx);
			yr2 = yr1 + sinq1_(alfa, r2pgy);
			yr3 = yr1 - sinq1_(alfa, r3pgy);
			zr2 = zr1 - sinbq3_(beta, r2);
			zr3 = zr1 + sinbq3_(beta, r3);
		} else {
			q4(r2pgx, r3pgx, r2pgy, r3pgy);
			xr2 = xr1 + cosq1_(alfa, r2pgx);
			xr3 = xr1 - cosq1_(alfa, r3pgx);
			yr2 = yr1 - sinq1_(alfa, r2pgy);
			yr3 = yr1 + sinq1_(alfa, r3pgy);
			zr2 = zr1 - sinbq4_(beta, r2);
			zr3 = zr1 + sinbq4_(beta, r3);
		}
	} else if (alfa < tlinsMath::PI) {
		xr1 = -1.0 * r1 * cos(tlinsMath::PI - alfa);
		yr1 = r1 * sin(tlinsMath::PI - alfa);
		zr1 = h;

		if (beta < (tlinsMath::PI / 2.0)) {
			q1(r2pgx, r3pgx, r2pgy, r3pgy);
			xr2 = xr1 + cosq2_(alfa, r2pgx);
			xr3 = xr1 - cosq2_(alfa, r3pgx);
			yr2 = yr1 + sinq2_(alfa, r2pgy);
			yr3 = yr1 - sinq2_(alfa, r3pgy);
			zr2 = zr1 + sinbq1_(beta, r2);
			zr3 = zr1 - sinbq1_(beta, r3);
		} else if (beta < tlinsMath::PI) {
			q2(r2pgx, r3pgx, r2pgy, r3pgy);
			xr2 = xr1 - cosq2_(alfa, r2pgx);
			xr3 = xr1 + cosq2_(alfa, r3pgx);
			yr2 = yr1 - sinq2_(alfa, r2pgy);
			yr3 = yr1 + sinq2_(alfa, r3pgy);
			zr2 = zr1 + sinbq2_(beta, r2);
			zr3 = zr1 - sinbq2_(beta, r3);
		} else if (beta < (3.0 / 2.0 * tlinsMath::PI)) {
			q3(r2pgx, r3pgx, r2pgy, r3pgy);
			xr2 = xr1 - cosq2_(alfa, r2pgx);
			xr3 = xr1 + cosq2_(alfa, r3pgx);
			yr2 = yr1 - sinq2_(alfa, r2pgy);
			yr3 = yr1 + sinq2_(alfa, r3pgy);
			zr2 = zr1 - sinbq3_(beta, r2);
			zr3 = zr1 + sinbq3_(beta, r3);
		} else {
			q4(r2pgx, r3pgx, r2pgy, r3pgy);
			xr2 = xr1 + cosq2_(alfa, r2pgx);
			xr3 = xr1 - cosq2_(alfa, r3pgx);
			yr2 = yr1 + sinq2_(alfa, r2pgy);
			yr3 = yr1 - sinq2_(alfa, r3pgy);
			zr2 = zr1 - sinbq4_(beta, r2);
			zr3 = zr1 + sinbq4_(beta, r3);
		}
	} else if (alfa <= (3.0 / 2.0 * tlinsMath::PI)) {
		xr1 = -1.0 * r1 * ::cos(alfa - tlinsMath::PI);
		yr1 = -1.0 * r1 * ::sin(alfa - tlinsMath::PI);
		zr1 = h;

		if (beta < (tlinsMath::PI / 2.0)) {
			q1(r2pgx, r3pgx, r2pgy, r3pgy);
			xr2 = xr1 - cosq3_(alfa, r2pgx);
			xr3 = xr1 + cosq3_(alfa, r3pgx);
			yr2 = yr1 + sinq3_(alfa, r2pgy);
			yr3 = yr1 - sinq3_(alfa, r3pgy);
			zr2 = zr1 + sinbq1_(beta, r2);
			zr3 = zr1 - sinbq1_(beta, r3);
		} else if (beta < tlinsMath::PI) {
			q2(r2pgx, r3pgx, r2pgy, r3pgy);
			xr2 = xr1 + cosq3_(alfa, r2pgx);
			xr3 = xr1 - cosq3_(alfa, r3pgx);
			yr2 = yr1 - sinq3_(alfa, r2pgy);
			yr3 = yr1 + sinq3_(alfa, r3pgy);
			zr2 = zr1 + sinbq2_(beta, r2);
			zr3 = zr1 - sinbq2_(beta, r3);
		} else if (beta < (3.0 / 2.0 * tlinsMath::PI)) {
			q3(r2pgx, r3pgx, r2pgy, r3pgy);
			xr2 = xr1 + cosq3_(alfa, r2pgx);
			xr3 = xr1 - cosq3_(alfa, r3pgx);
			yr2 = yr1 - sinq3_(alfa, r2pgy);
			yr3 = yr1 + sinq3_(alfa, r3pgy);
			zr2 = zr1 - sinbq3_(beta, r2);
			zr3 = zr1 + sinbq3_(beta, r3);
		} else {
			q4(r2pgx, r3pgx, r2pgy, r3pgy);
			xr2 = xr1 - cosq3_(alfa, r2pgx);
			xr3 = xr1 + cosq3_(alfa, r3pgx);
			yr2 = yr1 + sinq3_(alfa, r2pgy);
			yr3 = yr1 - sinq3_(alfa, r3pgy);
			zr2 = zr1 - sinbq4_(beta, r2);
			zr3 = zr1 + sinbq4_(beta, r3);
		}
	} else {
		xr1 = r1 * cos(2 * tlinsMath::PI - alfa);
		yr1 = -1.0 * r1 * sin(2 * tlinsMath::PI - alfa);
		zr1 = h;

		if (beta < (tlinsMath::PI / 2.0)) {
			q1(r2pgx, r3pgx, r2pgy, r3pgy);
			xr2 = xr1 - cosq4_(alfa, r2pgx);
			xr3 = xr1 + cosq4_(alfa, r3pgx);
			yr2 = yr1 - sinq4_(alfa, r2pgy);
			yr3 = yr1 + sinq4_(alfa, r3pgy);
			zr2 = zr1 + sinbq1_(beta, r2);
			zr3 = zr1 - sinbq1_(beta, r3);
		} else if (beta < tlinsMath::PI) {
			q2(r2pgx, r3pgx, r2pgy, r3pgy);
			xr2 = xr1 + cosq4_(alfa, r2pgx);
			xr3 = xr1 - cosq4_(alfa, r3pgx);
			yr2 = yr1 + sinq4_(alfa, r2pgy);
			yr3 = yr1 - sinq4_(alfa, r3pgy);
			zr2 = zr1 + sinbq2_(beta, r2);
			zr3 = zr1 - sinbq2_(beta, r3);
		} else if (beta < (3.0 / 2.0 * tlinsMath::PI)) {
			q3(r2pgx, r3pgx, r2pgy, r3pgy);
			xr2 = xr1 + cosq4_(alfa, r2pgx);
			xr3 = xr1 - cosq4_(alfa, r3pgx);
			yr2 = yr1 + sinq4_(alfa, r2pgy);
			yr3 = yr1 - sinq4_(alfa, r3pgy);
			zr2 = zr1 - sinbq3_(beta, r2);
			zr3 = zr1 + sinbq3_(beta, r3);
		} else {
			q4(r2pgx, r3pgx, r2pgy, r3pgy);
			xr2 = xr1 - cosq4_(alfa, r2pgx);
			xr3 = xr1 + cosq4_(alfa, r3pgx);
			yr2 = yr1 - sinq4_(alfa, r2pgy);
			yr3 = yr1 + sinq4_(alfa, r3pgy);
			zr2 = zr1 - sinbq4_(beta, r2);
			zr3 = zr1 + sinbq4_(beta, r3);
		}
	}

	// Rotacja wynikajaca z pochylenia calego ukladu
	Eigen::Matrix3d rotationMatrix{Eigen::Matrix3d::Identity()};

	if (axis.size() > 0) {
		for (auto &item : axis) {
			if (item.first == "X") {
				Eigen::Matrix3d out;
				attitude::tlinAttitudeUtilsClass::buildXRotaionMatrix(item.second, out);
				rotationMatrix = rotationMatrix * out;
			} else if (item.first == "Y") {
				Eigen::Matrix3d out;
				attitude::tlinAttitudeUtilsClass::buildYRotaionMatrix(item.second, out);
				rotationMatrix = rotationMatrix * out;
			} else if (item.first == "Z") {
				Eigen::Matrix3d out;
				attitude::tlinAttitudeUtilsClass::buildZRotaionMatrix(item.second, out);
				rotationMatrix = rotationMatrix * out;
			}
		}
	}
	return std::pair<Eigen::Vector3d, Eigen::Vector3d>{rotationMatrix * Eigen::Vector3d{xr2, yr2, zr2},
	                                                   rotationMatrix * Eigen::Vector3d{xr3, yr3, zr3}};
}

Eigen::Vector3d tlinsLimitsMath::midlePoint(const Eigen::Vector3d &p1, const Eigen::Vector3d &p2)
{
	return Eigen::Vector3d{(p1(0) + p2(0)) / 2.0, (p1(1) + p2(1)) / 2.0, (p1(2) + p2(2)) / 2.0};
}

bool tlinsLimitsMath::isInRange(const Eigen::Vector3d &p1, const Eigen::Vector3d &p2, const Eigen::Vector3d &pos)
{
	auto m         = tlinsLimitsMath::midlePoint(p1, p2);
	auto baseAngle = tlinsLimitsMath::angleBetweenVectrors(m, p1);

	auto testedAngle = tlinsLimitsMath::angleBetweenVectrors(m, pos);
	return testedAngle < baseAngle;
}

double tlinsLimitsMath::angleBetweenVectrors(const Eigen::Vector3d &p1, const Eigen::Vector3d &p2)
{
	return ::acos(p1.dot(p2) / (p1.norm() * p2.norm()));
}

bool tlinsLimitsMath::isInRange(const std::vector<std::tuple<Eigen::Vector3d, Eigen::Vector3d>> &limits,
                                const Eigen::Vector3d                                           &pos)
{
	for (auto &item : limits) {
		auto p1 = std::get<0>(item);
		auto p2 = std::get<1>(item);
		if (!tlinsLimitsMath::isInRange(p1, p2, pos)) {
			return false;
		}
	}
	return true;
}

}; // namespace limits