#ifndef TLINSASTROENGINESTATE_H
#define TLINSASTROENGINESTATE_H

#include <string>

namespace TlinsAstroBase {

class tlinsAstroEngineState {
public:
    enum class EngineMode {
        MODE_NONE = 0,
        MODE_STANDARD = 1,
        MODE_EXTERNAL_SUPPORT = 2
    };

    enum class EngineState {
        STATE_CALIBRATION = 0,
        STATE_CALIBRATION_VELOCITY = 1,
        STATE_REGULAR = 2
    };

private:
    std::string name;

    double RA; // + Right Ascension
    double DC; // + Declination
    double pmRA; // + Proper Motion in RA
    double pmDC; // + Proper Motion in DC
    double radialVelocity; // + Radial velocity
    double parallex; // + Parallex

    // katalog
    std::string catalogType;

    // Macierz transformacji
    double a11;
    double a12;
    double a13;
    double a21;
    double a22;
    double a23;
    double a31;
    double a32;
    double a33;

    bool xReverse;
    bool yReverse;

    // POzycja kontrolera
    long deviceX;
    long deviceY;
    long deviceXEncoder;
    long deviceYEncoder;

    // Tryb i stan silnika
    EngineMode mode;
    EngineState state;

    double aceleration;
    double speed;
    unsigned long delta;

public:
    void setXReverse(const bool v)
    {
        xReverse = v;
    }

    void setYReverse(const bool v)
    {
        yReverse = v;
    }

    bool getXReverse() const
    {
        return xReverse;
    }

    bool getYReverse() const
    {
        return yReverse;
    }

    std::string getName() const
    {
        return name;
    }

    void setName(const std::string& v)
    {
        name = v;
    }

    //
    // Get
    //
    double getAceleration() const
    {
        return aceleration;
    }

    double getSpeed() const
    {
        return speed;
    }

    unsigned long getDelta() const
    {
        return delta;
    }

    double getRA() const;
    double getDC() const;
    double getPmRA() const;
    double getPmDC() const;
    double getRadialVelocity() const;
    double getParallex() const;
    std::string getCatalogType() const;
    double getA11() const;
    double getA12() const;
    double getA13() const;
    double getA21() const;
    double getA22() const;
    double getA23() const;
    double getA31() const;
    double getA32() const;
    double getA33() const;

    long getDeviceX() const;
    long getDeviceY() const;
    long getDeviceXEncoder() const;
    long getDeviceYEncoder() const;

    EngineMode getMode() const;
    EngineState getState() const;

    //
    // Set
    //
    void setAceleration(const double v)
    {
        aceleration = v;
    }

    void setSpeed(const double v)
    {
        speed = v;
    }

    void setDelta(const unsigned long v)
    {
        delta = v;
    }

    void setRA(const double v);
    void setDC(const double v);
    void setPmRA(const double v);
    void setPmDC(const double v);
    void setRadialVelocity(const double v);
    void setParallex(const double v);
    void setCatalogType(const std::string& v);
    void setA11(const double v);
    void setA12(const double v);
    void setA13(const double v);
    void setA21(const double v);
    void setA22(const double v);
    void setA23(const double v);
    void setA31(const double v);
    void setA32(const double v);
    void setA33(const double v);

    void setDeviceX(const long v);
    void setDeviceY(const long v);
    void setDeviceXEncoder(const long v);
    void setDeviceYEncoder(const long v);

    void setMode(const EngineMode v);
    void setState(const EngineState v);

public:
    tlinsAstroEngineState& operator=(const tlinsAstroEngineState& v);
    tlinsAstroEngineState(const tlinsAstroEngineState& v);
    tlinsAstroEngineState();
};

}

#endif // TLINSASTROENGINESTATE_H
