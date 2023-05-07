#include "tlinsastrouibase.h"
#include "tlinsastrobaseutils.h"
#include "tlinscommunicationthread.h"
#include <QDebug>
#include <chrono>
#include <condition_variable>
#include <math.h>
#include <mutex>
#include <sofam.h>
#include <tlinsBacktrace.hpp>
#include <tlinsconfiguration.h>
#include <tlinsserverstatusinfo.h>

namespace TlinsAstroBase {

void tlinsAstroBase::speedParameters(Mode mode,
    long& interA,
    long& interD,
    long& interV)
{
    auto& cfg = tlinsConfiguration::getInstance();
    auto& statInfo = tlinsServerStatusInfo::getInstance();
    auto& devCfg = statInfo.getDeviceConfiguration()["X"];

    if (mode == Mode::ASTRO) {
        interA = static_cast<long>((cfg.getDouble(tlinsConfiguration::RAMP_PARAMETER_GROUP, tlinsConfiguration::RAMP_PARAMETER_ASTRO_RA_A) / 24.0) * static_cast<double>(devCfg.get_deviceResolution()));
        interD = static_cast<long>((cfg.getDouble(tlinsConfiguration::RAMP_PARAMETER_GROUP, tlinsConfiguration::RAMP_PARAMETER_ASTRO_RA_D) / 24.0) * static_cast<double>(devCfg.get_deviceResolution()));
        interV = static_cast<long>((cfg.getDouble(tlinsConfiguration::RAMP_PARAMETER_GROUP, tlinsConfiguration::RAMP_PARAMETER_ASTRO_RA_V_MAX) / 24.0) * static_cast<double>(devCfg.get_deviceResolution()));
    } else if (mode == Mode::DEGRIS) {
        interA = static_cast<long>((cfg.getDouble(tlinsConfiguration::RAMP_PARAMETER_GROUP, tlinsConfiguration::RAMP_PARAMETER_DEGRIS_X_A) / 360.0) * static_cast<double>(devCfg.get_deviceResolution()));
        interD = static_cast<long>((cfg.getDouble(tlinsConfiguration::RAMP_PARAMETER_GROUP, tlinsConfiguration::RAMP_PARAMETER_DEGRIS_X_D) / 360.0) * static_cast<double>(devCfg.get_deviceResolution()));
        interV = static_cast<long>((cfg.getDouble(tlinsConfiguration::RAMP_PARAMETER_GROUP, tlinsConfiguration::RAMP_PARAMETER_DEGRIS_X_V_MAX) / 360.0) * static_cast<double>(devCfg.get_deviceResolution()));
    } else {
        interA = static_cast<long>(cfg.getInt(tlinsConfiguration::RAMP_PARAMETER_GROUP, tlinsConfiguration::RAMP_PARAMETER_STEPS_X_A));
        interD = static_cast<long>(cfg.getInt(tlinsConfiguration::RAMP_PARAMETER_GROUP, tlinsConfiguration::RAMP_PARAMETER_STEPS_X_D));
        interV = static_cast<long>(cfg.getInt(tlinsConfiguration::RAMP_PARAMETER_GROUP, tlinsConfiguration::RAMP_PARAMETER_STEPS_X_V_MAX));
    }
}

bool tlinsAstroBase::generateMove(const Axis a,
    const bool isLeftX,
    const bool isLeftY,
    Mode mode,
    bool inSpeed,
    std::unique_ptr<tlinsMoveServerInterface::MoveRequestDevice>& moveReq,
    std::unique_ptr<tlinsAstroEngineInterface::tlinsTarget>& astroRequest)
{
    auto& statInfo = tlinsServerStatusInfo::getInstance();
    if (statInfo.getDeviceConfiguration().find("X") == statInfo.getDeviceConfiguration().end()) {
        TLINS_LOG_ERROR("No configuration for X");
        return false;
    }

    if (statInfo.getDeviceConfiguration().find("Y") == statInfo.getDeviceConfiguration().end()) {
        TLINS_LOG_ERROR("No configuration for Y");
        return false;
    }

    // 1. Nazwa urzadzenia glownego
    std::string mainDeviceName = "main";
    auto& cfg = tlinsConfiguration::getInstance();

    if (cfg.hasKey(tlinsConfiguration::COMMON_PARAMETER_GROUP, tlinsConfiguration::COMMON_MAIN_DEVICE_NAME))
        mainDeviceName = cfg.getString(tlinsConfiguration::COMMON_PARAMETER_GROUP, tlinsConfiguration::COMMON_MAIN_DEVICE_NAME);

    // Parametery rampy dla obu osi
    long Ax = 0;
    long Dx = 0;
    long Vx = 0;
    long Lx = 0;
    double AxD = 0.0;
    double DxD = 0.0;
    double VxD = 0.0;
    double AyD = 0.0;
    double DyD = 0.0;
    double VyD = 0.0;
    long Ay = 0;
    long Dy = 0;
    long Vy = 0;
    long Ly = 0;

    long interA;
    long interD;
    long interV;

    double lx;
    double ly;
    double vx;
    double vy;

    if (mode == Mode::ASTRO) {
        // Astro - wspolrzedne astronomiczne
        vx = velRA;
        vy = velDC;
        lx = disRA;
        ly = disDC;
    } else if (mode == Mode::DEGRIS) {
        // Stopnie
        vx = velDegX;
        vy = velDegY;
        lx = disDegX;
        ly = disDegY;
    } else {
        // Kroki
        vx = velStepX;
        vy = velStepY;
        lx = disStepX;
        ly = disStepY;
    }

    // Parametery rampy w trybie interpolowanym - tylko dla trybu astro
    // W trybie interpolowanym uzywamy konfiguracji dla osi RA
    speedParameters(mode, interA, interD, interV);

    // Przemieszczenie kontowe w trybie astro
    bool XSign = false;
    int Xh = 0;
    int Xm = 0;
    double Xs = 0.0;

    bool YSign = false;
    int Yd = 0;
    int Ym = 0;
    double Ys = 0.0;

    //
    // Okreslenie A, D, V dla osi ktorych bedzie wykonane przemieszczenie
    //
    if (a == Axis::AxisX || a == Axis::AxisXY) {
        // Konfiguracja osi X (pobrana z kontrolera)
        auto& devCfg = statInfo.getDeviceConfiguration()["X"];

        if (mode == Mode::ASTRO) {
            // Astro - wspolrzedne astronomiczne
            AxD = cfg.getDouble(tlinsConfiguration::RAMP_PARAMETER_GROUP, tlinsConfiguration::RAMP_PARAMETER_ASTRO_RA_A);
            DxD = cfg.getDouble(tlinsConfiguration::RAMP_PARAMETER_GROUP, tlinsConfiguration::RAMP_PARAMETER_ASTRO_RA_D);

            Ax = static_cast<long>(AxD);
            Dx = static_cast<long>(DxD);
            VxD = (vx / 24.0) * static_cast<double>(devCfg.get_deviceResolution());
            Vx = static_cast<long>(VxD);

            // Przyrost wspolrzednej RA
            double raVal = cfg.getDouble(tlinsConfiguration::PILOT_PARAMETER_GROUP, tlinsConfiguration::PILOT_PARAMETER_ASTRO_RA);
            tlinsAstroBaseUtils::splitRA(raVal, Xh, Xm, Xs, XSign);

            if (isLeftX) {
                Xh *= -1;
                XSign = true;
            }
            Lx = 0;
        } else if (mode == Mode::DEGRIS) {
            // Stopnie
            Ax = static_cast<long>((cfg.getDouble(tlinsConfiguration::RAMP_PARAMETER_GROUP,
                                        tlinsConfiguration::RAMP_PARAMETER_DEGRIS_X_A)
                                       / 360.0)
                * static_cast<double>(devCfg.get_deviceResolution()));
            Dx = static_cast<long>((cfg.getDouble(tlinsConfiguration::RAMP_PARAMETER_GROUP,
                                        tlinsConfiguration::RAMP_PARAMETER_DEGRIS_X_D)
                                       / 360.0)
                * static_cast<double>(devCfg.get_deviceResolution()));
            Vx = static_cast<long>((vx / 360.0) * static_cast<double>(devCfg.get_deviceResolution()));
            Lx = static_cast<long>((lx / 360.0) * static_cast<double>(devCfg.get_deviceResolution()));
        } else {
            // Kroki
            Ax = cfg.getInt(tlinsConfiguration::RAMP_PARAMETER_GROUP, tlinsConfiguration::RAMP_PARAMETER_STEPS_X_A);
            Dx = cfg.getInt(tlinsConfiguration::RAMP_PARAMETER_GROUP, tlinsConfiguration::RAMP_PARAMETER_STEPS_X_D);
            Vx = static_cast<long>(vx);
            Lx = static_cast<long>(lx);
        }
    }

    if (a == Axis::AxisY || a == Axis::AxisXY) {
        // Konfiguracja osi Y
        auto& devCfg = statInfo.getDeviceConfiguration()["Y"];

        if (mode == Mode::ASTRO) {
            AyD = cfg.getDouble(tlinsConfiguration::RAMP_PARAMETER_GROUP, tlinsConfiguration::RAMP_PARAMETER_ASTRO_DC_A);
            DyD = cfg.getDouble(tlinsConfiguration::RAMP_PARAMETER_GROUP, tlinsConfiguration::RAMP_PARAMETER_ASTRO_DC_D);

            // Astro - wspolrzedne astronomiczne
            Ay = static_cast<long>(AyD);
            Dy = static_cast<long>(DyD);
            VyD = (vy / 24.0) * static_cast<double>(devCfg.get_deviceResolution());
            Vy = static_cast<long>(VyD);

            // Przyrost wsporzednej DC
            double dcVal = cfg.getDouble(tlinsConfiguration::PILOT_PARAMETER_GROUP, tlinsConfiguration::PILOT_PARAMETER_ASTRO_DC);
            tlinsAstroBaseUtils::splitRA(dcVal, Yd, Ym, Ys, YSign);

            if (isLeftY) {
                Yd *= -1;
                YSign = true;
            }
            Ly = 0;
        } else if (mode == Mode::DEGRIS) {
            // Stopnie
            Ay = static_cast<long>((cfg.getDouble(tlinsConfiguration::RAMP_PARAMETER_GROUP, tlinsConfiguration::RAMP_PARAMETER_DEGRIS_Y_A) / 360.0) * static_cast<double>(devCfg.get_deviceResolution()));
            Dy = static_cast<long>((cfg.getDouble(tlinsConfiguration::RAMP_PARAMETER_GROUP, tlinsConfiguration::RAMP_PARAMETER_DEGRIS_Y_D) / 360.0) * static_cast<double>(devCfg.get_deviceResolution()));
            Vy = static_cast<long>((vy / 360.0) * static_cast<double>(devCfg.get_deviceResolution()));
            Ly = static_cast<long>((ly / 360.0) * static_cast<double>(devCfg.get_deviceResolution()));
        } else {
            // Kroki
            Ay = cfg.getInt(tlinsConfiguration::RAMP_PARAMETER_GROUP, tlinsConfiguration::RAMP_PARAMETER_STEPS_Y_A);
            Dy = cfg.getInt(tlinsConfiguration::RAMP_PARAMETER_GROUP, tlinsConfiguration::RAMP_PARAMETER_STEPS_Y_D);
            Vy = static_cast<long>(vy);
            Ly = static_cast<long>(ly);
        }
    }

    if (mode == Mode::ASTRO && !inSpeed) {
        //
        // Tworzenie wynikowego celu
        //
        astroRequest = std::move(std::unique_ptr<tlinsAstroEngineInterface::tlinsTarget> { new tlinsAstroEngineInterface::tlinsTarget {} });
        tlinsAstroEngineInterface::tlinsAstroObject object;

        // Paralaksa, ruch wlasny, predkosc katowa, katalog
        object.set_parallax(0.0);
        object.set_properMotionRA(0.0);
        object.set_properMotionDC(0.0);
        object.set_radialVelocity(0.0);
        object.set_catalogType(std::string {});

        tlinsAstroEngineInterface::tlinsCoordinate ra {};
        tlinsAstroEngineInterface::tlinsCoordinate dc {};

        astroRequest->set_delta(0);

        if (a == Axis::AxisX || a == Axis::AxisXY) {
            astroRequest->set_speed(vx /*VxD*/);
            astroRequest->set_aceleration(AxD);
            ra.set_sign(XSign);
            ra.set_degris(Xh);
            ra.set_minutes(Xm);
            ra.set_seconds(Xs);
        }

        if (a == Axis::AxisY || a == Axis::AxisXY) {
            astroRequest->set_speed(vy /*VyD*/);
            astroRequest->set_aceleration(AyD);
            dc.set_sign(YSign);
            dc.set_degris(Yd);
            dc.set_minutes(Ym);
            dc.set_seconds(Ys);
        }

        object.set_hourAngle(ra);
        object.set_declination(dc);
        astroRequest->set_object(object);
    } else {
        //
        // Tworzenie rzadania przemieszczenia
        //
        moveReq = std::move(std::unique_ptr<tlinsMoveServerInterface::MoveRequestDevice> { new tlinsMoveServerInterface::MoveRequestDevice {} });
        moveReq->set_A(interA);
        moveReq->set_D(interD);

        if (a == Axis::AxisX || a == Axis::AxisXY) {
            auto& items = moveReq->getRequestItems();
            moveReq->set_V(Vx);

            // Parametery rampy
            auto& item = items["X"];
            item.set_A(Ax);
            item.set_D(Dx);
            item.set_V(Vx);
            item.set_distance((Lx < 0) ? (Lx * -1) : (Lx));
            item.set_direction(isLeftX ? (tlinsMoveServerInterface::RequestDirection::LEFT) : (tlinsMoveServerInterface::RequestDirection::RIGHT));
        }

        if (a == Axis::AxisY || a == Axis::AxisXY) {
            auto& items = moveReq->getRequestItems();
            moveReq->set_V(Vy);

            // Parametery rampy
            auto& item = items["Y"];
            item.set_A(Ay);
            item.set_D(Dy);
            item.set_V(Vy);
            item.set_distance((Ly < 0) ? (Ly * -1) : (Ly));
            item.set_direction(isLeftY ? (tlinsMoveServerInterface::RequestDirection::LEFT) : (tlinsMoveServerInterface::RequestDirection::RIGHT));
        }

        // W trybie predkosci przemieszczenie absolutne
        // W trybie przemieszczenia delta przemieszczenie relatywne
        if (inSpeed) {
            moveReq->set_relAbs(tlinsMoveServerInterface::ModeRelAbs::ABS);
            moveReq->set_moveType(tlinsMoveServerInterface::MoveType::SPEED);
        } else {
            moveReq->set_relAbs(tlinsMoveServerInterface::ModeRelAbs::REL);
            moveReq->set_moveType(tlinsMoveServerInterface::MoveType::MOVE);
        }

        // Brak interpolacji
        moveReq->set_interpolationType(tlinsMoveServerInterface::InterpolationType::NONE);
    }
    return true;
}

void tlinsAstroBase::readMoveDataAstro(long& Ax, long& Dx, long& Vx, long& Lx,
    double& AxD, double& DxD, double& VxD,
    double& AyD, double& DyD, double& VyD,
    long& Ay, long& Dy, long& Vy, long& Ly,
    double lx, double ly,
    double vx, double vy)
{
    auto& statInfo = tlinsServerStatusInfo::getInstance();
    auto& cfg = tlinsConfiguration::getInstance();

    AxD = cfg.getDouble(tlinsConfiguration::RAMP_PARAMETER_GROUP,
        tlinsConfiguration::RAMP_PARAMETER_ASTRO_RA_A);

    DxD = cfg.getDouble(tlinsConfiguration::RAMP_PARAMETER_GROUP,
        tlinsConfiguration::RAMP_PARAMETER_ASTRO_RA_D);

    AyD = cfg.getDouble(tlinsConfiguration::RAMP_PARAMETER_GROUP,
        tlinsConfiguration::RAMP_PARAMETER_ASTRO_DC_A);
    DyD = cfg.getDouble(tlinsConfiguration::RAMP_PARAMETER_GROUP,
        tlinsConfiguration::RAMP_PARAMETER_ASTRO_DC_D);

    vx = velRA;
    vy = velDC;
    lx = disRA;
    ly = disDC;

    {
        auto& devCfg = statInfo.getDeviceConfiguration()["X"];
        VxD = (velRA / 24.0) * static_cast<double>(devCfg.get_deviceResolution());
        Vx = static_cast<long>(VxD);
        Lx = 0;

        AxD = (AxD / 24.0) * static_cast<double>(devCfg.get_deviceResolution());
        DxD = (DxD / 24.0) * static_cast<double>(devCfg.get_deviceResolution());
        Ax = static_cast<long>(AxD);
        Dx = static_cast<long>(DxD);
    }
    {
        auto& devCfg = statInfo.getDeviceConfiguration()["Y"];
        VyD = (velDC / 360.0) * static_cast<double>(devCfg.get_deviceResolution());
        Vy = static_cast<long>(VyD);
        Ly = 0;
        AyD = (AyD / 360.0) * static_cast<double>(devCfg.get_deviceResolution());
        DyD = (DyD / 360.0) * static_cast<double>(devCfg.get_deviceResolution());
        Ay = static_cast<long>(AyD);
        Dy = static_cast<long>(DyD);
    }
}

void tlinsAstroBase::readMoveDataDegris(long& Ax, long& Dx, long& Vx, long& Lx,
    long& Ay, long& Dy, long& Vy, long& Ly,
    double lx, double ly, double vx, double vy)
{
    auto& statInfo = tlinsServerStatusInfo::getInstance();
    auto& cfg = tlinsConfiguration::getInstance();

    vx = velDegX;
    vy = velDegY;
    lx = disDegX;
    ly = disDegY;

    {
        auto& devCfg = statInfo.getDeviceConfiguration()["X"];
        Ax = static_cast<long>((cfg.getDouble(tlinsConfiguration::RAMP_PARAMETER_GROUP,
                                    tlinsConfiguration::RAMP_PARAMETER_DEGRIS_X_A)
                                   / 360.0)
            * static_cast<double>(devCfg.get_deviceResolution()));
        Dx = static_cast<long>((cfg.getDouble(tlinsConfiguration::RAMP_PARAMETER_GROUP,
                                    tlinsConfiguration::RAMP_PARAMETER_DEGRIS_X_D)
                                   / 360.0)
            * static_cast<double>(devCfg.get_deviceResolution()));
        Vx = static_cast<long>((vx / 360.0) * static_cast<double>(devCfg.get_deviceResolution()));
        Lx = static_cast<long>((lx / 360.0) * static_cast<double>(devCfg.get_deviceResolution()));
    }

    {
        auto& devCfg = statInfo.getDeviceConfiguration()["Y"];
        Ay = static_cast<long>((cfg.getDouble(tlinsConfiguration::RAMP_PARAMETER_GROUP,
                                    tlinsConfiguration::RAMP_PARAMETER_DEGRIS_Y_A)
                                   / 360.0)
            * static_cast<double>(devCfg.get_deviceResolution()));
        Dy = static_cast<long>((cfg.getDouble(tlinsConfiguration::RAMP_PARAMETER_GROUP,
                                    tlinsConfiguration::RAMP_PARAMETER_DEGRIS_Y_D)
                                   / 360.0)
            * static_cast<double>(devCfg.get_deviceResolution()));
        Vy = static_cast<long>((vx / 360.0) * static_cast<double>(devCfg.get_deviceResolution()));
        Ly = static_cast<long>((lx / 360.0) * static_cast<double>(devCfg.get_deviceResolution()));
    }
}

void tlinsAstroBase::readMoveDataSteps(long& Ax, long& Dx, long& Vx, long& Lx,
    long& Ay, long& Dy, long& Vy, long& Ly,
    double lx, double ly, double vx, double vy)
{
    auto& cfg = tlinsConfiguration::getInstance();

    vx = velStepX;
    vy = velStepY;
    lx = disStepX;
    ly = disStepY;

    {
        Ax = cfg.getInt(tlinsConfiguration::RAMP_PARAMETER_GROUP,
            tlinsConfiguration::RAMP_PARAMETER_STEPS_X_A);
        Dx = cfg.getInt(tlinsConfiguration::RAMP_PARAMETER_GROUP,
            tlinsConfiguration::RAMP_PARAMETER_STEPS_X_D);
        Vx = static_cast<long>(vx);
        Lx = static_cast<long>(lx);
    }

    {
        Ay = cfg.getInt(tlinsConfiguration::RAMP_PARAMETER_GROUP, tlinsConfiguration::RAMP_PARAMETER_STEPS_Y_A);
        Dy = cfg.getInt(tlinsConfiguration::RAMP_PARAMETER_GROUP, tlinsConfiguration::RAMP_PARAMETER_STEPS_Y_D);
        Vy = static_cast<long>(vy);
        Ly = static_cast<long>(ly);
    }
}

void tlinsAstroBase::buildRequest(long Ax, long Dx, long Vx, long Lx,
    long Ay, long Dy, long Vy, long Ly,
    const bool isLeftX,
    const bool isLeftY,
    const bool inSpeed,
    const Axis axis,
    const Mode mode,
    std::unique_ptr<tlinsMoveServerInterface::MoveRequestDevice>& moveReq)
{
    long interA = 0;
    long interD = 0;
    long interV = 0;

    // Parametery rampy w trybie interpolowanym - tylko dla trybu astro
    // W trybie interpolowanym uzywamy konfiguracji dla osi RA
    speedParameters(mode, interA, interD, interV);

    //
    // Tworzenie rzadania przemieszczenia
    //
    moveReq = std::move(std::unique_ptr<tlinsMoveServerInterface::MoveRequestDevice> { new tlinsMoveServerInterface::MoveRequestDevice {} });
    moveReq->set_A(interA);
    moveReq->set_D(interD);

    if (axis == Axis::AxisX || axis == Axis::AxisXY) {
        auto& items = moveReq->getRequestItems();
        moveReq->set_V(Vx);

        // Parametery rampy
        auto& item = items["X"];
        item.set_A(Ax);
        item.set_D(Dx);
        item.set_V(Vx);
        item.set_distance((Lx < 0) ? (Lx * -1) : (Lx));
        item.set_direction(isLeftX ? (tlinsMoveServerInterface::RequestDirection::LEFT) : (tlinsMoveServerInterface::RequestDirection::RIGHT));
    }

    if (axis == Axis::AxisY || axis == Axis::AxisXY) {
        auto& items = moveReq->getRequestItems();
        moveReq->set_V(Vy);

        // Parametery rampy
        auto& item = items["Y"];
        item.set_A(Ay);
        item.set_D(Dy);
        item.set_V(Vy);
        item.set_distance((Ly < 0) ? (Ly * -1) : (Ly));
        item.set_direction(isLeftY ? (tlinsMoveServerInterface::RequestDirection::LEFT) : (tlinsMoveServerInterface::RequestDirection::RIGHT));
    }

    if (inSpeed) {
        moveReq->set_relAbs(tlinsMoveServerInterface::ModeRelAbs::ABS);
        moveReq->set_moveType(tlinsMoveServerInterface::MoveType::SPEED);
    } else {
        moveReq->set_relAbs(tlinsMoveServerInterface::ModeRelAbs::REL);
        moveReq->set_moveType(tlinsMoveServerInterface::MoveType::MOVE);
    }

    // Brak interpolacji
    moveReq->set_interpolationType(tlinsMoveServerInterface::InterpolationType::NONE);
}

void tlinsAstroBase::generateMove3(const Axis axis,
    const bool isLeftX,
    const bool isLeftY,
    const Mode mode,
    const bool inSpeed,
    std::unique_ptr<tlinsMoveServerInterface::MoveRequestDevice>& moveReq,
    const long scaleX_,
    const long scaleY_,
    const long maxScaleX_,
    const long maxScaleY_)
{
    long Ax = 0, Dx = 0, Vx = 0, Lx = 0;
    long Ay = 0, Dy = 0, Vy = 0, Ly = 0;
    double AxD = 0.0, DxD = 0.0, VxD = 0.0;
    double AyD = 0.0, DyD = 0.0, VyD = 0.0;
    double lx = 0.0, ly = 0.0;
    double vx = 0.0, vy = 0.0;

    long scaleX = scaleX_;
    long scaleY = scaleY_;
    long maxScaleX = maxScaleX_;
    long maxScaleY = maxScaleY_;

    if (scaleX > maxScaleX)
        scaleX = maxScaleX;

    if (scaleY > maxScaleY)
        scaleY = maxScaleY;

    TLINS_LOG_DEBUG("scaleX = " + std::to_string(scaleX) + "; scaleY = " + std::to_string(scaleY));

    switch (mode) {
    case Mode::ASTRO:
        //  W trybie astro jerst generowany tylko tryb speed
        readMoveDataAstro(Ax, Dx, Vx, Lx, AxD, DxD, VxD, AyD, DyD, VyD, Ay, Dy, Vy, Ly, lx, ly, vx, vy);

        // Skalowanie predkosci
        if (scaleX != 0) {
            double maxScaleXD = static_cast<double>(maxScaleX);
            double scaleXD = static_cast<double>(scaleX);
            Vx = Vx * scaleX / maxScaleX;
            VxD = VxD * scaleXD / maxScaleXD;
        }

        if (scaleY != 0) {
            double maxScaleYD = static_cast<double>(maxScaleY);
            double scaleYD = static_cast<double>(scaleY);
            Vy = Vy * scaleY / maxScaleY;
            VyD = VyD * scaleYD / maxScaleYD;
        }

        TLINS_LOG_DEBUG("VX = " + std::to_string(Vx) + "; VY = " + std::to_string(Vy));

        //        qDebug() << "VX = " << Vx << "; VY = " << Vy << "; SCALE X = " << scaleX << "; SCALE Y = " << scaleY;

        buildRequest(Ax, Dx, Vx, Lx, Ay, Dy, Vy, Ly, isLeftX, isLeftY, true, axis, mode, moveReq);
        break;

    case Mode::DEGRIS:
        readMoveDataDegris(Ax, Dx, Vx, Lx, Ay, Dy, Vy, Ly, lx, ly, vx, vy);
        //        qDebug() << "VX = " << Vx << "; VY = " << Vy << "; SCALE X = " << scaleX << "; SCALE Y = " << scaleY << "; maxScaleX = " << maxScaleX;

        // Skalowanie predkosci
        if (scaleX != 0)
            Vx = Vx * scaleX / maxScaleX;
        else
            Vx = 0;

        if (scaleY != 0)
            Vy = Vy * scaleY / maxScaleY;
        else
            Vy = 0;

        TLINS_LOG_DEBUG("VX = " + std::to_string(Vx) + "; VY = " + std::to_string(Vy));
        //        qDebug() << "VX = " << Vx << "; VY = " << Vy << "; SCALE X = " << scaleX << "; SCALE Y = " << scaleY;

        buildRequest(Ax, Dx, Vx, Lx, Ay, Dy, Vy, Ly, isLeftX, isLeftY, inSpeed, axis, mode, moveReq);
        break;

    case Mode::STEPS:
        readMoveDataSteps(Ax, Dx, Vx, Lx, Ay, Dy, Vy, Ly, lx, ly, vx, vy);

        // Skalowanie predkosci
        if (scaleX != 0)
            Vx = Vx * scaleX / maxScaleX;

        if (scaleY != 0)
            Vy = Vy * scaleY / maxScaleY;

        TLINS_LOG_DEBUG("VX = " + std::to_string(Vx) + "; VY = " + std::to_string(Vy));

        //        qDebug() << "VX = " << Vx << "; VY = " << Vy << "; SCALE X = " << scaleX << "; SCALE Y = " << scaleY;

        buildRequest(Ax, Dx, Vx, Lx, Ay, Dy, Vy, Ly, isLeftX, isLeftY, inSpeed, axis, mode, moveReq);
        break;
    }
}

bool tlinsAstroBase::createStopRequest(const Axis a,
    Mode mode,
    std::unique_ptr<tlinsMoveServerInterface::MoveRequestDevice>& moveReq,
    const bool isAbort)
{
    long interA;
    long interD;

    auto& cfg = TlinsAstroBase::tlinsConfiguration::getInstance();

    // Singleton zawierajacu aktualny stan i konfiguracje kontrolera
    auto& statInfo = TlinsAstroBase::tlinsServerStatusInfo::getInstance();

    {
        // Parametery rampy w trybie interpolowanym - tylko dla trybu astro
        // W trybie interpolowanym uzywamy konfiguracji dla osi RA
        if (statInfo.getDeviceConfiguration().find("X") == statInfo.getDeviceConfiguration().end()) {
            TLINS_LOG_ERROR("No configuration for X");
            return false;
        }

        auto& devCfg = statInfo.getDeviceConfiguration()["X"];
        interA = static_cast<long>((cfg.getDouble(TlinsAstroBase::tlinsConfiguration::RAMP_PARAMETER_GROUP,
                                        TlinsAstroBase::tlinsConfiguration::RAMP_PARAMETER_ASTRO_RA_A)
                                       / 24.0)
            * static_cast<double>(devCfg.get_deviceResolution()));
        interD = static_cast<long>((cfg.getDouble(TlinsAstroBase::tlinsConfiguration::RAMP_PARAMETER_GROUP,
                                        TlinsAstroBase::tlinsConfiguration::RAMP_PARAMETER_ASTRO_RA_D)
                                       / 24.0)
            * static_cast<double>(devCfg.get_deviceResolution()));
    }

    // Parametery rampy
    long Ax = 0;
    long Dx = 0;
    long Ay = 0;
    long Dy = 0;

    // Okreslenie osi dla ktorych bedzie wykonane przemieszczenie
    if (a == Axis::AxisX || a == Axis::AxisXY) {
        // Konfiguracja osi X (pobrana z kontrolera)
        if (statInfo.getDeviceConfiguration().find("X") == statInfo.getDeviceConfiguration().end()) {
            TLINS_LOG_ERROR("No configuration for X");
            return false;
        }

        auto& devCfg = statInfo.getDeviceConfiguration()["X"];

        if (mode == Mode::ASTRO) {
            // Astro - wspolrzedne astronomiczne
            double AxD = (cfg.getDouble(TlinsAstroBase::tlinsConfiguration::RAMP_PARAMETER_GROUP, TlinsAstroBase::tlinsConfiguration::RAMP_PARAMETER_ASTRO_RA_A) / 24.0) * static_cast<double>(devCfg.get_deviceResolution());
            Ax = static_cast<long>(AxD);
            double DxD = (cfg.getDouble(TlinsAstroBase::tlinsConfiguration::RAMP_PARAMETER_GROUP, TlinsAstroBase::tlinsConfiguration::RAMP_PARAMETER_ASTRO_RA_D) / 360.0) * static_cast<double>(devCfg.get_deviceResolution());
            Dx = static_cast<long>(DxD);
        } else if (mode == Mode::DEGRIS) {
            // Stopnie
            Ax = static_cast<long>((cfg.getDouble(TlinsAstroBase::tlinsConfiguration::RAMP_PARAMETER_GROUP,
                                        TlinsAstroBase::tlinsConfiguration::RAMP_PARAMETER_DEGRIS_X_A)
                                       / 360.0)
                * static_cast<double>(devCfg.get_deviceResolution()));
            Dx = static_cast<long>((cfg.getDouble(TlinsAstroBase::tlinsConfiguration::RAMP_PARAMETER_GROUP,
                                        TlinsAstroBase::tlinsConfiguration::RAMP_PARAMETER_DEGRIS_X_D)
                                       / 360.0)
                * static_cast<double>(devCfg.get_deviceResolution()));
        } else {
            // Kroki
            Ax = cfg.getInt(TlinsAstroBase::tlinsConfiguration::RAMP_PARAMETER_GROUP,
                TlinsAstroBase::tlinsConfiguration::RAMP_PARAMETER_STEPS_X_A);
            Dx = cfg.getInt(TlinsAstroBase::tlinsConfiguration::RAMP_PARAMETER_GROUP,
                TlinsAstroBase::tlinsConfiguration::RAMP_PARAMETER_STEPS_X_D);
        }
    }

    if (a == Axis::AxisY || a == Axis::AxisXY) {
        // Konfiguracja osi Y
        auto& statInfo = TlinsAstroBase::tlinsServerStatusInfo::getInstance();
        if (statInfo.getDeviceConfiguration().find("Y") == statInfo.getDeviceConfiguration().end()) {
            TLINS_LOG_ERROR("No configuration for Y");
            return false;
        }

        auto& devCfg = statInfo.getDeviceConfiguration()["Y"];

        if (mode == Mode::ASTRO) {
            // Astro - wspolrzedne astronomiczne
            double AyD = (cfg.getDouble(TlinsAstroBase::tlinsConfiguration::RAMP_PARAMETER_GROUP, TlinsAstroBase::tlinsConfiguration::RAMP_PARAMETER_ASTRO_DC_A) / 24.0) * static_cast<double>(devCfg.get_deviceResolution());
            Ay = static_cast<long>(AyD);
            double DyD = (cfg.getDouble(TlinsAstroBase::tlinsConfiguration::RAMP_PARAMETER_GROUP, TlinsAstroBase::tlinsConfiguration::RAMP_PARAMETER_ASTRO_DC_D) / 360.0) * static_cast<double>(devCfg.get_deviceResolution());
            Dy = static_cast<long>(DyD);
        } else if (mode == Mode::DEGRIS) {
            // Stopnie
            Ay = static_cast<long>((cfg.getDouble(TlinsAstroBase::tlinsConfiguration::RAMP_PARAMETER_GROUP,
                                        TlinsAstroBase::tlinsConfiguration::RAMP_PARAMETER_DEGRIS_Y_A)
                                       / 360.0)
                * static_cast<double>(devCfg.get_deviceResolution()));
            Dy = static_cast<long>((cfg.getDouble(TlinsAstroBase::tlinsConfiguration::RAMP_PARAMETER_GROUP,
                                        TlinsAstroBase::tlinsConfiguration::RAMP_PARAMETER_DEGRIS_Y_D)
                                       / 360.0)
                * static_cast<double>(devCfg.get_deviceResolution()));
        } else {
            // Kroki
            Ay = cfg.getInt(TlinsAstroBase::tlinsConfiguration::RAMP_PARAMETER_GROUP,
                TlinsAstroBase::tlinsConfiguration::RAMP_PARAMETER_STEPS_X_A);
            Dy = cfg.getInt(TlinsAstroBase::tlinsConfiguration::RAMP_PARAMETER_GROUP,
                TlinsAstroBase::tlinsConfiguration::RAMP_PARAMETER_STEPS_X_D);
        }
    }

    //
    // Tworzenie rzadania przemieszczenia
    //
    moveReq = std::move(std::unique_ptr<tlinsMoveServerInterface::MoveRequestDevice> { new tlinsMoveServerInterface::MoveRequestDevice {} });
    moveReq->set_A(interA);
    moveReq->set_D(interD);
    moveReq->set_V(0);

    if (a == Axis::AxisXY) {
        // Tryb interpolowany
        moveReq->set_A(interA);
        moveReq->set_D(interD);
        moveReq->set_V(0);
    }

    if (a == Axis::AxisX || a == Axis::AxisXY) {
        auto& items = moveReq->getRequestItems();

        // Parametery rampy
        auto& item = items["X"];
        item.set_A(Ax);
        item.set_D(Dx);
        item.set_V(0);
        item.set_distance(0);
        item.set_direction(tlinsMoveServerInterface::RequestDirection::LEFT);
    }

    if (a == Axis::AxisY || a == Axis::AxisXY) {
        auto& items = moveReq->getRequestItems();

        // Parametery rampy
        auto& item = items["Y"];
        item.set_A(Ay);
        item.set_D(Dy);
        item.set_V(0);
        item.set_distance(0);
        item.set_direction(tlinsMoveServerInterface::RequestDirection::LEFT);
    }

    moveReq->set_relAbs(tlinsMoveServerInterface::ModeRelAbs::ABS);

    if (isAbort)
        moveReq->set_moveType(tlinsMoveServerInterface::MoveType::ABORT);
    else
        moveReq->set_moveType(tlinsMoveServerInterface::MoveType::STOP);

    // Brak interpolacji
    moveReq->set_interpolationType(tlinsMoveServerInterface::InterpolationType::NONE);

    return true;
}

//
// Przemieszczenie w trybie astro typu SPEED
// Generacja przemieszczenia bedzie odbywala sie w nastepuyjacych krokach
// 0. Zostanie zatrzymane sledzenie obiektow (jesli jestesmy w trybie regularnym)
// 1. Przestawienie kontrolera silnikow w tryb asynchroniczny jesli jestesmy w trybie regularnym
// 2. Wygenerowanie zadania przemieszczenia w trybie predkosc
// ....
// 3. W momencie konczenia zatrzymania wystelane bedzie rzadanie zatrzymania wskazanej osi
// 4. Jesli w trybie regularnym kontroler zostanie przelaczony w tryb synchroniczny
// 5. Aktualna pozycja osi zostanie przeliczona na wspolrzedne obuiektu ktopry
//    zostanie oznaczony jako biezacy cel
// 6. Sledzenie zostanie ponownie wlaczone
//

//
// ------------------------------
// Obsluga wcisniecia klawisza
// ------------------------------
//
class tlinsSpeedMoveRequestPress : public TlinsAstroBase::tlinsCommunicationThreadRequest {
private:
    class moveCb : public tlinsMoveServerInterface::tlinsMoveRequestConfirmation {
    private:
    public:
        virtual void process(const tlins::tlinsRpcConfirmationStatus&)
        {
        }

