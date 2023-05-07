#ifndef __tlinsAtroEngine_hpp__
#define __tlinsAtroEngine_hpp__

#include <Eigen/Eigenvalues>
#include <Eigen/Geometry>
#include <atomic>
#include <chrono>
#include <condition_variable>
#include <list>
#include <memory>
#include <mutex>
#include <vector>

#include <tlinAttitudeProcess.hpp>
#include <tlinsAstroException.hpp>
#include <tlinsAstroObject.hpp>
#include <tlinsBacktrace.hpp>
#include <tlinsFullCoordinate.hpp>
#include <tlinsMoveServerInterface.hpp>
#include <tlinsStarApparentPlaceCalculationSofa.hpp>
#include <tlins_math.hpp>

#include <astro.grpc.pb.h>
#include <atomic>


class tlinsAstroEngine {
  public:
	enum class ENGINE_STATE {
		STATE_CALIBRATION = 0, // Tryb zbierania pomiarow dla potrzeb
		// pudowania macierzy transformacji

		STATE_REGULAR = 1, // Normalny tryb sinlika polegajacy na
		                   // regulanrym sledzeniu obiektu
	};

	enum class ENGINE_MODE {
		MODE_NONE             = 0,
		MODE_STANDARD         = 1, // Standardowy tryb pracy
		MODE_EXTERNAL_SUPPORT = 2, // Tryb sledzenia ze wsparciem guidera.
		MODE_STANDARD_SPEED   = 3  // Standardowy tryb pracy
	};

	enum class ENGINE_MULTIPLE_MODE_FINALL {
		SWITCH_TO_STANDARD = 0, // Silnik przelaczy sie do trybu MODE_STANDARD
		SWITCH_TO_EXTERNAL = 1  // Silnik perzelaczy się do trybu MODE_EXTERNAL_SUPPORT
	};

  public:
	EIGEN_MAKE_ALIGNED_OPERATOR_NEW

  public:
	// Struktura przechowuje pojedynczy cel
	struct tlinsSingleTarget {
		// Cel
		tlinsAstroObject target;

		// Informacja potrzebna do przetwarzania tracowania
		tlinsAstroObject                      targetTrackBase;
		std::chrono::system_clock::time_point targetTrackBaseTime;

		// Predkosc przemieszczenia [radiany]
		double speed;

		// Przyspieszenie i hamowanie (rampa symetryczna) [radiany]
		double aceleration;

		tlinsSingleTarget &operator=(const tlinsSingleTarget &t) = default;
		tlinsSingleTarget(const tlinsAstroObject &t, const double v, const double a);
		tlinsSingleTarget();

		virtual ~tlinsSingleTarget() = default;
	};

  public:
	enum class AXIS { RA = 1, DEC = 2 };
	enum class DIRECTION { UP = 1, DOWN = 2, LEFT = 3, RIGHT = 4 };

  private:
	std::shared_ptr<tlinsMoveServerInterface> moveService;
	std::string                               deviceName;
	std::string                               axisXName{"X"};
	std::string                               axisYName{"Y"};

	enum class __MOVE_ENGINE_STATE_ENFORE__ { AXIS = 1, SYNCH = 2 };
	std::atomic<__MOVE_ENGINE_STATE_ENFORE__> moveEngineSetIntoAxisMode;

	// Znacznik czy ma nastapic automatyczna zmina trybu pracy z synchronicznego na predkosc w trybie SPEED
	std::atomic<bool>        switchMode;
	std::atomic<ENGINE_MODE> desiredMode;

	long speedModeWaitIterval;

	// Procentowa minimalna predkość nominalnej gdy musimy zwalniać.
	double minSpeedPercantage;
	double maxSpeedPercantage;
	double minSpeedCorrection;
	bool   suspendSpeedCorrection;
	bool   reverseSpeedCorrection;

	bool tracePosition;

