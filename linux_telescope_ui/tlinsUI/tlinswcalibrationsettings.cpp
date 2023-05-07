#include "tlinswcalibrationsettings.h"
#include "tlinsBacktrace.hpp"
#include "tlinsconfiguration.h"
#include "ui_tlinswcalibrationsettings.h"

tlinsWCalibrationSettings::tlinsWCalibrationSettings(QWidget* parent)
    : QWidget(parent)
    , ui(new Ui::tlinsWCalibrationSettings)
{
    ui->setupUi(this);
    ui->minNumberMeasurments->setDecimal(0);
    ui->minNumberReferenceObjects->setDecimal(0);
    restore();
}

tlinsWCalibrationSettings::~tlinsWCalibrationSettings()
{
    delete ui;
}

void tlinsWCalibrationSettings::save()
{
    // Instancja konfiguracji
    auto& inst = TlinsAstroBase::tlinsConfiguration::getInstance();
    inst.setValue(TlinsAstroBase::tlinsConfiguration::CALIBRARION_GROUP,
        TlinsAstroBase::tlinsConfiguration::CALIBRARION_MIN_NUMBER_MEASURMENTS, static_cast<int>(ui->minNumberMeasurments->getValue()));
    inst.setValue(TlinsAstroBase::tlinsConfiguration::CALIBRARION_GROUP,
        TlinsAstroBase::tlinsConfiguration::CALIBRARION_MIN_NUMBER_REFERENCE_OBJECTS, static_cast<int>(ui->minNumberReferenceObjects->getValue()));
}

void tlinsWCalibrationSettings::saveDefault()
{
    // Instancja konfiguracji
    auto& inst = TlinsAstroBase::tlinsConfiguration::getInstance();
    inst.setValue(TlinsAstroBase::tlinsConfiguration::CALIBRARION_GROUP,
        TlinsAstroBase::tlinsConfiguration::CALIBRARION_MIN_NUMBER_MEASURMENTS, 3);
    inst.setValue(TlinsAstroBase::tlinsConfiguration::CALIBRARION_GROUP,
        TlinsAstroBase::tlinsConfiguration::CALIBRARION_MIN_NUMBER_REFERENCE_OBJECTS, 2);
}

void tlinsWCalibrationSettings::restore()
{
    // Instancja konfiguracji
    auto& inst = TlinsAstroBase::tlinsConfiguration::getInstance();
    if (!inst.hasKey(TlinsAstroBase::tlinsConfiguration::CALIBRARION_GROUP,
            TlinsAstroBase::tlinsConfiguration::CALIBRARION_MIN_NUMBER_MEASURMENTS)) {
        ui->minNumberMeasurments->setValue(3);
        ui->minNumberReferenceObjects->setValue(2);
    } else {
        ui->minNumberMeasurments->setValue(inst.getInt(TlinsAstroBase::tlinsConfiguration::CALIBRARION_GROUP,
            TlinsAstroBase::tlinsConfiguration::CALIBRARION_MIN_NUMBER_MEASURMENTS));
        ui->minNumberReferenceObjects->setValue(inst.getInt(TlinsAstroBase::tlinsConfiguration::CALIBRARION_GROUP,
            TlinsAstroBase::tlinsConfiguration::CALIBRARION_MIN_NUMBER_REFERENCE_OBJECTS));
    }
}
