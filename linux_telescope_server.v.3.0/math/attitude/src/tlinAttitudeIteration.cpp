
#include "tlinAttitudeIteration.hpp"
#include "tlinAttitudeProcessorBase.hpp"
#include "tlinAttitudeUtilsClass.hpp"


#include <cmath>
#include <tlinsBacktrace.hpp>

namespace attitude
{


bool tlinAttitudeIterations::ProcessorCompartatorLess::operator()(const std::unique_ptr<tlinsAttitudeProcessor> &v1,
                                                                  const std::unique_ptr<tlinsAttitudeProcessor> &v2)
{
	return v1->name() < v2->name();
};


std ::shared_ptr<tlinsAttitudeProcessorState> tlinAttitudeIteration::getState(const std::string &id)
{
	if (statesMap.count(id) == 0) {
		return std ::shared_ptr<tlinsAttitudeProcessorState>{nullptr};
	}

	return statesMap[id];
};

void tlinAttitudeIteration::setState(const std::string &id, std::shared_ptr<tlinsAttitudeProcessorState> state)
{
	statesMap[id] = state;
};

const tlinAttitudeMeasurement &tlinAttitudeIteration::getMeasurment() const
{
	return measurment;
}

static double _getNorm(Eigen::Vector3d v)
{
	return 1.0 / ::sqrt(v(0) * v(0) + v(1) * v(1) + v(2) * v(2));
}

static Eigen::Vector3d cross(const Eigen::Vector3d &a, const Eigen::Vector3d &b)
{
	Eigen::Vector3d ret;

	ret(0) = a(1) * b(2) - a(2) * b(1);
	ret(1) = a(2) * b(0) - a(0) * b(2);
	ret(2) = a(0) * b(1) - a(1) * b(0);
	return ret;
}

tlinAttitudeIteration::tlinAttitudeIteration()
{
}

// Konstruktor/destruktor klasy
tlinAttitudeIteration::tlinAttitudeIteration(const tlinAttitudeMeasurement &m) : measurment{m}
{
}

tlinAttitudeIteration::~tlinAttitudeIteration()
{
}

//
// --- Kontener przechowujacy iteracje
//
void tlinAttitudeIterations::add(const std::shared_ptr<tlinAttitudeIteration> &iter)
{
	std::unique_lock<std::mutex> lock{mtx};

	iterations.push_front(iter);
	iter->setSeqId(iterations.size());
}

void tlinAttitudeIterations::add2(const std::shared_ptr<tlinAttitudeIteration> &iter)
{
	//
	// 1. Dodanie iteracji
	add(iter);

	//
	// 2. Uruchomienie procesorów
	auto currentIter  = getFirst();
	auto previousIter = getSecond();
	auto firstIter    = getLast();

	for (auto &item : attitudeProcessors) {
		auto                                          processorId = item->name();
		std ::shared_ptr<tlinsAttitudeProcessorState> currentState{nullptr};
		if (previousIter) {
			currentState = previousIter->getState(processorId);
		}

		std::shared_ptr<tlinsAttitudeProcessorState> newState{nullptr};

		if (item->isReqursive()) {
			// Macierz obrotu jest aktualizowana incrementalnie
			newState = item->iteration(currentState, currentIter, previousIter, firstIter);
		} else {
			// Macierz obrotu jest obliczana dla wszystkich pomiarow
			newState = item->compute(*this);
		}

		TLINS_LOG_DEBUG("");
		TLINS_LOG_DEBUG("Processor: " + processorId);
		TLINS_LOG_DEBUG("---------------------------------------------------------------");
		PRINT_M(newState->getAttitutude(), "  Attitude          ", "%f");
		PRINT_M(newState->getInvertedAttitutude(), "  Attitude (A ^ -1) ", "%f");

		if (newState) {
			currentIter->setState(processorId, newState);
		}
	}
}

std::shared_ptr<tlinAttitudeIteration> tlinAttitudeIterations::getLast()
{
	return iterations.back();
}

std::shared_ptr<tlinAttitudeIteration> tlinAttitudeIterations::getFirst()
{
	std::unique_lock<std::mutex>           lock{mtx};
	std::shared_ptr<tlinAttitudeIteration> result{nullptr};

	if (iterations.empty())
		return std::shared_ptr<tlinAttitudeIteration>{nullptr};

	return iterations.front();
}

std::shared_ptr<tlinAttitudeIteration> tlinAttitudeIterations::getSecond()
{
	std::unique_lock<std::mutex> lock{mtx};

	if (iterations.size() < 2)
		return std::shared_ptr<tlinAttitudeIteration>{nullptr};

	auto iter = iterations.begin();
	iter++;
	return *iter;
}

const unsigned int tlinAttitudeIterations::size()
{
	iterations.size();
}

tlinAttitudeIterations::~tlinAttitudeIterations()
{
}
}; // namespace attitude