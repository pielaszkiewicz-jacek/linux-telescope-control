#ifndef __tlinAttitudeIteration_hpp__
#define __tlinAttitudeIteration_hpp__

#include <Eigen/Dense>
#include <Eigen/Geometry>
#include <list>
#include <map>
#include <memory>
#include <mutex>
#include <utility>
#include <vector>

#include "tlinAttitudeMeasurment.hpp"
#include <tlinsAstroObject.hpp>

//
// --- Pojedyncza iteracja
//
namespace attitude
{

class tlinsAttitudeProcessorState;

class tlinAttitudeIteration {
  public:
	EIGEN_MAKE_ALIGNED_OPERATOR_NEW

  private:
	// Mapa stanów poszczegolnych algorytmow wyliczajacych mmacierz transformacji
	std::map<std::string, std::shared_ptr<tlinsAttitudeProcessorState>> statesMap;

  private:
	// Pomiar zwiazany z iteracja
	tlinAttitudeMeasurement measurment;

  public:
	const tlinAttitudeMeasurement               &getMeasurment() const;
	std::shared_ptr<tlinsAttitudeProcessorState> getState(const std::string &id)
	{
		if (statesMap.count(id) == 0) {
			return std::shared_ptr<tlinsAttitudeProcessorState>{nullptr};
		}
		return getState[id];
	};

  public:
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
	std::shared_ptr<tlinAttitudeIteration>             firstElement;
	std ::list<std::shared_ptr<tlinAttitudeIteration>> iterations;

	// Aktualna macierz transformacji
	Eigen ::Matrix3d attirtude;

	std ::mutex  mtx;
	unsigned int sizeLimit;
	int          totalCount;

  public:
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

	tlinAttitudeIterations(const unsigned int maxSize);
	virtual ~tlinAttitudeIterations();
};

}; // namespace attitude

#endif