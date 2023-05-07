#ifndef TLINSWPILOTSHORTCUTSDEFINITIONS_H
#define TLINSWPILOTSHORTCUTSDEFINITIONS_H
#include <QWidget>
#include <map>
#include <memory>
#include <tlinskeyssortcut.h>
#include <tlinspilotshortcutsdefinitioninterface.h>
#include <vector>

#include <QAbstractTableModel>
#include <QItemSelection>
#include <QPushButton>
#include <unordered_map>

namespace Ui {
class tlinsWPilotShortcutsDefinitions;
}

class tlinsShortcutDefinitionModel : public QAbstractTableModel {
    Q_OBJECT
public:
    int rowCount(const QModelIndex& parent = QModelIndex()) const Q_DECL_OVERRIDE;
    int columnCount(const QModelIndex& parent = QModelIndex()) const
        Q_DECL_OVERRIDE;
    QVariant data(const QModelIndex& index,
        int role = Qt::DisplayRole) const Q_DECL_OVERRIDE;
    QVariant headerData(int section, Qt::Orientation orientation,
        int role) const Q_DECL_OVERRIDE;

private:
    std::vector<TlinsAstroBase::tlinsKeysSortcut> actionsData;

public:
    std::vector<TlinsAstroBase::tlinsKeysSortcut>& getData();
    void setItems(const std::vector<TlinsAstroBase::tlinsKeysSortcut>& data);
    bool updateItem(const TlinsAstroBase::tlinsKeysSortcut& data);
    bool insertItem(const TlinsAstroBase::tlinsKeysSortcut& data);
    void deleteItems(const std::vector<TlinsAstroBase::tlinsKeysSortcut>& data);
    bool deleteItem(const unsigned int idx);
    void clear();

public:
    tlinsShortcutDefinitionModel(QObject* parent = nullptr);
    virtual ~tlinsShortcutDefinitionModel() override;

signals:
    void editCompleted(const QString&);
};

class tlinsWPilotShortcutsDefinitions : public QWidget {
    Q_OBJECT

private:
    std::vector<std::string> sequence;
    int currPos;

    std::unordered_map<std::string, QPushButton*> widgetsMap;
    tlinsShortcutDefinitionModel dataModel;

private:
    void insertPos(const std::string& v, const bool isChecked);

private slots:
    void on_selectionChanged(const QItemSelection& selected,
        const QItemSelection& deselected);

public slots:

    // Sloty dla gamepad/joystick
    void jButtonUpSlot(bool v);
    void jButtonDownSlot(bool v);
    void jButtonLeftSlot(bool v);
    void jButtonRightSlot(bool v);

    void jButtonF01Slot(bool v);
    void jButtonF02Slot(bool v);

    void jButtonF11Slot(bool v);
    void jButtonF12Slot(bool v);
    void jButtonF13Slot(bool v);
    void jButtonF14Slot(bool v);

    void jButtonF21Slot(bool v);
    void jButtonF22Slot(bool v);
    void jButtonF23Slot(bool v);
    void jButtonF24Slot(bool v);

    void jButtonF32Slot(bool v);

    void jButtonLeftPadSlot(bool v);

    void jTypeKeyboard(bool v);
    void jTypeJoystick(bool v);

    void jSubTypeKeyboard(bool v);
    void jSubTypeJoystick(bool v);

    // ------------------------

    // Sloty dla pilota
    void buttonUpSlot(bool v);
    void buttonDownSlot(bool v);
    void buttonLeftSlot(bool v);
    void buttonRightSlot(bool v);
    void buttonOkSlot(bool v);
    void buttonF01Slot(bool v);
    void buttonF02Slot(bool v);
    void buttonF11Slot(bool v);
    void buttonF12Slot(bool v);
    void buttonF13Slot(bool v);
    void buttonF14Slot(bool v);
    void buttonF21Slot(bool v);
    void buttonF22Slot(bool v);
    void buttonF23Slot(bool v);
    void buttonF24Slot(bool v);
    void buttonF31Slot(bool v);
    void buttonF32Slot(bool v);
    void buttonF33Slot(bool v);
    void buttonF34Slot(bool v);
    void editingFinishedSlot();
    void cursorPositionChangedSlot(int oldPos, int newPos);
    void actionActivatedSlot(int index);

    void buttonNewClickedSlot();
    void buttonAddClickedSlot();
    void buttonUpdateClickedSlot();
    void buttonRemoveClickedSlot();

    void buttonLoadClickedSlot();
    void buttonStoreClickedSlot();

private:
    bool getSelected(std::vector<int>& rows);
    bool getDataItem(TlinsAstroBase::tlinsKeysSortcut& data);

    std::map<
        std::string,
        std::shared_ptr<TlinsAstroBase::tlinsPilotShortcutsDefinitionInterface>>
        configsMap;

public:
    explicit tlinsWPilotShortcutsDefinitions(QWidget* parent = nullptr);
    ~tlinsWPilotShortcutsDefinitions();

private:
    Ui::tlinsWPilotShortcutsDefinitions* ui;
};

#endif // TLINSWPILOTSHORTCUTSDEFINITIONS_H
