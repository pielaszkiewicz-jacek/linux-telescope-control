#include "tlinswenvironmentwindow.h"
#include "tlinsenvironment.h"
#include "ui_tlinswenvironmentwindow.h"

tlinsWEnvironmentWindow::tlinsWEnvironmentWindow(QWidget* parent)
    : QDialog(parent)
    , ui(new Ui::tlinsWEnvironmentWindow)
{
    ui->setupUi(this);
    connect(ui->buttons, SIGNAL(accepted()), this, SLOT(accepted()));
}

void tlinsWEnvironmentWindow::accepted()
{
    auto& ins = tlinsEnvironment::getInstance();
    ins.setAmbientPressure(ui->env->getAmbientPressure());
    ins.setEffectiveColor(ui->env->getEffectiveColor());
    ins.setRealHumidity(ui->env->getRealHumidity());
    ins.setTemperature(ui->env->getTemperature());
}

tlinsWEnvironmentWindow::~tlinsWEnvironmentWindow()
{
    delete ui;
}
