#include "tlinswpilotsetreferenceobject.h"
#include "ui_tlinswpilotsetreferenceobject.h"

void tlinsWPilotSetReferenceObject::setParameters(const QJsonObject&)
{
}

void tlinsWPilotSetReferenceObject::getParameters(QJsonObject&)
{
}

QWidget* tlinsWPilotSetReferenceObject::getWidget()
{
    return this;
}

void tlinsWPilotSetReferenceObject::reset()
{
}

TlinsAstroBase::tlinsPilotShortcutsDefinitionValidMode tlinsWPilotSetReferenceObject::getValidMode()
{
    return TlinsAstroBase::tlinsPilotShortcutsDefinitionValidMode::DEVICE;
}

tlinsWPilotSetReferenceObject::tlinsWPilotSetReferenceObject(QWidget* parent)
    : QWidget(parent)
    , ui(new Ui::tlinsWPilotSetReferenceObject)
{
    ui->setupUi(this);
}

tlinsWPilotSetReferenceObject::~tlinsWPilotSetReferenceObject()
{
    delete ui;
}
