#include "tlinAttitudeUtilsClass.hpp"
#include <Eigen/Eigenvalues>
#include <Eigen/Geometry>
#include <tlinAttitudeProcess.hpp>
#include <tlinsBacktrace.hpp>
#include <tlinsLogger.hpp>
#include <tlinsTimeInfo.hpp>
#include <tlins_math.hpp>

#include <cmath>
#include <sofa.h>

#include <Eigen/Geometry>
#include <get_quat_from_K.h>
#include <optimal_request.h>
#include <optimal_request_init.h>
#include <tlinsAttitudeProcessor.hpp>

namespace attitude
{

void tlinAttitudeProcess ::registerMeasurment(const Eigen::Vector3d &ref, const Eigen::Vector3d &obs,
                                              const Eigen::Vector3d &obsErr, const double w, const double detlaMk)
{
	// Wyznaczenie kota rotacji dla danej pomiaru
	auto &tInfo = tlinsTimeInfo ::getInstance();
	tInfo.update();
	double timeStamp = tInfo.getCurrentTimeSecends();
	registerMeasurment(ref, obs, obsErr, w, detlaMk, timeStamp);
}

void tlinAttitudeProcess ::registerMeasurment(const Eigen::Vector3d &ref, const Eigen::Vector3d &obs,
                                              const Eigen::Vector3d &obsErr, const double w, const double detlaMk,
                                              const double timeStamp)
{
	// Wyznaczenie kota rotacji dla danej pomiaru
	auto &tInfo = tlinsTimeInfo ::getInstance();
	tInfo.update();

	// Katy rotacji dla chwili pomiaru
	double zAngle = -1.0 * ::iauEra00(tInfo.getD1(), tInfo.getD2());

	// Wyznaczenie predkosci rotacji
	Eigen::Vector3d rotSpeed;
	Eigen::Vector3d rotSpeedErr;

	rotSpeed(0)    = 0.0;
	rotSpeed(1)    = 0.0;
	rotSpeed(2)    = rotationSpeed;
	rotSpeedErr(0) = 0.0;
	rotSpeedErr(1) = 0.0;
	rotSpeedErr(2) = 0.0;

	// Wstawienie pomiaru
	registerMeasurment(ref, obs, obsErr, rotSpeed, rotSpeedErr, timeStamp, w, detlaMk, zAngle);
}

void tlinAttitudeProcess ::registerMeasurment(const Eigen::Vector3d &inRef_, const Eigen::Vector3d &obs,
                                              const Eigen::Vector3d &obsErr, const Eigen::Vector3d &rotSpeed,
                                              const Eigen::Vector3d &rotSpeedErr, const double timeStamp,
                                              const double w, const double detlaMk, const double aZ)
{
	tlinAttitudeMeasurement measure{};

	// Rotacja obiektu referencyjnego o kat wynikajacy z rotacji ziemi
	Eigen ::Vector3d ref;
	Eigen ::Matrix3d rot;

	double rotZRad = 0.0;
	rotZRad        = aZ;

	// Rotacja obiektu referencyjnego
	attitude ::tlinAttitudeUtilsClass ::buildZRotaionMatrix(/*aZ*/ rotZRad, rot);

	TLINS_LOG_DEBUG("rotZRad = " + std::to_string(rotZRad));
	PRINT_M(rot, "rot", "%f");

	ref = rot * inRef_;
	PRINT_M(inRef_, "inRef", "%f");
	PRINT_M(ref, "Ref  ", "%f");
	PRINT_M(obs, "Obs  ", "%f");

	measure.setReferenceVector(ref);
	measure.setReferenceVectorOrg(inRef_);

	measure.setObservationVector(obs);
	measure.setObservationVectorError(obsErr);
	PRINT_M(obsErr, "obsErr", "%f");
	measure.setObservationTime(timeStamp);

	// Okreslenie katow rotacji ukladu
	measure.setAngleZ(aZ);

	// Wyznaczenie przyrostu czasu
	auto last = iterations.getFirst();
	if (last) {
		double deltaT = ::fabs(timeStamp - last->getMeasurment().getObservationTime());
		measure.setDeltaTime(deltaT);
	} else {
		measure.setDeltaTime(0.0);
	}

	measure.setWeight(w);
	measure.setDeltaM(detlaMk);
	measure.setRotationSpeed(rotSpeed);
	measure.setRotationSpeedError(rotSpeedErr);

	// Instancja iteracji
	std::shared_ptr<tlinAttitudeIteration> newIter = std ::make_shared<tlinAttitudeIteration>(measure);
	iterations.add2(newIter);
}

Eigen::Matrix3d tlinAttitudeProcess::getOptimalA()
{
	return optimalA;
}

Eigen::Matrix3d tlinAttitudeProcess::getOptimalAInversed()
{
	return optimalAInversed;
}

unsigned int tlinAttitudeProcess ::size()
{
	return iterations.size();
}

// +++++++++++++++++++++++++++++
// +++++++++++++++++++++++++++++
// +++++++++++++++++++++++++++++

struct AttitudePair {
	Eigen::Matrix3d attitudeOptimal;
	Eigen::Matrix3d attitudeOptimalInverted;

