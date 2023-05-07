#include "tlinswsettingsdatabase.h"
#include "tlinsconfiguration.h"
#include "tlinsuidatabase.h"
#include "tlinsuidatabasedefinition.h"
#include "ui_tlinswsettingsdatabase.h"

#include <stdlib.h>

tlinsWSettingsDatabase::tlinsWSettingsDatabase(QWidget* parent)
    : QWidget(parent)
    , ui(new Ui::tlinsWSettingsDatabase)
{
    ui->setupUi(this);

    connect(ui->selectFile, SIGNAL(clicked(bool)), this, SLOT(selectFile(bool)));
    restore();
}

tlinsWSettingsDatabase::~tlinsWSettingsDatabase()
{
    delete ui;
}

void tlinsWSettingsDatabase::selectFile(bool)
{
    QFileDialog fileSelector(this);

    fileSelector.setNameFilter(tr("Database (*.db)"));
    fileSelector.setFileMode(QFileDialog::AnyFile);

    if (fileSelector.exec()) {
        QStringList fileNames = fileSelector.selectedFiles();
        ui->filePath->clear();
        ui->filePath->insert(fileNames.first());
    }
}

void tlinsWSettingsDatabase::save()
{
    auto& inst = TlinsAstroBase::tlinsConfiguration::getInstance();
    inst.setValueFile(TlinsAstroBase::tlinsConfiguration::DATABASE_GROUP,
        TlinsAstroBase::tlinsConfiguration::DATABASE_FILE, ui->filePath->text().toStdString());
    inst.setValueFile(TlinsAstroBase::tlinsConfiguration::DATABASE_GROUP,
        TlinsAstroBase::tlinsConfiguration::DATABASE_TYPE, ui->databaseType->text().toStdString());
    inst.setValueFile(TlinsAstroBase::tlinsConfiguration::DATABASE_GROUP,
        TlinsAstroBase::tlinsConfiguration::DATABASE_CONNECTION_NAME, ui->connectionName->text().toStdString());
    inst.setValueFile(TlinsAstroBase::tlinsConfiguration::DATABASE_GROUP,
        TlinsAstroBase::tlinsConfiguration::DATABASE_HOST, ui->host->text().toStdString());
    inst.setValueFile(TlinsAstroBase::tlinsConfiguration::DATABASE_GROUP,
        TlinsAstroBase::tlinsConfiguration::DATABASE_USER, ui->user->text().toStdString());
    inst.setValueFile(TlinsAstroBase::tlinsConfiguration::DATABASE_GROUP,
        TlinsAstroBase::tlinsConfiguration::DATABASE_PASSWORD, ui->password->text().toStdString());

    try {
        TlinsAstroBase::tlinsUIDatabase db;
        TlinsAstroBase::tlinsUIDatabaseDefinition dbDef(db);
        dbDef.createDatabae();
    } catch (...) {
        qDebug() << "Error create database !!!";
    }
}

void tlinsWSettingsDatabase::saveDefault()
{
    auto& inst = TlinsAstroBase::tlinsConfiguration::getInstance();
    inst.setValueFile(TlinsAstroBase::tlinsConfiguration::DATABASE_GROUP,
        TlinsAstroBase::tlinsConfiguration::DATABASE_FILE, std::string(getenv("HOME")) + std::string("/.astro.db"));
    inst.setValueFile(TlinsAstroBase::tlinsConfiguration::DATABASE_GROUP,
        TlinsAstroBase::tlinsConfiguration::DATABASE_TYPE, std::string("QSQLITE"));
    inst.setValueFile(TlinsAstroBase::tlinsConfiguration::DATABASE_GROUP,
        TlinsAstroBase::tlinsConfiguration::DATABASE_CONNECTION_NAME, std::string(""));
    inst.setValueFile(TlinsAstroBase::tlinsConfiguration::DATABASE_GROUP,
        TlinsAstroBase::tlinsConfiguration::DATABASE_HOST, std::string { "" });
    inst.setValueFile(TlinsAstroBase::tlinsConfiguration::DATABASE_GROUP,
        TlinsAstroBase::tlinsConfiguration::DATABASE_USER, std::string { "astro" });
    inst.setValueFile(TlinsAstroBase::tlinsConfiguration::DATABASE_GROUP,
        TlinsAstroBase::tlinsConfiguration::DATABASE_PASSWORD, std::string { "password" });

    try {
        TlinsAstroBase::tlinsUIDatabase db;
        TlinsAstroBase::tlinsUIDatabaseDefinition dbDef(db);
        dbDef.createDatabae();
    } catch (...) {
        qDebug() << "Error create database !!!";
    }
}

void tlinsWSettingsDatabase::restore()
{
    auto& inst = TlinsAstroBase::tlinsConfiguration::getInstance();
    ui->filePath->clear();
    ui->filePath->insert(QString::fromStdString(inst.getStringFile(TlinsAstroBase::tlinsConfiguration::DATABASE_GROUP,
        TlinsAstroBase::tlinsConfiguration::DATABASE_FILE)));
    ui->databaseType->clear();
    ui->databaseType->insert(QString::fromStdString(inst.getStringFile(TlinsAstroBase::tlinsConfiguration::DATABASE_GROUP,
        TlinsAstroBase::tlinsConfiguration::DATABASE_TYPE)));
    ui->connectionName->clear();
    ui->connectionName->insert(QString::fromStdString(inst.getStringFile(TlinsAstroBase::tlinsConfiguration::DATABASE_GROUP,
        TlinsAstroBase::tlinsConfiguration::DATABASE_CONNECTION_NAME)));
    ui->host->clear();
    ui->host->insert(QString::fromStdString(inst.getStringFile(TlinsAstroBase::tlinsConfiguration::DATABASE_GROUP,
        TlinsAstroBase::tlinsConfiguration::DATABASE_HOST)));
    ui->user->clear();
    ui->user->insert(QString::fromStdString(inst.getStringFile(TlinsAstroBase::tlinsConfiguration::DATABASE_GROUP,
        TlinsAstroBase::tlinsConfiguration::DATABASE_USER)));
    ui->password->clear();
    ui->password->insert(QString::fromStdString(inst.getStringFile(TlinsAstroBase::tlinsConfiguration::DATABASE_GROUP,
        TlinsAstroBase::tlinsConfiguration::DATABASE_PASSWORD)));
}
