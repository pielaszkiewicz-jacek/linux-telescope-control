#include "tlinscalibrationitemmodel.h"
#include "tlinsuistrutils.h"

#include <QFont>

static std::vector<std::string> __columns__ = {
    "Status",
    "Catalog type",
    "Catalog ID",
    "Catalog description",
    "Name",
    "Description",
    "Type",
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
    "Radial velocity",
    "Parallex",
    "Record id"
};

int tlinsCalibrationItemModel::rowCount(const QModelIndex&) const
{
    return static_cast<int>(calibrationData.size());
}

int tlinsCalibrationItemModel::columnCount(const QModelIndex&) const
{
    return static_cast<int>(__columns__.size());
}

void tlinsCalibrationItemModel::updateItemStatus(const TlinsAstroBase::tlinsAstroCalibrationItem::calibrationStatus status, int row)
{
    auto& dataRow = calibrationData[static_cast<unsigned int>(row)];
    dataRow.setStatus(status);
}

QVariant tlinsCalibrationItemModel::data(const QModelIndex& index, int role) const
{
    int row = index.row();
    int column = index.column();

    QVariant out;

    TlinsAstroBase::tlinsAstroCalibrationItem dataRow = calibrationData[static_cast<unsigned int>(row)];

    if (role == Qt::TextAlignmentRole) {
        if (column >= 8) {
            return QVariant(Qt::AlignVCenter | Qt::AlignRight);
        }
    }

    if (role == Qt::CheckStateRole) {
        if (column == 0) {
            if (dataRow.getStatus() == TlinsAstroBase::tlinsAstroCalibrationItem::calibrationStatus::COMPLETED) {
                return Qt::Checked;
            } else {
                return Qt::Unchecked;
            }
        }
    }

    if (role == Qt::DisplayRole) {
        switch (column) {
        case 0: {
            switch (dataRow.getStatus()) {
            case TlinsAstroBase::tlinsAstroCalibrationItem::calibrationStatus::NONE:
                out = "Not used";
                break;
            case TlinsAstroBase::tlinsAstroCalibrationItem::calibrationStatus::SET_AS_BASE_OBJECT:
                out = "Set as base";
                break;
            case TlinsAstroBase::tlinsAstroCalibrationItem::calibrationStatus::COMPLETED:
                out = "Completed";
                break;
            }
        } break;
        case 1:
            out = dataRow.getCatalogType().name.c_str();
            break;
        case 2:
            out = dataRow.getObjectIdInCatalog().c_str();
            break;
        case 3:
            out = dataRow.getObjectDescription().c_str();
            break;
        case 4:
            out = dataRow.getName().c_str();
            break;
        case 5:
            out = dataRow.getDescription().c_str();
            break;
        case 6:
            out = dataRow.getType().name.c_str();
            break;
        case 7:
            out = dataRow.getConstelation().name.c_str();
            break;
        case 8:
            out = tlinsUiStrUtils::setValueHour(dataRow.getRA());
            break;
        case 9:
            out = tlinsUiStrUtils::setValueDegris(dataRow.getDC());
            break;
        case 10:
            out = dataRow.getPmRA();
            break;
        case 11:
            out = dataRow.getPmDC();
            break;
        case 12:
            out = dataRow.getEpRA();
            break;
        case 13:
            out = dataRow.getEpDC();
            break;
        case 14:
            out = dataRow.getMinErrRA();
            break;
        case 15:
            out = dataRow.getMinErrDC();
            break;
        case 16:
            out = dataRow.getErrMeanRA();
            break;
        case 17:
            out = dataRow.getErrMeanDC();
            break;
        case 18:
            out = dataRow.getErrMeanPmRA();
            break;
        case 19:
            out = dataRow.getErrMeanPmDC();
            break;
        case 20:
            out = dataRow.getRadialVelocity();
            break;
        case 21:
            out = dataRow.getParallex();
            break;
        case 22:
            out = static_cast<unsigned int>(dataRow.getObjectOrder());
            break;
        default:
            break;
        }
    }
    return out;
}

QVariant tlinsCalibrationItemModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (static_cast<unsigned int>(section) >= __columns__.size()) {
        return QVariant();
    }

    if (role == Qt::DisplayRole && orientation == Qt::Horizontal) {
        return QVariant(__columns__[static_cast<unsigned int>(section)].c_str());
    }

    return QVariant();
}

