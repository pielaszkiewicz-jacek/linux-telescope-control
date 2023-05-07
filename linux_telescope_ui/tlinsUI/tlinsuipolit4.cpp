#include "tlinsuipolit4.h"
#include "tlinscommunicationthread.h"
#include "tlinsconfiguration.h"
#include "tlinsconnection.h"
#include "tlinsserverstatusinfo.h"
#include "tlinsuiutils.h"
#include "tlinsupdatestatemanager.h"
#include "tlinsvalueabstract.h"
#include "ui_tlinsuipolit4.h"
#include <QMessageBox>
#include <QSettings>
#include <tlinsAstroEngineInterface.hpp>
#include <tlinsAstroObject.hpp>
#include <tlinsBacktrace.hpp>
#include <tlinsCoordinate.hpp>
#include <tlinsException.hpp>
#include <tlinsLogger.hpp>
#include <tlinsastrouibase.h>

void tlinsUiPolit4::keyPressEvent(QKeyEvent* ev)
{
    switch (ev->key()) {
    case Qt::Key_Up:
        upClicked();
        break;

    case Qt::Key_Down:
        downClicked();
        break;

    case Qt::Key_Left:
        leftClicked();
        break;

    case Qt::Key_Right:
        rightClicked();
        break;
    }
}

void tlinsUiPolit4::keyReleaseEvent(QKeyEvent* ev)
{
    switch (ev->key()) {
    case Qt::Key_Up:
        upRelised();
        break;

    case Qt::Key_Down:
        downRelised();
        break;

    case Qt::Key_Left:
        leftRelised();
        break;

    case Qt::Key_Right:
        rightRelised();
        break;
    }
}

tlinsUiPolit4::tlinsUiPolit4(QWidget* parent)
    : QWidget(parent)
    , ui(new Ui::tlinsUiPolit4)
{
    statusChangeCbId = -1;

    ui->setupUi(this);

    connect(ui->inSteps, SIGNAL(stateChanged(int)), this, SLOT(onInStepChange(int)));
    connect(ui->speedMode, SIGNAL(stateChanged(int)), this, SLOT(onSpeedMode(int)));
    connect(ui->bUp, SIGNAL(pressed()), this, SLOT(upClicked()));
    connect(ui->bUp, SIGNAL(released()), this, SLOT(upRelised()));
    connect(ui->bDown, SIGNAL(pressed()), this, SLOT(downClicked()));
    connect(ui->bDown, SIGNAL(released()), this, SLOT(downRelised()));
    connect(ui->bLeft, SIGNAL(pressed()), this, SLOT(leftClicked()));
    connect(ui->bLeft, SIGNAL(released()), this, SLOT(leftRelised()));
    connect(ui->bRight, SIGNAL(pressed()), this, SLOT(rightClicked()));
    connect(ui->bRight, SIGNAL(released()), this, SLOT(rightRelised()));
    connect(ui->bStop, SIGNAL(pressed()), this, SLOT(stopPressed()));
    connect(ui->bAbort, SIGNAL(pressed()), this, SLOT(abortPressed()));
    connect(this, SIGNAL(setSignlMode(const displayMode)), this, SLOT(setModeSlot(const displayMode)), Qt::BlockingQueuedConnection);

    sAbort = new QShortcut(QKeySequence(Qt::CTRL + Qt::Key_A), this);
    connect(sAbort, SIGNAL(activated()), this, SLOT(abortPressed()));

    sStop = new QShortcut(QKeySequence(Qt::CTRL + Qt::Key_S), this);
    connect(sStop, SIGNAL(activated()), this, SLOT(stopPressed()));

    setFocusPolicy(Qt::StrongFocus);

    inSpeed = false;
    inDegris = true;
    mode = displayMode::DEGRIS;

    ui->Sx->setDecimal(0);
    ui->Sy->setDecimal(0);
    ui->VSx->setDecimal(0);
    ui->VSy->setDecimal(0);

    ui->inSteps->setChecked(false);

    //
    // Rejestrowanie sie w managerze na zmiane status
    //
    auto& mgrIns = TlinsAstroBase::tlinsUpdateStateManager<tlinsAstroEngineInterface::tlinsEngineStateValue>::getInstance();
    auto updateState = [this](const tlinsAstroEngineInterface::tlinsEngineStateValue& s) {
        if (s == tlinsAstroEngineInterface::tlinsEngineStateValue::STATE_REGULAR) {
            // Teleskop jest po kalibracji
            emit this->setSignlMode(displayMode::ASTRO);
        } else {
            // Teleskop jest w trybie kalibracji
            if (this->ui->inSteps->isEnabled())
                emit this->setSignlMode(displayMode::STEPS);
            else
                emit this->setSignlMode(displayMode::DEGRIS);
        }
    };
    statusChangeCbId = mgrIns.registerObject(UPDATE_CATEGORY_ASTRO_STATUS, updateState);

    // Ustawienie domyslnego trybu pracy
    setMode(mode);
}

