#include "tlinsconfiguration.h"
#include <QCoreApplication>
#include <string>
#include <tlinsuidatabasedefinition.h>

#include <QSettings>

#define __SET_STRING_FILE__(group, name, v)                                          \
    do {                                                                             \
        std::unique_lock<std::recursive_mutex> lock(mtx);                            \
        settings->beginGroup(QString::fromStdString(group));                         \
        settings->setValue(QString::fromStdString(name), QString::fromStdString(v)); \
        settings->endGroup();                                                        \
        setKeyString(group, name, v);                                                \
    } while (false)

#define __SET_LONG_FILE__(group, name, v)                    \
    do {                                                     \
        std::unique_lock<std::recursive_mutex> lock(mtx);    \
        settings->beginGroup(QString::fromStdString(group)); \
        QVariant x;                                          \
        x.setValue(v);                                       \
        settings->setValue(QString::fromStdString(name), x); \
        settings->endGroup();                                \
        setKeyInt(group, name, v);                           \
    } while (false)

#define __SET_DOUBLE_FILE__(group, name, v)                            \
    do {                                                               \
        std::unique_lock<std::recursive_mutex> lock(mtx);              \
        settings->beginGroup(QString::fromStdString(group));           \
        settings->setValue(QString::fromStdString(name), QVariant(v)); \
        settings->endGroup();                                          \
        setKeyDouble(group, name, v);                                  \
    } while (false)

#define __GET_STRING_FILE__(group, name)                                        \
    do {                                                                        \
        std::unique_lock<std::recursive_mutex> lock(mtx);                       \
        if (hasKeyString(group, name)) {                                        \
            return stringMap[createKey(group, name)];                           \
        }                                                                       \
        settings->beginGroup(QString::fromStdString(group));                    \
        QString ret = settings->value(QString::fromStdString(name)).toString(); \
        settings->endGroup();                                                   \
        setKeyString(group, name, ret.toStdString());                           \
        return ret.toStdString();                                               \
    } while (false)

#define __GET_LONG_FILE__(group, name)                                   \
    do {                                                                 \
        std::unique_lock<std::recursive_mutex> lock(mtx);                \
        if (hasKeyInt(group, name)) {                                    \
            return intMap[createKey(group, name)];                       \
        }                                                                \
        settings->beginGroup(QString::fromStdString(group));             \
        int ret = settings->value(QString::fromStdString(name)).toInt(); \
        settings->endGroup();                                            \
        setKeyInt(group, name, ret);                                     \
        return ret;                                                      \
    } while (false)

#define __GET_DOUBLE_FILE__(group, name)                                       \
    do {                                                                       \
        std::unique_lock<std::recursive_mutex> lock(mtx);                      \
        if (hasKeyDouble(group, name)) {                                       \
            return doubleMap[createKey(group, name)];                          \
        }                                                                      \
        settings->beginGroup(QString::fromStdString(group));                   \
        double ret = settings->value(QString::fromStdString(name)).toDouble(); \
        settings->endGroup();                                                  \
        setKeyDouble(group, name, ret);                                        \
        return ret;                                                            \
    } while (false)

#define __SET_STRING__(group, name, v)                       \
    do {                                                     \
        std::unique_lock<std::recursive_mutex> lock(mtx);    \
        TlinsAstroBase::tlinsUIDatabase db;                  \
        TlinsAstroBase::tlinsUIDatabaseDefinition dbDef(db); \
        TlinsAstroBase::tlinsUiConfgiurationItem item;       \
        item.setGroupName(group);                            \
        item.setParameter(name);                             \
        item.setValues(0, v);                                \
        dbDef.insertConfigurationItem(item);                 \
        setKeyString(group, name, v);                        \
    } while (false)

