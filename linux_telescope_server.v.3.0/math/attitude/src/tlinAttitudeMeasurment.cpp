#include "tlinAttitudeMeasurment.hpp"
#include <tlinAttitudeUtilsClass.hpp>
#include <tlinsBacktrace.hpp>

namespace attitude
{

const bool tlinAttitudeMeasurement::theSameReference(const tlinAttitudeMeasurement &m) const
{
	bool result{true};
	for (int i = 0; i < 3; i++) {
		auto delta = m.referenceVectorOrg(i) - referenceVectorOrg(i);
		result     = result && (delta < 0.00001);
	}
	return result;
	// return 		attitude::tlinAttitudeUtilsClass::testEpsylon(m.referenceVectorOrg(0) - referenceVectorOrg(0))
	// 		&&	attitude::tlinAttitudeUtilsClass::testEpsylon(m.referenceVectorOrg(1) - referenceVectorOrg(1));
	// return m.referenceVectorOrg(0) == referenceVectorOrg(0) && m.referenceVectorOrg(1) == referenceVectorOrg(1);
}

const Eigen::Vector3d &tlinAttitudeMeasurement ::getObservationVectorNorm() const
{
	return observationVectorNorm;
}

const Eigen::Vector3d &tlinAttitudeMeasurement ::getObservationVector() const
{
	return observationVector;
}

const Eigen::Vector3d &tlinAttitudeMeasurement ::getObservationVectorError() const
{
	return observationVectorError;
}

const Eigen::Vector3d &tlinAttitudeMeasurement ::getReferenceVector() const
{
	return referenceVector;
}

const Eigen::Vector3d &tlinAttitudeMeasurement ::getReferenceVectorNorm() const
{
	return referenceVectorNorm;
}

double tlinAttitudeMeasurement ::getObservationTime() const
{
	return static_cast<double>(observationTime);
}

double tlinAttitudeMeasurement ::getDeltaTime() const
{
	return static_cast<double>(deltaTime);
}

double tlinAttitudeMeasurement ::getWeight() const
{
	return weight;
}

double tlinAttitudeMeasurement ::getDeltaM() const
{
	return delta_m;
}

double tlinAttitudeMeasurement ::getAngleZ() const
{
	return angleZ;
}

void tlinAttitudeMeasurement ::setAngleZ(const double v)
{
	angleZ = v;
}

void tlinAttitudeMeasurement ::setObservationVector(const Eigen::Vector3d &v)
{
	observationVector = v;

	// Normalizacja wektora
	double nLen           = ::sqrt(v(0) * v(0) + v(1) * v(1) + v(2) * v(2));
	observationVectorNorm = v / nLen;
}

void tlinAttitudeMeasurement ::setObservationVectorError(const Eigen::Vector3d &v)
{
	double nLen            = ::sqrt(v(0) * v(0) + v(1) * v(1) + v(2) * v(2));
	observationVectorError = v / nLen;
}

void tlinAttitudeMeasurement ::setReferenceVector(const Eigen::Vector3d &v)
{
	referenceVector = v;

	double nLen         = ::sqrt(v(0) * v(0) + v(1) * v(1) + v(2) * v(2));
	referenceVectorNorm = v / nLen;
}

const Eigen::Vector3d &tlinAttitudeMeasurement ::getReferenceVectorOrg() const
{
	return referenceVectorOrg;
}

const Eigen::Vector3d &tlinAttitudeMeasurement ::getReferenceVectorOrgNorm() const
{
	return referenceVectorOrg;
}

void tlinAttitudeMeasurement ::setReferenceVectorOrg(const Eigen::Vector3d &v)
{
	referenceVectorOrg = v;

	double nLen            = ::sqrt(v(0) * v(0) + v(1) * v(1) + v(2) * v(2));
	referenceVectorOrgNorm = v / nLen;
}

void tlinAttitudeMeasurement ::setObservationTime(const double t)
{
	observationTime = t;
}

void tlinAttitudeMeasurement ::setDeltaTime(const double t)
{
	deltaTime = t;
}

void tlinAttitudeMeasurement ::setWeight(const double w)
{
	weight = w;
}

void tlinAttitudeMeasurement ::setDeltaM(const double w)
{
	delta_m = w;
}

const Eigen::Vector3d &tlinAttitudeMeasurement ::getRotationSpeed()
{
	return rotationSpeed;
}

const Eigen::Vector3d &tlinAttitudeMeasurement ::getRotationSpeedError()
{
	return rotationSpeedError;
}

void tlinAttitudeMeasurement ::setRotationSpeed(const Eigen::Vector3d &v)
{
	rotationSpeed = v;
}

void tlinAttitudeMeasurement ::setRotationSpeedError(const Eigen::Vector3d &v)
{
	rotationSpeedError = v;
}

tlinAttitudeMeasurement &tlinAttitudeMeasurement ::operator=(const tlinAttitudeMeasurement &v)
{
	rotationSpeed          = v.rotationSpeed;
	rotationSpeedError     = v.rotationSpeedError;
	observationVectorNorm  = v.observationVectorNorm;
	observationVector      = v.observationVector;
	observationVectorError = v.observationVectorError;
	referenceVector        = v.referenceVector;
	referenceVectorNorm    = v.referenceVectorNorm;
	referenceVectorOrgNorm = v.referenceVectorOrgNorm;
	referenceVectorOrg     = v.referenceVectorOrg;
	observationTime        = v.observationTime;
	weight                 = v.weight;
	delta_m                = v.delta_m;
	angleZ                 = v.angleZ;
	return *this;
}

tlinAttitudeMeasurement &tlinAttitudeMeasurement ::operator=(tlinAttitudeMeasurement &&v)
{
	rotationSpeed          = std ::move(v.rotationSpeed);
	rotationSpeedError     = std ::move(v.rotationSpeedError);
	observationVector      = std ::move(v.observationVector);
	observationVectorNorm  = std ::move(v.observationVectorNorm);
	observationVectorError = std ::move(v.observationVectorError);
	referenceVector        = std ::move(v.referenceVector);
	referenceVectorNorm    = std ::move(v.referenceVectorNorm);
	referenceVectorOrgNorm = std ::move(v.referenceVectorOrgNorm);
	referenceVectorOrg     = std ::move(v.referenceVectorOrg);
	observationTime        = v.observationTime;
	weight                 = v.weight;
	delta_m                = v.delta_m;
	angleZ                 = v.angleZ;
	return *this;
}

tlinAttitudeMeasurement ::tlinAttitudeMeasurement()
{
	observationVectorNorm  = Eigen ::Vector3d ::Zero();
	observationVector      = Eigen ::Vector3d ::Zero();
	observationVectorError = Eigen ::Vector3d ::Zero();
	referenceVector        = Eigen ::Vector3d ::Zero();
	referenceVectorNorm    = Eigen ::Vector3d ::Zero();
	referenceVectorOrgNorm = Eigen ::Vector3d ::Zero();
	referenceVectorOrg     = Eigen ::Vector3d ::Zero();
	rotationSpeed          = Eigen ::Vector3d ::Zero();
	rotationSpeedError     = Eigen ::Vector3d ::Zero();
	observationTime        = 0L;
	deltaTime              = 0L;
	weight                 = 0.0;
	delta_m                = 0.0;
	angleZ                 = 0.0;
}

tlinAttitudeMeasurement ::tlinAttitudeMeasurement(const tlinAttitudeMeasurement &v)
{
	rotationSpeed          = v.rotationSpeed;
	rotationSpeedError     = v.rotationSpeedError;
	observationVectorNorm  = v.observationVectorNorm;
	observationVector      = v.observationVector;
	observationVectorError = v.observationVectorError;
	referenceVector        = v.referenceVector;
	referenceVectorNorm    = v.referenceVectorNorm;
	referenceVectorOrgNorm = v.referenceVectorOrgNorm;
	referenceVectorOrg     = v.referenceVectorOrg;
	observationTime        = v.observationTime;
	weight                 = v.weight;
	delta_m                = v.delta_m;
	angleZ                 = v.angleZ;
}

tlinAttitudeMeasurement ::tlinAttitudeMeasurement(tlinAttitudeMeasurement &&v)
{
	rotationSpeed          = std ::move(v.rotationSpeed);
	rotationSpeedError     = std ::move(v.rotationSpeedError);
	observationVectorNorm  = std ::move(v.observationVectorNorm);
	observationVector      = std ::move(v.observationVector);
	observationVectorError = std ::move(v.observationVectorError);
	referenceVector        = std ::move(v.referenceVector);
	referenceVectorNorm    = std ::move(v.referenceVectorNorm);
	referenceVectorOrgNorm = std ::move(v.referenceVectorOrgNorm);
	referenceVectorOrg     = std ::move(v.referenceVectorOrg);
	observationTime        = v.observationTime;
	weight                 = v.weight;
	delta_m                = v.delta_m;
	angleZ                 = v.angleZ;
}

}; // namespace attitude
