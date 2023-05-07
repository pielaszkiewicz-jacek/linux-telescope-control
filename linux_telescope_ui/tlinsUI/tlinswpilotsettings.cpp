#include "tlinswpilotsettings.h"
#include "tlinsconfiguration.h"
#include "ui_tlinswpilotsettings.h"

#include <tlinsBacktrace.hpp>

tlinsWPilotSettings::tlinsWPilotSettings(QWidget* parent)
    : QWidget(parent)
    , ui(new Ui::tlinsWPilotSettings)
{
    ui->setupUi(this);

    ui->stepsX->setDecimal(0);
    ui->stepsY->setDecimal(0);
    ui->stepsVX->setDecimal(0);
    ui->stepsVY->setDecimal(0);
    restore();
}

void tlinsWPilotSettings::save()
{
    auto& inst = TlinsAstroBase::tlinsConfiguration::getInstance();

    inst.setValue(TlinsAstroBase::tlinsConfiguration::PILOT_PARAMETER_GROUP,
        TlinsAstroBase::tlinsConfiguration::PILOT_PARAMETER_STEPS_X_V, static_cast<int>(ui->stepsVX->getValue()));
    inst.setValue(TlinsAstroBase::tlinsConfiguration::PILOT_PARAMETER_GROUP,
        TlinsAstroBase::tlinsConfiguration::PILOT_PARAMETER_STEPS_X, static_cast<int>(ui->stepsX->getValue()));

    inst.setValue(TlinsAstroBase::tlinsConfiguration::PILOT_PARAMETER_GROUP,
        TlinsAstroBase::tlinsConfiguration::PILOT_PARAMETER_STEPS_Y_V, static_cast<int>(ui->stepsVY->getValue()));
    inst.setValue(TlinsAstroBase::tlinsConfiguration::PILOT_PARAMETER_GROUP,
        TlinsAstroBase::tlinsConfiguration::PILOT_PARAMETER_STEPS_Y, static_cast<int>(ui->stepsY->getValue()));

    inst.setValue(TlinsAstroBase::tlinsConfiguration::PILOT_PARAMETER_GROUP,
        TlinsAstroBase::tlinsConfiguration::PILOT_PARAMETER_DEGRIS_X_V, static_cast<double>(ui->degrisVX->getValue()));
    inst.setValue(TlinsAstroBase::tlinsConfiguration::PILOT_PARAMETER_GROUP,
        TlinsAstroBase::tlinsConfiguration::PILOT_PARAMETER_DEGRIS_X, static_cast<double>(ui->degrisX->getValue()));

    inst.setValue(TlinsAstroBase::tlinsConfiguration::PILOT_PARAMETER_GROUP,
        TlinsAstroBase::tlinsConfiguration::PILOT_PARAMETER_DEGRIS_Y_V, static_cast<double>(ui->degrisVY->getValue()));
    inst.setValue(TlinsAstroBase::tlinsConfiguration::PILOT_PARAMETER_GROUP,
        TlinsAstroBase::tlinsConfiguration::PILOT_PARAMETER_DEGRIS_Y, static_cast<double>(ui->degrisY->getValue()));

    inst.setValue(TlinsAstroBase::tlinsConfiguration::PILOT_PARAMETER_GROUP,
        TlinsAstroBase::tlinsConfiguration::PILOT_PARAMETER_ASTRO_RA_V, static_cast<double>(ui->astroVRA->getValue()));
    inst.setValue(TlinsAstroBase::tlinsConfiguration::PILOT_PARAMETER_GROUP,
        TlinsAstroBase::tlinsConfiguration::PILOT_PARAMETER_ASTRO_RA, static_cast<double>(ui->astroRA->getValue()));

    inst.setValue(TlinsAstroBase::tlinsConfiguration::PILOT_PARAMETER_GROUP,
        TlinsAstroBase::tlinsConfiguration::PILOT_PARAMETER_ASTRO_DC_V, static_cast<double>(ui->astroVDC->getValue()));
    inst.setValue(TlinsAstroBase::tlinsConfiguration::PILOT_PARAMETER_GROUP,
        TlinsAstroBase::tlinsConfiguration::PILOT_PARAMETER_ASTRO_DC, static_cast<double>(ui->astroDC->getValue()));

    inst.setValue(TlinsAstroBase::tlinsConfiguration::PILOT_PARAMETER_GROUP,
        TlinsAstroBase::tlinsConfiguration::PILOT_PARAMETER_GUIDING_RA_V, static_cast<double>(ui->guideVX->getValue()));
    inst.setValue(TlinsAstroBase::tlinsConfiguration::PILOT_PARAMETER_GROUP,
        TlinsAstroBase::tlinsConfiguration::PILOT_PARAMETER_GUIDING_RA, static_cast<double>(ui->guideX->getValue()));

    inst.setValue(TlinsAstroBase::tlinsConfiguration::PILOT_PARAMETER_GROUP,
        TlinsAstroBase::tlinsConfiguration::PILOT_PARAMETER_GUIDING_DC_V, static_cast<double>(ui->guideVY->getValue()));
    inst.setValue(TlinsAstroBase::tlinsConfiguration::PILOT_PARAMETER_GROUP,
        TlinsAstroBase::tlinsConfiguration::PILOT_PARAMETER_GUIDING_DC, static_cast<double>(ui->guideY->getValue()));
}