#define __SET_DIGIT__(group, name, v)                        \
    do {                                                     \
        TlinsAstroBase::tlinsUIDatabase db;                  \
        TlinsAstroBase::tlinsUIDatabaseDefinition dbDef(db); \
        TlinsAstroBase::tlinsUiConfgiurationItem item;       \
        item.setGroupName(group);                            \
        item.setParameter(name);                             \
        item.setValues(0, std::to_string(v));                \
        dbDef.insertConfigurationItem(item);                 \
    } while (false)

#define __SET_LONG__(group, name, v)                      \
    do {                                                  \
        std::unique_lock<std::recursive_mutex> lock(mtx); \
        __SET_DIGIT__(group, name, v);                    \
        setKeyInt(group, name, v);                        \
    } while (false)

#define __SET_DOUBLE__(group, name, v)                    \
    do {                                                  \
        std::unique_lock<std::recursive_mutex> lock(mtx); \
        __SET_DIGIT__(group, name, v);                    \
        setKeyDouble(group, name, v);                     \
    } while (false)

#define __GET_STRING__(group, name)                          \
    do {                                                     \
        std::unique_lock<std::recursive_mutex> lock(mtx);    \
        if (hasKeyString(group, name)) {                     \
            return stringMap[createKey(group, name)];        \
        }                                                    \
        TlinsAstroBase::tlinsUIDatabase db;                  \
        TlinsAstroBase::tlinsUIDatabaseDefinition dbDef(db); \
        TlinsAstroBase::tlinsUiConfgiurationItem item;       \
        dbDef.selectConfigurationItem(group,                 \
            name,                                            \
            item);                                           \
        std::string value;                                   \
        if (item.getItemValue(0, value)) {                   \
            setKeyString(group, name, value);                \
            return value;                                    \
        }                                                    \
        setKeyString(group, name, std::string { "" });       \
        return std::string { "" };                           \
    } while (false)

#define __GET_LONG__(group, name)                            \
    do {                                                     \
        std::unique_lock<std::recursive_mutex> lock(mtx);    \
        if (hasKeyInt(group, name)) {                        \
            return intMap[createKey(group, name)];           \
        }                                                    \
        TlinsAstroBase::tlinsUIDatabase db;                  \
        TlinsAstroBase::tlinsUIDatabaseDefinition dbDef(db); \
        TlinsAstroBase::tlinsUiConfgiurationItem item;       \
        dbDef.selectConfigurationItem(group,                 \
            name,                                            \
            item);                                           \
        std::string strValue;                                \
        if (item.getItemValue(0, strValue)) {                \
            setKeyInt(group, name, std::stol(strValue));     \
            return std::stol(strValue);                      \
        }                                                    \
        setKeyInt(group, name, 0);                           \
        return 0;                                            \
    } while (false)

#define __GET_DOUBLE__(group, name)                          \
    do {                                                     \
        std::unique_lock<std::recursive_mutex> lock(mtx);    \
        if (hasKeyDouble(group, name)) {                     \
            return doubleMap[createKey(group, name)];        \
        }                                                    \
        TlinsAstroBase::tlinsUIDatabase db;                  \
        TlinsAstroBase::tlinsUIDatabaseDefinition dbDef(db); \
        TlinsAstroBase::tlinsUiConfgiurationItem item;       \
        dbDef.selectConfigurationItem(group,                 \
            name,                                            \
            item);                                           \
        std::string strValue;                                \
        if (item.getItemValue(0, strValue)) {                \
            setKeyDouble(group, name, std::stod(strValue));  \
            return std::stod(strValue);                      \
        }                                                    \
        setKeyDouble(group, name, 0.0);                      \
        return 0.0;                                          \
    } while (false)

