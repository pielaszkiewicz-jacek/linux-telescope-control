#include "tlinswmanageenginestate.h"
#include "tlinsastrobaseutils.h"
#include "tlinsastroenginestate.h"
#include "tlinsconfiguration.h"
#include "tlinsserverstatusinfo.h"
#include "tlinsuidatabase.h"
#include "tlinsuidatabasedefinition.h"
#include "tlinsuimainwindow.h"
#include "tlinsuistrutils.h"
#include "tlinsupdatestatemanager.h"
#include "ui_tlinswmanageenginestate.h"
#include <tlinscommunicationthread.h>

#include <QMessageBox>
#include <tlinsBacktrace.hpp>

#include <sys/time.h>
#include <vector>

#define __dilerResolution__ 1000000

static std::vector<std::string> __columns__ = {
    "Name",
    "Right ascension",
    "Declination",
    "Proper motion (RA)",
    "Proper motion (dc)",
    "Radial velocity",
    "Parallex",
    "Catalog type",
    "Attitude Matrix",
    "Device X",
    "Device Y",
    "Device encoder X",
    "Device encoder Y",
    "Mode",
    "State",
    "Reverese X",
    "Reverese Y",
    ""
};

int tlinsEngineStateModelModel::rowCount(const QModelIndex&) const
{
    int size = static_cast<int>(stateData.size());
    return size;
}

int tlinsEngineStateModelModel::columnCount(const QModelIndex&) const
{
    int size = static_cast<int>(__columns__.size());
    return size;
}

QVariant tlinsEngineStateModelModel::data(const QModelIndex& index, int role) const
{
    auto row = index.row();
    auto column = index.column();
    QVariant out;

    if (role == Qt::TextAlignmentRole)
        return QVariant(Qt::AlignVCenter | Qt::AlignRight);

    if (role == Qt::DisplayRole) {
        auto& dataRow = stateData[static_cast<unsigned int>(row)];

        switch (column) {
        case 0:
            // Name
            out = QString::fromStdString(dataRow.getName().c_str());
            break;

        case 1:
            // RA
            out = tlinsUiStrUtils::setValueHour(dataRow.getRA());
            break;

        case 2:
            // DC
            out = tlinsUiStrUtils::setValueDegris(dataRow.getDC());
            break;

        case 3:
            // PM RA
            out = tlinsUiStrUtils::setValueDegris(dataRow.getPmRA());
            break;

        case 4:
            // PM DC
            out = tlinsUiStrUtils::setValueDegris(dataRow.getPmDC());
            break;

        case 5:
            // Radial velocity
            out = dataRow.getRadialVelocity();
            break;

        case 6:
            // Parallex
            out = dataRow.getParallex();
            break;

        case 7:
            // Catalog type
            out = dataRow.getCatalogType().c_str();
            break;

        case 8:
            // Macierz
            {
                char txt[1024];
                sprintf(txt, "{{%+02.07f, %+02.07f, %+02.07f},{%+02.07f, %+02.07f, %+02.07f},{%+02.07f, %+02.07f, %+02.07f}}",
                    dataRow.getA11(), dataRow.getA12(), dataRow.getA13(),
                    dataRow.getA21(), dataRow.getA22(), dataRow.getA23(),
                    dataRow.getA31(), dataRow.getA32(), dataRow.getA33());
                out = txt;
            }
            break;

        case 9:
            // Dev X
            out = static_cast<int>(dataRow.getDeviceX());
            break;

        case 10:
            // Dev Y
            out = static_cast<int>(dataRow.getDeviceY());
            break;

        case 11:
            // Enc Dev X
            out = static_cast<int>(dataRow.getDeviceXEncoder());
            break;

        case 12:
            // Enc Dev Y
            out = static_cast<int>(dataRow.getDeviceYEncoder());
            break;

        case 13:
            // Mode
            switch (dataRow.getMode()) {
            case TlinsAstroBase::tlinsAstroEngineState::EngineMode::MODE_NONE:
                out = "None";
                break;

            case TlinsAstroBase::tlinsAstroEngineState::EngineMode::MODE_STANDARD:
                out = "Standard";
                break;

            case TlinsAstroBase::tlinsAstroEngineState::EngineMode::MODE_EXTERNAL_SUPPORT:
                out = "External support";
                break;
            }
            break;

        case 14:
            // State
            switch (dataRow.getState()) {
            case TlinsAstroBase::tlinsAstroEngineState::EngineState::STATE_CALIBRATION:
                out = "Calibration";
                break;
            case TlinsAstroBase::tlinsAstroEngineState::EngineState::STATE_CALIBRATION_VELOCITY:
                out = "Calibration velocity";
                break;

            case TlinsAstroBase::tlinsAstroEngineState::EngineState::STATE_REGULAR:
                out = "Regular";
                break;
            }
            break;

        case 15:
            if (dataRow.getXReverse()) {
                out = "Reverse direction";
            } else {
                out = "Same direction";
            }
            break;

        case 16:
            if (dataRow.getYReverse()) {
                out = "Reverse direction";
            } else {
                out = "Same direction";
            }
            break;

        default:
            break;
        }
    }
    return out;
}

QVariant tlinsEngineStateModelModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (static_cast<unsigned int>(section) >= __columns__.size())
        return QVariant();

    if (role == Qt::DisplayRole && orientation == Qt::Horizontal) {
        QVariant ret(__columns__[static_cast<unsigned long>(section)].c_str());
        return ret;
    }
    return QVariant();
}

void tlinsEngineStateModelModel::setItems(const std::vector<TlinsAstroBase::tlinsAstroEngineState>& data)
{
    stateData.clear();

    for (auto& item : data)
        stateData.push_back(item);

    emit layoutChanged();
}

bool tlinsEngineStateModelModel::updateItem(const TlinsAstroBase::tlinsAstroEngineState& data)
{
    // Wyszukanie pozycji
    unsigned int idx = 0;
    for (idx = 0; idx < stateData.size(); idx++) {
        auto& item = stateData[idx];
        if (item.getName() == data.getName())
            break;
    }
    if (idx >= stateData.size()) {
        insertItem(data);
        return true;
    }
    stateData[idx] = data;
    emit layoutChanged();

    return true;
}

bool tlinsEngineStateModelModel::insertItem(const TlinsAstroBase::tlinsAstroEngineState& data)
{
    // Sprawdzanie duplikatu
    if (data.getName().length() == 0)
        return false;

    for (auto& item : stateData) {
        if (item.getName() == data.getName())
            return false;
    }

    // Insert new item into the list
    stateData.push_back(data);

    // Sort data
    std::sort(stateData.begin(),
        stateData.end(),
        [](TlinsAstroBase::tlinsAstroEngineState a, TlinsAstroBase::tlinsAstroEngineState b) {
            if (a.getName() < b.getName())
                return true;
            return false;
        });

    emit layoutChanged();
    return true;
}

void tlinsEngineStateModelModel::deleteItems(const std::vector<TlinsAstroBase::tlinsAstroEngineState>& data)
{
    for (auto& iter : data) {
        for (auto iter2 = stateData.begin(); iter2 != stateData.end(); iter2++) {
            if (iter2->getName() == iter.getName()) {
                stateData.erase(iter2);
                break;
            }
        }
    }
    emit layoutChanged();
}

bool tlinsEngineStateModelModel::deleteItem(const unsigned int idx)
{
    if (idx >= stateData.size())
        return false;

    stateData.erase(stateData.begin() + idx);
    emit layoutChanged();

    return true;
}

void tlinsEngineStateModelModel::clear()
{
    stateData.clear();
    emit layoutChanged();
}

tlinsEngineStateModelModel::tlinsEngineStateModelModel(QObject* parent)
    : QAbstractTableModel { parent }
{
}

