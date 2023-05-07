#include "tlinswobservationerrorsettings.h"
#include "ui_tlinswobservationerrorsettings.h"

#include "tlinsBacktrace.hpp"
#include "tlinsconfiguration.h"

tlinsWObservationErrorSettings::tlinsWObservationErrorSettings(QWidget* parent)
    : QWidget(parent)
    , ui(new Ui::tlinsWObservationErrorSettings)
{
    ui->setupUi(this);
    restore();
}

void tlinsWObservationErrorSettings::save()
{
    // Instancja konfiguracji
    auto& inst = TlinsAstroBase::tlinsConfiguration::getInstance();

    inst.setValue(TlinsAstroBase::tlinsConfiguration::OBSERVATION_ERRORS_GROUP,
        TlinsAstroBase::tlinsConfiguration::OBSERVATION_ERRORS_LONGITUDE, ui->wData->getLongitudeError());
    inst.setValue(TlinsAstroBase::tlinsConfiguration::OBSERVATION_ERRORS_GROUP,
        TlinsAstroBase::tlinsConfiguration::OBSERVATION_ERRORS_LATITUDE, ui->wData->getLatitudeError());
    inst.setValue(TlinsAstroBase::tlinsConfiguration::OBSERVATION_ERRORS_GROUP,
        TlinsAstroBase::tlinsConfiguration::OBSERVATION_ERRORS_WEIGHT, ui->wData->getWeight());
}

void tlinsWObservationErrorSettings::saveDefault()
{
    // Instancja konfiguracji
    auto& inst = TlinsAstroBase::tlinsConfiguration::getInstance();

    inst.setValue(TlinsAstroBase::tlinsConfiguration::OBSERVATION_ERRORS_GROUP,
        TlinsAstroBase::tlinsConfiguration::OBSERVATION_ERRORS_LONGITUDE, 0.0);
    inst.setValue(TlinsAstroBase::tlinsConfiguration::OBSERVATION_ERRORS_GROUP,
        TlinsAstroBase::tlinsConfiguration::OBSERVATION_ERRORS_LATITUDE, 0.0);
    inst.setValue(TlinsAstroBase::tlinsConfiguration::OBSERVATION_ERRORS_GROUP,
        TlinsAstroBase::tlinsConfiguration::OBSERVATION_ERRORS_WEIGHT, 0.0);
}

void tlinsWObservationErrorSettings::restore()
{
    // Instancja konfiguracji
    auto& inst = TlinsAstroBase::tlinsConfiguration::getInstance();

    if (!inst.hasKey(TlinsAstroBase::tlinsConfiguration::OBSERVATION_ERRORS_GROUP,
            TlinsAstroBase::tlinsConfiguration::OBSERVATION_ERRORS_LONGITUDE)) {
        ui->wData->setLongitudeError(0.0);
        ui->wData->setLatitudeError(0.0);
        ui->wData->setWeight(0.0);
    } else {
        ui->wData->setLongitudeError(inst.getDouble(TlinsAstroBase::tlinsConfiguration::OBSERVATION_ERRORS_GROUP,
            TlinsAstroBase::tlinsConfiguration::OBSERVATION_ERRORS_LONGITUDE));
        ui->wData->setLatitudeError(inst.getDouble(TlinsAstroBase::tlinsConfiguration::OBSERVATION_ERRORS_GROUP,
            TlinsAstroBase::tlinsConfiguration::OBSERVATION_ERRORS_LATITUDE));
        ui->wData->setWeight(inst.getDouble(TlinsAstroBase::tlinsConfiguration::OBSERVATION_ERRORS_GROUP,
            TlinsAstroBase::tlinsConfiguration::OBSERVATION_ERRORS_WEIGHT));
    }
}

tlinsWObservationErrorSettings::~tlinsWObservationErrorSettings()
{
    delete ui;
}
