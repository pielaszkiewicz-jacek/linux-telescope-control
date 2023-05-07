#include "tlinsobservationplacenodel.h"

#include "tlinsuistrutils.h"

static std::vector<std::string> __columns__ = {
    "Is default",
    "Name",
    "Longitude",
    "Latitude",
    "High over elipsoide",
    "Elipsoide type"
};

int tlinsObservationPlaceNodel::rowCount(const QModelIndex&) const
{
    return static_cast<int>(placeData.size());
}

int tlinsObservationPlaceNodel::columnCount(const QModelIndex&) const
{
    return static_cast<int>(__columns__.size());
}

QVariant tlinsObservationPlaceNodel::data(const QModelIndex& index, int role) const
{
    int row = index.row();
    int column = index.column();

    QVariant out;

    TlinsAstroBase::tlinsPlace dataRow = placeData[static_cast<unsigned int>(row)];

    if (role == Qt::TextAlignmentRole)
        return QVariant(Qt::AlignVCenter | Qt::AlignRight);

    if (role == Qt::CheckStateRole) {
        if (column == 0) {
            if (dataRow.isDefault())
                return Qt::Checked;
            else
                return Qt::Unchecked;
        }
    }

    if (role == Qt::DisplayRole) {
        switch (column) {
        case 0:
            // Default
            if (dataRow.isDefault())
                out = "Default";
            else
                out = "Non default";
            break;

        case 1:
            // Name
            out = QString(dataRow.getName().c_str());
            break;

        case 2:
            // Longitude
            out = tlinsUiStrUtils::setValueDegris(dataRow.getLongitude());
            break;

        case 3:
            // Latitude
            out = tlinsUiStrUtils::setValueDegris(dataRow.getLatitude());
            break;

        case 4:
            // High over elipsoide
            out = dataRow.getHm();
            break;

        case 5:
            // Elipsoide type
            switch (dataRow.getEpType()) {
            case TlinsAstroBase::tlinsPlace::ElipsoideType::GRS_80:
                out = QString("GRS_80");
                break;
            case TlinsAstroBase::tlinsPlace::ElipsoideType::WGS_72:
                out = QString("WGS_80");
                break;
            case TlinsAstroBase::tlinsPlace::ElipsoideType::WGS_84:
                out = QString("WGS_84");
                break;
            }
            break;

        default:
            break;
        }
    }
    return out;
}

QVariant tlinsObservationPlaceNodel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (static_cast<unsigned>(section) >= __columns__.size())
        return QVariant();

    if (role == Qt::DisplayRole && orientation == Qt::Horizontal)
        return QVariant(__columns__[static_cast<unsigned int>(section)].c_str());

    return QVariant();
}

void tlinsObservationPlaceNodel::setItems(const std::vector<TlinsAstroBase::tlinsPlace>&)
{
}

bool tlinsObservationPlaceNodel::updateItem(const TlinsAstroBase::tlinsPlace& data)
{
    if (data.isDefault()) {
        for (auto& item : placeData)
            item.setDefault(false);
    }

    for (auto& item : placeData) {
        if (item.getName() == data.getName()) {
            item = data;
            emit layoutChanged();
            return true;
        }
    }

    placeData.push_back(data);

    std::sort(placeData.begin(),
        placeData.end(),
        [](TlinsAstroBase::tlinsPlace a, TlinsAstroBase::tlinsPlace b) {
            return a.getName() < b.getName();
        });

    emit layoutChanged();
    return true;
}

bool tlinsObservationPlaceNodel::insertItem(const TlinsAstroBase::tlinsPlace& data)
{
    for (auto& item : placeData) {
        if (item.getName() == data.getName())
            return false;
    }

    if (data.isDefault()) {
        for (auto& item : placeData)
            item.setDefault(false);
    }

    placeData.push_back(data);

    std::sort(placeData.begin(),
        placeData.end(),
        [](TlinsAstroBase::tlinsPlace a, TlinsAstroBase::tlinsPlace b) {
            return a.getName() < b.getName();
        });

    emit layoutChanged();
    return true;
}

void tlinsObservationPlaceNodel::deleteItems(const std::vector<TlinsAstroBase::tlinsPlace>& data)
{
    for (auto& item : data) {
        for (auto iter = placeData.begin(); iter != placeData.end(); iter++) {
            if (item.getName() == iter->getName()) {
                placeData.erase(iter);
                break;
            }
        }
    }
    emit layoutChanged();
}

bool tlinsObservationPlaceNodel::deleteItem(const unsigned int)
{
    return false;
}

void tlinsObservationPlaceNodel::clear()
{
}

tlinsObservationPlaceNodel::tlinsObservationPlaceNodel(QObject* parent)
    : QAbstractTableModel(parent)
{
}