//
// —------------------------------------------------------
// —------------------------------------------------------
// —------------------------------------------------------
//

tlinsWManageEngineState::tlinsWManageEngineState(QWidget* parent)
    : QWidget { parent }
    , isSet { false }
    , ui { new Ui::tlinsWManageEngineState }
{
    ui->setupUi(this);
    ui->statesList->setModel(&dataModel);

    isSet = false;

    ui->a11->disableButtons();
    ui->a12->disableButtons();
    ui->a13->disableButtons();
    ui->a21->disableButtons();
    ui->a22->disableButtons();
    ui->a23->disableButtons();
    ui->a31->disableButtons();
    ui->a32->disableButtons();
    ui->a33->disableButtons();
    ui->aX->disableButtons();
    ui->aY->disableButtons();
    ui->aXEncoder->disableButtons();
    ui->aYEncoder->disableButtons();
    ui->paralex->disableButtons();
    ui->radialVelocity->disableButtons();
    ui->pmRA->disableButtons();
    ui->pmDC->disableButtons();

    ui->a11->setDecimal(6);
    ui->a12->setDecimal(6);
    ui->a13->setDecimal(6);
    ui->a21->setDecimal(6);
    ui->a22->setDecimal(6);
    ui->a23->setDecimal(6);
    ui->a31->setDecimal(6);
    ui->a32->setDecimal(6);
    ui->a33->setDecimal(6);
    ui->aX->setDecimal(0);
    ui->aXEncoder->setDecimal(0);
    ui->aY->setDecimal(0);
    ui->aYEncoder->setDecimal(0);
    ui->paralex->setDecimal(6);
    ui->radialVelocity->setDecimal(6);
    ui->catalogType->disable();

    ui->targetRA->setValue(0.0);
    ui->targetDC->setValue(0.0);
    ui->pmRA->setValue(0.0);
    ui->pmDC->setValue(0.0);

    ui->a11->setValue(0.0);
    ui->a12->setValue(0.0);
    ui->a13->setValue(0.0);
    ui->a21->setValue(0.0);
    ui->a22->setValue(0.0);
    ui->a23->setValue(0.0);
    ui->a31->setValue(0.0);
    ui->a32->setValue(0.0);
    ui->a33->setValue(0.0);
    ui->aX->setValue(0);
    ui->aXEncoder->setValue(0);
    ui->aY->setValue(0);
    ui->aYEncoder->setValue(0);
    ui->paralex->setValue(0.0);
    ui->radialVelocity->setValue(0.0);

    //	ui -> statesList -> setSortingEnabled( true );

    // Sposob rozciagania kolumn w widoku danych
    ui->statesList->horizontalHeader()->resizeSections(QHeaderView::ResizeToContents);
    ui->statesList->horizontalHeader()->setSectionResizeMode(QHeaderView::Interactive);
    ui->statesList->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
    ui->statesList->horizontalHeader()->setFixedHeight(30);

    // Sposob selekcji danych
    ui->statesList->setSelectionMode(QAbstractItemView::SingleSelection /* MultiSelection */);
    ui->statesList->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->statesList->setColumnHidden(dataModel.columnCount() - 1, true);

    auto selModel = ui->statesList->selectionModel();
    connect(selModel, SIGNAL(selectionChanged(QItemSelection, QItemSelection)),
        this, SLOT(on_selectionChanged(QItemSelection, QItemSelection)));

    connect(this, SIGNAL(notiStatus(std::string)),
        this, SLOT(notiStatusSlot(std::string)), Qt::BlockingQueuedConnection);

    //
    // Odczyt zawartosci bazy
    //
    TlinsAstroBase::tlinsUIDatabase db;
    TlinsAstroBase::tlinsUIDatabaseDefinition dbDef(db);

    try {
        std::vector<TlinsAstroBase::tlinsAstroEngineState> outData;
        dbDef.selectAstroEngineStates(outData);
        dataModel.setItems(outData);
        ui->statesList->horizontalHeader()->resizeSections(QHeaderView::ResizeToContents);
    } catch (TlinsAstroBase::tlinsUIException&) {
    }

    ui->groupBoxGuider->setVisible(false);
    ui->groupBoxManualCorrections->setVisible(false);
    ui->frameGuider->setVisible(false);
    ui->frameManual->setVisible(false);

    ui->groupBoxState->setVisible(true);
    ui->gbStateControl->setVisible(false);

    ui->radioButtonStateView->setChecked(true);
    ui->rbStandard->setChecked(true);

    ui->guiderRaRatio->setDecimal(6);
    ui->guiderDecRatio->setDecimal(6);
    ui->manualRaCorrection->setDecimal(6);
    ui->manualDecCorrection->setDecimal(6);

    ui->radioButtonAllView->setVisible(false);

    ui->guiderRaRatio->setMinMax(0.0, static_cast<double>(__dilerResolution__));
    ui->guiderDecRatio->setMinMax(0.0, static_cast<double>(__dilerResolution__));
    ui->manualRaCorrection->setMinMax(-1.0 * static_cast<double>(__dilerResolution__), static_cast<double>(__dilerResolution__));
    ui->manualRaCorrection->setMinMax(-1.0 * static_cast<double>(__dilerResolution__), static_cast<double>(__dilerResolution__));

    ui->guiderRaRatio->setCallback([this](double value) {
        ui->dialRARatio->setValue(static_cast<int>(value * static_cast<double>(__dilerResolution__)));
    });

    ui->guiderDecRatio->setCallback([this](double value) {
        ui->dialDECRatio->setValue(static_cast<int>(value * static_cast<double>(__dilerResolution__)));
    });

    ui->manualRaCorrection->setCallback([this](double value) {
        ui->dialRACorrection->setValue(static_cast<int>(value * static_cast<double>(__dilerResolution__)));
    });

    ui->manualDecCorrection->setCallback([this](double value) {
        ui->dialDECCorrection->setValue(static_cast<int>(value * static_cast<double>(__dilerResolution__)));
    });

    ui->dialDECCorrection->setMaximum(__dilerResolution__);
    ui->dialDECCorrection->setMinimum(-1 * __dilerResolution__);
    ui->dialRACorrection->setMaximum(__dilerResolution__);
    ui->dialRACorrection->setMinimum(-1 * __dilerResolution__);

    ui->dialRARatio->setMaximum(__dilerResolution__);
    ui->dialRARatio->setMinimum(0);
    ui->dialDECRatio->setMaximum(__dilerResolution__);
    ui->dialDECRatio->setMinimum(0);

    connect(this, SIGNAL(updateGuiderRatio(double, double)), this, SLOT(updateGuiderRatioSlot(double, double)));
    connect(this, SIGNAL(updateCorrection(double, double)), this, SLOT(updateCorrectionSlot(double, double)));
}

