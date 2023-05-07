#include "tlinswtimedateierssettings.h"
#include "logevent.hpp"
#include "tlinsBacktrace.hpp"
#include "tlinsuidatabase.h"
#include "tlinsuidatabasedefinition.h"
#include "ui_tlinswtimedateierssettings.h"
#include <csvparser.h>

#include <QFileDialog>
#include <QMessageBox>

#include <chrono>
#include <ctime>
#include <iostream>
#include <unistd.h>

#include <memory>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

tlinsWTimeDateIERSSettings::tlinsWTimeDateIERSSettings(QWidget* parent)
    : QWidget { parent }
    , dataModel { parent }
    , ui { new Ui::tlinsWTimeDateIERSSettings }
{
    ui->setupUi(this);

    ui->iersTableView->setModel(&dataModel);

    auto now = std::chrono::system_clock::now();
    std::time_t now_c = std::chrono::system_clock::to_time_t(now);
    struct tm* parts = std::localtime(&now_c);

    ui->year->setValue(static_cast<double>(parts->tm_year + 1900));
    ui->month->setValue(static_cast<double>(parts->tm_mon + 1));
    ui->day->setValue(static_cast<double>(parts->tm_mday));

    ui->year->setDecimal(0);
    ui->year->disableButtons();

    ui->month->setDecimal(0);
    ui->month->disableButtons();

    ui->day->setDecimal(0);
    ui->day->disableButtons();

    ui->ut1_utc->setDecimal(9);
    ui->ut1_utc->disableButtons();

    ui->dPsi->setDecimal(9);
    ui->dPsi->disableButtons();
    ui->dEpsilon->setDecimal(9);
    ui->dEpsilon->disableButtons();

    // Sposob rozciagania kolumn w widoku danych
    ui->iersTableView->horizontalHeader()->resizeSections(QHeaderView::ResizeToContents);
    ui->iersTableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Interactive);
    ui->iersTableView->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
    ui->iersTableView->horizontalHeader()->setFixedHeight(30);

    // Sposob selekcji danych
    ui->iersTableView->setSelectionMode(QAbstractItemView::SingleSelection /* MultiSelection */);
    ui->iersTableView->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->iersTableView->setColumnHidden(dataModel.columnCount() - 1, true);

    auto selModel = ui->iersTableView->selectionModel();
    connect(selModel, SIGNAL(selectionChanged(QItemSelection, QItemSelection)),
        this, SLOT(on_selectionChanged(QItemSelection, QItemSelection)));

    void on_pushButtonSelectFile_clicked();
    void on_loadFile_clicked();

    try {
        loadData();
    } catch (...) {
    }
}

void tlinsWTimeDateIERSSettings::on_selectionChanged(const QItemSelection& selected, const QItemSelection&)
{
    if (selected.size() == 0) {
        return;
    }

    auto list = selected.indexes();
    for (auto& item : list) {
        int row = item.row();
        auto data = dataModel.getData()[row];

        ui->year->setValue(data.getYear());
        ui->month->setValue(data.getMonth());
        ui->day->setValue(data.getDay());

        ui->pmx->setValue(data.getPmx());
        ui->pmy->setValue(data.getPmy());
        //		ui -> pmx -> setValue( data.get);
        //		ui -> pmy -> getValue();
        ui->ut1_utc->setValue(data.getDeltaUt());
        ui->dPsi->setValue(data.getDPsi());
        ui->dEpsilon->setValue(data.getDEpsilon());
        ui->dx->setValue(data.getDx());
        ui->dy->setValue(data.getDy());
        //		ui -> dx -> getValue();
        //		ui -> dy -> getValue();
        break;
    }
}

