#ifndef TLINSUPDATESTATEMANAGER_H
#define TLINSUPDATESTATEMANAGER_H

#include <functional>
#include <map>
#include <mutex>
#include <tlinsBacktrace.hpp>
#include <tlinsLogger.hpp>

#define UPDATE_CATEGORY_ASTRO_STATUS \
    std::string { "__ASTRO_STAT__" }

namespace TlinsAstroBase {

template <typename T>
class tlinsUpdateStateManager {
private:
    std::map<std::string, std::map<int, std::function<void(const T&)>>> objects;
    std::mutex mtx;

public:
    int registerObject(const std::string& category, std::function<void(const T&)> object)
    {
        static int id = 0;
        static std::mutex mtxi;

        {
            std::lock_guard<std::mutex> lock(mtxi);
            id++;
        }

        std::lock_guard<std::mutex> lock(mtx);
        objects[category][id] = object;
        return id;
    }

    bool unregisterObject(const std::string& category, const int id)
    {
        std::lock_guard<std::mutex> lock(mtx);

        if (objects.find(category) == objects.end())
            return false;

        if (objects[category].find(id) == objects[category].end())
            return false;

        objects[category].erase(id);

        return true;
    }

    // Aktualizuje zarejestrowane obiekty
    void update(const std::string& category, const T& status)
    {
        std::lock_guard<std::mutex> lock(mtx);

        if (objects.find(category) == objects.end())
            return;

        for (auto& item : objects[category])
            item.second(status);
    }

    static tlinsUpdateStateManager& getInstance()
    {
        static tlinsUpdateStateManager instance {};
        return instance;
    }

private:
    tlinsUpdateStateManager()
    {
    }

public:
    virtual ~tlinsUpdateStateManager()
    {
    }
};

}

#endif // TLINSUPDATESTATEMANAGER_H
