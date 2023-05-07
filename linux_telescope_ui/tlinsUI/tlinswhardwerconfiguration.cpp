#include "tlinswhardwerconfiguration.h"
#include "ui_tlinswhardwerconfiguration.h"

tlinsWHardwerConfiguration::tlinsWHardwerConfiguration(QWidget* parent)
    : QWidget(parent)
    , ui(new Ui::tlinsWHardwerConfiguration)
{
    ui->setupUi(this);
}

tlinsWHardwerConfiguration::~tlinsWHardwerConfiguration()
{
    delete ui;
}
