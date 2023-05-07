#include "tlinswpilothvdelta.h"
#include "ui_tlinswpilothvdelta.h"

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

void tlinsWPilotHVDelta::degrisSelected()
{
    ui->groupDegris->setVisible(true);
    ui->groupSteps->setVisible(false);
}

void tlinsWPilotHVDelta::stepsSelected()
{
    ui->groupDegris->setVisible(false);
    ui->groupSteps->setVisible(true);
}

void tlinsWPilotHVDelta::setParameters(const QJsonObject& doc)
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
            ui->deltaSteps->setValue(stepsValue);

            ui->radioTypeSteps->setChecked(true);
            ui->radioTypeDegris->setChecked(false);

            ui->deltaSteps->setValue(stepsValue);
        } else {
            // W stopniach
            ui->groupDegris->setVisible(true);
            ui->groupSteps->setVisible(false);
            ui->deltaDegris->setValue(degrisValue);

            ui->radioTypeSteps->setChecked(false);
            ui->radioTypeDegris->setChecked(true);

            ui->deltaDegris->setValue(degrisValue);
        }

        if (a == Axis::H) {
            ui->radioAxisHorisontal->setChecked(true);
            ui->radioAxisVertical->setChecked(false);
        } else {
            ui->radioAxisHorisontal->setChecked(false);
            ui->radioAxisVertical->setChecked(true);
        }
    }
}

void tlinsWPilotHVDelta::getParameters(QJsonObject& doc)
{
    // Os
    doc.insert("type", ui->radioTypeSteps->isChecked() ? QString { "steps" } : QString { "degris" });
    doc.insert("axis", ui->radioAxisHorisontal->isChecked() ? QString { "horisontal" } : QString { "vertical" });

    if (ui->radioTypeSteps->isChecked()) {
        // W krokach
        doc.insert("value-steps", ui->deltaSteps->getValue());
        doc.insert("value-degris", 0.0);
    } else {
        // W stopniach
        doc.insert("value-steps", 0.0);
        doc.insert("value-degris", ui->deltaDegris->getValue());
    }
}

QWidget* tlinsWPilotHVDelta::getWidget()
{
    return this;
}

void tlinsWPilotHVDelta::reset()
{
    ui->groupDegris->setVisible(false);
    ui->groupSteps->setVisible(false);

    ui->radioTypeDegris->setChecked(false);
    ui->radioTypeSteps->setChecked(false);
    ui->radioAxisHorisontal->setChecked(true);
    ui->radioAxisVertical->setChecked(false);
}

TlinsAstroBase::tlinsPilotShortcutsDefinitionValidMode tlinsWPilotHVDelta::getValidMode()
{
    return TlinsAstroBase::tlinsPilotShortcutsDefinitionValidMode::DEVICE;
}

tlinsWPilotHVDelta::tlinsWPilotHVDelta(QWidget* parent)
    : QWidget(parent)
    , ui(new Ui::tlinsWPilotHVDelta)
{
    ui->setupUi(this);
    ui->deltaSteps->setDecimal(0);

    ui->groupDegris->setVisible(false);
    ui->groupSteps->setVisible(false);

    ui->radioTypeDegris->setChecked(false);
    ui->radioTypeSteps->setChecked(false);
    ui->radioAxisHorisontal->setChecked(true);
    ui->radioAxisVertical->setChecked(false);
}

tlinsWPilotHVDelta::~tlinsWPilotHVDelta()
{
    delete ui;
}
