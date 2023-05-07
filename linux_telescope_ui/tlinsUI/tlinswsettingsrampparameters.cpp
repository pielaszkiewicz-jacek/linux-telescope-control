#include "tlinswsettingsrampparameters.h"
#include "ui_tlinswsettingsrampparameters.h"

#include "tlinsconfiguration.h"

#define __PI__ 3.141592653589793

#define MAX_STEPS 6553600
#define DEFAULT_A_STEPS 1024000
#define DEFAULT_D_STEPS 1024000
#define DEFAULT_V_MAX_STEPS 64000

tlinsWSettingsRampParameters::tlinsWSettingsRampParameters(QWidget* parent)
    : QWidget(parent)
    , ui(new Ui::tlinsWSettingsRampParameters)
{
    ui->setupUi(this);

    ui->stepsAX->setDecimal(0);
    ui->stepsDX->setDecimal(0);
    ui->stepsVmaxX->setDecimal(0);

    ui->stepsAY->setDecimal(0);
    ui->stepsDY->setDecimal(0);
    ui->stepsVmaxY->setDecimal(0);

    restore();
}

void tlinsWSettingsRampParameters::restore()
{
    // Instancja konfiguracji
    auto& inst = TlinsAstroBase::tlinsConfiguration::getInstance();

    ui->stepsAX->setValue(static_cast<double>(inst.getInt(TlinsAstroBase::tlinsConfiguration::RAMP_PARAMETER_GROUP,
        TlinsAstroBase::tlinsConfiguration::RAMP_PARAMETER_STEPS_X_A)));
    ui->stepsDX->setValue(static_cast<double>(inst.getInt(TlinsAstroBase::tlinsConfiguration::RAMP_PARAMETER_GROUP,
        TlinsAstroBase::tlinsConfiguration::RAMP_PARAMETER_STEPS_X_D)));
    ui->stepsVmaxX->setValue(static_cast<double>(inst.getInt(TlinsAstroBase::tlinsConfiguration::RAMP_PARAMETER_GROUP,
        TlinsAstroBase::tlinsConfiguration::RAMP_PARAMETER_STEPS_X_V_MAX)));

    ui->stepsAY->setValue(static_cast<double>(inst.getInt(TlinsAstroBase::tlinsConfiguration::RAMP_PARAMETER_GROUP,
        TlinsAstroBase::tlinsConfiguration::RAMP_PARAMETER_STEPS_Y_A)));
    ui->stepsDY->setValue(static_cast<double>(inst.getInt(TlinsAstroBase::tlinsConfiguration::RAMP_PARAMETER_GROUP,
        TlinsAstroBase::tlinsConfiguration::RAMP_PARAMETER_STEPS_Y_D)));
    ui->stepsVmaxY->setValue(static_cast<double>(inst.getInt(TlinsAstroBase::tlinsConfiguration::RAMP_PARAMETER_GROUP,
        TlinsAstroBase::tlinsConfiguration::RAMP_PARAMETER_STEPS_Y_V_MAX)));

    ui->degrisAX->setValue(inst.getDouble(TlinsAstroBase::tlinsConfiguration::RAMP_PARAMETER_GROUP,
        TlinsAstroBase::tlinsConfiguration::RAMP_PARAMETER_DEGRIS_X_A));
    ui->degrisDX->setValue(inst.getDouble(TlinsAstroBase::tlinsConfiguration::RAMP_PARAMETER_GROUP,
        TlinsAstroBase::tlinsConfiguration::RAMP_PARAMETER_DEGRIS_X_D));
    ui->degrisVmaxX->setValue(inst.getDouble(TlinsAstroBase::tlinsConfiguration::RAMP_PARAMETER_GROUP,
        TlinsAstroBase::tlinsConfiguration::RAMP_PARAMETER_DEGRIS_X_V_MAX));

    ui->degrisAY->setValue(inst.getDouble(TlinsAstroBase::tlinsConfiguration::RAMP_PARAMETER_GROUP,
        TlinsAstroBase::tlinsConfiguration::RAMP_PARAMETER_DEGRIS_Y_A));
    ui->degrisDY->setValue(inst.getDouble(TlinsAstroBase::tlinsConfiguration::RAMP_PARAMETER_GROUP,
        TlinsAstroBase::tlinsConfiguration::RAMP_PARAMETER_DEGRIS_Y_D));
    ui->degrisVmaxY->setValue(inst.getDouble(TlinsAstroBase::tlinsConfiguration::RAMP_PARAMETER_GROUP,
        TlinsAstroBase::tlinsConfiguration::RAMP_PARAMETER_DEGRIS_Y_V_MAX));

    ui->astroARa->setValue(inst.getDouble(TlinsAstroBase::tlinsConfiguration::RAMP_PARAMETER_GROUP,
        TlinsAstroBase::tlinsConfiguration::RAMP_PARAMETER_ASTRO_RA_A));
    ui->astroDRa->setValue(inst.getDouble(TlinsAstroBase::tlinsConfiguration::RAMP_PARAMETER_GROUP,
        TlinsAstroBase::tlinsConfiguration::RAMP_PARAMETER_ASTRO_RA_D));
    ui->astroVmaxRa->setValue(inst.getDouble(TlinsAstroBase::tlinsConfiguration::RAMP_PARAMETER_GROUP,
        TlinsAstroBase::tlinsConfiguration::RAMP_PARAMETER_ASTRO_RA_V_MAX));

    ui->astroADc->setValue(inst.getDouble(TlinsAstroBase::tlinsConfiguration::RAMP_PARAMETER_GROUP,
        TlinsAstroBase::tlinsConfiguration::RAMP_PARAMETER_ASTRO_DC_A));
    ui->astroDDc->setValue(inst.getDouble(TlinsAstroBase::tlinsConfiguration::RAMP_PARAMETER_GROUP,
        TlinsAstroBase::tlinsConfiguration::RAMP_PARAMETER_ASTRO_DC_D));
    ui->astroVmaxDc->setValue(inst.getDouble(TlinsAstroBase::tlinsConfiguration::RAMP_PARAMETER_GROUP,
        TlinsAstroBase::tlinsConfiguration::RAMP_PARAMETER_ASTRO_DC_V_MAX));

    ui->guidingARa->setValue(inst.getDouble(TlinsAstroBase::tlinsConfiguration::RAMP_PARAMETER_GROUP,
        TlinsAstroBase::tlinsConfiguration::RAMP_PARAMETER_GUIDING_RA_A));
    ui->guidingDRa->setValue(inst.getDouble(TlinsAstroBase::tlinsConfiguration::RAMP_PARAMETER_GROUP,
        TlinsAstroBase::tlinsConfiguration::RAMP_PARAMETER_GUIDING_RA_D));
    ui->guidingVmaxRa->setValue(inst.getDouble(TlinsAstroBase::tlinsConfiguration::RAMP_PARAMETER_GROUP,
        TlinsAstroBase::tlinsConfiguration::RAMP_PARAMETER_GUIDING_RA_V_MAX));

    ui->guidingADc->setValue(inst.getDouble(TlinsAstroBase::tlinsConfiguration::RAMP_PARAMETER_GROUP,
        TlinsAstroBase::tlinsConfiguration::RAMP_PARAMETER_GUIDING_DC_A));
    ui->guidingDDc->setValue(inst.getDouble(TlinsAstroBase::tlinsConfiguration::RAMP_PARAMETER_GROUP,
        TlinsAstroBase::tlinsConfiguration::RAMP_PARAMETER_GUIDING_DC_D));
    ui->guidingVmaxDc->setValue(inst.getDouble(TlinsAstroBase::tlinsConfiguration::RAMP_PARAMETER_GROUP,
        TlinsAstroBase::tlinsConfiguration::RAMP_PARAMETER_GUIDING_DC_V_MAX));
}

