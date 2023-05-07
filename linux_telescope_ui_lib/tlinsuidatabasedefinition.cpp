#include "tlinsuidatabasedefinition.h"
#include <stdio.h>

namespace TlinsAstroBase {

tlinsUIDatabaseDefinition::tlinsUIDatabaseDefinition(tlinsUIDatabase& db_)
    : db(db_)
{
}

tlinsUIDatabaseDefinition::~tlinsUIDatabaseDefinition()
{
}

//
// ----
//
void tlinsUIDatabaseDefinition::updateShortcuts(const std::vector<TlinsAstroBase::tlinsKeysSortcut>& data)
{
    std::vector<std::string> toRemove;

    for (auto& iter : data)
        toRemove.push_back(iter.getShortcutName());

    deleteShortcuts(toRemove);
    insertShortcuts(data);
}

void tlinsUIDatabaseDefinition::insertShortcuts(const std::vector<TlinsAstroBase::tlinsKeysSortcut>& data)
{
    std::string sql = "INSERT OR REPLACE INTO KEYS_SHORTCUT "
                      "( name,                              "
                      "  type,                              "
                      "  subType,                           "
                      "  defaultHandler,                    "
                      "  actionName,                        "
                      "  actionKeys,                        "
                      "  actionSettings,                    "
                      "  actionMode )                       "
                      "VALUES                               "
                      "( :name,                             "
                      "  :type,                             "
                      "  :subType,                          "
                      "  :defaultHandler,                   "
                      "  :actionName,                       "
                      "  :actionKeys,                       "
                      "  :actionSettings,                   "
                      "  :actionMode );                     ";

    std::shared_ptr<tlinsUIDatabase::Query> query = db.createQuery();

    query->prepere(sql);
    db.startTransaction();

    try {
        for (auto& iter : data) {
            query->bindValue(std::string(":name"), iter.getShortcutName());
            query->bindValue(std::string(":type"), static_cast<int>(iter.getType()));
            query->bindValue(std::string(":subType"), static_cast<int>(iter.getSubType()));
            query->bindValue(std::string(":actionName"), iter.getActionName());
            query->bindValue(std::string(":defaultHandler"), static_cast<int>(iter.getDefaultHandler()));
            query->bindValue(std::string(":actionKeys"), iter.getActionKeys());
            query->bindValue(std::string(":actionSettings"), iter.getActionSettingsJson());
            query->bindValue(std::string(":actionMode"), static_cast<int>(iter.getActionMode()));
            query->execute();
        }
    } catch (...) {
        db.rollbackTransaction();
        throw;
    }
    db.commitTransaction();
}

void tlinsUIDatabaseDefinition::deleteShortcuts(const std::vector<std::string>& data)
{
    std::string sql = "DELETE FROM KEYS_SHORTCUT "
                      "WHERE name = :name;       ";

    db.startTransaction();
    try {
        for (auto& iter : data) {
            std::shared_ptr<tlinsUIDatabase::Query> query = db.createQuery();
            query->prepere(sql);

            query->bindValue(std::string(":name"), iter);
            query->execute();
        }
    } catch (...) {
        db.rollbackTransaction();
        throw;
    }
    db.commitTransaction();
}

void tlinsUIDatabaseDefinition::clearShortcuts()
{
    std::string sql = "DELETE FROM KEYS_SHORTCUT;  ";

    std::shared_ptr<tlinsUIDatabase::Query> query = db.createQuery();

    query->prepere(sql);
    db.startTransaction();

    try {
        query->execute();
    } catch (...) {
        db.rollbackTransaction();
        throw;
    }
    db.commitTransaction();
}

void tlinsUIDatabaseDefinition::selectShortcuts(std::vector<TlinsAstroBase::tlinsKeysSortcut>& data)
{
    std::string sql = "SELECT name,           "
                      "       type,           "
                      "       subType,        "
                      "       defaultHandler, "
                      "       actionName,     "
                      "       actionKeys,     "
                      "       actionSettings, "
                      "       actionMode      "
                      "FROM   KEYS_SHORTCUT;  ";

    std::shared_ptr<tlinsUIDatabase::Query> query = db.createQuery();

    query->prepere(sql);
    query->execute();

    while (query->next()) {
        bool isNULL;
        std::string name;
        std::string actionName;
        std::string actionKeys;
        std::string actionSettings;
        int type;
        int subType;
        int defaultHandler;
        int actionMode;

        query->readValue(std::string("name"), name, isNULL);
        query->readValue(std::string("type"), type, isNULL);
        query->readValue(std::string("subType"), subType, isNULL);
        query->readValue(std::string("defaultHandler"), defaultHandler, isNULL);
        query->readValue(std::string("actionName"), actionName, isNULL);
        query->readValue(std::string("actionKeys"), actionKeys, isNULL);
        query->readValue(std::string("actionSettings"), actionSettings, isNULL);
        query->readValue(std::string("actionMode"), actionMode, isNULL);

        TlinsAstroBase::tlinsKeysSortcut item;
        item.setAhortcutName(name);
        item.setActionName(actionName);
        item.setActionKeys(actionKeys);
        item.setActionSettingsJson(actionSettings);
        item.setType(static_cast<tlinsKeysSortcutType>(type));
        item.setSubType(static_cast<tlinsKeysSortcutSubType>(subType));
        item.setDefaultHandler(static_cast<tlinsDefaultHandler>(defaultHandler));

        switch (actionMode) {
        case 1:
            item.setActionMode(TlinsAstroBase::tlinsPilotShortcutsDefinitionValidMode::DEVICE);
            break;

        case 2:
            item.setActionMode(TlinsAstroBase::tlinsPilotShortcutsDefinitionValidMode::ASTRO);
            break;

        case 3:
            item.setActionMode(TlinsAstroBase::tlinsPilotShortcutsDefinitionValidMode::BOTH);
            break;
        }
        data.push_back(item);
    }
}

void tlinsUIDatabaseDefinition::selectShortcuts(std::vector<TlinsAstroBase::tlinsKeysSortcut>& data,
    const tlinsKeysSortcutType type,
    const tlinsKeysSortcutSubType subType)
{
    std::string sql1 = "SELECT name,                   "
                       "       type,                   "
                       "       subType,                "
                       "       defaultHandler,         "
                       "       actionName,             "
                       "       actionKeys,             "
                       "       actionSettings,         "
                       "       actionMode              "
                       "FROM   KEYS_SHORTCUT           "
                       "WHERE  type = :type            "
                       "       AND subType = :subType; ";

    std::string sql2 = "SELECT name,                   "
                       "       type,                   "
                       "       subType,                "
                       "       defaultHandler,         "
                       "       actionName,             "
                       "       actionKeys,             "
                       "       actionSettings,         "
                       "       actionMode              "
                       "FROM   KEYS_SHORTCUT           "
                       "WHERE  type = :type;           ";

    std::string sql = sql1;
    if (subType == tlinsKeysSortcutSubType::ANY)
        sql = sql2;

    // Create query
    std::shared_ptr<tlinsUIDatabase::Query> query = db.createQuery();
    query->prepere(sql);

    // Bindowanie parameterow
    query->bindValue(std::string(":type"), static_cast<int>(type));
    if (subType != tlinsKeysSortcutSubType::ANY)
        query->bindValue(std::string(":subType"), static_cast<int>(subType));

    query->execute();

    while (query->next()) {
        bool isNULL;
        std::string name;
        std::string actionName;
        std::string actionKeys;
        std::string actionSettings;
        int type;
        int subType;
        int actionMode;
        int defaultHandler;

        query->readValue(std::string("name"), name, isNULL);
        query->readValue(std::string("type"), type, isNULL);
        query->readValue(std::string("subType"), subType, isNULL);
        query->readValue(std::string("defaultHandler"), defaultHandler, isNULL);
        query->readValue(std::string("actionName"), actionName, isNULL);
        query->readValue(std::string("actionKeys"), actionKeys, isNULL);
        query->readValue(std::string("actionSettings"), actionSettings, isNULL);
        query->readValue(std::string("actionMode"), actionMode, isNULL);

        TlinsAstroBase::tlinsKeysSortcut item;
        item.setAhortcutName(name);
        item.setActionName(actionName);
        item.setActionKeys(actionKeys);
        item.setActionSettingsJson(actionSettings);
        item.setType(static_cast<tlinsKeysSortcutType>(type));
        item.setSubType(static_cast<tlinsKeysSortcutSubType>(subType));
        item.setDefaultHandler(static_cast<tlinsDefaultHandler>(defaultHandler));

        switch (actionMode) {
        case 1:
            item.setActionMode(TlinsAstroBase::tlinsPilotShortcutsDefinitionValidMode::DEVICE);
            break;

        case 2:
            item.setActionMode(TlinsAstroBase::tlinsPilotShortcutsDefinitionValidMode::ASTRO);
            break;

        case 3:
            item.setActionMode(TlinsAstroBase::tlinsPilotShortcutsDefinitionValidMode::BOTH);
            break;
        }
        data.push_back(item);
    }
}

//
// ----
//
void tlinsUIDatabaseDefinition::insertAstroEngineState(const tlinsAstroEngineState& data)
{
    std::string sql = "INSERT OR REPLACE INTO ASTRO_ENGINE_STATE        "
                      "( name,                                          "
                      "  ra, dc,                                        "
                      "  pm_ra, pm_dc, radial_velocity, parallex,       "
                      "  catalog_type,                                  "
                      "  a11, a12, a13,                                 "
                      "  a21, a22, a23,                                 "
                      "  a31, a32, a33,                                 "
                      "  deviceX, deviceY,                              "
                      "  deviceXEncoder, deviceYEncoder,                "
                      "  mode, state,                                   "
                      "  x_reverse, y_reverse)                          "
                      "VALUES                                           "
                      "( :name,                                         "
                      "  :ra, :dc,                                      "
                      "  :pm_ra, :pm_dc, :radial_velocity, :parallex,   "
                      "  :catalog_type,                                 "
                      "  :a11, :a12, :a13,                              "
                      "  :a21, :a22, :a23,                              "
                      "  :a31, :a32, :a33,                              "
                      "  :deviceX, :deviceY,                            "
                      "  :deviceXEncoder, :deviceYEncoder,              "
                      "  :mode, :state,                                 "
                      "  :x_reverse, :y_reverse );                      ";

    std::shared_ptr<tlinsUIDatabase::Query> query = db.createQuery();

    query->prepere(sql);
    db.startTransaction();

    try {
        query->bindValue(std::string(":name"), data.getName());
        query->bindValue(std::string(":ra"), data.getRA());
        query->bindValue(std::string(":dc"), data.getDC());
        query->bindValue(std::string(":pm_ra"), data.getPmRA());
        query->bindValue(std::string(":pm_dc"), data.getPmDC());
        query->bindValue(std::string(":radial_velocity"), data.getRadialVelocity());
        query->bindValue(std::string(":parallex"), data.getParallex());
        query->bindValue(std::string(":catalog_type"), data.getCatalogType());
        query->bindValue(std::string(":a11"), data.getA11());
        query->bindValue(std::string(":a12"), data.getA12());
        query->bindValue(std::string(":a13"), data.getA13());
        query->bindValue(std::string(":a21"), data.getA21());
        query->bindValue(std::string(":a22"), data.getA22());
        query->bindValue(std::string(":a23"), data.getA23());
        query->bindValue(std::string(":a31"), data.getA31());
        query->bindValue(std::string(":a32"), data.getA32());
        query->bindValue(std::string(":a33"), data.getA33());
        query->bindValue(std::string(":deviceX"), static_cast<long long>(data.getDeviceX()));
        query->bindValue(std::string(":deviceY"), static_cast<long long>(data.getDeviceY()));
        query->bindValue(std::string(":deviceXEncoder"), static_cast<long long>(data.getDeviceXEncoder()));
        query->bindValue(std::string(":deviceYEncoder"), static_cast<long long>(data.getDeviceYEncoder()));
        query->bindValue(std::string(":mode"), static_cast<long long>(data.getMode()));
        query->bindValue(std::string(":state"), static_cast<long long>(data.getState()));

        if (data.getXReverse()) {
            query->bindValue(std::string(":x_reverse"), "true");
        } else {
            query->bindValue(std::string(":x_reverse"), "false");
        }
        if (data.getYReverse()) {
            query->bindValue(std::string(":y_reverse"), "true");
        } else {
            query->bindValue(std::string(":y_reverse"), "false");
        }

        query->execute();
    } catch (...) {
        db.rollbackTransaction();
        throw;
    }

    db.commitTransaction();
}

void tlinsUIDatabaseDefinition::updateAstroEngineStates(const std::vector<tlinsAstroEngineState>& objects)
{
    std::string sql = "INSERT OR REPLACE INTO ASTRO_ENGINE_STATE        "
                      "( name,                                          "
                      "  ra, dc,                                        "
                      "  pm_ra, pm_dc, radial_velocity, parallex,       "
                      "  catalog_type,                                  "
                      "  a11, a12, a13,                                 "
                      "  a21, a22, a23,                                 "
                      "  a31, a32, a33,                                 "
                      "  deviceX, deviceY,                              "
                      "  deviceXEncoder, deviceYEncoder,                "
                      "  mode, state,                                   "
                      "  x_reverse, y_reverse )                          "
                      "VALUES                                           "
                      "( :name,                                         "
                      "  :ra, :dc,                                      "
                      "  :pm_ra, :pm_dc, :radial_velocity, :parallex,   "
                      "  :catalog_type,                                 "
                      "  :a11, :a12, :a13,                              "
                      "  :a21, :a22, :a23,                              "
                      "  :a31, :a32, :a33,                              "
                      "  :deviceX, :deviceY,                            "
                      "  :deviceXEncoder, :deviceYEncoder,              "
                      "  :mode, :state,                                 "
                      "  :x_reverse, :y_revers );                       ";

    std::string sqlDelete = "DELETE FROM ASTRO_ENGINE_STATE;";

    db.startTransaction();

    try {
        std::shared_ptr<tlinsUIDatabase::Query> queryDel = db.createQuery();
        queryDel->prepere(sqlDelete);
        queryDel->execute();

        for (auto& data : objects) {
            std::shared_ptr<tlinsUIDatabase::Query> query = db.createQuery();
            query->prepere(sql);

            query->bindValue(std::string(":name"), data.getName());
            query->bindValue(std::string(":ra"), data.getRA());
            query->bindValue(std::string(":dc"), data.getDC());
            query->bindValue(std::string(":pm_ra"), data.getPmRA());
            query->bindValue(std::string(":pm_dc"), data.getPmDC());
            query->bindValue(std::string(":radial_velocity"), data.getRadialVelocity());
            query->bindValue(std::string(":parallex"), data.getParallex());
            query->bindValue(std::string(":catalog_type"), data.getCatalogType());
            query->bindValue(std::string(":a11"), data.getA11());
            query->bindValue(std::string(":a12"), data.getA12());
            query->bindValue(std::string(":a13"), data.getA13());
            query->bindValue(std::string(":a21"), data.getA21());
            query->bindValue(std::string(":a22"), data.getA22());
            query->bindValue(std::string(":a23"), data.getA23());
            query->bindValue(std::string(":a31"), data.getA31());
            query->bindValue(std::string(":a32"), data.getA32());
            query->bindValue(std::string(":a33"), data.getA33());
            query->bindValue(std::string(":deviceX"), static_cast<long long>(data.getDeviceX()));
            query->bindValue(std::string(":deviceY"), static_cast<long long>(data.getDeviceY()));
            query->bindValue(std::string(":deviceXEncoder"), static_cast<long long>(data.getDeviceXEncoder()));
            query->bindValue(std::string(":deviceYEncoder"), static_cast<long long>(data.getDeviceYEncoder()));
            query->bindValue(std::string(":mode"), static_cast<long long>(data.getMode()));
            query->bindValue(std::string(":state"), static_cast<long long>(data.getState()));

            if (data.getXReverse()) {
                query->bindValue(std::string(":x_reverse"), "true");
            } else {
                query->bindValue(std::string(":x_reverse"), "false");
            }
            if (data.getYReverse()) {
                query->bindValue(std::string(":y_reverse"), "true");
            } else {
                query->bindValue(std::string(":y_reverse"), "false");
            }

            query->execute();
        }
    } catch (...) {
        db.rollbackTransaction();
        throw;
    }

    db.commitTransaction();
}

void tlinsUIDatabaseDefinition::removeAstroEngineState(const std::string& name)
{
    std::string sql = "DELETE FROM ASTRO_ENGINE_STATE "
                      "WHERE name = :name;            ";

    std::shared_ptr<tlinsUIDatabase::Query> query = db.createQuery();

    query->prepere(sql);
    db.startTransaction();

    try {
        query->bindValue(std::string(":name"), name);
        query->execute();
    } catch (...) {
        db.rollbackTransaction();
        throw;
    }

    db.commitTransaction();
}

void tlinsUIDatabaseDefinition::clearAstroEngineStates()
{
    std::string sql = "DELETE FROM ASTRO_ENGINE_STATE; ";
    std::shared_ptr<tlinsUIDatabase::Query> query = db.createQuery();

    query->prepere(sql);
    db.startTransaction();

    try {
        query->execute();
    } catch (...) {
        db.rollbackTransaction();
        throw;
    }

    db.commitTransaction();
}

void tlinsUIDatabaseDefinition::selectAstroEngineStates(std::vector<tlinsAstroEngineState>& outData)
{
    std::string sql = "SELECT name,              "
                      "       ra,                "
                      "       dc,                "
                      "       pm_ra,             "
                      "       pm_dc,             "
                      "       radial_velocity,   "
                      "       parallex,          "
                      "       catalog_type,      "
                      "       a11,               "
                      "       a12,               "
                      "       a13,               "
                      "       a21,               "
                      "       a22,               "
                      "       a23,               "
                      "       a31,               "
                      "       a32,               "
                      "       a33,               "
                      "       deviceX,           "
                      "       deviceY,           "
                      "       deviceXEncoder,    "
                      "       deviceYEncoder,    "
                      "       mode,              "
                      "       state,             "
                      "       x_reverse,         "
                      "       y_reverse          "
                      "FROM   ASTRO_ENGINE_STATE "
                      "ORDER BY name;            ";

    std::shared_ptr<tlinsUIDatabase::Query> query = db.createQuery();

    query->prepere(sql);
    query->execute();

    while (query->next()) {
        bool isNULL;
        std::string name;
        double ra;
        double dc;
        double pm_ra;
        double pm_dc;
        double radial_velocity;
        double parallex;
        std::string catalog_type;
        double a11;
        double a12;
        double a13;
        double a21;
        double a22;
        double a23;
        double a31;
        double a32;
        double a33;
        long long deviceX;
        long long deviceY;
        long long deviceXEncoder;
        long long deviceYEncoder;
        tlinsAstroEngineState::EngineMode mode;
        tlinsAstroEngineState::EngineState state;

        std::string strXReverese;
        std::string strYReverese;

        query->readValue(std::string("name"), name, isNULL);
        query->readValue(std::string("ra"), ra, isNULL);
        query->readValue(std::string("dc"), dc, isNULL);
        query->readValue(std::string("pm_ra"), pm_ra, isNULL);
        query->readValue(std::string("pm_dc"), pm_dc, isNULL);
        query->readValue(std::string("radial_velocity"), radial_velocity, isNULL);
        query->readValue(std::string("parallex"), parallex, isNULL);
        query->readValue(std::string("catalog_type"), catalog_type, isNULL);
        query->readValue(std::string("a11"), a11, isNULL);
        query->readValue(std::string("a12"), a12, isNULL);
        query->readValue(std::string("a13"), a13, isNULL);
        query->readValue(std::string("a21"), a21, isNULL);
        query->readValue(std::string("a22"), a22, isNULL);
        query->readValue(std::string("a23"), a23, isNULL);
        query->readValue(std::string("a31"), a31, isNULL);
        query->readValue(std::string("a32"), a32, isNULL);
        query->readValue(std::string("a33"), a33, isNULL);
        query->readValue(std::string("deviceX"), deviceX, isNULL);
        query->readValue(std::string("deviceY"), deviceY, isNULL);
        query->readValue(std::string("deviceXEncoder"), deviceXEncoder, isNULL);
        query->readValue(std::string("deviceYEncoder"), deviceYEncoder, isNULL);

        query->readValue(std::string("x_reverse"), strXReverese, isNULL);
        query->readValue(std::string("y_reverse"), strYReverese, isNULL);

        {
            int val;
            query->readValue(std::string("mode"), val, isNULL);
            switch (val) {
            case 0:
                mode = tlinsAstroEngineState::EngineMode::MODE_NONE;
                break;
            case 1:
                mode = tlinsAstroEngineState::EngineMode::MODE_STANDARD;
                break;
            case 2:
                mode = tlinsAstroEngineState::EngineMode::MODE_EXTERNAL_SUPPORT;
                break;
            }
        }
        {
            int val;

            query->readValue(std::string("state"), val, isNULL);
            switch (val) {
            case 0:
                state = tlinsAstroEngineState::EngineState::STATE_CALIBRATION;
                break;
            case 1:
                state = tlinsAstroEngineState::EngineState::STATE_CALIBRATION_VELOCITY;
                break;
            case 2:
                state = tlinsAstroEngineState::EngineState::STATE_REGULAR;
                break;
            }
        }

        tlinsAstroEngineState item;
        item.setName(name);
        item.setRA(ra);
        item.setDC(dc);
        item.setPmRA(pm_ra);
        item.setPmDC(pm_dc);
        item.setRadialVelocity(radial_velocity);
        item.setParallex(parallex);
        item.setCatalogType(catalog_type);
        item.setA11(a11);
        item.setA12(a12);
        item.setA13(a13);
        item.setA21(a21);
        item.setA22(a22);
        item.setA23(a23);
        item.setA31(a31);
        item.setA32(a32);
        item.setA33(a33);
        item.setDeviceX(deviceX);
        item.setDeviceY(deviceY);
        item.setDeviceXEncoder(deviceXEncoder);
        item.setDeviceYEncoder(deviceYEncoder);
        item.setMode(mode);
        item.setState(state);

        item.setXReverse(strXReverese == "true");
        item.setYReverse(strYReverese == "true");

        outData.push_back(item);
    }
}

//
// ----
//
void tlinsUIDatabaseDefinition::replaceAstroCalibrationObjects(const std::vector<tlinsAstroCalibrationItem>& objects)
{
    std::string sql1 = "DELETE FROM astro_calibration_objects; ";
    std::string sql2 = "INSERT INTO astro_calibration_objects                 "
                       "( catalog_type, object_id_in_catalog, object_order    "
                       ")                                                     "
                       "VALUES                                                "
                       "( :catalog_type, :object_id_in_catalog, :object_order "
                       ");                                                    ";

    std::shared_ptr<tlinsUIDatabase::Query> query1 = db.createQuery();
    query1->prepere(sql1);

    std::shared_ptr<tlinsUIDatabase::Query> query2 = db.createQuery();
    query2->prepere(sql2);

    db.startTransaction();

    // Delete old records
    try {
        // Wstawienie danych
        query1->execute();
    } catch (...) {
        db.rollbackTransaction();
        throw;
    }

    // Insert new records
    for (auto iter = objects.begin(); iter != objects.end(); iter++) {
        try {
            query2->bindValue(std::string(":catalog_type"), iter->getCatalogType().label);
            query2->bindValue(std::string(":object_id_in_catalog"), iter->getObjectIdInCatalog());
            query2->bindValue(std::string(":object_order"), static_cast<long long>(iter->getObjectOrder()));

            // Wstawienie danych
            query2->execute();
        } catch (...) {
            db.rollbackTransaction();
            throw;
        }
    }

    db.commitTransaction();
}

void tlinsUIDatabaseDefinition::insertAstroCalibrationObjects(const std::vector<tlinsAstroCalibrationItem>& objects)
{
    std::string sql = "INSERT INTO astro_calibration_objects                 "
                      "( catalog_type, object_id_in_catalog, object_order    "
                      ")                                                     "
                      "VALUES                                                "
                      "( :catalog_type, :object_id_in_catalog, :object_order "
                      ");                                                    ";

    std::shared_ptr<tlinsUIDatabase::Query> query = db.createQuery();
    query->prepere(sql);

    db.startTransaction();
    for (auto iter = objects.begin(); iter != objects.end(); iter++) {
        try {
            query->bindValue(std::string(":catalog_type"), iter->getCatalogType().label);
            query->bindValue(std::string(":object_id_in_catalog"), iter->getObjectIdInCatalog());
            query->bindValue(std::string(":object_order"), static_cast<long long>(iter->getObjectOrder()));

            // Wstawienie danych
            query->execute();
        } catch (...) {
            db.rollbackTransaction();
            throw;
        }
    }
    db.commitTransaction();
}

void tlinsUIDatabaseDefinition::deleteAstroCalibrationObjects(const std::vector<tlinsAstroCalibrationItem>& objects)
{
    std::string sql = "DELETE FROM astro_calibration_objects                   "
                      " WHERE                                                  "
                      "         catalog_type         = :catalog_type           "
                      "     AND object_id_in_catalog = :object_id_in_catalog ; ";

    std::shared_ptr<tlinsUIDatabase::Query> query = db.createQuery();
    query->prepere(sql);

    db.startTransaction();
    for (auto iter = objects.begin(); iter != objects.end(); iter++) {
        try {
            query->bindValue(std::string(":catalog_type"), iter->getCatalogType().label);
            query->bindValue(std::string(":object_id_in_catalog"), iter->getObjectIdInCatalog());
            query->execute();
        } catch (...) {
            db.rollbackTransaction();
            throw;
        }
    }
    db.commitTransaction();
}

void tlinsUIDatabaseDefinition::selectAstroCalibrationObjects(std::vector<tlinsAstroCalibrationItem>& cobjects)
{
    std::string sql = " SELECT astro_objects.catalog_type,                                                                                                  "
                      "        astro_objects.object_id_in_catalog,                                                                                          "
                      "        astro_objects.object_description,                                                                                            "
                      "        astro_objects.name,                                                                                                          "
                      "        astro_objects.description,                                                                                                   "
                      "        astro_objects.type,                                                                                                          "
                      "        astro_objects.type_details_1,                                                                                                "
                      "        astro_objects.type_details_2,                                                                                                "
                      "        astro_objects.type_details_3,                                                                                                "
                      "        astro_objects.constelation,                                                                                                  "
                      "        astro_objects.ra,                                                                                                            "
                      "        astro_objects.dc,                                                                                                            "
                      "        astro_objects.pm_ra,                                                                                                         "
                      "        astro_objects.pm_dc,                                                                                                         "
                      "        astro_objects.ep_ra,                                                                                                         "
                      "        astro_objects.ep_dc,                                                                                                         "
                      "        astro_objects.min_err_ra,                                                                                                    "
                      "        astro_objects.min_err_dc,                                                                                                    "
                      "        astro_objects.err_mean_ra,                                                                                                   "
                      "        astro_objects.err_mean_dc,                                                                                                   "
                      "        astro_objects.err_mean_pm_ra,                                                                                                "
                      "        astro_objects.err_mean_pm_dc,                                                                                                "
                      "        astro_objects.magnitude,                                                                                                     "
                      "        astro_objects.err_magnitude,                                                                                                 "
                      "        astro_calibration_objects.object_order,                                                                                      "
                      "        astro_objects.radial_velocity,                                                                                               "
                      "        astro_objects.parallex                                                                                                       "
                      " FROM  astro_objects                                                                                                                 "
                      " INNER JOIN astro_calibration_objects ON (     astro_objects.catalog_type         = astro_calibration_objects.catalog_type           "
                      "                                           AND astro_objects.object_id_in_catalog = astro_calibration_objects.object_id_in_catalog ) "
                      " ORDER BY astro_calibration_objects.object_order;                                                                                    ";

    std::shared_ptr<tlinsUIDatabase::Query> query = db.createQuery();

    query->prepere(sql);
    query->execute();

    while (query->next()) {
        bool isNULL;
        long long objectOrder;
        std::string name;
        std::string description;
        std::string type;
        std::string typeDetails1;
        std::string typeDetails2;
        std::string typeDetails3;
        std::string constelation;
        double RA;
        double DC;
        double pmRA;
        double pmDC;
        double epRA;
        double epDC;
        double minErrRa;
        double minErrDc;
        double errMeanRA;
        double errMeanDC;
        double errMeanPmRA;
        double errMeanPmDC;
        double magnitude;
        double radialVelocity;
        double parallex;
        double errMagnitude;
        std::string catalogType;
        std::string objectIdInCatalog;
        std::string objectDescription;

        query->readValue(std::string("object_order"), objectOrder, isNULL);
        query->readValue(std::string("catalog_type"), catalogType, isNULL);
        query->readValue(std::string("object_id_in_catalog"), objectIdInCatalog, isNULL);
        query->readValue(std::string("object_description"), objectDescription, isNULL);
        query->readValue(std::string("name"), name, isNULL);
        query->readValue(std::string("description"), description, isNULL);
        query->readValue(std::string("type"), type, isNULL);
        query->readValue(std::string("type_details_1"), typeDetails1, isNULL);
        query->readValue(std::string("type_details_2"), typeDetails2, isNULL);
        query->readValue(std::string("type_details_3"), typeDetails3, isNULL);
        query->readValue(std::string("constelation"), constelation, isNULL);
        query->readValue(std::string("ra"), RA, isNULL);
        query->readValue(std::string("dc"), DC, isNULL);
        query->readValue(std::string("pm_ra"), pmRA, isNULL);
        query->readValue(std::string("pm_dc"), pmDC, isNULL);
        query->readValue(std::string("ep_ra"), epRA, isNULL);
        query->readValue(std::string("ep_dc"), epDC, isNULL);
        query->readValue(std::string("min_err_ra"), minErrRa, isNULL);
        query->readValue(std::string("min_err_dc"), minErrDc, isNULL);
        query->readValue(std::string("err_mean_ra"), errMeanRA, isNULL);
        query->readValue(std::string("err_mean_dc"), errMeanDC, isNULL);
        query->readValue(std::string("err_mean_pm_ra"), errMeanPmRA, isNULL);
        query->readValue(std::string("err_mean_pm_dc"), errMeanPmDC, isNULL);
        query->readValue(std::string("magnitude"), magnitude, isNULL);
        query->readValue(std::string("err_magnitude"), errMagnitude, isNULL);
        query->readValue(std::string("radial_velocity"), radialVelocity, isNULL);
        query->readValue(std::string("parallex"), parallex, isNULL);

        tlinsAstroCalibrationItem item;

        item.setName(name);
        item.setDescription(description);
        {
            TlinsAstroBase::ObjectType::ObjectTypeInfo typeInfo;
            if (TlinsAstroBase::ObjectType::get(type, typeInfo))
                item.setType(typeInfo);
        }

        item.setTypeDetails1(typeDetails1);
        item.setTypeDetails2(typeDetails2);
        item.setTypeDetails3(typeDetails3);
        {
            TlinsAstroBase::Constelations::ConstelationInfo constelationInfo;
            if (TlinsAstroBase::Constelations::get(constelation, constelationInfo))
                item.setConstelation(constelationInfo);
        }
        item.setRA(RA);
        item.setDC(DC);
        item.setPmRA(pmRA);
        item.setPmDC(pmDC);
        item.setEpRA(epRA);
        item.setEpDC(epDC);
        item.setMinErrRA(minErrRa);
        item.setMinErrDC(minErrDc);
        item.setErrMeanRA(errMeanRA);
        item.setErrMeanDC(errMeanDC);
        item.setErrMeanPmRA(errMeanPmRA);
        item.setErrMeanPmDC(errMeanPmDC);
        item.setMagnitude(magnitude);
        item.setErrMagnitude(errMagnitude);
        {
            TlinsAstroBase::CatalogType::CatalogTypeInfo catalogTypeInfo;
            if (TlinsAstroBase::CatalogType::get(catalogType, catalogTypeInfo))
                item.setCatalogType(catalogTypeInfo);
        }
        item.setObjectIdInCatalog(objectIdInCatalog);
        item.setObjectDescription(objectDescription);

        item.setObjectIdInCatalog(objectIdInCatalog);
        item.setObjectOrder(static_cast<long>(objectOrder));
        item.setRadialVelocity(radialVelocity);
        item.setParallex(parallex);

        cobjects.push_back(item);
    }
}

//
// ----
//

// Operacje na bazie obiektow astronomicznych
void tlinsUIDatabaseDefinition::insertAstroObjects(const std::vector<tlinsAstroCatalogItem>& objects)
{
    std::string sql = "INSERT INTO astro_objects                                                                                                                                                                      "
                      "( catalog_type, object_id_in_catalog, object_description, name, description,                                                                                                                   "
                      "  type, type_details_1, type_details_2, type_details_3, constelation,                                                                                                                          "
                      "  ra, dc, pm_ra, pm_dc, ep_ra, ep_dc, min_err_ra, min_err_dc, err_mean_ra, err_mean_dc, err_mean_pm_ra, err_mean_pm_dc, magnitude, err_magnitude, radial_velocity, parallex )                  "
                      "VALUES                                                                                                                                                                                         "
                      "( :catalog_type, :object_id_in_catalog, :object_description, :name, :description,                                                                                                              "
                      "  :type, :type_details_1, :type_details_2, :type_details_3, :constelation,                                                                                                                     "
                      "  :ra, :dc, :pm_ra, :pm_dc, :ep_ra, :ep_dc, :min_err_ra, :min_err_dc, :err_mean_ra, :err_mean_dc, :err_mean_pm_ra, :err_mean_pm_dc, :magnitude, :err_magnitude, :radial_velocity, :parallex ); ";

    std::shared_ptr<tlinsUIDatabase::Query> query = db.createQuery();
    query->prepere(sql);

    db.startTransaction();
    for (auto iter = objects.begin(); iter != objects.end(); iter++) {
        try {
            query->bindValue(std::string(":catalog_type"), iter->getCatalogType().label);
            query->bindValue(std::string(":object_id_in_catalog"), iter->getObjectIdInCatalog());
            query->bindValue(std::string(":object_description"), iter->getObjectDescription());
            query->bindValue(std::string(":name"), iter->getName());
            query->bindValue(std::string(":description"), iter->getDescription());

            query->bindValue(std::string(":type"), iter->getType().label);
            query->bindValue(std::string(":type_details_1"), iter->getTypeDetails1());
            query->bindValue(std::string(":type_details_2"), iter->getTypeDetails2());
            query->bindValue(std::string(":type_details_3"), iter->getTypeDetails3());

            query->bindValue(std::string(":constelation"), iter->getConstelation().label);

            query->bindValue(std::string(":ra"), iter->getRA());
            query->bindValue(std::string(":dc"), iter->getDC());
            query->bindValue(std::string(":pm_ra"), iter->getPmRA());
            query->bindValue(std::string(":pm_dc"), iter->getPmDC());
            query->bindValue(std::string(":ep_ra"), iter->getEpRA());
            query->bindValue(std::string(":ep_dc"), iter->getEpDC());

            query->bindValue(std::string(":min_err_ra"), iter->getMinErrRA());
            query->bindValue(std::string(":min_err_dc"), iter->getMinErrDC());

            query->bindValue(std::string(":err_mean_ra"), iter->getErrMeanRA());
            query->bindValue(std::string(":err_mean_dc"), iter->getErrMeanDC());

            query->bindValue(std::string(":err_mean_pm_ra"), iter->getErrMeanPmRA());
            query->bindValue(std::string(":err_mean_pm_dc"), iter->getErrMeanPmDC());

            query->bindValue(std::string(":magnitude"), iter->getMagnitude());
            query->bindValue(std::string(":err_magnitude"), iter->getErrMagnitude());

            query->bindValue(std::string(":radial_velocity"), iter->getRadialVelocity());
            query->bindValue(std::string(":parallex"), iter->getParallex());

            // Wstawienie danych
            query->execute();
        } catch (...) {
            db.rollbackTransaction();
            throw;
        }
    }
    db.commitTransaction();
}

void tlinsUIDatabaseDefinition::updateAstroObjects(const std::vector<tlinsAstroCatalogItem>& objects)
{
    std::string sql = "UPDATE astro_objects                                    "
                      "SET object_description = :object_description,           "
                      "    name               = :name,                         "
                      "    description        = :description,                  "
                      "    type               = :type,                         "
                      "    type_details_1     = :type_details_1,               "
                      "    type_details_2     = :type_details_2,               "
                      "    type_details_3     = :type_details_3,               "
                      "    constelation       = :constelation,                 "
                      "    ra                 = :ra,                           "
                      "    dc                 = :dc,                           "
                      "    pm_ra              = :pm_ra,                        "
                      "    pm_dc              = :pm_dc,                        "
                      "    ep_ra              = :ep_ra,                        "
                      "    ep_dc              = :ep_dc,                        "
                      "    min_err_ra         = :min_err_ra,                   "
                      "    min_err_dc         = :min_err_dc,                   "
                      "    err_mean_ra        = :err_mean_ra,                  "
                      "    err_mean_dc        = :err_mean_dc,                  "
                      "    err_mean_pm_ra     = :err_mean_pm_ra,               "
                      "    err_mean_pm_dc     = :err_mean_pm_dc,               "
                      "    magnitude          = :magnitude,                    "
                      "    err_magnitude      = :err_magnitude,                "
                      "    radial_velocity    = :radial_velocity,              "
                      "    parallex           = :parallex                      "
                      "WHERE                                                   "
                      "          catalog_type = :catalog_type                  "
                      "      AND object_id_in_catalog = :object_id_in_catalog; ";

    db.startTransaction();
    for (auto iter = objects.begin(); iter != objects.end(); iter++) {
        try {
            std::shared_ptr<tlinsUIDatabase::Query> query = db.createQuery();
            query->prepere(sql);

            query->bindValue(std::string(":object_description"), iter->getObjectDescription());
            query->bindValue(std::string(":name"), iter->getName());
            query->bindValue(std::string(":description"), iter->getDescription());
            query->bindValue(std::string(":type"), iter->getType().label);
            query->bindValue(std::string(":type_details_1"), iter->getTypeDetails1());
            query->bindValue(std::string(":type_details_2"), iter->getTypeDetails2());
            query->bindValue(std::string(":type_details_3"), iter->getTypeDetails3());
            query->bindValue(std::string(":constelation"), iter->getConstelation().label);
            query->bindValue(std::string(":ra"), iter->getRA());
            query->bindValue(std::string(":dc"), iter->getDC());
            query->bindValue(std::string(":pm_ra"), iter->getPmRA());
            query->bindValue(std::string(":pm_dc"), iter->getPmDC());
            query->bindValue(std::string(":ep_ra"), iter->getEpRA());
            query->bindValue(std::string(":ep_dc"), iter->getEpDC());
            query->bindValue(std::string(":min_err_ra"), iter->getMinErrRA());
            query->bindValue(std::string(":min_err_dc"), iter->getMinErrDC());
            query->bindValue(std::string(":err_mean_ra"), iter->getErrMeanRA());
            query->bindValue(std::string(":err_mean_dc"), iter->getErrMeanDC());
            query->bindValue(std::string(":err_mean_pm_ra"), iter->getErrMeanPmRA());
            query->bindValue(std::string(":err_mean_pm_dc"), iter->getErrMeanPmDC());
            query->bindValue(std::string(":magnitude"), iter->getMagnitude());
            query->bindValue(std::string(":err_magnitude"), iter->getErrMagnitude());
            query->bindValue(std::string(":catalog_type"), iter->getCatalogType().label);
            query->bindValue(std::string(":object_id_in_catalog"), iter->getObjectIdInCatalog());
            query->bindValue(std::string(":radial_velocity"), iter->getRadialVelocity());
            query->bindValue(std::string(":parallex"), iter->getParallex());

            // Modyfikacja danych
            query->execute();
        } catch (...) {
            db.rollbackTransaction();
            throw;
        }
    }
    db.commitTransaction();
}

void tlinsUIDatabaseDefinition::removeAstroObjects(const std::vector<std::pair<std::string, std::string>>& objects)
{
    std::string sql = "DELETE FROM astro_objects                               "
                      "WHERE                                                   "
                      "          catalog_type         = :catalog_type          "
                      "      AND object_id_in_catalog = :object_id_in_catalog; ";

    std::string sql2 = "DELETE FROM astro_calibration_objects                   "
                       " WHERE                                                  "
                       "         catalog_type         = :catalog_type2          "
                       "     AND object_id_in_catalog = :object_id_in_catalog2; ";

    std::shared_ptr<tlinsUIDatabase::Query> query = db.createQuery();
    std::shared_ptr<tlinsUIDatabase::Query> query2 = db.createQuery();

    query->prepere(sql);
    query2->prepere(sql2);

    db.startTransaction();
    for (auto iter = objects.begin(); iter != objects.end(); iter++) {
        try {
            query->bindValue(std::string(":catalog_type"), iter->first);
            query->bindValue(std::string(":object_id_in_catalog"), iter->second);

            query2->bindValue(std::string(":catalog_type2"), iter->first);
            query2->bindValue(std::string(":object_id_in_catalog2"), iter->second);

            query->execute();
            query2->execute();
        } catch (...) {
            db.rollbackTransaction();
            throw;
        }
    }
    db.commitTransaction();
}

void tlinsUIDatabaseDefinition::selectAstroObjects(const std::string& condition,
    const long offset,
    const long windowSize,
    tlinsAstroCatalogCollection& output)
{
    std::string sql1 = "SELECT catalog_type,         "
                       "       object_id_in_catalog, "
                       "       object_description,   "
                       "       name,                 "
                       "       description,          "
                       "       type,                 "
                       "       type_details_1,       "
                       "       type_details_2,       "
                       "       type_details_3,       "
                       "       constelation,         "
                       "       ra,                   "
                       "       dc,                   "
                       "       pm_ra,                "
                       "       pm_dc,                "
                       "       ep_ra,                "
                       "       ep_dc,                "
                       "       min_err_ra,           "
                       "       min_err_dc,           "
                       "       err_mean_ra,          "
                       "       err_mean_dc,          "
                       "       err_mean_pm_ra,       "
                       "       err_mean_pm_dc,       "
                       "       magnitude,            "
                       "       err_magnitude,        "
                       "       radial_velocity,      "
                       "       parallex              "
                       "FROM astro_objects           ";

    std::string sql2;
    if (condition.size() != 0)
        sql2 = sql1 + std::string(" WHERE ") + condition;
    else
        sql2 = sql1;

    std::string sql;
    if (windowSize > 0)
        sql = sql2 + std::string(" LIMIT ") + std::to_string(windowSize) + std::string(" OFFSET ") + std::to_string(offset) + std::string(";");
    else
        sql = sql2 + std::string(";");

    std::shared_ptr<tlinsUIDatabase::Query> query = db.createQuery();

    query->prepere(sql);
    query->execute();

    // Rozmiaru zestawu danych

    while (query->next()) {
        bool isNULL;
        std::string name;
        std::string description;
        std::string type;
        std::string typeDetails1;
        std::string typeDetails2;
        std::string typeDetails3;
        std::string constelation;
        double RA;
        double DC;
        double pmRA;
        double pmDC;
        double epRA;
        double epDC;
        double minErrRa;
        double minErrDc;
        double errMeanRA;
        double errMeanDC;
        double errMeanPmRA;
        double errMeanPmDC;
        double magnitude;
        double errMagnitude;
        double radialVelocity;
        double parallex;
        std::string catalogType;
        std::string objectIdInCatalog;
        std::string objectDescription;

        query->readValue(std::string("catalog_type"), catalogType, isNULL);
        query->readValue(std::string("object_id_in_catalog"), objectIdInCatalog, isNULL);
        query->readValue(std::string("object_description"), objectDescription, isNULL);
        query->readValue(std::string("name"), name, isNULL);
        query->readValue(std::string("description"), description, isNULL);
        query->readValue(std::string("type"), type, isNULL);
        query->readValue(std::string("type_details_1"), typeDetails1, isNULL);
        query->readValue(std::string("type_details_2"), typeDetails2, isNULL);
        query->readValue(std::string("type_details_3"), typeDetails3, isNULL);
        query->readValue(std::string("constelation"), constelation, isNULL);
        query->readValue(std::string("ra"), RA, isNULL);
        query->readValue(std::string("dc"), DC, isNULL);
        query->readValue(std::string("pm_ra"), pmRA, isNULL);
        query->readValue(std::string("pm_dc"), pmDC, isNULL);
        query->readValue(std::string("ep_ra"), epRA, isNULL);
        query->readValue(std::string("ep_dc"), epDC, isNULL);
        query->readValue(std::string("min_err_ra"), minErrRa, isNULL);
        query->readValue(std::string("min_err_dc"), minErrDc, isNULL);
        query->readValue(std::string("err_mean_ra"), errMeanRA, isNULL);
        query->readValue(std::string("err_mean_dc"), errMeanDC, isNULL);
        query->readValue(std::string("err_mean_pm_ra"), errMeanPmRA, isNULL);
        query->readValue(std::string("err_mean_pm_dc"), errMeanPmDC, isNULL);
        query->readValue(std::string("magnitude"), magnitude, isNULL);
        query->readValue(std::string("err_magnitude"), errMagnitude, isNULL);
        query->readValue(std::string("radial_velocity"), radialVelocity, isNULL);
        query->readValue(std::string("parallex"), parallex, isNULL);

        tlinsAstroCatalogItem aItem;
        aItem.setName(name);
        aItem.setDescription(description);
        {
            TlinsAstroBase::ObjectType::ObjectTypeInfo typeInfo;
            if (TlinsAstroBase::ObjectType::get(type, typeInfo))
                aItem.setType(typeInfo);
        }
        aItem.setTypeDetails1(typeDetails1);
        aItem.setTypeDetails2(typeDetails2);
        aItem.setTypeDetails3(typeDetails3);
        {
            TlinsAstroBase::Constelations::ConstelationInfo constelationInfo;
            if (TlinsAstroBase::Constelations::get(constelation, constelationInfo))
                aItem.setConstelation(constelationInfo);
        }
        aItem.setRA(RA);
        aItem.setDC(DC);
        aItem.setPmRA(pmRA);
        aItem.setPmDC(pmDC);
        aItem.setEpRA(epRA);
        aItem.setEpDC(epDC);
        aItem.setMinErrRA(minErrRa);
        aItem.setMinErrDC(minErrDc);
        aItem.setErrMeanRA(errMeanRA);
        aItem.setErrMeanDC(errMeanDC);
        aItem.setErrMeanPmRA(errMeanPmRA);
        aItem.setErrMeanPmDC(errMeanPmDC);
        aItem.setMagnitude(magnitude);
        aItem.setErrMagnitude(errMagnitude);
        aItem.setErrMagnitude(radialVelocity);
        {
            TlinsAstroBase::CatalogType::CatalogTypeInfo catalogTypeInfo;
            if (TlinsAstroBase::CatalogType::get(catalogType, catalogTypeInfo))
                aItem.setCatalogType(catalogTypeInfo);
        }
        aItem.setObjectIdInCatalog(objectIdInCatalog);
        aItem.setObjectDescription(objectDescription);
        aItem.setRadialVelocity(radialVelocity);
        aItem.setParallex(parallex);

        output.addItem(aItem);
    }
}

int tlinsUIDatabaseDefinition::countAstroObjects(const std::string& condition)
{
    std::string sql1 = "SELECT count(1) as rows_count "
                       "FROM astro_objects            ";

    std::string sql2;
    if (condition.size() != 0)
        sql2 = sql1 + std::string(" WHERE ") + condition;
    else
        sql2 = sql1;

    std::string sql = sql2 + std::string(";");
    std::shared_ptr<tlinsUIDatabase::Query> query = db.createQuery();

    query->prepere(sql);
    query->execute();

    long long count = 0;

    while (query->next()) {
        bool isNULL;
        query->readValue(std::string("rows_count"), count, isNULL);
    }

    return static_cast<int>(count);
}

// -------------------------------------------
// -------------------------------------------

//
// Operacje na konfiguracji
//
void tlinsUIDatabaseDefinition::insertConfigurationItem(const tlinsUiConfgiurationItem& cfgItems)
{
    std::string sql = "INSERT OR REPLACE INTO configuration               "
                      "( group_name, parameter, sequence,                 "
                      "  value1,  value2,  value3,  value4,  value5,      "
                      "  value6,  value7,  value8,  value9,  value10,     "
                      "  value11, value12, value13, value14, value15 )    "
                      "VALUES                                             "
                      "( :group_name, :parameter, :sequence,              "
                      "  :value1, :value2, :value3, :value4, :value5,     "
                      "  :value6, :value7, :value8, :value9, :value10,    "
                      "  :value11, :value12, :value13, :value14, :value15 "
                      ")                                                  ";

    std::shared_ptr<tlinsUIDatabase::Query> query = db.createQuery();
    query->prepere(sql);

    db.startTransaction();

    try {
        // Parametery grupy
        query->bindValue(std::string(":group_name"), cfgItems.getGroupName());
        query->bindValue(std::string(":parameter"), cfgItems.getParameter());
        query->bindValue(std::string(":sequence"), static_cast<long long>(0));

        // Values
        for (int j = 0; j < cfgItems.getMaxValuesCount(); j++) {
            char name[512];
            sprintf(name, ":value%d", j + 1);
            std::string vStr("");
            if (cfgItems.getItemValue(j, vStr)) {
                query->bindValue(std::string(name), vStr);
            }
        }
        query->execute();
        //		query ->clear();
    } catch (...) {
        db.rollbackTransaction();
        throw;
    }

    db.commitTransaction();
}

void tlinsUIDatabaseDefinition::updateConfigurationItem(const tlinsUiConfgiurationItem& cfgItems)
{
    std::string sql = "UPDATE OR REPLACE configuration    "
                      "SET value1  = :value1,             "
                      "    value2  = :value2,             "
                      "    value3  = :value3,             "
                      "    value4  = :value4,             "
                      "    value5  = :value5,             "
                      "    value6  = :value6,             "
                      "    value7  = :value7,             "
                      "    value8  = :value8,             "
                      "    value9  = :value9,             "
                      "    value10 = :value10,            "
                      "    value11 = :value11,            "
                      "    value12 = :value12,            "
                      "    value13 = :value13,            "
                      "    value14 = :value14,            "
                      "    value15 = :value15             "
                      "WHERE     group_name = :group_name "
                      "      AND parameter  = :parameter  "
                      "      AND sequence   = :sequence;  ";

    std::shared_ptr<tlinsUIDatabase::Query> query = db.createQuery();
    query->prepere(std::string(sql));

    db.startTransaction();

    try {
        // Values
        for (int j = 0; j < cfgItems.getMaxValuesCount(); j++) {
            char name[512];
            sprintf(name, ":value%d", j + 1);
            std::string vStr;
            if (cfgItems.getItemValue(j, vStr)) {
                query->bindValue(name, vStr);
            }
        }

        // Parametery grupy
        query->bindValue(std::string(":group_name"), cfgItems.getGroupName());
        query->bindValue(std::string(":parameter"), cfgItems.getParameter());
        query->bindValue(std::string(":sequence"), static_cast<long long>(0));

        query->execute();
        //		query ->clear();
    } catch (...) {
        db.rollbackTransaction();
        throw;
    }
    db.commitTransaction();
}

void tlinsUIDatabaseDefinition::selectConfigurationItem(const std::string& group,
    const std::string& parameter,
    tlinsUiConfgiurationItem& output)
{
    std::string sql = "SELECT group_name,                 "
                      "       parameter,                  "
                      "       sequence,                   "
                      "       value1,                     "
                      "       value2,                     "
                      "       value3,                     "
                      "       value4,                     "
                      "       value5,                     "
                      "       value6,                     "
                      "       value7,                     "
                      "       value8,                     "
                      "       value9,                     "
                      "       value10,                    "
                      "       value11,                    "
                      "       value12,                    "
                      "       value13,                    "
                      "       value14,                    "
                      "       value15                     "
                      "FROM   configuration               "
                      "WHERE     group_name = :group_name "
                      "      AND parameter  = :parameter  "
                      "ORDER BY sequence;                 ";

    std::shared_ptr<tlinsUIDatabase::Query> query = db.createQuery();

    query->prepere(std::string(sql));
    query->bindValue(":group_name", group);
    query->bindValue(":parameter", parameter);
    query->execute();

    while (query->next()) {
        bool isNull = false;
        std::string group_name;
        std::string parameter;

        query->readValue(std::string("group_name"), group_name, isNull);
        query->readValue(std::string("parameter"), parameter, isNull);

        output.setGroupName(group_name);
        output.setParameter(parameter);

        // Values
        tlinsUiConfgiurationItem::itemValues v;

        for (int j = 0; j < output.getMaxValuesCount(); j++) {
            std::string value;
            std::string name = std::string { "value" } + std::to_string(j + 1);

            query->readValue(name, value, isNull);
            v.setValue(j, value);
        }
        output.addItem(v);
    }
}

// -------------------------------------------
//
// Operacje na bazie danych IERS
//

void tlinsUIDatabaseDefinition::clearIERS()
{
    std::string sql = "DELETE FROM IERS;";

    std::shared_ptr<tlinsUIDatabase::Query> query = db.createQuery();
    query->prepere(sql);
    query->execute();
}

void tlinsUIDatabaseDefinition::insertIERS(const std::vector<tlinsIERS>& data)
{
    std::string sql = "INSERT OR REPLACE INTO IERS                     "
                      "(  year, month, day, pmx, pmy, delta_ut,        "
                      "   dpsi, depsilon, dx, dy )                     "
                      "VALUES                                          "
                      "(  :year, :month, :day, :pmx, :pmy, :delta_ut,  "
                      "   :dpsi, :depsilon, :dx, :dy );                ";

    std::shared_ptr<tlinsUIDatabase::Query> query = db.createQuery();
    query->prepere(sql);

    try {
        for (auto& item : data) {
            query->bindValue(":year", item.getYear());
            query->bindValue(":month", item.getMonth());
            query->bindValue(":day", item.getDay());
            query->bindValue(":pmx", item.getPmx());
            query->bindValue(":pmy", item.getPmy());
            query->bindValue(":delta_ut", item.getDeltaUt());
            query->bindValue(":dpsi", item.getDPsi());
            query->bindValue(":depsilon", item.getDEpsilon());
            query->bindValue(":dx", item.getDx());
            query->bindValue(":dy", item.getDy());
            query->execute();
        }
    } catch (...) {
        throw;
    }
}

void tlinsUIDatabaseDefinition::deleteIERS(const std::vector<tlinsIERS>& data)
{
    std::string sql = "DELETE FROM IERS          "
                      " WHERE     1 = 1          "
                      "       AND year = :year   "
                      "       AND month = :month "
                      "       AND day = :day;    ";

    db.startTransaction();

    try {
        for (auto& item : data) {
            std::shared_ptr<tlinsUIDatabase::Query> query = db.createQuery();
            query->prepere(sql);

            query->bindValue(":year", item.getYear());
            query->bindValue(":month", item.getMonth());
            query->bindValue(":day", item.getDay());
            query->execute();
        }
    } catch (...) {
        db.rollbackTransaction();
        throw;
    }

    db.commitTransaction();
}

void tlinsUIDatabaseDefinition::updateIERS(const std::vector<tlinsIERS>& data)
{
    std::string sql = "UPDATE IERS                "
                      "SET year     = :year,      "
                      "    month    = :month,     "
                      "    day      = :day,       "
                      "    pmx      = :pmx,       "
                      "    pmy      = :pmy,       "
                      "    delta_ut = :delta_ut,  "
                      "    dpsi     = :dpsi,      "
                      "    depsilon = :depsilon,  "
                      "    dx       = :dx,        "
                      "    dy       = :dy         "
                      "WHERE     1     = 1        "
                      "      AND year  = :c_year  "
                      "      AND month = :c_month "
                      "      AND day   = :c_day;  ";

    std::shared_ptr<tlinsUIDatabase::Query> query = db.createQuery();
    query->prepere(sql);

    db.startTransaction();

    try {
        for (auto& item : data) {
            query->bindValue(":year", item.getYear());
            query->bindValue(":month", item.getMonth());
            query->bindValue(":day", item.getDay());
            query->bindValue(":pmx", item.getPmx());
            query->bindValue(":pmy", item.getPmy());
            query->bindValue(":delta_ut", item.getDeltaUt());
            query->bindValue(":dpsi", item.getDPsi());
            query->bindValue(":depsilon", item.getDEpsilon());
            query->bindValue(":dx", item.getDx());
            query->bindValue(":dy", item.getDy());

            query->bindValue(":c_year", item.getYear());
            query->bindValue(":c_month", item.getMonth());
            query->bindValue(":c_day", item.getDay());

            query->execute();
            //			query -> clear();
        }
    } catch (...) {
        db.rollbackTransaction();
        throw;
    }

    db.commitTransaction();
}

void tlinsUIDatabaseDefinition::selectIERS(std::vector<tlinsIERS>& data)
{
    std::string sql = "SELECT year,     "
                      "       month,    "
                      "       day,      "
                      "       pmx,      "
                      "       pmy,      "
                      "       delta_ut, "
                      "       dpsi,     "
                      "       depsilon, "
                      "       dx,       "
                      "       dy        "
                      "FROM   IERS      "
                      "ORDER BY year,   "
                      "         month,  "
                      "         day;    ";

    std::shared_ptr<tlinsUIDatabase::Query> query = db.createQuery();

    query->prepere(sql);
    query->execute();

    while (query->next()) {
        bool isNULL;
        int year;
        int month;
        int day;
        double pmx;
        double pmy;
        double delta_ut;
        double dpsi;
        double depsilon;
        double dx;
        double dy;

        query->readValue("year", year, isNULL);
        query->readValue("month", month, isNULL);
        query->readValue("day", day, isNULL);
        query->readValue("pmx", pmx, isNULL);
        query->readValue("pmy", pmy, isNULL);
        query->readValue("delta_ut", delta_ut, isNULL);
        query->readValue("dpsi", dpsi, isNULL);
        query->readValue("depsilon", depsilon, isNULL);
        query->readValue("dx", dx, isNULL);
        query->readValue("dy", dy, isNULL);

        tlinsIERS item;
        item.setYear(year);
        item.setMonth(month);
        item.setDay(day);
        item.setPmx(pmx);
        item.setPmy(pmy);
        item.setDeltaUt(delta_ut);
        item.setDPsi(dpsi);
        item.setDEpsilon(depsilon);
        item.setDx(dx);
        item.setDy(dy);

        data.push_back(item);
    }
}

bool tlinsUIDatabaseDefinition::selectIERS(int year, int month, int day, tlinsIERS& data)
{
    std::string sql = "SELECT year,              "
                      "       month,             "
                      "       day,               "
                      "       pmx,               "
                      "       pmy,               "
                      "       delta_ut,          "
                      "       dpsi,              "
                      "       depsilon,          "
                      "       dx,                "
                      "       dy                 "
                      "FROM   IERS               "
                      "WHERE      1 = 1          "
                      "       AND year  = :year  "
                      "       AND month = :month "
                      "       AND day   = :day;  ";

    std::shared_ptr<tlinsUIDatabase::Query> query = db.createQuery();

    query->prepere(sql);

    query->bindValue(":year", year);
    query->bindValue(":month", month);
    query->bindValue(":day", day);

    query->execute();
    bool hasData = false;
    while (query->next()) {
        bool isNULL;
        int year;
        int month;
        int day;
        double pmx;
        double pmy;
        double delta_ut;
        double dpsi;
        double depsilon;
        double dx;
        double dy;

        query->readValue("year", year, isNULL);
        query->readValue("month", month, isNULL);
        query->readValue("day", day, isNULL);
        query->readValue("pmx", pmx, isNULL);
        query->readValue("pmy", pmy, isNULL);
        query->readValue("delta_ut", delta_ut, isNULL);
        query->readValue("dpsi", dpsi, isNULL);
        query->readValue("depsilon", depsilon, isNULL);
        query->readValue("dx", dx, isNULL);
        query->readValue("dy", dy, isNULL);

        data.setYear(year);
        data.setMonth(month);
        data.setDay(day);
        data.setPmx(pmx);
        data.setPmy(pmy);
        data.setDeltaUt(delta_ut);
        data.setDPsi(dpsi);
        data.setDEpsilon(depsilon);
        data.setDx(dx);
        data.setDy(dy);

        hasData = true;
        break;
    }
    return hasData;
}

//
// -------------------------------------------
//
// Operacje na bazie danych miejsc obserwcji
//

void tlinsUIDatabaseDefinition::clearPlaces()
{
    std::string sql = "DELETE FROM OBSERVATION_PLACE; ";

    std::shared_ptr<tlinsUIDatabase::Query> query = db.createQuery();
    query->prepere(sql);
    query->execute();
}

void tlinsUIDatabaseDefinition::insertPlaces(const std::vector<tlinsPlace>& data)
{
    std::string sql = "INSERT OR REPLACE INTO OBSERVATION_PLACE                         "
                      "( name, longitude, latitude, hm, elipsoideType, isdefault )        "
                      "VALUES                                                           "
                      "( :name, :longitude, :latitude, :hm, :elipsoideType, :isdefault ); ";

    try {
        for (auto& item : data) {
            std::shared_ptr<tlinsUIDatabase::Query> query = db.createQuery();
            query->prepere(sql);

            query->bindValue(":name", item.getName());
            query->bindValue(":longitude", item.getLongitude());
            query->bindValue(":latitude", item.getLatitude());
            query->bindValue(":hm", item.getHm());

            switch (item.getEpType()) {
            case tlinsPlace::ElipsoideType::WGS_84:
                query->bindValue(":elipsoideType", 0);
                break;
            case tlinsPlace::ElipsoideType::GRS_80:
                query->bindValue(":elipsoideType", 1);
                break;
            case tlinsPlace::ElipsoideType::WGS_72:
                query->bindValue(":elipsoideType", 2);
                break;
            }

            query->bindValue(":isdefault", item.isDefault() ? 1 : 0);
            query->execute();
            //			query -> clear();
        }
    } catch (...) {
        throw;
    }
}

void tlinsUIDatabaseDefinition::deletePlaces(const std::vector<tlinsPlace>& data)
{
    std::string sql = "DELETE FROM OBSERVATION_PLACE "
                      " WHERE     1 = 1              "
                      "       AND name = :name;      ";

    db.startTransaction();
    try {
        for (auto& item : data) {
            std::shared_ptr<tlinsUIDatabase::Query> query = db.createQuery();
            query->prepere(sql);

            query->bindValue(":name", item.getName());
            query->execute();
            //			query -> clear();
        }
    } catch (...) {
        db.rollbackTransaction();
        throw;
    }
    db.commitTransaction();
}

void tlinsUIDatabaseDefinition::updatePlaces(const std::vector<tlinsPlace>& data)
{
    std::string sql = "UPDATE OBSERVATION_PLACE            "
                      "SET name          = :name,          "
                      "    longitude     = :longitude,     "
                      "    latitude      = :latitude,      "
                      "    hm            = :hm,            "
                      "    elipsoideType = :elipsoideType, "
                      "    isdefault     = :isdefault      "
                      "WHERE name = :c_name;               ";

    db.startTransaction();

    try {
        for (auto& item : data) {
            std::shared_ptr<tlinsUIDatabase::Query> query = db.createQuery();
            query->prepere(sql);

            query->bindValue(":name", item.getName());
            query->bindValue(":longitude", item.getLongitude());
            query->bindValue(":latitude", item.getLatitude());
            query->bindValue(":hm", item.getHm());

            switch (item.getEpType()) {
            case tlinsPlace::ElipsoideType::WGS_84:
                query->bindValue(":elipsoideType", 0);
                break;
            case tlinsPlace::ElipsoideType::GRS_80:
                query->bindValue(":elipsoideType", 1);
                break;
            case tlinsPlace::ElipsoideType::WGS_72:
                query->bindValue(":elipsoideType", 2);
                break;
            }

            query->bindValue(":isdefault", item.isDefault() ? 1 : 0);
            query->bindValue(":c_name", item.getName());
            query->execute();
            //			query -> clear();
        }
    } catch (...) {
        db.rollbackTransaction();
        throw;
    }

    db.commitTransaction();
}

void tlinsUIDatabaseDefinition::selectAllPlaces(std::vector<tlinsPlace>& data)
{
    std::string sql = "SELECT name,             "
                      "       longitude,        "
                      "       latitude,         "
                      "       hm,               "
                      "       elipsoideType,    "
                      "       isdefault         "
                      "FROM   OBSERVATION_PLACE "
                      "ORDER BY name;           ";

    std::shared_ptr<tlinsUIDatabase::Query> query = db.createQuery();

    query->prepere(sql);
    query->execute();

    while (query->next()) {
        bool isNULL;
        std::string name;
        double longitude;
        double latitude;
        double hm;
        int elipsoideType;
        int default_;

        query->readValue("name", name, isNULL);
        query->readValue("longitude", longitude, isNULL);
        query->readValue("latitude", latitude, isNULL);
        query->readValue("hm", hm, isNULL);
        query->readValue("elipsoideType", elipsoideType, isNULL);
        query->readValue("isdefault", default_, isNULL);

        tlinsPlace item;
        item.setName(name);
        item.setLongitude(longitude);
        item.setLatitude(latitude);
        item.setHm(hm);

        switch (elipsoideType) {
        case 0:
            item.setEpType(tlinsPlace::ElipsoideType::WGS_84);
            break;

        case 1:
            item.setEpType(tlinsPlace::ElipsoideType::GRS_80);
            break;

        case 2:
            item.setEpType(tlinsPlace::ElipsoideType::WGS_72);
            break;

        default:
            item.setEpType(tlinsPlace::ElipsoideType::GRS_80);
            break;
        }

        item.setDefault(default_ == 1 ? true : false);
        data.push_back(item);
    }
}

bool tlinsUIDatabaseDefinition::selectDefaultPlace(tlinsPlace& data)
{
    std::string sql = "SELECT name,             "
                      "       longitude,        "
                      "       latitude,         "
                      "       hm,               "
                      "       elipsoideType,    "
                      "       isdefault         "
                      "FROM   OBSERVATION_PLACE "
                      "WHERE  isdefault = 1;    ";

    std::shared_ptr<tlinsUIDatabase::Query> query = db.createQuery();

    query->prepere(sql);
    query->execute();

    bool exists = false;

    while (query->next()) {
        bool isNULL;
        std::string name;
        double longitude;
        double latitude;
        double hm;
        int elipsoideType;
        int default_;

        query->readValue("name", name, isNULL);
        query->readValue("longitude", longitude, isNULL);
        query->readValue("latitude", latitude, isNULL);
        query->readValue("hm", hm, isNULL);
        query->readValue("elipsoideType", elipsoideType, isNULL);
        query->readValue("isdefault", default_, isNULL);

        data.setName(name);
        data.setLongitude(longitude);
        data.setLatitude(latitude);
        data.setHm(hm);

        switch (elipsoideType) {
        case 0:
            data.setEpType(tlinsPlace::ElipsoideType::WGS_84);
            break;

        case 1:
            data.setEpType(tlinsPlace::ElipsoideType::GRS_80);
            break;

        case 2:
            data.setEpType(tlinsPlace::ElipsoideType::WGS_72);
            break;

        default:
            data.setEpType(tlinsPlace::ElipsoideType::GRS_80);
            break;
        }

        data.setDefault(default_ == 1 ? true : false);
        exists = true;
        break;
    }
    return exists;
}

void tlinsUIDatabaseDefinition::selectByNamePlace(const std::string& name, tlinsPlace& data)
{
    std::string sql = "SELECT name,             "
                      "       longitude,        "
                      "       latitude,         "
                      "       hm,               "
                      "       elipsoideType,    "
                      "       isdefault         "
                      "FROM   OBSERVATION_PLACE "
                      "WHERE  name = :name;     ";

    std::shared_ptr<tlinsUIDatabase::Query> query = db.createQuery();

    query->prepere(sql);
    query->bindValue(":name", name);

    while (query->next()) {
        bool isNULL;
        std::string name;
        double longitude;
        double latitude;
        double hm;
        int elipsoideType;
        int default_;

        query->readValue("name", name, isNULL);
        query->readValue("longitude", longitude, isNULL);
        query->readValue("latitude", latitude, isNULL);
        query->readValue("hm", hm, isNULL);
        query->readValue("elipsoideType", elipsoideType, isNULL);
        query->readValue("isdefault", default_, isNULL);

        data.setName(name);
        data.setLongitude(longitude);
        data.setLatitude(latitude);
        data.setHm(hm);

        switch (elipsoideType) {
        case 0:
            data.setEpType(tlinsPlace::ElipsoideType::WGS_84);
            break;

        case 1:
            data.setEpType(tlinsPlace::ElipsoideType::GRS_80);
            break;

        case 2:
            data.setEpType(tlinsPlace::ElipsoideType::WGS_72);
            break;

        default:
            data.setEpType(tlinsPlace::ElipsoideType::GRS_80);
            break;
        }

        data.setDefault(default_ == 1 ? true : false);
        break;
    }
}

void tlinsUIDatabaseDefinition::createDatabae()
{
    std::string schema_1 = "CREATE TABLE IF NOT EXISTS astro_objects           "
                           "(                                                  "
                           "catalog_type         TEXT,                         "
                           "object_id_in_catalog TEXT,                         "
                           "object_description   TEXT,                         "
                           "name                 TEXT,                         "
                           "description          TEXT,                         "
                           "type                 TEXT,                         "
                           "type_details_1       TEXT,                         "
                           "type_details_2       TEXT,                         "
                           "type_details_3       TEXT,                         "
                           "constelation         TEXT,                         "
                           "ra                   REAL NOT NULL,                "
                           "dc                   REAL NOT NULL,                "
                           "pm_ra                REAL NOT NULL DEFAULT ( 0 ),  "
                           "pm_dc                REAL NOT NULL DEFAULT ( 0 ),  "
                           "ep_ra                REAL NOT NULL DEFAULT ( 0 ),  "
                           "ep_dc                REAL NOT NULL DEFAULT ( 0 ),  "
                           "min_err_ra           REAL NOT NULL DEFAULT ( 0 ),  "
                           "min_err_dc           REAL NOT NULL DEFAULT ( 0 ),  "
                           "err_mean_ra          REAL NOT NULL DEFAULT ( 0 ),  "
                           "err_mean_dc          REAL NOT NULL DEFAULT ( 0 ),  "
                           "err_mean_pm_ra       REAL NOT NULL DEFAULT ( 0 ),  "
                           "err_mean_pm_dc       REAL NOT NULL DEFAULT ( 0 ),  "
                           "magnitude            REAL NOT NULL DEFAULT ( 0 ),  "
                           "err_magnitude        REAL NOT NULL DEFAULT ( 0 ),  "
                           "radial_velocity      REAL NOT NULL DEFAULT ( 0 ),  "
                           "parallex             REAL NOT NULL DEFAULT ( 0 ),  "
                           "PRIMARY KEY (catalog_type, object_id_in_catalog) );";

    std::string schema_2 = "CREATE TABLE IF NOT EXISTS configuration    "
                           "(                                           "
                           "  group_name TEXT NOT NULL,                 "
                           "  parameter  TEXT NOT NULL,                 "
                           "  sequence   INTEGER NOT NULL DEFAULT( 0 ), "
                           "  value1     TEXT,                          "
                           "  value2     TEXT,                          "
                           "  value3     TEXT,                          "
                           "  value4     TEXT,                          "
                           "  value5     TEXT,                          "
                           "  value6     TEXT,                          "
                           "  value7     TEXT,                          "
                           "  value8     TEXT,                          "
                           "  value9     TEXT,                          "
                           "  value10    TEXT,                          "
                           "  value11    TEXT,                          "
                           "  value12    TEXT,                          "
                           "  value13    TEXT,                          "
                           "  value14    TEXT,                          "
                           "  value15    TEXT,                          "
                           "  PRIMARY KEY (group_name, parameter, sequence)"
                           ");";

    std::string schema_3 = "CREATE TABLE IF NOT EXISTS constelations "
                           "(                                        "
                           "  id    INTEGER NOT NULL,                "
                           "  label TEXT NOT NULL,                   "
                           "  name  TEXT NOT NULL,                   "
                           "  PRIMARY KEY (id)                       "
                           ");                                       ";

    std::string schema_4 = "CREATE TABLE IF NOT EXISTS object_type "
                           "(                                      "
                           "  id    INTEGER NOT NULL,              "
                           "  label TEXT NOT NULL,                 "
                           "  name  TEXT NOT NULL,                 "
                           "  PRIMARY KEY (id)                     "
                           ");                                     ";

    std::string schema_5 = "CREATE TABLE IF NOT EXISTS catalog_type "
                           "(                                       "
                           "  id    INTEGER NOT NULL,               "
                           "  label TEXT NOT NULL,                  "
                           "  name  TEXT NOT NULL,                  "
                           "  PRIMARY KEY (id)                      "
                           ");                                      ";

    std::string schema_6 = "CREATE TABLE IF NOT EXISTS astro_calibration_objects "
                           "(                                                    "
                           "  catalog_type         TEXT    NOT NULL,             "
                           "  object_id_in_catalog TEXT    NOT NULL,             "
                           "  object_order         INTEGER NOT NULL,             "
                           "  UNIQUE ( catalog_type, object_id_in_catalog )      "
                           "  UNIQUE ( object_order )                            "
                           "  FOREIGN KEY(catalog_type, object_id_in_catalog) REFERENCES astro_objects(catalog_type, object_id_in_catalog)"
                           ");";

    std::string schema_7 = "CREATE TABLE IF NOT EXISTS IERS            "
                           "(                                          "
                           "  year     INTEGER NOT NULL DEFAULT ( 0 ), "
                           "  month    INTEGER NOT NULL DEFAULT ( 0 ), "
                           "  day      INTEGER NOT NULL DEFAULT ( 0 ), "
                           "  pmx      REAL    NOT NULL DEFAULT ( 0 ), "
                           "  pmy      REAL    NOT NULL DEFAULT ( 0 ), "
                           "  delta_ut REAL    NOT NULL DEFAULT ( 0 ), "
                           "  dpsi     REAL    NOT NULL DEFAULT ( 0 ), "
                           "  depsilon REAL    NOT NULL DEFAULT ( 0 ), "
                           "  dx       REAL    NOT NULL DEFAULT ( 0 ), "
                           "  dy       REAL    NOT NULL DEFAULT ( 0 ), "
                           "  UNIQUE ( year, month, day )              "
                           ");";

    std::string schema_8 = "CREATE TABLE IF NOT EXISTS OBSERVATION_PLACE    "
                           "(                                               "
                           "  name          TEXT    NOT NULL,               "
                           "  longitude     REAL    NOT NULL DEFAULT ( 0 ), "
                           "  latitude      REAL    NOT NULL DEFAULT ( 0 ), "
                           "  hm            REAL    NOT NULL DEFAULT ( 0 ), "
                           "  elipsoideType INTEGER NOT NULL DEFAULT ( 0 ), "
                           "  isdefault     INTEGER NOT NULL DEFAULT ( 0 ), "
                           "  UNIQUE ( name )                               "
                           ");                                              ";

    std::string schema_9 = "CREATE TABLE IF NOT EXISTS ASTRO_ENGINE_STATE     "
                           "(                                                 "
                           "  name            TEXT    NOT NULL,               "
                           "  ra              REAL    NOT NULL DEFAULT ( 0 ), "
                           "  dc              REAL    NOT NULL DEFAULT ( 0 ), "
                           "  pm_ra           REAL    NOT NULL DEFAULT ( 0 ), "
                           "  pm_dc           REAL    NOT NULL DEFAULT ( 0 ), "
                           "  radial_velocity REAL    NOT NULL DEFAULT ( 0 ), "
                           "  parallex        REAL    NOT NULL DEFAULT ( 0 ), "
                           "  catalog_type    TEXT    NOT NULL,               "
                           "  a11             REAL    NOT NULL DEFAULT ( 0 ), "
                           "  a12             REAL    NOT NULL DEFAULT ( 0 ), "
                           "  a13             REAL    NOT NULL DEFAULT ( 0 ), "
                           "  a21             REAL    NOT NULL DEFAULT ( 0 ), "
                           "  a22             REAL    NOT NULL DEFAULT ( 0 ), "
                           "  a23             REAL    NOT NULL DEFAULT ( 0 ), "
                           "  a31             REAL    NOT NULL DEFAULT ( 0 ), "
                           "  a32             REAL    NOT NULL DEFAULT ( 0 ), "
                           "  a33             REAL    NOT NULL DEFAULT ( 0 ), "
                           "  deviceX         INTEGER NOT NULL DEFAULT ( 0 ), "
                           "  deviceY         INTEGER NOT NULL DEFAULT ( 0 ), "
                           "  deviceXEncoder  INTEGER NOT NULL DEFAULT ( 0 ), "
                           "  deviceYEncoder  INTEGER NOT NULL DEFAULT ( 0 ), "
                           "  mode            INTEGER NOT NULL DEFAULT ( 0 ), "
                           "  state           INTEGER NOT NULL DEFAULT ( 0 ), "
                           "  speed           REAL    NOT NULL DEFAULT ( 0 ), "
                           "  aceleration     REAL    NOT NULL DEFAULT ( 0 ), "
                           "  delta           INTEGER NOT NULL DEFAULT ( 0 ), "
                           "  x_reverse       TEXT    NOT NULL DEFAULT ( 'false' ), "
                           "  y_reverse       TEXT    NOT NULL DEFAULT ( 'false' ), "
                           "  UNIQUE ( name )                                 "
                           ");                                                ";

    std::string schema_10 = "CREATE TABLE IF NOT EXISTS KEYS_SHORTCUT          "
                            "(                                                 "
                            "  name            TEXT    NOT NULL,               "
                            "  type            INTEGER NOT NULL,               "
                            "  subType         INTEGER NOT NULL,               "
                            "  defaultHandler  INTEGER NOT NULL DEFAULT ( 0 ), "
                            "  actionName      TEXT    NOT NULL,               "
                            "  actionKeys      TEXT    NOT NULL,               "
                            "  actionSettings  TEXT    NOT NULL,               "
                            "  actionMode      INTEGER NOT NULL DEFAULT ( 0 ), "
                            "  UNIQUE ( name )                                 "
                            ");                                                ";

    std::string schema_100 = "PRAGMA foreign_keys = ON;";

    std::shared_ptr<tlinsUIDatabase::Query> query_s1 = db.createQuery();
    std::shared_ptr<tlinsUIDatabase::Query> query_s2 = db.createQuery();
    std::shared_ptr<tlinsUIDatabase::Query> query_s3 = db.createQuery();
    std::shared_ptr<tlinsUIDatabase::Query> query_s4 = db.createQuery();
    std::shared_ptr<tlinsUIDatabase::Query> query_s5 = db.createQuery();
    std::shared_ptr<tlinsUIDatabase::Query> query_s6 = db.createQuery();
    std::shared_ptr<tlinsUIDatabase::Query> query_s7 = db.createQuery();
    std::shared_ptr<tlinsUIDatabase::Query> query_s8 = db.createQuery();
    std::shared_ptr<tlinsUIDatabase::Query> query_s9 = db.createQuery();
    std::shared_ptr<tlinsUIDatabase::Query> query_s10 = db.createQuery();

    std::shared_ptr<tlinsUIDatabase::Query> query_s100 = db.createQuery();

    try {
        qDebug() << "--------------------------------------------------------";
        qDebug() << "Create database";
        qDebug() << "--------------------------------------------------------";
        db.startTransaction();

        // Przygotowanie zapytania
        query_s1->prepere(std::string(schema_1));
        query_s2->prepere(std::string(schema_2));
        query_s3->prepere(std::string(schema_3));
        query_s4->prepere(std::string(schema_4));
        query_s5->prepere(std::string(schema_5));
        query_s6->prepere(std::string(schema_6));
        query_s7->prepere(std::string(schema_7));
        query_s8->prepere(std::string(schema_8));
        query_s9->prepere(std::string(schema_9));
        query_s10->prepere(std::string(schema_10));

        query_s100->prepere(std::string(schema_100));

        // Ececute query
        query_s1->execute();
        query_s2->execute();
        query_s3->execute();
        query_s4->execute();
        query_s5->execute();
        query_s6->execute();
        query_s7->execute();
        query_s8->execute();
        query_s9->execute();
        query_s10->execute();
        query_s100->execute();

        // Ececute query
        db.commitTransaction();
    } catch (...) {
        // Rollback transaction
        qDebug() << "--------------------------------------------------------";
        qDebug() << "Rollback";
        db.rollbackTransaction();
        qDebug() << "DB ERROR";
        qDebug() << "--------------------------------------------------------";
        throw;
    }
}

}
