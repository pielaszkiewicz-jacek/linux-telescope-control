#include "tlinswpilothvspeeddelta.h"
#include "ui_tlinswpilothvspeeddelta.h"

#include <tlinsBacktrace.hpp>
#include <tlinsuiexception.h>

enum class Axis {
    H = 1,
    V = 2
};

enum class TYPE {
    STEPS = 1,
    DEGRIS = 2
};

void tlinsWPilotHVSpeedDelta::degrisSelected()
{
    ui->groupDegris->setVisible(true);
    ui->groupSteps->setVisible(false);
}

void tlinsWPilotHVSpeedDelta::stepsSelected()
{
    ui->groupDegris->setVisible(false);
    ui->groupSteps->setVisible(true);
}

void tlinsWPilotHVSpeedDelta::setParameters(const QJsonObject& doc)
{
    Axis a = Axis::H;
    TYPE type = TYPE::STEPS;
    double stepsValue = 0.0;
    double degrisValue = 0.0;

    {
        QJsonValue v = doc["type"];
        if (!v.isString()) {
            // Przekazana wartosc nie jest typu double
            __THROW__(TlinsAstroBase::tlinsUIException(TlinsAstroBase::tlinsUIException::ERROR_INVALID_PARAMETER, "Parameter value is not string"));
        }

        QString val = v.toString();
        if (val.toUpper() == "STEPS")
            type = TYPE::STEPS;
        else if (val.toUpper() == "DEGRIS")
            type = TYPE::DEGRIS;
    }

    {
        QJsonValue v = doc["axis"];
        if (!v.isString()) {
            // Przekazana wartosc nie jest typu double
            __THROW__(TlinsAstroBase::tlinsUIException(TlinsAstroBase::tlinsUIException::ERROR_INVALID_PARAMETER, "Parameter value is not double"));
        }

        QString val = v.toString();

        if (val.toUpper() == "HORISONTAL")
            a = Axis::H;
        else if (val.toUpper() == "VERTICAL")
            a = Axis::V;
    }

    if (type == TYPE::STEPS) {
        QJsonValue v = doc["value-steps"];
        if (!v.isDouble()) {
            // Przekazana wartosc nie jest typu double
            __THROW__(TlinsAstroBase::tlinsUIException(TlinsAstroBase::tlinsUIException::ERROR_INVALID_PARAMETER, "Parameter value-steps is not double"));
        }
        stepsValue = v.toDouble();
    } else {
        QJsonValue v = doc["value-degris"];
        if (!v.isDouble()) {
            // Przekazana wartosc nie jest typu double
            __THROW__(TlinsAstroBase::tlinsUIException(TlinsAstroBase::tlinsUIException::ERROR_INVALID_PARAMETER, "Parameter value is not double"));
        }
        degrisValue = v.toDouble();
    }

    // Modyfikacja UI
    {
        if (type == TYPE::STEPS) {
            // W krokach
            ui->groupDegris->setVisible(false);
            ui->groupSteps->setVisible(true);
            ui->stepsValue->setValue(stepsValue);

            ui->radioSteps->setChecked(true);
            ui->radioDegris->setChecked(false);

            ui->stepsValue->setValue(stepsValue);
        } else {
            // W stopniach
            ui->groupDegris->setVisible(true);
            ui->groupSteps->setVisible(false);
            ui->degrisValue->setValue(degrisValue);

            ui->radioSteps->setChecked(false);
            ui->radioDegris->setChecked(true);

            ui->degrisValue->setValue(degrisValue);
        }

        if (a == Axis::H) {
            ui->radioHorisontal->setChecked(true);
            ui->radioVertical->setChecked(false);
        } else {
            ui->radioHorisontal->setChecked(false);
            ui->radioVertical->setChecked(true);
        }
    }
}

void tlinsWPilotHVSpeedDelta::getParameters(QJsonObject& doc)
{
    // Os
    doc.insert("type", ui->radioSteps->isChecked() ? QString { "steps" } : QString { "degris" });
    doc.insert("axis", ui->radioHorisontal->isChecked() ? QString { "horisontal" } : QString { "vertical" });

    if (ui->radioSteps->isChecked()) {
        // W krokach
        doc.insert("value-steps", ui->stepsValue->getValue());
        doc.insert("value-degris", 0.0);
    } else {
        // W stopniach
        doc.insert("value-steps", 0.0);
        doc.insert("value-degris", ui->degrisValue->getValue());
    }
}

QWidget* tlinsWPilotHVSpeedDelta::getWidget()
{
    return this;
}

void tlinsWPilotHVSpeedDelta::reset()
{
    ui->groupDegris->setVisible(false);
    ui->groupSteps->setVisible(false);

    ui->radioDegris->setChecked(false);
    ui->radioSteps->setChecked(false);
    ui->radioHorisontal->setChecked(true);
    ui->radioVertical->setChecked(false);
}

TlinsAstroBase::tlinsPilotShortcutsDefinitionValidMode tlinsWPilotHVSpeedDelta::getValidMode()
{
    return TlinsAstroBase::tlinsPilotShortcutsDefinitionValidMode::DEVICE;
}

tlinsWPilotHVSpeedDelta::tlinsWPilotHVSpeedDelta(QWidget* parent)
    : QWidget(parent)
    , ui(new Ui::tlinsWPilotHVSpeedDelta)
{
    ui->setupUi(this);

    ui->stepsValue->setDecimal(0);

    ui->groupDegris->setVisible(false);
    ui->groupSteps->setVisible(false);

    ui->radioDegris->setChecked(false);
    ui->radioSteps->setChecked(false);
    ui->radioHorisontal->setChecked(true);
    ui->radioVertical->setChecked(false);
}

tlinsWPilotHVSpeedDelta::~tlinsWPilotHVSpeedDelta()
{
    delete ui;
}
