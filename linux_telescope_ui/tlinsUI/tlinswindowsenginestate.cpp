#include "tlinswindowsenginestate.h"
#include "ui_tlinswindowsenginestate.h"
#include <QIcon>

tlinsWindowsEngineState::tlinsWindowsEngineState(QWidget* parent)
    : QDialog(parent)
    , ui(new Ui::tlinsWindowsEngineState)
{
    ui->setupUi(this);
    setWindowTitle("Engine State Managment");
    QIcon icon { ":/icons/state.svg" };
    setWindowIcon(icon);
}

tlinsWindowsEngineState::~tlinsWindowsEngineState()
{
    delete ui;
}
