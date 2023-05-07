#include "tlinswobservationplace.h"
#include "logevent.hpp"
#include "tlinsBacktrace.hpp"
#include "tlinsuidatabase.h"
#include "tlinsuidatabasedefinition.h"
#include "ui_tlinswobservationplace.h"

#include <QMessageBox>

tlinsWObservationPlace::tlinsWObservationPlace(QWidget* parent)
    : QWidget(parent)
    , ui(new Ui::tlinsWObservationPlace)
{
    ui->setupUi(this);

    ui->places->setModel(&dataModel);

    ui->longitude->setValue(0);
    ui->latitude->setValue(0);
    ui->name->setText("");
    ui->elipsoideType->setCurrentIndex(0);
    ui->isDefault->setChecked(false);

    ui->hm->setDecimal(9);
    ui->hm->setValue(0);

    // Sposob rozciagania kolumn w widoku danych
    ui->places->horizontalHeader()->resizeSections(QHeaderView::ResizeToContents);
    ui->places->horizontalHeader()->setSectionResizeMode(QHeaderView::Interactive);
    ui->places->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
    ui->places->horizontalHeader()->setFixedHeight(30);

    // Sposob selekcji danych
    ui->places->setSelectionMode(QAbstractItemView::SingleSelection /* MultiSelection */);
    ui->places->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->places->setColumnHidden(dataModel.columnCount() - 1, true);

    auto selModel = ui->places->selectionModel();
    connect(selModel, SIGNAL(selectionChanged(QItemSelection, QItemSelection)),
        this, SLOT(on_selectionChanged(QItemSelection, QItemSelection)));

    try {
        on_reloadItems_clicked();
    } catch (...) {
    }
}

void tlinsWObservationPlace::on_selectionChanged(const QItemSelection& selected, const QItemSelection&)
{
    if (selected.size() == 0) {
        return;
    }

    auto list = selected.indexes();
    for (auto& item : list) {
        int row = item.row();
        auto data = dataModel.getData()[row];

        ui->longitude->setValue(data.getLongitude());
        ui->latitude->setValue(data.getLatitude());
        ui->name->setText(QString::fromStdString(data.getName()));

        switch (data.getEpType()) {
        case TlinsAstroBase::tlinsPlace::ElipsoideType::GRS_80:
            break;
        case TlinsAstroBase::tlinsPlace::ElipsoideType::WGS_72:
            break;
        case TlinsAstroBase::tlinsPlace::ElipsoideType::WGS_84:
            break;
        }

        ui->elipsoideType->setCurrentIndex(0);
        ui->isDefault->setChecked(data.isDefault());
        ui->hm->setValue(data.getHm());
        break;
    }
}

tlinsWObservationPlace::~tlinsWObservationPlace()
{
    delete ui;
}

void tlinsWObservationPlace::on_updateItem_clicked()
{
    TlinsAstroBase::tlinsPlace item;

    item.setName(ui->name->text().toStdString());
    item.setDefault(ui->isDefault->isChecked() ? true : false);
    item.setLatitude(ui->latitude->getValue());
    item.setLongitude(ui->longitude->getValue());
    item.setHm(ui->hm->getValue());

    if (ui->elipsoideType->currentText() == "WGS_84")
        item.setEpType(TlinsAstroBase::tlinsPlace::ElipsoideType::WGS_84);
    else if (ui->elipsoideType->currentText() == "GRS_80")
        item.setEpType(TlinsAstroBase::tlinsPlace::ElipsoideType::GRS_80);
    else if (ui->elipsoideType->currentText() == "WGS_72")
        item.setEpType(TlinsAstroBase::tlinsPlace::ElipsoideType::WGS_72);

    dataModel.updateItem(item);
    ui->places->horizontalHeader()->resizeSections(QHeaderView::ResizeToContents);
}

