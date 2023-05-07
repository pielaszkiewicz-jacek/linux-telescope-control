#include "tlinsastroobjectsviewmodel.h"

#include "tlinsastrocatalogitem.h"
#include "tlinsuistrutils.h"
#include "tlinswcoordinatedeclination.h"
#include "tlinswcoordinatedegris.h"
#include "tlinswcoordinatehourangle.h"

#include <QDebug>
#include <string>
#include <vector>

static std::vector<std::string> __columns__ = {
    "Catalog type",
    "Catalog ID",
    "Catalog description",
    "Name",
    "Description",
    "Type",
    "Type details 1",
    "Type details 2",
    "Type details 3",
    "Constelation",
    "Right ascension",
    "Declination",
    "Proper motion (RA)",
    "Proper motion (DC)",
    "Central epoch (RA)",
    "Central epoch (DC)",
    "Min error (RA)",
    "Min error (DC)",
    "Mean error (RA)",
    "Mean error (DC)",
    "PM mean error (RA)",
    "PM mean error (DC)",
    "Magnitude",
    "Magnitude error",
    "Radial velocity",
    "Parallex",
    "Record ID"
};

tlinsAstroObjectsViewModel::tlinsAstroObjectsViewModel(QObject* parent)
    : QAbstractTableModel(parent)
{
}

void tlinsAstroObjectsViewModel::deleteDataItems(TlinsAstroBase::tlinsAstroCatalogCollection& items)
{
    for (int i = 0; i < items.count(); i++) {
        auto item = items.getItem(i);
        catalogData.removeItem(item);
    }
}

void tlinsAstroObjectsViewModel::confirm()
{
    emit layoutChanged();
}

void tlinsAstroObjectsViewModel::insertDataItem(TlinsAstroBase::tlinsAstroCatalogItem& item)
{
    catalogData.addItem(item);
    unsigned int idx = catalogData.count() - 1;
    catalogData[idx].setRecordID(idx /* - 1*/);
}

bool tlinsAstroObjectsViewModel::updateDataItem(int idx, const TlinsAstroBase::tlinsAstroCatalogItem& item)
{
    if (idx >= catalogData.count()) {
        return false;
    }

    unsigned int id = catalogData[idx].getRecordID();

    catalogData[idx] = item;
    catalogData[idx].setRecordID(id);
    return true;
}

void tlinsAstroObjectsViewModel::setData(const TlinsAstroBase::tlinsAstroCatalogCollection& data_)
{
    catalogData = data_;
    emit layoutChanged();
}

int tlinsAstroObjectsViewModel::rowCount(const QModelIndex& /*parent*/) const
{
    return catalogData.count();
}

int tlinsAstroObjectsViewModel::columnCount(const QModelIndex& /*parent*/) const
{
    return static_cast<int>(__columns__.size());
}

QVariant tlinsAstroObjectsViewModel::data(const QModelIndex& index, int role) const
{
    int row = index.row();
    int column = index.column();

    QVariant out;

    if (role == Qt::TextAlignmentRole) {
        if (column >= 10) {
            return QVariant(Qt::AlignVCenter | Qt::AlignRight);
        }
    }

    if (role == Qt::DisplayRole) {
        auto dataRow = catalogData.getItem(row);

        switch (column) {
        case 0:
            out = dataRow.getCatalogType().name.c_str();
            break;
        case 1:
            out = dataRow.getObjectIdInCatalog().c_str();
            break;
        case 2:
            out = dataRow.getObjectDescription().c_str();
            break;
        case 3:
            out = dataRow.getName().c_str();
            break;
        case 4:
            out = dataRow.getDescription().c_str();
            break;
        case 5:
            out = dataRow.getType().name.c_str();
            break;
        case 6:
            out = dataRow.getTypeDetails1().c_str();
            break;
        case 7:
            out = dataRow.getTypeDetails2().c_str();
            break;
        case 8:
            out = dataRow.getTypeDetails3().c_str();
            break;
        case 9:
            out = dataRow.getConstelation().name.c_str();
            break;
        case 10:
            out = tlinsUiStrUtils::setValueHour(dataRow.getRA());
            break;
        case 11:
            out = tlinsUiStrUtils::setValueDegris(dataRow.getDC());
            break;
        case 12:
            out = dataRow.getPmRA();
            break;
        case 13:
            out = dataRow.getPmDC();
            break;
        case 14:
            out = dataRow.getEpRA();
            break;
        case 15:
            out = dataRow.getEpDC();
            break;
        case 16:
            out = dataRow.getMinErrRA();
            break;
        case 17:
            out = dataRow.getMinErrDC();
            break;
        case 18:
            out = dataRow.getErrMeanRA();
            break;
        case 19:
            out = dataRow.getErrMeanDC();
            break;
        case 20:
            out = dataRow.getErrMeanPmRA();
            break;
        case 21:
            out = dataRow.getErrMeanPmDC();
            break;
        case 22:
            out = dataRow.getMagnitude();
            break;
        case 23:
            out = dataRow.getErrMagnitude();
            break;
        case 24:
            out = dataRow.getRadialVelocity();
            break;
        case 25:
            out = dataRow.getParallex();
            break;
        case 26:
            out = (unsigned int)dataRow.getRecordID();
            break;
        default:
            break;
        }
    }
    return out;
}

QVariant tlinsAstroObjectsViewModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (static_cast<unsigned long>(section) >= __columns__.size()) {
        return QVariant();
    }

    if (role == Qt::DisplayRole && orientation == Qt::Horizontal) {
        return QVariant(__columns__[static_cast<unsigned long>(section)].c_str());
    }

    return QVariant();
}
