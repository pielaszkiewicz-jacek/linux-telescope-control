#include "tlinswenvironment.h"
#include "tlinsenvironment.h"
#include "ui_tlinswenvironment.h"

tlinsWEnvironment::tlinsWEnvironment(QWidget* parent)
    : QWidget(parent)
    , ui(new Ui::tlinsWEnvironment)
{
    ui->setupUi(this);

    auto& ins = tlinsEnvironment::getInstance();

    ui->ambientPressure->setDecimal(5);
    ui->effectiveColor->setDecimal(5);
    ui->realHumidity->setDecimal(5);
    ui->temperature->setDecimal(5);

    ui->ambientPressure->setValue(ins.getAmbientPressure());
    ui->effectiveColor->setValue(ins.getEffectiveColor());
    ui->realHumidity->setValue(ins.getRealHumidity());
    ui->temperature->setValue(ins.getTemperature());
}

double tlinsWEnvironment::getAmbientPressure() const
{
    return ui->ambientPressure->getValue();
}

double tlinsWEnvironment::getEffectiveColor() const
{
    return ui->effectiveColor->getValue();
}

double tlinsWEnvironment::getRealHumidity() const
{
    return ui->realHumidity->getValue();
}

double tlinsWEnvironment::getTemperature() const
{
    return ui->temperature->getValue();
}

tlinsWEnvironment::~tlinsWEnvironment()
{
    delete ui;
}
