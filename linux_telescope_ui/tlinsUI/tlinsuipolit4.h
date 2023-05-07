#ifndef TLINSUIPOLIT4_H
#define TLINSUIPOLIT4_H

#include <QKeyEvent>
#include <QShortcut>
#include <QVBoxLayout>
#include <QWidget>
#include <memory>

#include "tlinswcoordinatedeclination.h"
#include "tlinswcoordinatedegris.h"
#include "tlinswcoordinatehourangle.h"
#include "tlinswdecimalvalue.h"
#include <tlinsAstroEngineInterface.hpp>
#include <tlinsMoveServerInterface.hpp>

namespace Ui {
class tlinsUiPolit4;
}

class tlinsUiPolit4 : public QWidget {
    Q_OBJECT

public:
    enum class displayMode {
        STEPS = 1,
        DEGRIS = 2,
        ASTRO = 3
    };

private:
    void handleClickedMove(const bool X, const bool Y, const bool leftX, const bool leftY);
    void handleClickedMoveRelease(const bool X, const bool Y);

    void keyPressEvent(QKeyEvent* ev);
    void keyReleaseEvent(QKeyEvent* ev);

    QShortcut* sUp;
    QShortcut* sDown;
    QShortcut* sLeft;
    QShortcut* sRight;
    QShortcut* sAbort;
    QShortcut* sStop;

    bool inSpeed;
    int statusChangeCbId;

private:
    QSize noSettingsSize;

public:
    void setMode(displayMode mode);

signals:
    void setSignlMode(displayMode);
    void saveGeometry();
    void restoreGeometry();

public slots:
    void setModeSlot(const displayMode m);

    void onInStepChange(int state);
    void onSpeedMode(int state);

    void upClicked();
    void upRelised();

    void downClicked();
    void downRelised();

    void leftClicked();
    void leftRelised();

    void rightClicked();
    void rightRelised();

    //	void okPressed();
    void stopPressed();
    void abortPressed();

private:
    enum class __Axis__ {
        __X__ = 1,
        __Y__ = 2,
        __XY__ = 3
    };
    bool createStopRequest(const __Axis__ a,
        std::unique_ptr<tlinsMoveServerInterface::MoveRequestDevice>& moveReq,
        const bool isAbort = false);

    void setMode(bool steps, bool degris, bool astro, bool vSteps, bool vDegris, bool vAstro);
    void setSpeedMode();

    void setDeviceMode(bool axis);

private:
    bool inDegris;
    displayMode mode;

public:
    explicit tlinsUiPolit4(QWidget* parent = 0);
    virtual ~tlinsUiPolit4();

private:
    Ui::tlinsUiPolit4* ui;
};

#endif // TLINSUIPOLIT4_H
