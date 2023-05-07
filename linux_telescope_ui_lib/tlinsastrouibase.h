#ifndef TLINSASTROUIBASE_H
#define TLINSASTROUIBASE_H

#include <memory>
#include <tlinsAstroEngineInterface.hpp>
#include <tlinsMoveServerInterface.hpp>
#include <tlinsconnection.h>
#include <utility>

namespace TlinsAstroBase {

class tlinsAstroBase {
public:
    enum class Mode {
        ASTRO = 1,
        DEGRIS = 2,
        STEPS = 3
    };

    enum class Axis {
        AxisX = 1,
        AxisY = 2,
        AxisXY = 3
    };

private:
    double velRA;
    double velDC;
    double velDegX;
    double velDegY;
    double velStepX;
    double velStepY;

    double disRA;
    double disDC;
    double disDegX;
    double disDegY;
    double disStepX;
    double disStepY;

    void speedParameters(Mode mode, long& interA, long& interD, long& interV);

    void readMoveDataAstro(long& Ax, long& Dx, long& Vx, long& Lx,
        double& AxD, double& DxD, double& VxD, double& AyD, double& DyD, double& VyD,
        long& Ay, long& Dy, long& Vy, long& Ly,
        double lx, double ly, double vx, double vy);

    void readMoveDataDegris(long& Ax, long& Dx, long& Vx, long& Lx,
        long& Ay, long& Dy, long& Vy, long& Ly,
        double lx, double ly, double vx, double vy);

    void readMoveDataSteps(long& Ax, long& Dx, long& Vx, long& Lx,
        long& Ay, long& Dy, long& Vy, long& Ly,
        double lx, double ly, double vx, double vy);

    void buildRequest(long Ax, long Dx, long Vx, long Lx,
        long Ay, long Dy, long Vy, long Ly,
        const bool isLeftX,
        const bool isLeftY,
        const bool inSpeed,
        const Axis a,
        const Mode mode,
        std::unique_ptr<tlinsMoveServerInterface::MoveRequestDevice>& moveReq);

public:
    void setValueSteps(const double lx, const double ly, const double vx, const double vy)
    {
        velStepX = vx;
        velStepY = vy;
        disStepX = lx;
        disStepY = ly;
    }

    void setValueDegris(const double lx, const double ly, const double vx, const double vy)
    {
        velDegX = vx;
        velDegY = vy;
        disDegX = lx;
        disDegY = ly;
    }

    void setValueAstro(const double lx, const double ly, const double vx, const double vy)
    {
        velRA = vx;
        velDC = vy;
        disRA = lx;
        disDC = ly;
    }

    bool createStopRequest(const Axis a, Mode mode,
        std::unique_ptr<tlinsMoveServerInterface::MoveRequestDevice>& moveReq,
        const bool isAbort);

    bool generateMoveX(const bool isLeft, Mode mode,
        bool inSpeed,
        std::unique_ptr<tlinsMoveServerInterface::MoveRequestDevice>& moveReq,
        std::unique_ptr<tlinsAstroEngineInterface::tlinsTarget>& astroRequest);

    bool generateMoveY(const bool isLeft, Mode mode,
        bool inSpeed,
        std::unique_ptr<tlinsMoveServerInterface::MoveRequestDevice>& moveReq,
        std::unique_ptr<tlinsAstroEngineInterface::tlinsTarget>& astroRequest);

    bool generateMove(const Axis a, const bool isLeftX, const bool isLeftY,
        Mode mode, bool inSpeed,
        std::unique_ptr<tlinsMoveServerInterface::MoveRequestDevice>& moveReq,
        std::unique_ptr<tlinsAstroEngineInterface::tlinsTarget>& astroRequest);

    void generateMove3(const Axis a, const bool isLeftX, const bool isLeftY,
        const Mode mode, const bool inSpeed,
        std::unique_ptr<tlinsMoveServerInterface::MoveRequestDevice>& moveReq,
        const long scaleX = 1,
        const long scaleY = 1,
        const long maxScaleX = 1,
        const long maxScaleY = 1);

    static void speedRequestMove(const bool aX, const bool aY,
        const bool isLeftX, const bool isLeftY,
        const long scaleX, const long scaleXMax,
        const long scaleY, const long scaleYMax,
        const bool inAstro, const bool fullInit,
        const tlinsAstroBase::Mode mode,
        const bool isTrackingEnabled);

    static void speedRequestMoveRelease(const bool aX, const bool aY,
        const bool isAstro, const bool completeStop,
        const tlinsAstroBase::Mode mode,
        const bool isTrackingEnabled);

    static void distanceRequestMove(const bool aX, // Uzycie osi X
        const bool aY, // Uzycie osi Y
        const bool inAstro,
        const double distanceX, // Wartosc przemieszczenia w OSI X
        // Gdy < 0.0 lewo, gdy >= 0.0 w prawo
        const double distanceY, // Wartosc przemieszczenia w OSI Y
        // Gdy < 0.0 gora, gdy >= 0.0 w dol
        const double vX_,
        const double vY_,
        const tlinsAstroBase::Mode mode);

    static void trackingStop(const bool stop = false, const bool noSynch = false);
    static void trackingSart(const bool noSynch = false);
    static void getAstroStaetInfo(bool& state, bool& trackingStatet);

    tlinsAstroBase();
};

}

#endif // TLINSASTROUIBASE_H
