#include "tlinswpilotradcincrement.h"
#include "ui_tlinswpilotradcincrement.h"

#include <tlinsBacktrace.hpp>
#include <tlinsuiexception.h>

enum class Axis {
    RA = 1,
    DC = 2
};

enum class Direction {
    LEFT = 1,
    RIGHT = 2
};

void tlinsWPilotRaDcIncrement::raAxisSelected()
{
    ui->groupRA->setVisible(true);
    ui->groupDC->setVisible(false);
}

void tlinsWPilotRaDcIncrement::dcAxisSelected()
{
    ui->groupRA->setVisible(false);
    ui->groupDC->setVisible(true);
}

void tlinsWPilotRaDcIncrement::setParameters(const QJsonObject& doc)
{
    Axis a = Axis::RA;
    Direction dir = Direction::LEFT;

    {
        QJsonValue v = doc["axis"];
        if (!v.isString()) {
            // Przekazana wartosc nie jest typu double
            __THROW__(TlinsAstroBase::tlinsUIException(TlinsAstroBase::tlinsUIException::ERROR_INVALID_PARAMETER, "Parameter value is not a string"));
        }

        QString val = v.toString();
        if (val.toUpper() == "RA")
            a = Axis::RA;
        else if (val.toUpper() == "DC")
            a = Axis::DC;
    }

    {
        QJsonValue v = doc["direction"];
        if (!v.isString()) {
            // Przekazana wartosc nie jest typu double
            __THROW__(TlinsAstroBase::tlinsUIException(TlinsAstroBase::tlinsUIException::ERROR_INVALID_PARAMETER, "Parameter value is a string"));
        }

        QString val = v.toString();

        if (val.toUpper() == "RIGHT")
            dir = Direction::RIGHT;
        else if (val.toUpper() == "LEFT")
            dir = Direction::LEFT;
    }

    if (a == Axis::RA) {
        ui->groupRA->setVisible(true);
        ui->groupDC->setVisible(false);

        ui->radioDcUp->setChecked(false);
        ui->radioDcDown->setChecked(false);

        if (dir == Direction::LEFT) {
            ui->radioRaLeft->setChecked(true);
            ui->radioRaRight->setChecked(false);
        } else {
            ui->radioRaLeft->setChecked(false);
            ui->radioRaRight->setChecked(true);
        }
    } else {
        ui->groupRA->setVisible(false);
        ui->groupDC->setVisible(true);

        ui->radioRaLeft->setChecked(false);
        ui->radioRaRight->setChecked(false);

        if (dir == Direction::LEFT) {
            ui->radioDcUp->setChecked(true);
            ui->radioDcDown->setChecked(false);
        } else {
            ui->radioDcUp->setChecked(false);
            ui->radioDcDown->setChecked(true);
        }
    }
}

void tlinsWPilotRaDcIncrement::getParameters(QJsonObject& doc)
{
    Axis a = Axis::RA;
    Direction dir = Direction::LEFT;

    if (ui->radioRA->isChecked()) {
        a = Axis::RA;
        if (ui->radioRaLeft->isChecked())
            dir = Direction::LEFT;
        else
            dir = Direction::RIGHT;
    } else {
        a = Axis::DC;
        if (ui->radioDcUp->isChecked())
            dir = Direction::LEFT;
        else
            dir = Direction::RIGHT;
    }

    doc.insert("axis", a == Axis::RA ? QString { "ra" } : QString { "dc" });
    doc.insert("direction", dir == Direction::LEFT ? QString { "left" } : QString { "right" });
}

QWidget* tlinsWPilotRaDcIncrement::getWidget()
{
    return this;
}

void tlinsWPilotRaDcIncrement::reset()
{
    ui->radioRA->setChecked(false);
    ui->radioDC->setChecked(false);
    ui->groupRA->setVisible(false);
    ui->groupDC->setVisible(false);

    ui->radioDcUp->setChecked(false);
    ui->radioDcDown->setChecked(false);
    ui->radioRaLeft->setChecked(false);
    ui->radioRaRight->setChecked(false);
}

TlinsAstroBase::tlinsPilotShortcutsDefinitionValidMode tlinsWPilotRaDcIncrement::getValidMode()
{
    return TlinsAstroBase::tlinsPilotShortcutsDefinitionValidMode::ASTRO;
}

tlinsWPilotRaDcIncrement::tlinsWPilotRaDcIncrement(QWidget* parent)
    : QWidget(parent)
    , ui(new Ui::tlinsWPilotRaDcIncrement)
{
    ui->setupUi(this);

    ui->radioRA->setChecked(false);
    ui->radioDC->setChecked(false);
    ui->groupRA->setVisible(false);
    ui->groupDC->setVisible(false);

    ui->radioDcUp->setChecked(false);
    ui->radioDcDown->setChecked(false);
    ui->radioRaLeft->setChecked(false);
    ui->radioRaRight->setChecked(false);
}

tlinsWPilotRaDcIncrement::~tlinsWPilotRaDcIncrement()
{
    delete ui;
}
