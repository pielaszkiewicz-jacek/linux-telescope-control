#ifndef TLINSPLUGINSSTATE_H
#define TLINSPLUGINSSTATE_H

#include <functional>
#include <mutex>
#include <vector>

namespace tlinsAstroPilot
{

//
// Klasa zawiera aktualny stan kontrolera klawiatury
//
class tlinsPluginsState
{
public:
    enum class VALUE_TYPE {
        __raDelta__,
        __dcDelta__,
        __raSpeed__,
        __dcSpeed__,
        __calibrationObjectId__,
        __xDegrisDelta__,
        __yDegrisDelta__,
        __xDegrisSpeed__,
        __yDegrisSpeed__,
        __xStepsDelta__,
        __yStepsDelta__,
        __xStepsSpeed__,
        __yStepsSpeed__,
        __speedMode__,
        __inSteps__,
        __xScale__,
        __yScale__
    };
private:
    std::vector<std::function<void(VALUE_TYPE)>> callbacks;

    void executeCb(const VALUE_TYPE v);

public:
    void addCallback(std::function<void(const VALUE_TYPE)> fun);

private:
	//
	// Parametery przemieszczenia w trybie astro
	//
	// 1. aktualny przyrost wspolrzednej
	double raDelta;
	double dcDelta;

	// 2. Aktualna predkosc oraz przyspieszenie przemieszczenia
	double raSpeed;
	double dcSpeed;

	// 3. Biezacy obiekt kalibreacji
	int calibrationObjectId;

	//
	// Parametery w trybie urzadzenia
	//
	double xDegrisDelta;
	double yDegrisDelta;

	double xDegrisSpeed;
	double yDegrisSpeed;

	long xStepsDelta;
	long yStepsDelta;

	long xStepsSpeed;
	long yStepsSpeed;

	bool speedMode;
	bool inSteps;

    std::recursive_mutex mtx;

    int xScale;
    int yScale;

public:
	static tlinsPluginsState &getInstance();

    int getXScale();
    int getYScale();

    bool setXScale(const int xs);
    bool setYScale(const int ys);

    bool updateXScale(const int xs);
    bool updateYScale(const int ys);

	bool getSpeedMode();
	bool getInSteps();

	double getRaDelta();
	double getDcDelta();

	bool setRaDelta( const double v );
	bool setDcDelta( const double v );

    bool updateRaDelta( const double v );
    bool updateDcDelta( const double v );

	double getRaSpeed();
	double getDcSpeed();

	bool setRaSpeed( const double v );
	bool setDcSpeed( const double v );
    bool updateRaSpeed( const double v );
    bool updateDcSpeed( const double v );

	double getRaAceleration() ;
	double getDcAceleration() ;

	bool setRaAceleration( const double v );
	bool setDcAceleration( const double v );

    bool updateRaAceleration( const double v );
    bool updateDcAceleration( const double v );

	//
	// ----------------------------
	//
	double getXDegrisDelta();
	double getYDegrisDelta();

	double getXDegrisSpeed();
	double getYDegrisSpeed();

	long getXStepsDelta();
	long getYStepsDelta();

	long getXStepsSpeed();
	long getYStepsSpeed();

	void setSpeedMode( const bool v);
	void setInSteps( const bool v);

    void updateSpeedMode( const bool v);
    void updateInSteps( const bool v);

	bool setXDegrisDelta( const double v );
	bool setYDegrisDelta( const double v );

    bool updateXDegrisDelta( const double v );
    bool updateYDegrisDelta( const double v );

	bool setXDegrisSpeed( const double v );
	bool setYDegrisSpeed( const double v );

    bool updateXDegrisSpeed( const double v );
    bool updateYDegrisSpeed( const double v );

	bool setXStepsDelta( const long v );
	bool setYStepsDelta( const long v );

    bool updateXStepsDelta( const long v );
    bool updateYStepsDelta( const long v );

	bool setXStepsSpeed( const long v );
	bool setYStepsSpeed( const long v );

    bool updateXStepsSpeed( const long v );
    bool updateYStepsSpeed( const long v );

private:
	tlinsPluginsState();
};

};

#endif // TLINSPLUGINSSTATE_H
