#include "tlinswdatabasesearchmain.h"
#include "tlinsastroobjectsviewmodel.h"
#include "tlinsuiconfgiurationitem.h"
#include "tlinsuidatabase.h"
#include "tlinsuidatabasedefinition.h"
#include "tlinswastrodatabasesearch3.h"
#include "ui_tlinswdatabasesearchmain.h"
#include <QDebug>
#include <QLineEdit>
#include <QMessageBox>

tlinsWDatabaseSearchMain::tlinsWDatabaseSearchMain(QWidget* parent)
    : QWidget { parent }
    , proxyModel { this }
    , dataModel { this }
    , searchWidget { this }
    , ui { new Ui::tlinsWDatabaseSearchMain }
{
    ui->setupUi(this);

    // Search widget
    //    searchWidget.setMaximumSize(searchWidget.size() );
    ui->search->setWidget(&searchWidget);
    ui->search->resize(searchWidget.size());

    // Set input mask
    ui->winSize->lineEdit()->setInputMask("999");

    // Prox
    proxyModel.setDynamicSortFilter(true);
    proxyModel.setSourceModel(&dataModel);

    ui->data->setModel(&proxyModel);
    ui->data->setSortingEnabled(true);

    // Sposob rozciagania kolumn w widoku danych
    ui->data->horizontalHeader()->resizeSections(QHeaderView::ResizeToContents);
    ui->data->horizontalHeader()->setSectionResizeMode(QHeaderView::Interactive);
    ui->data->horizontalHeader()->setFixedHeight(30);

    // Sposob selekcji danych
    ui->data->setSelectionMode(QAbstractItemView::ExtendedSelection);
    ui->data->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->data->setColumnHidden(dataModel.columnCount() - 1, true);

    // Sygnaly
    connect(ui->searchButton, SIGNAL(released()), this, SLOT(buttonSearchPresed()));
    connect(ui->next, SIGNAL(released()), this, SLOT(next()));
    connect(ui->previous, SIGNAL(released()), this, SLOT(previous()));
    currentOffset = -1;
    previousOffset = -1;

    totalRowsCount = 0;

    // Domyslnie przycisk remove jest ukryty
    ui->removeButton->setVisible(false);
    ui->removeButton->setEnabled(false);
}

void tlinsWDatabaseSearchMain::setSingleLineSelection()
{
    ui->data->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->data->setSelectionBehavior(QAbstractItemView::SelectRows);
}

void tlinsWDatabaseSearchMain::activateRemoveButton()
{
    ui->removeButton->setVisible(true);
    ui->removeButton->setEnabled(true);
}

void tlinsWDatabaseSearchMain::hideSelectAllButton()
{
    ui->selectButton->setVisible(false);
}

void tlinsWDatabaseSearchMain::next()
{
    currentOffset = ui->actualOffset->value();
    int wSize = std::stoi(ui->winSize->currentText().toStdString());

    if ((currentOffset * wSize) < totalRowsCount) {
        fetchData(offsetOperation::OFFSET_INCREASE);
    }

    // Resize columns
    ui->data->horizontalHeader()->resizeSections(QHeaderView::ResizeToContents);
}

void tlinsWDatabaseSearchMain::previous()
{
    fetchData(offsetOperation::OFFSET_DECRASE);

    // Resize columns
    ui->data->horizontalHeader()->resizeSections(QHeaderView::ResizeToContents);
}

void tlinsWDatabaseSearchMain::fetchData(offsetOperation increaseOffset)
{
    ui->data->clearSelection();

    //	// Pobranie instancji bazy danych
    //	std:: shared_ptr<tlinsUiConfgiurationItem> value;
    //	if( !tlinsUiConfgiurationItemsCollection::getItem( "SYSTEM::DB", "DB_NAME", value ) )
    //	{
    //		qDebug() << "No database configuration";
    //		return;
    //	}

    // Rozmiar okna danych
    int wSize = std::stoi(ui->winSize->currentText().toStdString());

    if (increaseOffset == offsetOperation::OFFSET_DECRASE) {
        currentOffset--;
        if (currentOffset < 0)
            currentOffset = 0;
    } else if (increaseOffset == offsetOperation::OFFSET_INCREASE) {
        currentOffset++;
    }

    try {
        int rowCount = 0;
        TlinsAstroBase::tlinsUIDatabase db;

        // Database definition
        TlinsAstroBase::tlinsUIDatabaseDefinition dbDef(db);

        // Read database
        TlinsAstroBase::tlinsAstroCatalogCollection outputCollection;
        tlinsWAstroDatabaseSearch3* w = reinterpret_cast<tlinsWAstroDatabaseSearch3*>(ui->search->widget());
        dbDef.selectAstroObjects(w->getCondition(), (currentOffset)*wSize, wSize, outputCollection);

        rowCount = outputCollection.count();

        if (rowCount == 0 && increaseOffset != offsetOperation::OFFSET_NON) {
            currentOffset--;
            if (currentOffset < 0)
                currentOffset = 0;
        } else {
            ui->data->reset();
            dataModel.setData(outputCollection);
        }
        ui->actualOffset->setValue(currentOffset);
    } catch (TlinsAstroBase::tlinsUIException&) {
    }
}

