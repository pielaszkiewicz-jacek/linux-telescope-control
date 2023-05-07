#include "tlinswpilothorisintalverticalincrement.h"
#include "ui_tlinswpilothorisintalverticalincrement.h"
#include <tlinsBacktrace.hpp>
#include <tlinsuiexception.h>

void tlinsWPilotHorisintalVerticalIncrement::setParameters(const QJsonObject& doc)
{
}

void tlinsWPilotHorisintalVerticalIncrement::getParameters(QJsonObject& doc)
{
}

QWidget* tlinsWPilotHorisintalVerticalIncrement::getWidget()
{
    return this;
}

void tlinsWPilotHorisintalVerticalIncrement::reset()
{
}

TlinsAstroBase::tlinsPilotShortcutsDefinitionValidMode tlinsWPilotHorisintalVerticalIncrement::getValidMode()
{
    return TlinsAstroBase::tlinsPilotShortcutsDefinitionValidMode::BOTH;
}

tlinsWPilotHorisintalVerticalIncrement::tlinsWPilotHorisintalVerticalIncrement(QWidget* parent)
    : QWidget(parent)
    , ui(new Ui::tlinsWPilotHorisintalVerticalIncrement)
{
    ui->setupUi(this);
}

tlinsWPilotHorisintalVerticalIncrement::~tlinsWPilotHorisintalVerticalIncrement()
{
    delete ui;
}
