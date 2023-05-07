#include "tlinswpilotclosevelocitymeasurment.h"
#include "ui_tlinswpilotclosevelocitymeasurment.h"

void tlinsWPilotCloseVelocityMeasurment::setParameters(const QJsonObject&)
{
}

void tlinsWPilotCloseVelocityMeasurment::getParameters(QJsonObject&)
{
}

QWidget* tlinsWPilotCloseVelocityMeasurment::getWidget()
{
    return this;
}

void tlinsWPilotCloseVelocityMeasurment::reset()
{
}

TlinsAstroBase::tlinsPilotShortcutsDefinitionValidMode tlinsWPilotCloseVelocityMeasurment::getValidMode()
{
    return TlinsAstroBase::tlinsPilotShortcutsDefinitionValidMode::DEVICE;
}

tlinsWPilotCloseVelocityMeasurment::tlinsWPilotCloseVelocityMeasurment(QWidget* parent)
    : QWidget(parent)
    , ui(new Ui::tlinsWPilotCloseVelocityMeasurment)
{
    ui->setupUi(this);
}

tlinsWPilotCloseVelocityMeasurment::~tlinsWPilotCloseVelocityMeasurment()
{
    delete ui;
}