void tlinsWTimeDateIERSSettings::on_newItem_clicked()
{
    auto now = std::chrono::system_clock::now();
    std::time_t now_c = std::chrono::system_clock::to_time_t(now);
    struct tm* parts = std::localtime(&now_c);

    ui->year->setValue(static_cast<double>(parts->tm_year + 1900));
    ui->month->setValue(static_cast<double>(parts->tm_mon + 1));
    ui->day->setValue(static_cast<double>(parts->tm_mday));
    ui->pmx->setValue(0);
    ui->pmy->setValue(0);
    ui->ut1_utc->setValue(0);
    ui->dPsi->setValue(0);
    ui->dEpsilon->setValue(0);
    ui->dx->setValue(0);
    ui->dy->setValue(0);
}

void tlinsWTimeDateIERSSettings::on_addItem_clicked()
{
    TlinsAstroBase::tlinsIERS item;

    item.setYear(static_cast<int>(ui->year->getValue()));
    item.setMonth(static_cast<int>(ui->month->getValue()));
    item.setDay(static_cast<int>(ui->day->getValue()));

    item.setPmx(ui->pmx->getValue());
    item.setPmy(ui->pmy->getValue());
    item.setDeltaUt(ui->ut1_utc->getValue());
    item.setDPsi(ui->dPsi->getValue());
    item.setDEpsilon(ui->dEpsilon->getValue());
    item.setDx(ui->dx->getValue());
    item.setDy(ui->dy->getValue());

    if (!dataModel.insertItem(item)) {
        QMessageBox msg;
        msg.setText(QString("A new item has not been added due to incorrect data"));
        msg.exec();
    } else {
        ui->iersTableView->horizontalHeader()->resizeSections(QHeaderView::ResizeToContents);
    }
}

bool tlinsWTimeDateIERSSettings::getSelected(std::vector<int>& rows)
{
    if (ui->iersTableView->selectionModel()->hasSelection()) {
        QModelIndexList select = ui->iersTableView->selectionModel()->selectedRows();
        for (int i = 0; i < select.count(); i++) {
            QModelIndex idx = select.at(i);
            rows.push_back(idx.row());
        }
        return true;
    }
    return false;
}

void tlinsWTimeDateIERSSettings::on_removeItem_clicked()
{
    std::vector<int> rows;
    if (!getSelected(rows)) {
        QMessageBox msg;
        msg.setText(QString("Rows need to be selected"));
        msg.exec();
    }

    // Pobranie pozycji z modelu
    std::vector<TlinsAstroBase::tlinsIERS> data;
    for (auto& id : rows)
        dataModel.deleteItem(id);

    ui->iersTableView->horizontalHeader()->resizeSections(QHeaderView::ResizeToContents);

    QMessageBox msg;
    msg.setText(QString("Rows have been removed from the list"));
    msg.exec();
}

void tlinsWTimeDateIERSSettings::on_updateItem_clicked()
{
    std::vector<int> rows;
    getSelected(rows);
    if (rows.size() != 1) {
        QMessageBox msg;
        msg.setText(QString("One row should be selected"));
        msg.exec();
        return;
    }

    TlinsAstroBase::tlinsIERS item;
    item.setYear(static_cast<int>(ui->year->getValue()));
    item.setMonth(static_cast<int>(ui->month->getValue()));
    item.setDay(static_cast<int>(ui->day->getValue()));

    item.setPmx(ui->pmx->getValue());
    item.setPmy(ui->pmy->getValue());
    item.setDeltaUt(ui->ut1_utc->getValue());
    item.setDPsi(ui->dPsi->getValue());
    item.setDEpsilon(ui->dEpsilon->getValue());
    item.setDx(ui->dx->getValue());
    item.setDy(ui->dy->getValue());

    dataModel.updateItem(item);
    ui->iersTableView->horizontalHeader()->resizeSections(QHeaderView::ResizeToContents);

    QMessageBox msg;
    msg.setText(QString("Item updated"));
    msg.exec();
}

