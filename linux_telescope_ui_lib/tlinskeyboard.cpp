#include "tlinskeyboard.h"
#include "tlinsuiexception.h"
#include <fcntl.h>
#include <iomanip>
#include <linux/input-event-codes.h>
#include <memory>
#include <sstream>
#include <sys/stat.h>
#include <sys/types.h>
#include <tlinsBacktrace.hpp>
#include <unistd.h>
#include <vector>

#include <QDebug>

namespace TlinsAstroBase {

void tlinsKeyboard::openDevice(const std::string& devName)
{
    // Sprawdzenie pliku urzadzenia
    struct stat buf;
    if (::stat(devName.c_str(), &buf) < 0) {
        throw TlinsAstroBase::tlinsUIException { TlinsAstroBase::tlinsUIException::ERROR_INVALID_FILE_PATH,
            std::string { "Error open device file: " } + devName };
    }

    fd = ::open(devName.c_str(), O_RDONLY);
    if (fd < 0) {
        throw TlinsAstroBase::tlinsUIException { TlinsAstroBase::tlinsUIException::ERROR_IO,
            std::string { "Error open file: " } + devName };
    }
}

struct input_event {
    struct timeval time;
    unsigned short type;
    unsigned short code;
    unsigned int value;
};

static std::string _buildKey_(const std::vector<int> v)
{
    // Budowanie klucza sekwencji
    std::string outKey;
    for (auto& item : v) {
        std::ostringstream keys;
        keys << std::setw(5) << item << "::";
        outKey += keys.str();
    }
    return outKey;
}

void tlinsKeyboard::addCallback(int key,
    std::function<void(int, keyStatus)> fun)
{
    std::unique_lock<std::mutex> lock { mtx };
    auto& l = callbacks[key];
    l.push_back(fun);
}

void tlinsKeyboard::addCallback(int key,
    std::function<void(int, keyStatus)> fun,
    std::function<void(int, keyStatus)> funR)
{
    std::unique_lock<std::mutex> lock { mtx };
    {
        auto& l = callbacks[key];
        l.push_back(fun);
    }

    {
        auto& l = callbacksRelease[key];
        l.push_back(funR);
    }
}

void tlinsKeyboard::addCallback(std::vector<int> inkey,
    std::function<void()> fun)
{
    std::unique_lock<std::mutex> lock { mtx };

    std::string key = _buildKey_(inkey);
    auto& l = callbacksSequences[key];
    l.push_back(fun);
}

void tlinsKeyboard::addCallback(std::vector<int> inkey,
    std::function<void()> fun,
    std::function<void()> funR)
{
    std::unique_lock<std::mutex> lock { mtx };
    {
        std::string key = _buildKey_(inkey);
        auto& l = callbacksSequences[key];
        l.push_back(fun);
    }

    {
        std::string key = _buildKey_(inkey);
        auto& l = callbacksSequencesRelease[key];
        l.push_back(funR);
    }
}

tlinsKeyboard::tlinsKeyboard()
    : end { false }
    , fd { -1 }
{
    fd = -1;
}

void tlinsKeyboard::event(const unsigned short code,
    const unsigned int value)
{
    // Status klawisza
    keyStatus s = keyStatus::RELEASED;
    switch (value) {
    case 0:
        s = keyStatus::RELEASED;
        break;
    case 1:
        s = keyStatus::PRESED;
        break;
    case 2:
        s = keyStatus::REPEAT;
        break;
    }

    // Odszukanie klawisza
    auto iter = sequenceList.begin();
    for (; iter != sequenceList.end(); iter++) {
        if (iter->code == code)
            break;
    }

    if (iter == sequenceList.end()) {
        // Wstawienie nowego elementu do listy
        keyStatusInfo v;
        v.code = code;
        v.stat = s;
        sequenceList.push_back(v);
    } else {
        // Modyfikacja statusu lub usuniecie z listy
        if (s == keyStatus::RELEASED) {
            // Wywolanie callbacka w momencie uwolnienia klawisza
            std::vector<int> result;
            for (auto& item : sequenceList)
                result.push_back(item.code);

            std::string key { _buildKey_(result) };
            if (callbacksSequencesRelease.count(key) != 0) {
                //				qDebug() << "KEY Release = " << QString:: fromStdString( key );
                for (auto& item : callbacksSequencesRelease[key]) {
                    try {
                        item();
                    } catch (...) {
                    }
                }
            }

            // Usuniecie zwalnianego klawisza
            sequenceList.erase(iter);
        } else {
            iter->stat = s;
        }
    }

    // Budowanie tablicy rezultatu
    std::vector<int> result;
    for (auto& item : sequenceList)
        result.push_back(item.code);

    std::string key { _buildKey_(result) };
    if (callbacksSequences.count(key) != 0) {
        //		qDebug() << "KEY PRESED = " << QString:: fromStdString( key );
        for (auto& item : callbacksSequences[key]) {
            try {
                item();
            } catch (...) {
            }
        }
    }

    //
    // Obsluga pojedynczych klawiszy
    //
    if (s != keyStatus::RELEASED) {
        // Wcisniecie lub powtorzenie klawisza
        auto& list = callbacks[code];
        for (auto& item : list) {
            try {
                item(code, s);
            } catch (...) {
            }
        }
    } else {
        // Puszczenie klawisza
        auto& list = callbacksRelease[code];
        for (auto& item : list) {
            try {
                item(code, s);
            } catch (...) {
            }
        }
    }
}

tlinsKeyboard::tlinsKeyboard(const std::string& devName)
    : end { false }
{
    // Otwarcie pliku urzadzenia
    openDevice(devName);

    auto fun = [this]() {
        while (!end) {
            // Czytanie urzadzenia wejsciowego
            struct input_event ev;
            auto res = ::read(this->fd, reinterpret_cast<void*>(&ev), sizeof(struct input_event));
            if (res <= 0)
                continue;

            // Tylko klawiatura. Inne zdarzenia beda ignorowane
            if (ev.type != EV_KEY)
                continue;

            // Status klawisza
            keyStatus s;
            switch (ev.value) {
            case 1:
                s = keyStatus::PRESED;
                break;
            case 2:
                s = keyStatus::REPEAT;
                break;
            case 0:
                s = keyStatus::RELEASED;
                break;
            }

            //
            // Obsluga sekewncji klawiszy
            //

            // Odszukanie klawisza
            auto iter = sequenceList.begin();
            for (; iter != sequenceList.end(); iter++) {
                if (iter->code == ev.code)
                    break;
            }

            if (iter == sequenceList.end()) {
                // Wstawienie nowego elementu do listy
                keyStatusInfo v;
                v.code = ev.code;
                v.stat = s;
                sequenceList.push_back(v);
            } else {
                // Modyfikacja statusu lub usuniecie z listy
                if (s == keyStatus::RELEASED)
                    sequenceList.erase(iter);
                else
                    iter->stat = s;
            }

            // Budowanie tablicy rezultatu
            std::vector<int> result;
            for (auto& item : sequenceList)
                result.push_back(item.code);

            std::string key { _buildKey_(result) };
            if (callbacksSequences.count(key) != 0) {
                for (auto& item : callbacksSequences[key]) {
                    try {
                        item();
                    } catch (...) {
                    }
                }
            }

            //
            // Obsluga pojedynczych klawiszy
            //
            auto& list = callbacks[ev.code];
            for (auto& item : list) {
                try {
                    item(ev.code, s);
                } catch (...) {
                }
            }
        }
    };

    th = std::move(std::thread { fun });
}

tlinsKeyboard::~tlinsKeyboard()
{
    end = true;

    if (fd >= 0)
        ::close(fd);

    if (th.joinable())
        th.join();
}

}
