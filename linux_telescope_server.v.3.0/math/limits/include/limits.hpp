#ifndef __limits_hpp__
#define __limits_hpp__

#include <Eigen/Eigenvalues>
#include <Eigen/Geometry>

#include <tuple>
#include <utility>
#include <vector>

#include "tlinAttitudeUtilsClass.hpp"
#include "tlins_math.hpp"

namespace limits
{

/*
   Klasa opisuje montaz jako:
   - walec pionowy bedacy baza do ktorej pzymocowane sa nogi
   - walce uksne ustawione pod katem w ilosci n
 */

class tlinsLimitsMount {
  public:
	EIGEN_MAKE_ALIGNED_OPERATOR_NEW

  private:
	int             legs{3};                      // Liczba nog montazu
	double          legRadius{30.0};              // Promien nogi montazu
	Eigen::Vector3d legsZOffset{0.0, 0.0, -20.0}; // Przesuniecie nog montazu
	double          legsSartAngle{0.0}; // Kat obrotu w okol osi Z pierwszej nogi monatazu. Wyznaczany obserwacyjnie
	double          legsAngle{tlinsMath::PI / 3.0 * 2.0}; // Kat pod ktorym pochylona jest noga montazu
	double          baseRadius{75.0};                     // Promien glonej kolumny montazu
	double          baseLength{300.0};
	double          tubeRadius{110.0}; // Srednica tubusa

  public:
	enum class colistionType { COLISTION_NONE = 0, COLISTION_BASE = 1, COLISTION_LEG = 2 };

	// Metoda sprawdza czy jest kolizja
	std::pair<colistionType, int> checkColistion(const Eigen::Vector3d &pos);

	// Detekcja kolizji przy przejzdzie miedzy dwoma pozycjami
	std::vector<std::pair<tlinsLimitsMount::colistionType, int>>
	detectColistion(const Eigen::Vector3d &s, const Eigen::Vector3d &e, const double delta);

	// Wyznaczenie drogi miedzy dwoma pozycjami aby uniknac kolizji.
	// Metoda wyznacza dwa dodatkowe punkty posrendnie
	// Parameter delta oznacza o ile bedziemy podnosic tubus do gory.
	std::vector<Eigen::Vector3d> makePathWithoutCollision(const Eigen::Vector3d &s, const Eigen::Vector3d &e,
	                                                      const double delta, const double deltaMove, const int n);

	tlinsLimitsMount &operator=(const tlinsLimitsMount &v) = default;
	tlinsLimitsMount(const tlinsLimitsMount &v)            = default;

	// Konstruktor klasy
	tlinsLimitsMount(const int legs_, const double legRadius_, const Eigen::Vector3d &legsZOffset_,
	                 const double legsSartAngle_, const double legsAngle_, const double baseRadius_,
	                 const double baseLength_);

	virtual ~tlinsLimitsMount() = default;
};


struct tlinsLimitsDeviceInfo {
	double alfa  = 0.0;
	double a     = 0.0;
	double d     = 0.0;
	double sigma = 0.0;

	tlinsLimitsDeviceInfo &operator=(const tlinsLimitsDeviceInfo &v) = default;
	tlinsLimitsDeviceInfo()                                          = default;
	tlinsLimitsDeviceInfo(const tlinsLimitsDeviceInfo &v)            = default;
	tlinsLimitsDeviceInfo(const double alfa_, const double a_, const double d_, const double sigma_)
	    : alfa{alfa_}, a{a_}, d{d_}, sigma{sigma_} {};
	~tlinsLimitsDeviceInfo() = default;
};

class tlinsLimitsMath {
  public:
	EIGEN_MAKE_ALIGNED_OPERATOR_NEW

  public:
	// Metoda oblicza odleglosc katową dwóch prostych które przechodzą przez
	// poczatek układy współrzednych i punkty p1 i p2
	static double straightLinesAngleDistance(const Eigen::Vector3d &p1, const Eigen::Vector3d &p2);

	// Metoda wyznacza wspolrzedne konca urzadzenia na podstawie przekazanej tablicy danych
	/*
	        # Ogniwo | alfa[i]     | a[i] | d[i]   | sigma[i]
	        # -------+-------------+------+--------+-------------
	        # 1      | -1 * pi / 2 |  0   | d(1)   | sigma(1)       Os RA d(1) odlegosc przegubu od podstawy
	        # 2      |  1 * pi / 2 |  0   | d(2)   | sigma(2)       Os DEC d(2) odlegosc drugiego przegubu
	        # 3(1)   |           0 |  0   | d(3,1) |        0       Dlugosc pierwszej polowy tubusu skierowanej w gorę
	        # 3(2)   | -1 * pi / 2 |  0   | d(3,2) |        0       Dlugosc drugiej polowy tubusa skierowanej w dol
	*/
	// Metoda oblicza pozycje obu koncow urzadzenia
	// Pierwszy element pary zwraca pozycję ogniwa numer 3
	// Drugi elelemnt pary zwraca pozycje ogniwa numer 4
	static std::pair<Eigen::Vector3d, Eigen::Vector3d>
	kinematicsPosition(const std::vector<tlinsLimitsDeviceInfo> &devInfo);

	static std::pair<Eigen::Vector3d, Eigen::Vector3d>
	kinematicsPositionGemetric(const double alfa, const double beta, const double h, const double r1, const double r2,
	                           const double r3, const std::vector<std::pair<std::string, double>> &axis);

	static std::pair<Eigen::Vector3d, Eigen::Vector3d>
	kinematicsPositionGemetric2(const double alfa, const double beta, const double r1, const double r2, const double dx,
	                            const double dz, const double h,
	                            const std::vector<std::pair<std::string, double>> &axis);

	// Metoda zwraca informację czy prosta identyfikowana przez punkt p3 jest w odleglosci kontowej <= od odleglosci
	// miedzy prostymi identyfikowanymi przez punkty p1 i p2. Wszystkie proste przechodzą przez poczatek ukladu
	// wspolrzednych. Metoda efektywnie sprawdza czy prosta trzecia jest wewnątrz stozka tworzonego przez proste p1 i p2

	static Eigen::Vector3d midlePoint(const Eigen::Vector3d &p1, const Eigen::Vector3d &p2);

	static double angleBetweenVectrors(const Eigen::Vector3d &p1, const Eigen::Vector3d &p2);

	// Metoda sprawdza limit dla pojednynczego ograniczenia
	static bool isInRange(const Eigen::Vector3d &p1, const Eigen::Vector3d &p2, const Eigen::Vector3d &pos);

	// Metoda analogoczna do powyzszej sprawdza dla listy ograniczen
	static bool isInRange(const std::vector<std::tuple<Eigen::Vector3d, Eigen::Vector3d>> &limits,
	                      const Eigen::Vector3d                                           &pos);
};

}; // namespace limits

#endif