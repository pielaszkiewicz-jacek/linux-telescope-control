#ifndef __tlinsSerialServer_hpp__
#define __tlinsSerialServer_hpp__

#include <device.grpc.pb.h>
#include <tlinsSerialDevice.hpp>
#include <tlinsSerialDeviceException.hpp>
#include <tlinsSerialGpio.hpp>

#include <Eigen/Eigenvalues>
#include <Eigen/Geometry>

#include <condition_variable>
#include <memory>
#include <mutex>
#include <thread>
#include <tuple>

/*
 * Klasa servera
 */

class tlinsRpcConfigurationServer;
class tlinsRpcMoveControlServer;

/*
 * Informacja o statusie przetwarzania
 */
struct tlinsSerialCompletation {
	int         status;
	std::string axis;

	tlinsSerialCompletation &operator=(const tlinsSerialCompletation &v) = default;
	tlinsSerialCompletation(const tlinsSerialCompletation &v)            = default;
	tlinsSerialCompletation()                                            = default;
	tlinsSerialCompletation(const int status_, const std::string &axis_) : status{status_}, axis{axis_} {};
	~tlinsSerialCompletation() = default;
};

/*
 * Watek przetwarzajacy zlecenia
 */

enum class tlinsSerialOperation {
	OPERATION_NOTHING       = 0, // Nic sie nie dzieje
	OPERATION_MOVE_POSITION = 1, // Wymaga potwierdzenia
	OPERATION_MOVE_SPEED    = 2, // Nie wymaga potwierdzenia
	OPERATION_MOVE_LINEAR   = 3, // Aproksymacja liniowa
	OPERATION_MOVE_STOP     = 4, // Zatrzymanie wskazanej osi
	OPERATION_ABORT         = 5, // Awaryjne zatrzymanie
	OPERATION_END           = 6  // Zatrzymanie watku
};

enum class tlinsServerDirectionInfo { IDLE = 0, LEFT = 1, RIGHT = 2, ANY = 3 };

enum class tlinsSerialRequestStatusResult {
	STATUS_NONE                = 1,
	STATUS_WATING              = 0,
	STATUS_COMPLETED_SUCCESS   = 1,
	STATUS_REJECTED            = 2,
	STATUS_COMPLETED_INCMPLETE = 3, // Nie udalo zarejestrowac sie w pelni zlecenia.
	                                // Bedzie obsluzone czesciowo
	STATUS_ERROR = 4
};

enum class tlinsSerialServerMode {
	// Tryb pracy interpolowany. Synchronizowane sa wszystkie osie
	// Dostepe typy operacji: INTERPOLATED, POSITION, SPEED oraz STOP
	// Inne typy rzadan beda odrzucae.
	MODE_SYNCHRONISED = 1,

	// Tryb separowany
	// Dostepe typy operacji: POSITION, SPEED oraz STOP. Inne typy rzadan beda odrzucae.
	MODE_SEPARATE_AXIS = 2
};

//
// Opis limitu pozycji
//
struct DeviceLimitDefinition {

	EIGEN_MAKE_ALIGNED_OPERATOR_NEW

	std::mutex                                                mtx;
	std::vector<std::tuple<Eigen::Vector3d, Eigen::Vector3d>> limits;

	void addLimit(const Eigen::Vector3d &l, const Eigen::Vector3d &r)
	{
		std::unique_lock<std::mutex> lock(mtx);
		limits.emplace_back(std::tuple<Eigen::Vector3d, Eigen::Vector3d>{l, r});
	};

	std::vector<std::tuple<Eigen::Vector3d, Eigen::Vector3d>> getLimits()
	{
		std::unique_lock<std::mutex> lock(mtx);
		return limits;
	};

	DeviceLimitDefinition &operator=(const DeviceLimitDefinition &v) = default;

	DeviceLimitDefinition(const DeviceLimitDefinition &v) = default;
	DeviceLimitDefinition()                               = default;
	virtual ~DeviceLimitDefinition()                      = default;
};

// Definicja parameterow urzdzenia branych podczas wyznaczania obszaru niedostepnego dla tubusa
struct DeviceLimitDeviceDefinition {
	// Parametery d1 i d2 zwiazane z konfiguracja montazu i przechowywane są w konfiguracji
	double h;  // Przesuniecie wzdluz osi Z podstawy monatazu
	double r1; // Pierwsza polowa tubusa
	double r2; // druga polowa tubusa polowa tubusa
	double dx; // Przesuniecie dlaosi X
	double dz; // Przesuniecie dla osi Z

