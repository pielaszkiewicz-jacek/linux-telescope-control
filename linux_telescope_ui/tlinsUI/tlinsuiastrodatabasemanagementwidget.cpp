#include "tlinsuiastrodatabasemanagementwidget.h"
#include "logevent.hpp"
#include "tlinsuiastrodatabasemanagement.h"
#include "tlinsuidatabasedefinition.h"
#include "tlinswastrodatabasesearch3.h"
#include "ui_tlinsuiastrodatabasemanagementwidget.h"

#include <QDebug>
#include <QMessageBox>

tlinsUiAstroDatabaseManagementWidget::tlinsUiAstroDatabaseManagementWidget(QWidget* parent)
    : QWidget(parent)
    , editObject { this }
    , ui(new Ui::tlinsUiAstroDatabaseManagementWidget)
{
    ui->setupUi(this);

    QSize s;
    s = ui->searchWidget->size();
    ui->searchWidget->resize(s);

    // Sygnal obslugujacy mopdyfikacje i zmiany obiektu
    connect(&editObject, SIGNAL(objectChanged(TlinsAstroBase::tlinsAstroCatalogItem, int)), this, SLOT(objectChanged(TlinsAstroBase::tlinsAstroCatalogItem, int)));
    connect(&editObject, SIGNAL(objectCreated(TlinsAstroBase::tlinsAstroCatalogItem)), this, SLOT(objectCreated(TlinsAstroBase::tlinsAstroCatalogItem)));
}

void tlinsUiAstroDatabaseManagementWidget::objectCreated(TlinsAstroBase::tlinsAstroCatalogItem v)
{
    qDebug() << "Object created";

    // 1. Modyfikacja bazy danych
    try {
        TlinsAstroBase::tlinsUIDatabase db;

        // Database definition
        TlinsAstroBase::tlinsUIDatabaseDefinition dbDef(db);

        // Read database
        std::vector<TlinsAstroBase::tlinsAstroCatalogItem> items;
        items.push_back(v);
        dbDef.insertAstroObjects(items);
    } catch (TlinsAstroBase::tlinsUIException&) {
        QMessageBox msg;
        msg.setText(QString("Error insert astro object into database"));

        emit getMainWindowInstance()->logEvent(msg.text());

        msg.exec();

        PRINT_LOG(QString("Error insert astro object into database"));
        return;
    }

    // 2. Modyfikacja obiektu w liscie
    ui->searchWidget->insertRecord(v);

    QMessageBox msg;
    msg.setText(QString("Record inserted into database"));
    msg.exec();
}

void tlinsUiAstroDatabaseManagementWidget::objectChanged(TlinsAstroBase::tlinsAstroCatalogItem v, int id)
{
    qDebug() << "Object updated";

    // 1. Modyfikacja bazy danych
    try {
        TlinsAstroBase::tlinsUIDatabase db;

        // Database definition
        TlinsAstroBase::tlinsUIDatabaseDefinition dbDef(db);

        // Read database
        std::vector<TlinsAstroBase::tlinsAstroCatalogItem> items;
        items.push_back(v);
        items[0].setRecordID(id);
        dbDef.updateAstroObjects(items);
    } catch (TlinsAstroBase::tlinsUIException&) {
        QMessageBox msg;
        msg.setText(QString("Error update database"));
        emit getMainWindowInstance()->logEvent(msg.text());
        msg.exec();
        PRINT_LOG(QString("Error update database"));
        return;
    }

    // 2. Modyfikacja obiektu w liscie
    ui->searchWidget->updateRecord(id, v);

    QMessageBox msg;
    msg.setText(QString("Record updated"));
    msg.exec();
}

void tlinsUiAstroDatabaseManagementWidget::on_addButton_clicked()
{
    editObject.reset();
    editObject.setIsUpdate(false);
    editObject.show();
}

void tlinsUiAstroDatabaseManagementWidget::on_editButton_clicked()
{
    std::vector<int> recordsIndex;
    TlinsAstroBase::tlinsAstroCatalogCollection result;

    // Pobranie zaznaczonych wierszy
    ui->searchWidget->getSelectedRows(recordsIndex, result);
    if (result.count() > 1) {
        QMessageBox msgBox;
        msgBox.setText("Select one object only");
        msgBox.exec();
        return;
    }

    if (result.count() < 1) {
        QMessageBox msgBox;
        msgBox.setText("Please slect any object");
        msgBox.exec();
        return;
    }
    editObject.setCatalogItem(result.getItem(0), recordsIndex[0]);

    editObject.setIsUpdate(true);
    editObject.show();
}

void tlinsUiAstroDatabaseManagementWidget::on_deleteButton_clicked()
{
    std::vector<int> recordsIndex;
    TlinsAstroBase::tlinsAstroCatalogCollection result;

    // Pobranie zaznaczonych wierszy
    ui->searchWidget->getSelectedRows(recordsIndex, result);

    if (result.count() < 1) {
        QMessageBox msgBox;
        msgBox.setText("Select one or more rows");
        msgBox.exec();
        return;
    }

    // 1. Modyfikacja bazy danych
    try {
        TlinsAstroBase::tlinsUIDatabase db;

        // Database definition
        TlinsAstroBase::tlinsUIDatabaseDefinition dbDef(db);

        // Delete records from database

        std::vector<std::pair<std::string, std::string>> objects;

        for (int i = 0; i < result.count(); i++) {
            auto item = result.getItem(i);
            objects.push_back(std::pair<std::string, std::string>(item.getCatalogType().label, item.getObjectIdInCatalog()));
        }

        dbDef.removeAstroObjects(objects);
    } catch (TlinsAstroBase::tlinsUIException&) {
        QMessageBox msg;
        msg.setText(QString("Error remove records from database"));
        emit getMainWindowInstance()->logEvent(msg.text());
        msg.exec();
        return;
    }

    // Update list
    ui->searchWidget->removeRecords(result);

    QMessageBox msg;
    msg.setText(QString("Records removed from database sucessfully"));
    msg.exec();
}

void tlinsUiAstroDatabaseManagementWidget::on_importButton_clicked()
{
}

tlinsUiAstroDatabaseManagementWidget::~tlinsUiAstroDatabaseManagementWidget()
{
    delete ui;
}
