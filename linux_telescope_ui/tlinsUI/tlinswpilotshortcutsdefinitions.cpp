#include "tlinswpilothorisintalverticalincrement.h"
#include "ui_tlinswpilotshortcutsdefinitions.h"
#include <tlinswpilotshortcutsdefinitions.h>

#include "tlinswpilotclosecalibration.h"
#include "tlinswpilotclosevelocitymeasurment.h"
#include "tlinswpilothorisintalverticalsteps.h"
#include "tlinswpilothvdelta.h"
#include "tlinswpilothvspeeddelta.h"
#include "tlinswpilotradcdelta.h"
#include "tlinswpilotradcincrement.h"
#include "tlinswpilotradcspeeddelta.h"
#include "tlinswpilotsetreferenceobject.h"
#include "tlinswpilotsetvelocitymeasurment.h"
#include "tlinswpilotstartresetcalibration.h"
#include "tlinswpilottrackingstart.h"
#include "tlinswpilottrackingstop.h"
#include <tlinsBacktrace.hpp>
#include <tlinsuidatabase.h>
#include <tlinsuidatabasedefinition.h>

#include "tlinswpilothorisontalverticalkeys.h"

#include <QRegExp>
#include <QString>
#include <iterator>
#include <regex>
#include <set>
#include <string>

#include <QDebug>
#include <QMessageBox>
#include <algorithm>

//
// ----
//
static std::vector<std::string> __columns__ = {
    "Shortcut name",
    "Type",
    "Sub type",
    "Default",
    "Action name",
    "Mode",
    "Keys",
    "Configuration"
};

static std::map<std::string, std::string> configsActionsMap = { { "horisontal-vertical-move", "Horisontal/vertical move" },
    { "horisontal-vertical-move-keys", "Horisontal/vertical move (keys)" },
    { "horisontal-vertical-delta", "Horisontal/vertical set delta" },
    { "horisontal-vertical-speed-delta", "Horisontal/vertical set speed delta" },
    { "horisintal-vertical-steps", "Horisontal/vertical steps move" },
    { "hour-amgle-declination-delta", "Hour angle/declination set delta" },
    { "hour-amgle-declination-speed-delta", "Hour angle/declination set speed delta" },
    { "hour-amgle-declination-move-increment", "Hour angle/declination move" },
    { "start-reset-calibration", "Start/reset calibration" },
    { "set-reference-object", "Set reference object" },
    { "close-calibration", "Close calibration" },
    { "tracking-start", "Objerct tracking enable" },
    { "tracking-stop", "Objerct tracking disable" } };

int tlinsShortcutDefinitionModel::rowCount(const QModelIndex&) const
{
    return static_cast<int>(actionsData.size());
}

int tlinsShortcutDefinitionModel::columnCount(const QModelIndex&) const
{
    return static_cast<int>(__columns__.size());
}

QVariant tlinsShortcutDefinitionModel::data(const QModelIndex& index, int role) const
{
    int row = index.row();
    int column = index.column();

    QVariant out;
    TlinsAstroBase::tlinsKeysSortcut dataRow = actionsData[static_cast<unsigned int>(row)];

    if (role == Qt::TextAlignmentRole)
        return QVariant(Qt::AlignVCenter | Qt::AlignLeft);

    if (role == Qt::DisplayRole) {
        switch (column) {
        case 0:
            out = dataRow.getShortcutName().c_str();
            break;

        case 1:
            switch (dataRow.getType()) {
            case TlinsAstroBase::tlinsKeysSortcutType::JOYSTICK:
                out = "Joystick";
                break;
            case TlinsAstroBase::tlinsKeysSortcutType::KEYBOARD:
                out = "Keyboard";
                break;
            }
            break;

        case 2:
            switch (dataRow.getSubType()) {
            case TlinsAstroBase::tlinsKeysSortcutSubType::ANY:
                out = "Any";
                break;
            case TlinsAstroBase::tlinsKeysSortcutSubType::JOYSTICK_KEYS:
                out = "Keys";
                break;
            case TlinsAstroBase::tlinsKeysSortcutSubType::JOYSTICK_GAMEPAD:
                out = "Gamepad";
                break;
            }
            break;

        case 3:
            switch (dataRow.getDefaultHandler()) {
            case TlinsAstroBase::tlinsDefaultHandler::NO:
                out = "";
                break;
            case TlinsAstroBase::tlinsDefaultHandler::YES:
                out = "Default";
                break;
            }
            break;

        case 4:
            out = configsActionsMap[dataRow.getActionName()].c_str();
            break;

        case 5:
            switch (dataRow.getActionMode()) {
            case TlinsAstroBase::tlinsPilotShortcutsDefinitionValidMode::ASTRO:
                out = "Astro";
                break;
            case TlinsAstroBase::tlinsPilotShortcutsDefinitionValidMode::DEVICE:
                out = "Device";
                break;
            case TlinsAstroBase::tlinsPilotShortcutsDefinitionValidMode::BOTH:
                out = "Astro and device";
                break;
            }
            break;

        case 6:
            out = dataRow.getActionKeys().c_str();
            break;

        case 7:
            out = dataRow.getActionSettingsJson().c_str();
            break;

        default:
            break;
        }
    }
    return out;
}

QVariant tlinsShortcutDefinitionModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (static_cast<unsigned int>(section) >= __columns__.size())
        return QVariant();

    if (role == Qt::DisplayRole && orientation == Qt::Horizontal)
        return QVariant(__columns__[static_cast<unsigned int>(section)].c_str());

    return QVariant();
}

