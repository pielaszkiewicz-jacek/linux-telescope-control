#ifndef TLINSWMANAGEENGINESTATE_H
#define TLINSWMANAGEENGINESTATE_H

#include <QItemSelection>
#include <QModelIndex>
#include <QVariant>
#include <QWidget>
#include <tlinsastroenginestate.h>

class tlinsEngineStateModelModel : public QAbstractTableModel {
    Q_OBJECT
public:
    int rowCount(const QModelIndex& parent = QModelIndex()) const;
    int columnCount(const QModelIndex& parent = QModelIndex()) const;
    QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const;
    QVariant headerData(int section, Qt::Orientation orientation, int role) const;

private:
    std::vector<TlinsAstroBase::tlinsAstroEngineState> stateData;

public:
    std::vector<TlinsAstroBase::tlinsAstroEngineState>& getData()
    {
        return stateData;
    }

    void
    setItems(const std::vector<TlinsAstroBase::tlinsAstroEngineState>& data);
    bool updateItem(const TlinsAstroBase::tlinsAstroEngineState& data);
    bool insertItem(const TlinsAstroBase::tlinsAstroEngineState& data);
    void
    deleteItems(const std::vector<TlinsAstroBase::tlinsAstroEngineState>& data);
    bool deleteItem(const unsigned int idx);
    void clear();

public:
    tlinsEngineStateModelModel(QObject* parent = nullptr);

signals:
    void editCompleted(const QString&);
};

//
// —------------------------------------------------------
// —------------------------------------------------------
// —------------------------------------------------------
//

namespace Ui {
class tlinsWManageEngineState;
}

class tlinsWManageEngineState : public QWidget {
    Q_OBJECT

public:
    explicit tlinsWManageEngineState(QWidget* parent = nullptr);
    ~tlinsWManageEngineState();

signals:
    void notiStatus(std::string);
    void updateCurrentState(const TlinsAstroBase::tlinsAstroEngineState& state);

    void updateGuiderRatio(double ra, double dc);
    void updateCorrection(double ra, double dc);

public slots:
    void notiStatusSlot(std::string str);
    void
    updateCurrentStateSlot(const TlinsAstroBase::tlinsAstroEngineState& state);

private slots:

    void updateGuiderRatioSlot(double ra, double dc);
    void updateCorrectionSlot(double ra, double dc);

    void on_selectionChanged(const QItemSelection& selected,
        const QItemSelection& deselected);
    void on_btAdd_clicked();
    void on_btRemove_clicked();
    void on_btSave_clicked();
    void on_btStart_clicked();
    void on_btStop_clicked();

    void on_btLoad_clicked();

    void on_btUploadState_clicked();
    void on_btDownloadState_clicked();

    void on_pbReadFromDeviceManual_clicked();
    void on_pbUpdateDeviceManual_clicked();

    void on_pbLoadGuider_clicked();
    void on_pbUpdateDeviceGuider_clicked();
    void on_pbSReadFromDeviceGuider_clicked();
    void on_pbStoreGuider_clicked();

    void slotViewSelection(bool val);

    void slot_dialRARatio(int);
    void slot_dialDECRatio(int);

    void slot_dialRACorrection(int);
    void slot_dialDECCorrection(int);

private:
    TlinsAstroBase::tlinsAstroEngineState currentState;
    bool isSet;

private:
    void setValueUi(const TlinsAstroBase::tlinsAstroEngineState& data);

private:
    Ui::tlinsWManageEngineState* ui;
    tlinsEngineStateModelModel dataModel;
};

#endif // TLINSWMANAGEENGINESTATE_H
