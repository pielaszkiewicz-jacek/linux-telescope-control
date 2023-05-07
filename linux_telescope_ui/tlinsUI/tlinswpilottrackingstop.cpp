#include "tlinswpilottrackingstop.h"
#include "ui_tlinswpilottrackingstop.h"

void tlinsWPilotTrackingStop::setParameters(const QJsonObject&)
{
}

void tlinsWPilotTrackingStop::getParameters(QJsonObject&)
{
}

QWidget* tlinsWPilotTrackingStop::getWidget()
{
    return this;
}

void tlinsWPilotTrackingStop::reset()
{
}

tlinsWPilotTrackingStop::tlinsWPilotTrackingStop(QWidget* parent)
    : QWidget(parent)
    , ui(new Ui::tlinsWPilotTrackingStop)
{
    ui->setupUi(this);
}

tlinsWPilotTrackingStop::~tlinsWPilotTrackingStop()
{
    delete ui;
}