void tlinsUiPolit4::setModeSlot(const displayMode m)
{
    mode = m;
    setMode(mode);
}

//
// -------------------------------
// -------------------------------
//
class tlinsPilotMoveRequest : public TlinsAstroBase::tlinsCommunicationThreadRequest {
private:
    class moveCb : public tlinsMoveServerInterface::tlinsMoveRequestConfirmation {
    private:
        tlinsPilotMoveRequest& parent;

    public:
        void process(const tlins::tlinsRpcConfirmationStatus& status);
        bool release();

        moveCb(tlinsPilotMoveRequest& parent_)
            : parent { parent_ }
        {
        }

        virtual ~moveCb()
        {
        }
    };

    std::shared_ptr<tlinsMoveServerInterface::tlinsMoveRequestConfirmation> callback;
    std::shared_ptr<TlinsAstroBase::tlinsConnectionContext> connection;

private:
    std::unique_ptr<tlinsMoveServerInterface::MoveRequestDevice> request;

public:
    void confirm();

    virtual void operator()() noexcept;
    virtual bool isAsynchronuus();
    virtual std::string name()
    {
        return "tlinsPilotMoveRequest";
    }

    tlinsPilotMoveRequest(std::unique_ptr<tlinsMoveServerInterface::MoveRequestDevice>& ptr);
    virtual ~tlinsPilotMoveRequest();
};

void tlinsPilotMoveRequest::moveCb::process(const tlins::tlinsRpcConfirmationStatus&)
{
    parent.confirm();
}

bool tlinsPilotMoveRequest::moveCb::release()
{
    return true;
}

void tlinsPilotMoveRequest::confirm()
{
    TlinsAstroBase::tlinsCommunicationThreadRequest::confirm();
}

void tlinsPilotMoveRequest::operator()() noexcept
{
    try {
        // Nazwa urzadzenia glownego
        std::string mainDeviceName = "main";
        auto& cfg = TlinsAstroBase::tlinsConfiguration::getInstance();

        if (cfg.hasKey(TlinsAstroBase::tlinsConfiguration::COMMON_PARAMETER_GROUP,
                TlinsAstroBase::tlinsConfiguration::COMMON_MAIN_DEVICE_NAME))
            mainDeviceName = cfg.getString(TlinsAstroBase::tlinsConfiguration::COMMON_PARAMETER_GROUP,
                TlinsAstroBase::tlinsConfiguration::COMMON_MAIN_DEVICE_NAME);

        // Uruchomienie zapytania
        connection->getDevice()->moveRequest(mainDeviceName, *request, callback);
    } catch (tlinsInterfaceException&) {
        // Mamy blad wywolania nie bedzie potwierdzenia asynchronicznego
        confirm();
        return;
    }
}

bool tlinsPilotMoveRequest::isAsynchronuus()
{
    return true;
}

tlinsPilotMoveRequest::tlinsPilotMoveRequest(std::unique_ptr<tlinsMoveServerInterface::MoveRequestDevice>& ptr)
    : request { std::move(ptr) }
{
    // Pobranie polaczenia
    if (!TlinsAstroBase::tlinsConnectionsManager::getInstance().hasConnection(std::string { TLINS_CONNECTION_DEFAULT }))
        __THROW__(tlinsException(std::string("No active connection: ") + std::string(TLINS_CONNECTION_DEFAULT), -1));

    // Polaczenie
    connection = TlinsAstroBase::tlinsConnectionsManager::getInstance().getConnection(TLINS_CONNECTION_DEFAULT);

    // Obiekt potwierdzen
    callback.reset(new moveCb { *this });
}

tlinsPilotMoveRequest::~tlinsPilotMoveRequest()
{
    connection.reset();
}

//
// -------------------------------
// -------------------------------
//

