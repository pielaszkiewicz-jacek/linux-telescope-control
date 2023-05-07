#include "tlinsastrocalibrationitem.h"

namespace TlinsAstroBase {

long tlinsAstroCalibrationItem::getObjectOrder() const
{
    return objectOrder;
}

void tlinsAstroCalibrationItem::setObjectOrder(const long v)
{
    objectOrder = v;
}

tlinsAstroCalibrationItem& tlinsAstroCalibrationItem::operator=(const tlinsAstroCalibrationItem& v)
{
    tlinsAstroCatalogItem::operator=(v);
    objectOrder = v.objectOrder;
    status = v.status;
    return *this;
}

tlinsAstroCalibrationItem::calibrationStatus tlinsAstroCalibrationItem::getStatus() const
{
    return status;
}
void tlinsAstroCalibrationItem::setStatus(const tlinsAstroCalibrationItem::calibrationStatus v)
{
    status = v;
}

tlinsAstroCalibrationItem::tlinsAstroCalibrationItem(const tlinsAstroCatalogItem& v)
    : tlinsAstroCatalogItem(v)
{
    status = tlinsAstroCalibrationItem::calibrationStatus::NONE;
}

tlinsAstroCalibrationItem::tlinsAstroCalibrationItem(const tlinsAstroCalibrationItem& v)
{
    *this = v;
}

tlinsAstroCalibrationItem::tlinsAstroCalibrationItem()
{
    status = tlinsAstroCalibrationItem::calibrationStatus::NONE;
}

tlinsAstroCalibrationItem::~tlinsAstroCalibrationItem()
{
}

}
