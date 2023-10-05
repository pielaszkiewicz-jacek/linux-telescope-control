/*
 * tlinm_utils.hpp
 *
 *  Created on: 09-10-2012
 *      Author: jacek
 */

#ifndef __tlinmAttitudeUtilsClass_hpp__
#define __tlinmAttitudeUtilsClass_hpp__

#include <Eigen/Eigenvalues>
#include <Eigen/Geometry>
#include <iostream>
#include <memory>
#include <stdio.h>
#include <vector>

// #include <tlinAttitudeMeasurment.hpp>

/*
 * Zestaw klas reprezentujacych dane pomiarowe.
 */

#ifdef ___DEBUG___

#define DEBUG_MATRIX_INFO(m, name, format) tlinmUtilsClass::printMatrix(m, name, format)
#define DEBUG_SCALAR_INFO(m, v) printf("%s = %20.17f\n", m, v);

#else

#define DEBUG_MATRIX_INFO(m, name, format)
#define DEBUG_SCALAR_INFO(m, v)

#endif

namespace attitude
{

class tlinAttitudeUtilsClass {
  public:
	EIGEN_MAKE_ALIGNED_OPERATOR_NEW

  public:
	static bool   testEpsylon(double val);
	static double epsylon;
	static double epsylonError;
	static double pi;

	static std::pair<double, bool> deltaMinimumPosition(const double currPos, const double newPos);

	//
	// Metoda wyznacza prekosc obroitu dla pary wektorów obserwacyjnych
	//
	static void estimnateRotationSpeed(const Eigen::Vector3d &v1, const Eigen::Vector3d &v2, const double dt,
	                                   Eigen::Vector3d &output);

	//
	// Macierze transformacji dla obrotow
	//
	static void buildZRotaionMatrix(const double angle, Eigen::Matrix3d &out);
	static void buildYRotaionMatrix(const double angle, Eigen::Matrix3d &out);
	static void buildXRotaionMatrix(const double angle, Eigen::Matrix3d &out);

	static void buildXYZRotaionMatrix(const double a, const double b, const double g, Eigen::Matrix3d &out);

	//
	// Konwersja miedzy ukladami wspolrzednych
	//
	static Eigen::Vector3d toCartesianBase(const double alfa, const double beta, const double r = 1.0);

	static void toCartesian(const double alfa, const double beta, Eigen::Vector3d &axis, const double r = 1.0);
	static void toCartesian(const Eigen::Vector2d &in, Eigen::Vector3d &axis, const double r = 1.0);
	static void toSpeherical(const Eigen::Vector3d &in, Eigen::Vector2d &out);

	static void toSpeherical(const Eigen::Vector3d &in, Eigen::Vector2d &out, double &r);

	static void calculate_inv(const Eigen::Matrix3d &in, Eigen::Matrix3d &out);


	//
	// Budowanie podstawowych macierzy dl ametody
	//
	// 1. Macierz B
	static void create_B(const Eigen ::Vector3d &ref, const Eigen ::Vector3d &obs, const double weight,
	                     Eigen ::Matrix3d &B);

	static void create_B(const std::vector<Eigen::Vector3d> &ref, const std::vector<Eigen::Vector3d> &obs,
	                     const std::vector<double> weight, Eigen ::Matrix3d &B);

	static void create_S(const Eigen ::Matrix3d &B, Eigen ::Matrix3d &S);

	static void create_Z(const Eigen ::Vector3d &ref, const Eigen ::Vector3d &obs, const double weight,
	                     Eigen ::Vector3d &Z);

	static void create_Z(const Eigen::Matrix3d &B, Eigen ::Vector3d &Z);

	static void create_sigma(const Eigen ::Matrix3d &B, double &sigma);

	static void create_K(const Eigen ::Matrix3d &S, const Eigen ::Vector3d &Z, const double sigma, const double w,
	                     Eigen ::Matrix4d &K);

	static void create_FI(const Eigen::Matrix4d &omega, const double deltaT, Eigen::Matrix4d &fi);

	static void build_Q(const double lambda, const double sigma, const Eigen::Matrix3d &S, const Eigen::Vector3d &Z,
	                    Eigen::Vector3d &Q);

	static void   create_attitude(const Eigen::Vector3d &Q, Eigen::Matrix3d &O);
	static double claculate_function_F(const Eigen::Matrix4d &K, const double l);
	static double calculate_derivative_F(const Eigen::Matrix4d &K, const double l);

	static void create_exp(const Eigen ::Matrix4d &m, Eigen ::Matrix4d out);
	static void create_exp(const Eigen ::Matrix3d &m, Eigen ::Matrix3d out);

