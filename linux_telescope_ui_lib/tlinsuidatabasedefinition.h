#ifndef TLINSDUIDATABASEDEFINITION_H
#define TLINSDUIDATABASEDEFINITION_H

#include "tlinsastrocalibrationitem.h"
#include "tlinsastrocatalogcollection.h"
#include "tlinsastrocatalogitem.h"
#include "tlinsastroenginestate.h"
#include "tlinsiers.h"
#include "tlinskeyssortcut.h"
#include "tlinsplace.h"
#include "tlinsuiconfgiurationitem.h"
#include "tlinsuidatabase.h"
#include "tlinsuiexception.h"
#include <tlinsastrobaseutils.h>
#include <vector>

namespace TlinsAstroBase {

class tlinsUIDatabaseDefinition {
private:
    tlinsUIDatabase& db;

public:
    //
    // Zarzadanie skrotami pilota
    //
    void updateShortcuts(const std::vector<TlinsAstroBase::tlinsKeysSortcut>& data);
    void insertShortcuts(const std::vector<TlinsAstroBase::tlinsKeysSortcut>& data);
    void deleteShortcuts(const std::vector<std::string>& data);
    void selectShortcuts(std::vector<TlinsAstroBase::tlinsKeysSortcut>& data);
    void selectShortcuts(std::vector<TlinsAstroBase::tlinsKeysSortcut>& data,
        const tlinsKeysSortcutType type,
        const tlinsKeysSortcutSubType subType = tlinsKeysSortcutSubType::ANY);
    void clearShortcuts();

    //
    // Zarzadanie stanem kalibracji
    //
    void replaceAstroCalibrationObjects(const std::vector<tlinsAstroCalibrationItem>& objects);
    void insertAstroCalibrationObjects(const std::vector<tlinsAstroCalibrationItem>& objects);
    void deleteAstroCalibrationObjects(const std::vector<tlinsAstroCalibrationItem>& objects);
    void selectAstroCalibrationObjects(std::vector<tlinsAstroCalibrationItem>& objects);

    //
    // Zarzadzanie statusem kontrolera
    //
    void insertAstroEngineState(const tlinsAstroEngineState& data);
    void removeAstroEngineState(const std::string& name);
    void selectAstroEngineStates(std::vector<tlinsAstroEngineState>& outData);
    void updateAstroEngineStates(const std::vector<tlinsAstroEngineState>& outData);
    void clearAstroEngineStates();

    //
    // Operacje na bazie obiektow astronomicznych
    //
    void insertAstroObjects(const std::vector<tlinsAstroCatalogItem>& objects);
    void updateAstroObjects(const std::vector<tlinsAstroCatalogItem>& objects);
    void removeAstroObjects(const std::vector<std::pair<std::string, std::string>>& objects);
    void selectAstroObjects(const std::string& condition,
        const long offset,
        const long windowSize,
        tlinsAstroCatalogCollection& output);
    int countAstroObjects(const std::string& condition);

    //
    // Operacje na bazie danych miejsc obserwacji
    //
    void insertPlaces(const std::vector<tlinsPlace>& data);
    void deletePlaces(const std::vector<tlinsPlace>& data);
    void updatePlaces(const std::vector<tlinsPlace>& data);
    void selectAllPlaces(std::vector<tlinsPlace>& data);
    bool selectDefaultPlace(tlinsPlace& data);
    void selectByNamePlace(const std::string& name, tlinsPlace& data);
    void clearPlaces();

    //
    // Operacje na bazie danych IERS
    //
    void insertIERS(const std::vector<tlinsIERS>& data);
    void deleteIERS(const std::vector<tlinsIERS>& data);
    void updateIERS(const std::vector<tlinsIERS>& data);
    void selectIERS(std::vector<tlinsIERS>& data);
    bool selectIERS(int year, int month, int day, tlinsIERS& data);
    void clearIERS();

    //
    // Operacje na konfiguracji
    //
    void insertConfigurationItem(const tlinsUiConfgiurationItem& cfgItems);
    void updateConfigurationItem(const tlinsUiConfgiurationItem& cfgItems);
    void selectConfigurationItem(const std::string& group,
        const std::string& parameter,
        tlinsUiConfgiurationItem& output);

    //
    // Operacje na obiektach referencyjnych
    //
    void insertReferenceObjectes(const tlinsUiConfgiurationItem& cfgItems);
    void selectReferenceObjectes(const tlinsUiConfgiurationItem& cfgItems);
    void deleteReferenceObjectes(const tlinsUiConfgiurationItem& cfgItems);
    void updateReferenceObjectes(const tlinsUiConfgiurationItem& cfgItems);

    // Tworzenie bazy danych
    void createDatabae();

public:
    tlinsUIDatabaseDefinition(tlinsUIDatabase& db);
    virtual ~tlinsUIDatabaseDefinition();
};

}
#endif // TLINSDUIDATABASEDEFINITION_H
