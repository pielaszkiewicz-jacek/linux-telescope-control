#ifndef TLINSASTROOBJECTSVIEWMODEL_H
#define TLINSASTROOBJECTSVIEWMODEL_H

#include <QAbstractTableModel>
#include <tlinsastrocatalogcollection.h>

#include <vector>

class tlinsAstroObjectsViewModel : public QAbstractTableModel {
    Q_OBJECT
public:
    int rowCount(const QModelIndex& parent = QModelIndex()) const;
    int columnCount(const QModelIndex& parent = QModelIndex()) const;
    QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const;
    QVariant headerData(int section, Qt::Orientation orientation, int role) const;

private:
    TlinsAstroBase::tlinsAstroCatalogCollection catalogData;

public:
    bool updateDataItem(int idx, const TlinsAstroBase::tlinsAstroCatalogItem& item);
    void insertDataItem(TlinsAstroBase::tlinsAstroCatalogItem& item);
    void setData(const TlinsAstroBase::tlinsAstroCatalogCollection& data);
    void deleteDataItems(TlinsAstroBase::tlinsAstroCatalogCollection& items);
    TlinsAstroBase::tlinsAstroCatalogCollection& getData()
    {
        return catalogData;
    }

    void confirm();

public:
    // Konstruktor klasy
    tlinsAstroObjectsViewModel(QObject* parent);

signals:
    void editCompleted(const QString&);
};

#endif // TLINSASTROOBJECTSVIEWMODEL_H
