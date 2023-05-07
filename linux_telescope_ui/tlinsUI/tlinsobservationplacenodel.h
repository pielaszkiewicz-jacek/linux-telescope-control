#ifndef TLINSOBSERVATIONPLACENODEL_H
#define TLINSOBSERVATIONPLACENODEL_H

#include <QModelIndex>
#include <QVariant>
#include <vector>

#include "tlinsplace.h"

class tlinsObservationPlaceNodel : public QAbstractTableModel {
    Q_OBJECT

public:
    int rowCount(const QModelIndex& parent = QModelIndex()) const Q_DECL_OVERRIDE;
    int columnCount(const QModelIndex& parent = QModelIndex()) const Q_DECL_OVERRIDE;
    QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const Q_DECL_OVERRIDE;
    QVariant headerData(int section, Qt::Orientation orientation, int role) const Q_DECL_OVERRIDE;

private:
    std::vector<TlinsAstroBase::tlinsPlace> placeData;

public:
    std::vector<TlinsAstroBase::tlinsPlace>& getData()
    {
        return placeData;
    }

    void setItems(const std::vector<TlinsAstroBase::tlinsPlace>& data);
    bool updateItem(const TlinsAstroBase::tlinsPlace& data);
    bool insertItem(const TlinsAstroBase::tlinsPlace& data);
    void deleteItems(const std::vector<TlinsAstroBase::tlinsPlace>& data);
    bool deleteItem(const unsigned int idx);
    void clear();

signals:
    void editCompleted(const QString&);

public:
    tlinsObservationPlaceNodel(QObject* parent = nullptr);
};

#endif // TLINSOBSERVATIONPLACENODEL_H