std::vector<TlinsAstroBase::tlinsKeysSortcut>& tlinsShortcutDefinitionModel::getData()
{
    return actionsData;
}

void tlinsShortcutDefinitionModel::setItems(const std::vector<TlinsAstroBase::tlinsKeysSortcut>& data)
{
    actionsData.clear();

    for (auto& item : data)
        actionsData.push_back(item);

    std::sort(actionsData.begin(),
        actionsData.end(),
        [](const TlinsAstroBase::tlinsKeysSortcut& a,
            const TlinsAstroBase::tlinsKeysSortcut& b) { return a.getShortcutName() == b.getShortcutName(); });

    emit layoutChanged();
}

bool tlinsShortcutDefinitionModel::updateItem(const TlinsAstroBase::tlinsKeysSortcut& data)
{
    bool isPresent = false;
    for (auto s = actionsData.begin(); s != actionsData.end(); s++) {
        if (s->getShortcutName() == data.getShortcutName()) {
            isPresent = true;
            *s = data;
        }
    }

    if (isPresent)
        emit layoutChanged();

    return isPresent;
}

bool tlinsShortcutDefinitionModel::insertItem(const TlinsAstroBase::tlinsKeysSortcut& data)
{
    bool isPresent = false;
    for (auto s = actionsData.begin(); s != actionsData.end(); s++) {
        if (s->getShortcutName() == data.getShortcutName())
            isPresent = true;
    }

    if (!isPresent) {
        actionsData.push_back(data);
        std::sort(actionsData.begin(),
            actionsData.end(),
            [](const TlinsAstroBase::tlinsKeysSortcut& a,
                const TlinsAstroBase::tlinsKeysSortcut& b) { return a.getShortcutName() == b.getShortcutName(); });

        emit layoutChanged();
    }
    return !isPresent;
}

void tlinsShortcutDefinitionModel::deleteItems(const std::vector<TlinsAstroBase::tlinsKeysSortcut>& data)
{
    for (auto& item : data) {
        for (auto iter = actionsData.begin(); iter != actionsData.end(); iter++) {
            if (iter->getShortcutName() == item.getShortcutName()) {
                actionsData.erase(iter);
                break;
            }
        }
    }
    emit layoutChanged();
}

bool tlinsShortcutDefinitionModel::deleteItem(const unsigned int idx)
{
    if (idx < actionsData.size()) {
        actionsData.erase(actionsData.begin() + idx);
        emit layoutChanged();
        return true;
    }
    return false;
}

void tlinsShortcutDefinitionModel::clear()
{
    actionsData.clear();
    emit layoutChanged();
}

tlinsShortcutDefinitionModel::tlinsShortcutDefinitionModel(QObject*)
{
}

tlinsShortcutDefinitionModel::~tlinsShortcutDefinitionModel()
{
}

//
// ----
//
static std::string createString(std::vector<std::string>& v)
{
    std::string out {};
    unsigned int count = 0;
    for (auto& i : v) {
        out += i;
        if ((count + 1) < v.size())
            out += "+";
        count++;
    }
    return out;
}

