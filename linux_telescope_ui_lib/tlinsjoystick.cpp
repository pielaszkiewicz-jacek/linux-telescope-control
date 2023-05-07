#include "tlinsjoystick.h"
#include "monitors/tlinsKeysDefinition.hpp"
#include <QDebug>
#include <iomanip>
#include <linux/joystick.h>
#include <sstream>
#include <tlinsBacktrace.hpp>
#include <unordered_map>

namespace TlinsAstroBase {

tlinsJoystick::tlinsJoystick()
    : end { false }
{
    defaultJoystickOpenHandler = nullptr;
    defaultJoystickReleaseHandler = nullptr;
}

void tlinsJoystick::setDefaultHandlers(std::function<void(const keyStatusInfo&)> open_,
    std::function<void(const keyStatusInfo&)> release_)
{
    defaultJoystickOpenHandler = open_;
    defaultJoystickReleaseHandler = release_;
}

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

void tlinsJoystick::addKeyboardCallback(std::vector<int> inkey,
    std::function<void()> fun,
    std::function<void()> funR)
{
    std::unique_lock<std::mutex> lock { mtx };
    std::string key = _buildKey_(inkey);
    {
        auto& l = keyCallbacksSequences[key];
        l.push_back(fun);
    }
    {
        auto& l = keyCallbacksSequencesRelease[key];
        l.push_back(funR);
    }
}

void tlinsJoystick::addEventHandler(std::vector<int> inkey,
    std::function<void(const std::list<keyStatusInfo>&, const keyStatusInfo&)> fun,
    std::function<void(const std::list<keyStatusInfo>&, const keyStatusInfo&)> funRel)
{
    std::unique_lock<std::mutex> lock { mtx };
    std::string key = _buildKey_(inkey);
    {
        auto& l = callbacks[key];
        l.push_back(fun);
    }
    {
        auto& l = callbacksRel[key];
        l.push_back(funRel);
    }
}

static std::string sKey(int t, int v) {
    return std::to_string(t) + ":" + std::to_string(v);
}

static std::map<int, int> joyKeyMap {
    { 292, tlinsKeysDefinition::JOY_PAD_UP },
    { 295, tlinsKeysDefinition::JOY_PAD_LEFT },
    { 293, tlinsKeysDefinition::JOY_PAD_RIGHT },
    { 294, tlinsKeysDefinition::JOY_PAD_DOWN },
    { 288, tlinsKeysDefinition::JOY_KEY_SELECT },
    { 291, tlinsKeysDefinition::JOY_KEY_START },
    { 298, tlinsKeysDefinition::JOY_KEY_L1 },
    { 296, tlinsKeysDefinition::JOY_KEY_L2 },
    { 299, tlinsKeysDefinition::JOY_KEY_R1 },
    { 297, tlinsKeysDefinition::JOY_KEY_R2 },
    { 300, tlinsKeysDefinition::JOY_KEY_1 },
    { 301, tlinsKeysDefinition::JOY_KEY_2 },
    { 302, tlinsKeysDefinition::JOY_KEY_3 },
    { 303, tlinsKeysDefinition::JOY_KEY_4 },
    //    {std::string{"Joy_Main_Left"},  tlinsKeysDefinition::JOY_LPAD      },
    //    {std::string{"Joy_Left_Pad"},   tlinsKeysDefinition::JOY_LPAD      },
    //    {std::string{"Joy_Main_Right"}, tlinsKeysDefinition::JOY_RPAD      },
    //    {std::string{"Joy_Right_Pad"},  tlinsKeysDefinition::JOY_RPAD      }
    { 292, tlinsKeysDefinition::JOY_PAD_UP },
    { 295, tlinsKeysDefinition::JOY_PAD_LEFT },
    { 293, tlinsKeysDefinition::JOY_PAD_RIGHT },
    { 294, tlinsKeysDefinition::JOY_PAD_DOWN },
    { 10, tlinsKeysDefinition::JOY_KEY_SELECT },
    { 11, tlinsKeysDefinition::JOY_KEY_START },
    { 8, tlinsKeysDefinition::JOY_KEY_L1 },
    { 6, tlinsKeysDefinition::JOY_KEY_L2 },
    { 9, tlinsKeysDefinition::JOY_KEY_R1 },
    { 7, tlinsKeysDefinition::JOY_KEY_R2 },
    { 4, tlinsKeysDefinition::JOY_KEY_1 },
    { 1, tlinsKeysDefinition::JOY_KEY_2 },
    { 0, tlinsKeysDefinition::JOY_KEY_3 },
    { 3, tlinsKeysDefinition::JOY_KEY_4 },
};




static std::map<std::string, int> joyKeyMapStr {
    { "_:292", tlinsKeysDefinition::JOY_PAD_UP },
    { "_:295", tlinsKeysDefinition::JOY_PAD_LEFT },
    { "_:293", tlinsKeysDefinition::JOY_PAD_RIGHT },
    { "_:294", tlinsKeysDefinition::JOY_PAD_DOWN },
    { "_:288", tlinsKeysDefinition::JOY_KEY_SELECT },
    { "_:291", tlinsKeysDefinition::JOY_KEY_START },
    { "_:298", tlinsKeysDefinition::JOY_KEY_L1 },
    { "_:296", tlinsKeysDefinition::JOY_KEY_L2 },
    { "_:299", tlinsKeysDefinition::JOY_KEY_R1 },
    { "_:297", tlinsKeysDefinition::JOY_KEY_R2 },
    { "_:300", tlinsKeysDefinition::JOY_KEY_1 },
    { "_:301", tlinsKeysDefinition::JOY_KEY_2 },
    { "_:302", tlinsKeysDefinition::JOY_KEY_3 },
    { "_:303", tlinsKeysDefinition::JOY_KEY_4 },
    //    {std::string{"Joy_Main_Left"},  tlinsKeysDefinition::JOY_LPAD      },
    //    {std::string{"Joy_Left_Pad"},   tlinsKeysDefinition::JOY_LPAD      },
    //    {std::string{"Joy_Main_Right"}, tlinsKeysDefinition::JOY_RPAD      },
    //    {std::string{"Joy_Right_Pad"},  tlinsKeysDefinition::JOY_RPAD      }
    { "1:1000", tlinsKeysDefinition::JOY_PAD_UP },
    { "1:1002", tlinsKeysDefinition::JOY_PAD_LEFT },
    { "1:1003", tlinsKeysDefinition::JOY_PAD_RIGHT },
    { "1:1001", tlinsKeysDefinition::JOY_PAD_DOWN },
    { "1:10", tlinsKeysDefinition::JOY_KEY_SELECT },
    { "1:11", tlinsKeysDefinition::JOY_KEY_START },
    { "2:8", tlinsKeysDefinition::JOY_KEY_L1 },
    { "1:6", tlinsKeysDefinition::JOY_KEY_L2 },
    { "2:9", tlinsKeysDefinition::JOY_KEY_R1 },
    { "1:7", tlinsKeysDefinition::JOY_KEY_R2 },
    { "1:4", tlinsKeysDefinition::JOY_KEY_1 },
    { "1:1", tlinsKeysDefinition::JOY_KEY_2 },
    { "1:0", tlinsKeysDefinition::JOY_KEY_3 },
    { "1:3", tlinsKeysDefinition::JOY_KEY_4 },
};

void tlinsJoystick::eventKeyboard(const int type,
    const int value,
    const int number_)
{
    int number = number_;
    if (joyKeyMap.count(number_) != 0) {
        number = joyKeyMap[number_];
    }

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
        if (iter->code == number)
            break;
    }