void tlinsWManageEngineState::setValueUi(const TlinsAstroBase::tlinsAstroEngineState& data)
{
    // Nazwa konfiguracji
    ui->name->setText(QString::fromStdString(data.getName()));

    // Macierz
    ui->a11->setValue(data.getA11());
    ui->a21->setValue(data.getA12());
    ui->a31->setValue(data.getA13());

    ui->a12->setValue(data.getA21());
    ui->a22->setValue(data.getA22());
    ui->a32->setValue(data.getA23());

    ui->a13->setValue(data.getA31());
    ui->a23->setValue(data.getA32());
    ui->a33->setValue(data.getA33());

    ui->xReverse->setChecked(data.getXReverse());
    ui->yReverse->setChecked(data.getYReverse());

    // Target
    ui->targetRA->setValue(data.getRA());
    ui->targetDC->setValue(data.getDC());
    ui->pmRA->setValue(data.getPmRA());
    ui->pmDC->setValue(data.getPmDC());

    ui->radialVelocity->setValue(data.getRadialVelocity());
    ui->paralex->setValue(data.getParallex());
    ui->catalogType->setCurrent(data.getCatalogType());

    ui->aX->setValue(data.getDeviceX());
    ui->aY->setValue(data.getDeviceY());
    ui->aXEncoder->setValue(data.getDeviceXEncoder());
    ui->aYEncoder->setValue(data.getDeviceYEncoder());

    // Tryb silnika
    switch (data.getMode()) {
    case TlinsAstroBase::tlinsAstroEngineState::EngineMode::MODE_NONE:
        ui->engineMode->setText("none");
        break;

    case TlinsAstroBase::tlinsAstroEngineState::EngineMode::MODE_STANDARD:
        ui->engineMode->setText("standard");
        break;

    case TlinsAstroBase::tlinsAstroEngineState::EngineMode::MODE_EXTERNAL_SUPPORT:
        ui->engineMode->setText("external support");
        break;
    }

    // Stan silnika
    switch (data.getState()) {
    case TlinsAstroBase::tlinsAstroEngineState::EngineState::STATE_CALIBRATION:
        ui->engineState->setText("calibration");
        break;

    case TlinsAstroBase::tlinsAstroEngineState::EngineState::STATE_CALIBRATION_VELOCITY:
        ui->engineState->setText("calibration velocity");
        break;

    case TlinsAstroBase::tlinsAstroEngineState::EngineState::STATE_REGULAR:
        ui->engineState->setText("regular");
        break;
    }

    // Biezacy obiekt
    ui->targetRA->setValue(data.getRA());
    ui->targetDC->setValue(data.getDC());

    ui->pmRA->setValue(data.getPmRA());
    ui->pmDC->setValue(data.getPmDC());

    ui->paralex->setValue(data.getParallex());
    ui->radialVelocity->setValue(data.getRadialVelocity());
}

void tlinsWManageEngineState::on_selectionChanged(const QItemSelection& selected, const QItemSelection&)
{
    if (selected.size() == 0)
        return;

    auto list = selected.indexes();
    for (auto& item : list) {
        auto row = item.row();
        auto data = dataModel.getData()[static_cast<unsigned int>(row)];
        isSet = true;
        currentState = data;
        setValueUi(data);
    }
}

void tlinsWManageEngineState::on_btAdd_clicked()
{
    if (!isSet) {
        QMessageBox msgBox;
        msgBox.setText("No state data.");
        msgBox.exec();
        return;
    }

    currentState.setName(ui->name->text().toStdString());

    if (!dataModel.insertItem(currentState)) {
        QMessageBox msgBox;
        msgBox.setText("Duplicated or incorrect state data.");
        msgBox.exec();
        return;
    }

    ui->statesList->horizontalHeader()->resizeSections(QHeaderView::ResizeToContents);
}

void tlinsWManageEngineState::on_btRemove_clicked()
{
    if (!isSet) {
        QMessageBox msgBox;
        msgBox.setText("No state data.");
        msgBox.exec();
        return;
    }

    std::string name = currentState.getName();

    std::vector<TlinsAstroBase::tlinsAstroEngineState> data { currentState };
    dataModel.deleteItems(data);

    //
    // Zapisanie zmian do bazy danych
    //
    TlinsAstroBase::tlinsUIDatabase db;
    TlinsAstroBase::tlinsUIDatabaseDefinition dbDef(db);

    try {
        db.startTransaction();
        dbDef.removeAstroEngineState(currentState.getName());
        db.commitTransaction();
    } catch (TlinsAstroBase::tlinsUIException&) {
        db.rollbackTransaction();
        QMessageBox msg;
        msg.setText("Error save state data");
        msg.exec();
        return;
    }

    currentState = TlinsAstroBase::tlinsAstroEngineState {};
    setValueUi(currentState);

    isSet = false;

    QMessageBox msgBox;
    msgBox.setText("Item removed." + QString::fromStdString(name));
    msgBox.exec();

    ui->statesList->horizontalHeader()->resizeSections(QHeaderView::ResizeToContents);
}

void tlinsWManageEngineState::on_btLoad_clicked()
{
    //
    // Odczyt zawartosci bazy
    //
    TlinsAstroBase::tlinsUIDatabase db;
    TlinsAstroBase::tlinsUIDatabaseDefinition dbDef(db);

    try {
        std::vector<TlinsAstroBase::tlinsAstroEngineState> outData;
        dbDef.selectAstroEngineStates(outData);
        dataModel.setItems(outData);
        ui->statesList->horizontalHeader()->resizeSections(QHeaderView::ResizeToContents);
    } catch (TlinsAstroBase::tlinsUIException&) {
    }
}

void tlinsWManageEngineState::on_btSave_clicked()
{
    if (dataModel.getData().size() == 0) {
        QMessageBox msgBox;
        msgBox.setText("No data to save.");
        msgBox.exec();
        return;
    }

    TlinsAstroBase::tlinsUIDatabase db;
    TlinsAstroBase::tlinsUIDatabaseDefinition dbDef(db);

    try {
        db.startTransaction();
        dbDef.updateAstroEngineStates(dataModel.getData());
        db.commitTransaction();

        QMessageBox msg;
        msg.setText("Engine states saved.");
        msg.exec();
        return;

    } catch (TlinsAstroBase::tlinsUIException&) {
        db.rollbackTransaction();
        QMessageBox msg;
        msg.setText("Error save state data");
        msg.exec();
        return;
    }
}

void tlinsWManageEngineState::notiStatusSlot(std::string str)
{
    QMessageBox msgBox;
    msgBox.setText(QString::fromStdString(str));
    msgBox.exec();
}

//
// -------------------------------
// Start engine
// -------------------------------
//
class tlinsStateStartEngine : public TlinsAstroBase::tlinsCommunicationThreadRequest {
private:
    std::shared_ptr<TlinsAstroBase::tlinsConnectionContext> connection;
    tlinsWManageEngineState* parent;
    tlinsAstroEngineInterface::tlinsEngineMode mode;

public:
    void confirm()
    {
        TlinsAstroBase::tlinsCommunicationThreadRequest::confirm();
    }

    virtual void operator()() noexcept
    {
        try {
            // Ustawienie zadanego trybu pracy
            connection->getAstro()->setMode(mode);

            // Uruchomienie sledzenie
            connection->getAstro()->startTracking();

            auto mw = getMainWindowInstance();
            emit mw->logEvent("Tracking started");
            emit parent->notiStatus("Tracking started");
        } catch (tlinsInterfaceException& exc) {
            auto mw = getMainWindowInstance();
            emit mw->logEvent(QString::fromStdString(std::string { "Error start tracking: " } + exc.getErrorMessage()));
            emit parent->notiStatus("Error start tracking: " + exc.getErrorMessage());
        }
    }

    virtual bool isAsynchronuus()
    {
        return false;
    }

    virtual std::string name()
    {
        return "tlinsStateStartEngine";
    }

    tlinsStateStartEngine(tlinsWManageEngineState* parent_, tlinsAstroEngineInterface::tlinsEngineMode mode_)
        : parent { parent_ }
        , mode { mode_ }
    {
        // Pobranie polaczenia
        if (!TlinsAstroBase::tlinsConnectionsManager::getInstance().hasConnection(std::string { TLINS_CONNECTION_DEFAULT }))
            __THROW__(tlinsException(std::string("No active connection: ") + std::string(TLINS_CONNECTION_DEFAULT), -1));

        // Polaczenie
        connection = TlinsAstroBase::tlinsConnectionsManager::getInstance().getConnection(TLINS_CONNECTION_DEFAULT);
    }

    virtual ~tlinsStateStartEngine()
    {
        connection.reset();
    }
};