	double              raManualCorrection{0.0};
	DIRECTION           raManualCorrectionDir;
	double              decManualCorrection{0.0};
	DIRECTION           decManualCorrectionDir;
	std::atomic<double> speedManualCorrectionX{0.0};
	std::atomic<double> speedManualCorrectionY{0.0};

	// Double auto guider corrections
	std::mutex          correctionSetMtx;
	std::atomic<double> guiderXCorrection{0.0};
	std::atomic<double> guiderYCorrection{0.0};
	double              guiderXSpeed;
	double              guiderYSpeed;

	bool guiderUseRAspeedForDEC;

	// Klasa timera
	struct __timer___;

	// Timery zwiazane z obsluga guidera
	std::mutex guiderTimerMutex;

	std::shared_ptr<__timer___> guiderTimer;
	std::atomic<bool>           guiderTimerInUse;
	std::thread                 guiderTimerThread;

  private:
	//
	// Klasa implementujaca callback potwierdzajacy wykonanie przemieszczenia
	//
	class ConfirmationCallback : public tlinsMoveServerInterface::tlinsMoveRequestConfirmation {
	  private:
		// Obiekt rodzic
		tlinsAstroEngine &engine;
		std::atomic<bool> reqConfirmed{false};

	  public:
		virtual void process(const tlins::tlinsRpcConfirmationStatus &status);
		virtual bool release();

		ConfirmationCallback(tlinsAstroEngine &engine);
		virtual ~ConfirmationCallback() = default;
	};

	friend class ConfirmationCallback;

  private:
	//
	// 1. Statystyki czasu
	//
	struct TimeStatistics {
		// Calowity czas przetwarzania rzadania
		double processingTime;

		// Czas spedzony na obliczeniach
		double processingTimeCalculation;

		// Czas spedzony na przetwarzaniu rzadania
		double processingTimeMoveRequest;

		TimeStatistics &operator=(const TimeStatistics &v) = default;

		TimeStatistics(const double processingTime_, const double processingTimeCalculation_,
		               const double processingTimeMoveRequest_);
		TimeStatistics(const TimeStatistics &v) = default;
		TimeStatistics();
		virtual ~TimeStatistics() = default;
	};

	// Znacznik nowego targetu
	bool newTarget{false};

	std ::list<TimeStatistics> timeStatistics;
	TimeStatistics             timeStatisticsAvg;
	TimeStatistics             timeStatisticsMax;
	TimeStatistics             timeStatisticsMin;
	unsigned long              timeStatisticsMaxHistoryLenght{2000};
	std::mutex                 timeStatisticsMtx;

	void addTimeStatistic(const double processingTime, const double processingTimeCalculation,
	                      const double processingTimeMoveRequest);
	void getTimeStatisticAvg(double &processingTime, double &processingTimeCalculation,
	                         double &processingTimeMoveRequest) const;
	void getTimeStatisticMax(double &processingTime, double &processingTimeCalculation,
	                         double &processingTimeMoveRequest) const;
	void getTimeStatisticMin(double &processingTime, double &processingTimeCalculation,
	                         double &processingTimeMoveRequest) const;

	//
	// Rzadanie korekty w trybie nadzoru przez zewnetrzny gudider
	//
	class CorrectionRequest {
	  public:
		double deltaX;     // w radianach
		bool   directionX; // true -> R, false -> L

		double deltaY;     // w radianach
		bool   directionY; // true -> R, false -> L

		CorrectionRequest &operator=(const CorrectionRequest &v) = default;
		CorrectionRequest(const CorrectionRequest &v)            = default;
		CorrectionRequest()                                      = default;

		CorrectionRequest(const double X, const bool dirX, const double Y, const bool dirY)
		    : deltaX{X}, directionX{dirX}, deltaY{Y}, directionY{dirY} {};
	};

	//
	// Parametery rampy dla poszczegolnych osi
	//
	// - przyspieszenie
	double aX{0.0};
	double aY{0.0};
	// - hamowanie
	double dX{0.0};
	double dY{0.0};