class tlinsPilotAstroMoveRequest : public TlinsAstroBase::tlinsCommunicationThreadRequest {
private:
    std::shared_ptr<TlinsAstroBase::tlinsConnectionContext> connection;

private:
    std::unique_ptr<tlinsAstroEngineInterface::tlinsTarget> request;

public:
    virtual void operator()() noexcept;
    virtual bool isAsynchronuus();

    virtual std::string name()
    {
        return "tlinsAstroMoveRequest";
    }

    tlinsPilotAstroMoveRequest(std::unique_ptr<tlinsAstroEngineInterface::tlinsTarget>& ptr);
    virtual ~tlinsPilotAstroMoveRequest();
};

void tlinsPilotAstroMoveRequest::operator()() noexcept
{
    try {
        // Uruchomienie zapytania
        connection->getAstro()->setTarget(*request);
    } catch (tlinsInterfaceException&) {
    }
}

bool tlinsPilotAstroMoveRequest::isAsynchronuus()
{
    return false;
}

tlinsPilotAstroMoveRequest::tlinsPilotAstroMoveRequest(std::unique_ptr<tlinsAstroEngineInterface::tlinsTarget>& ptr)
    : request { std::move(ptr) }
{
    // Pobranie polaczenia
    if (!TlinsAstroBase::tlinsConnectionsManager::getInstance().hasConnection(std::string { TLINS_CONNECTION_DEFAULT }))
        __THROW__(tlinsException(std::string("No active connection: ") + std::string(TLINS_CONNECTION_DEFAULT), -1));

    // Polaczenie
    connection = TlinsAstroBase::tlinsConnectionsManager::getInstance().getConnection(TLINS_CONNECTION_DEFAULT);
}

tlinsPilotAstroMoveRequest::~tlinsPilotAstroMoveRequest()
{
}

//
// -------------------------------
// -------------------------------
//

class tlinsSetTargetForPosition : public TlinsAstroBase::tlinsCommunicationThreadRequest {
private:
    std::shared_ptr<TlinsAstroBase::tlinsConnectionContext> connection;

public:
    virtual void operator()() noexcept
    {
        try {
            connection->getAstro()->setTargetForCurrentPosition();
        } catch (tlinsInterfaceException& exc) {
            TLINS_LOG_ERROR("Error : " + exc.getErrorMessage());
        }
    }

    bool isAsynchronuus()
    {
        return false;
    }

    virtual std::string name()
    {
        return "tlinsSetTargetForPosition";
    }

    tlinsSetTargetForPosition()
    {
        // Pobranie polaczenia
        if (!TlinsAstroBase::tlinsConnectionsManager::getInstance().hasConnection(std::string { TLINS_CONNECTION_DEFAULT }))
            __THROW__(tlinsException(std::string("No active connection: ") + std::string(TLINS_CONNECTION_DEFAULT), -1));

        // Polaczenie
        connection = TlinsAstroBase::tlinsConnectionsManager::getInstance().getConnection(TLINS_CONNECTION_DEFAULT);
    }

    virtual ~tlinsSetTargetForPosition()
    {
    }
};

