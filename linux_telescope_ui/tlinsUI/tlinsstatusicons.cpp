#include "tlinsstatusicons.h"
#include "ui_tlinsstatusicons.h"

tlinsStatusIcons::tlinsStatusIcons(QWidget* parent)
    : QWidget(parent)
    , ui(new Ui::tlinsStatusIcons)
{
    ui->setupUi(this);
    ui->posX->setValue(0);
    ui->posX->disableButtons();
    ui->posY->disableButtons();

    ui->posX->setDecimal(0);
    ui->posY->setDecimal(0);

    ui->posX->setEnabled(false);
    ui->posY->setEnabled(false);

    ui->posX->setValue(0);
    ui->posY->setValue(0);

    ui->posRA->setEnabled(false);
    ui->posDEC->setEnabled(false);

    ui->posRA->setValue(0.0);
    ui->posDEC->setValue(0.0);

    //	ui ->wX->
}

void tlinsStatusIcons::setCalibrationState(const CalibrationStatus v)
{
    switch (v) {
    case tlinsStatusIcons::CalibrationStatus::UNDEFINED:
        ui->calibrationStatus->setText("Undefined");
        break;

    case tlinsStatusIcons::CalibrationStatus::UNDER_CALIBRATION:
        ui->calibrationStatus->setText("Calibration");
        break;

    case tlinsStatusIcons::CalibrationStatus::REGULAR:
        ui->calibrationStatus->setText("Ready");
        break;
    }
}

void tlinsStatusIcons::setPos(const long& X, const long& Y)
{
    ui->posX->setValue(X);
    ui->posY->setValue(Y);
}

void tlinsStatusIcons::setPos(const double& RA, const double& DEC)
{
    ui->posRA->setValue(RA);
    ui->posDEC->setValue(DEC);
}

void tlinsStatusIcons::setConnectionStatus(bool stat)
{
    ui->isConnected->setChecked(stat);
}

tlinsStatusIcons::~tlinsStatusIcons()
{
    delete ui;
}