	// - predkosci
	double vX{0.0};
	double vXOrg{0.0};
	double vY{0.0};
	double vYOrg{0.0};

	// Parametery rampy dla interpolacji liniowej w rad/s^2.
	double A{0.0};
	double D{0.0};

	//
	// Rozdzielczosci obu osi w krokach
	//
	// - w krokach
	long xResolution;
	long yResolution;
	// - w krokach jako double
	double xDResolution;
	double yDResolution;

	// Aktualna pozycja osi
	double xPosition{0.0};
	double yPosition{0.0};

	double    avgProcessingTime{0.0};
	long long avgProcessingTimeCount{0};

	long xPostionSteps;
	long yPostionSteps;

	long xPostionStepsRaw;
	long yPostionStepsRaw;

	long synchDeviceCount;

	//
	// Tryb przemieszczenia
	//
	bool absoluteMovment;

	// Bledy dla osi X i Y
	tlinsFullCoordinate devicePositionError;
	double              xError;
	double              yError;
	long                stopTimeout;

	bool timeRotationSign = false;

	bool fistIteration;

  public:
	void updateInternalPosition(double &x, double &y);
	void setInternalPosition(const double x, const double y, long &dX, long &dY);

	void readPositionInfo(long &xOut, long &xOutRaw, long &yOut, long &yOutRaw) const;

	Eigen::Matrix3d getAttitudeOptimal() const;

	void readState(Eigen::Matrix3d &attitude, tlinsSingleTarget &target, bool &isTarget, long &xOut, long &xOutRaw,
	               long &yOut, long &yOutRaw, ENGINE_MULTIPLE_MODE_FINALL &mulMode, ENGINE_STATE &state,
	               ENGINE_MODE &mode, const bool suspendRun = true);

	// Odczytuje biezacy cel
	void readCurrentTarget(tlinsSingleTarget &target, bool &isTarget);
	bool readCurrentTarget(tlinsSingleTarget &target);

	// Jesli sa oczekujace cele wymusza ustawienie nowego
	bool readCurrentTargetOrForceNew(tlinsSingleTarget &target);

	void restoreState(const Eigen::Matrix3d &attitude, const tlinsSingleTarget &target, const bool isTarget,
	                  const unsigned long xOut, const unsigned long yOut, const unsigned long xOutEnc,
	                  const unsigned long yOutEnc, const ENGINE_MULTIPLE_MODE_FINALL mulMode, const ENGINE_STATE state_,
	                  const ENGINE_MODE mode_, const bool revX, const bool revY);

  private:
	// Przetwarza pomiary na podsatwie ktorych generowana jest wynikowa
	// macierz transformacji
	std::unique_ptr<attitude ::tlinAttitudeProcess> attitudeProcess;

	// Optymalna macierz transformacji wyznaczona w procesie kalibracji
	Eigen::Matrix3d attitudeOptimal;
	Eigen::Matrix3d attitudeOptimalInverted;

	//
	// Parametery zwiazane z czestotliwoscia odswiezania
	//
	// Czestotliwosc aktualizacji pozycji w milisekundach
	unsigned long runFequency;
	unsigned long minRunFequency;

	// Pierwszy czas aktualizacji po zakonczeniu kalibracji lub zmianie celu
	unsigned long firstRunFrequency;
	bool          firstRunAfter;

	// Graniczne wartosci przy ktorych modyfikowane jest opoznienie
	// oraz generowany jest error
	unsigned long runFrequencyErrorCount; // Detekcja bledu po zwiekszeniu czasu

	unsigned long trackingDeviceSynchronisationFrequency;
	unsigned long trackingSpeedIncrease;

	struct PositionRequestInfo {
		// Przemieszczenie dla poszczegolnych osi w radianach
		double                                    delatMoveX;
		double                                    delatMoveY;
		std::chrono::duration<double, std::milli> moveTime;

