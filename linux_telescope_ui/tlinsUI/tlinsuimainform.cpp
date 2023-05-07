#include "tlinsuimainform.h"
#include "ui_tlinsuimainform.h"

tlinsUiMainForm::tlinsUiMainForm(QWidget* parent)
    : QWidget(parent)
    , ui(new Ui::tlinsUiMainForm)
{
    ui->setupUi(this);
}

tlinsUiMainForm::~tlinsUiMainForm()
{
    delete ui;
}