void tlinsWObservationPlace::on_addItem_clicked()
{
    TlinsAstroBase::tlinsPlace item;

    item.setName(ui->name->text().toStdString());
    item.setDefault(ui->isDefault->isChecked() ? true : false);
    item.setLatitude(ui->latitude->getValue());
    item.setLongitude(ui->longitude->getValue());
    item.setHm(ui->hm->getValue());

    if (item.getName().empty()) {
        QMessageBox msg;
        msg.setText(QString("Name is empty"));
        msg.exec();
        return;
    }

    if (ui->elipsoideType->currentText() == "WGS_84")
        item.setEpType(TlinsAstroBase::tlinsPlace::ElipsoideType::WGS_84);
    else if (ui->elipsoideType->currentText() == "GRS_80")
        item.setEpType(TlinsAstroBase::tlinsPlace::ElipsoideType::GRS_80);
    else if (ui->elipsoideType->currentText() == "WGS_72")
        item.setEpType(TlinsAstroBase::tlinsPlace::ElipsoideType::WGS_72);

    if (!dataModel.insertItem(item)) {
        QMessageBox msg;
        msg.setText(QString("A new item has not been added due to incorrect data"));
        msg.exec();
    } else {
        ui->places->horizontalHeader()->resizeSections(QHeaderView::ResizeToContents);
    }
}

bool tlinsWObservationPlace::getSelected(std::vector<int>& rows)
{
    if (ui->places->selectionModel()->hasSelection()) {
        QModelIndexList select = ui->places->selectionModel()->selectedRows();
        for (int i = 0; i < select.count(); i++) {
            QModelIndex idx = select.at(i);
            rows.push_back(idx.row());
        }
        return true;
    }
    return false;
}

void tlinsWObservationPlace::on_deleteItem_clicked()
{
    std::vector<int> rows;
    if (!getSelected(rows)) {
        QMessageBox msg;
        msg.setText(QString("Rows need to be selected"));
        msg.exec();
    }

    // Pobranie pozycji z modelu
    std::vector<TlinsAstroBase::tlinsPlace> data;
    for (auto id : rows) {
        data.push_back(dataModel.getData()[id]);
    }

    // Remove items from the list
    dataModel.deleteItems(data);

    ui->places->horizontalHeader()->resizeSections(QHeaderView::ResizeToContents);

    QMessageBox msg;
    msg.setText(QString("Rows have been removed from the list"));
    msg.exec();
}

void tlinsWObservationPlace::on_newItem_clicked()
{
    ui->longitude->setValue(0.0);
    ui->latitude->setValue(0.0);
    ui->name->setText("New item");
    ui->elipsoideType->setCurrentIndex(0);
    ui->isDefault->setChecked(false);
    ui->hm->setValue(0.0);
}

void tlinsWObservationPlace::on_saveItems_clicked()
{
    TlinsAstroBase::tlinsUIDatabase db;
    TlinsAstroBase::tlinsUIDatabaseDefinition dbDef(db);

    try {
        // Usuniecie zawartosci IERS
        db.startTransaction();
        dbDef.clearPlaces();
        dbDef.insertPlaces(dataModel.getData());
        db.commitTransaction();

        // Dane zapisane do bazy
        QMessageBox msgBox;
        msgBox.setText("Observation places saved.");
        msgBox.exec();

        PRINT_LOG(QString("Observation places data hve been saved."));
    } catch (TlinsAstroBase::tlinsUIException&) {
        db.rollbackTransaction();
        QMessageBox msg;
        msg.setText(QString("Error insert observation places data"));
        msg.exec();

        PRINT_LOG(QString("Error insert §bservation places into database"));
        return;
    }
}

void tlinsWObservationPlace::on_reloadItems_clicked()
{
    try {
        TlinsAstroBase::tlinsUIDatabase db;
        TlinsAstroBase::tlinsUIDatabaseDefinition dbDef(db);

        std::vector<TlinsAstroBase::tlinsPlace> data;
        dbDef.selectAllPlaces(data);
        dataModel.clear();

        for (auto& item : data)
            dataModel.insertItem(item);

        ui->places->horizontalHeader()->resizeSections(QHeaderView::ResizeToContents);
    } catch (TlinsAstroBase::tlinsUIException& exc) {
        QMessageBox msg;
        msg.setText(QString("Error reload data"));
        msg.exec();
        PRINT_LOG(QString("Error reload data"));
    }
}
