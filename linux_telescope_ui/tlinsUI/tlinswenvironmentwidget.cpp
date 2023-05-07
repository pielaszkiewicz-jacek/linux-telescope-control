#include "tlinswenvironmentwidget.h"
#include "tlinsenvironment.h"
#include "ui_tlinswenvironmentwidget.h"

tlinsWEnvironmentWidget::tlinsWEnvironmentWidget(QWidget* parent)
    : QWidget(parent)
    , ui(new Ui::tlinsWEnvironmentWidget)
{
    ui->setupUi(this);
    connect(ui->buttons, SIGNAL(accepted()), this, SLOT(accepted()));
}

void tlinsWEnvironmentWidget::accepted()
{
    auto& ins = tlinsEnvironment::getInstance();
    ins.setAmbientPressure(ui->env->getAmbientPressure());
    ins.setEffectiveColor(ui->env->getEffectiveColor());
    ins.setRealHumidity(ui->env->getRealHumidity());
    ins.setTemperature(ui->env->getTemperature());
}

tlinsWEnvironmentWidget::~tlinsWEnvironmentWidget()
{
    delete ui;
}