        virtual bool release()
        {
            return true;
        }

        moveCb() = default;
        virtual ~moveCb() = default;
    };

    std::shared_ptr<tlinsMoveServerInterface::tlinsMoveRequestConfirmation> callback;
    std::shared_ptr<TlinsAstroBase::tlinsConnectionContext> connection;
    std::string deviceName;

    // Parametery przemieszczenia
    tlinsAstroBase::Mode mode;
    bool aX;
    bool aY;
    bool isLeftX;
    bool isLeftY;
    long scaleX;
    long scaleXMax;
    long scaleY;
    long scaleYMax;
    bool isAstro;
    bool fullInit;
    bool isTrackingEnabled;

private:
    //
    // Zmiana stanu kontrolera osi
    //
    void executeMotoEngineMode(const bool synchronus)
    {
        if (!synchronus)
            connection->getDevice()->setMoveMode(deviceName, tlinsMoveServerInterface::tlinsSerialDeviceMode::AXIS);
        else
            connection->getDevice()->setMoveMode(deviceName, tlinsMoveServerInterface::tlinsSerialDeviceMode::SYNCHRONISED);
    }

    //
    // Zatrzymanie uruchomienie sledzenia obiektu
    //
    void executeCtrlTracking(const bool stop)
    {
        if (stop)
            connection->getAstro()->stopTracking();
        else
            connection->getAstro()->startTracking();
    }

