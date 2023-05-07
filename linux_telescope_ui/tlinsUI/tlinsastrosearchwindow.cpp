#include "tlinsastrosearchwindow.h"
#include "ui_tlinsastrosearchwindow.h"

#include <QDebug>

tlinsAstroSearchWindow::tlinsAstroSearchWindow(QWidget* parent, bool remove_bt)
    : QDialog(parent)
    , ui(new Ui::tlinsAstroSearchWindow)
{
    ui->setupUi(this);

    if (remove_bt) {
        searchWidget.activateRemoveButton();
    }
    lsearchWidget.addWidget(&searchWidget);
    ui->searchWidget->setLayout(&lsearchWidget);

    QSize s;
    s = ui->searchWidget->size();
    ui->searchWidget->resize(s);
}

void tlinsAstroSearchWindow::getSelectedRows(std::vector<int>& records, TlinsAstroBase::tlinsAstroCatalogCollection& result)
{
    ui->searchWidget->getSelectedRows(records, result);
}

tlinsAstroSearchWindow::~tlinsAstroSearchWindow()
{
    delete ui;
}

void tlinsAstroSearchWindow::hideSelectAllButton()
{
    ui->searchWidget->hideSelectAllButton();
}

void tlinsAstroSearchWindow::singleRowSelectionMode()
{
    ui->searchWidget->setSingleLineSelection();
}

void tlinsAstroSearchWindow::on_buttonBox_accepted()
{
    std::vector<int> records;
    TlinsAstroBase::tlinsAstroCatalogCollection result;
    getSelectedRows(records, result);

    if (records.size() != 0) {
        qDebug() << "Selection accepted";
        emit selectionAccepted();
    }
}
