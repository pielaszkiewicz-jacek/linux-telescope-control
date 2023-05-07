#include "tlinsierswindow.h"
#include "ui_tlinsierswindow.h"

tlinsIERSWindow::tlinsIERSWindow(QWidget* parent)
    : QDialog(parent)
    , ui(new Ui::tlinsIERSWindow)
{
    ui->setupUi(this);
}

tlinsIERSWindow::~tlinsIERSWindow()
{
    delete ui;
}
