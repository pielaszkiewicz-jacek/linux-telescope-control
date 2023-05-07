#ifndef TLINSCALIBRATIONITEMMODEL_H
#define TLINSCALIBRATIONITEMMODEL_H

#include <tlinsastrocalibrationitem.h>
#include <tlinsastrocatalogcollection.h>

#include <QAbstractTableModel>
#include <QObject>
#include <vector>

class tlinsCalibrationItemModel : public QAbstractTableModel {
    Q_OBJECT

public:
    int rowCount(const QModelIndex& parent = QModelIndex()) const;
    int columnCount(const QModelIndex& parent = QModelIndex()) const;
    QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const;
    QVariant headerData(int section, Qt::Orientation orientation, int role) const;

private:
    std::vector<TlinsAstroBase::tlinsAstroCalibrationItem> calibrationData;

public:
    std::vector<TlinsAstroBase::tlinsAstroCalibrationItem>& getCalibrationData()
    {
        return calibrationData;
    }

    void setItems(const std::vector<TlinsAstroBase::tlinsAstroCalibrationItem>& calibrationData_);
    bool insertItem(const TlinsAstroBase::tlinsAstroCalibrationItem& calibrationData_);
    void deleteItems(const std::vector<TlinsAstroBase::tlinsAstroCalibrationItem>& calibrationData_);
    void deleteItem(const int idx);

    void updateItemStatus(const TlinsAstroBase::tlinsAstroCalibrationItem::calibrationStatus status, int row);

    void moveUp(const int item);
    void moveDown(const int item);
    void clear();

public:
    tlinsCalibrationItemModel(QObject* parent = nullptr);

signals:
    void editCompleted(const QString&);
};

#endif // TLINSCALIBRATIONITEMMODEL_H