tlinsWPilotShortcutsDefinitions::tlinsWPilotShortcutsDefinitions(QWidget* parent)
    : QWidget { parent }
    , dataModel { parent }
    , ui { new Ui::tlinsWPilotShortcutsDefinitions }
{
    ui->setupUi(this);

    ui->list->setModel(&dataModel);

    // Lista typow akcji i odpowiadajace im akcje
    configsMap["horisontal-vertical-move"] = std::shared_ptr<TlinsAstroBase::tlinsPilotShortcutsDefinitionInterface>(new tlinsWPilotHorisintalVerticalIncrement(this));
    configsMap["horisontal-vertical-move-keys"] = std::shared_ptr<TlinsAstroBase::tlinsPilotShortcutsDefinitionInterface>(new tlinsWPilotHorisontalVerticalKeys(this));
    configsMap["horisontal-vertical-delta"] = std::shared_ptr<TlinsAstroBase::tlinsPilotShortcutsDefinitionInterface>(new tlinsWPilotHVDelta(this));
    configsMap["horisontal-vertical-speed-delta"] = std::shared_ptr<TlinsAstroBase::tlinsPilotShortcutsDefinitionInterface>(new tlinsWPilotHVSpeedDelta(this));
    configsMap["horisintal-vertical-steps"] = std::shared_ptr<TlinsAstroBase::tlinsPilotShortcutsDefinitionInterface>(new tlinsWPilotHorisintalVerticalSteps(this));
    configsMap["hour-amgle-declination-delta"] = std::shared_ptr<TlinsAstroBase::tlinsPilotShortcutsDefinitionInterface>(new tlinsWPilotRaDcDelta(this));
    configsMap["hour-amgle-declination-speed-delta"] = std::shared_ptr<TlinsAstroBase::tlinsPilotShortcutsDefinitionInterface>(new tlinsWPilotRaDcSpeedDelta(this));
    configsMap["hour-amgle-declination-move-increment"] = std::shared_ptr<TlinsAstroBase::tlinsPilotShortcutsDefinitionInterface>(new tlinsWPilotRaDcIncrement(this));
    configsMap["start-reset-calibration"] = std::shared_ptr<TlinsAstroBase::tlinsPilotShortcutsDefinitionInterface>(new tlinsWPilotStartResetCalibration(this));
    configsMap["set-reference-object"] = std::shared_ptr<TlinsAstroBase::tlinsPilotShortcutsDefinitionInterface>(new tlinsWPilotSetReferenceObject(this));
    configsMap["close-calibration"] = std::shared_ptr<TlinsAstroBase::tlinsPilotShortcutsDefinitionInterface>(new tlinsWPilotCloseCalibration(this));
    configsMap["tracking-start"] = std::shared_ptr<TlinsAstroBase::tlinsPilotShortcutsDefinitionInterface>(new tlinsWPilotTrackingStart(this));
    configsMap["tracking-stop"] = std::shared_ptr<TlinsAstroBase::tlinsPilotShortcutsDefinitionInterface>(new tlinsWPilotTrackingStop(this));

    // Dodanie widgetow
    for (auto& item : configsMap)
        ui->parameters->addWidget(item.second->getWidget());

    // Ustawienie bioezacego
    for (auto& item : configsActionsMap)
        ui->actions->addItem(QString::fromStdString(item.second), QVariant(QString::fromStdString(item.first)));

    for (int i = 0; i < ui->actions->count(); i++) {
        QVariant d = ui->actions->itemData(i);
        std::string ds = d.toString().toStdString();

        if (ds == "horisontal-vertical-move") {
            ui->actions->setCurrentIndex(i);
            actionActivatedSlot(i);
            break;
        }
    }

    // Domyslnie pokazywany to RA delta
    ui->parameters->setCurrentWidget(configsMap["horisontal-vertical-move"]->getWidget());

    // Ustawienie wartosci dopmyslnych w poszczegolnych kontrolkach
    for (auto& item : configsMap)
        item.second->reset();

    // Tworzenie mapy widgetow
    widgetsMap["UP"] = ui->buttonUp;
    widgetsMap["DOWN"] = ui->buttonDown;
    widgetsMap["LEFT"] = ui->buttonLeft;
    widgetsMap["RIGHT"] = ui->buttonRight;
    widgetsMap["OK"] = ui->buttonOk;
    widgetsMap["F01"] = ui->buttonF01;
    widgetsMap["F02"] = ui->buttonF02;
    widgetsMap["F11"] = ui->buttonF11;
    widgetsMap["F12"] = ui->buttonF12;
    widgetsMap["F13"] = ui->buttonF13;
    widgetsMap["F14"] = ui->buttonF14;
    widgetsMap["F21"] = ui->buttonF21;
    widgetsMap["F22"] = ui->buttonF22;
    widgetsMap["F23"] = ui->buttonF23;
    widgetsMap["F24"] = ui->buttonF24;
    widgetsMap["F31"] = ui->buttonF31;
    widgetsMap["F32"] = ui->buttonF32;
    widgetsMap["F33"] = ui->buttonF33;
    widgetsMap["F34"] = ui->buttonF34;

    // +++
    widgetsMap["Joy_L11"] = ui->jButtonF11;
    widgetsMap["Joy_L12"] = ui->jButtonF12;
    widgetsMap["Joy_R11"] = ui->jButtonF13;
    widgetsMap["Joy_R12"] = ui->jButtonF14;
    widgetsMap["Joy_Up"] = ui->jButtonUp;
    widgetsMap["Joy_Down"] = ui->jButtonDown;
    widgetsMap["Joy_Left"] = ui->jButtonLeft;
    widgetsMap["Joy_Right"] = ui->jButtonRight;
    widgetsMap["Joy_Select"] = ui->jButtonF01;
    widgetsMap["Joy_Start"] = ui->jButtonF02;
    widgetsMap["Joy_1"] = ui->jButtonF21;
    widgetsMap["Joy_2"] = ui->jButtonF22;
    widgetsMap["Joy_3"] = ui->jButtonF23;
    widgetsMap["Joy_4"] = ui->jButtonF24;

    widgetsMap["Joy_Main_Right"] = ui->jButtonF32;

    widgetsMap["Joy_Left_Pad"] = ui->jButtonLeftPad;
    // ---

    ui->name->setText("__new_action__");
    ui->keysSequence->setText("");

    // Sposob rozciagania kolumn w widoku danych
    ui->list->horizontalHeader()->resizeSections(QHeaderView::ResizeToContents);
    ui->list->horizontalHeader()->setSectionResizeMode(QHeaderView::Interactive);
    ui->list->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
    ui->list->horizontalHeader()->setFixedHeight(30);

    // Sposob selekcji danych
    ui->list->setSelectionMode(QAbstractItemView::SingleSelection /* MultiSelection */);
    ui->list->setSelectionBehavior(QAbstractItemView::SelectRows);

    auto selModel = ui->list->selectionModel();
    connect(selModel, SIGNAL(selectionChanged(QItemSelection, QItemSelection)),
        this, SLOT(on_selectionChanged(QItemSelection, QItemSelection)));

    // Inicialne wypelnienie okna trescia
    {
        TlinsAstroBase::tlinsUIDatabase db;
        TlinsAstroBase::tlinsUIDatabaseDefinition dbDef(db);

        std::vector<TlinsAstroBase::tlinsKeysSortcut> data;
        dbDef.selectShortcuts(data);

        dataModel.clear();
        dataModel.setItems(data);
    }

    ui->radioButtonTypeKeyboard->setChecked(true);
    ui->radioButtonTypeGamepad->setChecked(false);

    ui->groupGamePad->setVisible(false);
    ui->groupPilot->setVisible(true);
    ui->defaultHandler->setVisible(false);
}

static bool hasDuplicates(const std::vector<std::string>& v, std::set<std::string>& dup)
{
    std::set<std::string> test;
    bool result = false;

    for (auto& i : v) {
        if (test.count(i) != 0) {
            dup.insert(i);
            result = true;
        } else {
            test.insert(i);
        }
    }
    return result;
}

