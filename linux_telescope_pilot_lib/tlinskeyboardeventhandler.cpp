#include "tlinskeyboardeventhandler.h"
#include <monitors/tlinsKeysDefinition.hpp>
#include <tlinsBacktrace.hpp>
#include <tlinsSystemServiceClient.hpp>
#include <tlinsuidatabase.h>
#include <tlinsuidatabasedefinition.h>

#include "tlinsshortcutsmanager.h"

#include <QtDebug>
#include <functional>
#include <memory>
#include <regex>

namespace tlinsAstroPilot {

void tlinsKeyboardEventHandler ::operator()(const tlinsSystemServiceClient ::Event& event)
{
    // Przetwarzanie zdarzenia
    keyboardMapper.event(static_cast<unsigned int>(event.keyId), static_cast<unsigned short>(event.keyStatus));
}

static void convertIntoNumbers(const std ::vector<std ::string> in, std ::vector<int>& out)
{
    // Mapowanie do poprawy
    std ::map<std ::string, int> kmap {
        { "UP", tlinsKeysDefinition ::KEY_UP }, // W
        { "LEFT", tlinsKeysDefinition ::KEY_LEFT }, // A
        { "OK", tlinsKeysDefinition ::KEY_OK }, // X
        { "RIGHT", tlinsKeysDefinition ::KEY_RIGHT }, // S
        { "DOWN", tlinsKeysDefinition ::KEY_DOWN }, // Z
        { "F01", tlinsKeysDefinition ::KEY_F01 }, // P
        { "F02", tlinsKeysDefinition ::KEY_F02 }, // O
        { "F11", tlinsKeysDefinition ::KEY_F11 }, // I
        { "F13", tlinsKeysDefinition ::KEY_F13 }, // D
        { "F14", tlinsKeysDefinition ::KEY_F14 }, // C
        { "F12", tlinsKeysDefinition ::KEY_F12 }, // T
        { "F21", tlinsKeysDefinition ::KEY_F21 }, // L
        { "F22", tlinsKeysDefinition ::KEY_F22 }, // K
        { "F23", tlinsKeysDefinition ::KEY_F23 }, // K
        { "F24", tlinsKeysDefinition ::KEY_F24 }, // J
        { "F34", tlinsKeysDefinition ::KEY_F31 }, // H
        { "F33", tlinsKeysDefinition ::KEY_F33 }, // G
        { "F32", tlinsKeysDefinition ::KEY_F32 }, // F
        { "F31", tlinsKeysDefinition ::KEY_F34 }
    }; // D

    for (auto& inIter : in) {
        if (kmap.count(inIter) != 0)
            out.push_back(kmap[inIter]);
    }
}

void tlinsKeyboardEventHandler ::applayConfiguration()
{
    TlinsAstroBase ::tlinsUIDatabase db;
    TlinsAstroBase ::tlinsUIDatabaseDefinition dbDef(db);

    std ::vector<TlinsAstroBase ::tlinsKeysSortcut> data;
    dbDef.selectShortcuts(data, TlinsAstroBase ::tlinsKeysSortcutType ::KEYBOARD);

    for (auto& item : data) {
        // Sekwencja klawiszy
        std ::vector<std ::string> keys;
        item.getActionKeys(keys);

        // Konfiguracja
        std ::string cfgJson { item.getActionSettingsJson() };

        // Nazwa skrotu klawiszowego
        std ::string shortcutName { item.getShortcutName() };

        // Nazwa akcji
        std ::string actionName { item.getActionName() };

        qDebug() << "Configuration : " << QString ::fromStdString(cfgJson);
        qDebug() << "Name          : " << QString ::fromStdString(shortcutName);
        qDebug() << "Action        : " << QString ::fromStdString(actionName);

        TlinsAstroBase ::tlinsPilotShortcutsDefinitionValidMode mode = item.getActionMode();

        // Pobranie fabryki
        auto& factoryInstance = tlinsShortcutsFactoriesManager ::getInstance();
        auto factory = factoryInstance.getFactory(actionName);
        if (!factory) {
            // Brak fabryki
            qDebug() << "No factory for " << QString ::fromStdString(actionName);
            TLINS_LOG_ERROR("№ factory for " + actionName);
            continue;
        }

        // Rejestracja nowego callbacka
        std ::vector<int> numKeys;
        convertIntoNumbers(keys, numKeys);

        // Tworzenie instancji przez fabryke
        auto shortCutInstance = factory->createInstance(TlinsAstroBase ::tlinsKeysSortcutType ::KEYBOARD,
            TlinsAstroBase ::tlinsKeysSortcutSubType ::ANY,
            shortcutName,
            cfgJson,
            mode,
            numKeys);
        if (!shortCutInstance) {
            TLINS_LOG_ERROR("Error create shortcut instance for " + actionName);
            continue;
        }

        // Rejestracja w managerze
        tlinsShortcutsManager ::getInstance().addShortcut(shortCutInstance);

        std::function<void()> fun = [shortCutInstance] { shortCutInstance->callback(); };
        std::function<void()> funRelease = [shortCutInstance] { shortCutInstance->release(); };
        keyboardMapper.addCallback(shortCutInstance->getKeys(), fun, funRelease);
    }
}

tlinsKeyboardEventHandler ::tlinsKeyboardEventHandler(std ::shared_ptr<grpc ::Channel>& channel)
{
    using namespace std::placeholders;

    // Rejestracja obiektu nasluchujacego na zdarzenia z klawiatury
    std ::vector<tlinsSystemServiceClient ::EventType> evs { tlinsSystemServiceClient ::EventType ::KEYBOARD };
    tlinsSystemServiceClient* ptr = new tlinsSystemServiceClient(channel, evs, std::bind(&tlinsKeyboardEventHandler::operator(), this, _1));
    eventsReader = std ::move(std ::unique_ptr<tlinsSystemServiceClient> { ptr });

    // Rejestracja zdefiniowanych skrotow klawiszowych
    applayConfiguration();
}

tlinsKeyboardEventHandler ::~tlinsKeyboardEventHandler()
{
}

};