    void generateMove(const tlinsAstroBase::Axis axis,
        const bool isLeftX, const bool isLeftY,
        const tlinsAstroBase::Mode mode,
        const bool inSpeed,
        std::unique_ptr<tlinsMoveServerInterface::MoveRequestDevice>& moveReq)
    {
        tlinsAstroBase tools {};

        // Tworzenie rzadania
        tools.generateMove3(axis, isLeftX, isLeftY, mode, inSpeed, moveReq, scaleX, scaleY, scaleXMax, scaleYMax);
    }

    void sendMoveRequest(std::unique_ptr<tlinsMoveServerInterface::MoveRequestDevice>& moveReq)
    {
        connection->getDevice()->moveRequest(deviceName, *moveReq, callback);
    }

    void executeSpeedMoveAstro()
    {
        // Okreslenie osi
        tlinsAstroBase::Axis axis = tlinsAstroBase::Axis::AxisX;

        if (aX && aY)
            axis = tlinsAstroBase::Axis::AxisXY;
        else if (aX && !aY)
            axis = tlinsAstroBase::Axis::AxisX;
        else if (!aX && aY)
            axis = tlinsAstroBase::Axis::AxisY;

        // Wejscie w tryb pojedynczych osi
        executeMotoEngineMode(false);

        // Tworzenie zadania przemieszczenia
        std::unique_ptr<tlinsMoveServerInterface::MoveRequestDevice> moveReq;
        generateMove(axis, isLeftX, isLeftY, tlinsAstroBase::Mode::ASTRO, true, moveReq);
        sendMoveRequest(moveReq);
    }

