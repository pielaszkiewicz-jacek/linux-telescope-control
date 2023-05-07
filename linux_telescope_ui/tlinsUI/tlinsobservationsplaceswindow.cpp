#include "tlinsobservationsplaceswindow.h"
#include "ui_tlinsobservationsplaceswindow.h"

tlinsObservationsPlacesWindow::tlinsObservationsPlacesWindow(QWidget* parent)
    : QDialog(parent)
    , ui(new Ui::tlinsObservationsPlacesWindow)
{
    ui->setupUi(this);
}

tlinsObservationsPlacesWindow::~tlinsObservationsPlacesWindow()
{
    delete ui;
}