    if (iter != sequenceList.end()) {
        iter->stat = s;
        iter->number = number_;
        iter->code = number;
        iter->value = value;
        iter->type = type;
    }

    if (s == keyStatus::RELEASED) {
        if (iter != sequenceList.end()) {
            // Wywolanie callbacka w momencie uwolnienia klawisza
            std::vector<int> result;
            for (auto& item : sequenceList)
                result.push_back(item.code);

            for (auto& cbI : iter->relCallbackToExecute) {
                cbI(sequenceList, *iter);
            }

            // Usuniecie zwalnianego klawisza
            sequenceList.erase(iter);
        }
    } else {
        if (iter == sequenceList.end()) {
            // Wstawienie nowego elementu do listy
            keyStatusInfo v;
            v.number = number_;
            v.code = number;
            v.value = value;
            v.type = type;
            v.stat = s;
            sequenceList.push_back(v);
            iter = sequenceList.begin();
        }

        // Budowanie tablicy rezultatu
        std::vector<int> result;
        for (auto& item : sequenceList)
            result.push_back(item.code);

        std::string key { _buildKey_(result) };
        if (callbacks.count(key) != 0) {
            for (auto& item : callbacks[key]) {
                try {
                    item(sequenceList, *iter);
                } catch (...) {
                }
            }

            // Dodanie zamykajacych
            if (callbacksRel.count(key) != 0) {
                for (auto& item : callbacksRel[key]) {
                    iter->relCallbackToExecute.push_back(item);
                }
            }
        }
    }
}

