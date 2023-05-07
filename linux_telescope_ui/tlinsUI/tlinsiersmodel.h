#ifndef TLINSIERSMODEL_H
#define TLINSIERSMODEL_H

#include "tlinsiers.h"

#include <QModelIndex>
#include <QVariant>
#include <vector>

class tlinsIERSModel : public QAbstractTableModel {
    Q_OBJECT

public:
    int rowCount(const QModelIndex& parent = QModelIndex()) const;
    int columnCount(const QModelIndex& parent = QModelIndex()) const;
    QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const;
    QVariant headerData(int section, Qt::Orientation orientation, int role) const;

private:
    std::vector<TlinsAstroBase::tlinsIERS> iersData;

public:
    std::vector<TlinsAstroBase::tlinsIERS>& getData()
    {
        return iersData;
    }

    void setItems(const std::vector<TlinsAstroBase::tlinsIERS>& data);
    bool updateItem(const TlinsAstroBase::tlinsIERS& data);
    bool insertItem(const TlinsAstroBase::tlinsIERS& data);
    void deleteItems(const std::vector<TlinsAstroBase::tlinsIERS>& data);
    bool deleteItem(const unsigned int idx);
    void clear();

public:
    tlinsIERSModel(QObject* parent = nullptr);

signals:
    void editCompleted(const QString&);
};

#endif // TLINSIERSMODEL_H
