#include "tlinsuiastrodatabasemanagement.h"
#include "logevent.hpp"
#include "tlinsuiastrodatabasemanagement.h"
#include "tlinsuidatabasedefinition.h"
#include "tlinswastrodatabasesearch3.h"
#include "ui_tlinsuiastrodatabasemanagement.h"

#include <QDebug>
#include <QMessageBox>

tlinsUiAstroDatabaseManagement::tlinsUiAstroDatabaseManagement(QWidget* parent)
    : QDialog { parent }
    , ui { new Ui::tlinsUiAstroDatabaseManagement }
{
    ui->setupUi(this);
}

tlinsUiAstroDatabaseManagement::~tlinsUiAstroDatabaseManagement()
{
    delete ui;
}
