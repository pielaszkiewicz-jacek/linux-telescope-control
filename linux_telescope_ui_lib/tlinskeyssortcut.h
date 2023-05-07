#ifndef TLINSKEYSSORTCUT_H
#define TLINSKEYSSORTCUT_H

#include "tlinspilotshortcutsdefinitionvalidmode.h"
#include <string>
#include <vector>

namespace TlinsAstroBase {

enum class tlinsKeysSortcutType {
    KEYBOARD = 1,
    JOYSTICK = 2
};

enum class tlinsKeysSortcutSubType {
    JOYSTICK_KEYS = 1,
    JOYSTICK_GAMEPAD = 2,
    ANY = 3
};

enum class tlinsDefaultHandler {
    NO = 0,
    YES = 1
};

class tlinsKeysSortcut {
private:
    std::string shortcutName;
    std::string actionName;
    std::string actionKeys;
    std::string actionSettingsJson;
    tlinsDefaultHandler defaultHandler;
    tlinsKeysSortcutSubType subType;
    tlinsKeysSortcutType type;
    TlinsAstroBase::tlinsPilotShortcutsDefinitionValidMode actionMode;

public:
    tlinsKeysSortcut& operator=(const tlinsKeysSortcut& v) = default;
    tlinsKeysSortcut(const tlinsKeysSortcut& v) = default;

    tlinsKeysSortcutSubType getSubType() const;
    tlinsKeysSortcutType getType() const;

    std::string getShortcutName() const;
    std::string getActionSettingsJson() const;
    std::string getActionKeys() const;
    void getActionKeys(std::vector<std::string>& keys) const;
    std::string getActionName() const;
    TlinsAstroBase::tlinsPilotShortcutsDefinitionValidMode getActionMode() const;

    tlinsDefaultHandler getDefaultHandler() const;
    void setDefaultHandler(const tlinsDefaultHandler& v);

    void setSubType(const tlinsKeysSortcutSubType v);
    void setType(const tlinsKeysSortcutType v);

    void setAhortcutName(const std::string& v);
    void setActionSettingsJson(const std::string& v);
    void setActionKeys(const std::string& v);
    void setActionKeys(const std::vector<std::string>& v);
    void setActionName(const std::string& v);
    void setActionMode(const TlinsAstroBase::tlinsPilotShortcutsDefinitionValidMode v);

    tlinsKeysSortcut();
    virtual ~tlinsKeysSortcut();
};

}

#endif // TLINSKEYSSORTCUT_H
