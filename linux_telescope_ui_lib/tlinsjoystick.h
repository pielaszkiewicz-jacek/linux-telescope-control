#ifndef TLINSJOYSTICK_H
#define TLINSJOYSTICK_H

#include <atomic>
#include <functional>
#include <list>
#include <map>
#include <mutex>
#include <thread>
#include <vector>

namespace TlinsAstroBase {

class tlinsJoystick {
public:
    enum class keyStatus {
        PRESED = 1,
        RELEASED = 2,
        REPEAT = 3
    };

    struct keyStatusInfo {
        int type;
        int code;
        int number;
        int value;
        int axis;
        keyStatus stat;

        std::list<std::function<void(const std::list<keyStatusInfo>&, const keyStatusInfo&)>> relCallbackToExecute;

        keyStatusInfo() = default;

        keyStatusInfo& operator=(const keyStatusInfo& v)
        {
            value = v.value;
            number = v.number;
            code = v.code;
            stat = v.stat;
            type = v.type;
            relCallbackToExecute = v.relCallbackToExecute;
            return *this;
        }

        keyStatusInfo(const keyStatusInfo& v)
        {
            number = v.number;
            value = v.value;
            code = v.code;
            stat = v.stat;
            type = v.type;
            relCallbackToExecute = v.relCallbackToExecute;
        }

        ~keyStatusInfo() = default;
    };

private:
    std::atomic<bool> end;
    std::thread th;

    // Lista obslugi zdarzen typu sekwencja klawiszy np. ALT+R
    std::map<std::string, std::list<std::function<void()>>> keyCallbacksSequences;
    std::map<std::string, std::list<std::function<void()>>> keyCallbacksSequencesRelease;

    // Mapa calbackow nowa
    std::map<std::string, std::list<std::function<void(const std::list<keyStatusInfo>&, const keyStatusInfo&)>>> callbacks;
    std::map<std::string, std::list<std::function<void(const std::list<keyStatusInfo>&, const keyStatusInfo&)>>> callbacksRel;

    std::function<void(const keyStatusInfo&)> defaultJoystickOpenHandler;
    std::function<void(const keyStatusInfo&)> defaultJoystickReleaseHandler;

    std::mutex mtx;

    std::list<keyStatusInfo> sequenceList;

    void eventKeyboard(const int type,
        const int value,
        const int number);

    void eventJoystick(const int type,
        const int value,
        const int number);

public:
    void event(const int type,
        const int value,
        const int number);

    void setDefaultHandlers(std::function<void(const keyStatusInfo&)> open_,
        std::function<void(const keyStatusInfo&)> release_);

    void addEventHandler(std::vector<int> key,
        std::function<void(const std::list<keyStatusInfo>&, const keyStatusInfo&)> fun,
        std::function<void(const std::list<keyStatusInfo>&, const keyStatusInfo&)> funRel);

    // Dodanie callbacka klawisz
    void addKeyboardCallback(std::vector<int> key,
        std::function<void()> fun,
        std::function<void()> Rel);

    tlinsJoystick();
    virtual ~tlinsJoystick();
};

}

#endif // TLINSJOYSTICK_H
