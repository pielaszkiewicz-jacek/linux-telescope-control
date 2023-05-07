#include <Eigen/Geometry>
#include <get_quat_from_K.h>
#include <get_quat_from_K_data.h>
#include <optimal_request.h>
#include <optimal_request_init.h>
#include <tlinAttitudeUtilsClass.hpp>
#include <tlinsAttitudeProcessor.hpp>
#include <tlinsBacktrace.hpp>

namespace attitude
{
//
// ----------------------------
// Validator
// ----------------------------
//
std::vector<tlinMaxAttitudeInfo> tlinsAttitudeProcessorStandardValidator::validate(tlinAttitudeIterations &iters)
{
	std::vector<tlinMaxAttitudeInfo> result{};

	// Tworzenie rezultatu
	for (auto iter : iters) {
		auto &states = iter->getStates();

		// Potencialnie jako rezultat nalezy wykorzystac ostatnią macierz transformacji - TODO
		// Przejscie po wynikach
		for (auto state : states) {

			result.push_back(tlinMaxAttitudeInfo{});
			auto itemIdx = result.size() - 1;

			result[itemIdx].state     = state.second;
			result[itemIdx].processor = state.first;
			result[itemIdx].iteration = iter;
			// Blad bedzie wyliczony w nastepnym kroku
		}
	}

	auto errorVec = [](const Eigen::Matrix3d &m, const Eigen::Vector3d &obs,
	                   const Eigen::Vector3d &ref) -> Eigen::Vector3d {
		Eigen::Vector3d newObs = m * ref;
		return obs - newObs;
	};

	auto errorNorm = [](const Eigen::Vector3d &err) -> double {
		//		return (::fabs(err(0)) + ::fabs(err(1)) + ::fabs(err(2))) / 3.0;
		// Zmormalizowany blad to dlugosc wektora bledu
		return ::sqrt(err(0) * err(0) + err(1) * err(1) + err(2) * err(2));
		/* return err.norm();*/
	};

	// Obliczanie bledu dla poszczegolnych pozycji
	// Blad liczonmy jest jako warto ść srednia ze wszystkich pomiarow dla kazdej macierzy transfoemacji
	for (auto &resItem : result) {
		int             count = 0;
		Eigen::Vector3d errorV{Eigen::Vector3d::Zero()};
		double          errorS{0.0};

		for (auto iter : iters) {
			auto &m = iter->getMeasurment();

			auto err =
			    errorVec(resItem.state->getAttitutude(), m.getObservationVectorNorm(), m.getReferenceVectorNorm());
			errorV = errorV + err;
			// errorS = errorS + errorNorm(err);
			count++;
		}
		double countd  = static_cast<double>(count);
		resItem.errorV = errorV / countd;
		resItem.error  = errorNorm(resItem.errorV); // errorS / countd;
	}

	// Sortowanie wyniku po błedzie skalarnym
	std::sort(result.begin(), result.end(),
	          [](const tlinMaxAttitudeInfo &a, const tlinMaxAttitudeInfo &b) { return a.error < b.error; });
	return result;
}

//
// ----------------------------
// ----- OPTIMAL REQUEST ------
// ----------------------------
//
class tlinsAttProcessorOptimalRequestState : public tlinsAttitudeProcessorState {
	friend class tlinsAttProcessorOptimalRequest;

  private:
	struct0_T optReqState;

  public:
	virtual Eigen::Matrix3d getAttitutude();
	virtual Eigen::Matrix3d getInvertedAttitutude();

	tlinsAttProcessorOptimalRequestState &operator=(const tlinsAttProcessorOptimalRequestState &v);
	tlinsAttProcessorOptimalRequestState &operator=(tlinsAttProcessorOptimalRequestState &&v);

