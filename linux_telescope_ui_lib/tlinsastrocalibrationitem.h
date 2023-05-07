#ifndef TLINSASTROCALIBRATIONITEM_H
#define TLINSASTROCALIBRATIONITEM_H

#include <string>
#include <tlinsastrocatalogitem.h>

namespace TlinsAstroBase {

class tlinsAstroCalibrationItem : public tlinsAstroCatalogItem {
public:
    enum class calibrationStatus {
        NONE = 0, // Nie uzyty jeszcze
        SET_AS_BASE_OBJECT = 1, // Ustawiony jako obiekt bazowy
        COMPLETED = 3 // Po kalibracji
    };

private:
    // Licznik kolejnosci
    long objectOrder;
    calibrationStatus status;

public:
    calibrationStatus getStatus() const;
    void setStatus(const calibrationStatus v);
    long getObjectOrder() const;
    void setObjectOrder(const long v);
    tlinsAstroCalibrationItem& operator=(const tlinsAstroCalibrationItem& v);

    tlinsAstroCalibrationItem();
    tlinsAstroCalibrationItem(const tlinsAstroCatalogItem& v);
    tlinsAstroCalibrationItem(const tlinsAstroCalibrationItem& v);
    virtual ~tlinsAstroCalibrationItem();
};

}

#endif // TLINSASTROCALIBRATIONITEM_H