void tlinsWSettingsRampParameters::save()
{
    // Instancja konfiguracji
    auto& inst = TlinsAstroBase::tlinsConfiguration::getInstance();

    inst.setValue(TlinsAstroBase::tlinsConfiguration::RAMP_PARAMETER_GROUP,
        TlinsAstroBase::tlinsConfiguration::RAMP_PARAMETER_STEPS_X_A, static_cast<int>(ui->stepsAX->getValue()));
    inst.setValue(TlinsAstroBase::tlinsConfiguration::RAMP_PARAMETER_GROUP,
        TlinsAstroBase::tlinsConfiguration::RAMP_PARAMETER_STEPS_X_D, static_cast<int>(ui->stepsDX->getValue()));
    inst.setValue(TlinsAstroBase::tlinsConfiguration::RAMP_PARAMETER_GROUP,
        TlinsAstroBase::tlinsConfiguration::RAMP_PARAMETER_STEPS_X_V_MAX, static_cast<int>(ui->stepsVmaxX->getValue()));

    inst.setValue(TlinsAstroBase::tlinsConfiguration::RAMP_PARAMETER_GROUP,
        TlinsAstroBase::tlinsConfiguration::RAMP_PARAMETER_STEPS_Y_A, static_cast<int>(ui->stepsAY->getValue()));
    inst.setValue(TlinsAstroBase::tlinsConfiguration::RAMP_PARAMETER_GROUP,
        TlinsAstroBase::tlinsConfiguration::RAMP_PARAMETER_STEPS_Y_D, static_cast<int>(ui->stepsDY->getValue()));
    inst.setValue(TlinsAstroBase::tlinsConfiguration::RAMP_PARAMETER_GROUP,
        TlinsAstroBase::tlinsConfiguration::RAMP_PARAMETER_STEPS_Y_V_MAX, static_cast<int>(ui->stepsVmaxY->getValue()));

    inst.setValue(TlinsAstroBase::tlinsConfiguration::RAMP_PARAMETER_GROUP,
        TlinsAstroBase::tlinsConfiguration::RAMP_PARAMETER_DEGRIS_X_A, ui->degrisAX->getValue());
    inst.setValue(TlinsAstroBase::tlinsConfiguration::RAMP_PARAMETER_GROUP,
        TlinsAstroBase::tlinsConfiguration::RAMP_PARAMETER_DEGRIS_X_D, ui->degrisDX->getValue());
    inst.setValue(TlinsAstroBase::tlinsConfiguration::RAMP_PARAMETER_GROUP,
        TlinsAstroBase::tlinsConfiguration::RAMP_PARAMETER_DEGRIS_X_V_MAX, ui->degrisVmaxX->getValue());

    inst.setValue(TlinsAstroBase::tlinsConfiguration::RAMP_PARAMETER_GROUP,
        TlinsAstroBase::tlinsConfiguration::RAMP_PARAMETER_DEGRIS_Y_A, ui->degrisAY->getValue());
    inst.setValue(TlinsAstroBase::tlinsConfiguration::RAMP_PARAMETER_GROUP,
        TlinsAstroBase::tlinsConfiguration::RAMP_PARAMETER_DEGRIS_Y_D, ui->degrisDY->getValue());
    inst.setValue(TlinsAstroBase::tlinsConfiguration::RAMP_PARAMETER_GROUP,
        TlinsAstroBase::tlinsConfiguration::RAMP_PARAMETER_DEGRIS_Y_V_MAX, ui->degrisVmaxY->getValue());

    inst.setValue(TlinsAstroBase::tlinsConfiguration::RAMP_PARAMETER_GROUP,
        TlinsAstroBase::tlinsConfiguration::RAMP_PARAMETER_ASTRO_RA_A, ui->astroARa->getValue());
    inst.setValue(TlinsAstroBase::tlinsConfiguration::RAMP_PARAMETER_GROUP,
        TlinsAstroBase::tlinsConfiguration::RAMP_PARAMETER_ASTRO_RA_D, ui->astroDRa->getValue());
    inst.setValue(TlinsAstroBase::tlinsConfiguration::RAMP_PARAMETER_GROUP,
        TlinsAstroBase::tlinsConfiguration::RAMP_PARAMETER_ASTRO_RA_V_MAX, ui->astroVmaxRa->getValue());

    inst.setValue(TlinsAstroBase::tlinsConfiguration::RAMP_PARAMETER_GROUP,
        TlinsAstroBase::tlinsConfiguration::RAMP_PARAMETER_ASTRO_DC_A, ui->astroADc->getValue());
    inst.setValue(TlinsAstroBase::tlinsConfiguration::RAMP_PARAMETER_GROUP,
        TlinsAstroBase::tlinsConfiguration::RAMP_PARAMETER_ASTRO_DC_D, ui->astroDDc->getValue());
    inst.setValue(TlinsAstroBase::tlinsConfiguration::RAMP_PARAMETER_GROUP,
        TlinsAstroBase::tlinsConfiguration::RAMP_PARAMETER_ASTRO_DC_V_MAX, ui->astroVmaxDc->getValue());

    inst.setValue(TlinsAstroBase::tlinsConfiguration::RAMP_PARAMETER_GROUP,
        TlinsAstroBase::tlinsConfiguration::RAMP_PARAMETER_GUIDING_RA_A, ui->guidingARa->getValue());
    inst.setValue(TlinsAstroBase::tlinsConfiguration::RAMP_PARAMETER_GROUP,
        TlinsAstroBase::tlinsConfiguration::RAMP_PARAMETER_GUIDING_RA_D, ui->guidingDRa->getValue());
    inst.setValue(TlinsAstroBase::tlinsConfiguration::RAMP_PARAMETER_GROUP,
        TlinsAstroBase::tlinsConfiguration::RAMP_PARAMETER_GUIDING_RA_V_MAX, ui->guidingVmaxRa->getValue());

    inst.setValue(TlinsAstroBase::tlinsConfiguration::RAMP_PARAMETER_GROUP,
        TlinsAstroBase::tlinsConfiguration::RAMP_PARAMETER_GUIDING_DC_A, ui->guidingADc->getValue());
    inst.setValue(TlinsAstroBase::tlinsConfiguration::RAMP_PARAMETER_GROUP,
        TlinsAstroBase::tlinsConfiguration::RAMP_PARAMETER_GUIDING_DC_D, ui->guidingDDc->getValue());
    inst.setValue(TlinsAstroBase::tlinsConfiguration::RAMP_PARAMETER_GROUP,
        TlinsAstroBase::tlinsConfiguration::RAMP_PARAMETER_GUIDING_DC_V_MAX, ui->guidingVmaxDc->getValue());
}