	tlinsAttProcessorOptimalRequestState() = delete;
	tlinsAttProcessorOptimalRequestState(std::shared_ptr<tlinsAttitudeProcessorState> current,
	                                     std::shared_ptr<tlinAttitudeIteration> v, double dt, Eigen::Vector3d &aSpeed);
	virtual ~tlinsAttProcessorOptimalRequestState() = default;
};

Eigen::Matrix3d tlinsAttProcessorOptimalRequestState::getAttitutude()
{
	float qEst[4];
	::get_quat_from_K(optReqState.K, qEst);

	Eigen::Quaterniond qq(qEst[0], qEst[1], qEst[2], qEst[3]);
	Eigen::Matrix3d    result = qq.toRotationMatrix().inverse();
	return result;
}

Eigen::Matrix3d tlinsAttProcessorOptimalRequestState::getInvertedAttitutude()
{
	float qEst[4];
	::get_quat_from_K(optReqState.K, qEst);

	Eigen::Quaterniond qq(qEst[0], qEst[1], qEst[2], qEst[3]);
	Eigen::Matrix3d    result = qq.toRotationMatrix();
	return result;
}

tlinsAttProcessorOptimalRequestState &
tlinsAttProcessorOptimalRequestState::operator=(const tlinsAttProcessorOptimalRequestState &v)
{
	optReqState = v.optReqState;
	return *this;
}

tlinsAttProcessorOptimalRequestState &
tlinsAttProcessorOptimalRequestState::operator=(tlinsAttProcessorOptimalRequestState &&v)
{
	optReqState = v.optReqState;
	return *this;
}

tlinsAttProcessorOptimalRequestState::tlinsAttProcessorOptimalRequestState(
    std::shared_ptr<tlinsAttitudeProcessorState> prev_, std::shared_ptr<tlinAttitudeIteration> v, double dt,
    Eigen::Vector3d &aSpeed)
{
	tlinsAttProcessorOptimalRequestState *prev = dynamic_cast<tlinsAttProcessorOptimalRequestState *>(prev_.get());

	// Kopia poprzedniego stanu
	if (prev) {
		optReqState = prev->optReqState;
	} else {
		::memset((void *) &optReqState, 0, sizeof(struct0_T));
		optReqState.Mu_noise_var  = 0.0000010f;
		optReqState.Eta_noise_var = 0.0000010f;
	}

	// Pomiar
	auto &m = v->getMeasurment();

	// Blad pomiaru
	double sumErr = 0.0;
	for (int i = 0; i < 3; i++) {
		sumErr += m.getObservationVectorError()(i);
	}
	sumErr /= 3.0;

	// optReqState.Mu_noise_var  = 0.0008117f;
	// optReqState.Eta_noise_var = 0.0000010f;
	optReqState.Mu_noise_var  = sumErr;
	optReqState.Eta_noise_var = sumErr;

	Eigen ::Vector3d newRef     = m.getReferenceVectorNorm();
	auto             ref        = newRef;
	auto             obs        = m.getObservationVectorNorm();
	auto             refVirtual = ref * -1.0;
	auto             obsVirtual = obs * -1.0;

	// Obiekty referencyjne i obserwowane
	for (int i = 0; i < 3; i++) {
		optReqState.r[i]     = ref(i);
		optReqState.r[i + 3] = refVirtual(i);

		optReqState.b[i]     = obs(i);
		optReqState.b[i + 3] = obsVirtual(i);
	}

	// Rotacja
	optReqState.w[0] = aSpeed(0);
	optReqState.w[1] = aSpeed(1);
	optReqState.w[2] = aSpeed(2);

	// Dystan czasu
	optReqState.dT = dt;
}

//
// ----------------------------------
//
std::shared_ptr<tlinsAttitudeProcessorState> tlinsAttProcessorOptimalRequest::iteration(
    std::shared_ptr<tlinsAttitudeProcessorState> currentState, std::shared_ptr<tlinAttitudeIteration> curIter,
    std::shared_ptr<tlinAttitudeIteration> prevIter, std::shared_ptr<tlinAttitudeIteration> firstIter)
{
	bool                                         isFirst = !prevIter || !currentState;
	std::shared_ptr<tlinsAttitudeProcessorState> state{nullptr};
	Eigen::Vector3d                              aSpeed;

	if (isFirst) {
		double          dt     = 0.0;
		Eigen::Vector3d aSpeed = Eigen::Vector3d::Zero();
		state                  = std::make_shared<tlinsAttProcessorOptimalRequestState>(nullptr, curIter, 0.0, aSpeed);
	} else {
		// Obliczenie przyrostu czasu
		auto  &currM = curIter->getMeasurment();
		auto  &prevM = prevIter->getMeasurment();
		double dt    = ::fabs(currM.getObservationTime() - prevM.getObservationTime());

		// Wyznaczenie predkosci obrotowej
		Eigen::Vector3d aSpeed = Eigen::Vector3d::Zero();
		aSpeed[2]              = erathRotationSpeed;
		state.reset(new tlinsAttProcessorOptimalRequestState{currentState, curIter, dt, aSpeed});
	}

	tlinsAttProcessorOptimalRequestState *ptr = dynamic_cast<tlinsAttProcessorOptimalRequestState *>(state.get());
	struct0_T                            &optReqHandle = ptr->optReqState;

	if (isFirst) {
		// Pierwsza iteracja
		::optimal_request_init(&optReqHandle);
	} else {
		// Next iteration
		::optimal_request(&optReqHandle);
	}
	return state;
}

bool tlinsAttProcessorOptimalRequest::isReqursive()
{
	return true;
}

std::string tlinsAttProcessorOptimalRequest::name()
{
	return {"Attitude-Processor::OPTIMAL_REQUEST"};
}

std::shared_ptr<tlinsAttitudeProcessorState> tlinsAttProcessorOptimalRequest::compute(tlinAttitudeIterations &iters)
{
	std::shared_ptr<tlinsAttitudeProcessorState> state{nullptr};
	std::shared_ptr<tlinAttitudeIteration>       curIter;
	std::shared_ptr<tlinAttitudeIteration>       prevIter;
	std::shared_ptr<tlinAttitudeIteration>       first = iters.getLast();

	for (auto iter : iters) {
		prevIter = curIter;
		curIter  = iter;
		state    = iteration(state, curIter, prevIter, first);
	}
	return state;
}

tlinsAttProcessorOptimalRequest::tlinsAttProcessorOptimalRequest(const double erathRotationSpeed_)
    : erathRotationSpeed{erathRotationSpeed_}
{
}

//
// ----------------------------
// --------- TRIAD ------------
// ----------------------------
//
class tlinsAttProcessorTraiadState : public tlinsAttitudeProcessorState {

