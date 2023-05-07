#include "tlinswpilotclosecalibration.h"
#include "ui_tlinswpilotclosecalibration.h"

void tlinsWPilotCloseCalibration::setParameters(const QJsonObject&)
{
}

void tlinsWPilotCloseCalibration::getParameters(QJsonObject&)
{
}

QWidget* tlinsWPilotCloseCalibration::getWidget()
{
    return this;
}

void tlinsWPilotCloseCalibration::reset()
{
}

TlinsAstroBase::tlinsPilotShortcutsDefinitionValidMode tlinsWPilotCloseCalibration::getValidMode()
{
    return TlinsAstroBase::tlinsPilotShortcutsDefinitionValidMode::BOTH;
}

tlinsWPilotCloseCalibration::tlinsWPilotCloseCalibration(QWidget* parent)
    : QWidget(parent)
    , ui(new Ui::tlinsWPilotCloseCalibration)
{
    ui->setupUi(this);
}

tlinsWPilotCloseCalibration::~tlinsWPilotCloseCalibration()
{
    delete ui;
}