class tlinsDeviceMode : public TlinsAstroBase::tlinsCommunicationThreadRequest {
private:
    std::shared_ptr<TlinsAstroBase::tlinsConnectionContext> connection;
    std::string deviceName;
    bool axis;

public:
    virtual void operator()() noexcept
    {
        try {
            if (axis)
                connection->getDevice()->setMoveMode(deviceName, tlinsMoveServerInterface::tlinsSerialDeviceMode::AXIS);
            else
                connection->getDevice()->setMoveMode(deviceName, tlinsMoveServerInterface::tlinsSerialDeviceMode::SYNCHRONISED);
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

    tlinsDeviceMode(const bool axis_)
        : axis { axis_ }
    {
        // Pobranie polaczenia
        if (!TlinsAstroBase::tlinsConnectionsManager::getInstance().hasConnection(std::string { TLINS_CONNECTION_DEFAULT }))
            __THROW__(tlinsException(std::string("No active connection: ") + std::string(TLINS_CONNECTION_DEFAULT), -1));

        // Polaczenie
        connection = TlinsAstroBase::tlinsConnectionsManager::getInstance().getConnection(TLINS_CONNECTION_DEFAULT);

        auto& cfgInst = TlinsAstroBase::tlinsConfiguration::getInstance();
        deviceName = cfgInst.getString(TlinsAstroBase::tlinsConfiguration::COMMON_PARAMETER_GROUP,
            TlinsAstroBase::tlinsConfiguration::COMMON_MAIN_DEVICE_NAME);
    }

    virtual ~tlinsDeviceMode()
    {
    }
};

void tlinsUiPolit4::setDeviceMode(bool axis)
{
    auto& tInst = TlinsAstroBase::tlinsCommunicationThread::getInstance();
    auto ptr = std::unique_ptr<TlinsAstroBase::tlinsCommunicationThreadRequest>(new tlinsDeviceMode(axis));
    tInst.push(ptr);
}

bool tlinsUiPolit4::createStopRequest(const __Axis__ a,
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
    if (a == __Axis__::__X__ || a == __Axis__::__XY__) {
        // Konfiguracja osi X (pobrana z kontrolera)
        if (statInfo.getDeviceConfiguration().find("X") == statInfo.getDeviceConfiguration().end()) {
            TLINS_LOG_ERROR("No configuration for X");
            return false;
        }

        auto& devCfg = statInfo.getDeviceConfiguration()["X"];

        if (mode == displayMode::ASTRO) {
            // Astro - wspolrzedne astronomiczne
            double AxD = (cfg.getDouble(TlinsAstroBase::tlinsConfiguration::RAMP_PARAMETER_GROUP, TlinsAstroBase::tlinsConfiguration::RAMP_PARAMETER_ASTRO_RA_A) / 24.0) * static_cast<double>(devCfg.get_deviceResolution());
            Ax = static_cast<long>(AxD);
            double DxD = (cfg.getDouble(TlinsAstroBase::tlinsConfiguration::RAMP_PARAMETER_GROUP, TlinsAstroBase::tlinsConfiguration::RAMP_PARAMETER_ASTRO_RA_D) / 360.0) * static_cast<double>(devCfg.get_deviceResolution());
            Dx = static_cast<long>(DxD);
        } else if (mode == displayMode::DEGRIS) {
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

    if (a == __Axis__::__Y__ || a == __Axis__::__XY__) {
        // Konfiguracja osi Y
        auto& statInfo = TlinsAstroBase::tlinsServerStatusInfo::getInstance();
        if (statInfo.getDeviceConfiguration().find("Y") == statInfo.getDeviceConfiguration().end()) {
            TLINS_LOG_ERROR("No configuration for Y");
            return false;
        }

        auto& devCfg = statInfo.getDeviceConfiguration()["Y"];

        if (mode == displayMode::ASTRO) {
            // Astro - wspolrzedne astronomiczne
            double AyD = (cfg.getDouble(TlinsAstroBase::tlinsConfiguration::RAMP_PARAMETER_GROUP, TlinsAstroBase::tlinsConfiguration::RAMP_PARAMETER_ASTRO_DC_A) / 24.0) * static_cast<double>(devCfg.get_deviceResolution());
            Ay = static_cast<long>(AyD);
            double DyD = (cfg.getDouble(TlinsAstroBase::tlinsConfiguration::RAMP_PARAMETER_GROUP, TlinsAstroBase::tlinsConfiguration::RAMP_PARAMETER_ASTRO_DC_D) / 360.0) * static_cast<double>(devCfg.get_deviceResolution());
            Dy = static_cast<long>(DyD);
        } else if (mode == displayMode::DEGRIS) {
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

    if (a == __Axis__::__XY__) {
        // Tryb interpolowany
        moveReq->set_A(interA);
        moveReq->set_D(interD);
        moveReq->set_V(0);
    }

    if (a == __Axis__::__X__ || a == __Axis__::__XY__) {
        auto& items = moveReq->getRequestItems();

        // Parametery rampy
        auto& item = items["X"];
        item.set_A(Ax);
        item.set_D(Dx);
        item.set_V(0);
        item.set_distance(0);
        item.set_direction(tlinsMoveServerInterface::RequestDirection::LEFT);
    }

    if (a == __Axis__::__Y__ || a == __Axis__::__XY__) {
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

void tlinsUiPolit4::handleClickedMoveRelease(const bool X, const bool Y)
{
    //
    // Status napedu
    //
    bool isAstro = false;
    bool isTrackingEnabled = false;

    TlinsAstroBase::tlinsAstroBase::getAstroStaetInfo(isAstro, isTrackingEnabled);

    if (ui->speedMode->isChecked()) {
        TlinsAstroBase::tlinsAstroBase::speedRequestMoveRelease(X, Y,
            isAstro, true,
            TlinsAstroBase::tlinsAstroBase::Mode::DEGRIS,
            isTrackingEnabled);
    }
}

void tlinsUiPolit4::handleClickedMove(const bool X, const bool Y, const bool leftX, const bool leftY)
{
    //
    // Status napedu
    //
    bool isAstro = false;
    bool isTrackingEnabled = false;

    TlinsAstroBase::tlinsAstroBase::getAstroStaetInfo(isAstro, isTrackingEnabled);

    if (ui->speedMode->isChecked()) {
        // Tryb predkosci

        TlinsAstroBase::tlinsAstroBase::Mode m;
        long scaleMax = 32767;
        long scaleX = scaleMax;
        long scaleY = scaleMax;
        bool fullInit = true;

        if (isAstro) {
            m = TlinsAstroBase::tlinsAstroBase::Mode::ASTRO;
        } else {
            if (mode == displayMode::STEPS) {
                m = TlinsAstroBase::tlinsAstroBase::Mode::STEPS;
            } else {
                m = TlinsAstroBase::tlinsAstroBase::Mode::DEGRIS;
            }
        }

        // Tryb ciaglego przemieszczebia
        TlinsAstroBase::tlinsAstroBase::speedRequestMove(X, Y, leftX, leftY, scaleX, scaleMax, scaleY, scaleMax, isAstro, fullInit, m, isTrackingEnabled);
    } else {
        // Tryb przemieszczenia

        double vX = 0.0;
        double vY = 0.0;
        double distanceX = 0.0;
        double distanceY = 0.0;
        TlinsAstroBase::tlinsAstroBase::Mode m;

        switch (mode) {
        case displayMode::STEPS:
            vX = static_cast<double>(ui->VSx->getValue());
            vY = static_cast<double>(ui->VSy->getValue());
            distanceX = static_cast<double>(ui->Sx->getValue());
            distanceY = static_cast<double>(ui->Sy->getValue());
            m = TlinsAstroBase::tlinsAstroBase::Mode::STEPS;
            break;

        case displayMode::DEGRIS:
            vX = static_cast<double>(ui->VDx->getValue());
            vY = static_cast<double>(ui->VDy->getValue());
            distanceX = static_cast<double>(ui->Dx->getValue());
            distanceY = static_cast<double>(ui->Dy->getValue());
            m = TlinsAstroBase::tlinsAstroBase::Mode::DEGRIS;
            break;

        case displayMode::ASTRO:

            vX = static_cast<double>(ui->VRa->getValue());
            vY = static_cast<double>(ui->VDc->getValue());
            distanceX = static_cast<double>(ui->RaX->getValue());
            distanceY = static_cast<double>(ui->DcY->getValue());
            m = TlinsAstroBase::tlinsAstroBase::Mode::DEGRIS;
            break;
        }

        TlinsAstroBase::tlinsAstroBase::distanceRequestMove(X, Y,
            isAstro,
            leftX ? distanceX * -1.0 : distanceX,
            leftY ? distanceY * -1.0 : distanceY, vX, vY, m);
    }
}

void tlinsUiPolit4::upClicked()
{
    try {
        handleClickedMove(false, true, false, true);
    } catch (tlinsException& exc) {
        QMessageBox msgBox;
        msgBox.setText(QString::fromStdString(exc.getErrorMessage()));
        msgBox.exec();
    } catch (...) {
        QMessageBox msgBox;
        msgBox.setText("Error");
        msgBox.exec();
    }
}

void tlinsUiPolit4::upRelised()
{
    try {
        handleClickedMoveRelease(false, true);
    } catch (...) {
    }
}

void tlinsUiPolit4::downClicked()
{
    try {
        handleClickedMove(false, true, false, false);
    } catch (tlinsException& exc) {
        QMessageBox msgBox;
        msgBox.setText(QString::fromStdString(exc.getErrorMessage()));
        msgBox.exec();
    } catch (...) {
        QMessageBox msgBox;
        msgBox.setText("Error");
        msgBox.exec();
    }
}

void tlinsUiPolit4::downRelised()
{
    try {
        handleClickedMoveRelease(false, true);
    } catch (...) {
    }
}

void tlinsUiPolit4::leftClicked()
{
    try {
        handleClickedMove(true, false, true, false);
    } catch (tlinsException& exc) {
        QMessageBox msgBox;
        msgBox.setText(QString::fromStdString(exc.getErrorMessage()));
        msgBox.exec();
    } catch (...) {
        QMessageBox msgBox;
        msgBox.setText("Error");
        msgBox.exec();
    }
}

void tlinsUiPolit4::leftRelised()
{
    try {
        handleClickedMoveRelease(true, false);
    } catch (...) {
    }
}

void tlinsUiPolit4::rightClicked()
{
    try {
        handleClickedMove(true, false, false, true);
    } catch (tlinsException& exc) {
        QMessageBox msgBox;
        msgBox.setText(QString::fromStdString(exc.getErrorMessage()));
        msgBox.exec();
    } catch (...) {
        QMessageBox msgBox;
        msgBox.setText("Error");
        msgBox.exec();
    }
}

void tlinsUiPolit4::rightRelised()
{
    try {
        handleClickedMoveRelease(true, false);
    } catch (...) {
    }
}

void tlinsUiPolit4::stopPressed()
{
    std::unique_ptr<tlinsMoveServerInterface::MoveRequestDevice> moveReqest;
    TlinsAstroBase::tlinsAstroBase astroUtilObj;
    TlinsAstroBase::tlinsAstroBase::Mode mode_;

    if (mode == displayMode::ASTRO)
        mode_ = TlinsAstroBase::tlinsAstroBase::Mode::ASTRO;
    else if (mode == displayMode::DEGRIS)
        mode_ = TlinsAstroBase::tlinsAstroBase::Mode::DEGRIS;
    else
        mode_ = TlinsAstroBase::tlinsAstroBase::Mode::STEPS;

    if (!astroUtilObj.createStopRequest(TlinsAstroBase::tlinsAstroBase::Axis::AxisXY,
            mode_,
            moveReqest, false)) {
        QMessageBox msgBox;
        msgBox.setText("Error build move request");
        msgBox.exec();
        return;
    }

    try {
        std::unique_ptr<TlinsAstroBase::tlinsCommunicationThreadRequest> req(new tlinsPilotMoveRequest { moveReqest });
        TlinsAstroBase::tlinsCommunicationThread::getInstance().push(req, true);
    } catch (tlinsException& exc) {
        TLINS_LOG_ERROR("Error: " + exc.getErrorMessage());

        QMessageBox msgBox;
        msgBox.setText(QString::fromStdString("Error: " + exc.getErrorMessage()));
        msgBox.exec();
    }
}

void tlinsUiPolit4::abortPressed()
{
    std::unique_ptr<tlinsMoveServerInterface::MoveRequestDevice> moveReqest;

    TlinsAstroBase::tlinsAstroBase astroUtilObj;
    TlinsAstroBase::tlinsAstroBase::Mode mode_;

    if (mode == displayMode::ASTRO)
        mode_ = TlinsAstroBase::tlinsAstroBase::Mode::ASTRO;
    else if (mode == displayMode::DEGRIS)
        mode_ = TlinsAstroBase::tlinsAstroBase::Mode::DEGRIS;
    else
        mode_ = TlinsAstroBase::tlinsAstroBase::Mode::STEPS;

    if (!astroUtilObj.createStopRequest(TlinsAstroBase::tlinsAstroBase::Axis::AxisXY,
            mode_,
            moveReqest, true)) {
        QMessageBox msgBox;
        msgBox.setText("Error build move request");
        msgBox.exec();
        return;
    }

    try {
        std::unique_ptr<TlinsAstroBase::tlinsCommunicationThreadRequest> req(new tlinsPilotMoveRequest { moveReqest });
        TlinsAstroBase::tlinsCommunicationThread::getInstance().push(req, true);
    } catch (tlinsException& exc) {
        TLINS_LOG_ERROR("Error: " + exc.getErrorMessage());

        QMessageBox msgBox;
        msgBox.setText(QString::fromStdString("Error: " + exc.getErrorMessage()));
        msgBox.exec();
    }
}

void tlinsUiPolit4::setSpeedMode()
{
    if (mode == displayMode::STEPS) {
        ui->Sx->setVisible(!inSpeed);
        ui->Sy->setVisible(!inSpeed);
        ui->ldsx->setVisible(!inSpeed);
        ui->ltdsx->setVisible(!inSpeed);
        ui->ldsy->setVisible(!inSpeed);
        ui->ltdsy->setVisible(!inSpeed);
    }

    if (mode == displayMode::DEGRIS) {
        ui->Dx->setVisible(!inSpeed);
        ui->Dy->setVisible(!inSpeed);
        ui->lddx->setVisible(!inSpeed);
        ui->ltddx->setVisible(!inSpeed);
        ui->lddy->setVisible(!inSpeed);
        ui->ltddy->setVisible(!inSpeed);
    }

    if (mode == displayMode::ASTRO) {
        ui->RaX->setVisible(!inSpeed);
        ui->DcY->setVisible(!inSpeed);
        ui->ldax->setVisible(!inSpeed);
        ui->ltdax->setVisible(!inSpeed);
        ui->lday->setVisible(!inSpeed);
        ui->ltday->setVisible(!inSpeed);
    }
}

void tlinsUiPolit4::onSpeedMode(int state)
{
    bool status = (state == 2 ? false : true);
    inSpeed = !status;
    setSpeedMode();
}

void tlinsUiPolit4::onInStepChange(int state)
{
    if (mode != displayMode::ASTRO) {
        if (state == 2)
            mode = displayMode::STEPS;
        else
            mode = displayMode::DEGRIS;
        setMode(mode);
    }
}

void tlinsUiPolit4::setMode(bool steps,
    bool degris,
    bool astro,
    bool vSteps,
    bool vDegris,
    bool vAstro)
{
    ui->Sx->setVisible(steps);
    ui->Sy->setVisible(steps);
    ui->ldsx->setVisible(steps);
    ui->ltdsx->setVisible(steps);
    ui->ldsy->setVisible(steps);
    ui->ltdsy->setVisible(steps);

    ui->Dx->setVisible(degris);
    ui->Dy->setVisible(degris);
    ui->lddx->setVisible(degris);
    ui->ltddx->setVisible(degris);
    ui->lddy->setVisible(degris);
    ui->ltddy->setVisible(degris);

    ui->RaX->setVisible(astro);
    ui->DcY->setVisible(astro);
    ui->ldax->setVisible(astro);
    ui->ltdax->setVisible(astro);
    ui->lday->setVisible(astro);
    ui->ltday->setVisible(astro);

    ui->VSx->setVisible(vSteps);
    ui->VSy->setVisible(vSteps);
    ui->lvsx->setVisible(vSteps);
    ui->ltvsx->setVisible(vSteps);
    ui->lvsy->setVisible(vSteps);
    ui->ltvsy->setVisible(vSteps);

    ui->VDx->setVisible(vDegris);
    ui->VDy->setVisible(vDegris);
    ui->lvdx->setVisible(vDegris);
    ui->ltvdx->setVisible(vDegris);
    ui->lvdy->setVisible(vDegris);
    ui->ltvdy->setVisible(vDegris);

    ui->VRa->setVisible(vAstro);
    ui->VDc->setVisible(vAstro);
    ui->lvax->setVisible(vAstro);
    ui->lvay->setVisible(vAstro);
    ui->ltvax->setVisible(vAstro);
    ui->ltvay->setVisible(vAstro);

    setSpeedMode();
}

void tlinsUiPolit4::setMode(displayMode mode)
{
    switch (mode) {
    case tlinsUiPolit4::displayMode::STEPS:
        setMode(true, false, false, true, false, false);
        ui->speedMode->setVisible(true);
        ui->inSteps->setVisible(true);
        break;

    case tlinsUiPolit4::displayMode::DEGRIS:
        setMode(false, true, false, false, true, false);
        ui->speedMode->setVisible(true);
        ui->inSteps->setVisible(true);
        break;

    case tlinsUiPolit4::displayMode::ASTRO:
        setMode(false, false, true, false, false, true);
        ui->speedMode->setVisible(true);
        ui->inSteps->setVisible(false);
        inSpeed = false;
        break;
    }
}

tlinsUiPolit4::~tlinsUiPolit4()
{
    delete ui;

    auto& mgrIns = TlinsAstroBase::tlinsUpdateStateManager<tlinsAstroEngineInterface::tlinsEngineStateValue>::getInstance();
    if (statusChangeCbId >= 0)
        mgrIns.unregisterObject(UPDATE_CATEGORY_ASTRO_STATUS, statusChangeCbId);
}
