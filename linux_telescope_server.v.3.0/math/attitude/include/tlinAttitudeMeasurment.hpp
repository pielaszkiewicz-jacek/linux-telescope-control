#ifndef __tlinAttitudeMeasurment_hpp__
#define __tlinAttitudeMeasurment_hpp__

#include <Eigen/Dense>
#include <Eigen/Geometry>

#include <memory>
#include <vector>

namespace attitude
{

//
// Pojedynczy pomiar
//
class tlinAttitudeMeasurement {
  public:
	EIGEN_MAKE_ALIGNED_OPERATOR_NEW

  private:
	// Obserwacja we wspórzednych kontowych
	Eigen::Vector3d observationVector;
	Eigen::Vector3d observationVectorNorm;

	// Blad pomiaru
	Eigen::Vector3d observationVectorError;

	// Obiekt referencyjny
	Eigen::Vector3d referenceVector;
	Eigen::Vector3d referenceVectorNorm;

	Eigen::Vector3d referenceVectorOrg;
	Eigen::Vector3d referenceVectorOrgNorm;

	// Rotacja
	Eigen::Vector3d rotationSpeed;      // Predkosc XYZ
	Eigen::Vector3d rotationSpeedError; // Predkosc error XYZ

	// Czas obserwacji
	double observationTime;
	double deltaTime;

	// Wagapomiaru
	double weight;

	//
	double delta_m;

	// Kat rotacji dla poszcxzegolnych osi na moment pomiaru
	double angleZ;

  public:
	const bool theSameReference(const tlinAttitudeMeasurement &m) const;

	// Gettery
	const Eigen::Vector3d &getObservationVectorNorm() const;
	const Eigen::Vector3d &getObservationVector() const;
	const Eigen::Vector3d &getObservationVectorError() const;
	const Eigen::Vector3d &getReferenceVector() const;
	const Eigen::Vector3d &getReferenceVectorNorm() const;


	const Eigen::Vector3d &getRotationSpeed();
	const Eigen::Vector3d &getRotationSpeedError();

	double getObservationTime() const;
	double getDeltaTime() const;
	double getWeight() const;
	double getDeltaM() const;

	double getAngleZ() const;

	const Eigen::Vector3d &getReferenceVectorOrg() const;
	const Eigen::Vector3d &getReferenceVectorOrgNorm() const;

	void setReferenceVectorOrg(const Eigen::Vector3d &v);

	void setObservationVector(const Eigen::Vector3d &v);
	void setObservationVectorError(const Eigen::Vector3d &v);
	void setReferenceVector(const Eigen::Vector3d &v);

	void setObservationTime(const double t);
	void setDeltaTime(const double t);
	void setWeight(const double w);
	void setDeltaM(const double w);

	void setRotationSpeed(const Eigen::Vector3d &v);
	void setRotationSpeedError(const Eigen::Vector3d &v);

	void setAngleZ(const double v);

	tlinAttitudeMeasurement &operator=(const tlinAttitudeMeasurement &v);
	tlinAttitudeMeasurement &operator=(tlinAttitudeMeasurement &&v);

	tlinAttitudeMeasurement(const tlinAttitudeMeasurement &v);
	tlinAttitudeMeasurement(tlinAttitudeMeasurement &&v);
	tlinAttitudeMeasurement();
	virtual ~tlinAttitudeMeasurement() = default;
};

}; // namespace attitude

#endif