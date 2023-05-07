#ifndef TLINSKEYBOARD_H
#define TLINSKEYBOARD_H

#include <atomic>
#include <functional>
#include <list>
#include <map>
#include <mutex>
#include <string>
#include <thread>
#include <vector>

namespace TlinsAstroBase {

class tlinsKeyboard {
public:
    enum class keyStatus {
        PRESED = 1,
        RELEASED = 2,
        REPEAT = 3
    };

private:
    std::atomic<bool> end;
    int fd;
    std::thread th;
    // Lista obslugi zdarzen typu pojedynczy klawisz
    std::map<int, std::list<std::function<void(int, keyStatus)>>> callbacks;
    std::map<int, std::list<std::function<void(int, keyStatus)>>> callbacksRelease;

    // Lista obslugi zdarzen typu sekwencja klawiszy np. ALT+R
    std::map<std::string, std::list<std::function<void()>>> callbacksSequences;
    std::map<std::string, std::list<std::function<void()>>> callbacksSequencesRelease;
    std::mutex mtx;

    struct keyStatusInfo {
        int code;
        keyStatus stat;

        keyStatusInfo() = default;

        keyStatusInfo& operator=(const keyStatusInfo& v)
        {
            code = v.code;
            stat = v.stat;
            return *this;
        }

        keyStatusInfo(const keyStatusInfo& v)
        {
            code = v.code;
            stat = v.stat;
        }

        ~keyStatusInfo()
        {
        }
    };

    std::list<keyStatusInfo> sequenceList;

private:
    void openDevice(const std::string& devName);

public:
    void event(const unsigned short code,
        const unsigned int value);

    void addCallback(int key,
        std::function<void(int, keyStatus)> fun);
    void addCallback(int key,
        std::function<void(int, keyStatus)> fun,
        std::function<void(int, keyStatus)> funR);
    void addCallback(std::vector<int> key,
        std::function<void()> fun);
    void addCallback(std::vector<int> key,
        std::function<void()> fun,
        std::function<void()> funR);

public:
    tlinsKeyboard();
    tlinsKeyboard(const std::string& devName);

    virtual ~tlinsKeyboard();
};

}

#endif // TLINSKEYBOARD_H
