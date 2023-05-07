#ifndef TLINSWINDOWSENGINESTATE_H
#define TLINSWINDOWSENGINESTATE_H

#include <QDialog>

namespace Ui {
class tlinsWindowsEngineState;
}

class tlinsWindowsEngineState : public QDialog {
    Q_OBJECT

public:
    explicit tlinsWindowsEngineState(QWidget* parent = nullptr);
    ~tlinsWindowsEngineState();

private:
    Ui::tlinsWindowsEngineState* ui;
};

#endif // TLINSWINDOWSENGINESTATE_H
