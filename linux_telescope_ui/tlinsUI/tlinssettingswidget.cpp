#include "tlinssettingswidget.h"
#include "ui_tlinssettingswidget.h"

#include <QMessageBox>

tlinsSettingsWidget::tlinsSettingsWidget(QWidget* parent)
    : QWidget(parent)
    , ui(new Ui::tlinsSettingsWidget)
{
    ui->setupUi(this);

    saveAll = new QPushButton("Save all");
    saveAll->setAutoDefault(false);
    saveAll->setAutoRepeat(false);

    save = new QPushButton("Save");
    save->setAutoDefault(false);
    save->setAutoRepeat(false);

    defaults = new QPushButton("Defaults");
    defaults->setAutoDefault(false);
    defaults->setAutoRepeat(false);

    reject = new QPushButton("Discard");
    reject->setAutoDefault(false);
    reject->setAutoRepeat(false);

    ui->buttonBox->addButton(save, QDialogButtonBox::ActionRole);
    ui->buttonBox->addButton(saveAll, QDialogButtonBox::ActionRole);
    ui->buttonBox->addButton(defaults, QDialogButtonBox::ActionRole);
    ui->buttonBox->addButton(reject, QDialogButtonBox::ActionRole);

    objMap["connection"] = ui->connectionConfiguration;
    objMap["ramp"] = ui->rampConfiguration;
    objMap["database"] = ui->databaseConfiguration;
    objMap["observationErrors"] = ui->observationErrors;
    objMap["calibration"] = ui->calibration;
    objMap["pilot"] = ui->pilot;

    ui->tabRampSettings->setProperty("key", QVariant("ramp"));
    ui->tabConnection->setProperty("key", QVariant("connection"));
    ui->tabDatabase->setProperty("key", QVariant("database"));
    ui->tabObservationErrors->setProperty("key", QVariant("observationErrors"));
    ui->tabCalibration->setProperty("key", QVariant("calibration"));
    ui->tabPilot->setProperty("key", QVariant("pilot"));

    connect(saveAll, SIGNAL(pressed()), this, SLOT(saveAllSlot()));
    connect(save, SIGNAL(pressed()), this, SLOT(saveSlot()));
    connect(defaults, SIGNAL(pressed()), this, SLOT(defaultsSlot()));
    connect(reject, SIGNAL(pressed()), this, SLOT(discardSlot()));
}

void tlinsSettingsWidget::saveSlot()
{
    auto w = ui->tabWidget->currentWidget();
    auto var = w->property("key");
    if (var.isValid())
        objMap[var.toString().toStdString()]->save();

    QMessageBox msgBox;
    msgBox.setText("Changes saved.");
    msgBox.exec();
}

void tlinsSettingsWidget::saveAllSlot()
{
    for (auto iter = objMap.begin(); iter != objMap.end(); iter++) {
        iter->second->save();
    }

    QMessageBox msgBox;
    msgBox.setText("All changes saved.");
    msgBox.exec();
}

void tlinsSettingsWidget::defaultsSlot()
{
    auto w = ui->tabWidget->currentWidget();
    auto var = w->property("key");
    if (var.isValid()) {
        objMap[var.toString().toStdString()]->saveDefault();
        objMap[var.toString().toStdString()]->restore();
    }

    QMessageBox msgBox;
    msgBox.setText("Settings have been restored to default values.");
    msgBox.exec();
}

void tlinsSettingsWidget::discardSlot()
{
    auto w = ui->tabWidget->currentWidget();
    auto var = w->property("key");
    if (var.isValid()) {
        objMap[var.toString().toStdString()]->restore();
    }

    QMessageBox msgBox;
    msgBox.setText("Changes have been discarded.");
    msgBox.exec();
}

tlinsSettingsWidget::~tlinsSettingsWidget()
{
    if (save != nullptr)
        delete save;
    if (defaults != nullptr)
        delete defaults;
    if (reject != nullptr)
        delete reject;
    if (saveAll != nullptr)
        delete saveAll;
    if (ui != nullptr)
        delete ui;
}