	std::vector<Eigen::Vector3d> errors;
	std::vector<Eigen::Vector3d> errorsInv;

	AttitudePair(Eigen::Matrix3d attitudeOptimal_, Eigen::Matrix3d attitudeOptimalInverted_)
	    : attitudeOptimal{attitudeOptimal_}, attitudeOptimalInverted{attitudeOptimalInverted_}
	{
	}
};


std::vector<tlinAttitudeProcess::VctorsAngleInfo> tlinAttitudeProcess::getVctorsAngle()
{
	std::vector<tlinAttitudeProcess::VctorsAngleInfo> result;
	std::set<std::string> resultUnique;

	std::vector<Eigen::Vector3d> refVectors;
	std::vector<Eigen::Vector3d> refVectorsOrg;
	std::vector<Eigen::Vector3d> obsVectors;

	for(auto &item: iterations) {
		auto &m = item -> getMeasurment();
		obsVectors.push_back(m.getObservationVectorNorm());

		refVectorsOrg.push_back(m.getReferenceVectorOrgNorm());
		refVectors.push_back(m.getReferenceVectorNorm());
	}

	for(int i = 0; i < refVectors.size(); i ++) {
		for(int j = 0; j < refVectors.size(); j ++) {
			std::string key1 = std::to_string(i) + "::" + std::to_string(j);
			std::string key2 = std::to_string(j) + "::" + std::to_string(i);
			if(i == j || resultUnique.count(key1) != 0 || resultUnique.count(key2) != 0) {
				// Juz jest
				continue;
			}
			resultUnique.insert(key1);
			resultUnique.insert(key2);


			// Liczymy katy
			double aRef = tlinAttitudeUtilsClass::vectorsAngle(refVectors[i], refVectors[j]);
			double aRefOrg = tlinAttitudeUtilsClass::vectorsAngle(refVectorsOrg[i], refVectorsOrg[j]);
			double aObs = tlinAttitudeUtilsClass::vectorsAngle(obsVectors[i], obsVectors[j]);

			tlinAttitudeProcess::VctorsAngleInfo info{};
			info.iteration1  = i;
			info.iteration2  = j;
			info.angleRef    = aRef;
			info.angleRefOrg = aRefOrg;
			info.angleObs    = aObs;

			info.observationVector_1  = obsVectors[i];
			info.referenceVector_1    = refVectors[i];
			info.referenceVectorOrg_1 = refVectorsOrg[i];

			info.observationVector_2  = obsVectors[j];
			info.referenceVector_2    = refVectors[j];
			info.referenceVectorOrg_2 = refVectorsOrg[j];

			result.push_back(info);
		}
	}


	return result;
}


std::vector<tlinMaxAttitudeInfo> tlinAttitudeProcess::validate()
{
	if (validator) {
		return validator->validate(iterations);
	}
	return {};
}

tlinAttitudeProcess::tlinAttitudeProcess() : iterations{}, validator{nullptr}
{
	// Okreslenie predkosci obrotowej

	auto &timeInst = tlinsTimeInfo ::getInstance();

	timeInst.setDateTime(2010, 1, 1, 12, 0, 0.0, tlinsTimeInfo ::getInstance().getScale());
	double angleStart = ::iauEra00(timeInst.getD1(), timeInst.getD2());

	timeInst.setDateTime(2010, 1, 1, 12, 0, 1.0, tlinsTimeInfo ::getInstance().getScale());
	double angleEnd = ::iauEra00(timeInst.getD1(), timeInst.getD2());

	// TODO - jeszcze do weryfikacji
	// Do sprawdzenia
	rotationSpeed = -1.0 * (angleEnd - angleStart);

	// Przywrucenie czasu
	timeInst.update();

	//
	// Rejestracja procesorow obliczajacych macierz transformacji
	//
	{
		attitude::tlinsAttitudeProcessor *      ptr_ = new attitude::tlinsAttProcessorOptimalRequest{rotationSpeed};
		std::unique_ptr<tlinsAttitudeProcessor> ptr{new tlinsAttProcessorOptimalRequest{rotationSpeed}};
		iterations.registerAttitudeProcessor(ptr);
	}

	{
		std::unique_ptr<tlinsAttitudeProcessor> ptr{new tlinsAttProcessorTraiad{}};
		iterations.registerAttitudeProcessor(ptr);
	}

	{
		std::unique_ptr<tlinsAttitudeProcessor> ptr{new tlinsAttProcessorQMethod{}};
		iterations.registerAttitudeProcessor(ptr);
	}

	// Rejestracja validatora
	validator.reset(new tlinsAttitudeProcessorStandardValidator{});
}

tlinAttitudeProcess ::~tlinAttitudeProcess()
{
}
}; // namespace attitude