void tlinsWManageEngineState::on_btStart_clicked()
{
    auto& statusInfo = TlinsAstroBase::tlinsServerStatusInfo::getInstance();
    auto& cStatus = statusInfo.getCalibrarionState();

    switch (cStatus.get_engineState()) {
    case tlinsAstroEngineInterface::tlinsEngineStateValue::STATE_CALIBRATION: {
        QMessageBox msg;
        msg.setText("Engine not ready - not configured or under calibration.");
        msg.exec();
        return;
    }
    case tlinsAstroEngineInterface::tlinsEngineStateValue::STATE_REGULAR:
        break;
    }

    try {
        tlinsAstroEngineInterface::tlinsEngineMode mode { tlinsAstroEngineInterface::tlinsEngineMode::MODE_STANDARD };
        if (ui->rbStandard->isChecked()) {
            mode = tlinsAstroEngineInterface::tlinsEngineMode::MODE_STANDARD;
        } else if (ui->rbStandardSpeed->isChecked()) {
            mode = tlinsAstroEngineInterface::tlinsEngineMode::MODE_STANDARD_SPEED;
        } else if (ui->rbGuider->isChecked()) {
            mode = tlinsAstroEngineInterface::tlinsEngineMode::MODE_EXTERNAL_SUPPORT;
        }

        std::unique_ptr<TlinsAstroBase::tlinsCommunicationThreadRequest> req(new tlinsStateStartEngine { this, mode });
        TlinsAstroBase::tlinsCommunicationThread::getInstance().push(req);
    } catch (tlinsException& exc) {
        TLINS_LOG_ERROR("Error: " + exc.getErrorMessage());
        auto mw = getMainWindowInstance();
        emit mw->logEvent(QString::fromStdString("Error: " + exc.getErrorMessage()));

        QMessageBox msgBox;
        msgBox.setText(QString::fromStdString("Error: " + exc.getErrorMessage()));
        msgBox.exec();
    }
}

//
// -------------------------------
// Stop engine
// -------------------------------
//
class tlinsStateStopEngine : public TlinsAstroBase::tlinsCommunicationThreadRequest {
private:
    std::shared_ptr<TlinsAstroBase::tlinsConnectionContext> connection;
    tlinsWManageEngineState* parent;

public:
    void confirm()
    {
        TlinsAstroBase::tlinsCommunicationThreadRequest::confirm();
    }

    virtual void operator()() noexcept
    {
        try {
            // Uruchomienie zapytania
            connection->getAstro()->stopTracking();
            auto mw = getMainWindowInstance();
            emit mw->logEvent("Tracking stoped");
            emit parent->notiStatus("Tracking started");
        } catch (tlinsInterfaceException& exc) {
            auto mw = getMainWindowInstance();
            emit mw->logEvent(QString::fromStdString(std::string { "Error start tracking: " } + exc.getErrorMessage()));
            emit parent->notiStatus("Error stop tracking: " + exc.getErrorMessage());
        }
    }

    virtual bool isAsynchronuus()
    {
        return false;
    }

    virtual std::string name()
    {
        return "tlinsStartStopEngine";
    }

    tlinsStateStopEngine(tlinsWManageEngineState* parent_)
        : parent { parent_ }
    {
        // Pobranie polaczenia
        if (!TlinsAstroBase::tlinsConnectionsManager::getInstance().hasConnection(std::string { TLINS_CONNECTION_DEFAULT }))
            __THROW__(tlinsException(std::string("No active connection: ") + std::string(TLINS_CONNECTION_DEFAULT), -1));

        // Polaczenie
        connection = TlinsAstroBase::tlinsConnectionsManager::getInstance().getConnection(TLINS_CONNECTION_DEFAULT);
    }

    virtual ~tlinsStateStopEngine()
    {
        connection.reset();
    }
};

void tlinsWManageEngineState::on_btStop_clicked()
{
    // Status kalibracji
    auto& statusInfo = TlinsAstroBase::tlinsServerStatusInfo::getInstance();
    auto& cStatus = statusInfo.getCalibrarionState();

    switch (cStatus.get_engineState()) {
    case tlinsAstroEngineInterface::tlinsEngineStateValue::STATE_CALIBRATION:
    case tlinsAstroEngineInterface::tlinsEngineStateValue::STATE_CALIBRATION_VELOCITY: {
        QMessageBox msg;
        msg.setText("Engine is not started.");
        msg.exec();
        return;
    }
    case tlinsAstroEngineInterface::tlinsEngineStateValue::STATE_REGULAR:
        break;
    }

    try {
        std::unique_ptr<TlinsAstroBase::tlinsCommunicationThreadRequest> req(new tlinsStateStopEngine { this });
        TlinsAstroBase::tlinsCommunicationThread::getInstance().push(req);
    } catch (tlinsException& exc) {
        TLINS_LOG_ERROR("Error: " + exc.getErrorMessage());

        auto mw = getMainWindowInstance();
        emit mw->logEvent(QString::fromStdString("Error: " + exc.getErrorMessage()));

        QMessageBox msgBox;
        msgBox.setText(QString::fromStdString("Error: " + exc.getErrorMessage()));
        msgBox.exec();
    }
}

//
// -------------------------------
// Odczyt stanu silnika
// -------------------------------
//
class tlinsStateDownload : public TlinsAstroBase::tlinsCommunicationThreadRequest {
private:
    std::shared_ptr<TlinsAstroBase::tlinsConnectionContext> connection;
    tlinsWManageEngineState* parent;

public:
    void confirm()
    {
        TlinsAstroBase::tlinsCommunicationThreadRequest::confirm();
    }