namespace TlinsAstroBase {

bool tlinsConfiguration::hasKey(const std::string& group, const std::string& key)
{
    std::unique_lock<std::recursive_mutex> lock(mtx);

    TlinsAstroBase::tlinsUIDatabase db;
    TlinsAstroBase::tlinsUIDatabaseDefinition dbDef(db);
    TlinsAstroBase::tlinsUiConfgiurationItem item;
    dbDef.selectConfigurationItem(group,
        key,
        item);
    std::string strValue;
    if (item.getItemValue(0, strValue))
        return true;
    return false;
}

bool tlinsConfiguration::hasKeyFile(const std::string& group, const std::string& key)
{
    settings->beginGroup(QString::fromStdString(group));
    auto ret = settings->contains(QString::fromStdString(key));
    settings->endGroup();
    return ret;
}

void tlinsConfiguration::setValue(const std::string& group, const std::string& key, const double v)
{
    __SET_DOUBLE__(group, key, v);
}

void tlinsConfiguration::setValueFile(const std::string& group, const std::string& key, const double v)
{
    __SET_DOUBLE_FILE__(group, key, v);
}

void tlinsConfiguration::setValue(const std::string& group, const std::string& key, const int v)
{
    __SET_LONG__(group, key, v);
}

void tlinsConfiguration::setValueFile(const std::string& group, const std::string& key, const int v)
{
    __SET_LONG_FILE__(group, key, v);
}

void tlinsConfiguration::setValue(const std::string& group, const std::string& key, const long v)
{
    __SET_LONG__(group, key, v);
}

void tlinsConfiguration::setValueFile(const std::string& group, const std::string& key, const long v)
{
    __SET_LONG_FILE__(group, key, v);
}

void tlinsConfiguration::setValue(const std::string& group, const std::string& key, const std::string& v)
{
    __SET_STRING__(group, key, v);
}

void tlinsConfiguration::setValueFile(const std::string& group, const std::string& key, const std::string& v)
{
    __SET_STRING_FILE__(group, key, v);
}

std::string tlinsConfiguration::getString(const std::string& group, const std::string& key)
{
    __GET_STRING__(group, key);
}

std::string tlinsConfiguration::getStringFile(const std::string& group, const std::string& key)
{
    __GET_STRING_FILE__(group, key);
}

double tlinsConfiguration::getDouble(const std::string& group, const std::string& key)
{
    __GET_DOUBLE__(group, key);
}

double tlinsConfiguration::getDoubleFile(const std::string& group, const std::string& key)
{
    __GET_DOUBLE_FILE__(group, key);
}

int tlinsConfiguration::getInt(const std::string& group, const std::string& key)
{
    __GET_LONG__(group, key);
}

long tlinsConfiguration::getLong(const std::string& group, const std::string& key)
{
    __GET_LONG__(group, key);
}

int tlinsConfiguration::getIntFile(const std::string& group, const std::string& key)
{
    __GET_LONG_FILE__(group, key);
}

long tlinsConfiguration::getLongFile(const std::string& group, const std::string& key)
{
    __GET_LONG_FILE__(group, key);
}

tlinsConfiguration& tlinsConfiguration::getInstance()
{
    static tlinsConfiguration instance;
    return instance;
}

tlinsConfiguration::tlinsConfiguration()
{
    QCoreApplication::setOrganizationName("Jacek Pielaszkiewicz - Astro");
    QCoreApplication::setApplicationName("tlins");

    std::string filePath {};
    QString dbFile {};
    if (getenv("TLINS_ASTRO_DB") != NULL) {
        filePath = getenv("TLINS_ASTRO_DB");
        dbFile = QString::fromStdString(filePath);
    } else {
        filePath = getenv("HOME");
        dbFile = QString::fromStdString(filePath) + QString("/.tlins.conf");
    }
    settings = std::make_shared<QSettings>(dbFile, QSettings::NativeFormat);
}

tlinsConfiguration::~tlinsConfiguration()
{
}

std::string tlinsConfiguration::COMMON_PARAMETER_GROUP = "common-parameters";
std::string tlinsConfiguration::COMMON_MAIN_DEVICE_NAME = "main-device-name";

std::string tlinsConfiguration::DATABASE_GROUP = "database-parameters";
std::string tlinsConfiguration::DATABASE_FILE = "file";
std::string tlinsConfiguration::DATABASE_TYPE = "type";
std::string tlinsConfiguration::DATABASE_CONNECTION_NAME = "connection-name";
std::string tlinsConfiguration::DATABASE_HOST = "host";
std::string tlinsConfiguration::DATABASE_USER = "user";
std::string tlinsConfiguration::DATABASE_PASSWORD = "password";

//
// Konfiguracja polaczenia z silnikiem astro i silnikiem urzadzen
//
std::string tlinsConfiguration::CONNECTION_PARAMETER_GROUP = "connection-parameters";
std::string tlinsConfiguration::CONNECTION_PARAMETER_CONNECT_SYSTEM_EVENT_MONITOR = "connect-to_system-event-monitor";
std::string tlinsConfiguration::CONNECTION_PARAMETER_URL_ASTRO_ENGINE = "url/astro-engine";
std::string tlinsConfiguration::CONNECTION_PARAMETER_URL_ASTRO_ENGINE_AUTH = "url/astro-engine-auth";
std::string tlinsConfiguration::CONNECTION_PARAMETER_URL_DEVICE_ENGINE = "url/device-engine";
std::string tlinsConfiguration::CONNECTION_PARAMETER_URL_DEVICE_ENGINE_AUTH = "url/device-engine-auth";

std::string tlinsConfiguration::CONNECTION_PARAMETER_URL_ASTRO_ENGINE_ASYNCH = "url/astro-engine-asynch";
std::string tlinsConfiguration::CONNECTION_PARAMETER_URL_ASTRO_ENGINE_ASYNCH_AUTH = "url/astro-engine-asynch-auth";
std::string tlinsConfiguration::CONNECTION_PARAMETER_URL_DEVICE_ENGINE_ASYNCH = "url/device-engine-asynch";
std::string tlinsConfiguration::CONNECTION_PARAMETER_URL_DEVICE_ENGINE_ASYNCH_AUTH = "url/device-engine-asynch-auth";

std::string tlinsConfiguration::CONNECTION_PARAMETER_URL_SYSTEM_SERVICE = "url/system-service";
std::string tlinsConfiguration::CONNECTION_PARAMETER_URL_SYSTEM_SERVICE_AUTH = "url/system-service-auth";

std::string tlinsConfiguration::CONNECTION_PARAMETER_URL_ASTRO_ENGINE_PORT = "url/astro-engine-port";
std::string tlinsConfiguration::CONNECTION_PARAMETER_URL_DEVICE_ENGINE_PORT = "url/device-engine-port";
std::string tlinsConfiguration::CONNECTION_PARAMETER_URL_ASTRO_ENGINE_ASYNCH_PORT = "url/astro-engine-asynch-port";
std::string tlinsConfiguration::CONNECTION_PARAMETER_URL_DEVICE_ENGINE_ASYNCH_PORT = "url/device-engine-asynch-port";
std::string tlinsConfiguration::CONNECTION_PARAMETER_URL_SYSTEM_SERVICE_PORT = "url/system-service-port";
std::string tlinsConfiguration::CONNECTION_PARAMETER_URL_COMMON_ADDRESS_IP = "url/common-address";
std::string tlinsConfiguration::CONNECTION_PARAMETER_URL_USE_COMMON_ADDRESS = "url/use-common-address";

//
// Konfiguracja rampy przyspieszania
//
std::string tlinsConfiguration::RAMP_PARAMETER_GROUP = "ramp-parameters";

std::string tlinsConfiguration::RAMP_PARAMETER_STEPS_X_A = "steps/x/A";
std::string tlinsConfiguration::RAMP_PARAMETER_STEPS_X_D = "steps/x/D";
std::string tlinsConfiguration::RAMP_PARAMETER_STEPS_X_V_MAX = "steps/x/Vmax";

std::string tlinsConfiguration::RAMP_PARAMETER_STEPS_Y_A = "steps/y/A";
std::string tlinsConfiguration::RAMP_PARAMETER_STEPS_Y_D = "steps/y/A";
std::string tlinsConfiguration::RAMP_PARAMETER_STEPS_Y_V_MAX = "steps/y/Vmax";

std::string tlinsConfiguration::RAMP_PARAMETER_DEGRIS_X_A = "degris/x/A";
std::string tlinsConfiguration::RAMP_PARAMETER_DEGRIS_X_D = "degris/x/D";
std::string tlinsConfiguration::RAMP_PARAMETER_DEGRIS_X_V_MAX = "degris/x/Vmax";

std::string tlinsConfiguration::RAMP_PARAMETER_DEGRIS_Y_A = "degris/y/A";
std::string tlinsConfiguration::RAMP_PARAMETER_DEGRIS_Y_D = "degris/y/D";
std::string tlinsConfiguration::RAMP_PARAMETER_DEGRIS_Y_V_MAX = "degris/y/Vmax";

std::string tlinsConfiguration::RAMP_PARAMETER_ASTRO_RA_A = "astro/ra/A";
std::string tlinsConfiguration::RAMP_PARAMETER_ASTRO_RA_D = "astro/ra/D";
std::string tlinsConfiguration::RAMP_PARAMETER_ASTRO_RA_V_MAX = "astro/ra/Vmax";

std::string tlinsConfiguration::RAMP_PARAMETER_ASTRO_DC_A = "astro/dc/A";
std::string tlinsConfiguration::RAMP_PARAMETER_ASTRO_DC_D = "astro/dc/D";
std::string tlinsConfiguration::RAMP_PARAMETER_ASTRO_DC_V_MAX = "astro/dc/Vmax";

std::string tlinsConfiguration::RAMP_PARAMETER_GUIDING_RA_A = "guding/ra/A";
std::string tlinsConfiguration::RAMP_PARAMETER_GUIDING_RA_D = "guding/ra/D";
std::string tlinsConfiguration::RAMP_PARAMETER_GUIDING_RA_V_MAX = "guding/ra/Vmax";

std::string tlinsConfiguration::RAMP_PARAMETER_GUIDING_DC_A = "guding/dc/A";
std::string tlinsConfiguration::RAMP_PARAMETER_GUIDING_DC_D = "guding/dc/D";
std::string tlinsConfiguration::RAMP_PARAMETER_GUIDING_DC_V_MAX = "guding/dc/Vmax";

//
// Konfiguracja pilota
//
std::string tlinsConfiguration::PILOT_PARAMETER_GROUP = "pilot-parameters";

std::string tlinsConfiguration::PILOT_PARAMETER_STEPS_X_V = "steps/x/V";
std::string tlinsConfiguration::PILOT_PARAMETER_STEPS_X = "steps/x/X";

std::string tlinsConfiguration::PILOT_PARAMETER_STEPS_Y_V = "steps/y/A";
std::string tlinsConfiguration::PILOT_PARAMETER_STEPS_Y = "steps/y/Y";

std::string tlinsConfiguration::PILOT_PARAMETER_DEGRIS_X_V = "degris/x/V";
std::string tlinsConfiguration::PILOT_PARAMETER_DEGRIS_X = "degris/x/X";

std::string tlinsConfiguration::PILOT_PARAMETER_DEGRIS_Y_V = "degris/y/V";
std::string tlinsConfiguration::PILOT_PARAMETER_DEGRIS_Y = "degris/y/Y";

std::string tlinsConfiguration::PILOT_PARAMETER_ASTRO_RA_V = "astro/ra/V";
std::string tlinsConfiguration::PILOT_PARAMETER_ASTRO_RA = "astro/ra/RA";

std::string tlinsConfiguration::PILOT_PARAMETER_ASTRO_DC_V = "astro/dc/V";
std::string tlinsConfiguration::PILOT_PARAMETER_ASTRO_DC = "astro/dc/DC";

std::string tlinsConfiguration::PILOT_PARAMETER_GUIDING_RA_V = "guding/ra/V";
std::string tlinsConfiguration::PILOT_PARAMETER_GUIDING_RA = "guding/ra/RA";

std::string tlinsConfiguration::PILOT_PARAMETER_GUIDING_DC_V = "guding/dc/V";
std::string tlinsConfiguration::PILOT_PARAMETER_GUIDING_DC = "guding/dc/DC";

//
// Bledy obserwacji
//
std::string tlinsConfiguration::OBSERVATION_ERRORS_GROUP = "observation-errors";
std::string tlinsConfiguration::OBSERVATION_ERRORS_LONGITUDE = "longitude-error";
std::string tlinsConfiguration::OBSERVATION_ERRORS_LATITUDE = "latitude-error";
std::string tlinsConfiguration::OBSERVATION_ERRORS_WEIGHT = "weight";

//
// Parametery kalibracji
//
std::string tlinsConfiguration::CALIBRARION_GROUP = "calibrarion";
std::string tlinsConfiguration::CALIBRARION_MIN_NUMBER_MEASURMENTS = "min-number-measurments";
std::string tlinsConfiguration::CALIBRARION_MIN_NUMBER_REFERENCE_OBJECTS = "min-number-reference-objects";

//
// Parametery skrutów klawiszowych
//
std::string tlinsConfiguration::SHORTCUT_PARAMETER_GROUP = "keyboard-shortcut";
std::string tlinsConfiguration::SHORTCUT_PARAMETER_RADELTA = "ra-delta";
std::string tlinsConfiguration::SHORTCUT_PARAMETER_DECDELTA = "dec-delta";
std::string tlinsConfiguration::SHORTCUT_PARAMETER_RASPEED = "ra-speed";
std::string tlinsConfiguration::SHORTCUT_PARAMETER_DECSPEED = "dec-speed";
std::string tlinsConfiguration::SHORTCUT_PARAMETER_CALIBRATION_OBJECT_ID = "calibration-object-id";
std::string tlinsConfiguration::SHORTCUT_PARAMETER_XDEGRISDELTA = "x-degris-delta";
std::string tlinsConfiguration::SHORTCUT_PARAMETER_YDEGRISDELTA = "y-degris-delta";
std::string tlinsConfiguration::SHORTCUT_PARAMETER_XDEGRISSPEED = "x-degris-speed";
std::string tlinsConfiguration::SHORTCUT_PARAMETER_YDEGRISSPEED = "y-degris-speed";
std::string tlinsConfiguration::SHORTCUT_PARAMETER_XSTEPSDELTA = "x-steps-delta";
std::string tlinsConfiguration::SHORTCUT_PARAMETER_YSTEPSDELTA = "y-steps-delta";
std::string tlinsConfiguration::SHORTCUT_PARAMETER_XSTEPSSPEED = "x-steps-speed";
std::string tlinsConfiguration::SHORTCUT_PARAMETER_YSTEPSSPEED = "y-steps-speed";
std::string tlinsConfiguration::SHORTCUT_PARAMETER_XSCALE = "x-scale";
std::string tlinsConfiguration::SHORTCUT_PARAMETER_YSCALE = "y-scale";
std::string tlinsConfiguration::SHORTCUT_PARAMETER_SPEEDMODE = "speed-mode";
std::string tlinsConfiguration::SHORTCUT_PARAMETER_INSTEPS = "in-steps";

std::string tlinsConfiguration::GUIDER_PARAMETER_GROUP = "guider";
std::string tlinsConfiguration::GUIDER_PARAMETER_RA_RATE = "guider-ra-ratio";
std::string tlinsConfiguration::GUIDER_PARAMETER_DEC_RATE = "guider-dec-ratio";

}