    void executeStandard()
    {
        tlinsAstroBase::Axis axis = tlinsAstroBase::Axis::AxisX;
        if (aX && aY)
            axis = tlinsAstroBase::Axis::AxisXY;
        else if (aX && !aY)
            axis = tlinsAstroBase::Axis::AxisX;
        else if (!aX && aY)
            axis = tlinsAstroBase::Axis::AxisY;

        //
        // Tworzenie zadania przemieszczenia
        //
        std::unique_ptr<tlinsMoveServerInterface::MoveRequestDevice> moveReq;
        generateMove(axis, isLeftX, isLeftY, mode, true, moveReq);
        sendMoveRequest(moveReq);
    }

    void executeAstro()
    {
        if (isTrackingEnabled) {
            // Sledzenie jest wlaczone
            return;
        }

        // Rozpoczecie przemieszczrnia
        executeSpeedMoveAstro();
    }

public:
    virtual void operator()() noexcept
    {
        try {
            if (isAstro)
                executeAstro();
            else
                executeStandard();
        } catch (tlinsInterfaceException& exc) {
            TLINS_LOG_ERROR("Error : " + exc.getErrorMessage());
        }
    }

    virtual std::string name()
    {
        return "tlinsDeviceMode";
    }

    bool isAsynchronuus()
    {
        return false;
    }