void tlinsWTimeDateIERSSettings::on_storeItems_clicked()
{
    TlinsAstroBase::tlinsUIDatabase db;
    TlinsAstroBase::tlinsUIDatabaseDefinition dbDef(db);

    try {
        if (dataModel.getData().size() == 0) {
            QMessageBox msgBox;
            msgBox.setText("No IERS data");
            msgBox.exec();
            return;
        }

        // Usuniecie zawartosci IERS
        db.startTransaction();
        dbDef.clearIERS();
        dbDef.insertIERS(dataModel.getData());
        db.commitTransaction();

        // Dane zapisane do bazy
        QMessageBox msgBox;
        msgBox.setText("IERS saved.");
        msgBox.exec();

        PRINT_LOG(QString("IERS data hve been saved."));
    } catch (TlinsAstroBase::tlinsUIException&) {
        db.rollbackTransaction();
        QMessageBox msg;
        msg.setText(QString("Error insert astro object into database"));
        msg.exec();

        PRINT_LOG(QString("Error insert astro object into database"));
        return;
    }
}

void tlinsWTimeDateIERSSettings::loadData()
{
    TlinsAstroBase::tlinsUIDatabase db;
    TlinsAstroBase::tlinsUIDatabaseDefinition dbDef(db);

    std::vector<TlinsAstroBase::tlinsIERS> data;
    dbDef.selectIERS(data);

    dataModel.getData().clear();
    for (auto& item : data) {
        dataModel.insertItem(item);
    }
}

void tlinsWTimeDateIERSSettings::on_reload_clicked()
{
    try {
        loadData();

        ui->iersTableView->horizontalHeader()->resizeSections(QHeaderView::ResizeToContents);

        QMessageBox msgBox;
        msgBox.setText("IERS data loaded.");
        msgBox.exec();
    } catch (TlinsAstroBase::tlinsUIException&) {
        QMessageBox msg;
        msg.setText(QString("IERS data loaded error."));
        msg.exec();

        PRINT_LOG(QString("IERS data loaded error."));
        return;
    }
}

enum class CsvItesms {
    MJD = 0,
    Year,
    Month,
    Day,
    Type_1,
    X_pole,
    Sigma_x_pole,
    Y_pole,
    Sigma_y_pole,
    Type_2,
    UT1_UTC,
    Sigma_UT1_UTC,
    LOD,
    Sigma_LOD,
    Type_3,
    DPsi,
    Sigma_dPsi,
    DEpsilon,
    Sigma_dEpsilon,
    DX,
    Sigma_dX,
    DY,
    Sigma_dY
};

void tlinsWTimeDateIERSSettings::on_pushButtonSelectFile_clicked()
{
    char buf[1024];

    QString currPth { ::getcwd(buf, sizeof(buf) - 1) };

    QFileDialog dialog(this);
    dialog.setFileMode(QFileDialog::ExistingFile);
    dialog.setReadOnly(true);
    dialog.setOptions(QFileDialog::DontUseNativeDialog | QFileDialog::ReadOnly);

    QString file {};
    if (dialog.exec())
        file = dialog.selectedFiles().first();

    if (!file.isEmpty()) {
        ui->inputFle->setText(file);
    }
}

void tlinsWTimeDateIERSSettings::on_loadFile_clicked()
{
    if (!ui->inputFle->text().isEmpty()) {
        loadFromFile(ui->inputFle->text());

        QMessageBox msg;
        msg.setText(QString("IERS data loaded."));
        msg.exec();
    } else {
        QMessageBox msg;
        msg.setText(QString("No input file"));
        msg.exec();
    }
}

