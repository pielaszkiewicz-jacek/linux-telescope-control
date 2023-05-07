#include "tlinssinglecoordinate.h"
#include "ui_tlinssinglecoordinate.h"

tlinsSingleCoordinate::tlinsSingleCoordinate(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::tlinsSingleCoordinate)
{
    ui->setupUi(this);
}

tlinsSingleCoordinate::~tlinsSingleCoordinate()
{
    delete ui;
}