	std::vector<std::pair<std::string, double>> deviceMountAngles;

	void addAngle(const std::string &a, const double val)
	{
		deviceMountAngles.push_back(std::pair<std::string, double>{a, val});
	}

	// Parametr dlugosci tubusa i odleglosci jednego konca tubusa od osi oraz srednicy tubusa sa przekjazywane sa z
	// zewnatrz lub konfigurane w pliuku
	long frequency; // W milisekundach


	// Domyslny konstruktory i destruktor
	DeviceLimitDeviceDefinition(const double h_, const double r1_, const double r2_, const double dx_, const double dz_,
	                            const long frequency_)
	    : h{h_}, r1{r1_}, r2{r2_}, dx{dx_}, dz{dz_}, frequency{frequency_} {};

	DeviceLimitDeviceDefinition &operator=(const DeviceLimitDeviceDefinition &v) = default;
	// Domyslny konstruktory i destruktor
	DeviceLimitDeviceDefinition(const DeviceLimitDeviceDefinition &v) = default;
	DeviceLimitDeviceDefinition()                                     = default;
	virtual ~DeviceLimitDeviceDefinition()                            = default;
};

class MainDeviceMoreRequestsThread;

class MainDeviveLimit {
  public:
	EIGEN_MAKE_ALIGNED_OPERATOR_NEW

  private:
	std::mutex limitMutex;

	// Mapa zawierajaca informacje o zarejestrowanych potwierdzeniach
	std::mutex            confirmationsMtx;
	std::set<std::string> confirmations;

	// Ustawienia limitu
	DeviceLimitDefinition deviceLimitDefinition;

	// Konfiguracja urzadzenia zwiazana z limitem
	DeviceLimitDeviceDefinition deviceLimitConfiguration;

	// Macierz transformacji
	Eigen::Matrix3d deviceTransformationMatrix;
	Eigen::Matrix3d deviceTransformationMatrixInverted;

	// Watek sledzacy czy tubus nie dotarl do limitu pozycji
	std::atomic<bool> enableTrackPosition{false};

	// Watek sledzacy limit.
	// W sytuacji gdy monitirowanie pozycji jest wlaczone watek bedzie odpowiedzialny za zatrzymanie urzadzenia w celu
	// unikniecia kolizji.
	std::thread threadTrackPositionLimit;

	std::condition_variable threadTrackPositionLimitCtrlCv;
	std::mutex              threadTrackPositionLimitCtrlMtx;

	std::atomic<bool> endTrackPositionLimit{false}; // Znacznik konca pracy watku sledzacego limity

	// Urzadzenie glowne ktore bedzie monitorowane
	std::shared_ptr<tlinsSerialMainDevice>        mainDevice;
	std::shared_ptr<MainDeviceMoreRequestsThread> mainDeviceThread;

  public:
	void registerConfirmation(const std::string &id);

	void addLimitDefinition(const Eigen::Vector3d &v1, const Eigen::Vector3d &v2);

	// Metoda wyzancza pozycje dla zadnych kontow osi glownych
	std::pair<Eigen::Vector3d, Eigen::Vector3d> positionLimitGetPosition(const double alfa, const double beta);

	// Metoda bada czy wysapi kolizja podczas przemieszczenia do zadanej pozycji
	// Punkt startowy odczytywany jest z urzadzenia
	// Metoda bedzie uzywana w momencie gdy:
	bool checkColision(const Eigen::Vector3d &position);

	// Metoda sprawdza czy sciezka miedzy pozycjami jest dozwolona. Czy nie bedzie sytuacji ze zostanie osiagniety limit.
	bool checkPath(const Eigen::Vector2d &start, const Eigen::Vector2d &end, const double deltaX, const double deltaY);

	void startMonitoring(void);
	void stopMonitoring(void);

	void endTrack(void);
	void join();

	explicit MainDeviveLimit(const std::shared_ptr<MainDeviceMoreRequestsThread> &mainDeviceThread_,
	                         const DeviceLimitDeviceDefinition                   &limitConf);
	MainDeviveLimit() = default;
	virtual ~MainDeviveLimit();
};


class MainDeviveLimitManager {
  private:
	std::map<std::string, std::shared_ptr<MainDeviveLimit>> devicesMap;

	MainDeviveLimitManager() = default;

