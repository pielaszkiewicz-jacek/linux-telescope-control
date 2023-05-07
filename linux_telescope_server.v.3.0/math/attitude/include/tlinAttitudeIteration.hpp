#ifndef __tlinAttitudeIteration_hpp__
#define __tlinAttitudeIteration_hpp__

#include <Eigen/Dense>
#include <Eigen/Geometry>
#include <list>
#include <map>
#include <memory>
#include <mutex>
#include <set>
#include <utility>
#include <vector>

#include "tlinAttitudeMeasurment.hpp"
#include <tlinsAstroObject.hpp>
//
// --- Pojedyncza iteracja
//
namespace attitude
{
class tlinsAttitudeProcessorValidatorBase;
class tlinsAttitudeProcessorState;
class tlinsAttitudeProcessor;

// enum class AttitudeLogLevel { DEBUG = 0, INFO = 1, WARNING = 2, ERROR = 3 };

class tlinAttitudeIteration {
  public:
	EIGEN_MAKE_ALIGNED_OPERATOR_NEW
	int seqId;

  private:
	// Mapa stanów poszczegolnych algorytmow wyliczajacych mmacierz transformacji
	std::map<std::string, std::shared_ptr<tlinsAttitudeProcessorState>> statesMap;

  private:
	// Pomiar zwiazany z iteracja
	tlinAttitudeMeasurement measurment;

  public:
	void setSeqId(const int v)
	{
		seqId = v;
	};

	int getSeqId() const
	{
		return seqId;
	};

	bool setAttitude(const std::string &id);

	const std::map<std::string, std::shared_ptr<tlinsAttitudeProcessorState>> &getStates()
	{
		return statesMap;
	};

	std ::shared_ptr<tlinsAttitudeProcessorState> getState(const std::string &id);
	void setState(const std::string &id, std::shared_ptr<tlinsAttitudeProcessorState> state);

	const tlinAttitudeMeasurement &getMeasurment() const;

  public:
	// Obliczanie iteracji
	void compute(std ::shared_ptr<tlinAttitudeIteration> prev);

	// Konstruktor/destruktor klasy/operatory
	tlinAttitudeIteration &operator=(const tlinAttitudeIteration &v) = default;
	tlinAttitudeIteration &operator=(tlinAttitudeIteration &&v) = default;

	tlinAttitudeIteration();
	tlinAttitudeIteration(const tlinAttitudeMeasurement &m);

	tlinAttitudeIteration(const tlinAttitudeIteration &v) = default;
	tlinAttitudeIteration(tlinAttitudeIteration &&v)      = default;
	virtual ~tlinAttitudeIteration();
};

//
// --- Kontener przechowujacy iteracje
//
class tlinAttitudeIterations {
  private:
	// Iteracje
	std ::list<std::shared_ptr<tlinAttitudeIteration>> iterations;

	// Aktualna macierz transformacji
	Eigen ::Matrix3d attirtude;

	std ::mutex mtx;

	struct ProcessorCompartatorLess {
		bool operator()(const std::unique_ptr<tlinsAttitudeProcessor> &v1,
		                const std::unique_ptr<tlinsAttitudeProcessor> &v2);
	};

	std::set<std::unique_ptr<tlinsAttitudeProcessor>, ProcessorCompartatorLess> attitudeProcessors;

  public:
	void registerAttitudeProcessor(std::unique_ptr<tlinsAttitudeProcessor> &ptr)
	{
		std::unique_lock<std::mutex> lock{mtx};
		attitudeProcessors.insert(std::move(ptr));
	};

	void add2(const std::shared_ptr<tlinAttitudeIteration> &iter);

	// Dodanie iteracji oraz obliczenie aktualnej macierzy obrotu
	void add(const std::shared_ptr<tlinAttitudeIteration> &iter);

	// Licznik iteracji
	const unsigned int size();

	std ::list<std::shared_ptr<tlinAttitudeIteration>>::iterator begin()
	{
		return iterations.begin();
	};

	std ::list<std::shared_ptr<tlinAttitudeIteration>>::iterator end()
	{
		return iterations.end();
	};

	bool isEmpty() const
	{
		return iterations.empty();
	};

	std ::shared_ptr<tlinAttitudeIteration> getLast();
	std ::shared_ptr<tlinAttitudeIteration> getFirst();
	std ::shared_ptr<tlinAttitudeIteration> getSecond();

	tlinAttitudeIterations() = default;
	virtual ~tlinAttitudeIterations();
};

}; // namespace attitude

#endif