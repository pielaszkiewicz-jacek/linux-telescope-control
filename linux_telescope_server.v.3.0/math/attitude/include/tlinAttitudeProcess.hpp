#ifndef __tlinAttitudeProcess_hpp__
#define __tlinAttitudeProcess_hpp__

#include <Eigen/Dense>
#include <Eigen/Geometry>
#include <memory>
#include <vector>

#define METHOD_REQUEST 1
#define METHOD_OPTIMAL_REQUEST 2

#include "tlinAttitudeIteration.hpp"
#include "tlinAttitudeProcessorBase.hpp"
#include <tlinmException.hpp>
#include <tlinsAstroObject.hpp>

#include <get_quat_from_K_data.h>

namespace attitude
{
class tlinAttitudeProcess {
  public:
	EIGEN_MAKE_ALIGNED_OPERATOR_NEW

  private:
	// Kolekcja zawierajaca poszczegolne iteracje
	tlinAttitudeIterations iterations;

	// Biezaca macierz transformacji wyzanaczana na
	// podstawie wszystkich pomiaróþw
	Eigen::Matrix3d attitude;
	Eigen::Matrix3d attitudeInversted;

	Eigen::Matrix3d optimalA;
	Eigen::Matrix3d optimalAInversed;
	double          rotationSpeed;

	std::unique_ptr<tlinsAttitudeProcessorValidatorBase> validator;

  public:
	tlinAttitudeIterations &getIterations()
	{
		return iterations;
	};

	Eigen::Matrix3d getOptimalA();
	Eigen::Matrix3d getOptimalAInversed();

	// Rejestracja pomiaru
	// Metoda wyzabzca predkosc rotacji
	void registerMeasurment(const Eigen::Vector3d &ref, const Eigen::Vector3d &obs, const Eigen::Vector3d &obsErr,
	                        const double w, const double detlaMk);

	void registerMeasurment(const Eigen::Vector3d &ref, const Eigen::Vector3d &obs, const Eigen::Vector3d &obsErr,
	                        const double w, const double detlaMk, const double timeStamp);

	// Rejestracja pomiaru
	// Metoda zaklada ze predkosc rotacji jest przekazana
	void registerMeasurment(const Eigen::Vector3d &ref, const Eigen::Vector3d &obs, const Eigen::Vector3d &obsErr,
	                        const Eigen::Vector3d &rotSpeed, const Eigen::Vector3d &rotSpeedErr, const double timeStamp,
	                        const double w, const double detlaMk, const double aZ);

	std::vector<tlinMaxAttitudeInfo> validate();

	struct VctorsAngleInfo {
		int iteration1;
		int iteration2;
		double angleRef;
		double angleRefOrg;
		double angleObs;

		Eigen::Vector3d observationVector_1;
		Eigen::Vector3d referenceVector_1;
		Eigen::Vector3d referenceVectorOrg_1;

		Eigen::Vector3d observationVector_2;
		Eigen::Vector3d referenceVector_2;
		Eigen::Vector3d referenceVectorOrg_2;

		VctorsAngleInfo &operator=(const VctorsAngleInfo &v) = default;
		VctorsAngleInfo(const VctorsAngleInfo &v) = default;
		VctorsAngleInfo() = default;
		~VctorsAngleInfo() = default;
	};

	std::vector<VctorsAngleInfo> getVctorsAngle();

	// Liczba iteracji
	unsigned int size();

	// Konstruktor/destruktor klasy
	tlinAttitudeProcess();
	virtual ~tlinAttitudeProcess();
};

}; // namespace attitude

#endif
