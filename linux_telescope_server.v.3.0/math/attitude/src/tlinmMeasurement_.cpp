#include <tlinmMeasurement.hpp>
#include <tlinmUtilsClass.hpp>
#include <tlinsBacktrace.hpp>
#include <tlinsLogger.hpp>

/*
 * ---
 * --- ------------------------------------------------------------
 * ---
 */
void tlinmMeasurement::set(const tlinmMeasurement &i)
{
	*this = i;
}

// Pobranie wartosci wektora
Eigen::Vector2d &tlinmMeasurement::getInputObservationVector()
{
	return inputObservationVector;
}

Eigen::Vector2d &tlinmMeasurement::getInputObservationErrorVector()
{
	return inputObservationErrorVector;
}

Eigen::Vector2d &tlinmMeasurement::getInputReferenceVector()
{
	return inputReferenceVector;
}

const double tlinmMeasurement::getObservationTime() const
{
	return observationTime;
}

const Eigen::Vector3d &tlinmMeasurement::getObservationVector() const
{
	return observationVector;
}

const Eigen::Vector3d &tlinmMeasurement::getObservationErrorVector() const
{
	return observationErrorVector;
}

const Eigen::Vector3d &tlinmMeasurement::getReferenceVector() const
{
	return referenceVector;
}

const double tlinmMeasurement::getWeight() const
{
	return weight;
}

tlinmMeasurement &tlinmMeasurement::operator=(const tlinmMeasurement &v)
{
	inputObservationVector      = v.inputObservationVector;
	inputObservationErrorVector = v.inputObservationErrorVector;
	inputReferenceVector        = v.inputReferenceVector;
	referenceVector             = v.referenceVector;
	observationVector           = v.observationVector;
	observationErrorVector      = v.observationErrorVector;
	observationTime             = v.observationTime;
	weight                      = v.weight;
	return *this;
}

tlinmMeasurement::tlinmMeasurement()
{
	tlinmUtilsClass::init2(inputObservationVector);
	tlinmUtilsClass::init2(inputObservationErrorVector);
	tlinmUtilsClass::init2(inputReferenceVector);

	tlinmUtilsClass::init3(referenceVector);
	tlinmUtilsClass::init3(observationVector);
	tlinmUtilsClass::init3(observationErrorVector);

	observationTime = 0.0;
	weight          = 0.0;
}

// Konstruktor klasy
tlinmMeasurement::tlinmMeasurement(const double oX, const double oY, const double oZ, const double oErrX,
                                   const double oErrY, const double oErrZ, const double rX, const double rY,
                                   const double rZ, const double t, const double w)
{
	Eigen::Vector3d tmp;

	// Waga pomiaru
	weight = w;

	// Czas obserwacji
	observationTime = t;

	// Wektor wejsciowy - referencyjny
	tmp(0) = rX;
	tmp(1) = rY;
	tmp(2) = rZ;
	tlinmUtilsClass::toSpeherical(tmp, inputReferenceVector);

	// Wektor wejsciowy
	tmp(0) = oX;
	tmp(1) = oY;
	tmp(2) = oZ;
	tlinmUtilsClass::toSpeherical(tmp, inputObservationVector);

	// Wektor wejsciowy - referencyjny
	tmp(0) = oErrX;
	tmp(1) = oErrY;
	tmp(2) = oErrZ;
	tlinmUtilsClass::toSpeherical(tmp, inputObservationErrorVector);

	// Zmormalizowany wektor
	observationVector(0) = oX;
	observationVector(1) = oY;
	observationVector(2) = oZ;
	tlinmUtilsClass ::printMatrix(observationVector, "observationVector", "%f");

	observationErrorVector(0) = oErrX;
	observationErrorVector(1) = oErrY;
	observationErrorVector(2) = oErrZ;
	tlinmUtilsClass ::printMatrix(observationErrorVector, "observationErrorVector", "%f");

	referenceVector(0) = rX;
	referenceVector(1) = rY;
	referenceVector(2) = rZ;
	tlinmUtilsClass ::printMatrix(referenceVector, "referenceVector", "%f");
}

tlinmMeasurement::tlinmMeasurement(const tlinmMeasurement &v)
{
	*this = v;
}

tlinmMeasurement::~tlinmMeasurement()
{
}