void tlinsWSettingsRampParameters::saveDefault()
{
    // Instancja konfiguracji
    auto& inst = TlinsAstroBase::tlinsConfiguration::getInstance();

    inst.setValue(TlinsAstroBase::tlinsConfiguration::RAMP_PARAMETER_GROUP,
        TlinsAstroBase::tlinsConfiguration::RAMP_PARAMETER_STEPS_X_A, DEFAULT_A_STEPS);
    inst.setValue(TlinsAstroBase::tlinsConfiguration::RAMP_PARAMETER_GROUP,
        TlinsAstroBase::tlinsConfiguration::RAMP_PARAMETER_STEPS_X_D, DEFAULT_D_STEPS);
    inst.setValue(TlinsAstroBase::tlinsConfiguration::RAMP_PARAMETER_GROUP,
        TlinsAstroBase::tlinsConfiguration::RAMP_PARAMETER_STEPS_X_V_MAX, DEFAULT_V_MAX_STEPS);

    inst.setValue(TlinsAstroBase::tlinsConfiguration::RAMP_PARAMETER_GROUP,
        TlinsAstroBase::tlinsConfiguration::RAMP_PARAMETER_STEPS_Y_A, DEFAULT_A_STEPS);
    inst.setValue(TlinsAstroBase::tlinsConfiguration::RAMP_PARAMETER_GROUP,
        TlinsAstroBase::tlinsConfiguration::RAMP_PARAMETER_STEPS_Y_D, DEFAULT_D_STEPS);
    inst.setValue(TlinsAstroBase::tlinsConfiguration::RAMP_PARAMETER_GROUP,
        TlinsAstroBase::tlinsConfiguration::RAMP_PARAMETER_STEPS_Y_V_MAX, DEFAULT_V_MAX_STEPS);

    inst.setValue(TlinsAstroBase::tlinsConfiguration::RAMP_PARAMETER_GROUP,
        TlinsAstroBase::tlinsConfiguration::RAMP_PARAMETER_DEGRIS_X_A, 2.0 * __PI__ * static_cast<double>(DEFAULT_A_STEPS) / static_cast<double>(MAX_STEPS));
    inst.setValue(TlinsAstroBase::tlinsConfiguration::RAMP_PARAMETER_GROUP,
        TlinsAstroBase::tlinsConfiguration::RAMP_PARAMETER_DEGRIS_X_D, 2.0 * __PI__ * static_cast<double>(DEFAULT_D_STEPS) / static_cast<double>(MAX_STEPS));
    inst.setValue(TlinsAstroBase::tlinsConfiguration::RAMP_PARAMETER_GROUP,
        TlinsAstroBase::tlinsConfiguration::RAMP_PARAMETER_DEGRIS_X_V_MAX, 2.0 * __PI__ * static_cast<double>(DEFAULT_V_MAX_STEPS) / static_cast<double>(MAX_STEPS));

    inst.setValue(TlinsAstroBase::tlinsConfiguration::RAMP_PARAMETER_GROUP,
        TlinsAstroBase::tlinsConfiguration::RAMP_PARAMETER_DEGRIS_Y_A, 2.0 * __PI__ * static_cast<double>(DEFAULT_A_STEPS) / static_cast<double>(MAX_STEPS));
    inst.setValue(TlinsAstroBase::tlinsConfiguration::RAMP_PARAMETER_GROUP,
        TlinsAstroBase::tlinsConfiguration::RAMP_PARAMETER_DEGRIS_Y_D, 2.0 * __PI__ * static_cast<double>(DEFAULT_D_STEPS) / static_cast<double>(MAX_STEPS));
    inst.setValue(TlinsAstroBase::tlinsConfiguration::RAMP_PARAMETER_GROUP,
        TlinsAstroBase::tlinsConfiguration::RAMP_PARAMETER_DEGRIS_Y_V_MAX, 2.0 * __PI__ * static_cast<double>(DEFAULT_V_MAX_STEPS) / static_cast<double>(MAX_STEPS));

    inst.setValue(TlinsAstroBase::tlinsConfiguration::RAMP_PARAMETER_GROUP,
        TlinsAstroBase::tlinsConfiguration::RAMP_PARAMETER_ASTRO_RA_A, 2.0 * __PI__ * static_cast<double>(DEFAULT_A_STEPS) / static_cast<double>(MAX_STEPS));
    inst.setValue(TlinsAstroBase::tlinsConfiguration::RAMP_PARAMETER_GROUP,
        TlinsAstroBase::tlinsConfiguration::RAMP_PARAMETER_ASTRO_RA_D, 2.0 * __PI__ * static_cast<double>(DEFAULT_D_STEPS) / static_cast<double>(MAX_STEPS));
    inst.setValue(TlinsAstroBase::tlinsConfiguration::RAMP_PARAMETER_GROUP,
        TlinsAstroBase::tlinsConfiguration::RAMP_PARAMETER_ASTRO_RA_V_MAX, 2.0 * __PI__ * static_cast<double>(DEFAULT_V_MAX_STEPS) / static_cast<double>(MAX_STEPS));

    inst.setValue(TlinsAstroBase::tlinsConfiguration::RAMP_PARAMETER_GROUP,
        TlinsAstroBase::tlinsConfiguration::RAMP_PARAMETER_ASTRO_DC_A, 2.0 * __PI__ * static_cast<double>(DEFAULT_A_STEPS) / static_cast<double>(MAX_STEPS));
    inst.setValue(TlinsAstroBase::tlinsConfiguration::RAMP_PARAMETER_GROUP,
        TlinsAstroBase::tlinsConfiguration::RAMP_PARAMETER_ASTRO_DC_D, 2.0 * __PI__ * static_cast<double>(DEFAULT_D_STEPS) / static_cast<double>(MAX_STEPS));
    inst.setValue(TlinsAstroBase::tlinsConfiguration::RAMP_PARAMETER_GROUP,
        TlinsAstroBase::tlinsConfiguration::RAMP_PARAMETER_ASTRO_DC_V_MAX, 2.0 * __PI__ * static_cast<double>(DEFAULT_V_MAX_STEPS) / static_cast<double>(MAX_STEPS));

    inst.setValue(TlinsAstroBase::tlinsConfiguration::RAMP_PARAMETER_GROUP,
        TlinsAstroBase::tlinsConfiguration::RAMP_PARAMETER_GUIDING_RA_A, 2.0 * __PI__ * static_cast<double>(DEFAULT_A_STEPS) / static_cast<double>(MAX_STEPS));
    inst.setValue(TlinsAstroBase::tlinsConfiguration::RAMP_PARAMETER_GROUP,
        TlinsAstroBase::tlinsConfiguration::RAMP_PARAMETER_GUIDING_RA_D, 2.0 * __PI__ * static_cast<double>(DEFAULT_D_STEPS) / static_cast<double>(MAX_STEPS));
    inst.setValue(TlinsAstroBase::tlinsConfiguration::RAMP_PARAMETER_GROUP,
        TlinsAstroBase::tlinsConfiguration::RAMP_PARAMETER_GUIDING_RA_V_MAX, 2.0 * __PI__ * static_cast<double>(DEFAULT_V_MAX_STEPS) / static_cast<double>(MAX_STEPS));

    inst.setValue(TlinsAstroBase::tlinsConfiguration::RAMP_PARAMETER_GROUP,
        TlinsAstroBase::tlinsConfiguration::RAMP_PARAMETER_GUIDING_DC_A, 2.0 * __PI__ * static_cast<double>(DEFAULT_A_STEPS) / static_cast<double>(MAX_STEPS));
    inst.setValue(TlinsAstroBase::tlinsConfiguration::RAMP_PARAMETER_GROUP,
        TlinsAstroBase::tlinsConfiguration::RAMP_PARAMETER_GUIDING_DC_D, 2.0 * __PI__ * static_cast<double>(DEFAULT_D_STEPS) / static_cast<double>(MAX_STEPS));
    inst.setValue(TlinsAstroBase::tlinsConfiguration::RAMP_PARAMETER_GROUP,
        TlinsAstroBase::tlinsConfiguration::RAMP_PARAMETER_GUIDING_DC_V_MAX, 2.0 * __PI__ * static_cast<double>(DEFAULT_V_MAX_STEPS) / static_cast<double>(MAX_STEPS));
}

tlinsWSettingsRampParameters::~tlinsWSettingsRampParameters()
{
    delete ui;
}
