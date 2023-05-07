#include "tlinswpilottrackingstart.h"
#include "ui_tlinswpilottrackingstart.h"

void tlinsWPilotTrackingStart::setParameters(const QJsonObject&)
{
}

void tlinsWPilotTrackingStart::getParameters(QJsonObject&)
{
}

QWidget* tlinsWPilotTrackingStart::getWidget()
{
    return this;
}

void tlinsWPilotTrackingStart::reset()
{
}

tlinsWPilotTrackingStart::tlinsWPilotTrackingStart(QWidget* parent)
    : QWidget(parent)
    , ui(new Ui::tlinsWPilotTrackingStart)
{
    ui->setupUi(this);
}

tlinsWPilotTrackingStart::~tlinsWPilotTrackingStart()
{
    delete ui;
}
