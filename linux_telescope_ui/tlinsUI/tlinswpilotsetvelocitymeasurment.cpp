#include "tlinswpilotsetvelocitymeasurment.h"
#include "ui_tlinswpilotsetvelocitymeasurment.h"

void tlinsWPilotSetVelocityMeasurment::setParameters(const QJsonObject&)
{
}

void tlinsWPilotSetVelocityMeasurment::getParameters(QJsonObject&)
{
}

QWidget* tlinsWPilotSetVelocityMeasurment::getWidget()
{
    return this;
}

void tlinsWPilotSetVelocityMeasurment::reset()
{
}

TlinsAstroBase::tlinsPilotShortcutsDefinitionValidMode tlinsWPilotSetVelocityMeasurment::getValidMode()
{
    return TlinsAstroBase::tlinsPilotShortcutsDefinitionValidMode::DEVICE;
}

tlinsWPilotSetVelocityMeasurment::tlinsWPilotSetVelocityMeasurment(QWidget* parent)
    : QWidget(parent)
    , ui(new Ui::tlinsWPilotSetVelocityMeasurment)
{
    ui->setupUi(this);
}

tlinsWPilotSetVelocityMeasurment::~tlinsWPilotSetVelocityMeasurment()
{
    delete ui;
}