  private:
	Eigen::Matrix3d attitude;

  public:
	virtual Eigen::Matrix3d getAttitutude()
	{
		return attitude.inverse();
	};

	virtual Eigen::Matrix3d getInvertedAttitutude()
	{
		return attitude;
	};

	tlinsAttProcessorTraiadState &operator=(const tlinsAttProcessorTraiadState &v)
	{
		attitude = v.attitude;
		return *this;
	};

	tlinsAttProcessorTraiadState &operator=(tlinsAttProcessorTraiadState &&v)
	{
		attitude = v.attitude;
		return *this;
	};

	tlinsAttProcessorTraiadState()
	{
		attitude = Eigen::Matrix3d::Zero();
	};

	tlinsAttProcessorTraiadState(Eigen::Matrix3d attitude_)
	{
		attitude = attitude_;
	};

	virtual ~tlinsAttProcessorTraiadState() = default;
};

// ----------------------------

std::shared_ptr<tlinsAttitudeProcessorState> tlinsAttProcessorTraiad::iteration(
    std::shared_ptr<tlinsAttitudeProcessorState>, std::shared_ptr<tlinAttitudeIteration> curIter,
    std::shared_ptr<tlinAttitudeIteration> prevIter, std::shared_ptr<tlinAttitudeIteration>)
{
	bool                                         isFirst = !prevIter;
	std::shared_ptr<tlinsAttitudeProcessorState> state{new tlinsAttProcessorTraiadState{Eigen::Matrix3d::Identity()}};

	if (isFirst) {
		// Pierwsza iteracja
		return state;
	} else {
		// Pomiary

		auto &currM = curIter->getMeasurment();
		auto &prevM = prevIter->getMeasurment();

		Eigen::Vector3d t1b = currM.getObservationVectorNorm();
		Eigen::Vector3d t1r = currM.getReferenceVectorNorm();

		Eigen::Vector3d t2b_ = currM.getObservationVectorNorm().cross(prevM.getObservationVectorNorm());
		Eigen::Vector3d t2b  = t2b_ / t2b_.norm();

		Eigen::Vector3d t2r_ = currM.getReferenceVectorNorm().cross(prevM.getReferenceVectorNorm());
		Eigen::Vector3d t2r  = t2r_ / t2r_.norm();

		Eigen::Vector3d t3b = t1b.cross(t2b);
		Eigen::Vector3d t3r = t1r.cross(t2r);

		Eigen::Matrix3d Rb = Eigen::Matrix3d::Zero();
		Eigen::Matrix3d Rr = Eigen::Matrix3d::Zero();

		for (int i = 0; i < 3; i++) {
			Rb(i, 0) = t1b(i);
			Rb(i, 1) = t2b(i);
			Rb(i, 2) = t3b(i);

			Rr(i, 0) = t1r(i);
			Rr(i, 1) = t2r(i);
			Rr(i, 2) = t3r(i);
		}

		// Nowy stan dla aktualnych dwóch pomiarow
		Eigen::Matrix3d D = Rb * Rr.transpose();

		// Zapamietanie stanu
		state.reset(new tlinsAttProcessorTraiadState{D.transpose()});
		return state;
	}
}

std::string tlinsAttProcessorTraiad::name()
{
	return {"Attitude-Processor::TRIAD"};
}

bool tlinsAttProcessorTraiad::isReqursive()
{
	return true;
}

std::shared_ptr<tlinsAttitudeProcessorState> tlinsAttProcessorTraiad::compute(tlinAttitudeIterations &iters)
{
	std::shared_ptr<tlinsAttitudeProcessorState> state{nullptr};
	std::shared_ptr<tlinAttitudeIteration>       curIter{nullptr};
	std::shared_ptr<tlinAttitudeIteration>       prevIter{nullptr};

	for (auto iter : iters) {
		prevIter = curIter;
		curIter  = iter;
		state    = iteration({nullptr}, curIter, prevIter, {nullptr});
	}
	return state;
}

//
// Q-Method
//
class tlinsAttProcessorQMethodState : public tlinsAttitudeProcessorState {
	friend class tlinsAttProcessorQMethod;