    virtual void operator()() noexcept
    {
        try {
            // Odczy stanu
            tlinsAstroEngineInterface::tlinsEngineStateInfo stateInfo;

            // Uruchomienie zapytania
            connection->getAstro()->getState(stateInfo);

            TlinsAstroBase::tlinsAstroEngineState state;

            state.setA11(stateInfo.get_attitude()[0][0]);
            state.setA12(stateInfo.get_attitude()[0][1]);
            state.setA13(stateInfo.get_attitude()[0][2]);

            state.setA21(stateInfo.get_attitude()[1][0]);
            state.setA22(stateInfo.get_attitude()[1][1]);
            state.setA23(stateInfo.get_attitude()[1][2]);

            state.setA31(stateInfo.get_attitude()[2][0]);
            state.setA32(stateInfo.get_attitude()[2][1]);
            state.setA33(stateInfo.get_attitude()[2][2]);

            state.setDeviceX(stateInfo.get_devicePosition().get_x());
            state.setDeviceY(stateInfo.get_devicePosition().get_y());
            state.setDeviceXEncoder(stateInfo.get_devicePosition().get_xEncoder());
            state.setDeviceYEncoder(stateInfo.get_devicePosition().get_yEncoder());

            switch (stateInfo.get_mode()) {
            case tlinsAstroEngineInterface::tlinsEngineMode::MODE_EXTERNAL_SUPPORT:
                state.setMode(TlinsAstroBase::tlinsAstroEngineState::EngineMode::MODE_EXTERNAL_SUPPORT);
                break;

            case tlinsAstroEngineInterface::tlinsEngineMode::MODE_STANDARD:
                state.setMode(TlinsAstroBase::tlinsAstroEngineState::EngineMode::MODE_STANDARD);
                break;

            case tlinsAstroEngineInterface::tlinsEngineMode::MODE_NONE:
                state.setMode(TlinsAstroBase::tlinsAstroEngineState::EngineMode::MODE_NONE);
                break;
            }

            tlinsAstroEngineInterface::tlinsEngineStateValue sInfo;
            switch (stateInfo.get_state()) {
            case tlinsAstroEngineInterface::tlinsEngineStateValue::STATE_CALIBRATION:
                state.setState(TlinsAstroBase::tlinsAstroEngineState::EngineState::STATE_CALIBRATION);
                sInfo = tlinsAstroEngineInterface::tlinsEngineStateValue::STATE_CALIBRATION;
                break;

            case tlinsAstroEngineInterface::tlinsEngineStateValue::STATE_CALIBRATION_VELOCITY:
                state.setState(TlinsAstroBase::tlinsAstroEngineState::EngineState::STATE_CALIBRATION_VELOCITY);
                sInfo = tlinsAstroEngineInterface::tlinsEngineStateValue::STATE_CALIBRATION_VELOCITY;
                break;

            case tlinsAstroEngineInterface::tlinsEngineStateValue::STATE_REGULAR:
                state.setState(TlinsAstroBase::tlinsAstroEngineState::EngineState::STATE_REGULAR);
                sInfo = tlinsAstroEngineInterface::tlinsEngineStateValue::STATE_REGULAR;
                break;
            }

            state.setRadialVelocity(stateInfo.get_currentTarget().get_object().get_radialVelocity());
            state.setPmRA(stateInfo.get_currentTarget().get_object().get_properMotionRA());
            state.setPmDC(stateInfo.get_currentTarget().get_object().get_properMotionDC());

            {
                double h = static_cast<double>(stateInfo.get_currentTarget().get_object().get_hourAngle().get_degris());
                double m = static_cast<double>(stateInfo.get_currentTarget().get_object().get_hourAngle().get_minutes());
                double s = static_cast<double>(stateInfo.get_currentTarget().get_object().get_hourAngle().get_seconds());
                double hh = h + m / 60.0 + s / 3600.0;
                state.setRA(hh);
            }

            {
                double d = static_cast<double>(stateInfo.get_currentTarget().get_object().get_declination().get_degris());
                double m = static_cast<double>(stateInfo.get_currentTarget().get_object().get_declination().get_minutes());
                double s = static_cast<double>(stateInfo.get_currentTarget().get_object().get_declination().get_seconds());
                bool sign = stateInfo.get_currentTarget().get_object().get_declination().get_sign();
                double dd = d + m / 60.0 + s / 3600.0;
                if (sign)
                    dd *= -1.0;
                state.setDC(dd);
            }

            state.setParallex(stateInfo.get_currentTarget().get_object().get_parallax());
            state.setCatalogType(stateInfo.get_currentTarget().get_object().get_catalogType());

            state.setSpeed(stateInfo.get_currentTarget().get_speed());
            state.setAceleration(stateInfo.get_currentTarget().get_aceleration());
            state.setDelta(stateInfo.get_currentTarget().get_delta());

            state.setXReverse(stateInfo.get_xReverse());
            state.setYReverse(stateInfo.get_yReverse());

            struct timeval timeV;
            gettimeofday(&timeV, nullptr);

            struct tm* tmTime = localtime(&timeV.tv_sec);
            char timeStr[400];
            std::string strLevel;

            sprintf(timeStr, "State[%04d.%02d.%02d %02d:%02d:%02d]",
                tmTime->tm_year + 1900,
                tmTime->tm_mon + 1,
                tmTime->tm_mday,
                tmTime->tm_hour,
                tmTime->tm_min,
                tmTime->tm_sec);

            state.setName(std::string { timeStr });

            // Aktualizacja sobiektu z danymi
            emit parent->updateCurrentStateSlot(state);

            auto mw = getMainWindowInstance();
            emit mw->logEvent("Engine state downloaded");
            emit parent->notiStatus("Engine state downloaded");
        } catch (tlinsInterfaceException& exc) {
            auto mw = getMainWindowInstance();
            emit mw->logEvent(QString::fromStdString(std::string { "Engine state download error. Error " } + exc.getErrorMessage()));
            emit parent->notiStatus("Engine state download error. Error " + exc.getErrorMessage());
        }
    }

    virtual bool isAsynchronuus()
    {
        return false;
    }

    virtual std::string name()
    {
        return "tlinsStateDownload";
    }

    tlinsStateDownload(tlinsWManageEngineState* parent_)
        : parent { parent_ }
    {
        // Pobranie polaczenia
        if (!TlinsAstroBase::tlinsConnectionsManager::getInstance().hasConnection(std::string { TLINS_CONNECTION_DEFAULT }))
            __THROW__(tlinsException(std::string("No active connection: ") + std::string(TLINS_CONNECTION_DEFAULT), -1));

        // Polaczenie
        connection = TlinsAstroBase::tlinsConnectionsManager::getInstance().getConnection(TLINS_CONNECTION_DEFAULT);
    }

    virtual ~tlinsStateDownload()
    {
        connection.reset();
    }
};

void tlinsWManageEngineState::updateCurrentStateSlot(const TlinsAstroBase::tlinsAstroEngineState& state)
{
    currentState = state;
    isSet = true;

    ///
    // Macierz tamsformacji
    //
    ui->a11->setValue(state.getA11());
    ui->a21->setValue(state.getA12());
    ui->a31->setValue(state.getA13());

    ui->a12->setValue(state.getA21());
    ui->a22->setValue(state.getA22());
    ui->a32->setValue(state.getA23());

    ui->a13->setValue(state.getA31());
    ui->a23->setValue(state.getA32());
    ui->a33->setValue(state.getA33());

    ui->xReverse->setChecked(currentState.getXReverse());
    ui->yReverse->setChecked(currentState.getYReverse());

    //
    // Pozycja urzadzenia
    //
    ui->aX->setValue(state.getDeviceX());
    ui->aY->setValue(state.getDeviceY());
    ui->aXEncoder->setValue(state.getDeviceXEncoder());
    ui->aYEncoder->setValue(state.getDeviceYEncoder());

    //
    // Mode
    //
    switch (state.getMode()) {
    case TlinsAstroBase::tlinsAstroEngineState::EngineMode::MODE_NONE:
        ui->engineMode->setText("None");
        break;

    case TlinsAstroBase::tlinsAstroEngineState::EngineMode::MODE_STANDARD:
        ui->engineMode->setText("Standard");
        break;

    case TlinsAstroBase::tlinsAstroEngineState::EngineMode::MODE_EXTERNAL_SUPPORT:
        ui->engineMode->setText("External support");
        break;
    }

    //
    // state
    //
    switch (state.getState()) {
    case TlinsAstroBase::tlinsAstroEngineState::EngineState::STATE_CALIBRATION:
        ui->engineState->setText("Calibration");
        break;

    case TlinsAstroBase::tlinsAstroEngineState::EngineState::STATE_CALIBRATION_VELOCITY:
        ui->engineState->setText("Calibration velocity");
        break;

    case TlinsAstroBase::tlinsAstroEngineState::EngineState::STATE_REGULAR:
        ui->engineState->setText("Regular");
        break;
    }

    // Biezacy obiekt
    ui->targetRA->setValue(state.getRA());
    ui->targetDC->setValue(state.getDC());

    ui->pmRA->setValue(state.getPmRA());
    ui->pmDC->setValue(state.getPmDC());

    ui->paralex->setValue(state.getParallex());
    ui->radialVelocity->setValue(state.getRadialVelocity());

    // Zapisanie stanu
    currentState = state;
}

