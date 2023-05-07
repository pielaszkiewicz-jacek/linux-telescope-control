#include "tlinswpilotstartresetcalibration.h"
#include "ui_tlinswpilotstartresetcalibration.h"

void tlinsWPilotStartResetCalibration::setParameters(const QJsonObject&)
{
}

void tlinsWPilotStartResetCalibration::getParameters(QJsonObject&)
{
}

QWidget* tlinsWPilotStartResetCalibration::getWidget()
{
    return this;
}

void tlinsWPilotStartResetCalibration::reset()
{
}

TlinsAstroBase::tlinsPilotShortcutsDefinitionValidMode tlinsWPilotStartResetCalibration::getValidMode()
{
    return TlinsAstroBase::tlinsPilotShortcutsDefinitionValidMode::DEVICE;
}

tlinsWPilotStartResetCalibration::tlinsWPilotStartResetCalibration(QWidget* parent)
    : QWidget(parent)
    , ui(new Ui::tlinsWPilotStartResetCalibration)
{
    ui->setupUi(this);
}

tlinsWPilotStartResetCalibration::~tlinsWPilotStartResetCalibration()
{
    delete ui;
}
