#include "tlinswobservationerrorswindow.h"
#include "tlinsconfiguration.h"
#include "ui_tlinswobservationerrorswindow.h"

tlinsWObservationErrorsWindow::tlinsWObservationErrorsWindow(QWidget* parent)
    : QDialog(parent)
    , ui(new Ui::tlinsWObservationErrorsWindow)
{
    ui->setupUi(this);

    // Instancja konfiguracji
    auto& inst = TlinsAstroBase::tlinsConfiguration::getInstance();

    ui->wData->setLongitudeError(inst.getDouble(TlinsAstroBase::tlinsConfiguration::OBSERVATION_ERRORS_GROUP,
        TlinsAstroBase::tlinsConfiguration::OBSERVATION_ERRORS_LONGITUDE));
    ui->wData->setLatitudeError(inst.getDouble(TlinsAstroBase::tlinsConfiguration::OBSERVATION_ERRORS_GROUP,
        TlinsAstroBase::tlinsConfiguration::OBSERVATION_ERRORS_LATITUDE));
    ui->wData->setWeight(inst.getDouble(TlinsAstroBase::tlinsConfiguration::OBSERVATION_ERRORS_GROUP,
        TlinsAstroBase::tlinsConfiguration::OBSERVATION_ERRORS_WEIGHT));
}

const tlinsWObservationError& tlinsWObservationErrorsWindow::getWErrors()
{
    return *(ui->wData);
}

tlinsWObservationErrorsWindow::~tlinsWObservationErrorsWindow()
{
    delete ui;
}