		PositionRequestInfo(double delatMoveX_, double delatMoveY_,
		                    std::chrono::duration<double, std::milli> &moveTime_);

		PositionRequestInfo &operator=(const PositionRequestInfo &v) = default;
		PositionRequestInfo(const PositionRequestInfo &v)            = default;

		PositionRequestInfo();
		virtual ~PositionRequestInfo() = default;
	};

	//
	// ---
	//

	// Cel
	// Lista oczekujacych celi
	std::list<tlinsSingleTarget> pendingTargets;

	tlinsSingleTarget actualTarget;
	std::mutex        actualTargetMtx;
	std::atomic<bool> actualTargetIsSet;

	// Tryb sledzenia
	std::atomic<ENGINE_MODE> mode;

	// Status silnika
	ENGINE_STATE state;

	double calibrartionStartTime;

	tlinsStarApparentPlaceType apparentPlaceType;

	// Dane aktualnego pomiaru
	tlinsAstroObject mesermenttroAstroObject;

	// Identyfikator ostatniego rzadania przemieszczenia
	long              lastMoveRequestID;
	std::atomic<bool> lastMoveRequestConfirmed{false};
	std::atomic<bool> lastMoveRequestFinalIsError;
	std::atomic<int>  lastMoveRequestFinalErrorCode;
	std::string       lastMoveRequestFinalErrorDescription;

	// Callback potwierdzenia
	std::shared_ptr<tlinsMoveServerInterface::tlinsMoveRequestConfirmation> lastMoveRequestCb;

	// Licznik pomiaru czasu
	unsigned long intervalCount;
	double        avgInterval;

	// Zmienna warunkowa uzywana w celu oczekiwania na wynik przemieszczenia
	std::mutex              lastMoveRequestIdMutex;
	std::condition_variable lastMoveRequestIdCV;

	bool computeTargetForCurrentPosition(double &outRA, double &outDC, const bool notRotate = false);

  public:
	bool computeTargetForCurrentPosition(tlinsCoordinate &outRA, tlinsCoordinate &outDC);
	bool setTargetForCurrentPossition();

	bool isTrackingActive() const;

	enum class ReverseDevice { DEVICE_SETTINGS = 1, DEVICE_NO_REVERSE = 2, DEVICE_REVERSE = 3 };

	void               resetEngine(const ReverseDevice &reverseX = ReverseDevice::DEVICE_SETTINGS,
	                               const ReverseDevice &reverseY = ReverseDevice::DEVICE_SETTINGS);
	const ENGINE_STATE getState() const;
	const int          iterationCount() const;

	// Oczekiwanie na zakonczenie przemieszczenia
	void wait(const long lenth);
	void wait();
	void signal();

  private:
	void apparentPosition(const tlinsAstroObject                                       &aobject,
	                      std::map<tlinsStarApparentPlaceType, tlinsAstroObjectSimple> &apparentResult,
	                      tlinsAstroObjectSimple &result, const bool rotate = true, struct timeval *tv = nullptr) const;

	Eigen::Matrix3d apparentPositionBase(const tlinsAstroObject                                       &aobject,
	                      				std::map<tlinsStarApparentPlaceType, tlinsAstroObjectSimple> &apparentResult,
	                      				Eigen::Vector3d &result, struct timeval *tv = nullptr) const;

	// Domyslny tryb dzilania kontrolera. Pozycja skokow jest okreslana na  podstawie wyznacvzenia
	// Oczekiwanbej pozycji teleskopu i wykonania przemieszczenia
	void iterationStandard();
	bool testIterationStandard();

	// Tryb pracy w ktorym przemieszcenie nie jest generowane krokowo ale na zasadzie ustawienia predkosci
	void iterationSpeed();
	bool testIterationSpeed();

	void iterationGuider();
	bool testIterationGuider();

	void singleIteration();

	bool standardIterationWhenNoCorrections;