    tlinsSpeedMoveRequestPress(const tlinsAstroBase::Mode mode_,
        const bool aX_, const bool aY_,
        const bool isLeftX_, const bool isLeftY_,
        const long scaleX_, const long scaleXMax_,
        const long scaleY_, const long scaleYMax_,
        const bool isAstro_, const bool fullInit_,
        const bool isTrackingEnabled_)
        : mode { mode_ }
        , aX { aX_ }
        , aY { aY_ }
        , isLeftX { isLeftX_ }
        , isLeftY { isLeftY_ }
        , scaleX { scaleX_ }
        , scaleXMax { scaleXMax_ }
        , scaleY { scaleY_ }
        , scaleYMax { scaleYMax_ }
        , isAstro { isAstro_ }
        , fullInit { fullInit_ }
        , isTrackingEnabled { isTrackingEnabled_ }
    {
        if (!TlinsAstroBase::tlinsConnectionsManager::getInstance().hasConnection(std::string { TLINS_CONNECTION_DEFAULT }))
            __THROW__(tlinsException(std::string("No active connection: ") + std::string(TLINS_CONNECTION_DEFAULT), -1));

        // Polaczenie
        connection = TlinsAstroBase::tlinsConnectionsManager::getInstance().getConnection(TLINS_CONNECTION_DEFAULT);

        auto& cfgInst = TlinsAstroBase::tlinsConfiguration::getInstance();
        deviceName = "main";
        if (cfgInst.hasKey(TlinsAstroBase::tlinsConfiguration::COMMON_PARAMETER_GROUP,
                TlinsAstroBase::tlinsConfiguration::COMMON_MAIN_DEVICE_NAME))
            deviceName = cfgInst.getString(TlinsAstroBase::tlinsConfiguration::COMMON_PARAMETER_GROUP,
                TlinsAstroBase::tlinsConfiguration::COMMON_MAIN_DEVICE_NAME);

        // Instancjonowani callbacka potwierdzen
        callback.reset(new moveCb {});
    }

    virtual ~tlinsSpeedMoveRequestPress()
    {
    }
};

//
// ------------------------------
// Obsluga puszczenia klawisza
// ------------------------------
//

class tlinsSpeedMoveRequestRelease : public TlinsAstroBase::tlinsCommunicationThreadRequest {
private:
    std::condition_variable confCv;
    std::mutex confMtx;

    class moveCb : public tlinsMoveServerInterface::tlinsMoveRequestConfirmation {
    private:
        std::condition_variable& confCvPtr;

    public:
        virtual void process(const tlins::tlinsRpcConfirmationStatus&)
        {
            // Potwierdzenie zatrzymania
            confCvPtr.notify_all();
        }

        virtual bool release()
        {
            confCvPtr.notify_all();
            return true;
        }

        moveCb(std::condition_variable& confCvPtr_)
            : confCvPtr { confCvPtr_ }
        {
        }

        virtual ~moveCb() = default;
    };

    std::shared_ptr<tlinsMoveServerInterface::tlinsMoveRequestConfirmation> callback;
    std::shared_ptr<TlinsAstroBase::tlinsConnectionContext> connection;
    tlinsAstroBase::Mode mode;
    std::string deviceName;
    bool completeStop;
    bool isAstro;
    bool aX;
    bool aY;
    bool isTrackingEnabled;

private:
    //
    // Zmiana stanu kontrolera osi
    //
    void executeMotoEngineMode(const bool synchronus)
    {
        if (!synchronus)
            connection->getDevice()->setMoveMode(deviceName, tlinsMoveServerInterface::tlinsSerialDeviceMode::AXIS);
        else
            connection->getDevice()->setMoveMode(deviceName, tlinsMoveServerInterface::tlinsSerialDeviceMode::SYNCHRONISED);
    }

    //
    // Zatrzymanie uruchomienie sledzenia obiektu
    //
    void executeCtrlTracking(const bool stop)
    {
        if (stop)
            connection->getAstro()->stopTracking();
        else
            connection->getAstro()->startTracking();
    }

    void generateMove(const tlinsAstroBase::Axis axis,
        const tlinsAstroBase::Mode mode,
        std::unique_ptr<tlinsMoveServerInterface::MoveRequestDevice>& moveReq)
    {
        tlinsAstroBase tools {};
        tools.createStopRequest(axis, mode, moveReq, false);
    }

    void sendMoveRequest(std::unique_ptr<tlinsMoveServerInterface::MoveRequestDevice>& moveReq)
    {
        connection->getDevice()->moveRequest(deviceName, *moveReq, callback);
    }

    void setCurtrentPositionAsTarhget()
    {
        connection->getAstro()->setTargetForCurrentPosition();
    }

