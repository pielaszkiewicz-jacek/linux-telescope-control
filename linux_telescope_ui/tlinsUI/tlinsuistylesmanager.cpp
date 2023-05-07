#include "tlinsuistylesmanager.h"

std::map<std::string, std::map<tlinsUiStylesManager::FieldType, std::string>> tlinsUiStylesManager::mapOfStyles;
std::vector<std::string> tlinsUiStylesManager::stylesList;

const std::string tlinsUiStylesManager::COMMON = "COMMON";
const std::string tlinsUiStylesManager::HOUR_ANGLE = "HOUR_ANGLE";
const std::string tlinsUiStylesManager::DECLINATION = "DECLINATION";
const std::string tlinsUiStylesManager::DEGRIS = "DEGRIS";
const std::string tlinsUiStylesManager::OBJECT_NAME = "OBJECT_NAME";
const std::string tlinsUiStylesManager::OBJECT_TYPE = "OBJECT_TYPE";
const std::string tlinsUiStylesManager::CATALOG_TYPE = "CATALOG_TYPE";
const std::string tlinsUiStylesManager::CATALOG_ID_TYPE = "CATALOG_ID_TYPE";
const std::string tlinsUiStylesManager::CONSTELATION = "CONSTELATION";
const std::string tlinsUiStylesManager::DECIMAL_VALUE = "DECIMAL_VALUE";

