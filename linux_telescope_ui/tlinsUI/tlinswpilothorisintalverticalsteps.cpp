#include "tlinswpilothorisintalverticalsteps.h"
#include "ui_tlinswpilothorisintalverticalsteps.h"
#include <tlinsBacktrace.hpp>
#include <tlinsuiexception.h>

/*
  {
     "axis":"X",
     "mode":"steps"|"degris"|"astro"
     "direction":"left"|"right"
  }
 */

void tlinsWPilotHorisintalVerticalSteps::setParameters(const QJsonObject& doc)
{
    //    Axis a = Axis:: H;
    //    Direction dir = Direction:: LEFT;

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

    QString mode;
    {
        //
        // Kierunek obrotu
        //
        QJsonValue v = doc["mode"];
        if (!v.isString()) {
            // Przekazana wartosc nie jest typu double
            __THROW__(TlinsAstroBase::tlinsUIException(TlinsAstroBase::tlinsUIException::ERROR_INVALID_PARAMETER, "Parameter value is not a string"));
        }

        QString val = v.toString();
        if (val.toUpper() == "STEPS")
            mode = "S";
        else if (val.toUpper() == "DEGRIS")
            mode = "D";
        else if (val.toUpper() == "ASTRO")
            mode = "A";
    }

    // Kierunek
    if (dir == "L") {
        ui->radioDirLeft->setChecked(true);
        ui->radioDirRight->setChecked(false);
    } else {
        ui->radioDirRight->setChecked(true);
        ui->radioDirLeft->setChecked(false);
    }

    // Tryb
    if (mode == "S") {
        ui->radioModeSteps->setChecked(true);
        ui->radioModeDegris->setChecked(false);
        ui->radioModeAstro->setChecked(false);
    } else if (mode == "D") {
        ui->radioModeSteps->setChecked(false);
        ui->radioModeDegris->setChecked(true);
        ui->radioModeAstro->setChecked(false);
    } else {
        ui->radioModeSteps->setChecked(false);
        ui->radioModeDegris->setChecked(false);
        ui->radioModeAstro->setChecked(true);
    }

    // Os
    if (a == "X") {
        ui->radioHorisontal->setChecked(true);
        ui->radioVertical->setChecked(false);
    } else {
        ui->radioHorisontal->setChecked(false);
        ui->radioVertical->setChecked(true);
    }
}

TlinsAstroBase::tlinsPilotShortcutsDefinitionValidMode tlinsWPilotHorisintalVerticalSteps::getValidMode()
{
    return TlinsAstroBase::tlinsPilotShortcutsDefinitionValidMode::BOTH;
}

void tlinsWPilotHorisintalVerticalSteps::getParameters(QJsonObject& doc)
{
    QString a;
    if (ui->radioHorisontal->isChecked())
        a = "X";
    else if (ui->radioVertical->isChecked())
        a = "Y";

    QString mode;
    if (ui->radioModeSteps->isChecked())
        mode = "steps";
    else if (ui->radioModeDegris->isChecked())
        mode = "degris";
    else if (ui->radioModeAstro->isChecked())
        mode = "astro";

    QString dir;
    if (ui->radioDirLeft->isChecked())
        dir = "left";
    else if (ui->radioDirRight->isChecked())
        dir = "right";

    doc.insert("axis", a);
    doc.insert("mode", mode);
    doc.insert("direction", dir);
}

QWidget* tlinsWPilotHorisintalVerticalSteps::getWidget()
{
    return this;
}

void tlinsWPilotHorisintalVerticalSteps::reset()
{
    ui->radioDirLeft->setChecked(false);
    ui->radioDirRight->setChecked(false);

    ui->radioModeSteps->setChecked(false);
    ui->radioModeDegris->setChecked(false);
    ui->radioModeAstro->setChecked(false);

    ui->radioHorisontal->setChecked(false);
    ui->radioVertical->setChecked(false);
}

tlinsWPilotHorisintalVerticalSteps::tlinsWPilotHorisintalVerticalSteps(QWidget* parent)
    : QWidget(parent)
    , ui(new Ui::tlinsWPilotHorisintalVerticalSteps)
{
    ui->setupUi(this);

    reset();
}

tlinsWPilotHorisintalVerticalSteps::~tlinsWPilotHorisintalVerticalSteps()
{
    delete ui;
}
