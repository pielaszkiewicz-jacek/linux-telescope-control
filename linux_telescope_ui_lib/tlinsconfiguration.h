#ifndef TLINSCONFIGURATION_H
#define TLINSCONFIGURATION_H

#include <map>
#include <memory>
#include <mutex>
#include <string>

class QSettings;

namespace TlinsAstroBase {

class tlinsConfiguration {
public:
    //
    // Ogolne parametery
    //
    static std::string COMMON_PARAMETER_GROUP;
    static std::string COMMON_MAIN_DEVICE_NAME;

    //
    // Parametery rampy
    //
    static std::string RAMP_PARAMETER_GROUP;

    static std::string RAMP_PARAMETER_STEPS_X_A;
    static std::string RAMP_PARAMETER_STEPS_X_D;
    static std::string RAMP_PARAMETER_STEPS_X_V_MAX;

    static std::string RAMP_PARAMETER_STEPS_Y_A;
    static std::string RAMP_PARAMETER_STEPS_Y_D;
    static std::string RAMP_PARAMETER_STEPS_Y_V_MAX;

    static std::string RAMP_PARAMETER_DEGRIS_X_A;
    static std::string RAMP_PARAMETER_DEGRIS_X_D;
    static std::string RAMP_PARAMETER_DEGRIS_X_V_MAX;

    static std::string RAMP_PARAMETER_DEGRIS_Y_A;
    static std::string RAMP_PARAMETER_DEGRIS_Y_D;
    static std::string RAMP_PARAMETER_DEGRIS_Y_V_MAX;

    static std::string RAMP_PARAMETER_ASTRO_RA_A;
    static std::string RAMP_PARAMETER_ASTRO_RA_D;
    static std::string RAMP_PARAMETER_ASTRO_RA_V_MAX;

    static std::string RAMP_PARAMETER_ASTRO_DC_A;
    static std::string RAMP_PARAMETER_ASTRO_DC_D;
    static std::string RAMP_PARAMETER_ASTRO_DC_V_MAX;

    static std::string RAMP_PARAMETER_GUIDING_RA_A;
    static std::string RAMP_PARAMETER_GUIDING_RA_D;
    static std::string RAMP_PARAMETER_GUIDING_RA_V_MAX;

    static std::string RAMP_PARAMETER_GUIDING_DC_A;
    static std::string RAMP_PARAMETER_GUIDING_DC_D;
    static std::string RAMP_PARAMETER_GUIDING_DC_V_MAX;

    //
    // Parametery pilota
    //
    static std::string PILOT_PARAMETER_GROUP;

    static std::string PILOT_PARAMETER_STEPS_X_V;
    static std::string PILOT_PARAMETER_STEPS_X;

    static std::string PILOT_PARAMETER_STEPS_Y_V;
    static std::string PILOT_PARAMETER_STEPS_Y;

    static std::string PILOT_PARAMETER_DEGRIS_X_V;
    static std::string PILOT_PARAMETER_DEGRIS_X;

    static std::string PILOT_PARAMETER_DEGRIS_Y_V;
    static std::string PILOT_PARAMETER_DEGRIS_Y;

    static std::string PILOT_PARAMETER_ASTRO_RA_V;
    static std::string PILOT_PARAMETER_ASTRO_RA;

    static std::string PILOT_PARAMETER_ASTRO_DC_V;
    static std::string PILOT_PARAMETER_ASTRO_DC;

    static std::string PILOT_PARAMETER_GUIDING_RA_V;
    static std::string PILOT_PARAMETER_GUIDING_RA;

    static std::string PILOT_PARAMETER_GUIDING_DC_V;
    static std::string PILOT_PARAMETER_GUIDING_DC;