bool tlinsWTimeDateIERSSettings::loadFromFile(const QString& file)
{
    struct stat statInfo;
    if (::stat(file.toStdString().c_str(), &statInfo) < 0) {
        return false;
    }

    CsvParser* csvparser = ::CsvParser_new(file.toStdString().c_str(), ";", 1);
    CsvRow* row = nullptr;

    std::vector<TlinsAstroBase::tlinsIERS> iersData;

    while ((row = CsvParser_getRow(csvparser))) {
        const char** rowFields = ::CsvParser_getFields(row);
        auto rsize = ::CsvParser_getNumFields(row);

        std::shared_ptr<CsvRow> rowPtr { row, [](void* ptr) {
                                            ::CsvParser_destroy_row(reinterpret_cast<CsvRow*>(ptr));
                                        } };

        int idx = 0;

        // Year
        idx = static_cast<int>(CsvItesms::Year);
        if (idx >= rsize)
            continue;
        QString str_year { rowFields[idx] };
        int year { str_year.toInt() };

        // Month
        idx = static_cast<int>(CsvItesms::Month);
        if (idx >= rsize)
            continue;
        QString str_month { rowFields[idx] };
        int month { str_month.toInt() };

        // Day
        idx = static_cast<int>(CsvItesms::Day);
        if (idx >= rsize)
            continue;
        QString str_day { rowFields[idx] };
        int day { str_day.toInt() };

        // Type 1
        idx = static_cast<int>(CsvItesms::Type_1);
        if (idx >= rsize)
            continue;
        QString type1 { rowFields[idx] };

        // x_pole
        idx = static_cast<int>(CsvItesms::X_pole);
        if (idx >= rsize)
            continue;
        QString str_xPole { rowFields[idx] };
        double xPole { str_xPole.toDouble() };

        // y_pole
        idx = static_cast<int>(CsvItesms::Y_pole);
        if (idx >= rsize)
            continue;
        QString str_yPole { rowFields[idx] };
        double yPole { str_yPole.toDouble() };

        // Type 2
        idx = static_cast<int>(CsvItesms::Type_2);
        if (idx >= rsize)
            continue;
        QString type2 { rowFields[idx] };

        // UT1-UTC
        idx = static_cast<int>(CsvItesms::UT1_UTC);
        if (idx >= rsize)
            continue;
        QString str_UT1_UTC { rowFields[idx] };
        double UT1_UTC { str_UT1_UTC.toDouble() };

        // Type 3
        idx = static_cast<int>(CsvItesms::Type_3);
        if (idx >= rsize)
            continue;
        QString type3 { rowFields[idx] };

        // dPsi
        idx = static_cast<int>(CsvItesms::DPsi);
        if (idx >= rsize)
            continue;
        QString str_dPsi { rowFields[idx] };
        double dPsi { str_dPsi.toDouble() };

        // dEpsilon
        idx = static_cast<int>(CsvItesms::DEpsilon);
        if (idx >= rsize)
            continue;
        QString str_dEpsilon { rowFields[idx] };
        double dEpsilon { str_dEpsilon.toDouble() };

        // dX
        idx = static_cast<int>(CsvItesms::DX);
        if (idx >= rsize)
            continue;
        QString str_dX { rowFields[idx] };
        double dX { str_dX.toDouble() };

        // dY
        idx = static_cast<int>(CsvItesms::DY);
        if (idx >= rsize)
            continue;
        QString str_dY { rowFields[idx] };
        double dY { str_dY.toDouble() };

        // Tworzenie instancji
        TlinsAstroBase::tlinsIERS iersItem {};
        iersItem.setYear(year);
        iersItem.setMonth(month);
        iersItem.setDay(day);

        iersItem.setDEpsilon(dEpsilon);
        iersItem.setDPsi(dPsi);
        iersItem.setDx(dX);
        iersItem.setDy(dY);

        iersItem.setPmx(xPole);
        iersItem.setPmy(yPole);
        iersItem.setDeltaUt(UT1_UTC);

        // Dodanie danych do wektora
        iersData.push_back(iersItem);
    }

    TlinsAstroBase::tlinsUIDatabase db;
    TlinsAstroBase::tlinsUIDatabaseDefinition dbDef(db);

    try {

        db.startTransaction();

        if (ui->replaceByFile->isChecked()) {
            // Czyszczenie danych
            dbDef.clearIERS();
        }

        dbDef.insertIERS(iersData);

        db.commitTransaction();

        // Odswiezenie zawartosci kontrolki
        loadData();
    } catch (...) {
        db.rollbackTransaction();
    }

    return true;
}

tlinsWTimeDateIERSSettings::~tlinsWTimeDateIERSSettings()
{
    delete ui;
}