  public:
	// Metoda na podstawie konfiguracji tworzy obiekty urzadzen
	void addDevicesLimit(const std::string &devName, const std::shared_ptr<MainDeviveLimit> &devLim);

	// Zwraca kon urzadzenia
	std::map<std::string, std::shared_ptr<MainDeviveLimit>>::iterator find(const std::string &name);
	std::map<std::string, std::shared_ptr<MainDeviveLimit>>::iterator begin();
	std::map<std::string, std::shared_ptr<MainDeviveLimit>>::iterator end();

  public:
	static MainDeviveLimitManager &getInstance();
};


/*
 * Watek serwera
 * Pracuje w dwoch zasadniczych trybach. 1 Synchroniczny
 */
class MainDeviceMoreRequestsThread {
  private:
	//
	// -- Kolejki oczekujacych rzadan
	//    Rzadanie typu abort bedzie zawsze wedrowalo na poczatek kolejki wysokopiorytetowej
	//
	// W sytuacji gdy kolejka jest oprozniana
	// Beda wysylane potwierdzenia.

	// Kolejka wykorzystywana jest w trybie synchronicznym gdy jednoczesnie zadawane jest przemieszczenie
	// dla wielu osi
	tlinsSerialQueue<tlinsSerialDeviceMoveRequest> requestQueue;

	// Kolejki uzywane w trybie indywidualnym gdy przemieszczenie zadawane jest niezalnie
	// dla poszczegolnych osi. Kazda os zewiera referencje na kompletny request
	// przy czym dla danej osi bedzie przetwarzany odpawiadajaca skladowa
	// rzadania.
	std::map<std::string, tlinsSerialQueue<tlinsSerialDeviceMoveRequest>> axisRequests;

	// Kolejka wysokiego piorytetu
	// Rzadania z tej kolejki sa obslugiwane jako pierwsze.
	// Po oproznieniu kolejki beda przetwarzane standardowe rzadania.
	// Kolejka obsluguje rzadania w obu trybach pracy
	// Zawiera rzadania awaryjnego zatrzymania lub instrukcje kontrolne
	tlinsSerialQueue<tlinsSerialDeviceMoveRequest> priorityRequestQueue;

	// Mapa zawiera informacje o aktualnym kierunku obrotu danej osi.
	// Mapa jest wykorzystywana w celu wygenerowania rzadania zatrzymania
	std::map<std::string, tlinsServerDirectionInfo> directions;

	// Mqpa identyfikatorow. Dla kazdej osoi zawie ID potwierdzenia ktore jest oczekiwane
	std::map<std::string, unsigned long> reqIdsMap;

	// Referencja na urzadzenie glowne obslugiwane przez watek
	std::shared_ptr<tlinsSerialMainDevice> mainDevice;

	// Tryb pracy serwera
	tlinsSerialServerMode serverMode;

	// Glwny mutex synchronizujacy dostep do servera
	std::recursive_mutex serverMtx;

	std::mutex              serverMtxCv;
	std::condition_variable serverCv;

	// Znacznik konca watku
	std::atomic<bool> end;

	//
	// Struktura przechowuje informacje o statusie rzadania
	//
	struct RequestStatusInfo {
		// 1. LIcznik calkowietek liczby potwierdzen ktora jest wymagana
		int confirmationCount{0};

		// 2. Szczegolowa informacja o statusie zakonczenia kazdej ze skladowej rzadania
		std::map<std::string, tlinsSerialRequestStatusResult> requestDetailStatus;

		// 3. Wksanik na request
		std::shared_ptr<tlinsSerialDeviceMoveRequest> request;

		std::map<std::string, bool> axisConfStatus;

		bool isFullyConfirmed{false};

		void reset()
		{
			requestDetailStatus.clear();
			axisConfStatus.clear();
			isFullyConfirmed  = false;
			confirmationCount = 0;
		}

		void addAxis(const std::string &a)
		{
			if (axisConfStatus.count(a) == 0) {
				confirmationCount++;
				axisConfStatus[a]      = false;
				requestDetailStatus[a] = tlinsSerialRequestStatusResult::STATUS_WATING;
			}
		}

		void confirm(const std::string &a, const tlinsSerialRequestStatusResult s)
		{
			if (axisConfStatus.count(a) != 0 && !axisConfStatus[a]) {
				confirmationCount--;
				axisConfStatus[a]      = true;
				requestDetailStatus[a] = s;

				if (confirmationCount <= 0) {
					isFullyConfirmed = true;
				}
			}
		}

