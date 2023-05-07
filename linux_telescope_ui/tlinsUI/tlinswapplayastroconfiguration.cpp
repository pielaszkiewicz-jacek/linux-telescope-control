#include "tlinswapplayastroconfiguration.h"
#include "ui_tlinswapplayastroconfiguration.h"

tlinsWApplayAstroConfiguration::tlinsWApplayAstroConfiguration(QWidget* parent)
    : QWidget(parent)
    , ui(new Ui::tlinsWApplayAstroConfiguration)
{
    ui->setupUi(this);

    ui->chbIERSApplay->setChecked(true);
    ui->chbEnv->setChecked(true);
    ui->chbObservationPLace->setChecked(true);
}

std::map<tlinsWApplayAstroConfiguration::CFG_TYPE, bool> tlinsWApplayAstroConfiguration::getCfgToBeApplyed() const
{
    std::map<tlinsWApplayAstroConfiguration::CFG_TYPE, bool> result;

    result[tlinsWApplayAstroConfiguration::CFG_TYPE::ENVIRONMENT] = false;
    if (ui->chbEnv->isChecked())
        result[tlinsWApplayAstroConfiguration::CFG_TYPE::ENVIRONMENT] = true;

    result[tlinsWApplayAstroConfiguration::CFG_TYPE::IERS] = false;
    if (ui->chbIERSApplay->isChecked())
        result[tlinsWApplayAstroConfiguration::CFG_TYPE::IERS] = true;

    result[tlinsWApplayAstroConfiguration::CFG_TYPE::IERS_STORE_LOCALY] = false;
    if (ui->chnIERSStoreLocaly->isChecked())
        result[tlinsWApplayAstroConfiguration::CFG_TYPE::IERS_STORE_LOCALY] = true;

    result[tlinsWApplayAstroConfiguration::CFG_TYPE::IERS_OVERWRITE] = false;
    if (ui->chbIERSOverwrite->isChecked())
        result[tlinsWApplayAstroConfiguration::CFG_TYPE::IERS_OVERWRITE] = true;

    result[tlinsWApplayAstroConfiguration::CFG_TYPE::OBSERVATION_PLACE] = false;
    if (ui->chbObservationPLace->isChecked())
        result[tlinsWApplayAstroConfiguration::CFG_TYPE::OBSERVATION_PLACE] = true;

    return result;
}

tlinsWApplayAstroConfiguration::~tlinsWApplayAstroConfiguration()
{
    delete ui;
}