void tlinsWPilotShortcutsDefinitions::on_selectionChanged(const QItemSelection& selected, const QItemSelection&)
{
    if (selected.size() == 0)
        return;

    auto list = selected.indexes();
    for (auto& item : list) {
        int row = item.row();
        auto data = dataModel.getData()[row];

        if (data.getType() == TlinsAstroBase::tlinsKeysSortcutType::KEYBOARD) {
            ui->groupGamePad->setVisible(false);
            ui->groupPilot->setVisible(true);

            ui->radioButtonTypeKeyboard->setChecked(true);
            ui->radioButtonTypeGamepad->setChecked(false);

            ui->radioButtonSubTypeGamepad->setChecked(false);
            ui->radioButtonSubTypeEmulation->setChecked(false);

            ui->groupSubType->setEnabled(false);
        } else {
            ui->defaultHandler->setVisible(true);
            ui->groupGamePad->setVisible(true);
            ui->groupPilot->setVisible(false);

            ui->radioButtonTypeKeyboard->setChecked(false);
            ui->radioButtonTypeGamepad->setChecked(true);

            ui->groupSubType->setEnabled(true);

            if (data.getSubType() == TlinsAstroBase::tlinsKeysSortcutSubType::JOYSTICK_KEYS) {
                ui->radioButtonSubTypeGamepad->setChecked(false);
                ui->radioButtonSubTypeEmulation->setChecked(true);
                ui->jButtonLeftPad->setVisible(false);
            } else {
                ui->radioButtonSubTypeGamepad->setChecked(true);
                ui->radioButtonSubTypeEmulation->setChecked(false);
                ui->jButtonLeftPad->setVisible(true);
            }
        }

        // Domyslny handler
        ui->defaultHandler->setChecked(data.getDefaultHandler() == TlinsAstroBase::tlinsDefaultHandler::YES);

        // Nazwa skrotu
        ui->name->setText(QString::fromStdString(data.getShortcutName()));

        // Klawisze skrotu
        ui->keysSequence->setText(QString::fromStdString(data.getActionKeys()));

        // Nazwa akcji
        auto actionName = data.getActionName();

        // Resetowanie wszystkich widgetow z konfiguracja
        for (auto& item : configsMap)
            item.second->reset();

        // Ustawinie akcji
        for (int i = 0; i < ui->actions->count(); i++) {
            QVariant d = ui->actions->itemData(i);
            std::string ds = d.toString().toStdString();

            if (ds == actionName) {
                ui->actions->setCurrentIndex(i);
                break;
            }
        }

        // Biezacy widget parametwrow
        ui->parameters->setCurrentWidget(configsMap[actionName]->getWidget());

        // Parametery widgetu
        auto strSetts = data.getActionSettingsJson();
        QJsonDocument doc = QJsonDocument::fromJson(QString::fromStdString(strSetts).toUtf8());
        configsMap[actionName]->setParameters(doc.object());

        switch (configsMap[actionName]->getValidMode()) {
        case TlinsAstroBase::tlinsPilotShortcutsDefinitionValidMode::ASTRO:
            ui->validMode->setText("Astro");
            break;

        case TlinsAstroBase::tlinsPilotShortcutsDefinitionValidMode::DEVICE:
            ui->validMode->setText("Device");
            break;

        case TlinsAstroBase::tlinsPilotShortcutsDefinitionValidMode::BOTH:
            ui->validMode->setText("Astro and device");
            break;
        }

        // Emulacja zakonczenia modyfikacji
        emit ui->keysSequence->editingFinished();
    }
}

void tlinsWPilotShortcutsDefinitions::buttonNewClickedSlot()
{
    ui->keysSequence->setText("");
    ui->name->setText("__new__");
    actionActivatedSlot(0);

    ui->groupGamePad->setVisible(false);
    ui->groupPilot->setVisible(true);

    ui->radioButtonTypeKeyboard->setChecked(true);
    ui->radioButtonTypeGamepad->setChecked(false);

    ui->radioButtonSubTypeGamepad->setChecked(false);
    ui->radioButtonSubTypeEmulation->setChecked(false);

    ui->groupSubType->setEnabled(false);
    ui->defaultHandler->setChecked(false);

    for (auto& item : widgetsMap)
        item.second->setChecked(false);

    for (auto& item : configsMap)
        item.second->reset();

    for (int i = 0; i < ui->actions->count(); i++) {
        QVariant d = ui->actions->itemData(i);
        std::string ds = d.toString().toStdString();

        if (ds == "horisontal-vertical-move") {
            ui->actions->setCurrentIndex(i);
            actionActivatedSlot(i);
            break;
        }
    }

    // Domyslnie pokazywany to RA delta
    ui->parameters->setCurrentWidget(configsMap["horisontal-vertical-move"]->getWidget());

    sequence.clear();
    currPos = 0;
}

