#include "tlinssettingswindow.h"
#include "ui_tlinssettingswindow.h"

#include <QMessageBox>

tlinsSettingsWindow::tlinsSettingsWindow(QWidget* parent)
    : QDialog(parent)
    , ui(new Ui::tlinsSettingsWindow)
{
    ui->setupUi(this);
}

tlinsSettingsWindow::~tlinsSettingsWindow()
{
    delete ui;
}