void tlinsWDatabaseSearchMain::buttonSearchPresed()
{
    {
        // Open database connection
        TlinsAstroBase::tlinsUIDatabase db;

        // Database definition
        TlinsAstroBase::tlinsUIDatabaseDefinition dbDef(db);

        try {
            totalRowsCount = dbDef.countAstroObjects(searchWidget.getCondition());
            qDebug() << "Query ROWS COUNT = " << totalRowsCount;
        } catch (TlinsAstroBase::tlinsUIException&) {
            totalRowsCount = 0;
        }
    }

    if (totalRowsCount == 0) {
        TlinsAstroBase::tlinsAstroCatalogCollection outputCollection;
        ui->data->reset();
        dataModel.setData(outputCollection);
    } else {
        // Read database
        currentOffset = -1;
        fetchData(offsetOperation::OFFSET_INCREASE);
    }
    ui->data->horizontalHeader()->resizeSections(QHeaderView::ResizeToContents);
}

void tlinsWDatabaseSearchMain::insertRecord(TlinsAstroBase::tlinsAstroCatalogItem& v)
{
    dataModel.insertDataItem(v);

    ui->data->reset();
    ui->data->clearSelection();
    ui->data->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
    dataModel.confirm();
}

void tlinsWDatabaseSearchMain::removeRecords(TlinsAstroBase::tlinsAstroCatalogCollection& records)
{
    dataModel.deleteDataItems(records);

    ui->data->reset();
    ui->data->clearSelection();
    ui->data->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
    dataModel.confirm();
}

bool tlinsWDatabaseSearchMain::updateRecord(int id, TlinsAstroBase::tlinsAstroCatalogItem& v)
{
    if (id >= dataModel.getData().count())
        return false;

    dataModel.updateDataItem(id, v);

    // Pobranie zaznaczonego wiersza
    int rowNum = ui->data->selectionModel()->selectedRows().begin()->row();

    // Czyszczenie wyselektowanych danych
    ui->data->clearSelection();

    // Ponowne zaznaczenie
    ui->data->selectRow(rowNum);

    ui->data->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);

    dataModel.confirm();

    return true;
}

void tlinsWDatabaseSearchMain::getSelectedRows(std::vector<int>& out, TlinsAstroBase::tlinsAstroCatalogCollection& result)
{
    if (ui->data->selectionModel()->hasSelection()) {
        QModelIndexList select = ui->data->selectionModel()->selectedRows();
        for (int i = 0; i < select.count(); i++) {
            QModelIndex idx = select.at(i);
            out.push_back(proxyModel.index(idx.row(), dataModel.columnCount() - 1).data().toInt());

            int ii = proxyModel.index(idx.row(), dataModel.columnCount() - 1).data().toInt();
            auto item = dataModel.getData().getItem(ii);
            result.addItem(item);
        }
    }
}

tlinsWDatabaseSearchMain::~tlinsWDatabaseSearchMain()
{
    delete ui;
}

void tlinsWDatabaseSearchMain::on_selectButton_clicked()
{
    ui->data->selectAll();
}

void tlinsWDatabaseSearchMain::on_deselectButton_clicked()
{
    ui->data->selectionModel()->clearSelection();
}

void tlinsWDatabaseSearchMain::on_actualOffset_valueChanged(int)
{
    currentOffset = ui->actualOffset->value();
    int wSize = std::stoi(ui->winSize->currentText().toStdString());

    if ((currentOffset * wSize) >= totalRowsCount) {
        currentOffset = totalRowsCount / wSize - 1;
        ui->actualOffset->setValue(currentOffset);
    }

    if (previousOffset != currentOffset) {
        previousOffset = currentOffset;
        fetchData(offsetOperation::OFFSET_NON);
    }
}

void tlinsWDatabaseSearchMain::on_removeButton_clicked()
{
    std::vector<int> recordsId;
    TlinsAstroBase::tlinsAstroCatalogCollection records;

    getSelectedRows(recordsId, records);
    if (recordsId.size() == 0) {
        QMessageBox msg;
        msg.setText(QString("Select rows to be remove from the list"));
        msg.exec();
        return;
    }

    removeRecords(records);
}
