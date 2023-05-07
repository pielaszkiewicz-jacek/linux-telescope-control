#include "tlinswobservationerror.h"
#include "ui_tlinswobservationerror.h"

tlinsWObservationError::tlinsWObservationError(QWidget* parent)
    : QWidget(parent)
    , ui(new Ui::tlinsWObservationError)
{
    ui->setupUi(this);
    ui->weight->setDecimal(5);
    ui->weight->disableButtons();
}

tlinsWObservationError::~tlinsWObservationError()
{
    delete ui;
}

void tlinsWObservationError::setLongitudeError(const double v)
{
    ui->longitudeError->setValue(v);
}

void tlinsWObservationError::setLatitudeError(const double v)
{
    ui->latitudeError->setValue(v);
}

void tlinsWObservationError::setWeight(const double v)
{
    ui->weight->setValue(v);
}

double tlinsWObservationError::getLongitudeError()
{
    return ui->longitudeError->getValue();
}

double tlinsWObservationError::getLatitudeError()
{
    return ui->latitudeError->getValue();
}
double tlinsWObservationError::getWeight()
{
    return ui->weight->getValue();
}
