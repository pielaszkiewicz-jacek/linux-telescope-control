#ifndef TLINSUISTYLESMANAGER_H
#define TLINSUISTYLESMANAGER_H

#include <map>
#include <string>
#include <vector>

class tlinsUiStylesManager {
public:
    enum class FieldType {
        GROUP_BOX,
        CTRL,
        TITLE,
        EDIT,
        COMBO_BOX,
        COMBO_BOX_EDIT,
        SPIN_BOX,
        TEXT_EDIT
    };

private:
    static std::map<std::string, std::map<FieldType, std::string>> mapOfStyles;
    static std::vector<std::string> stylesList;

public:
    static const std::string COMMON;
    static const std::string HOUR_ANGLE;
    static const std::string DECLINATION;
    static const std::string DEGRIS;
    static const std::string OBJECT_NAME;
    static const std::string OBJECT_TYPE;
    static const std::string CATALOG_TYPE;
    static const std::string CATALOG_ID_TYPE;
    static const std::string CONSTELATION;
    static const std::string DECIMAL_VALUE;

public:
    static void initDefaults();
    static void initFromFiles(const std::string& path);
    static bool getStyle(const std::string& ctrlName, const FieldType& ctlType, std::string& style);

    tlinsUiStylesManager()
    {
    }
};

#endif // TLINSUISTYLESMANAGER_H
