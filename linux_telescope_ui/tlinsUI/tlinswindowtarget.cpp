#include "tlinswindowtarget.h"
#include "ui_tlinswindowtarget.h"

tlinsWindowTarget::tlinsWindowTarget(QWidget* parent)
    : QDialog(parent)
    , ui(new Ui::tlinsWindowTarget)
{
    ui->setupUi(this);
}

tlinsWindowTarget::~tlinsWindowTarget()
{
    delete ui;
}