void tlinsUiStylesManager::initDefaults()
{
    std::string commonTextEdit(
        "QTextEdit {"
        "border-color: darkgray;"
        "border-width: 0.5px;"
        "border-top-style: solid; "
        "border-top-width: 0px; "
        "border-bottom-style: solid; "
        "border-bottom-width: 0.5px;"
        "border-left-style: solid; "
        "border-left-width: 0.5px;"
        "background-color: rgba(255, 255, 255, 0);"
        "margin-top: 0px;"
        "margin-bottom: 0px;"
        "background-attachment: scroll;"
        "}");

    std::string commonGroupBox(
        "QGroupBox {"
        "background-color: rgba(255, 255, 255, 10);"
        "}");

    std::string coordinateGroupBoxTitle(
        "QGroupBox {"
        "border-width: 0.5px;"
        "border-top-style: solid; "
        "border-top-width: 0px; "
        "background-color: rgba(255, 255, 255, 10);"
        "border-bottom-style: solid; "
        "border-bottom-width: 0px; "
        "}"
        "QGroupBox::title {subcontrol-position: left;"
        "margin-top:0px;"
        "margin-right:0px;"
        "}");

    std::string lineEdit(
        "QLineEdit {"
        " border-color: darkgray;"
        "border-width: 0.5px;"
        "border-top-style: solid; "
        "border-top-width: 0px; "
        "border-bottom-style: solid; "
        "border-bottom-width: 0.5px;"
        "background-color: rgba(255, 255, 255, 10);"
        "margin-top: 0px;"
        "margin-bottom: 0px;"
        "}");

    std::string comboBox(
        "QComboBox {"
        "border-color: darkgray;"
        "border-width: 0.5px;"
        "border-top-style: solid; "
        "border-top-width: 0px; "
        "border-bottom-style: solid; "
        "border-bottom-width: 0.5px;"
        "background-color: rgba(255, 255, 255, 0);"
        "}"
        "QComboBox::drop-down {"
        "background-color: rgba(255, 255, 255, 0);"
        "}"
        "QComboBox::down-arrow"
        "{"
        "image: url(:/icons/ic_keyboard_arrow_down_black_24px.svg);"
        "}"
        "QComboBox::down-arrow:disabled"
        "{"
        "background-color: rgba(255, 255, 255, 0);"
        "width:8px;"
        "}"
        "QComboBox::item"
        "{"
        "selection-background-color: lightslategray;"
        "}");

    std::string soubleSpinBox(
        "QDoubleSpinBox {"
        "border-color: darkgray;"
        "border-width: 0.5px;"
        "border-top-style: solid; "
        "border-top-width: 0px; "
        "border-bottom-style: solid; "
        "border-bottom-width: 0.5px;"
        "background-color: rgba(255, 255, 255, 0);"
        "}"
        "QDoubleSpinBox::up-arrow {"
        "image: url(:/icons/Collapse_Arrow.png);"
        "width:12px;"
        "}"
        "QDoubleSpinBox::down-arrow {"
        "image: url(:/icons/Expand_Arrow.png);"
        "width:12px;"
        "}"
        "QDoubleSpinBox::up-button:pressed {"
        "image: url(:/icons/Collapse_Arrow.png) 1; "
        "width:12px;"
        "background-color: darkgray;"
        "}"
        "QDoubleSpinBox::down-button:pressed {"
        "image: url(:/icons/Expand_Arrow.png) 1; "
        "width:12px;"
        "background-color: darkgray;"
        "}");

    tlinsUiStylesManager::mapOfStyles[COMMON][tlinsUiStylesManager::FieldType::GROUP_BOX] = commonGroupBox;
    tlinsUiStylesManager::mapOfStyles[COMMON][tlinsUiStylesManager::FieldType::TEXT_EDIT] = commonTextEdit;

    tlinsUiStylesManager::mapOfStyles[HOUR_ANGLE][tlinsUiStylesManager::FieldType::GROUP_BOX] = coordinateGroupBoxTitle;
    tlinsUiStylesManager::mapOfStyles[HOUR_ANGLE][tlinsUiStylesManager::FieldType::EDIT] = lineEdit;

    tlinsUiStylesManager::mapOfStyles[DECLINATION][tlinsUiStylesManager::FieldType::GROUP_BOX] = coordinateGroupBoxTitle;
    tlinsUiStylesManager::mapOfStyles[DECLINATION][tlinsUiStylesManager::FieldType::EDIT] = lineEdit;

    tlinsUiStylesManager::mapOfStyles[DEGRIS][tlinsUiStylesManager::FieldType::GROUP_BOX] = coordinateGroupBoxTitle;
    tlinsUiStylesManager::mapOfStyles[DEGRIS][tlinsUiStylesManager::FieldType::EDIT] = lineEdit;

    tlinsUiStylesManager::mapOfStyles[OBJECT_NAME][tlinsUiStylesManager::FieldType::GROUP_BOX] = coordinateGroupBoxTitle;
    tlinsUiStylesManager::mapOfStyles[OBJECT_NAME][tlinsUiStylesManager::FieldType::EDIT] = lineEdit;

    tlinsUiStylesManager::mapOfStyles[OBJECT_TYPE][tlinsUiStylesManager::FieldType::GROUP_BOX] = coordinateGroupBoxTitle;
    tlinsUiStylesManager::mapOfStyles[OBJECT_TYPE][tlinsUiStylesManager::FieldType::EDIT] = lineEdit;

    tlinsUiStylesManager::mapOfStyles[CATALOG_TYPE][tlinsUiStylesManager::FieldType::GROUP_BOX] = coordinateGroupBoxTitle;
    tlinsUiStylesManager::mapOfStyles[CATALOG_TYPE][tlinsUiStylesManager::FieldType::COMBO_BOX] = comboBox;

    tlinsUiStylesManager::mapOfStyles[CONSTELATION][tlinsUiStylesManager::FieldType::GROUP_BOX] = coordinateGroupBoxTitle;
    tlinsUiStylesManager::mapOfStyles[CONSTELATION][tlinsUiStylesManager::FieldType::COMBO_BOX] = comboBox;

    tlinsUiStylesManager::mapOfStyles[CATALOG_ID_TYPE][tlinsUiStylesManager::FieldType::GROUP_BOX] = coordinateGroupBoxTitle;
    tlinsUiStylesManager::mapOfStyles[CATALOG_ID_TYPE][tlinsUiStylesManager::FieldType::EDIT] = lineEdit;

    tlinsUiStylesManager::mapOfStyles[DECIMAL_VALUE][tlinsUiStylesManager::FieldType::GROUP_BOX] = coordinateGroupBoxTitle;
    tlinsUiStylesManager::mapOfStyles[DECIMAL_VALUE][tlinsUiStylesManager::FieldType::SPIN_BOX] = soubleSpinBox;
}

void tlinsUiStylesManager::initFromFiles(const std::string&)
{
}

bool tlinsUiStylesManager::getStyle(const std::string& ctrlName, const FieldType& ctlType, std::string& style)
{
    auto objIter = tlinsUiStylesManager::mapOfStyles.find(ctrlName);
    if (objIter == tlinsUiStylesManager::mapOfStyles.end()) {
        return false;
    }

    auto ctrlIter = objIter->second.find(ctlType);
    if (ctrlIter == objIter->second.end()) {
        return false;
    }

    style = ctrlIter->second;
    return true;
}