    void executeStopAstro()
    {
        // Okreslenie osi
        tlinsAstroBase::Axis axis = tlinsAstroBase::Axis::AxisX;

        if (aX && aY)
            axis = tlinsAstroBase::Axis::AxisXY;
        else if (aX && !aY)
            axis = tlinsAstroBase::Axis::AxisX;
        else if (!aX && aY)
            axis = tlinsAstroBase::Axis::AxisY;

        //
        // Tworzenie zadania przemieszczenia
        //
        std::unique_ptr<tlinsMoveServerInterface::MoveRequestDevice> moveReq;
        generateMove(axis, tlinsAstroBase::Mode::ASTRO, moveReq);
        sendMoveRequest(moveReq);
    }

    void executeStopStandard()
    {
        tlinsAstroBase::Axis axis = tlinsAstroBase::Axis::AxisX;
        if (aX && aY)
            axis = tlinsAstroBase::Axis::AxisXY;
        else if (aX && !aY)
            axis = tlinsAstroBase::Axis::AxisX;
        else if (!aX && aY)
            axis = tlinsAstroBase::Axis::AxisY;

        //
        // Tworzenie zadania przemieszczenia
        //
        std::unique_ptr<tlinsMoveServerInterface::MoveRequestDevice> moveReq;
        generateMove(axis, mode, moveReq);
        sendMoveRequest(moveReq);
    }

    void executeAstro()
    {
        if (isTrackingEnabled) {
            return;
        }

        // Zatrzymanie osi
        executeStopAstro();

        // Oczekiwanie na potwierdzenie zatrzymania
        // Maksymalnie 1000 milisekund
        {
            std::unique_lock<std::mutex> lock(confMtx);
            confCv.wait_for(lock, std::chrono::milliseconds(1000));
        }

        if (completeStop) {
            // Zmiana trybu kontrolera osi na synchronizowany
            executeMotoEngineMode(true);

            // Ustawienie beizacej pozycji jako cel astro
            setCurtrentPositionAsTarhget();

            // Uruchomienie sledzenia biezacego obiektu
            //            executeCtrlTracking( false );
        }
    }

public:
    virtual void operator()() noexcept
    {
        try {
            if (isAstro)
                executeAstro();
            else
                executeStopStandard();
        } catch (tlinsInterfaceException& exc) {
            TLINS_LOG_ERROR("Error : " + exc.getErrorMessage());
        }
    }

    virtual std::string name()
    {
        return "tlinsDeviceMode";
    }

    bool isAsynchronuus()
    {
        return true;
    }

    tlinsSpeedMoveRequestRelease(const tlinsAstroBase::Mode mode_,
        const bool aX_, const bool aY_,
        const bool isAstro_,
        const bool completeStop_,
        const bool isTrackingEnabled_)
        : mode { mode_ }
        , completeStop { completeStop_ }
        , isAstro { isAstro_ }
        , aX { aX_ }
        , aY { aY_ }
        , isTrackingEnabled { isTrackingEnabled_ }
    {
        if (!TlinsAstroBase::tlinsConnectionsManager::getInstance().hasConnection(std::string { TLINS_CONNECTION_DEFAULT }))
            __THROW__(tlinsException(std::string("No active connection: ") + std::string(TLINS_CONNECTION_DEFAULT), -1));

        // Polaczenie
        connection = TlinsAstroBase::tlinsConnectionsManager::getInstance().getConnection(TLINS_CONNECTION_DEFAULT);

        deviceName = "main";
        auto& cfgInst = TlinsAstroBase::tlinsConfiguration::getInstance();
        if (cfgInst.hasKey(TlinsAstroBase::tlinsConfiguration::COMMON_PARAMETER_GROUP,
                TlinsAstroBase::tlinsConfiguration::COMMON_MAIN_DEVICE_NAME))
            deviceName = cfgInst.getString(TlinsAstroBase::tlinsConfiguration::COMMON_PARAMETER_GROUP,
                TlinsAstroBase::tlinsConfiguration::COMMON_MAIN_DEVICE_NAME);

        // Instancjonowani callbacka potwierdzen
        callback.reset(new moveCb { confCv });
    }

    virtual ~tlinsSpeedMoveRequestRelease()
    {
    }
};

//
// ------------------------------
// ------------------------------
// ------------------------------
//
void tlinsAstroBase::speedRequestMove(const bool aX, const bool aY, const bool isLeftX, const bool isLeftY,
    const long scaleX, const long scaleXMax, const long scaleY, const long scaleYMax,
    const bool isAstro, const bool fullInit,
    const tlinsAstroBase::Mode mode,
    const bool isTrackingEnabled)
{
    auto& threadInst = TlinsAstroBase::tlinsCommunicationThread::getInstance();
    auto reqPtr = new tlinsSpeedMoveRequestPress(mode,
        aX, aY,
        isLeftX, isLeftY,
        scaleX, scaleXMax,
        scaleY, scaleYMax,
        isAstro, fullInit,
        isTrackingEnabled);
    auto ptr = std::unique_ptr<TlinsAstroBase::tlinsCommunicationThreadRequest>(reqPtr);
    threadInst.push(ptr);
}

void tlinsAstroBase::speedRequestMoveRelease(const bool aX, const bool aY,
    const bool isAstro, const bool completeStop,
    const tlinsAstroBase::Mode mode,
    const bool isTrackingEnabled)
{
    auto& threadInst = TlinsAstroBase::tlinsCommunicationThread::getInstance();
    auto reqPtr = new tlinsSpeedMoveRequestRelease(mode,
        aX, aY,
        isAstro, completeStop,
        isTrackingEnabled);
    auto ptr = std::unique_ptr<TlinsAstroBase::tlinsCommunicationThreadRequest>(reqPtr);
    threadInst.push(ptr);
}

tlinsAstroBase::tlinsAstroBase()
{
    // Odczyt z konfiguracji wartosci domyslnych pilota
    auto& cfg = tlinsConfiguration::getInstance();

    velStepX = cfg.getDouble(tlinsConfiguration::PILOT_PARAMETER_GROUP, tlinsConfiguration::PILOT_PARAMETER_STEPS_X_V);
    disStepX = cfg.getDouble(tlinsConfiguration::PILOT_PARAMETER_GROUP, tlinsConfiguration::PILOT_PARAMETER_STEPS_X);

    velStepY = cfg.getDouble(tlinsConfiguration::PILOT_PARAMETER_GROUP, tlinsConfiguration::PILOT_PARAMETER_STEPS_Y_V);
    disStepY = cfg.getDouble(tlinsConfiguration::PILOT_PARAMETER_GROUP, tlinsConfiguration::PILOT_PARAMETER_STEPS_Y);

    velDegX = cfg.getDouble(tlinsConfiguration::PILOT_PARAMETER_GROUP, tlinsConfiguration::PILOT_PARAMETER_DEGRIS_X_V);
    disDegX = cfg.getDouble(tlinsConfiguration::PILOT_PARAMETER_GROUP, tlinsConfiguration::PILOT_PARAMETER_DEGRIS_X);

    velDegY = cfg.getDouble(tlinsConfiguration::PILOT_PARAMETER_GROUP, tlinsConfiguration::PILOT_PARAMETER_DEGRIS_Y_V);
    disDegY = cfg.getDouble(tlinsConfiguration::PILOT_PARAMETER_GROUP, tlinsConfiguration::PILOT_PARAMETER_DEGRIS_Y);

    velRA = cfg.getDouble(tlinsConfiguration::PILOT_PARAMETER_GROUP, tlinsConfiguration::PILOT_PARAMETER_ASTRO_RA_V);
    disRA = cfg.getDouble(tlinsConfiguration::PILOT_PARAMETER_GROUP, tlinsConfiguration::PILOT_PARAMETER_ASTRO_RA);

    velDC = cfg.getDouble(tlinsConfiguration::PILOT_PARAMETER_GROUP, tlinsConfiguration::PILOT_PARAMETER_ASTRO_DC_V);
    disDC = cfg.getDouble(tlinsConfiguration::PILOT_PARAMETER_GROUP, tlinsConfiguration::PILOT_PARAMETER_ASTRO_DC);
}

// ------------------------------
// ------------------------------
// ------------------------------
class tlinsDistanceMoveRequestPress : public TlinsAstroBase::tlinsCommunicationThreadRequest {
private:
    class moveCb : public tlinsMoveServerInterface::tlinsMoveRequestConfirmation {
    private:
    public:
        virtual void process(const tlins::tlinsRpcConfirmationStatus&)
        {
        }

        virtual bool release()
        {
        }

        moveCb() = default;
        virtual ~moveCb() = default;
    };

    bool aX;
    bool aY;
    bool isAstro;

    // W przypadku przemieszczenia kontowego lub astro wartosc
    // jest w radiuanch
    double distanceX;
    double distanceY;
    double vX;
    double vY;
    tlinsAstroBase::Mode mode;

    std::shared_ptr<tlinsMoveServerInterface::tlinsMoveRequestConfirmation> callback;
    std::shared_ptr<TlinsAstroBase::tlinsConnectionContext> connection;
    std::string deviceName;