	static void create_ex(const Eigen::Vector3d &in, Eigen::Matrix3d &out);

	static void create_ex(const Eigen::Vector3d &v, Eigen::Matrix4d &out);

	static void create_omega(const Eigen::Vector3d &v, Eigen::Matrix4d &m);

	static void create_exp(const Eigen::Matrix4d &in, Eigen::Matrix4d &fi, const int res, const double t);

	static void create_exp(const Eigen::Matrix4d &in, Eigen::Matrix4d &fi, const int res);

	static void create_R(const Eigen ::Vector3d &ref, const Eigen ::Vector3d &obsErr, const double mi,
	                     Eigen::Matrix4d &R);

	static void create_Q(const Eigen ::Matrix3d &B, const Eigen ::Vector3d &Z, const double sigma, const double eta,
	                     Eigen ::Matrix4d &Q);

	// -------------------------------
	// -------------------------------

	//
	// Drukowanie zawartosci macierzy 4x4, 3x3 oraz wektorow 1x4 i 1x3
	//
	static std::string printMatrix(const Eigen::Matrix3d &m, std::string &out, const char *name, const char *format);
	static std::string printMatrix(const Eigen::Matrix4d &m, std::string &out, const char *name, const char *format);
	static std::string printMatrix(const Eigen::Vector2d &m, std::string &out, const char *name, const char *format);
	static std::string printMatrix(const Eigen::Vector3d &m, std::string &out, const char *name, const char *format);
	static std::string printMatrix(const Eigen::Vector4d &m, std::string &out, const char *name, const char *format);

	static void printMatrix(const Eigen::Matrix3d &m, const char *name, const char *format);
	static void printMatrix(const Eigen::Matrix4d &m, const char *name, const char *format);
	static void printMatrix(const Eigen::Vector2d &m, const char *name, const char *format);
	static void printMatrix(const Eigen::Vector3d &m, const char *name, const char *format);
	static void printMatrix(const Eigen::Vector4d &m, const char *name, const char *format);


	static void normaliseCartesian(const Eigen::Vector3d &im, Eigen::Vector3d &out);

	static void build_K(const Eigen::Matrix3d &S, const Eigen::Vector3d &z, const double sigma, const double ak,
	                    Eigen::Matrix4d &K);
	static void build_exp(const Eigen::Matrix4d &inM, Eigen::Matrix4d &resM, const double t, const int res);
	static void build_omega(Eigen::Matrix4d &m, const Eigen::Matrix3d &e, const Eigen::Vector3d &v);
	static void build_E(const Eigen::Matrix4d &in, Eigen::Matrix4d &out, int level);
	static void vector_from_ex(const Eigen::Matrix3d &m, Eigen::Vector3d &v);
	static void build_ex(Eigen::Matrix3d &m, const Eigen::Vector3d &v);

	static void create_attitude(const Eigen::Matrix4d &K, Eigen::Vector4d &eigenvalues, Eigen::Matrix4d &eigenvectors,
	                            double &lambda, Eigen::Matrix3d &optimalQ);

	// Pomocnicze metody inicujace macierze i wektory
	// 1. Wypeninaie calej macierzy jedynkami
	static void init33I1(Eigen::Matrix3d &m);
	static void init44I1(Eigen::Matrix4d &m);

	// 2. Macierz jednostokowa - elementy na przekatnej rowne 1.0 pozostale rowne 0.0
	static void init33I(Eigen::Matrix3d &m);
	static void init44I(Eigen::Matrix4d &m);

	// 1. Wypeninaie calej macierzy zerami
	static void init44(Eigen::Matrix4d &m);
	static void init33(Eigen::Matrix3d &m);

	// 1. Wypeninaie calego wektora zerami
	static void init4(Eigen::Vector4d &m);
	static void init3(Eigen::Vector3d &m);
	static void init2(Eigen::Vector2d &m);

	// Kat miedzy wektorami
	static double vectorsAngle(const Eigen::Vector3d &v1, const Eigen::Vector3d &v2);

	static void normAngles(Eigen::Vector2d &v);
	static void normAngles(double &alfa, double &beta);

	static void normAngles(Eigen::Vector2d &v, const int id);
	static void normAngles(double &alfa);
};

}; // namespace attitude

#define PRINT_M(a, n, f)                                                                                               \
	do {                                                                                                               \
		std ::string txt = std ::string{__FUNCTION__} + std ::string{"() ["} + std ::to_string(__LINE__) +             \
		                   std ::string{"] : "} + std ::string{n};                                                     \
		attitude::tlinAttitudeUtilsClass::printMatrix(a, txt.c_str(), f);                                              \
	} while (0)

#endif