void tlinsWPilotSettings::saveDefault()
{
    auto& inst = TlinsAstroBase::tlinsConfiguration::getInstance();

    double dv = 64000.0 / (256.0 * 256.0 * 200) * 360.0;
    double d = 10000.0 / (256.0 * 256.0 * 200) * 360.0;
    double hv = 64000.0 / (256.0 * 256.0 * 200) * 24.0;
    double h = 10000.0 / (256.0 * 256.0 * 200) * 240.0;

    inst.setValue(TlinsAstroBase::tlinsConfiguration::PILOT_PARAMETER_GROUP,
        TlinsAstroBase::tlinsConfiguration::PILOT_PARAMETER_STEPS_X_V, 64000);
    inst.setValue(TlinsAstroBase::tlinsConfiguration::PILOT_PARAMETER_GROUP,
        TlinsAstroBase::tlinsConfiguration::PILOT_PARAMETER_STEPS_X, 10000);

    inst.setValue(TlinsAstroBase::tlinsConfiguration::PILOT_PARAMETER_GROUP,
        TlinsAstroBase::tlinsConfiguration::PILOT_PARAMETER_STEPS_Y_V, 64000);
    inst.setValue(TlinsAstroBase::tlinsConfiguration::PILOT_PARAMETER_GROUP,
        TlinsAstroBase::tlinsConfiguration::PILOT_PARAMETER_STEPS_Y, 10000);

    inst.setValue(TlinsAstroBase::tlinsConfiguration::PILOT_PARAMETER_GROUP,
        TlinsAstroBase::tlinsConfiguration::PILOT_PARAMETER_DEGRIS_X_V, dv);
    inst.setValue(TlinsAstroBase::tlinsConfiguration::PILOT_PARAMETER_GROUP,
        TlinsAstroBase::tlinsConfiguration::PILOT_PARAMETER_DEGRIS_X, d);

    inst.setValue(TlinsAstroBase::tlinsConfiguration::PILOT_PARAMETER_GROUP,
        TlinsAstroBase::tlinsConfiguration::PILOT_PARAMETER_DEGRIS_Y_V, dv);
    inst.setValue(TlinsAstroBase::tlinsConfiguration::PILOT_PARAMETER_GROUP,
        TlinsAstroBase::tlinsConfiguration::PILOT_PARAMETER_DEGRIS_Y, d);

    inst.setValue(TlinsAstroBase::tlinsConfiguration::PILOT_PARAMETER_GROUP,
        TlinsAstroBase::tlinsConfiguration::PILOT_PARAMETER_ASTRO_RA_V, hv);
    inst.setValue(TlinsAstroBase::tlinsConfiguration::PILOT_PARAMETER_GROUP,
        TlinsAstroBase::tlinsConfiguration::PILOT_PARAMETER_ASTRO_RA, h);

    inst.setValue(TlinsAstroBase::tlinsConfiguration::PILOT_PARAMETER_GROUP,
        TlinsAstroBase::tlinsConfiguration::PILOT_PARAMETER_ASTRO_DC_V, dv);
    inst.setValue(TlinsAstroBase::tlinsConfiguration::PILOT_PARAMETER_GROUP,
        TlinsAstroBase::tlinsConfiguration::PILOT_PARAMETER_ASTRO_DC, d);

    inst.setValue(TlinsAstroBase::tlinsConfiguration::PILOT_PARAMETER_GROUP,
        TlinsAstroBase::tlinsConfiguration::PILOT_PARAMETER_GUIDING_RA_V, hv);
    inst.setValue(TlinsAstroBase::tlinsConfiguration::PILOT_PARAMETER_GROUP,
        TlinsAstroBase::tlinsConfiguration::PILOT_PARAMETER_GUIDING_RA, h);

    inst.setValue(TlinsAstroBase::tlinsConfiguration::PILOT_PARAMETER_GROUP,
        TlinsAstroBase::tlinsConfiguration::PILOT_PARAMETER_GUIDING_DC_V, dv);
    inst.setValue(TlinsAstroBase::tlinsConfiguration::PILOT_PARAMETER_GROUP,
        TlinsAstroBase::tlinsConfiguration::PILOT_PARAMETER_GUIDING_DC, d);
}

