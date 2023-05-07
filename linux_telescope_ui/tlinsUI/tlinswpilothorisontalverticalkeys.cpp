#include "tlinswpilothorisontalverticalkeys.h"
#include "ui_tlinswpilothorisontalverticalkeys.h"
#include <tlinsBacktrace.hpp>
#include <tlinsuiexception.h>

/*
  {
     "axis":"X",
     "direction":"left"|"right"
  }

 */
void tlinsWPilotHorisontalVerticalKeys::setParameters(const QJsonObject& doc)
{
    QString a;

    {
        //
        // Os obrotu
        //
        QJsonValue v = doc["axis"];
        if (!v.isString()) {
            // Przekazana wartosc nie jest typu double
            __THROW__(TlinsAstroBase::tlinsUIException(TlinsAstroBase::tlinsUIException::ERROR_INVALID_PARAMETER, "Parameter value is not a string"));
        }

        QString val = v.toString();
        if (val.toUpper() == "X")
            a = "X";
        else if (val.toUpper() == "Y")
            a = "Y";
    }

    QString dir;
    {
        //
        // Kierunek obrotu
        //
        QJsonValue v = doc["direction"];
        if (!v.isString()) {
            // Przekazana wartosc nie jest typu double
            __THROW__(TlinsAstroBase::tlinsUIException(TlinsAstroBase::tlinsUIException::ERROR_INVALID_PARAMETER, "Parameter value is not a string"));
        }

        QString val = v.toString();

        if (val.toUpper() == "RIGHT")
            dir = "R";
        else if (val.toUpper() == "LEFT")
            dir = "L";
    }

    // Kierunek
    if (dir == "L") {
        ui->rbLeftUp->setChecked(true);
        ui->rbRightDown->setChecked(false);
    } else {
        ui->rbLeftUp->setChecked(false);
        ui->rbRightDown->setChecked(true);
    }

    // Os
    if (a == "X") {
        ui->rbHorisintal->setChecked(true);
        ui->rbVertical->setChecked(false);
    } else {
        ui->rbHorisintal->setChecked(false);
        ui->rbVertical->setChecked(true);
    }
}

void tlinsWPilotHorisontalVerticalKeys::getParameters(QJsonObject& doc)
{
    QString dir;
    QString a;

    if (ui->rbHorisintal->isChecked()) {
        a = "X";
    } else if (ui->rbVertical->isChecked()) {
        a = "Y";
    }

    if (ui->rbLeftUp->isChecked()) {
        dir = "left";
    } else if (ui->rbRightDown->isChecked()) {
        dir = "right";
    }

    doc.insert("axis", a);
    doc.insert("direction", dir);
}

QWidget* tlinsWPilotHorisontalVerticalKeys::getWidget()
{
    return this;
}

void tlinsWPilotHorisontalVerticalKeys::reset()
{
    ui->rbHorisintal->setChecked(false);
    ui->rbVertical->setChecked(false);

    ui->rbLeftUp->setChecked(false);
    ui->rbRightDown->setChecked(false);
}

TlinsAstroBase::tlinsPilotShortcutsDefinitionValidMode tlinsWPilotHorisontalVerticalKeys::getValidMode()
{
    return TlinsAstroBase::tlinsPilotShortcutsDefinitionValidMode::BOTH;
}

tlinsWPilotHorisontalVerticalKeys::tlinsWPilotHorisontalVerticalKeys(QWidget* parent)
    : QWidget(parent)
    , ui(new Ui::tlinsWPilotHorisontalVerticalKeys)
{
    ui->setupUi(this);
}

tlinsWPilotHorisontalVerticalKeys::~tlinsWPilotHorisontalVerticalKeys()
{
    delete ui;
}
