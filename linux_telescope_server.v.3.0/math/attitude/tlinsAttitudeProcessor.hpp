#ifndef __tlinsAttitudeProcessor_hpp__
#define __tlinsAttitudeProcessor_hpp__

#include "tlinAttitudeIteration.hpp"
#include <memory.h>
#include <string.h>

//
// Procesor OPTIMAL REQUEST
//
namespace attitude
{

class tlinsAttProcessorOptimalRequest : public tlinsAttitudeProcessor {
  private:
	double erathRotationSpeed;

  public:
	// Procesowanie pojedynczej biezacej iteracji
	virtual std::shared_ptr<tlinsAttitudeProcessorState>
	iteration(std::shared_ptr<tlinsAttitudeProcessorState> currentState, std::shared_ptr<tlinAttitudeIteration> curIter,
	          std::shared_ptr<tlinAttitudeIteration> prevIter, std::shared_ptr<tlinAttitudeIteration> first);

	virtual std::string name();
	virtual bool        isReqursive();

	// Procesowanie calego batcha iteracji
	virtual std::shared_ptr<tlinsAttitudeProcessorState> compute(tlinAttitudeIterations &iters);

	tlinsAttProcessorOptimalRequest(const double erathRotationSpeed_);
	virtual ~tlinsAttProcessorOptimalRequest() = default;
};

//
// Procesor Triad
//
class tlinsAttProcessorTraiad : public tlinsAttitudeProcessor {
  private:
	double erathRotationSpeed;

  public:
	// Procesowanie pojedynczej biezacej iteracji
	virtual std::shared_ptr<tlinsAttitudeProcessorState>
	iteration(std::shared_ptr<tlinsAttitudeProcessorState> currentState, std::shared_ptr<tlinAttitudeIteration> curIter,
	          std::shared_ptr<tlinAttitudeIteration> prevIter, std::shared_ptr<tlinAttitudeIteration> first);

	virtual std::string name();
	virtual bool        isReqursive();

	// Procesowanie calego batcha iteracji
	virtual std::shared_ptr<tlinsAttitudeProcessorState> compute(tlinAttitudeIterations &iters);

	tlinsAttProcessorTraiad()          = default;
	virtual ~tlinsAttProcessorTraiad() = default;
};

//
//bQ-Method
//
class tlinsAttProcessorQMethod : public tlinsAttitudeProcessor {
  public:
	// Procesowanie pojedynczej biezacej iteracji
	virtual std::shared_ptr<tlinsAttitudeProcessorState>
	iteration(std::shared_ptr<tlinsAttitudeProcessorState> currentState, std::shared_ptr<tlinAttitudeIteration> curIter,
	          std::shared_ptr<tlinAttitudeIteration> prevIter, std::shared_ptr<tlinAttitudeIteration> first);

	virtual std::string name();
	virtual bool        isReqursive();

	// Procesowanie calego batcha iteracji
	virtual std::shared_ptr<tlinsAttitudeProcessorState> compute(tlinAttitudeIterations &iters);

	tlinsAttProcessorQMethod()          = default;
	virtual ~tlinsAttProcessorQMethod() = default;
};

}

#endif