void tlinsWPilotSettings::restore()
{
    auto& inst = TlinsAstroBase::tlinsConfiguration::getInstance();

    ui->stepsVX->setValue(static_cast<double>(inst.getInt(TlinsAstroBase::tlinsConfiguration::PILOT_PARAMETER_GROUP,
        TlinsAstroBase::tlinsConfiguration::PILOT_PARAMETER_STEPS_X_V)));
    ui->stepsX->setValue(static_cast<double>(inst.getInt(TlinsAstroBase::tlinsConfiguration::PILOT_PARAMETER_GROUP,
        TlinsAstroBase::tlinsConfiguration::PILOT_PARAMETER_STEPS_X)));

    ui->stepsVY->setValue(static_cast<double>(inst.getInt(TlinsAstroBase::tlinsConfiguration::PILOT_PARAMETER_GROUP,
        TlinsAstroBase::tlinsConfiguration::PILOT_PARAMETER_STEPS_Y_V)));
    ui->stepsY->setValue(static_cast<double>(inst.getInt(TlinsAstroBase::tlinsConfiguration::PILOT_PARAMETER_GROUP,
        TlinsAstroBase::tlinsConfiguration::PILOT_PARAMETER_STEPS_Y)));

    ui->degrisVX->setValue(inst.getDouble(TlinsAstroBase::tlinsConfiguration::PILOT_PARAMETER_GROUP,
        TlinsAstroBase::tlinsConfiguration::PILOT_PARAMETER_DEGRIS_X_V));
    ui->degrisX->setValue(inst.getDouble(TlinsAstroBase::tlinsConfiguration::PILOT_PARAMETER_GROUP,
        TlinsAstroBase::tlinsConfiguration::PILOT_PARAMETER_DEGRIS_X));

    ui->degrisVY->setValue(inst.getDouble(TlinsAstroBase::tlinsConfiguration::PILOT_PARAMETER_GROUP,
        TlinsAstroBase::tlinsConfiguration::PILOT_PARAMETER_DEGRIS_Y_V));
    ui->degrisY->setValue(inst.getDouble(TlinsAstroBase::tlinsConfiguration::PILOT_PARAMETER_GROUP,
        TlinsAstroBase::tlinsConfiguration::PILOT_PARAMETER_DEGRIS_Y));

    ui->astroVRA->setValue(inst.getDouble(TlinsAstroBase::tlinsConfiguration::PILOT_PARAMETER_GROUP,
        TlinsAstroBase::tlinsConfiguration::PILOT_PARAMETER_ASTRO_RA_V));
    ui->astroRA->setValue(inst.getDouble(TlinsAstroBase::tlinsConfiguration::PILOT_PARAMETER_GROUP,
        TlinsAstroBase::tlinsConfiguration::PILOT_PARAMETER_ASTRO_RA));

    ui->astroVDC->setValue(inst.getDouble(TlinsAstroBase::tlinsConfiguration::PILOT_PARAMETER_GROUP,
        TlinsAstroBase::tlinsConfiguration::PILOT_PARAMETER_ASTRO_DC_V));
    ui->astroDC->setValue(inst.getDouble(TlinsAstroBase::tlinsConfiguration::PILOT_PARAMETER_GROUP,
        TlinsAstroBase::tlinsConfiguration::PILOT_PARAMETER_ASTRO_DC));

    ui->guideVX->setValue(inst.getDouble(TlinsAstroBase::tlinsConfiguration::PILOT_PARAMETER_GROUP,
        TlinsAstroBase::tlinsConfiguration::PILOT_PARAMETER_GUIDING_RA_V));
    ui->guideX->setValue(inst.getDouble(TlinsAstroBase::tlinsConfiguration::PILOT_PARAMETER_GROUP,
        TlinsAstroBase::tlinsConfiguration::PILOT_PARAMETER_GUIDING_RA));

    ui->guideVY->setValue(inst.getDouble(TlinsAstroBase::tlinsConfiguration::PILOT_PARAMETER_GROUP,
        TlinsAstroBase::tlinsConfiguration::PILOT_PARAMETER_GUIDING_DC_V));
    ui->guideY->setValue(inst.getDouble(TlinsAstroBase::tlinsConfiguration::PILOT_PARAMETER_GROUP,
        TlinsAstroBase::tlinsConfiguration::PILOT_PARAMETER_GUIDING_DC));
}

tlinsWPilotSettings::~tlinsWPilotSettings()
{
    delete ui;
}
