#include "tlinsastroobjectcoordinate.h"
#include "tlinsuiutils.h"
#include "ui_tlinsastroobjectcoordinate.h"

tlinsAstroObjectCoordinate::tlinsAstroObjectCoordinate(QWidget* parent)
    : QWidget(parent)
    , ui(new Ui::tlinsAstroObjectCoordinate)
{
    ui->setupUi(this);

    tlinsWSetWidget(raMinErr, lraMinErr, ui->raMinError);
    tlinsWSetWidget(dcMinErr, ldcMinErr, ui->dcMinError);

    tlinsWSetWidget(raMeanErr, lraMeanErr, ui->raMeanError);
    tlinsWSetWidget(dcMeanErr, ldcMeanErr, ui->dcMeanError);

    tlinsWSetWidget(raCentralEpoch, lraCentralEpoch, ui->raCentralEpoch);
    tlinsWSetWidget(dcCentralEpoch, ldcCentralEpoch, ui->dcCentralEpoch);

    tlinsWSetWidget(raProperMotion, lraProperMotion, ui->raProperMotion);
    tlinsWSetWidget(dcProperMotion, ldcProperMotion, ui->dcProperMotion);

    tlinsWSetWidget(raProperMotionError, lraProperMotionError, ui->raProperMotionError);
    tlinsWSetWidget(dcProperMotionError, ldcProperMotionError, ui->dcProperMotionError);
}

tlinsAstroObjectCoordinate::~tlinsAstroObjectCoordinate()
{
    delete ui;
}