bool tlinsWPilotShortcutsDefinitions::getDataItem(TlinsAstroBase::tlinsKeysSortcut& data)
{
    // Klawisze
    if (sequence.empty()) {
        QMessageBox msg;
        msg.setText("No keys in definition.");
        msg.exec();
        return false;
    }
    data.setActionKeys(createString(sequence));

    // Nazwa skrotu
    data.setAhortcutName(ui->name->text().toStdString());

    // Domyslny handler
    data.setDefaultHandler(ui->defaultHandler->isChecked() ? TlinsAstroBase::tlinsDefaultHandler::YES : TlinsAstroBase::tlinsDefaultHandler::NO);

    // Nazwa akcji
    QVariant userData = ui->actions->currentData();
    std::string actionName = userData.toString().toStdString();
    data.setActionName(actionName);

    // Konfiguracja akcji
    QJsonObject jObj;
    configsMap[actionName]->getParameters(jObj);
    QJsonDocument doc(jObj);
    QString strJson(doc.toJson(QJsonDocument::Compact));
    data.setActionSettingsJson(doc.toJson().toStdString());

    // Tryb akcji
    data.setActionMode(configsMap[actionName]->getValidMode());

    // Typ kontrolera
    if (ui->radioButtonTypeKeyboard->isChecked()) {
        data.setType(TlinsAstroBase::tlinsKeysSortcutType::KEYBOARD);
        data.setSubType(TlinsAstroBase::tlinsKeysSortcutSubType::ANY);
    } else {
        data.setType(TlinsAstroBase::tlinsKeysSortcutType::JOYSTICK);

        if (ui->radioButtonSubTypeEmulation->isChecked())
            data.setSubType(TlinsAstroBase::tlinsKeysSortcutSubType::JOYSTICK_KEYS);
        else
            data.setSubType(TlinsAstroBase::tlinsKeysSortcutSubType::JOYSTICK_GAMEPAD);
    }

    return true;
}

bool tlinsWPilotShortcutsDefinitions::getSelected(std::vector<int>& rows)
{
    if (ui->list->selectionModel()->hasSelection()) {
        QModelIndexList select = ui->list->selectionModel()->selectedRows();
        for (int i = 0; i < select.count(); i++) {
            QModelIndex idx = select.at(i);
            rows.push_back(idx.row());
        }
        return true;
    }
    return false;
}

void tlinsWPilotShortcutsDefinitions::buttonAddClickedSlot()
{
    TlinsAstroBase::tlinsKeysSortcut data;
    if (!getDataItem(data))
        return;

    if (!dataModel.insertItem(data)) {
        QMessageBox msg;
        msg.setText("Shortcut definition not inserted.");
        msg.exec();
    }
    ui->list->horizontalHeader()->resizeSections(QHeaderView::ResizeToContents);
}

void tlinsWPilotShortcutsDefinitions::buttonStoreClickedSlot()
{
    TlinsAstroBase::tlinsUIDatabase db;
    TlinsAstroBase::tlinsUIDatabaseDefinition dbDef(db);

    dbDef.clearShortcuts();
    dbDef.insertShortcuts(dataModel.getData());

    QMessageBox msg;
    msg.setText("Data saved.");
    msg.exec();
}

void tlinsWPilotShortcutsDefinitions::buttonLoadClickedSlot()
{
    TlinsAstroBase::tlinsUIDatabase db;
    TlinsAstroBase::tlinsUIDatabaseDefinition dbDef(db);

    std::vector<TlinsAstroBase::tlinsKeysSortcut> data;
    dbDef.selectShortcuts(data);

    dataModel.clear();
    dataModel.setItems(data);

    QMessageBox msg;
    msg.setText("Data loaded.");
    msg.exec();
    ui->list->horizontalHeader()->resizeSections(QHeaderView::ResizeToContents);
}

void tlinsWPilotShortcutsDefinitions::buttonUpdateClickedSlot()
{
    TlinsAstroBase::tlinsKeysSortcut data;
    if (!getDataItem(data))
        return;

    dataModel.updateItem(data);
}

void tlinsWPilotShortcutsDefinitions::buttonRemoveClickedSlot()
{
    std::vector<int> rows;
    if (!getSelected(rows)) {
        QMessageBox msg;
        msg.setText(QString("Rows need to be selected"));
        msg.exec();
    }

    for (auto& id : rows)
        dataModel.deleteItem(static_cast<unsigned int>(id));

    ui->list->horizontalHeader()->resizeSections(QHeaderView::ResizeToContents);

    QMessageBox msg;
    msg.setText(QString("Rows have been removed from the list"));
    msg.exec();
}

void tlinsWPilotShortcutsDefinitions::actionActivatedSlot(int idx)
{
    QVariant qv = ui->actions->itemData(idx);
    std::string id = qv.toString().toStdString();

    ui->parameters->setCurrentWidget(configsMap[id]->getWidget());

    switch (configsMap[id]->getValidMode()) {
    case TlinsAstroBase::tlinsPilotShortcutsDefinitionValidMode::ASTRO:
        ui->validMode->setText("Astro");
        break;

    case TlinsAstroBase::tlinsPilotShortcutsDefinitionValidMode::DEVICE:
        ui->validMode->setText("Device");
        break;

    case TlinsAstroBase::tlinsPilotShortcutsDefinitionValidMode::BOTH:
        ui->validMode->setText("Astro and device");
        break;
    }
}

void tlinsWPilotShortcutsDefinitions::cursorPositionChangedSlot(int, int newPos)
{
    if (newPos == 0) {
        currPos = 0;
        return;
    }

    auto keys = ui->keysSequence->text().toStdString();
    std::vector<std::string> tmpSeq;
    std::regex separator { "\\+" };
    auto wIter = std::sregex_token_iterator(keys.begin(), keys.end(), separator, -1);
    auto wEnd = std::sregex_token_iterator();
    int count = 0;
    int size = 0;

    for (; wIter != wEnd; wIter++) {
        std::string match_str = *wIter;
        int prev = size;

        if (count == 0)
            size = static_cast<int>(match_str.length());
        else
            size += match_str.length() + 1;

        count++;
        int next = size;
        if (newPos >= prev && newPos <= next) {
            currPos = count;
            break;
        }
    }
}

