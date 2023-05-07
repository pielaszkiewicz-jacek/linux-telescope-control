#include "tlinspilotshortcutsdefinitionswindow.h"
#include "ui_tlinspilotshortcutsdefinitionswindow.h"

tlinsPilotShortcutsDefinitionsWindow::tlinsPilotShortcutsDefinitionsWindow(QWidget* parent)
    : QDialog(parent)
    , ui(new Ui::tlinsPilotShortcutsDefinitionsWindow)
{
    ui->setupUi(this);
}

tlinsPilotShortcutsDefinitionsWindow::~tlinsPilotShortcutsDefinitionsWindow()
{
    delete ui;
}