    //
    // Parametery polaczen
    //
    static std::string CONNECTION_PARAMETER_GROUP;
    static std::string CONNECTION_PARAMETER_CONNECT_SYSTEM_EVENT_MONITOR;
    static std::string CONNECTION_PARAMETER_URL_ASTRO_ENGINE;
    static std::string CONNECTION_PARAMETER_URL_ASTRO_ENGINE_AUTH;
    static std::string CONNECTION_PARAMETER_URL_DEVICE_ENGINE;
    static std::string CONNECTION_PARAMETER_URL_DEVICE_ENGINE_AUTH;
    static std::string CONNECTION_PARAMETER_URL_ASTRO_ENGINE_ASYNCH;
    static std::string CONNECTION_PARAMETER_URL_ASTRO_ENGINE_ASYNCH_AUTH;
    static std::string CONNECTION_PARAMETER_URL_DEVICE_ENGINE_ASYNCH;
    static std::string CONNECTION_PARAMETER_URL_DEVICE_ENGINE_ASYNCH_AUTH;
    static std::string CONNECTION_PARAMETER_URL_SYSTEM_SERVICE;
    static std::string CONNECTION_PARAMETER_URL_SYSTEM_SERVICE_AUTH;

    // Wspolny adress
    static std::string CONNECTION_PARAMETER_URL_ASTRO_ENGINE_PORT;
    static std::string CONNECTION_PARAMETER_URL_DEVICE_ENGINE_PORT;
    static std::string CONNECTION_PARAMETER_URL_ASTRO_ENGINE_ASYNCH_PORT;
    static std::string CONNECTION_PARAMETER_URL_DEVICE_ENGINE_ASYNCH_PORT;
    static std::string CONNECTION_PARAMETER_URL_SYSTEM_SERVICE_PORT;
    static std::string CONNECTION_PARAMETER_URL_COMMON_ADDRESS_IP;
    static std::string CONNECTION_PARAMETER_URL_USE_COMMON_ADDRESS;

    //
    // Baza danych
    //
    static std::string DATABASE_GROUP;
    static std::string DATABASE_FILE;
    static std::string DATABASE_TYPE;
    static std::string DATABASE_CONNECTION_NAME;
    static std::string DATABASE_HOST;
    static std::string DATABASE_USER;
    static std::string DATABASE_PASSWORD;

    // Bledy obserwacji
    static std::string OBSERVATION_ERRORS_GROUP;
    static std::string OBSERVATION_ERRORS_LONGITUDE;
    static std::string OBSERVATION_ERRORS_LATITUDE;
    static std::string OBSERVATION_ERRORS_WEIGHT;

    // Parametery kalibracji
    static std::string CALIBRARION_GROUP;
    static std::string CALIBRARION_MIN_NUMBER_MEASURMENTS;
    static std::string CALIBRARION_MIN_NUMBER_REFERENCE_OBJECTS;

    //
    // Parametery skrutow klawiszowych
    //
    static std::string SHORTCUT_PARAMETER_GROUP;
    static std::string SHORTCUT_PARAMETER_RADELTA;
    static std::string SHORTCUT_PARAMETER_DECDELTA;
    static std::string SHORTCUT_PARAMETER_RASPEED;
    static std::string SHORTCUT_PARAMETER_DECSPEED;
    static std::string SHORTCUT_PARAMETER_CALIBRATION_OBJECT_ID;
    static std::string SHORTCUT_PARAMETER_XDEGRISDELTA;
    static std::string SHORTCUT_PARAMETER_YDEGRISDELTA;
    static std::string SHORTCUT_PARAMETER_XDEGRISSPEED;
    static std::string SHORTCUT_PARAMETER_YDEGRISSPEED;
    static std::string SHORTCUT_PARAMETER_XSTEPSDELTA;
    static std::string SHORTCUT_PARAMETER_YSTEPSDELTA;
    static std::string SHORTCUT_PARAMETER_XSTEPSSPEED;
    static std::string SHORTCUT_PARAMETER_YSTEPSSPEED;
    static std::string SHORTCUT_PARAMETER_XSCALE;
    static std::string SHORTCUT_PARAMETER_YSCALE;
    static std::string SHORTCUT_PARAMETER_SPEEDMODE;
    static std::string SHORTCUT_PARAMETER_INSTEPS;

//
// Parametery guidera
//
static std::string GUIDER_PARAMETER_GROUP;
static std::string GUIDER_PARAMETER_RA_RATE;
    static std::string GUIDER_PARAMETER_DEC_RATE;

private:
    // Muteks synchronizujacy dostep do bazy konfiguracji
    std::recursive_mutex mtx;