  private:
	void calculateDeviceCoordinate(const double alfa, const double beta, Eigen::Vector2d &newCoordinate);
	void calculateDeviceCoordinate(const Eigen::Vector3d &pos, const Eigen::Matrix3d &earthRot, Eigen::Vector2d &newCoordinate);

  public:
	void guiderRequestHandling(const long period, const AXIS axis, const DIRECTION moveLeft);
	void setGuiderConfiguration(const double ra, const double dec, const bool useRaForDec);
	void getGuiderConfiguration(double &ra, double &dec, bool &useRaForDec) const;

	void manualCorrectionRequestHandling(const DIRECTION raDir, double raCorrection, const DIRECTION decDir,
	                                     double decCorrection);

	void manualCorrectionStatus(DIRECTION &raDir, double &raCorrection, DIRECTION &decDir, double &decCorrection) const;

	void manualCorrectionRequestHandlingReset();
	void sync(const double ra, const double dec);

  private:
	void readPositionInfo(double &xout, double &yout, long &xlOut, long &xlOutRaw, long &ylOut, long &ylOutRaw);

	enum enforceMoveType { __NON__ = 0, __ABS__ = 1, __REL__ = 2 };

	void stopDevice();

	void sendMoveRequest(const long xRaw, const long yRaw, const long dX, const long dY);

	void sendSpeedRequest(const double xV, const bool xDir, const double yV, const bool yDir);

	void readConfiguration(long &maxX, long &maxY) const;

	// direction == true  - prawo
	// direction == false - lewo
	// Pozycja w radianach
	double deltaMinimumPosition(const double currPos, const double newPos, bool &direction) const;

	// Zmienna warunkowa i mutex kontrolujacy wejscie w petle odpowiedzialną ze sledzenie obiektu
	// Zmienna warunkowa kontroluje wejscie w petle glowna po kalibracji
	std::condition_variable standardRunCV;
	std::mutex              standardRunMtx;

	void waitStandardRun();
	void signalStandardRun();

	// Atomic kontrolujacy petle glowna
	std::atomic_bool standardRunEnd{false};

	// Przetwarzanie
	void standardRun();

	// Zmienna pozwalajaca zatrzymac wznowic prace watku sledzacego
	std::condition_variable standardRunCtrlCV;
	std::mutex              standardRunCtrlMtx;
	std::atomic_bool        standardRunCtrl{true};
	void                    waitStandardRunCtrl();
	void                    signalStandardRunCtrl();

	std::thread mainThread;

	// Wektor prekosci obrotowej i bledu ziemi
	Eigen::Vector3d erathRotationSpeedVector;
	Eigen::Vector3d erathRotationSpeedVectorError;

	// Parametery sledzenia w radianach na sekunde
	double trackSpeedRa{0.0};
	double trackSpeedDec{0.0};

	// Kontrola wadku odpowiedzialnego za sledzenie
	std::atomic<bool> trackIsActive;

	// Bazowy obiekt ktory jest aktualnie sledzony
	tlinsSingleTarget trackingBaseObject;

	void trackProcess();

	template <typename T, typename... Args> void reportPositionInfo(T v, Args... args);

	template <typename T, typename... Args> std::string buildContent(T v, Args... args) const;

	std::string buildContent(std::string v) const;

	template <typename T> std::string buildContent(T v) const
	{
		return std::to_string(v);
	}

  private:
	bool reversX{true};
	bool reversY{true};
	void reversePostion(long &lx, long &ly, long &rawLx, long &rawLy);
	void reverseSpeed(bool &vxDir, bool &vyDir);

  public:
	bool getReversX() const
	{
		return reversX;
	}

	bool getReversY() const
	{
		return reversY;
	}

	// Kontrola mechanizmu zlsedzenia
	// Jednostka to secundy luku na sekunde
	void trackingSet(const double ra, const double dec);
	bool trackingStatusSet(const bool enable);
	void trackingStatusGet(bool &status, double &ra, double &dec) const;

