/*
 * tlinm_testUtilty.hpp
 *
 *  Created on: 15-10-2012
 *      Author: jacek
 */

#ifndef TLINM_TESTUTILTY_HPP_
#define TLINM_TESTUTILTY_HPP_

#include <tlinmException.hpp>
#include <tlinmMeasurement.hpp>
#include <tlinmMeasurementBase.hpp>
#include <tlinmMeasurements.hpp>

#include <Eigen/Dense>
#include <Eigen/Eigenvalues>
#include <Eigen/Geometry>

#include <tlinmMeasurementVelocity.hpp>
#include <tlinmMeasurementsVelocity.hpp>

#include "tlinAttitudeMeasurment.hpp"

#include <memory>
#include <set>
#include <vector>

class tlinmTestUtility {
  public:
	EIGEN_MAKE_ALIGNED_OPERATOR_NEW

	struct Object {
		std::string name;
		double      ra;
		double      dc;
		double      paraleks;
		double      radialVelocity;
		double      radialVelocityErr;
		double      pmRa;
		double      pmRaErr;
		double      pmDc;
		double      pmDcErr;

		Object()
		{
		}

		Object(const Object &v)
		{
			name = v.name;
			ra   = v.ra;
			dc   = v.dc;

			paraleks          = v.paraleks;
			radialVelocity    = v.radialVelocity;
			radialVelocityErr = v.radialVelocityErr;
			pmRa              = v.pmRa;
			pmRaErr           = v.pmRaErr;
			pmDc              = v.pmDc;
			pmDcErr           = v.pmDcErr;
		}

		Object &operator=(const Object &v)
		{
			name = v.name;
			ra   = v.ra;
			dc   = v.dc;

			paraleks          = v.paraleks;
			radialVelocity    = v.radialVelocity;
			radialVelocityErr = v.radialVelocityErr;
			pmRa              = v.pmRa;
			pmRaErr           = v.pmRaErr;
			pmDc              = v.pmDc;
			pmDcErr           = v.pmDcErr;
			return *this;
		}

		Object(const std::string &name_, const double ra_, const double dc_) : name{name_}, ra{ra_}, dc{dc_}
		{
		}

		virtual ~Object()
		{
		}
	};

  private:
	Eigen::Matrix3d zRotaionMatrix;
	Eigen::Matrix3d rotaionMatrix;

	// Wspolrzedne w ukladzie odniesienia
	std::vector<tlinmMeasurement> measurements;

	// Pomiary predkosci
	std::vector<tlinmMeasurementsVelocity> vMeasurements;

	// Nowe pomiary
	std ::vector<attitude ::tlinAttitudeMeasurement> newMeasurements;

	// Dodaje pomiar
	void addMeasurement2(const Eigen::Vector3d &b, const Eigen::Vector3d &err, const Eigen::Vector3d &r,
	                     const Eigen::Vector3d &rOrg, const double t, const double w, const double baseTime,
	                     const double ax, const double ay, const double az);

	void addMeasurement(const Eigen::Vector3d &b, const Eigen::Vector3d &err, const Eigen::Vector3d &r, const double t,
	                    const double w);
	void addVMeasurement(const Eigen::Vector3d &m, const Eigen::Vector3d &mErr, const double t, const double w,
	                     tlinmMeasurementsVelocity &vec);
	void transformVector(const Eigen::Vector3d &inVector, Eigen::Vector3d &outVector);
	void rotateVector(const Eigen::Vector3d &inVector, Eigen::Vector3d &outVector);

  public:
	void generateTestData(const double inSpeed, const double inDT, const double inCount, const double inErrorLevel,
	                      const int inSpeedMeasurments);

	void generateTestData(const double inSpeed, const double inDT, const double inErrorLevel,
	                      const int inSpeedMeasurments, const std::vector<Object> &refObjects);

	void generateTestData2(const double inSpeed, const double inDT, const double inErrorLevel,
	                       const int inSpeedMeasurments, const std::vector<Object> &refObjects);

	// Funkcja buduje macierz obrotu wokol osi Z
	Eigen::Matrix3d &buildZRotaionMatrix(double angle);

	// Metoda testuje rezultaty
	void testResult(const Eigen::Matrix3d &in);

	Eigen::Matrix3d &getRotaionMatrix();

	std::vector<tlinmMeasurement> &getMeasurements()
	{
		return measurements;
	}

	std::vector<tlinmMeasurementsVelocity> &getVMeasurements()
	{
		return vMeasurements;
	}

	std ::vector<attitude ::tlinAttitudeMeasurement> &getNewMeasurements()
	{
		return newMeasurements;
	}

  public:
	// Konstruktor/destruktor klasy
	tlinmTestUtility(const double nuatation, const double precesion, const double rotation);
	virtual ~tlinmTestUtility();
};

void populatePrdefinedList(std::vector<tlinmTestUtility::Object> &refObjects, const std::set<int> &items);

#endif /* TLINM_TESTUTILTY_HPP_ */