void tlinsWManageEngineState::on_pbLoadGuider_clicked()
{
    // Instancja konfiguracji
    auto& inst = TlinsAstroBase::tlinsConfiguration::getInstance();

    if (inst.hasKey(TlinsAstroBase::tlinsConfiguration::GUIDER_PARAMETER_GROUP, TlinsAstroBase::tlinsConfiguration::GUIDER_PARAMETER_RA_RATE)) {
        ui->guiderRaRatio->setValue(inst.getDouble(TlinsAstroBase::tlinsConfiguration::GUIDER_PARAMETER_GROUP, TlinsAstroBase::tlinsConfiguration::GUIDER_PARAMETER_RA_RATE));
    } else {
        ui->guiderRaRatio->setValue(0.0);
    }

    if (inst.hasKey(TlinsAstroBase::tlinsConfiguration::GUIDER_PARAMETER_GROUP, TlinsAstroBase::tlinsConfiguration::GUIDER_PARAMETER_DEC_RATE)) {
        ui->guiderDecRatio->setValue(inst.getDouble(TlinsAstroBase::tlinsConfiguration::GUIDER_PARAMETER_GROUP, TlinsAstroBase::tlinsConfiguration::GUIDER_PARAMETER_DEC_RATE));
    } else {
        ui->guiderDecRatio->setValue(0.0);
    }

    QMessageBox msgBox;
    msgBox.setText("Guider configuration has been loaded");
    msgBox.exec();

    auto mw = getMainWindowInstance();
    emit mw->logEvent("Guider configuration has been loaded");
}

class tlinsGuderSet : public TlinsAstroBase::tlinsCommunicationThreadRequest {
private:
    std::shared_ptr<TlinsAstroBase::tlinsConnectionContext> connection;
    tlinsWManageEngineState* parent;
    double ra;
    double dec;

public:
    void confirm()
    {
        TlinsAstroBase::tlinsCommunicationThreadRequest::confirm();
    }

    virtual void operator()() noexcept
    {
        try {
            // Uruchomienie zapytania
            connection->getAstro()->guiderRatioSet(ra, dec, false);
            auto mw = getMainWindowInstance();
            emit mw->logEvent("Guider ratios has been set");
            emit parent->notiStatus("Guider ratios has been set");
        } catch (tlinsInterfaceException& exc) {
            auto mw = getMainWindowInstance();
            emit mw->logEvent(QString::fromStdString(std::string { "Error set guider ratrios: " } + exc.getErrorMessage()));
            emit parent->notiStatus("Error set guider ratrios: " + exc.getErrorMessage());
        }
    }

    virtual bool isAsynchronuus()
    {
        return false;
    }

    virtual std::string name()
    {
        return "guiderRatioSet";
    }

    tlinsGuderSet(tlinsWManageEngineState* parent_, const double ra_, const double dec_)
        : parent { parent_ }
        , ra { ra_ }
        , dec { dec_ }
    {
        // Pobranie polaczenia
        if (!TlinsAstroBase::tlinsConnectionsManager::getInstance().hasConnection(std::string { TLINS_CONNECTION_DEFAULT }))
            __THROW__(tlinsException(std::string("No active connection: ") + std::string(TLINS_CONNECTION_DEFAULT), -1));

        // Polaczenie
        connection = TlinsAstroBase::tlinsConnectionsManager::getInstance().getConnection(TLINS_CONNECTION_DEFAULT);
    }

    virtual ~tlinsGuderSet()
    {
        connection.reset();
    }
};

void tlinsWManageEngineState::on_pbUpdateDeviceGuider_clicked()
{
    try {
        std::unique_ptr<TlinsAstroBase::tlinsCommunicationThreadRequest> req(new tlinsGuderSet { this, ui->guiderRaRatio->getValue(), ui->guiderDecRatio->getValue() });
        TlinsAstroBase::tlinsCommunicationThread::getInstance().push(req);
    } catch (tlinsException& exc) {
        TLINS_LOG_ERROR("Error: " + exc.getErrorMessage());

        auto mw = getMainWindowInstance();
        emit mw->logEvent(QString::fromStdString("Error: " + exc.getErrorMessage()));

        QMessageBox msgBox;
        msgBox.setText(QString::fromStdString("Error: " + exc.getErrorMessage()));
        msgBox.exec();
    }
}

class tlinsGuderGet : public TlinsAstroBase::tlinsCommunicationThreadRequest {
private:
    std::shared_ptr<TlinsAstroBase::tlinsConnectionContext> connection;
    tlinsWManageEngineState* parent;

public:
    void confirm()
    {
        TlinsAstroBase::tlinsCommunicationThreadRequest::confirm();
    }

    virtual void operator()() noexcept
    {
        try {
            double ra;
            double dec;
            bool useRaForDec;
            connection->getAstro()->guiderRatioGet(ra, dec, useRaForDec);

            emit parent->updateGuiderRatio(ra, dec);
            emit parent->notiStatus("Guider ratios has been read");

            auto mw = getMainWindowInstance();
            emit mw->logEvent("Guider ratios has been read");

        } catch (tlinsInterfaceException& exc) {
            auto mw = getMainWindowInstance();
            emit mw->logEvent(QString::fromStdString(std::string { "Error read guider ratrios: " } + exc.getErrorMessage()));
            emit parent->notiStatus("Error read guider ratrios: " + exc.getErrorMessage());
        }
    }

    virtual bool isAsynchronuus()
    {
        return false;
    }

    virtual std::string name()
    {
        return "guiderRatioGet";
    }

    tlinsGuderGet(tlinsWManageEngineState* parent_)
        : parent { parent_ }
    {
        // Pobranie polaczenia
        if (!TlinsAstroBase::tlinsConnectionsManager::getInstance().hasConnection(std::string { TLINS_CONNECTION_DEFAULT }))
            __THROW__(tlinsException(std::string("No active connection: ") + std::string(TLINS_CONNECTION_DEFAULT), -1));

        // Polaczenie
        connection = TlinsAstroBase::tlinsConnectionsManager::getInstance().getConnection(TLINS_CONNECTION_DEFAULT);
    }

    virtual ~tlinsGuderGet()
    {
        connection.reset();
    }
};

void tlinsWManageEngineState::on_pbSReadFromDeviceGuider_clicked()
{
    try {
        std::unique_ptr<TlinsAstroBase::tlinsCommunicationThreadRequest> req(new tlinsGuderGet { this });
        TlinsAstroBase::tlinsCommunicationThread::getInstance().push(req);
    } catch (tlinsException& exc) {
        TLINS_LOG_ERROR("Error: " + exc.getErrorMessage());

        auto mw = getMainWindowInstance();
        emit mw->logEvent(QString::fromStdString("Error: " + exc.getErrorMessage()));

        QMessageBox msgBox;
        msgBox.setText(QString::fromStdString("Error: " + exc.getErrorMessage()));
        msgBox.exec();
    }
}

void tlinsWManageEngineState::updateGuiderRatioSlot(double ra, double dec)
{
    ui->guiderRaRatio->setValue(ra);
    ui->guiderDecRatio->setValue(dec);
}

void tlinsWManageEngineState::updateCorrectionSlot(double ra, double dec)
{
    ui->manualRaCorrection->setValue(ra);
    ui->manualDecCorrection->setValue(dec);
}

void tlinsWManageEngineState::on_pbStoreGuider_clicked()
{
    // Instancja konfiguracji
    auto& inst = TlinsAstroBase::tlinsConfiguration::getInstance();

    inst.setValue(TlinsAstroBase::tlinsConfiguration::GUIDER_PARAMETER_GROUP, TlinsAstroBase::tlinsConfiguration::GUIDER_PARAMETER_RA_RATE, ui->guiderRaRatio->getValue());
    inst.setValue(TlinsAstroBase::tlinsConfiguration::GUIDER_PARAMETER_GROUP, TlinsAstroBase::tlinsConfiguration::GUIDER_PARAMETER_DEC_RATE, ui->guiderDecRatio->getValue());

    QMessageBox msgBox;
    msgBox.setText("Guider configuration has been saved");
    msgBox.exec();

    auto mw = getMainWindowInstance();
    emit mw->logEvent("Guider configuration has been saved");
}

