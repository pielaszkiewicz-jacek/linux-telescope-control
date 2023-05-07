#include "tlinswpilotradcdelta.h"
#include "ui_tlinswpilotradcdelta.h"

#include <tlinsBacktrace.hpp>
#include <tlinsuiexception.h>

enum class Axis {
    RA = 1,
    DC = 2
};

void tlinsWPilotRaDcDelta::raSelected()
{
    ui->groupHourAngle->setVisible(true);
    ui->groupDeclination->setVisible(false);
}

void tlinsWPilotRaDcDelta::dcSelected()
{
    ui->groupHourAngle->setVisible(false);
    ui->groupDeclination->setVisible(true);
}

void tlinsWPilotRaDcDelta::setParameters(const QJsonObject& doc)
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

            ui->radioRa->setChecked(true);
            ui->radioDc->setChecked(false);

            ui->negative->setChecked(raValueNegative);
            ui->hourAngleValue->setValue(raValue);
        } else {
            // W stopniach
            ui->groupDeclination->setVisible(true);
            ui->groupHourAngle->setVisible(false);

            ui->radioRa->setChecked(false);
            ui->radioDc->setChecked(true);
            ui->negative->setChecked(false);
            ui->declinationValue->setValue(dcValue);
        }
    }
}

void tlinsWPilotRaDcDelta::getParameters(QJsonObject& doc)
{
    // Os
    doc.insert("axis", ui->radioRa->isChecked() ? QString { "ra" } : QString { "dc" });

    if (ui->radioRa->isChecked()) {
        doc.insert("value-ra", ui->hourAngleValue->getValue());
        doc.insert("value-dc", 0.0);
        doc.insert("negative-ra", ui->negative->isChecked() ? true : false);
    } else {
        doc.insert("value-ra", 0.0);
        doc.insert("value-dc", ui->declinationValue->getValue());
        doc.insert("negative-ra", false);
    }
}

QWidget* tlinsWPilotRaDcDelta::getWidget()
{
    return this;
}

void tlinsWPilotRaDcDelta::reset()
{
    ui->groupHourAngle->setVisible(false);
    ui->groupDeclination->setVisible(false);

    ui->radioRa->setChecked(false);
    ui->radioDc->setChecked(false);
    ui->negative->setChecked(false);
}

TlinsAstroBase::tlinsPilotShortcutsDefinitionValidMode tlinsWPilotRaDcDelta::getValidMode()
{
    return TlinsAstroBase::tlinsPilotShortcutsDefinitionValidMode::ASTRO;
}

tlinsWPilotRaDcDelta::tlinsWPilotRaDcDelta(QWidget* parent)
    : QWidget(parent)
    , ui(new Ui::tlinsWPilotRaDcDelta)
{
    ui->setupUi(this);

    ui->groupHourAngle->setVisible(false);
    ui->groupDeclination->setVisible(false);

    ui->radioRa->setChecked(false);
    ui->radioDc->setChecked(false);
    ui->negative->setChecked(false);
}

tlinsWPilotRaDcDelta::~tlinsWPilotRaDcDelta()
{
    delete ui;
}