	void operator()();

	// Wlacza sledzenie z zadana predkoscia obiektu
	// Parametery to predkosc na sekunde
	// Trakowanie bedzie polegalo na tym efektywnie że z zadaną czestoliwością bedzie zadawana nowa pozycja
	void startCustomTracking(double raSpeed, double dcSpeed, unsigned long resolution);
	void stopCustomTracking();

	void suspendStandardRun();
	void reasumeStandardRun();

	void endStandardRun();

	// Pobranie i ustawienie macierzy transformacji

	// Ustawienie/pobranie czestotliwosci synchronizacji
	void                setRunFequency(const unsigned long m);
	const unsigned long getRunFequency(void) const;

	// Ustawienie trybu pracy silnika
	void setMode(const ENGINE_MODE mode);

	// Metoda ustawia obiekt docelowy który będzie śledzony przez teleskop
	// Wartosc predkosci przyspieszenia w radianach
	void setTarget(const tlinsAstroObject &t, const double v, const double a);
	void setTargetInternal(const tlinsAstroObject &t, const double v, const double a);

	bool getTarget(tlinsSingleTarget &target);

	// Metoda wymusza ustalenie nowego celu jsli jest jakis
	void getNextTarget();

	// Rejestracja pomiaru pozycji
	void registerMeserment(const tlinsFullCoordinate &input, const tlinsFullCoordinate &inputErr,
	                       const tlinsAstroObject &reference, const double w);

	// Rejestracja pomiaru pozycji
	void registerMeserment(const tlinsFullCoordinate &inputErr, const tlinsAstroObject &reference, const double w);

	void closeCalibration();

	// Konstruktor/destruktor klasy
	tlinsAstroEngine(std::shared_ptr<tlinsMoveServerInterface> &srv, tlinsAstroEnginConfiguration &cfg);
	virtual ~tlinsAstroEngine();
};

//
// --- Servera GRPC dla silnika Astro
//
class tlinsRpcAstroEngine final : public tlins::tlinsRpcAstroService::Service {
  private:
	tlinsAstroEngine &engine;

	// Odroczony obiekt referencyjny
	tlinsAstroObject    deferedReferenceObject;
	tlinsFullCoordinate deferedReferenceObjectInputErr;
	double              deferedReferenceObjectWeight;
	bool                isReferenceObjectDefered{false};
	bool                referenceObjectDeferedConfirmed{false};

  public:
	grpc::Status getCalibrationState(grpc::ServerContext *context, const tlins::Void *request,
	                                 tlins::tlinsEngineCalibrarionStateInfo *response);

	grpc::Status getState(grpc::ServerContext *context, const tlins::tlinsBoolValue *request,
	                      tlins::tlinsEngineStateInfo *response);

	grpc::Status restoreState(grpc::ServerContext *context, const tlins::tlinsEngineState *request,
	                          tlins::tlinsRpcStatus *response);

	grpc::Status startTracking(grpc::ServerContext *context, const tlins::Void *request,
	                           tlins::tlinsRpcStatus *response);

	grpc::Status stopTracking(grpc::ServerContext *context, const tlins::Void *request,
	                          tlins::tlinsRpcStatus *response);

	// Ustawienie obiektu docelowego
	grpc::Status setTarget(grpc::ServerContext *context, const tlins::tlinsTarget *request,
	                       tlins::tlinsRpcStatus *response);

	// Ustawienie obiektu docelowego
	grpc::Status getTarget(grpc::ServerContext *context, const tlins::Void *request,
	                       tlins::tlinsCurrentTargetInfo *response);

	// Rejestracja pomiaru
	grpc::Status registerMeserment(grpc::ServerContext *context, const tlins::tlinsMeserment *request,
	                               tlins::tlinsRpcStatus *response);

