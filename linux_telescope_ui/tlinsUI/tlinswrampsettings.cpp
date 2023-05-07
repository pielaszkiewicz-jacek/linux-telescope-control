#include "tlinswrampsettings.h"
#include "ui_tlinswrampsettings.h"

tlinsWRampSettings::tlinsWRampSettings(QWidget* parent)
    : QWidget(parent)
    , ui(new Ui::tlinsWRampSettings)
{
    ui->setupUi(this);
}

tlinsWRampSettings::~tlinsWRampSettings()
{
    delete ui;
}
