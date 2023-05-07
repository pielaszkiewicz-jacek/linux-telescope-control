#ifndef __tlinAttitudeProcessorBase_hpp__
#define __tlinAttitudeProcessorBase_hpp__

#include <Eigen/Dense>
#include <Eigen/Geometry>

#include <memory>
#include <vector>

#include "tlinAttitudeIteration.hpp"

namespace attitude
{
class tlinsAttitudeProcessorState {
  public:
	virtual Eigen::Matrix3d getAttitutude()         = 0;
	virtual Eigen::Matrix3d getInvertedAttitutude() = 0;
	virtual ~tlinsAttitudeProcessorState()          = default;
};

class tlinsAttitudeProcessor {
  public:
	// Procesowanie pojedynczej biezacej iteracji
	virtual std::shared_ptr<tlinsAttitudeProcessorState>
	iteration(std::shared_ptr<tlinsAttitudeProcessorState> currentState, std::shared_ptr<tlinAttitudeIteration> curIter,
	          std::shared_ptr<tlinAttitudeIteration> prevIter, std::shared_ptr<tlinAttitudeIteration> first) = 0;

	virtual std::string name() = 0;

	virtual bool isReqursive() = 0;

	// Procesowanie calego batcha iteracji
	virtual std::shared_ptr<tlinsAttitudeProcessorState> compute(tlinAttitudeIterations &iters) = 0;

	virtual ~tlinsAttitudeProcessor() = default;
};

//
// Zawiera informacje o macierzy rotacji, iteracji oraz typie procesora
//
struct tlinMaxAttitudeInfo {
	std::shared_ptr<tlinsAttitudeProcessorState> state;
	std::string                                  processor;
	std::shared_ptr<tlinAttitudeIteration>       iteration;
	Eigen::Vector3d                              errorV;
	double                                       error;

	tlinMaxAttitudeInfo &operator=(const tlinMaxAttitudeInfo &v) = default;
	tlinMaxAttitudeInfo &operator==(tlinMaxAttitudeInfo &&v)     = delete;

	tlinMaxAttitudeInfo() : state{nullptr}, processor{""}, iteration{nullptr}
	{
		errorV = Eigen::Vector3d::Zero();
		error  = 0.0;
	};
	~tlinMaxAttitudeInfo() = default;
};

class tlinsAttitudeProcessorValidatorBase {
  public:
	virtual std::vector<tlinMaxAttitudeInfo> validate(tlinAttitudeIterations &iters) = 0;
	virtual ~tlinsAttitudeProcessorValidatorBase()                                   = default;
};


}; // namespace attitude

#endif