    std::shared_ptr<QSettings> settings;

    std::map<std::string, double> doubleMap;
    std::map<std::string, int> intMap;
    std::map<std::string, std::string> stringMap;

    std::string createKey(const std::string& group, const std::string& key)
    {
        return group + "::" + key;
    }

    bool hasKeyDouble(const std::string& group, const std::string& key)
    {
        auto idx = createKey(group, key);

        if (doubleMap.count(idx) == 0)
            return false;
        return true;
    }

    void setKeyDouble(const std::string& group, const std::string& key, const double v)
    {
        auto idx = createKey(group, key);
        doubleMap[idx] = v;
    }

    bool getKeyDouble(const std::string& group, const std::string& key, double& out)
    {
        auto idx = createKey(group, key);
        if (hasKeyDouble(group, key)) {
            out = doubleMap[idx];
            return true;
        }
        return false;
    }

    bool hasKeyInt(const std::string& group, const std::string& key)
    {
        auto idx = createKey(group, key);

        if (intMap.count(idx) == 0)
            return false;
        return true;
    }

    void setKeyInt(const std::string& group, const std::string& key, const int v)
    {
        auto idx = createKey(group, key);
        intMap[idx] = v;
    }

    bool getKeyInt(const std::string& group, const std::string& key, int& out)
    {
        auto idx = createKey(group, key);
        if (hasKeyInt(group, key)) {
            out = intMap[idx];
            return true;
        }
        return false;
    }

    bool hasKeyString(const std::string& group, const std::string& key)
    {
        auto idx = createKey(group, key);

        if (stringMap.count(idx) == 0)
            return false;
        return true;
    }

    void setKeyString(const std::string& group, const std::string& key, const std::string& v)
    {
        auto idx = createKey(group, key);
        stringMap[idx] = v;
    }

    bool getKeyString(const std::string& group, const std::string& key, std::string& out)
    {
        auto idx = createKey(group, key);
        if (hasKeyString(group, key)) {
            out = stringMap[idx];
            return true;
        }
        return false;
    }

public:
    static tlinsConfiguration& getInstance();

    void setValueFile(const std::string& group, const std::string& key, const double v);
    void setValueFile(const std::string& group, const std::string& key, const int v);
    void setValueFile(const std::string& group, const std::string& key, const long v);
    void setValueFile(const std::string& group, const std::string& key, const std::string& v);
    bool hasKeyFile(const std::string& group, const std::string& key);

    void setValue(const std::string& group, const std::string& key, const double v);
    void setValue(const std::string& group, const std::string& key, const int v);
    void setValue(const std::string& group, const std::string& key, const long v);
    void setValue(const std::string& group, const std::string& key, const std::string& v);
    bool hasKey(const std::string& group, const std::string& key);

    std::string getString(const std::string& group, const std::string& key);
    double getDouble(const std::string& group, const std::string& key);
    long getLong(const std::string& group, const std::string& key);
    int getInt(const std::string& group, const std::string& key);

    std::string getStringFile(const std::string& group, const std::string& key);
    double getDoubleFile(const std::string& group, const std::string& key);
    long getLongFile(const std::string& group, const std::string& key);
    int getIntFile(const std::string& group, const std::string& key);

private:
    tlinsConfiguration();

public:
    virtual ~tlinsConfiguration();
};

}

#endif // TLINSCONFIGURATION_H
