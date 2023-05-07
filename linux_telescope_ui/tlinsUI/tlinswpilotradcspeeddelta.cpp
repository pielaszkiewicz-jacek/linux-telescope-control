#include "tlinswpilotradcspeeddelta.h"
#include "ui_tlinswpilotradcspeeddelta.h"

#include <tlinsBacktrace.hpp>
#include <tlinsuiexception.h>

enum class Axis {
    RA = 1,
    DC = 2
};

void tlinsWPilotRaDcSpeedDelta::raSelected()
{
    ui->groupHourAngle->setVisible(true);
    ui->groupDeclination->setVisible(false);
}

void tlinsWPilotRaDcSpeedDelta::dcSelected()
{
    ui->groupHourAngle->setVisible(false);
    ui->groupDeclination->setVisible(true);
}

void tlinsWPilotRaDcSpeedDelta::setParameters(const QJsonObject& doc)
{
    Axis a = Axis::RA;
    double dcValue = 0.0;
    double raValue = 0.0;
    bool raValueNegative = false;

    {
        QJsonValue v = doc["axis"];
        if (!v.isString()) {
            // Przekazana wartosc nie jest typu double
            __THROW__(TlinsAstroBase::tlinsUIException(TlinsAstroBase::tlinsUIException::ERROR_INVALID_PARAMETER, "Parameter value is not double"));
        }

        QString val = v.toString();

        if (val.toUpper() == "RA")
            a = Axis::RA;
        else if (val.toUpper() == "DC")
            a = Axis::DC;
    }

    if (a == Axis::RA) {
        QJsonValue vn = doc["negative-ra"];
        if (!vn.isBool()) {
            // Przekazana wartosc nie jest typu double
            __THROW__(TlinsAstroBase::tlinsUIException(TlinsAstroBase::tlinsUIException::ERROR_INVALID_PARAMETER, "Parameter value-steps is not bool"));
        }
        raValueNegative = vn.toBool();

        QJsonValue v = doc["value-ra"];
        if (!v.isDouble()) {
            // Przekazana wartosc nie jest typu double
            __THROW__(TlinsAstroBase::tlinsUIException(TlinsAstroBase::tlinsUIException::ERROR_INVALID_PARAMETER, "Parameter value-steps is not double"));
        }
        raValue = v.toDouble();
    } else {
        QJsonValue v = doc["value-dc"];
        if (!v.isDouble()) {
            // Przekazana wartosc nie jest typu double
            __THROW__(TlinsAstroBase::tlinsUIException(TlinsAstroBase::tlinsUIException::ERROR_INVALID_PARAMETER, "Parameter value is not double"));
        }
        dcValue = v.toDouble();
    }

    // Modyfikacja UI
    {
        if (a == Axis::RA) {
            // W krokach
            ui->groupDeclination->setVisible(false);
            ui->groupHourAngle->setVisible(true);

            ui->radioHourAngle->setChecked(true);
            ui->radioDeclination->setChecked(false);

            ui->negative->setChecked(raValueNegative);

            ui->valueHourAngle->setValue(raValue);
        } else {
            // W stopniach
            ui->groupDeclination->setVisible(true);
            ui->groupHourAngle->setVisible(false);

            ui->radioHourAngle->setChecked(false);
            ui->radioDeclination->setChecked(true);
            ui->negative->setChecked(false);

            ui->valueDeclination->setValue(dcValue);
        }
    }
}

void tlinsWPilotRaDcSpeedDelta::getParameters(QJsonObject& doc)
{
    // Os
    doc.insert("axis", ui->radioHourAngle->isChecked() ? QString { "ra" } : QString { "dc" });

    if (ui->radioHourAngle->isChecked()) {
        doc.insert("value-ra", ui->valueHourAngle->getValue());
        doc.insert("value-dc", 0.0);
        doc.insert("negative-ra", ui->negative->isChecked() ? true : false);
    } else {
        doc.insert("value-ra", 0.0);
        doc.insert("value-dc", ui->valueDeclination->getValue());
        doc.insert("negative-ra", false);
    }
}

QWidget* tlinsWPilotRaDcSpeedDelta::getWidget()
{
    return this;
}

void tlinsWPilotRaDcSpeedDelta::reset()
{
    ui->groupHourAngle->setVisible(false);
    ui->groupDeclination->setVisible(false);

    ui->radioHourAngle->setChecked(false);
    ui->radioDeclination->setChecked(false);
    ui->negative->setChecked(false);
}

TlinsAstroBase::tlinsPilotShortcutsDefinitionValidMode tlinsWPilotRaDcSpeedDelta::getValidMode()
{
    return TlinsAstroBase::tlinsPilotShortcutsDefinitionValidMode::ASTRO;
}

tlinsWPilotRaDcSpeedDelta::tlinsWPilotRaDcSpeedDelta(QWidget* parent)
    : QWidget(parent)
    , ui(new Ui::tlinsWPilotRaDcSpeedDelta)
{
    ui->setupUi(this);

    ui->groupHourAngle->setVisible(false);
    ui->groupDeclination->setVisible(false);

    ui->radioHourAngle->setChecked(false);
    ui->radioDeclination->setChecked(false);
    ui->negative->setChecked(false);
}

tlinsWPilotRaDcSpeedDelta::~tlinsWPilotRaDcSpeedDelta()
{
    delete ui;
}