		bool isConfirmed(const std::string &a)
		{
			if (axisConfStatus.count(a) == 0) {
				return true;
			}
			return axisConfStatus[a];
		}

		bool isConfirmed() const
		{
			return isFullyConfirmed;
		}

		RequestStatusInfo &operator=(const RequestStatusInfo &v) = default;
		RequestStatusInfo(const RequestStatusInfo &v)            = default;
		RequestStatusInfo()                                      = default;

		explicit RequestStatusInfo(const std::shared_ptr<tlinsSerialDeviceMoveRequest> &req) : request{req}
		{
			// Dodanioe osi
			for (auto iter : *req) {
				std::string a = iter.first;
				addAxis(a);
			}
		};

		virtual ~RequestStatusInfo() = default;
	};

	// Pola sluza do rejestrowania i przekazywania do klienta informacji o statusie
	// zakonczenia operacji
	// 1. Informacja o statusie rzadania
	std::map<unsigned long, std::shared_ptr<RequestStatusInfo>> requestStatusInfo;

	// Mapowanie osi na informacje o statusie rzadanias.
	// Zawiera informacje tylko o aktualnie przetwarzanych rzadaniach
	std::map<std::string, std::shared_ptr<RequestStatusInfo>> axisToRequestStatus;

	// Mapa zawierajaca informacje czy dana os wymaga potwierdzenia
	std::map<std::string, bool> statusNeeded;

	std::map<std::string, bool> statusNeededStart;

	// Maksymalny czas oczekiwania na zmiennej warunkowej w milisekundach
	long waitTimeoutMax;

  private:
	//
	// callback
	//
	void confirmMove(const std::vector<std::pair<std::string, tlinsSerialMainDevice::ConfirmationType>> &data);
	void confirmMove(const std::vector<std::pair<std::string, tlinsSerialMainDevice::ConfirmationInfo>> &data);

	// Metoda bada czy nalezy zakonczyc dzialanie watku
	const bool isEnd();

	// Metoda pobiera kolejne rzadanie do przetwarzania
	// Wolana jest w sytuacji gdy serwer otrzyma informacje o nowym rzadaniu
	// lub urzadzenie osiagnelo pozycje.
	void setNextRequest();

	// Metoda przekazuje do klienmta informacje o statusie zakonczonego rzadania.
	void confirmRequest(const long                           id,
	                    const tlinsSerialRequestStatusResult stat = tlinsSerialRequestStatusResult::STATUS_NONE);

	void confirmRequest(const std::shared_ptr<tlinsSerialDeviceMoveRequest> &req,
	                    const tlinsSerialRequestStatusResult stat = tlinsSerialRequestStatusResult::STATUS_NONE);

	//
	// Metoda odpowiedzialna jest za zatrzymanie wskazanej osi kontrolera
	// Zatrzymanie standardowe
	//
	void stopSelectedAxis(const std::string &a, const std::shared_ptr<tlinsSerialDeviceMoveRequest> &req);

	// Metoda tworzy rzadanie typy CTRL_STOP dla wskazanych osi
	std::shared_ptr<tlinsSerialDeviceMoveRequest> createCtrlStopRequest(const std::vector<std::string> &axies);


	// Metoda przetwarza rzadanie typu predkosc
	void speedSelectAxis(const std::string &a, const std::shared_ptr<tlinsSerialDeviceMoveRequest> &req);

	void positionSelectAxis(const std::string &a, const std::shared_ptr<tlinsSerialDeviceMoveRequest> &req);

	// Metoda przetwarza kolejke rzadan w trybie nie synchronicznym
	void setNextStandardRequestAxis();

	void setNextSynchronusRequest();

	// Metoda przetwarza kolejke piorytetowa
	bool setNextRequestPriorityQueue();

	// Rzadanie zatrzymania w trybie synchronicznym
	void stopRequestSynch(const std::shared_ptr<tlinsSerialDeviceMoveRequest> &req);

	// Reqularne przemieszczenie w trybie synchronicznym
	void moveRequestSynch(const std::shared_ptr<tlinsSerialDeviceMoveRequest> &req);

  public:
	std::shared_ptr<tlinsSerialMainDevice> getMainDevice()
	{
		return mainDevice;
	};

	// Metoda wolana jest w celu potwierdzenia ze naped osiagnol zadana pozycje
	void confirmPosition(const std::vector<std::pair<std::string, tlinsSerialRequestStatusResult>> &axis,
	                     const bool                                                                 noNoti);

