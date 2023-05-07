#include "tlinskeyssortcut.h"
#include <regex>

#include "tlinspilotshortcutsdefinitioninterface.h"

namespace TlinsAstroBase {

tlinsKeysSortcut::tlinsKeysSortcut()
{
}

tlinsKeysSortcut::~tlinsKeysSortcut()
{
}

std::string tlinsKeysSortcut::getShortcutName() const
{
    return shortcutName;
}

std::string tlinsKeysSortcut::getActionSettingsJson() const
{
    return actionSettingsJson;
}

std::string tlinsKeysSortcut::getActionKeys() const
{
    return actionKeys;
}

tlinsKeysSortcutSubType tlinsKeysSortcut::getSubType() const
{
    return subType;
}

tlinsKeysSortcutType tlinsKeysSortcut::getType() const
{
    return type;
}

tlinsDefaultHandler tlinsKeysSortcut::getDefaultHandler() const
{
    return defaultHandler;
}

void tlinsKeysSortcut::setDefaultHandler(const tlinsDefaultHandler& v)
{
    defaultHandler = v;
}

void tlinsKeysSortcut::setSubType(const tlinsKeysSortcutSubType v)
{
    subType = v;
}

void tlinsKeysSortcut::setType(const tlinsKeysSortcutType v)
{
    type = v;
}

__attribute__((visibility("default"))) void tlinsKeysSortcut::getActionKeys(std::vector<std::string>& keys) const
{
    std::vector<std::string> tmpSeq;
    std::regex separator { "\\+" };
    auto iter = std::sregex_token_iterator(actionKeys.begin(),
        actionKeys.end(),
        separator,
        -1);
    auto iterEnd = std::sregex_token_iterator();

    keys.clear();
    for (; iter != iterEnd; iter++)
        keys.push_back(*iter);
}

std::string tlinsKeysSortcut::getActionName() const
{
    return actionName;
}

TlinsAstroBase::tlinsPilotShortcutsDefinitionValidMode tlinsKeysSortcut::getActionMode() const
{
    return actionMode;
}

void tlinsKeysSortcut::setAhortcutName(const std::string& v)
{
    shortcutName = v;
}

void tlinsKeysSortcut::setActionSettingsJson(const std::string& v)
{
    actionSettingsJson = v;
}

void tlinsKeysSortcut::setActionKeys(const std::string& v)
{
    actionKeys = v;
}

void tlinsKeysSortcut::setActionKeys(const std::vector<std::string>& v)
{
    actionKeys = "";
    int count = 0;

    for (auto& iter : v) {
        actionKeys += iter;
        if ((count + 1) < v.size())
            actionKeys += "+";
        count++;
    }
}

void tlinsKeysSortcut::setActionName(const std::string& v)
{
    actionName = v;
}

void tlinsKeysSortcut::setActionMode(const TlinsAstroBase::tlinsPilotShortcutsDefinitionValidMode v)
{
    actionMode = v;
}

}
