#include "tlinsastroobjectvertical.h"
#include "ui_tlinsastroobjectvertical.h"

tlinsAstroObjectVertical::tlinsAstroObjectVertical(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::tlinsAstroObjectVertical)
{
    ui->setupUi(this);
}

tlinsAstroObjectVertical::~tlinsAstroObjectVertical()
{
    delete ui;
}