    void executeAstro()
    {
        if (!aX && !aY) {
            return;
        }

        // Pobranie aktualnego celu
        tlinsAstroEngineInterface::tlinsTarget target;
        connection->getAstro()->getTarget(target);

        // Wygenerowanie przemieszczenia
        auto& object = target.get_object();

        auto& ra = object.get_hourAngle();
        auto& dc = object.get_declination();

        // Koordynaty
        // - RA
        auto ra_sign = ra.get_sign();
        auto ra_hours = ra.get_degris();
        auto ra_minutes = ra.get_minutes();
        auto ra_seconds = ra.get_seconds();

        double tRA = static_cast<double>(ra_hours) + static_cast<double>(ra_minutes) / 60.0 + ra_seconds / 3600.0;

        // - DC
        auto dc_sign = dc.get_sign();
        auto dc_degris = dc.get_degris();
        auto dc_minutes = dc.get_minutes();
        auto dc_seconds = dc.get_seconds();

        double tDC = static_cast<double>(dc_degris) + static_cast<double>(dc_minutes) / 60.0 + dc_seconds / 3600.0;
        tDC *= dc_sign ? -1.0 : 1.0;

        // Przeliczenie na godziny i stopnie
        double dRA = distanceX;
        double dDC = distanceY;

        // Wygenerowanie zmiany
        //
        // -- Os Ra
        //
        if (aX) {
            tRA += dRA;

            // Normalizacja pozycji
            while (tRA >= 24.0)
                tRA -= 24.0;

            while (tRA < 0.0)
                tRA += 24.0;
        }

        //
        // -- Os Dc
        //
        if (aY) {
            tDC += dDC;

            while (tDC > 360.0)
                tDC -= 360.0;

            while (tDC < -360.0)
                tDC += 360.0;

            if (tDC >= 0.0) {
                if (tDC <= 90.0) {
                    // I
                    // Nic nie robimy
                } else if (tDC <= 180.0) {
                    // II
                    tRA += 12.0;
                    tDC -= 90.0;
                } else if (tDC <= 270.0) {
                    // III
                    tRA += 12;
                    tDC = (tDC - 180.0) * -1.0;
                } else {
                    // IV
                    tDC = (tDC - 270.0) * -1.0;
                }
            } else {
                if (tDC >= -90.0) {
                    // IV
                } else if (tDC >= -180) {
                    // III
                    tDC += 90.0;
                    tRA += 12;
                } else if (tDC >= -270) {
                    // II
                    tDC = (tDC + 180.0) * -1.0;
                    tRA += 12.0;
                } else {
                    // I
                    tDC *= -1;
                }
            }
            while (tRA >= 24.0)
                tRA -= 24.0;
        }

        // Tworzenie rzadania
        {
            tlinsAstroEngineInterface::tlinsTarget newTarget {};
            tlinsAstroEngineInterface::tlinsAstroObject astroObj {};

            astroObj.set_parallax(0.0);
            astroObj.set_properMotionRA(0.0);
            astroObj.set_properMotionDC(0.0);
            astroObj.set_radialVelocity(0.0);
            astroObj.set_catalogType(std::string { "" });

            int raH;
            int raM;
            double raS;
            bool raSign;
            TlinsAstroBase::tlinsAstroBaseUtils::splitRA(tRA, raH, raM, raS, raSign);
            tlinsAstroEngineInterface::tlinsCoordinate raV {};
            raV.set_degris(raH);
            raV.set_minutes(raM);
            raV.set_seconds(raS);
            raV.set_sign(raSign);

            int dcD;
            int dcM;
            double dcS;
            bool dcSign;
            TlinsAstroBase::tlinsAstroBaseUtils::splitDegris(tDC, dcD, dcM, dcS, dcSign);
            tlinsAstroEngineInterface::tlinsCoordinate dcV {};
            dcV.set_degris(dcD);
            dcV.set_minutes(dcM);
            dcV.set_seconds(dcS);
            dcV.set_sign(dcSign);

            astroObj.set_hourAngle(raV);
            astroObj.set_declination(dcV);

            newTarget.set_speed(target.get_speed());
            newTarget.set_delta(0);
            newTarget.set_aceleration(0.0);
            newTarget.set_object(astroObj);

            connection->getAstro()->setTarget(newTarget);
        }
    }

    void executeStandardSteps()
    {
        bool isLeftX { false };
        bool isLeftY { false };
        long X = 0;
        long Y = 0;
        tlinsAstroBase utils {};
        TlinsAstroBase::tlinsAstroBase::Axis axis { TlinsAstroBase::tlinsAstroBase::Axis::AxisX };
        std::unique_ptr<tlinsMoveServerInterface::MoveRequestDevice> moveReq;

        // Okreslenie osi dla ktorej bedzie wygenerowane przemieszczenie
        if (aX) {
            // Os X.
            if (distanceX < 0.0) {
                X = static_cast<long>(distanceX * -1.0);
            } else {
                X = static_cast<long>(distanceX);
            }

            isLeftX = distanceX < 0.0 ? true : false;
            axis = TlinsAstroBase::tlinsAstroBase::Axis::AxisX;
        } else if (aY) {
            // Os Y.
            if (distanceX < 0.0) {
                Y = static_cast<long>(distanceY * -1.0);
            } else {
                Y = static_cast<long>(distanceY);
            }

            isLeftY = distanceY < 0.0 ? true : false;
            axis = TlinsAstroBase::tlinsAstroBase::Axis::AxisY;
        } else if (aY && aX) {
            // Obie osie
            if (distanceX < 0.0) {
                X = static_cast<long>(distanceX * -1.0);
            } else {
                X = static_cast<long>(distanceX);
            }

            if (distanceX < 0.0) {
                Y = static_cast<long>(distanceY * -1.0);
            } else {
                Y = static_cast<long>(distanceY);
            }

            isLeftX = distanceX < 0.0 ? true : false;
            isLeftY = distanceY < 0.0 ? true : false;
            axis = TlinsAstroBase::tlinsAstroBase::Axis::AxisXY;
        } else {
            // Nic nie robimy
            return;
        }

        // Parametery przemieszczenia
        utils.setValueSteps(static_cast<double>(X), static_cast<double>(Y), vX, vY);

        // Tworzenie rzadania
        utils.generateMove3(axis,
            isLeftX,
            isLeftY,
            TlinsAstroBase::tlinsAstroBase::Mode::STEPS,
            false,
            moveReq);

        sendMoveRequest(moveReq);
    }

    void sendMoveRequest(std::unique_ptr<tlinsMoveServerInterface::MoveRequestDevice>& moveReq)
    {
        connection->getDevice()->moveRequest(deviceName, *moveReq, callback);
    }

    void executeStandardDegris()
    {
        bool isLeftX { false };
        bool isLeftY { false };

        tlinsAstroBase utils {};
        TlinsAstroBase::tlinsAstroBase::Axis axis { TlinsAstroBase::tlinsAstroBase::Axis::AxisX };
        std::unique_ptr<tlinsMoveServerInterface::MoveRequestDevice> moveReq;

        // Okreslenie osi dla ktorej bedzie wygenerowane przemieszczenie
        if (aX) {
            // Os X.
            isLeftX = distanceX < 0.0 ? true : false;
            axis = TlinsAstroBase::tlinsAstroBase::Axis::AxisX;
        } else if (aY) {
            // Os Y.
            isLeftY = distanceY < 0.0 ? true : false;
            axis = TlinsAstroBase::tlinsAstroBase::Axis::AxisY;
        } else if (aY && aX) {
            // Obie osie
            isLeftX = distanceX < 0.0 ? true : false;
            isLeftY = distanceY < 0.0 ? true : false;
            axis = TlinsAstroBase::tlinsAstroBase::Axis::AxisXY;
        } else {
            // Nic nie robimy
            return;
        }

        // Parametery przemieszczenia
        utils.setValueDegris(distanceX < 0.0 ? distanceX * -1.0 : distanceX,
            distanceY < 0.0 ? distanceY * -1.0 : distanceY, vX, vY);

        // Tworzenie rzadania
        utils.generateMove3(axis,
            isLeftX,
            isLeftY,
            TlinsAstroBase::tlinsAstroBase::Mode::DEGRIS,
            false,
            moveReq);
        sendMoveRequest(moveReq);
    }

    void executeStandard()
    {
        switch (mode) {
        case tlinsAstroBase::Mode::STEPS:
            executeStandardSteps();
            break;

        case tlinsAstroBase::Mode::DEGRIS:
            executeStandardDegris();
            break;

        default:
            return;
        }
    }

public:
    virtual void operator()() noexcept
    {
        try {
            if (isAstro) {
                executeAstro();
            } else {
                executeStandard();
            }
        } catch (tlinsInterfaceException& exc) {
            TLINS_LOG_ERROR("Error : " + exc.getErrorMessage());
        }
    }

    virtual std::string name()
    {
        return "tlinsDeviceDistanceMoveRequest";
    }

    bool isAsynchronuus()
    {
        return false;
    }