  private:
	Eigen::Matrix3d attitude;

  public:
	virtual Eigen::Matrix3d getAttitutude()
	{
		return attitude.inverse();
	};

	virtual Eigen::Matrix3d getInvertedAttitutude()
	{
		return attitude;
	};

	tlinsAttProcessorQMethodState &operator=(const tlinsAttProcessorQMethodState &v)
	{
		attitude = v.attitude;
		return *this;
	};

	tlinsAttProcessorQMethodState &operator=(tlinsAttProcessorQMethodState &&v)
	{
		attitude = v.attitude;
		return *this;
	};

	tlinsAttProcessorQMethodState()
	{
		attitude = Eigen::Matrix3d::Zero();
	};

	tlinsAttProcessorQMethodState(Eigen::Matrix3d attitude_)
	{
		attitude = attitude_;
	};

	virtual ~tlinsAttProcessorQMethodState() = default;
};

std::shared_ptr<tlinsAttitudeProcessorState> tlinsAttProcessorQMethod::iteration(
    std::shared_ptr<tlinsAttitudeProcessorState> currentState, std::shared_ptr<tlinAttitudeIteration> curIter,
    std::shared_ptr<tlinAttitudeIteration> prevIter, std::shared_ptr<tlinAttitudeIteration> first)
{
	return std::shared_ptr<tlinsAttitudeProcessorState>{nullptr};
}

std::string tlinsAttProcessorQMethod::name()
{
	return {"Attitude-Processor-Q_METHOD"};
}

bool tlinsAttProcessorQMethod::isReqursive()
{
	return false;
}

// Procesowanie calego batcha iteracji
std::shared_ptr<tlinsAttitudeProcessorState> tlinsAttProcessorQMethod::compute(tlinAttitudeIterations &iters)
{
	std::vector<Eigen::Vector3d> refv;
	std::vector<Eigen::Vector3d> obsv;
	std::vector<double>          wv;
	double                       w = 1.0 / static_cast<double>(iters.size());

	// Zbieranie pomiarow
	for (auto iter : iters) {
		auto &m = iter->getMeasurment();

		Eigen::Vector3d ref = m.getReferenceVectorNorm();
		Eigen::Vector3d obs = m.getObservationVectorNorm();

		refv.push_back(ref);
		obsv.push_back(obs);
		wv.push_back(w);
	}

	// Macierz B
	Eigen ::Matrix3d B;
	attitude::tlinAttitudeUtilsClass::create_B(refv, obsv, wv, B);

	// Macierz S
	Eigen ::Matrix3d S;
	attitude::tlinAttitudeUtilsClass::create_S(B, S);

	// Macierz Z
	Eigen ::Vector3d Z;
	attitude::tlinAttitudeUtilsClass::create_Z(B, Z);

	// Sigma
	double sigma;
	attitude::tlinAttitudeUtilsClass::create_sigma(B, sigma);

	// Macierz K
	Eigen ::Matrix4d K;
	attitude::tlinAttitudeUtilsClass::create_K(S, Z, sigma, 1.0, K);

	// Create attitude
	Eigen::Vector4d eigenvalues;
	Eigen::Matrix4d eigenvectors;
	double          lambda;
	Eigen::Matrix3d att;
	attitude::tlinAttitudeUtilsClass::create_attitude(K, eigenvalues, eigenvectors, lambda, att);

	// Wynik
	std::shared_ptr<tlinsAttitudeProcessorState> state{new tlinsAttProcessorQMethodState(att)};

	// Korekta - manualna
	tlinsAttProcessorQMethodState *state_ = dynamic_cast<tlinsAttProcessorQMethodState *>(state.get());

	return state;
}

} // namespace attitude