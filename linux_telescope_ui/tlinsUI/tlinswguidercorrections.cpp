#include "tlinswguidercorrections.h"
#include "ui_tlinswguidercorrections.h"

tlinsWGuiderCorrections::tlinsWGuiderCorrections(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::tlinsWGuiderCorrections)
{
	ui->setupUi(this);
}

tlinsWGuiderCorrections::~tlinsWGuiderCorrections()
{
	delete ui;
}
