#include <tlinAttitudeUtilsClass.hpp>
#include <tlinsBacktrace.hpp>
#include <tlinsLogger.hpp>
#include <tlins_math.hpp>

#include <Eigen/Geometry>
#include <cmath>
#include <limits>
#include <math.h>
#include <stdio.h>
#include <unsupported/Eigen/MatrixFunctions>

namespace attitude
{

double tlinAttitudeUtilsClass::epsylon      = DBL_EPSILON;
double tlinAttitudeUtilsClass::epsylonError = 0.000001;

double tlinAttitudeUtilsClass::pi = M_PI;

void tlinAttitudeUtilsClass::estimnateRotationSpeed(const Eigen::Vector3d &v1_, const Eigen::Vector3d &v2_,
                                                    const double dt, Eigen::Vector3d &output)
{
	auto norm = [](const Eigen::Vector3d &v) -> Eigen::Vector3d {
		return v * 1.0 / ::sqrt(v(0) * v(0) + v(1) * v(1) + v(2) * v(2));
	};

	auto norm_ = [](const Eigen::Vector3d &v) -> double { return ::sqrt(v(0) * v(0) + v(1) * v(1) + v(2) * v(2)); };

	auto dot = [&](const Eigen::Vector3d &v1, const Eigen::Vector3d &v2) -> double {
		double n1 = norm_(v1);
		double n2 = norm_(v2);

		auto ret = v1(0) * v2(0) + v1(1) * v2(1) + v1(2) * v2(2);
		return ret / (n1 * n2);
	};

	auto v1__ = v1_;
	auto v2__ = v2_;


	PRINT_M(v1_, "v1_", "%f");
	PRINT_M(v2_, "v2_", "%f");

	// X
	{
		Eigen::Vector3d v1 = v1__;
		Eigen::Vector3d v2 = v2__;

		v1(0) = 0.0;
		v2(0) = 0.0;

		double angle = ::acos(dot(v2, v1));
		output(0)    = angle / dt;
		TLINS_LOG_DEBUG("ANGLE = " + std::to_string(angle));
	}

	// Y
	{
		Eigen::Vector3d v1 = v1__;
		Eigen::Vector3d v2 = v2__;

		v1(1) = 0.0;
		v2(1) = 0.0;

		double angle = ::acos(dot(v2, v1));
		output(1)    = angle / dt;
		TLINS_LOG_DEBUG("ANGLE = " + std::to_string(angle));
	}

	// Z
	{
		Eigen::Vector3d v1 = v1__;
		Eigen::Vector3d v2 = v2__;

		v1(2) = 0.0;
		v2(2) = 0.0;

		double angle = ::acos(dot(v2, v1));
		output(2)    = angle / dt;
		TLINS_LOG_DEBUG("ANGLE = " + std::to_string(angle));
	}
}

void tlinAttitudeUtilsClass::toCartesian(const double alfa, const double beta, Eigen::Vector3d &axis)
{
	axis(0) = ::cos(beta) * ::cos(alfa);
	axis(1) = ::cos(beta) * ::sin(alfa);
	axis(2) = ::sin(beta);
}


Eigen::Vector3d tlinAttitudeUtilsClass::toCartesianBase(const double alfa, const double beta)
{
	Eigen::Vector3d axis;
	axis(0) = ::cos(beta) * ::cos(alfa);
	axis(1) = ::cos(beta) * ::sin(alfa);
	axis(2) = ::sin(beta);
	return axis;
}

void tlinAttitudeUtilsClass::toCartesian(const Eigen::Vector2d &in, Eigen::Vector3d &axis)
{
	axis(0) = ::cos(in(1)) * ::cos(in(0));
	axis(1) = ::cos(in(1)) * ::sin(in(0));
	axis(2) = ::sin(in(1));
}

void tlinAttitudeUtilsClass::toSpeherical(const Eigen::Vector3d &in, Eigen::Vector2d &out)
{
	out(0) = ::atan2(in(1), in(0));
	auto r = ::sqrt((in(0) * in(0)) + (in(1) * in(1)) + (in(2) * in(2)));
	out(1) = ::asin(in(2) / r);
}

static void buildXRotaionMatrix_(const double angle, Eigen::Matrix3d &out)
{
	out = Eigen::AngleAxisd(angle, Eigen::Vector3d::UnitX()).matrix();
}

void tlinAttitudeUtilsClass::buildXRotaionMatrix(const double angle, Eigen::Matrix3d &out)
{
	Eigen::Matrix3d out_;
	buildXRotaionMatrix_(angle, out_);
	// out = out_.transpose();
	out = out_;
}

static void buildYRotaionMatrix_(const double angle, Eigen::Matrix3d &out)
{
	out = Eigen::AngleAxisd(angle, Eigen::Vector3d::UnitY()).matrix();
}

void tlinAttitudeUtilsClass::buildYRotaionMatrix(const double angle, Eigen::Matrix3d &out)
{
	Eigen::Matrix3d out_;
	buildYRotaionMatrix_(angle, out_);
	// out = out_.transpose();
	out = out_;
}

static void buildZRotaionMatrix_(const double angle, Eigen::Matrix3d &out)
{
	out = Eigen::AngleAxisd(angle, Eigen::Vector3d::UnitZ()).matrix();
}

void tlinAttitudeUtilsClass::buildZRotaionMatrix(const double angle, Eigen::Matrix3d &out)
{
	Eigen::Matrix3d out_;
	buildZRotaionMatrix_(angle, out_);
	out = out_;
}

void tlinAttitudeUtilsClass::buildXYZRotaionMatrix(const double a, const double b, const double g, Eigen::Matrix3d &out)
{
	double          su = sin(a); // s1
	double          cu = cos(a); // c1
	double          sv = sin(b); // s2
	double          cv = cos(b); // c2
	double          sw = sin(g); // s3
	double          cw = cos(g); // c3
	Eigen::Matrix3d Rot_matrix(3, 3);
	Rot_matrix(0, 0) = cv * cw; // c2 * c3
	Rot_matrix(0, 1) = su * sv * cw - cu * sw;
	Rot_matrix(0, 2) = su * sw + cu * sv * cw;
	Rot_matrix(1, 0) = cv * sw;
	Rot_matrix(1, 1) = cu * cw + su * sv * sw;
	Rot_matrix(1, 2) = cu * sv * sw - su * cw;
	Rot_matrix(2, 0) = -sv;
	Rot_matrix(2, 1) = su * cv;
	Rot_matrix(2, 2) = cu * cv;
	// out              = Rot_matrix.transpose();
	out = Rot_matrix;
	// PRINT_M(out,  "OUT  ", "%f");
}

bool tlinAttitudeUtilsClass::testEpsylon(const double val)
{
	return ::fabs(val) < epsylon;
}

void tlinAttitudeUtilsClass::normaliseCartesian(const Eigen::Vector3d &in, Eigen::Vector3d &out)
{
	Eigen::Vector2d v;
	tlinAttitudeUtilsClass::toSpeherical(in, v);
	while (v[0] < 0.0)
		v[0] = v[0] + tlinsMath::PI_2;

	tlinAttitudeUtilsClass::toCartesian(v[0], v[1], out);
}

void tlinAttitudeUtilsClass::create_B(const Eigen::Vector3d &ref, const Eigen::Vector3d &obs, const double weight,
                                      Eigen::Matrix3d &B)
{
	B = (weight * obs * ref.transpose());
}

void tlinAttitudeUtilsClass::create_B(const std::vector<Eigen::Vector3d> &ref, const std::vector<Eigen::Vector3d> &obs,
                                      const std::vector<double> weight, Eigen::Matrix3d &B)
{
	B        = Eigen::Matrix3d::Zero();
	int size = ref.size();

	for (int i = 0; i < size; i++) {
		auto r = ref[i];
		auto b = obs[i];
		auto w = weight[i];

		Eigen::Matrix3d B_;
		tlinAttitudeUtilsClass::create_B(r, b, w, B_);
		B = B + B_;
	}
}

void tlinAttitudeUtilsClass::create_S(const Eigen::Matrix3d &B, Eigen::Matrix3d &S)
{
	S = B + B.transpose();
}

void tlinAttitudeUtilsClass::create_Z(const Eigen::Matrix3d &B, Eigen::Vector3d &Z)
{
	Z(0) = B(1, 2) - B(2, 1);
	Z(1) = B(2, 0) - B(0, 2);
	Z(2) = B(0, 1) - B(1, 0);
}

void tlinAttitudeUtilsClass::create_Z(const Eigen::Vector3d &ref, const Eigen::Vector3d &obs, const double weight,
                                      Eigen::Vector3d &Z)
{
	Eigen::Vector3d tmp = weight * obs;
	Z                   = tmp.cross(ref);
}

void tlinAttitudeUtilsClass::create_sigma(const Eigen::Matrix3d &B, double &sigma)
{
	sigma = B.trace();
}

void tlinAttitudeUtilsClass::calculate_inv(const Eigen::Matrix3d &in, Eigen::Matrix3d &out)
{
	Eigen::Matrix3d v;

	v(0, 0) = in(1, 1) * in(2, 2) - in(1, 2) * in(2, 1);
	v(0, 1) = in(0, 2) * in(2, 1) - in(0, 1) * in(2, 2);
	v(0, 2) = in(0, 1) * in(1, 2) - in(0, 2) * in(1, 1);

	v(1, 0) = in(1, 2) * in(2, 0) - in(1, 0) * in(2, 2);
	v(1, 1) = in(0, 0) * in(2, 2) - in(0, 2) * in(2, 0);
	v(1, 2) = in(0, 2) * in(1, 0) - in(0, 0) * in(1, 2);

	v(2, 0) = in(0, 1) * in(2, 1) - in(1, 1) * in(2, 0);
	v(2, 1) = in(0, 1) * in(2, 1) - in(0, 0) * in(2, 1);
	v(2, 2) = in(0, 0) * in(1, 1) - in(0, 1) * in(1, 0);

	out = 1.0 / in.determinant() * v;
}

void tlinAttitudeUtilsClass::build_Q(const double lambda, const double sigma, const Eigen::Matrix3d &S,
                                     const Eigen::Vector3d &Z, Eigen::Vector3d &Q)
{
	Eigen::Matrix3d v = (lambda + sigma) * Eigen::Matrix3d::Identity() - S;
	Q                 = v.inverse() * Z;
}

void tlinAttitudeUtilsClass::create_K(const Eigen::Matrix3d &S, const Eigen::Vector3d &Z, const double sigma,
                                      const double w, Eigen::Matrix4d &K)
{
	Eigen::Matrix4d resultK;

	resultK.block<3, 3>(0, 0) = S - sigma * Eigen::Matrix3d::Identity();

	for (int i = 0; i < 3; i++) {
		resultK(3, i) = Z(i);
		resultK(i, 3) = Z(i);
	}
	resultK(3, 3) = sigma;
	K             = (1.0 / w) * resultK;
}

void tlinAttitudeUtilsClass::create_exp(const Eigen::Matrix4d &m, Eigen::Matrix4d out)
{
	out = m.exp();
}

void tlinAttitudeUtilsClass::create_exp(const Eigen::Matrix3d &m, Eigen::Matrix3d out)
{
	out = m.exp();
}

// 1 - kolumna, 2 - wiersz
void tlinAttitudeUtilsClass::create_ex(const Eigen::Vector3d &v, Eigen::Matrix3d &out)
{
	out(0, 0) = 0.0;
	out(0, 1) = 1 * v(2);
	out(0, 2) = -1 * v(1);

	out(1, 0) = -1 * v(2);
	out(1, 1) = 0.0;
	out(1, 2) = 1 * v(0);

	out(2, 0) = 1 * v(1);
	out(2, 1) = -1 * v(0);
	out(2, 2) = 0.0;
}

void tlinAttitudeUtilsClass::create_ex(const Eigen::Vector3d &v, Eigen::Matrix4d &out_)
{
	Eigen::Matrix4d out;
	Eigen::Matrix3d ex3_;
	create_ex(v, ex3_);

	Eigen::Matrix3d ex3 = -1.0 * ex3_;

	out(0, 0) = ex3(0, 0);
	out(0, 1) = ex3(0, 1);
	out(0, 2) = ex3(0, 2);

	out(1, 0) = ex3(1, 0);
	out(1, 1) = ex3(1, 1);
	out(1, 1) = ex3(1, 2);

	out(2, 0) = ex3(2, 0);
	out(2, 1) = ex3(2, 1);
	out(2, 1) = ex3(2, 1);

	out(0, 3) = -1.0 * v(0);
	out(1, 3) = -1.0 * v(1);
	out(2, 3) = -1.0 * v(2);

	out(3, 0) = 1.0 * v(0);
	out(3, 1) = 1.0 * v(1);
	out(3, 2) = 1.0 * v(2);

	out(3, 3) = 0.0;

	out_ = 0.5 * out;
}

void tlinAttitudeUtilsClass::create_omega(const Eigen::Vector3d &v, Eigen::Matrix4d &m)
{
	Eigen::Matrix3d e;
	create_ex(v, e);

	m.block(0, 0, 3, 3) = -0.5 * e;

	m(3, 0) = -0.5 * v(0);
	m(3, 1) = -0.5 * v(1);
	m(3, 2) = -0.5 * v(2);
	m(0, 3) = 0.5 * v(0);
	m(1, 3) = 0.5 * v(1);
	m(2, 3) = 0.5 * v(2);
	m(3, 3) = 0.0;
}

void tlinAttitudeUtilsClass::create_exp(const Eigen::Matrix4d &in, Eigen::Matrix4d &out, const int res)
{
	// Zerowa iteracja
	unsigned long   sil = 1;
	Eigen::Matrix4d mm  = in;
	Eigen::Matrix4d output{Eigen::Matrix4d::Identity()};

	for (unsigned long i = 1; i < static_cast<unsigned long>(res); i++) {
		double c = 1.0 / static_cast<double>(sil);
		output += c * mm;

		// Potegowanie macierzy wejsciowej
		mm  = mm * in;
		sil = sil * i;
	}
	out = output;
}

void tlinAttitudeUtilsClass::create_exp(const Eigen::Matrix4d &in, Eigen::Matrix4d &out, const int res, const double t)
{
	Eigen::Matrix4d rTmpPow;
	Eigen::Matrix4d rTmp;
	Eigen::Matrix4d test;
	Eigen::Matrix4d I4;

	rTmp = I4 * t + in * t;

	double sil = 1.0;
	for (int i = 2; i <= res; i++) {
		rTmpPow = in;
		for (int j = 0; j < (i - 1); j++)
			rTmpPow *= in;

		sil *= static_cast<double>(i);
		rTmp += t * rTmpPow / sil;
	}
	out = rTmp;
}

void tlinAttitudeUtilsClass::create_FI(const Eigen::Matrix4d &omega, const double deltaT, Eigen::Matrix4d &fi)
{
	const Eigen::Matrix4d omegaTmp = deltaT * omega;
	tlinAttitudeUtilsClass::create_exp(omegaTmp, fi, 10);
}

void tlinAttitudeUtilsClass::create_R(const Eigen::Vector3d &ref, const Eigen::Vector3d &obsErr, const double mi,
                                      Eigen::Matrix4d &R)
{
	Eigen::Matrix3d R11;
	double          R22 = 2.0 * mi;

	Eigen::Matrix3d refx;
	tlinAttitudeUtilsClass::create_ex(ref, refx);
	double _a1_ = ref.transpose() * obsErr;
	auto   _a_  = _a1_ * _a1_;

	Eigen::Matrix3d R11_a = (3.0 - _a_) * Eigen::Matrix3d::Identity();
	Eigen::Matrix3d R11_b = (obsErr.transpose() * ref) * (obsErr * ref.transpose() + ref * obsErr.transpose());
	Eigen::Matrix3d R11_c = refx * (obsErr * obsErr.transpose()) * refx.transpose();
	R11                   = mi * (R11_a + R11_b + R11_c);
	R                     = Eigen::Matrix4d::Zero();

	R(0, 0) = R11(0, 0);
	R(0, 1) = R11(0, 1);
	R(0, 2) = R11(0, 2);

	R(1, 0) = R11(1, 0);
	R(1, 1) = R11(1, 1);
	R(1, 2) = R11(1, 2);

	R(2, 0) = R11(2, 0);
	R(2, 1) = R11(2, 1);
	R(2, 2) = R11(2, 2);

	R(3, 3) = R22;
}

void tlinAttitudeUtilsClass::create_Q(const Eigen::Matrix3d &B, const Eigen::Vector3d &Z, const double sigma,
                                      const double eta, Eigen::Matrix4d &Q)
{
	Eigen::Matrix3d Q11 = Eigen::Matrix3d::Zero();
	Eigen::Vector3d Q12 = Eigen::Vector3d::Zero();
	Eigen::Vector3d Q21 = Eigen::Vector3d::Zero();
	double          Q22{0.0};

	// Q11
	// printMatrix(B, "B", "%+2.15f");
	Eigen::Matrix3d Bm = B * B.transpose();
	// printMatrix(Bm, "Bm", "%+2.15f");

	double _z_ = Z.transpose() * Z;

	Eigen::Matrix3d Q11_a = 1.0 * (_z_ + (sigma * sigma) - Bm.trace()) * Eigen::Matrix3d::Identity();
	Eigen::Matrix3d Q11_b = 2.0 * ((B.transpose() * B) - (B * B) - (B.transpose() * B.transpose()));
	Q11                   = eta * (Q11_a + Q11_b);
	// printMatrix(Q11_a, "Q11_a", "%+2.15f");
	// printMatrix(Q11_b, "Q11_b", "%+2.15f");
	// printMatrix(Q11, "Q11", "%+2.15f");

	// Q12
	Eigen::Matrix3d M  = B * (B - (sigma * Eigen::Matrix3d::Identity()));
	Eigen::Matrix3d yx = M.transpose() - M;
	Eigen::Vector3d y;

	// printMatrix(M, "M", "%+2.15f");
	// printMatrix(yx, "yx", "%+2.15f");

	y(0) = yx(1, 2);
	y(1) = yx(2, 0);
	y(2) = yx(0, 1);

	// printMatrix(y, "y", "%+2.15f");

	Q12 = -1.0 * eta * (y + (B.transpose() * Z));

	// printMatrix(Q12, "Q12", "%+2.15f");

	// Q21
	Q21 = Q12.transpose();

	// printMatrix(Q21, "Q21", "%+2.15f");

	// Q22
	Q22 = eta * (Bm.trace() + (sigma * sigma) + (Z.transpose() * Z));

	Q(0, 0) = Q11(0, 0);
	Q(0, 1) = Q11(0, 1);
	Q(0, 2) = Q11(0, 2);
	Q(1, 0) = Q11(1, 0);
	Q(1, 1) = Q11(1, 1);
	Q(1, 2) = Q11(1, 2);
	Q(2, 0) = Q11(2, 0);
	Q(2, 1) = Q11(2, 1);
	Q(2, 2) = Q11(2, 2);

	Q(0, 3) = Q12(0);
	Q(1, 3) = Q12(1);
	Q(2, 3) = Q12(2);

	Q(3, 0) = Q21(0);
	Q(3, 0) = Q21(1);
	Q(3, 0) = Q21(2);

	Q(3, 3) = Q22;
}

void tlinAttitudeUtilsClass::create_attitude(const Eigen::Matrix4d &K, Eigen::Vector4d &eigenvalues,
                                             Eigen::Matrix4d &eigenvectors, double &lambda, Eigen::Matrix3d &optimalQ_)
{
	Eigen::Matrix4d A = K;
	Eigen::Matrix4d B = Eigen::Matrix4d::Identity();

	Eigen::GeneralizedSelfAdjointEigenSolver<Eigen::MatrixXd> es(A, B);

	eigenvalues  = es.eigenvalues();
	eigenvectors = es.eigenvectors();

	// Okreslenie optymalnego Q
	Eigen::Quaterniond optimalQ;
	optimalQ = eigenvectors.col(0);
	lambda   = eigenvalues(0);
	for (int i = 0; i < 4; i++) {
		if (eigenvalues(i) > lambda) {
			optimalQ = eigenvectors.col(i);
			lambda   = eigenvalues(i);
		}
	}

	// Eigen::Quaterniond qq(optimalQ[0], optimalQ[1], optimalQ[2], optimalQ[3]);
	optimalQ_ = optimalQ.toRotationMatrix();
}

void tlinAttitudeUtilsClass::create_attitude(const Eigen::Vector3d &Q, Eigen::Matrix3d &O_)
{
	Eigen::Matrix3d O;
	double          m  = ::sqrt(1 + Q.transpose() * Q);
	double          b0 = 1.0 / m;
	double          b1 = Q(0) / m;
	double          b2 = Q(1) / m;
	double          b3 = Q(2) / m;

	O(0, 0) = b0 * b0 + b1 * b1 - b2 * b2 - b3 * b3;
	O(0, 1) = 2.0 * (b1 * b2 + b0 * b3);
	O(0, 2) = 2.0 * (b1 * b3 - b0 * b2);

	O(1, 0) = 2.0 * (b1 * b2 - b0 * b3);
	O(1, 1) = b0 * b0 - b1 * b1 + b2 * b2 - b3 * b3;
	O(1, 2) = 2.0 * (b2 * b3 + b0 * b1);

	O(2, 0) = 2.0 * (b1 * b3 + b0 * b2);
	O(2, 1) = 2.0 * (b2 * b3 - b0 * b1);
	O(2, 2) = b0 * b0 - b1 * b1 - b2 * b2 + b3 * b3;

	// O_ = O.transpose();
	O_ = O;
}


double tlinAttitudeUtilsClass::claculate_function_F(const Eigen::Matrix4d &K, const double l)
{
	Eigen::Matrix4d v = K - l * Eigen::Matrix4d::Identity();
	return v.determinant();
}

double tlinAttitudeUtilsClass::calculate_derivative_F(const Eigen::Matrix4d &K, const double ll)
{
	double a = ll;
	double x = a + 1.0 / 100000.0;

	double v1 = claculate_function_F(K, a);
	double v2 = claculate_function_F(K, x);

	return (v2 - v1) / (x - a);
}

//
// --------------------------------------------------
// --------------------------------------------------
// --------------------------------------------------
//

//
// Drukowanie zawartosci macierzy 4x4, 3x3 oraz wektorow 1x4 i 1x3
//
void tlinAttitudeUtilsClass::printMatrix(const Eigen::Matrix3d &m, const char *name, const char *format)
{
	std::string out;
	TLINS_LOG_DEBUG(tlinAttitudeUtilsClass::printMatrix(m, out, name, format));
}

void tlinAttitudeUtilsClass::printMatrix(const Eigen::Matrix4d &m, const char *name, const char *format)
{
	std::string out;
	TLINS_LOG_DEBUG(tlinAttitudeUtilsClass::printMatrix(m, out, name, format));
}

void tlinAttitudeUtilsClass::printMatrix(const Eigen::Vector2d &m, const char *name, const char *format)
{
	std::string out;
	TLINS_LOG_DEBUG(tlinAttitudeUtilsClass::printMatrix(m, out, name, format));
}

void tlinAttitudeUtilsClass::printMatrix(const Eigen::Vector3d &m, const char *name, const char *format)
{
	std::string out;
	TLINS_LOG_DEBUG(tlinAttitudeUtilsClass::printMatrix(m, out, name, format));
}

void tlinAttitudeUtilsClass::printMatrix(const Eigen::Vector4d &m, const char *name, const char *format)
{
	std::string out;
	TLINS_LOG_DEBUG(tlinAttitudeUtilsClass::printMatrix(m, out, name, format));
}

std::string tlinAttitudeUtilsClass::printMatrix(const Eigen::Matrix3d &m, std::string &out, const char *name,
                                                const char *format)
{
	char        tmpTab[4096];
	int         nLen = strlen(name);
	std::string blankStr("");
	std::string f1("");
	std::string f2("");
	std::string f3("");

	for (int i = 0; i < nLen; i++)
		blankStr.append(" ");

	f1 = "\n%s   | ";
	f1.append(format);
	f1.append(", ");
	f1.append(format);
	f1.append(", ");
	f1.append(format);
	f1.append(" |\n");

	f2 = "%s = | ";
	f2.append(format);
	f2.append(", ");
	f2.append(format);
	f2.append(", ");
	f2.append(format);
	f2.append(" |\n");

	f3 = "%s   | ";
	f3.append(format);
	f3.append(", ");
	f3.append(format);
	f3.append(", ");
	f3.append(format);
	f3.append(" |\n");

	out = "";
	sprintf(tmpTab, f1.c_str(), blankStr.c_str(), m(0, 0), m(1, 0), m(2, 0));
	out.append(tmpTab);
	sprintf(tmpTab, f2.c_str(), name, m(0, 1), m(1, 1), m(2, 1));
	out.append(tmpTab);
	sprintf(tmpTab, f3.c_str(), blankStr.c_str(), m(0, 2), m(1, 2), m(2, 2));
	out.append(tmpTab);

	return out;
}

std::string tlinAttitudeUtilsClass::printMatrix(const Eigen::Matrix4d &m, std::string &out, const char *name,
                                                const char *format)
{
	char        tmpTab[4096];
	int         nLen = strlen(name);
	std::string blankStr("");
	std::string f1("");
	std::string f2("");
	std::string f3("");

	for (int i = 0; i < nLen; i++)
		blankStr.append(" ");

	f1 = "\n%s   | ";
	f1.append(format);
	f1.append(", ");
	f1.append(format);
	f1.append(", ");
	f1.append(format);
	f1.append(", ");
	f1.append(format);
	f1.append(" |\n");

	f2 = "%s = | ";
	f2.append(format);
	f2.append(", ");
	f2.append(format);
	f2.append(", ");
	f2.append(format);
	f2.append(", ");
	f2.append(format);
	f2.append(" |\n");

	f3 = "%s   | ";
	f3.append(format);
	f3.append(", ");
	f3.append(format);
	f3.append(", ");
	f3.append(format);
	f3.append(", ");
	f3.append(format);
	f3.append(" |\n");

	out = "";
	sprintf(tmpTab, f1.c_str(), blankStr.c_str(), m(0, 0), m(1, 0), m(2, 0), m(3, 0));
	out.append(tmpTab);
	sprintf(tmpTab, f2.c_str(), name, m(0, 1), m(1, 1), m(2, 1), m(3, 1));
	out.append(tmpTab);
	sprintf(tmpTab, f3.c_str(), blankStr.c_str(), m(0, 2), m(1, 2), m(2, 2), m(3, 2));
	out.append(tmpTab);
	sprintf(tmpTab, f3.c_str(), blankStr.c_str(), m(0, 3), m(1, 3), m(2, 3), m(3, 3));
	out.append(tmpTab);

	return out;
}

std::string tlinAttitudeUtilsClass::printMatrix(const Eigen::Vector3d &m, std::string &out, const char *name,
                                                const char *format)
{
	char        tmpTab[4096];
	int         nLen = strlen(name);
	std::string blankStr("");
	std::string f1("");
	std::string f2("");
	std::string f3("");

	for (int i = 0; i < nLen; i++)
		blankStr.append(" ");

	f1 = "\n%s   | ";
	f1.append(format);
	f1.append(" |\n");

	f2 = "%s = | ";
	f2.append(format);
	f2.append(" |\n");

	f3 = "%s   | ";
	f3.append(format);
	f3.append(" |\n");

	out = "";
	sprintf(tmpTab, f1.c_str(), blankStr.c_str(), m(0));
	out.append(tmpTab);
	sprintf(tmpTab, f2.c_str(), name, m(1));
	out.append(tmpTab);
	sprintf(tmpTab, f3.c_str(), blankStr.c_str(), m(2));
	out.append(tmpTab);

	return out;
}

std::string tlinAttitudeUtilsClass::printMatrix(const Eigen::Vector2d &m, std::string &out, const char *name,
                                                const char *format)
{
	char        tmpTab[4096];
	int         nLen = strlen(name);
	std::string blankStr("");
	std::string f1("");
	std::string f2("");

	for (int i = 0; i < nLen; i++)
		blankStr.append(" ");

	//   "%s = | %s |"
	f1 = "%s   | ";
	f1.append(format);
	f1.append(" |\n");

	f2 = "\n%s = | ";
	f2.append(format);
	f2.append(" |\n");

	out = "";
	sprintf(tmpTab, f2.c_str(), name, m(0));
	out.append(tmpTab);
	sprintf(tmpTab, f1.c_str(), blankStr.c_str(), m(1));
	out.append(tmpTab);

	return out;
}


std::string tlinAttitudeUtilsClass::printMatrix(const Eigen::Vector4d &m, std::string &out, const char *name,
                                                const char *format)
{
	char        tmpTab[4096];
	int         nLen = strlen(name);
	std::string blankStr("");
	std::string f1("");
	std::string f2("");
	std::string f3("");

	for (int i = 0; i < nLen; i++)
		blankStr.append(" ");

	f1 = "\n%s   | ";
	f1.append(format);
	f1.append(" |\n");

	f2 = "%s = | ";
	f2.append(format);
	f2.append(" |\n");

	f3 = "%s   | ";
	f3.append(format);
	f3.append(" |\n");

	out = "";
	sprintf(tmpTab, f1.c_str(), blankStr.c_str(), m(0));
	out.append(tmpTab);
	sprintf(tmpTab, f2.c_str(), name, m(1));
	out.append(tmpTab);
	sprintf(tmpTab, f3.c_str(), blankStr.c_str(), m(2));
	out.append(tmpTab);
	sprintf(tmpTab, f3.c_str(), blankStr.c_str(), m(3));
	out.append(tmpTab);

	return out;
}

//
// --------------------------------------------------
// --------------------------------------------------
// --------------------------------------------------
//

void tlinAttitudeUtilsClass::build_omega(Eigen::Matrix4d &m, const Eigen::Matrix3d &e, const Eigen::Vector3d &v)
{
	m.block(0, 0, 3, 3) = -0.5 * e;

	m(3, 0) = -0.5 * v(0);
	m(3, 1) = -0.5 * v(1);
	m(3, 2) = -0.5 * v(2);

	m(0, 3) = 0.5 * v(0);
	m(1, 3) = 0.5 * v(1);
	m(2, 3) = 0.5 * v(2);

	m(3, 3) = 0.0;
}

void tlinAttitudeUtilsClass::build_E(const Eigen::Matrix4d &in, Eigen::Matrix4d &out, const int level)
{
	Eigen::Matrix4d X = in;
	Eigen::Matrix4d I44x;
	Eigen::Matrix4d V;
	Eigen::Matrix4d x;
	double          n;

	// Macierz
	tlinAttitudeUtilsClass::init44I1(I44x);

	if (level == 0)
		n = 3.0;
	else
		n = 4.0;

	x   = X - I44x.transpose() * X * 1 / 4.0;
	out = x.transpose() * x * 1.0 / n;
}

void tlinAttitudeUtilsClass::build_K(const Eigen::Matrix3d &S, const Eigen::Vector3d &z, const double sigma,
                                     const double ak, Eigen::Matrix4d &K)
{
	Eigen::Matrix3d I3 = Eigen::Matrix3d::Identity();
	Eigen::Matrix4d tmpK;

	// K
	tmpK.block(0, 0, 3, 3) = S - sigma * I3;

	for (int i = 0; i < 3; i++) {
		tmpK(3, i) = z(i);
		tmpK(i, 3) = z(i);
	}
	tmpK(3, 3) = sigma;

	K = 1.0 / ak * tmpK;
}

void tlinAttitudeUtilsClass::build_ex(Eigen::Matrix3d &m, const Eigen::Vector3d &v)
{
	m(0, 0) = 0.0;
	m(0, 1) = -1 * v(2);
	m(0, 2) = +1 * v(1);
	m(1, 0) = +1 * v(2);
	m(1, 1) = 0.0;
	m(1, 2) = -1 * v(0);
	m(2, 0) = -1 * v(1);
	m(2, 1) = +1 * v(0);
	m(2, 2) = 0.0;
}

void tlinAttitudeUtilsClass::vector_from_ex(const Eigen::Matrix3d &m, Eigen::Vector3d &v)
{
	v(0) = m(2, 1);
	v(1) = m(0, 2);
	v(2) = m(1, 0);
}

void tlinAttitudeUtilsClass::build_exp(const Eigen::Matrix4d &inM, Eigen::Matrix4d &resM, const double t, const int res)
{
	Eigen::Matrix4d rTmpPow;
	Eigen::Matrix4d rTmp;
	Eigen::Matrix4d test;
	Eigen::Matrix4d I4;

	tlinAttitudeUtilsClass::init44I(I4);

	rTmp = /*I4 * t +*/ inM * t;

	double sil = 1.0;
	for (int i = 2; i <= res; i++) {
		rTmpPow = inM;
		for (int j = 0; j < (i - 1); j++)
			rTmpPow *= inM;

		sil *= (double) i;
		rTmp += t * rTmpPow / sil;
	}
	resM = rTmp;
}

void tlinAttitudeUtilsClass::init33I1(Eigen::Matrix3d &m)
{
	for (int i = 0; i < 3; i++)
		for (int j = 0; j < 3; j++)
			m(i, j) = 1.0;
}

void tlinAttitudeUtilsClass::init44I1(Eigen::Matrix4d &m)
{
	for (int i = 0; i < 4; i++)
		for (int j = 0; j < 4; j++)
			m(i, j) = 1.0;
}

void tlinAttitudeUtilsClass::init33I(Eigen::Matrix3d &m)
{
	m = Eigen::Matrix3d::Identity();
}

void tlinAttitudeUtilsClass::init33(Eigen::Matrix3d &m)
{
	m = Eigen::Matrix3d::Zero();
}

void tlinAttitudeUtilsClass::init44I(Eigen::Matrix4d &m)
{
	m = Eigen::Matrix4d::Identity();
}

void tlinAttitudeUtilsClass::init44(Eigen::Matrix4d &m)
{
	m = Eigen::Matrix4d::Zero();
}

void tlinAttitudeUtilsClass::init4(Eigen::Vector4d &m)
{
	m = Eigen::Vector4d::Zero();
}

void tlinAttitudeUtilsClass::init3(Eigen::Vector3d &m)
{
	m = Eigen::Vector3d::Zero();
}

void tlinAttitudeUtilsClass::init2(Eigen::Vector2d &m)
{
	m = Eigen::Vector2d::Zero();
}


double tlinAttitudeUtilsClass::vectorsAngle(const Eigen::Vector3d &v1, const Eigen::Vector3d &v2)
{
	double dot = v1.dot(v2);
	double l1 = v1.norm();
	double l2 = v2.norm();

	if(	dot <= std::numeric_limits<double>::epsilon() ||
		l1  <= std::numeric_limits<double>::epsilon() ||
		l2  <= std::numeric_limits<double>::epsilon()) {
		return tlinsMath::PI / 2.0;
	}
	return ::acos(dot / (l1 * l2));
}

void tlinAttitudeUtilsClass::normAngles(Eigen::Vector2d &v)
{
	while (v(0) < 0.0)
		v(0) = v(0) + tlinsMath::PI_2;

	while (v(0) > tlinsMath::PI_2)
		v(0) = v(0) - tlinsMath::PI_2;

	while (v(1) < 0.0)
		v(1) = v(1) + tlinsMath::PI_2;

	while (v(1) > tlinsMath::PI_2)
		v(1) = v(1) - tlinsMath::PI_2;
}

void tlinAttitudeUtilsClass::normAngles(Eigen::Vector2d &v, const int id)
{
	while (v(id) < 0.0)
		v(id) = v(id) + tlinsMath::PI_2;

	while (v(id) > tlinsMath::PI_2)
		v(id) = v(id) - tlinsMath::PI_2;
}

void tlinAttitudeUtilsClass::normAngles(double &alfa, double &beta)
{
	while (alfa < 0.0)
		alfa += tlinsMath::PI_2;

	while (alfa > tlinsMath::PI_2)
		alfa -= tlinsMath::PI_2;

	while (beta < 0.0)
		beta += tlinsMath::PI_2;

	while (beta > tlinsMath::PI_2)
		beta -= tlinsMath::PI_2;
}

void tlinAttitudeUtilsClass::normAngles(double &alfa)
{
	while (alfa < 0.0)
		alfa += tlinsMath::PI_2;

	while (alfa > tlinsMath::PI_2)
		alfa -= tlinsMath::PI_2;
}

} // namespace attitude