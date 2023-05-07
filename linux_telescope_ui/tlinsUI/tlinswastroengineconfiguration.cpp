#include "tlinswastroengineconfiguration.h"
#include "ui_tlinswastroengineconfiguration.h"

tlinsWAstroEngineConfiguration::tlinsWAstroEngineConfiguration(QWidget* parent)
    : QWidget(parent)
    , ui(new Ui::tlinsWAstroEngineConfiguration)
{
    ui->setupUi(this);
}

tlinsWAstroEngineConfiguration::~tlinsWAstroEngineConfiguration()
{
    delete ui;
}