    tlinsDistanceMoveRequestPress(const bool aX_,
        const bool aY_,
        const bool isAstro_,
        const double distanceX_, // Wartosc przemieszczenia w OSI X
        // Gdy < 0.0 lewo, gdy >= 0.0 w prawo
        const double distanceY_, // Wartosc przemieszczenia w OSI Y
        // Gdy < 0.0 gora, gdy >= 0.0 w dol
        const double vX_,
        const double vY_,
        const tlinsAstroBase::Mode mode_)
    {
        aX = aX_;
        aY = aY_;
        vX = vX_;
        vY = vY_;
        isAstro = isAstro_;
        distanceX = distanceX_;
        distanceY = distanceY_;
        mode = mode_;

        // Polaczenie
        if (!TlinsAstroBase::tlinsConnectionsManager::getInstance().hasConnection(std::string { TLINS_CONNECTION_DEFAULT }))
            __THROW__(tlinsException(std::string("No active connection: ") + std::string(TLINS_CONNECTION_DEFAULT), -1));

        // Polaczenie
        connection = TlinsAstroBase::tlinsConnectionsManager::getInstance().getConnection(TLINS_CONNECTION_DEFAULT);

        auto& cfgInst = TlinsAstroBase::tlinsConfiguration::getInstance();

        deviceName = "main";
        if (cfgInst.hasKey(TlinsAstroBase::tlinsConfiguration::COMMON_PARAMETER_GROUP,
                TlinsAstroBase::tlinsConfiguration::COMMON_MAIN_DEVICE_NAME))
            deviceName = cfgInst.getString(TlinsAstroBase::tlinsConfiguration::COMMON_PARAMETER_GROUP,
                TlinsAstroBase::tlinsConfiguration::COMMON_MAIN_DEVICE_NAME);

        // Instancjonowani callbacka potwierdzen
        callback.reset(new moveCb {});
    }
};

void tlinsAstroBase::distanceRequestMove(const bool aX_,
    const bool aY_,
    const bool inAstro_,
    const double distanceX_, // Wartosc przemieszczenia w OSI X
    // Gdy < 0.0 lewo, gdy >= 0.0 w prawo
    const double distanceY_, // Wartosc przemieszczenia w OSI Y
    // Gdy < 0.0 gora, gdy >= 0.0 w dol
    const double vX_,
    const double vY_,
    const tlinsAstroBase::Mode mode_)
{
    auto& threadInst = TlinsAstroBase::tlinsCommunicationThread::getInstance();
    auto reqPtr = new tlinsDistanceMoveRequestPress(aX_, aY_, inAstro_, distanceX_, distanceY_, vX_, vY_, mode_);
    auto ptr = std::unique_ptr<TlinsAstroBase::tlinsCommunicationThreadRequest>(reqPtr);
    threadInst.push(ptr);
}

//
// -------------------------------------------------
// -------------------------------------------------
// -------------------------------------------------
//
class tlinsTrackingCtrlStopStart : public TlinsAstroBase::tlinsCommunicationThreadRequest {
private:
    std::shared_ptr<TlinsAstroBase::tlinsConnectionContext> connection;
    std::shared_ptr<tlinsMoveServerInterface::tlinsMoveRequestConfirmation> callback;
    bool stop;
    bool noSynch;
    bool enable;
    std::string deviceName;

    class moveCb : public tlinsMoveServerInterface::tlinsMoveRequestConfirmation {
    public:
        virtual void process(const tlins::tlinsRpcConfirmationStatus&)
        {
        }

        virtual bool release()
        {
            return true;
        }

        moveCb() = default;
        virtual ~moveCb() = default;
    };

public:
    virtual void operator()() noexcept
    {
        try {
            if (!enable) {
                // Zatrzymanie sledzenia
                connection->getAstro()->stopTracking();

                // Zatrzymanie osi
                if (stop) {
                    tlinsAstroBase instance {};
                    std::unique_ptr<tlinsMoveServerInterface::MoveRequestDevice> moveReq;
                    instance.createStopRequest(tlinsAstroBase::Axis::AxisXY,
                        tlinsAstroBase::Mode::ASTRO,
                        moveReq,
                        true /*false*/);
                    connection->getDevice()->moveRequest(deviceName, *moveReq, callback);
                }

                // Wlaczenie niesynchronicznego sterowania osiami
                if (noSynch) {
                    connection->getDevice()->setMoveMode(deviceName, tlinsMoveServerInterface::tlinsSerialDeviceMode::AXIS);
                }
            } else {
                // Przelaczenie w tryb synchronicznych osi
                if (!noSynch) {
                    connection->getDevice()->setMoveMode(deviceName, tlinsMoveServerInterface::tlinsSerialDeviceMode::SYNCHRONISED);
                }

                // Uruchomienie sledzenia
                connection->getAstro()->startTracking();
            }
        } catch (tlinsInterfaceException& exc) {
            TLINS_LOG_ERROR("Error : " + exc.getErrorMessage());
        }
    }

    virtual std::string name()
    {
        return "tlinsTrackingCtrlStart";
    }

    bool isAsynchronuus()
    {
        return false;
    }

    tlinsTrackingCtrlStopStart(const bool enable_, const bool stop_, const bool noSynch_)
        : stop { stop_ }
        , noSynch { noSynch_ }
        , enable { enable_ }
    {
        if (!TlinsAstroBase::tlinsConnectionsManager::getInstance().hasConnection(std::string { TLINS_CONNECTION_DEFAULT }))
            __THROW__(tlinsException(std::string("No active connection: ") + std::string(TLINS_CONNECTION_DEFAULT), -1));

        // Polaczenie
        connection = TlinsAstroBase::tlinsConnectionsManager::getInstance().getConnection(TLINS_CONNECTION_DEFAULT);

        auto& cfgInst = TlinsAstroBase::tlinsConfiguration::getInstance();
        deviceName = "main";
        if (cfgInst.hasKey(TlinsAstroBase::tlinsConfiguration::COMMON_PARAMETER_GROUP,
                TlinsAstroBase::tlinsConfiguration::COMMON_MAIN_DEVICE_NAME))
            deviceName = cfgInst.getString(TlinsAstroBase::tlinsConfiguration::COMMON_PARAMETER_GROUP,
                TlinsAstroBase::tlinsConfiguration::COMMON_MAIN_DEVICE_NAME);

        // Instancjonowani callbacka potwierdzen
        callback.reset(new moveCb {});
    }

    virtual ~tlinsTrackingCtrlStopStart() = default;
};

void tlinsAstroBase::trackingStop(const bool stop, const bool noSynch)
{
    auto& threadInst = TlinsAstroBase::tlinsCommunicationThread::getInstance();
    auto reqPtr = new tlinsTrackingCtrlStopStart(false, stop, noSynch);
    auto ptr = std::unique_ptr<TlinsAstroBase::tlinsCommunicationThreadRequest>(reqPtr);
    threadInst.push(ptr);
}

void tlinsAstroBase::trackingSart(const bool noSynch)
{
    auto& threadInst = TlinsAstroBase::tlinsCommunicationThread::getInstance();
    auto reqPtr = new tlinsTrackingCtrlStopStart(true, false, noSynch);
    auto ptr = std::unique_ptr<TlinsAstroBase::tlinsCommunicationThreadRequest>(reqPtr);
    threadInst.push(ptr);
}

//
// ------------------------------------
// ------------------------------------
// ------------------------------------
//
class tlinsReadAstroStateSychronus : public TlinsAstroBase::tlinsCommunicationThreadRequest {
private:
    std::shared_ptr<TlinsAstroBase::tlinsConnectionContext> connection;
    std::condition_variable& cv;
    std::mutex& mtx;
    std::atomic<bool>& astroState;
    std::atomic<bool>& trackingState;
    bool& confirmed;

public:
    virtual void operator()() noexcept
    {
        try {
            tlinsAstroEngineInterface::tlinsCalibrarionStateInfo state;
            connection->getAstro()->getCalibrationState(state);
            astroState = state.get_engineState() == tlinsAstroEngineInterface::tlinsEngineStateValue::STATE_REGULAR;
            trackingState = state.get_isTrackingActive();
        } catch (tlinsInterfaceException& exc) {
            TLINS_LOG_ERROR("Error : " + exc.getErrorMessage());
        }

        {
            std::unique_lock<std::mutex> lock(mtx);
            confirmed = true;
        }
        cv.notify_all();
    }

    virtual std::string name()
    {
        return "tlinsReadAstroStateSychronus";
    }

    bool isAsynchronuus()
    {
        return false;
    }

    tlinsReadAstroStateSychronus(std::condition_variable& cv_,
        std::atomic<bool>& astroState_,
        std::atomic<bool>& trackingState_,
        bool& confirmed_,
        std::mutex& mtx_)
        : cv { cv_ }
        , mtx { mtx_ }
        , astroState { astroState_ }
        , trackingState { trackingState_ }
        , confirmed { confirmed_ }
    {
        confirmed = false;
        if (!TlinsAstroBase::tlinsConnectionsManager::getInstance().hasConnection(std::string { TLINS_CONNECTION_DEFAULT }))
            __THROW__(tlinsException(std::string("No active connection: ") + std::string(TLINS_CONNECTION_DEFAULT), -1));

        // Polaczenie
        connection = TlinsAstroBase::tlinsConnectionsManager::getInstance().getConnection(TLINS_CONNECTION_DEFAULT);
    }

    virtual ~tlinsReadAstroStateSychronus() = default;
};

void tlinsAstroBase::getAstroStaetInfo(bool& state_, bool& trackingStatet_)
{
    std::condition_variable cv;
    std::mutex mtx;
    std::atomic<bool> astroState;
    std::atomic<bool> trackingState;
    bool confirmed { false };

    auto& threadInst = TlinsAstroBase::tlinsCommunicationThread::getInstance();
    auto reqPtr = new tlinsReadAstroStateSychronus(cv, astroState, trackingState, confirmed, mtx);
    auto ptr = std::unique_ptr<TlinsAstroBase::tlinsCommunicationThreadRequest>(reqPtr);
    threadInst.push(ptr);

    std::unique_lock<std::mutex> lock(mtx);
    cv.wait(lock, [&confirmed]() {
        return confirmed;
    });

    state_ = astroState;
    trackingStatet_ = trackingState;
}

}
