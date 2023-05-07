#include "tlinsiersmodel.h"
#include "tlinsiers.h"
#include "tlinsuistrutils.h"

#include <algorithm>

static std::vector<std::string> __columns__ = {
    "  Year    ",
    "  Month   ",
    "  Day     ",
    "  PM X    ",
    "  PM Y    ",
    " UT1-UTC  ",
    "   Psi    ",
    " Epsilon  ",
    "   DX     ",
    "   DY     "
};

int tlinsIERSModel::rowCount(const QModelIndex&) const
{
    return static_cast<int>(iersData.size());
}

int tlinsIERSModel::columnCount(const QModelIndex&) const
{
    return static_cast<int>(__columns__.size()) + 1;
}

QVariant tlinsIERSModel::data(const QModelIndex& index, int role) const
{
    auto row = index.row();
    auto column = index.column();

    QVariant out;

    auto& dataRow = iersData[static_cast<unsigned int>(row)];

    if (role == Qt::TextAlignmentRole) {
        return QVariant(Qt::AlignVCenter | Qt::AlignRight);
    }

    if (role == Qt::DisplayRole) {
        switch (column) {
        case 0:
            // Year
            out = dataRow.getYear();
            break;

        case 1:
            // Month
            out = dataRow.getMonth();
            break;

        case 2:
            // Day
            out = dataRow.getDay();
            break;

        case 3:
            // PMX
            out = tlinsUiStrUtils::setValueDegris(dataRow.getPmx());
            break;

        case 4:
            // PMY
            out = tlinsUiStrUtils::setValueDegris(dataRow.getPmy());
            break;

        case 5:
            // UT1 - UTC
            out = dataRow.getDeltaUt();
            break;

        case 6:
            // Psi
            out = dataRow.getDPsi();
            break;

        case 7:
            // Epsilon
            out = dataRow.getDEpsilon();
            break;

        case 8:
            // DX
            out = tlinsUiStrUtils::setValueDegris(dataRow.getDx());
            break;

        case 9:
            // DY
            out = tlinsUiStrUtils::setValueDegris(dataRow.getDy());
            break;

        default:
            break;
        }
    }
    return out;
}

QVariant tlinsIERSModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (static_cast<unsigned>(section) >= __columns__.size()) {
        return QVariant();
    }

    if (role == Qt::DisplayRole && orientation == Qt::Horizontal) {
        return QVariant(__columns__[static_cast<unsigned int>(section)].c_str());
    }
    return QVariant();
}

void tlinsIERSModel::setItems(const std::vector<TlinsAstroBase::tlinsIERS>& data)
{
    iersData.clear();

    for (auto& item : data) {
        iersData.push_back(item);
    }
    emit layoutChanged();
}

static bool validateItem(const TlinsAstroBase::tlinsIERS& data)
{
    if (data.getDay() <= 0 || data.getDay() > 31) {
        return false;
    }

    if (data.getMonth() <= 0 || data.getMonth() > 12) {
        return false;
    }

    if (data.getYear() <= 0) {
        return false;
    }
    return true;
}

bool tlinsIERSModel::insertItem(const TlinsAstroBase::tlinsIERS& data)
{
    if (!validateItem(data)) {
        return false;
    }

    // Sprawdzanie duplikatu
    for (auto& item : iersData) {
        if (item.getYear() == data.getYear() && item.getMonth() == data.getMonth() && item.getDay() == data.getDay()) {
            // Duplikat
            return false;
        }
    }

    // Insert new item into the list
    iersData.push_back(data);

    // Sort data
    std::sort(iersData.begin(),
        iersData.end(),
        [](TlinsAstroBase::tlinsIERS a, TlinsAstroBase::tlinsIERS b) {
            if (a.getYear() < b.getYear()) {
                return true;
            } else if (a.getYear() == b.getYear() && a.getMonth() < b.getMonth()) {
                return true;
            } else if (a.getYear() == b.getYear() && a.getMonth() == b.getMonth() && a.getDay() < b.getDay()) {
                return true;
            }
            return false;
        });

    emit layoutChanged();
    return true;
}

bool tlinsIERSModel::updateItem(const TlinsAstroBase::tlinsIERS& data)
{
    if (!validateItem(data)) {
        return false;
    }

    // Wyszukanie pozycji
    unsigned int idx = 0;
    for (idx = 0; idx < iersData.size(); idx++) {
        auto& item = iersData[idx];
        if (item.getYear() == data.getYear() && item.getMonth() == data.getMonth() && item.getDay() == data.getDay()) {
            break;
        }
    }
    if (idx >= iersData.size()) {
        insertItem(data);
        return true;
    }
    iersData[idx] = data;
    emit layoutChanged();
    return true;
}

bool tlinsIERSModel::deleteItem(const unsigned int idx)
{
    if (idx >= iersData.size()) {
        return false;
    }

    iersData.erase(iersData.begin() + idx);
    emit layoutChanged();
    return true;
}

void tlinsIERSModel::clear()
{
    iersData.clear();
    emit layoutChanged();
}

void tlinsIERSModel::deleteItems(const std::vector<TlinsAstroBase::tlinsIERS>& data)
{
    for (auto& iter : data) {
        for (auto iter2 = iersData.begin(); iter2 != iersData.end(); iter2++) {
            if (iter2->getYear() == iter.getYear() && iter2->getMonth() == iter.getMonth() && iter2->getDay() == iter.getDay()) {
                iersData.erase(iter2);
                break;
            }
        }
    }
    emit layoutChanged();
}

tlinsIERSModel::tlinsIERSModel(QObject* parent)
    : QAbstractTableModel(parent)
{
}