static std::unordered_map<int, int> joysticMapping = {
    // Lewy pad
    { 0, tlinsKeysDefinition::JOY_LPAD },
    { 1, tlinsKeysDefinition::JOY_LPAD },
    // Prawy pad
    { 2, tlinsKeysDefinition::JOY_RPAD },
    { 3, tlinsKeysDefinition::JOY_RPAD },
};

static std::unordered_map<int, int> axisMapping = {
    // Lewy pad
    { 0, tlinsKeysDefinition::AXIS_X },
    { 1, tlinsKeysDefinition::AXIS_Y },
    // Prawy pad
    { 2, tlinsKeysDefinition::AXIS_X },
    { 3, tlinsKeysDefinition::AXIS_Y },
};

void tlinsJoystick::eventJoystick(const int type,
    const int value,
    const int number_)
{
    // Mapowanie klawisza na znormalizowane numery
    int number = number_;
    int axis = 0;
    if (joysticMapping.count(number_) != 0)
        number = joysticMapping[number_];

    if (axisMapping.count(number_) != 0)
        axis = axisMapping[number_];

    // Odszukanie klawisza/joystika
    auto iter = sequenceList.begin();
    for (; iter != sequenceList.end(); iter++) {
        if (iter->code == number)
            break;
    }

    if (value == 0) {
        if (sequenceList.size() == 0) {
            //
            // Uruchomienie domyslnej funkcji
            //
            if (defaultJoystickReleaseHandler) {
                keyStatusInfo v;
                v.number = number_;
                v.code = number;
                v.value = value;
                v.type = type;
                v.axis = axis;
                v.stat = keyStatus::PRESED;
                defaultJoystickReleaseHandler(v);
            }
        } else if (iter != sequenceList.end()) {
            //
            // Usuniecie zwalnianego klawisza
            //
            iter->number = number_;
            iter->code = number;
            iter->value = value;
            iter->type = type;
            iter->axis = axis;
            iter->stat = keyStatus::RELEASED;

            // Obsluga kombinacji klawisze joystik
            std::vector<int> result;
            for (auto& item : sequenceList)
                result.push_back(item.code);

            std::string key { _buildKey_(result) };
            if (callbacksRel.count(key) != 0) {
                qDebug() << "JOY KEY RELEASE = " << QString::fromStdString(key);
                for (auto& item : callbacksRel[key]) {
                    try {
                        item(sequenceList, *iter);
                    } catch (...) {
                    }
                }
            }
            sequenceList.erase(iter);
        }
    } else {
        if (sequenceList.size() == 0) {
            //
            // Uruchomienie domyslnej funkcji
            //
            if (defaultJoystickOpenHandler) {
                keyStatusInfo v;
                v.number = number_;
                v.code = number;
                v.value = value;
                v.type = type;
                v.axis = axis;
                v.stat = keyStatus::PRESED;
                defaultJoystickOpenHandler(v);
            }
        } else if (iter == sequenceList.end()) {
            // Dodanie do listy gdy nie ma
            keyStatusInfo v;
            v.number = number_;
            v.code = number;
            v.value = value;
            v.type = type;
            v.axis = axis;
            v.stat = keyStatus::PRESED;
            sequenceList.push_back(v);

            // Odszukanie klawisza/joystika
            iter = sequenceList.begin();
            for (; iter != sequenceList.end(); iter++) {
                if (iter->code == number)
                    break;
            }
        } else {
            // Aktualizacja statusu i wartosci
            iter->number = number_;
            iter->code = number;
            iter->value = value;
            iter->type = type;
            iter->axis = axis;
            iter->stat = keyStatus::REPEAT;
        }

        {
            // Obsluga kombinacji klawisze joystik
            std::vector<int> result;
            for (auto& item : sequenceList)
                result.push_back(item.code);

            std::string key { _buildKey_(result) };
            if (callbacks.count(key) != 0) {
                for (auto& item : callbacks[key]) {
                    try {
                        item(sequenceList, *iter);
                    } catch (...) {
                    }
                }
            }
        }
    }
}

std::mutex mtxSync;

void tlinsJoystick::event(const int type, const int value, const int number)
{
    qDebug() << "TYPE = " << type << "; VALUE = " << value << "; NUMBER =" << number;

    std::unique_lock<std::mutex> lock(mtxSync);
    switch (type) {
    case JS_EVENT_BUTTON:
        eventKeyboard(type, value, number);
        break;

    case JS_EVENT_AXIS:
        eventJoystick(type, value, number);
        break;

    case JS_EVENT_INIT:
        break;
    }
}

tlinsJoystick::~tlinsJoystick()
{
}

}