void tlinsWPilotShortcutsDefinitions::editingFinishedSlot()
{
    auto keys = ui->keysSequence->text().toStdString();

    if (!keys.empty() && keys[keys.size() - 1] == '+') {
        auto ss = keys.substr(0, keys.size() - 1);
        keys = ss;
        ui->keysSequence->setText(QString::fromStdString(keys));
    }

    std::vector<std::string> tmpSeq;
    std::regex separator { "\\+" };
    auto iter = std::sregex_token_iterator(keys.begin(), keys.end(), separator, -1);
    auto iterEnd = std::sregex_token_iterator();
    int errorCount = 0;
    std::string errorItems;
    for (; iter != iterEnd; iter++) {
        if (widgetsMap.count(*iter) == 0) {
            if (errorCount == 0)
                errorItems = *iter;
            else {
                errorItems += ", ";
                errorItems += *iter;
            }
            errorCount++;
        } else
            tmpSeq.push_back(*iter);
    }

    if (errorCount != 0 && !keys.empty()) {
        ui->keysSequence->setText(QString::fromStdString(createString(tmpSeq)));

        QMessageBox msg;
        msg.setText("Sourtcut contains unknown items: " + QString::fromStdString(errorItems));
        msg.exec();
    }

    // Wyczyszczenie tablicy
    sequence.clear();

    // Sprawdzenie duplikatow
    std::set<std::string> dups;
    auto dup = hasDuplicates(tmpSeq, dups);
    if (dup) {
        for (auto& iter : tmpSeq) {
            if (dups.count(iter) == 0)
                sequence.push_back(iter);
        }
        ui->keysSequence->setText(QString::fromStdString(createString(sequence)));

        QMessageBox msg;
        msg.setText("All duplicates found sequence were removed.");
        msg.exec();
    } else {
        sequence = std::move(tmpSeq);
    }

    // Ustawienie klawiatury zgodnie z tym co jest ustawione w tekstowym
    for (auto& iter : widgetsMap)
        iter.second->setChecked(false);

    for (auto& iter : sequence)
        widgetsMap[iter]->setChecked(true);
}

tlinsWPilotShortcutsDefinitions::~tlinsWPilotShortcutsDefinitions()
{
    delete ui;
}

void tlinsWPilotShortcutsDefinitions::insertPos(const std::string& v, const bool isChecked)
{
    if (!isChecked) {
        for (auto iter = sequence.begin(); iter != sequence.end(); iter++) {
            if (*iter == v) {
                sequence.erase(iter, iter + 1);
                break;
            }
        }
        return;
    }

    if (currPos >= static_cast<int>(sequence.size())) {
        sequence.push_back(v);
    } else {
        auto ipos = sequence.begin() + currPos;
        sequence.insert(ipos, v);
    }
    currPos++;
    if (currPos >= static_cast<int>(sequence.size()))
        currPos = static_cast<int>(sequence.size());
}

void tlinsWPilotShortcutsDefinitions::buttonOkSlot(bool v)
{
    insertPos("OK", v);
    ui->keysSequence->setText(QString::fromStdString(createString(sequence)));
}

// +++ Joystik +++

void tlinsWPilotShortcutsDefinitions::jButtonUpSlot(bool v)
{
    if (v) {
        insertPos("Joy_Main_Left", false);
        insertPos("Joy_Main_Right", false);
        insertPos("Joy_Left_Pad", false);
        ui->jButtonF32->setChecked(false);
        ui->jButtonLeftPad->setChecked(false);
    }

    insertPos("Joy_Up", v);
    ui->keysSequence->setText(QString::fromStdString(createString(sequence)));
}

void tlinsWPilotShortcutsDefinitions::jButtonDownSlot(bool v)
{
    if (v) {
        insertPos("Joy_Main_Left", false);
        insertPos("Joy_Main_Right", false);
        insertPos("Joy_Left_Pad", false);
        ui->jButtonF32->setChecked(false);
        ui->jButtonLeftPad->setChecked(false);
    }

    insertPos("Joy_Down", v);
    ui->keysSequence->setText(QString::fromStdString(createString(sequence)));
}

void tlinsWPilotShortcutsDefinitions::jButtonLeftSlot(bool v)
{
    if (v) {
        insertPos("Joy_Main_Left", false);
        insertPos("Joy_Main_Right", false);
        insertPos("Joy_Left_Pad", false);
        ui->jButtonF32->setChecked(false);
        ui->jButtonLeftPad->setChecked(false);
    }

    insertPos("Joy_Left", v);
    ui->keysSequence->setText(QString::fromStdString(createString(sequence)));
}

void tlinsWPilotShortcutsDefinitions::jButtonRightSlot(bool v)
{
    if (v) {
        insertPos("Joy_Main_Left", false);
        insertPos("Joy_Main_Right", false);
        insertPos("Joy_Left_Pad", false);
        ui->jButtonF32->setChecked(false);
        ui->jButtonLeftPad->setChecked(false);
    }

    insertPos("Joy_Right", v);
    ui->keysSequence->setText(QString::fromStdString(createString(sequence)));
}

// --- Joystik ---

void tlinsWPilotShortcutsDefinitions::buttonUpSlot(bool v)
{
    insertPos("UP", v);
    ui->keysSequence->setText(QString::fromStdString(createString(sequence)));
}

void tlinsWPilotShortcutsDefinitions::buttonDownSlot(bool v)
{
    insertPos("DOWN", v);
    ui->keysSequence->setText(QString::fromStdString(createString(sequence)));
}

void tlinsWPilotShortcutsDefinitions::buttonLeftSlot(bool v)
{
    insertPos("LEFT", v);
    ui->keysSequence->setText(QString::fromStdString(createString(sequence)));
}

void tlinsWPilotShortcutsDefinitions::buttonRightSlot(bool v)
{
    insertPos("RIGHT", v);
    ui->keysSequence->setText(QString::fromStdString(createString(sequence)));
}