void tlinsCalibrationItemModel::setItems(const std::vector<TlinsAstroBase::tlinsAstroCalibrationItem>& calibrationData_)
{
    calibrationData.erase(calibrationData.begin(), calibrationData.end());

    for (unsigned int i = 0; i < calibrationData_.size(); i++) {
        calibrationData.push_back(calibrationData_[i]);
        calibrationData[i].setObjectOrder(i);
    }
    emit layoutChanged();
}

bool tlinsCalibrationItemModel::insertItem(const TlinsAstroBase::tlinsAstroCalibrationItem& calibrationData_)
{
    // Sprawdzenie czy przypadkiem nie ma duplikaatu
    std::string catalog = calibrationData_.getCatalogType().label;
    std::string catalogId = calibrationData_.getObjectIdInCatalog();

    for (auto iter = calibrationData.begin(); iter != calibrationData.end(); iter++) {
        if (iter->getCatalogType().label.compare(catalog) == 0 && iter->getObjectIdInCatalog().compare(catalogId) == 0) {
            return false;
        }
    }

    calibrationData.push_back(calibrationData_);
    calibrationData[calibrationData.size() - 1].setObjectOrder(calibrationData.size() - 1);
    emit layoutChanged();
    return true;
}

void tlinsCalibrationItemModel::deleteItem(const int idx)
{
    if (idx < 0 || static_cast<unsigned int>(idx) >= calibrationData.size()) {
        return;
    }

    calibrationData.erase(calibrationData.begin() + idx);

    int i = 0;
    for (auto iter = calibrationData.begin(); iter != calibrationData.end(); iter++, i++) {
        calibrationData[static_cast<unsigned int>(i)].setObjectOrder(i);
    }
    emit layoutChanged();
}

void tlinsCalibrationItemModel::clear()
{
    calibrationData.erase(calibrationData.begin(), calibrationData.end());
    emit layoutChanged();
}

void tlinsCalibrationItemModel::deleteItems(const std::vector<TlinsAstroBase::tlinsAstroCalibrationItem>& calibrationData_)
{
    for (auto iter = calibrationData_.begin(); iter != calibrationData_.end(); iter++) {
        for (auto iter2 = calibrationData.begin(); iter2 != calibrationData.end(); iter2++) {
            if (iter2->getCatalogType().label.compare(iter->getCatalogType().label) == 0 && iter2->getObjectIdInCatalog().compare(iter->getObjectIdInCatalog()) == 0) {
                calibrationData.erase(iter2, iter2);
            }
        }
    }

    int i = 0;
    for (auto iter = calibrationData.begin(); iter != calibrationData.end(); iter++, i++) {
        calibrationData[static_cast<unsigned int>(i)].setObjectOrder(i);
    }
    emit layoutChanged();
}

void tlinsCalibrationItemModel::moveUp(const int i)
{
    if (i == 0 || calibrationData.size() < 2) {
        return;
    }

    TlinsAstroBase::tlinsAstroCalibrationItem item = calibrationData[static_cast<unsigned int>(i - 1)];
    calibrationData[static_cast<unsigned int>(i - 1)] = calibrationData[static_cast<unsigned int>(i)];
    calibrationData[static_cast<unsigned int>(i)] = item;
    calibrationData[static_cast<unsigned int>(i - 1)].setObjectOrder(i - 1);
    calibrationData[static_cast<unsigned int>(i)].setObjectOrder(i);
    emit layoutChanged();
}

void tlinsCalibrationItemModel::moveDown(const int i)
{
    if (i == calibrationData.size() - 1 || calibrationData.size() < 2) {
        return;
    }

    TlinsAstroBase::tlinsAstroCalibrationItem item = calibrationData[static_cast<unsigned int>(i + 1)];
    calibrationData[static_cast<unsigned int>(i + 1)] = calibrationData[static_cast<unsigned int>(i)];
    calibrationData[static_cast<unsigned int>(i)] = item;
    calibrationData[static_cast<unsigned int>(i + 1)].setObjectOrder(i + 1);
    calibrationData[static_cast<unsigned int>(i)].setObjectOrder(i);
    emit layoutChanged();
}

tlinsCalibrationItemModel::tlinsCalibrationItemModel(QObject* parent)
    : QAbstractTableModel(parent)
{
}