	// Metoda ustawia tryb pracy serwera
	// ++
	void setServerMode(const tlinsSerialServerMode mode);

	const tlinsSerialServerMode getServerMode() const
	{
		return serverMode;
	}

	// Wstawienie nowego rzadania
	// ++
	void enqueueRequest(const std::shared_ptr<tlinsSerialDeviceMoveRequest> &req);

	// Operator - implementuje petle glowna watka
	void operator()();

  public:
	// Wyslanie sygnalu do watku
	void signalThread();

	// Przekazanie potwierdzenia
	void requestCompleted(const tlinsSerialCompletation &status);

  private:
	std::string mainDeviceName;

	// Watek przetwarzajacy kolejke rzadania
	std::unique_ptr<std::thread> th;

  public:
	// Wstawienie rzadania
	void enqueRequest(const std::shared_ptr<tlinsSerialDeviceMoveRequest> &req);

	// Oczekiwanie
	void join();

	// Metoda rozlacza petle glowa watku
	void endThread();

	explicit MainDeviceMoreRequestsThread(const std::shared_ptr<tlinsSerialMainDevice> &mainDevice_);
	virtual ~MainDeviceMoreRequestsThread();
};

//
// ---------------------------------------------------------------------
//

class tlinsSerialServer {
  private:
	// Mapa watkow  roboczych obslugujacych
	std::map<std::string, std::shared_ptr<MainDeviceMoreRequestsThread>> serverThreads;

	// Mapa managerow odpowiuedzialnych za sledzenie czy urzadzenie znajduje się w lub poza obszarem zabronionym
	std::map<std::string, std::shared_ptr<MainDeviveLimit>> serverLimits;

	std::mutex mtx;

  public:
	// Rejestracja nowego urzadzenia
	// Metoda zwraca true gdy rejestracja sie powiodla
	// oraz false w sytuacji gdy mamy duplikat
	bool registerDevice(const std::string &devName, const std::shared_ptr<tlinsSerialMainDevice> &dev);

	bool registerDeviceLimit(const std::string &devName, const std::shared_ptr<tlinsSerialMainDevice> &dev);

	// Wstawienie rzadania do wskazanego urzadzenia
	void enqueRequest(const std::string &devName, const std::shared_ptr<tlinsSerialDeviceMoveRequest> &req);

	// Wstawienie rzadania do wskazanego urzadzenia
	void setServerMode(const std::string &devName, const tlinsSerialServerMode mode);

	bool colistionsDetectionTest(const std::string &devName, const Eigen::Vector3d &position);
	void enableColistionsDetection(const std::string &devName);
	void disableColistionsDetection(const std::string &devName);
	void addColistionDefinition(const std::string &devName, const Eigen::Vector3d &v1, const Eigen::Vector3d &v2);
	void colistionsDetectionRegisterConfirmation(const std::string &devName, const std::string &id);

	tlinsSerialServerMode getServerMode(const std::string &devName);

	// Czeka na zkonczenie wszystkich zarejestrowanych watkow
	void end();

  public:
	// Konstruktor i destruktor klasy
	tlinsSerialServer() = default;
	virtual ~tlinsSerialServer();
};

//
// ---------------------------------------------------------------------
// ---------------------------------------------------------------------
// ---------------------------------------------------------------------
//

// Typy potwierdzen
enum class tlinsSerialConfirmationType {
	// Potwierdzenie przemieszczenia
	CONF_MOVE_REQUEST = 0
};

class tlinsSerialConfirmationQueue {
  private:
	// Kolejak potwierdzen
	std::list<std::unique_ptr<tlins::tlinsRpcConfirmationStatus>> queue;

	std::condition_variable cv;
	std::mutex              mtx;

	std::atomic<bool> end{false};
	int               maxLen;

  public:
	void enqueue(std::unique_ptr<tlins::tlinsRpcConfirmationStatus> &conf);
	bool dequeue(std::unique_ptr<tlins::tlinsRpcConfirmationStatus> &conf);
	void setEnd();

	// Konstruktor i destruktor klasy
	explicit tlinsSerialConfirmationQueue(const int maxLen_ = 100);
	virtual ~tlinsSerialConfirmationQueue() = default;
};

//
// Menadzer potwierdzen. Przechowuje kolejkii potwierdzen
//
class tlinsSerialServerConfirmationManager {
  private:
	// Mapa potwierdzen
	std::recursive_mutex                                mtx;
	std::map<std::string, tlinsSerialConfirmationQueue> streams;