class tlinsCorrectionGet : public TlinsAstroBase::tlinsCommunicationThreadRequest {
private:
    std::shared_ptr<TlinsAstroBase::tlinsConnectionContext> connection;
    tlinsWManageEngineState* parent;

public:
    void confirm()
    {
        TlinsAstroBase::tlinsCommunicationThreadRequest::confirm();
    }

    virtual void operator()() noexcept
    {
        try {
            double ra;
            double dec;
            connection->getAstro()->manualCorrectionGet(ra, dec);

            emit parent->updateCorrection(ra, dec);
            emit parent->notiStatus("Manual correction params has been read");

            auto mw = getMainWindowInstance();
            emit mw->logEvent("Manual correction params has been read");

        } catch (tlinsInterfaceException& exc) {
            auto mw = getMainWindowInstance();
            emit mw->logEvent(QString::fromStdString(std::string { "Error read guider ratrios: " } + exc.getErrorMessage()));
            emit parent->notiStatus("Error read guider ratrios: " + exc.getErrorMessage());
        }
    }

    virtual bool isAsynchronuus()
    {
        return false;
    }

    virtual std::string name()
    {
        return "manualCorrectionGet";
    }

    tlinsCorrectionGet(tlinsWManageEngineState* parent_)
        : parent { parent_ }
    {
        // Pobranie polaczenia
        if (!TlinsAstroBase::tlinsConnectionsManager::getInstance().hasConnection(std::string { TLINS_CONNECTION_DEFAULT }))
            __THROW__(tlinsException(std::string("No active connection: ") + std::string(TLINS_CONNECTION_DEFAULT), -1));

        // Polaczenie
        connection = TlinsAstroBase::tlinsConnectionsManager::getInstance().getConnection(TLINS_CONNECTION_DEFAULT);
    }

    virtual ~tlinsCorrectionGet()
    {
        connection.reset();
    }
};

void tlinsWManageEngineState::on_pbReadFromDeviceManual_clicked()
{
    try {
        std::unique_ptr<TlinsAstroBase::tlinsCommunicationThreadRequest> req(new tlinsCorrectionGet { this });
        TlinsAstroBase::tlinsCommunicationThread::getInstance().push(req);
    } catch (tlinsException& exc) {
        TLINS_LOG_ERROR("Error: " + exc.getErrorMessage());

        auto mw = getMainWindowInstance();
        emit mw->logEvent(QString::fromStdString("Error: " + exc.getErrorMessage()));

        QMessageBox msgBox;
        msgBox.setText(QString::fromStdString("Error: " + exc.getErrorMessage()));
        msgBox.exec();
    }
}

class tlinsCorrectionSet : public TlinsAstroBase::tlinsCommunicationThreadRequest {
private:
    std::shared_ptr<TlinsAstroBase::tlinsConnectionContext> connection;
    tlinsWManageEngineState* parent;
    double ra;
    double dec;

public:
    void confirm()
    {
        TlinsAstroBase::tlinsCommunicationThreadRequest::confirm();
    }

    virtual void operator()() noexcept
    {
        try {
            // Uruchomienie zapytania
            connection->getAstro()->manualCorrection(ra, dec);
            auto mw = getMainWindowInstance();
            emit mw->logEvent("Manual correction has been set");
            emit parent->notiStatus("Manual correction has been set");
        } catch (tlinsInterfaceException& exc) {
            auto mw = getMainWindowInstance();
            emit mw->logEvent(QString::fromStdString(std::string { "Error set manual correction: " } + exc.getErrorMessage()));
            emit parent->notiStatus("Error set manual correction: " + exc.getErrorMessage());
        }
    }

    virtual bool isAsynchronuus()
    {
        return false;
    }

    virtual std::string name()
    {
        return "guiderRatioSet";
    }

    tlinsCorrectionSet(tlinsWManageEngineState* parent_, const double ra_, const double dec_)
        : parent { parent_ }
        , ra { ra_ }
        , dec { dec_ }
    {
        // Pobranie polaczenia
        if (!TlinsAstroBase::tlinsConnectionsManager::getInstance().hasConnection(std::string { TLINS_CONNECTION_DEFAULT }))
            __THROW__(tlinsException(std::string("No active connection: ") + std::string(TLINS_CONNECTION_DEFAULT), -1));

        // Polaczenie
        connection = TlinsAstroBase::tlinsConnectionsManager::getInstance().getConnection(TLINS_CONNECTION_DEFAULT);
    }

    virtual ~tlinsCorrectionSet()
    {
        connection.reset();
    }
};

void tlinsWManageEngineState::on_pbUpdateDeviceManual_clicked()
{
    try {
        std::unique_ptr<TlinsAstroBase::tlinsCommunicationThreadRequest> req(new tlinsCorrectionSet { this, ui->manualRaCorrection->getValue(), ui->manualDecCorrection->getValue() });
        TlinsAstroBase::tlinsCommunicationThread::getInstance().push(req);
    } catch (tlinsException& exc) {
        TLINS_LOG_ERROR("Error: " + exc.getErrorMessage());

        auto mw = getMainWindowInstance();
        emit mw->logEvent(QString::fromStdString("Error: " + exc.getErrorMessage()));

        QMessageBox msgBox;
        msgBox.setText(QString::fromStdString("Error: " + exc.getErrorMessage()));
        msgBox.exec();
    }
}

void tlinsWManageEngineState::slot_dialRARatio(int value)
{
    ui->guiderRaRatio->setValue(static_cast<double>(value) / __dilerResolution__ * 1.0);
}

void tlinsWManageEngineState::slot_dialDECRatio(int value)
{
    ui->guiderDecRatio->setValue(static_cast<double>(value) / __dilerResolution__ * 1.0);
}

void tlinsWManageEngineState::slot_dialRACorrection(int value)
{
    ui->manualRaCorrection->setValue(static_cast<double>(value) / __dilerResolution__ * 1.0);
}

void tlinsWManageEngineState::slot_dialDECCorrection(int value)
{
    ui->manualDecCorrection->setValue(static_cast<double>(value) / __dilerResolution__ * 1.0);
}

void tlinsWManageEngineState::slotViewSelection(bool)
{
    auto ctrSte = [this]() {
        ui->gbStateControl->setVisible(true);
        if (ui->rbStandard->isChecked()) {
            ui->groupBoxGuider->setVisible(false);
            ui->groupBoxManualCorrections->setVisible(false);
            ui->frameGuider->setVisible(false);
            ui->frameManual->setVisible(false);
        }

        if (ui->rbGuider->isChecked()) {
            ui->groupBoxGuider->setVisible(true);
            ui->groupBoxManualCorrections->setVisible(false);
            ui->frameGuider->setVisible(true);
            ui->frameManual->setVisible(false);
        }

        if (ui->rbStandardSpeed->isChecked()) {
            ui->frameGuider->setVisible(false);
            ui->frameManual->setVisible(true);
            ui->groupBoxGuider->setVisible(false);
            ui->groupBoxManualCorrections->setVisible(true);
        }
    };

    if (ui->radioButtonCtrlView->isChecked()) {
        ui->groupBoxState->setVisible(false);
        ctrSte();
    }

    if (ui->radioButtonStateView->isChecked()) {
        ui->groupBoxState->setVisible(true);
        ui->gbStateControl->setVisible(false);
        ui->groupBoxGuider->setVisible(false);
        ui->groupBoxManualCorrections->setVisible(false);
        ui->frameGuider->setVisible(false);
        ui->frameManual->setVisible(false);
    }

    if (ui->radioButtonAllView->isChecked()) {
        ui->groupBoxState->setVisible(true);
        ctrSte();
    }
}