	//
	// Rejestracja pomiaru odroczonego
	//
	grpc::Status registerMesermentDefered(grpc::ServerContext *context, const tlins::tlinsMeserment *request,
	                                      tlins::tlinsRpcStatus *response);

	// Potwierdzenie odroczonego obiektu referencyjnego - para do registerMesermentDefered()
	grpc::Status confirmDeferedMeserment(grpc::ServerContext *context, const tlins::Void *request,
	                                     tlins::tlinsRpcStatus *response);

	// Zamkniecie kalibracji
	grpc::Status closeCalibration(grpc::ServerContext *context, const tlins::Void *request,
	                              tlins::tlinsRpcStatus *response);

	// Parametery srodfowiska
	grpc::Status setEnvironment(grpc::ServerContext *context, const tlins::tlinsEnvironment *request,
	                            tlins::tlinsRpcStatus *response);

	// Parametery srodfowiska
	grpc::Status setIERSInfo(grpc::ServerContext *context, const tlins::tlinsIERSList *request,
	                         tlins::tlinsRpcStatus *response);

	// Ustawienie miesca obserwacji
	grpc::Status setObservationPlace(grpc::ServerContext *context, const tlins::tlinsObservationPlace *request,
	                                 tlins::tlinsRpcStatus *response);

	grpc::Status setMode(grpc::ServerContext *context, const tlins::tlinsEngineMode *request,
	                     tlins::tlinsRpcStatus *response);

	grpc::Status resetCalibration(grpc::ServerContext *context, const tlins::tlinsResetCalibration *request,
	                              tlins::tlinsRpcStatus *response);

	grpc::Status setTargetForCurrentPosition(grpc::ServerContext *context, const tlins::Void *request,
	                                         tlins::tlinsRpcStatus *response);

	// --------------
	grpc::Status setTracking(grpc::ServerContext *context, const tlins::tlinsTracking *request,
	                         tlins::tlinsRpcStatus *response);
	grpc::Status setTrackingState(grpc::ServerContext *context, const tlins::tlinsBoolValue *request,
	                              tlins::tlinsRpcStatus *response);
	grpc::Status getTrackingState(grpc::ServerContext *context, const tlins::Void *request,
	                              tlins::tlinsTrackingStatus *response);

	grpc::Status sync(grpc::ServerContext *context, const tlins::tlinsSync *request, tlins::tlinsRpcStatus *response);

	grpc::Status guideNorth(grpc::ServerContext *context, const tlins::tlinsIntValue *request,
	                        tlins::tlinsGuiderStatus *response);
	grpc::Status guideSounth(grpc::ServerContext *context, const tlins::tlinsIntValue *request,
	                         tlins::tlinsGuiderStatus *response);
	grpc::Status guideEst(grpc::ServerContext *context, const tlins::tlinsIntValue *request,
	                      tlins::tlinsGuiderStatus *response);
	grpc::Status guideWest(grpc::ServerContext *context, const tlins::tlinsIntValue *request,
	                       tlins::tlinsGuiderStatus *response);

	grpc::Status guiderRatioSet(grpc::ServerContext *context, const tlins::tlinsGuiderConfigSet *request,
	                            tlins::tlinsRpcStatus *response);

	grpc::Status guiderRatioGet(grpc::ServerContext *context, const tlins::Void *request,
	                            tlins::tlinsGuiderConfigStatus *response);

	grpc::Status manualCorrection(grpc::ServerContext *context, const tlins::tlinsManualCorrection *request,
	                              tlins::tlinsRpcStatus *response);

	grpc::Status manualCorrectionReset(grpc::ServerContext *context, const tlins::Void *request,
	                                   tlins::tlinsRpcStatus *response);

	grpc::Status manualCorrectionGet(grpc::ServerContext *context, const tlins::Void *request,
	                                 tlins::tlinsManualCorrectionStatus *response);

	tlinsRpcAstroEngine(tlinsAstroEngine &engine_);
	virtual ~tlinsRpcAstroEngine() = default;
};

#endif