	// Generator identyfikatyorow
	std::mutex idMtx;
	long       id{0L};

  private:
	// Prywatny konstruktor
	tlinsSerialServerConfirmationManager() = default;
	std::string getId();

  public:
	static tlinsSerialServerConfirmationManager &getInstance();

	std::string newConfInstance();
	bool        enqueue(const std::string &id, std::unique_ptr<tlins::tlinsRpcConfirmationStatus> &conf);

	bool dequeue(const std::string &id, std::unique_ptr<tlins::tlinsRpcConfirmationStatus> &conf);

	bool exists(const std::string &id);

	bool stop(const std::string &id);

	virtual ~tlinsSerialServerConfirmationManager() = default;
};

//
// ---------------------------------------------------------------------
// ---------------------------------------------------------------------
// ---------------------------------------------------------------------
//
enum class tlinsServerErrorCodes {
	SUCCESS                 = 0,
	WARNING                 = -1,
	ERROR                   = -2,
	INVALID_PARAMETER       = -3,
	INVALID_DEVICE          = -4,
	DEVICE_ERROR            = -5,
	ERROR_INVALID_PARAMETER = -6,
	MODBUS_ERROR            = -7,
	MISING_CONFIGURATION    = -8,
	ENQUEUE_REQUEST         = -9,
	INVALID_SERVER_MODE     = -10
};

class tlinsRpcConfirmationServer final : public tlins::tlinsRpcConfirmationService::Service {
  public:
	grpc::Status confirmation(grpc::ServerContext *context, const tlins::tlinsConfirmationHandler *request,
	                          grpc::ServerWriter<tlins::tlinsRpcConfirmationStatus> *writer);
};

class tlinsRpcMoveControlServer final : public tlins::tlinsRpcService::Service {
  private:
	tlinsSerialServer &parent;

  public:
	grpc::Status createConfirmation(grpc::ServerContext *context, const tlins::Void *request,
	                                tlins::tlinsConfirmationHandlerResult *response);

	grpc::Status setMoveRequest(grpc::ServerContext *context, const tlins::tlinsRpcMoveRequest *request,
	                            tlins::tlinsRpcMoveStatus *response);

	grpc::Status setMoveMode(grpc::ServerContext *context, const tlins::tlinsRpcDeviceMode *request,
	                         tlins::tlinsRpcStatus *response);

	grpc::Status getMoveMode(grpc::ServerContext *context, const tlins::tlinsStringValue *request,
	                         tlins::tlinsRpcDeviceModeStatus *response);

	grpc::Status getPosition(grpc::ServerContext *context, const tlins::tlinsRpcMainDevicesName *request,
	                         tlins::tlinsRpcPositionInfo *response);

	grpc::Status setPosition(grpc::ServerContext *context, const tlins::tlinsRpcPosition *request,
	                         tlins::tlinsRpcStatus *response);

	grpc::Status getConfiguration(grpc::ServerContext *context, const tlins::tlinsRpcMainDevicesName *request,
	                              tlins::tlinsRpcDeviceConfiguration *response);

	grpc::Status setDateTime(grpc::ServerContext *context, const tlins::tlinsRpcDateTime *request,
	                         tlins::tlinsRpcStatus *response);


	//
	// Obsluga limitow polozenia
	//
	grpc::Status colistionsDetectionConfirmationCreate(grpc::ServerContext                   *context,
	                                                   const tlins::tlinsStringValue         *request,
	                                                   tlins::tlinsConfirmationHandlerResult *response);
	grpc::Status colistionsDetectionSetLimits(grpc::ServerContext *context, const tlins::tlinsLimits *request,
	                                          tlins::tlinsRpcStatus *response);
	grpc::Status colistionsDetectionGetLimits(grpc::ServerContext *context, const tlins::Void *request,
	                                          tlins::tlinsLimits *response);
	grpc::Status colistionsDetectionTest(grpc::ServerContext *context, const tlins::tlinsTestLimit *request,
	                                     tlins::tlinsTestLimitResult *response);
	grpc::Status colistionsDetectionEnable(grpc::ServerContext *context, const tlins::tlinsStringValue *request,
	                                       tlins::tlinsRpcStatus *response);
	grpc::Status colistionsDetectionDisable(grpc::ServerContext *context, const tlins::tlinsStringValue *request,
	                                        tlins::tlinsRpcStatus *response);

	explicit tlinsRpcMoveControlServer(tlinsSerialServer &parent_);
};

#endif