// +++ Joystik +++

void tlinsWPilotShortcutsDefinitions::jButtonF01Slot(bool v)
{
    if (v) {
        insertPos("Joy_Main_Left", false);
        insertPos("Joy_Main_Right", false);
        insertPos("Joy_Left_Pad", false);
        ui->jButtonF32->setChecked(false);
        ui->jButtonLeftPad->setChecked(false);
    }

    insertPos("Joy_Select", v);
    ui->keysSequence->setText(QString::fromStdString(createString(sequence)));
}

void tlinsWPilotShortcutsDefinitions::jButtonF02Slot(bool v)
{
    if (v) {
        insertPos("Joy_Main_Left", false);
        insertPos("Joy_Main_Right", false);
        insertPos("Joy_Left_Pad", false);
        ui->jButtonF32->setChecked(false);
        ui->jButtonLeftPad->setChecked(false);
    }

    insertPos("Joy_Start", v);
    ui->keysSequence->setText(QString::fromStdString(createString(sequence)));
}

// --- Joystik ---

void tlinsWPilotShortcutsDefinitions::buttonF01Slot(bool v)
{
    insertPos("F01", v);
    ui->keysSequence->setText(QString::fromStdString(createString(sequence)));
}

void tlinsWPilotShortcutsDefinitions::buttonF02Slot(bool v)
{
    insertPos("F02", v);
    ui->keysSequence->setText(QString::fromStdString(createString(sequence)));
}

// +++ Joystik +++

void tlinsWPilotShortcutsDefinitions::jButtonF11Slot(bool v)
{
    if (v) {
        insertPos("Joy_Main_Left", false);
        insertPos("Joy_Main_Right", false);
        insertPos("Joy_Left_Pad", false);
        ui->jButtonF32->setChecked(false);
        ui->jButtonLeftPad->setChecked(false);
    }

    insertPos("Joy_L11", v);
    ui->keysSequence->setText(QString::fromStdString(createString(sequence)));
}

void tlinsWPilotShortcutsDefinitions::jButtonF12Slot(bool v)
{
    if (v) {
        insertPos("Joy_Main_Left", false);
        insertPos("Joy_Main_Right", false);
        insertPos("Joy_Left_Pad", false);
        ui->jButtonF32->setChecked(false);
        ui->jButtonLeftPad->setChecked(false);
    }

    insertPos("Joy_L12", v);
    ui->keysSequence->setText(QString::fromStdString(createString(sequence)));
}

void tlinsWPilotShortcutsDefinitions::jButtonF13Slot(bool v)
{
    if (v) {
        insertPos("Joy_Main_Left", false);
        insertPos("Joy_Main_Right", false);
        insertPos("Joy_Left_Pad", false);
        ui->jButtonF32->setChecked(false);
        ui->jButtonLeftPad->setChecked(false);
    }

    insertPos("Joy_R11", v);
    ui->keysSequence->setText(QString::fromStdString(createString(sequence)));
}

void tlinsWPilotShortcutsDefinitions::jButtonF14Slot(bool v)
{
    if (v) {
        insertPos("Joy_Main_Left", false);
        insertPos("Joy_Main_Right", false);
        insertPos("Joy_Left_Pad", false);
        ui->jButtonF32->setChecked(false);
        ui->jButtonLeftPad->setChecked(false);
    }

    insertPos("Joy_R12", v);
    ui->keysSequence->setText(QString::fromStdString(createString(sequence)));
}

// --- Joystik ---

void tlinsWPilotShortcutsDefinitions::buttonF11Slot(bool v)
{
    insertPos("F11", v);
    ui->keysSequence->setText(QString::fromStdString(createString(sequence)));
}

void tlinsWPilotShortcutsDefinitions::buttonF12Slot(bool v)
{
    insertPos("F12", v);
    ui->keysSequence->setText(QString::fromStdString(createString(sequence)));
}

void tlinsWPilotShortcutsDefinitions::buttonF13Slot(bool v)
{
    insertPos("F13", v);
    ui->keysSequence->setText(QString::fromStdString(createString(sequence)));
}

void tlinsWPilotShortcutsDefinitions::buttonF14Slot(bool v)
{
    insertPos("F14", v);
    ui->keysSequence->setText(QString::fromStdString(createString(sequence)));
}

// +++ Joystik +++

void tlinsWPilotShortcutsDefinitions::jButtonF21Slot(bool v)
{
    if (v) {
        insertPos("Joy_Main_Left", false);
        insertPos("Joy_Main_Right", false);
        insertPos("Joy_Left_Pad", false);
        ui->jButtonF32->setChecked(false);
        ui->jButtonLeftPad->setChecked(false);
    }

    insertPos("Joy_1", v);
    ui->keysSequence->setText(QString::fromStdString(createString(sequence)));
}

void tlinsWPilotShortcutsDefinitions::jButtonF22Slot(bool v)
{
    if (v) {
        insertPos("Joy_Main_Left", false);
        insertPos("Joy_Main_Right", false);
        insertPos("Joy_Left_Pad", false);
        ui->jButtonF32->setChecked(false);
        ui->jButtonLeftPad->setChecked(false);
    }

    insertPos("Joy_2", v);
    ui->keysSequence->setText(QString::fromStdString(createString(sequence)));
}

void tlinsWPilotShortcutsDefinitions::jButtonF23Slot(bool v)
{
    if (v) {
        insertPos("Joy_Main_Left", false);
        insertPos("Joy_Main_Right", false);
        insertPos("Joy_Left_Pad", false);
        ui->jButtonF32->setChecked(false);
        ui->jButtonLeftPad->setChecked(false);
    }

    insertPos("Joy_3", v);
    ui->keysSequence->setText(QString::fromStdString(createString(sequence)));
}