void tlinsWManageEngineState::on_btDownloadState_clicked()
{
    try {
        std::unique_ptr<TlinsAstroBase::tlinsCommunicationThreadRequest> req(new tlinsStateDownload { this });
        TlinsAstroBase::tlinsCommunicationThread::getInstance().push(req);
    } catch (tlinsException& exc) {
        TLINS_LOG_ERROR("Error: " + exc.getErrorMessage());

        auto mw = getMainWindowInstance();
        emit mw->logEvent(QString::fromStdString("Error: " + exc.getErrorMessage()));

        QMessageBox msgBox;
        msgBox.setText(QString::fromStdString("Error: " + exc.getErrorMessage()));
        msgBox.exec();
    }
}

//
// -------------------------------
// Odczyt stanu silnika
// -------------------------------
//
class tlinsStateUpload : public TlinsAstroBase::tlinsCommunicationThreadRequest {
private:
    std::shared_ptr<TlinsAstroBase::tlinsConnectionContext> connection;
    tlinsWManageEngineState* parent;
    TlinsAstroBase::tlinsAstroEngineState state;

public:
    void confirm()
    {
        TlinsAstroBase::tlinsCommunicationThreadRequest::confirm();
    }

    virtual void operator()() noexcept
    {
        try {
            // Odczy stanu
            tlinsAstroEngineInterface::tlinsEngineStateInfo stateInfo;

            stateInfo.set_xReverse(state.getXReverse());
            stateInfo.set_yReverse(state.getYReverse());

            std::array<std::array<double, 3>, 3> m;
            m[0][0] = state.getA11();
            m[0][1] = state.getA12();
            m[0][2] = state.getA13();

            m[1][0] = state.getA21();
            m[1][1] = state.getA22();
            m[1][2] = state.getA23();

            m[2][0] = state.getA31();
            m[2][1] = state.getA32();
            m[2][2] = state.getA33();
            stateInfo.set_attitude(m);

            tlinsAstroEngineInterface::tlinsDevicePosition devPos;
            devPos.set_x(state.getDeviceX());
            devPos.set_y(state.getDeviceY());
            devPos.set_xEncoder(state.getDeviceXEncoder());
            devPos.set_yEncoder(state.getDeviceYEncoder());
            stateInfo.set_devicePosition(devPos);

            switch (state.getMode()) {
            case TlinsAstroBase::tlinsAstroEngineState::EngineMode::MODE_EXTERNAL_SUPPORT:
                stateInfo.set_mode(tlinsAstroEngineInterface::tlinsEngineMode::MODE_EXTERNAL_SUPPORT);
                break;
            case TlinsAstroBase::tlinsAstroEngineState::EngineMode::MODE_STANDARD:
                stateInfo.set_mode(tlinsAstroEngineInterface::tlinsEngineMode::MODE_STANDARD);
                break;
            case TlinsAstroBase::tlinsAstroEngineState::EngineMode::MODE_NONE:
                stateInfo.set_mode(tlinsAstroEngineInterface::tlinsEngineMode::MODE_NONE);
                break;
            }

            switch (state.getState()) {
            case TlinsAstroBase::tlinsAstroEngineState::EngineState::STATE_CALIBRATION:
                stateInfo.set_state(tlinsAstroEngineInterface::tlinsEngineStateValue::STATE_CALIBRATION);
                break;
            case TlinsAstroBase::tlinsAstroEngineState::EngineState::STATE_CALIBRATION_VELOCITY:
                stateInfo.set_state(tlinsAstroEngineInterface::tlinsEngineStateValue::STATE_CALIBRATION_VELOCITY);
                break;
            case TlinsAstroBase::tlinsAstroEngineState::EngineState::STATE_REGULAR:
                stateInfo.set_state(tlinsAstroEngineInterface::tlinsEngineStateValue::STATE_REGULAR);
                break;
            }

            tlinsAstroEngineInterface::tlinsTarget target;
            tlinsAstroEngineInterface::tlinsAstroObject tObject;

            target.set_aceleration(state.getAceleration());
            target.set_speed(state.getSpeed());
            target.set_delta(state.getDelta());

            tObject.set_catalogType(state.getCatalogType());
            tObject.set_parallax(state.getParallex());
            tObject.set_properMotionRA(state.getPmRA());
            tObject.set_properMotionDC(state.getPmDC());
            tObject.set_radialVelocity(state.getRadialVelocity());

            {
                int h;
                int m;
                double s;
                bool sign;
                TlinsAstroBase::tlinsAstroBaseUtils::splitRA(state.getRA(), h, m, s, sign);

                tlinsAstroEngineInterface::tlinsCoordinate ra;
                ra.set_degris(h);
                ra.set_minutes(m);
                ra.set_seconds(s);
                ra.set_sign(sign);
                tObject.set_hourAngle(ra);
            }

            {
                int d;
                int m;
                double s;
                bool sign;
                TlinsAstroBase::tlinsAstroBaseUtils::splitDegris(state.getDC(), d, m, s, sign);

                tlinsAstroEngineInterface::tlinsCoordinate dc;
                dc.set_degris(d);
                dc.set_minutes(m);
                dc.set_seconds(s);
                dc.set_sign(sign);
                tObject.set_declination(dc);
            }

            target.set_object(tObject);

            stateInfo.set_currentTarget(target);

            // Uruchomienie zapytania
            connection->getAstro()->restoreState(stateInfo);

            // Aktualizacja stanu
            auto& statusInfo = TlinsAstroBase::tlinsServerStatusInfo::getInstance();
            statusInfo.update();

            auto mw = getMainWindowInstance();
            emit mw->logEvent("Engine state uploded");
            emit parent->notiStatus("Engine state uploded");
        } catch (tlinsInterfaceException& exc) {
            auto mw = getMainWindowInstance();
            emit mw->logEvent(QString::fromStdString(std::string { "Engine state upload error. Error " } + exc.getErrorMessage()));
            emit parent->notiStatus("Engine state upload error. Error " + exc.getErrorMessage());
        }
    }

    virtual bool isAsynchronuus()
    {
        return false;
    }

    virtual std::string name()
    {
        return "tlinsStateUload";
    }

    tlinsStateUpload(tlinsWManageEngineState* parent_,
        const TlinsAstroBase::tlinsAstroEngineState& state_)
        : parent { parent_ }
        , state { state_ }
    {
        // Pobranie polaczenia
        if (!TlinsAstroBase::tlinsConnectionsManager::getInstance().hasConnection(std::string { TLINS_CONNECTION_DEFAULT }))
            __THROW__(tlinsException(std::string("No active connection: ") + std::string(TLINS_CONNECTION_DEFAULT), -1));

        // Polaczenie
        connection = TlinsAstroBase::tlinsConnectionsManager::getInstance().getConnection(TLINS_CONNECTION_DEFAULT);
    }

    virtual ~tlinsStateUpload()
    {
        connection.reset();
    }
};

void tlinsWManageEngineState::on_btUploadState_clicked()
{
    try {
        if (isSet) {
            std::unique_ptr<TlinsAstroBase::tlinsCommunicationThreadRequest> req(new tlinsStateUpload(this, currentState));
            TlinsAstroBase::tlinsCommunicationThread::getInstance().push(req);
        } else {
            QMessageBox msgBox;
            msgBox.setText("No stored state or no state selected.");
            msgBox.exec();
        }
    } catch (tlinsException& exc) {
        TLINS_LOG_ERROR("Error: " + exc.getErrorMessage());

        auto mw = getMainWindowInstance();
        emit mw->logEvent(QString::fromStdString("Error: " + exc.getErrorMessage()));

        QMessageBox msgBox;
        msgBox.setText(QString::fromStdString("Error: " + exc.getErrorMessage()));
        msgBox.exec();
    }
}

tlinsWManageEngineState::~tlinsWManageEngineState()
{
    delete ui;
}