void tlinsWPilotShortcutsDefinitions::jButtonF24Slot(bool v)
{
    if (v) {
        insertPos("Joy_Main_Left", false);
        insertPos("Joy_Main_Right", false);
        insertPos("Joy_Left_Pad", false);
        ui->jButtonF32->setChecked(false);
        ui->jButtonLeftPad->setChecked(false);
    }

    insertPos("Joy_4", v);
    ui->keysSequence->setText(QString::fromStdString(createString(sequence)));
}

void tlinsWPilotShortcutsDefinitions::jTypeKeyboard(bool v)
{
    if (!ui->groupPilot->isVisible() && v) {
        for (auto& item : widgetsMap)
            item.second->setChecked(false);

        sequence.clear();
        ui->keysSequence->setText("");
        currPos = 0;

        ui->radioButtonSubTypeGamepad->setChecked(false);
        ui->radioButtonSubTypeEmulation->setChecked(false);

        ui->groupSubType->setEnabled(false);
    }

    if (v) {
        ui->groupGamePad->setVisible(false);
        ui->defaultHandler->setVisible(false);
        ui->groupPilot->setVisible(true);
        ui->defaultHandler->setChecked(false);
    } else {
        ui->defaultHandler->setVisible(true);
        ui->groupGamePad->setVisible(true);
        ui->groupPilot->setVisible(false);
    }
}

void tlinsWPilotShortcutsDefinitions::jTypeJoystick(bool v)
{
    if (!ui->groupGamePad->isVisible() && v) {
        for (auto& item : widgetsMap)
            item.second->setChecked(false);

        sequence.clear();
        ui->keysSequence->setText("");
        currPos = 0;

        ui->radioButtonSubTypeGamepad->setChecked(true);
        ui->radioButtonSubTypeEmulation->setChecked(false);

        ui->jButtonLeftPad->setVisible(true);
        ui->frameLeft->setVisible(true);

        ui->groupSubType->setEnabled(true);
        ui->defaultHandler->setChecked(false);
    }

    if (v) {
        ui->defaultHandler->setVisible(true);
        ui->groupGamePad->setVisible(true);
        ui->groupPilot->setVisible(false);
    } else {
        ui->defaultHandler->setVisible(false);
        ui->groupGamePad->setVisible(false);
        ui->groupPilot->setVisible(true);
    }
}

void tlinsWPilotShortcutsDefinitions::jSubTypeKeyboard(bool v)
{
    //    ui -> jButtonLeftPad -> setVisible(false);
    //    ui -> frameLeft -> setVisible( true);
}

void tlinsWPilotShortcutsDefinitions::jSubTypeJoystick(bool v)
{
    //    ui -> jButtonLeftPad -> setVisible(true);
    //    ui -> frameLeft -> setVisible(false);
}

// --- Joystik ---

void tlinsWPilotShortcutsDefinitions::buttonF21Slot(bool v)
{
    insertPos("F21", v);
    ui->keysSequence->setText(QString::fromStdString(createString(sequence)));
}

void tlinsWPilotShortcutsDefinitions::buttonF22Slot(bool v)
{
    insertPos("F22", v);
    ui->keysSequence->setText(QString::fromStdString(createString(sequence)));
}

void tlinsWPilotShortcutsDefinitions::buttonF23Slot(bool v)
{
    insertPos("F23", v);
    ui->keysSequence->setText(QString::fromStdString(createString(sequence)));
}

void tlinsWPilotShortcutsDefinitions::buttonF24Slot(bool v)
{
    insertPos("F24", v);
    ui->keysSequence->setText(QString::fromStdString(createString(sequence)));
}

// +++ Joystik +++
void tlinsWPilotShortcutsDefinitions::jButtonF32Slot(bool v)
{
    if (v) {
        if (ui->jButtonLeftPad->isChecked()) {
            insertPos("Joy_Main_Left", false);
            insertPos("Joy_Left_Pad", false);
            ui->jButtonLeftPad->setChecked(false);
        }
    }

    insertPos("Joy_Main_Right", v);
    ui->keysSequence->setText(QString::fromStdString(createString(sequence)));
}

void tlinsWPilotShortcutsDefinitions::jButtonLeftPadSlot(bool v)
{
    if (v) {
        if (ui->jButtonLeftPad->isChecked()) {
            insertPos("Joy_Main_Left", false);
            insertPos("Joy_Main_Right", false);
            ui->jButtonF32->setChecked(false);
        }
    }

    insertPos("Joy_Left_Pad", v);
    ui->keysSequence->setText(QString::fromStdString(createString(sequence)));
}

// --- Joystik ---

void tlinsWPilotShortcutsDefinitions::buttonF31Slot(bool v)
{
    insertPos("F31", v);
    ui->keysSequence->setText(QString::fromStdString(createString(sequence)));
}

void tlinsWPilotShortcutsDefinitions::buttonF32Slot(bool v)
{
    insertPos("F32", v);
    ui->keysSequence->setText(QString::fromStdString(createString(sequence)));
}

void tlinsWPilotShortcutsDefinitions::buttonF33Slot(bool v)
{
    insertPos("F33", v);
    ui->keysSequence->setText(QString::fromStdString(createString(sequence)));
}

void tlinsWPilotShortcutsDefinitions::buttonF34Slot(bool v)
{
    insertPos("F34", v);
    ui->keysSequence->setText(QString::fromStdString(createString(sequence)));
}
