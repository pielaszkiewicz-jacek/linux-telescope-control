/****************************************************************************
** Meta object code from reading C++ file 'tlinswpilotshortcutsdefinitions.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.12.7)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "tlinswpilotshortcutsdefinitions.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'tlinswpilotshortcutsdefinitions.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.12.7. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_tlinsShortcutDefinitionModel_t {
    QByteArrayData data[3];
    char stringdata0[44];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_tlinsShortcutDefinitionModel_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_tlinsShortcutDefinitionModel_t qt_meta_stringdata_tlinsShortcutDefinitionModel = {
    {
QT_MOC_LITERAL(0, 0, 28), // "tlinsShortcutDefinitionModel"
QT_MOC_LITERAL(1, 29, 13), // "editCompleted"
QT_MOC_LITERAL(2, 43, 0) // ""

    },
    "tlinsShortcutDefinitionModel\0editCompleted\0"
    ""
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_tlinsShortcutDefinitionModel[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       1,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   19,    2, 0x06 /* Public */,

 // signals: parameters
    QMetaType::Void, QMetaType::QString,    2,

       0        // eod
};

void tlinsShortcutDefinitionModel::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<tlinsShortcutDefinitionModel *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->editCompleted((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (tlinsShortcutDefinitionModel::*)(const QString & );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&tlinsShortcutDefinitionModel::editCompleted)) {
                *result = 0;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject tlinsShortcutDefinitionModel::staticMetaObject = { {
    &QAbstractTableModel::staticMetaObject,
    qt_meta_stringdata_tlinsShortcutDefinitionModel.data,
    qt_meta_data_tlinsShortcutDefinitionModel,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *tlinsShortcutDefinitionModel::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *tlinsShortcutDefinitionModel::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_tlinsShortcutDefinitionModel.stringdata0))
        return static_cast<void*>(this);
    return QAbstractTableModel::qt_metacast(_clname);
}

int tlinsShortcutDefinitionModel::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QAbstractTableModel::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 1)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 1;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 1)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 1;
    }
    return _id;
}

// SIGNAL 0
void tlinsShortcutDefinitionModel::editCompleted(const QString & _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
struct qt_meta_stringdata_tlinsWPilotShortcutsDefinitions_t {
    QByteArrayData data[58];
    char stringdata0[888];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_tlinsWPilotShortcutsDefinitions_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_tlinsWPilotShortcutsDefinitions_t qt_meta_stringdata_tlinsWPilotShortcutsDefinitions = {
    {
QT_MOC_LITERAL(0, 0, 31), // "tlinsWPilotShortcutsDefinitions"
QT_MOC_LITERAL(1, 32, 19), // "on_selectionChanged"
QT_MOC_LITERAL(2, 52, 0), // ""
QT_MOC_LITERAL(3, 53, 14), // "QItemSelection"
QT_MOC_LITERAL(4, 68, 8), // "selected"
QT_MOC_LITERAL(5, 77, 10), // "deselected"
QT_MOC_LITERAL(6, 88, 13), // "jButtonUpSlot"
QT_MOC_LITERAL(7, 102, 1), // "v"
QT_MOC_LITERAL(8, 104, 15), // "jButtonDownSlot"
QT_MOC_LITERAL(9, 120, 15), // "jButtonLeftSlot"
QT_MOC_LITERAL(10, 136, 16), // "jButtonRightSlot"
QT_MOC_LITERAL(11, 153, 14), // "jButtonF01Slot"
QT_MOC_LITERAL(12, 168, 14), // "jButtonF02Slot"
QT_MOC_LITERAL(13, 183, 14), // "jButtonF11Slot"
QT_MOC_LITERAL(14, 198, 14), // "jButtonF12Slot"
QT_MOC_LITERAL(15, 213, 14), // "jButtonF13Slot"
QT_MOC_LITERAL(16, 228, 14), // "jButtonF14Slot"
QT_MOC_LITERAL(17, 243, 14), // "jButtonF21Slot"
QT_MOC_LITERAL(18, 258, 14), // "jButtonF22Slot"
QT_MOC_LITERAL(19, 273, 14), // "jButtonF23Slot"
QT_MOC_LITERAL(20, 288, 14), // "jButtonF24Slot"
QT_MOC_LITERAL(21, 303, 14), // "jButtonF32Slot"
QT_MOC_LITERAL(22, 318, 18), // "jButtonLeftPadSlot"
QT_MOC_LITERAL(23, 337, 13), // "jTypeKeyboard"
QT_MOC_LITERAL(24, 351, 13), // "jTypeJoystick"
QT_MOC_LITERAL(25, 365, 16), // "jSubTypeKeyboard"
QT_MOC_LITERAL(26, 382, 16), // "jSubTypeJoystick"
QT_MOC_LITERAL(27, 399, 12), // "buttonUpSlot"
QT_MOC_LITERAL(28, 412, 14), // "buttonDownSlot"
QT_MOC_LITERAL(29, 427, 14), // "buttonLeftSlot"
QT_MOC_LITERAL(30, 442, 15), // "buttonRightSlot"
QT_MOC_LITERAL(31, 458, 12), // "buttonOkSlot"
QT_MOC_LITERAL(32, 471, 13), // "buttonF01Slot"
QT_MOC_LITERAL(33, 485, 13), // "buttonF02Slot"
QT_MOC_LITERAL(34, 499, 13), // "buttonF11Slot"
QT_MOC_LITERAL(35, 513, 13), // "buttonF12Slot"
QT_MOC_LITERAL(36, 527, 13), // "buttonF13Slot"
QT_MOC_LITERAL(37, 541, 13), // "buttonF14Slot"
QT_MOC_LITERAL(38, 555, 13), // "buttonF21Slot"
QT_MOC_LITERAL(39, 569, 13), // "buttonF22Slot"
QT_MOC_LITERAL(40, 583, 13), // "buttonF23Slot"
QT_MOC_LITERAL(41, 597, 13), // "buttonF24Slot"
QT_MOC_LITERAL(42, 611, 13), // "buttonF31Slot"
QT_MOC_LITERAL(43, 625, 13), // "buttonF32Slot"
QT_MOC_LITERAL(44, 639, 13), // "buttonF33Slot"
QT_MOC_LITERAL(45, 653, 13), // "buttonF34Slot"
QT_MOC_LITERAL(46, 667, 19), // "editingFinishedSlot"
QT_MOC_LITERAL(47, 687, 25), // "cursorPositionChangedSlot"
QT_MOC_LITERAL(48, 713, 6), // "oldPos"
QT_MOC_LITERAL(49, 720, 6), // "newPos"
QT_MOC_LITERAL(50, 727, 19), // "actionActivatedSlot"
QT_MOC_LITERAL(51, 747, 5), // "index"
QT_MOC_LITERAL(52, 753, 20), // "buttonNewClickedSlot"
QT_MOC_LITERAL(53, 774, 20), // "buttonAddClickedSlot"
QT_MOC_LITERAL(54, 795, 23), // "buttonUpdateClickedSlot"
QT_MOC_LITERAL(55, 819, 23), // "buttonRemoveClickedSlot"
QT_MOC_LITERAL(56, 843, 21), // "buttonLoadClickedSlot"
QT_MOC_LITERAL(57, 865, 22) // "buttonStoreClickedSlot"

    },
    "tlinsWPilotShortcutsDefinitions\0"
    "on_selectionChanged\0\0QItemSelection\0"
    "selected\0deselected\0jButtonUpSlot\0v\0"
    "jButtonDownSlot\0jButtonLeftSlot\0"
    "jButtonRightSlot\0jButtonF01Slot\0"
    "jButtonF02Slot\0jButtonF11Slot\0"
    "jButtonF12Slot\0jButtonF13Slot\0"
    "jButtonF14Slot\0jButtonF21Slot\0"
    "jButtonF22Slot\0jButtonF23Slot\0"
    "jButtonF24Slot\0jButtonF32Slot\0"
    "jButtonLeftPadSlot\0jTypeKeyboard\0"
    "jTypeJoystick\0jSubTypeKeyboard\0"
    "jSubTypeJoystick\0buttonUpSlot\0"
    "buttonDownSlot\0buttonLeftSlot\0"
    "buttonRightSlot\0buttonOkSlot\0buttonF01Slot\0"
    "buttonF02Slot\0buttonF11Slot\0buttonF12Slot\0"
    "buttonF13Slot\0buttonF14Slot\0buttonF21Slot\0"
    "buttonF22Slot\0buttonF23Slot\0buttonF24Slot\0"
    "buttonF31Slot\0buttonF32Slot\0buttonF33Slot\0"
    "buttonF34Slot\0editingFinishedSlot\0"
    "cursorPositionChangedSlot\0oldPos\0"
    "newPos\0actionActivatedSlot\0index\0"
    "buttonNewClickedSlot\0buttonAddClickedSlot\0"
    "buttonUpdateClickedSlot\0buttonRemoveClickedSlot\0"
    "buttonLoadClickedSlot\0buttonStoreClickedSlot"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_tlinsWPilotShortcutsDefinitions[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
      49,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    2,  259,    2, 0x08 /* Private */,
       6,    1,  264,    2, 0x0a /* Public */,
       8,    1,  267,    2, 0x0a /* Public */,
       9,    1,  270,    2, 0x0a /* Public */,
      10,    1,  273,    2, 0x0a /* Public */,
      11,    1,  276,    2, 0x0a /* Public */,
      12,    1,  279,    2, 0x0a /* Public */,
      13,    1,  282,    2, 0x0a /* Public */,
      14,    1,  285,    2, 0x0a /* Public */,
      15,    1,  288,    2, 0x0a /* Public */,
      16,    1,  291,    2, 0x0a /* Public */,
      17,    1,  294,    2, 0x0a /* Public */,
      18,    1,  297,    2, 0x0a /* Public */,
      19,    1,  300,    2, 0x0a /* Public */,
      20,    1,  303,    2, 0x0a /* Public */,
      21,    1,  306,    2, 0x0a /* Public */,
      22,    1,  309,    2, 0x0a /* Public */,
      23,    1,  312,    2, 0x0a /* Public */,
      24,    1,  315,    2, 0x0a /* Public */,
      25,    1,  318,    2, 0x0a /* Public */,
      26,    1,  321,    2, 0x0a /* Public */,
      27,    1,  324,    2, 0x0a /* Public */,
      28,    1,  327,    2, 0x0a /* Public */,
      29,    1,  330,    2, 0x0a /* Public */,
      30,    1,  333,    2, 0x0a /* Public */,
      31,    1,  336,    2, 0x0a /* Public */,
      32,    1,  339,    2, 0x0a /* Public */,
      33,    1,  342,    2, 0x0a /* Public */,
      34,    1,  345,    2, 0x0a /* Public */,
      35,    1,  348,    2, 0x0a /* Public */,
      36,    1,  351,    2, 0x0a /* Public */,
      37,    1,  354,    2, 0x0a /* Public */,
      38,    1,  357,    2, 0x0a /* Public */,
      39,    1,  360,    2, 0x0a /* Public */,
      40,    1,  363,    2, 0x0a /* Public */,
      41,    1,  366,    2, 0x0a /* Public */,
      42,    1,  369,    2, 0x0a /* Public */,
      43,    1,  372,    2, 0x0a /* Public */,
      44,    1,  375,    2, 0x0a /* Public */,
      45,    1,  378,    2, 0x0a /* Public */,
      46,    0,  381,    2, 0x0a /* Public */,
      47,    2,  382,    2, 0x0a /* Public */,
      50,    1,  387,    2, 0x0a /* Public */,
      52,    0,  390,    2, 0x0a /* Public */,
      53,    0,  391,    2, 0x0a /* Public */,
      54,    0,  392,    2, 0x0a /* Public */,
      55,    0,  393,    2, 0x0a /* Public */,
      56,    0,  394,    2, 0x0a /* Public */,
      57,    0,  395,    2, 0x0a /* Public */,

 // slots: parameters
    QMetaType::Void, 0x80000000 | 3, 0x80000000 | 3,    4,    5,
    QMetaType::Void, QMetaType::Bool,    7,
    QMetaType::Void, QMetaType::Bool,    7,
    QMetaType::Void, QMetaType::Bool,    7,
    QMetaType::Void, QMetaType::Bool,    7,
    QMetaType::Void, QMetaType::Bool,    7,
    QMetaType::Void, QMetaType::Bool,    7,
    QMetaType::Void, QMetaType::Bool,    7,
    QMetaType::Void, QMetaType::Bool,    7,
    QMetaType::Void, QMetaType::Bool,    7,
    QMetaType::Void, QMetaType::Bool,    7,
    QMetaType::Void, QMetaType::Bool,    7,
    QMetaType::Void, QMetaType::Bool,    7,
    QMetaType::Void, QMetaType::Bool,    7,
    QMetaType::Void, QMetaType::Bool,    7,
    QMetaType::Void, QMetaType::Bool,    7,
    QMetaType::Void, QMetaType::Bool,    7,
    QMetaType::Void, QMetaType::Bool,    7,
    QMetaType::Void, QMetaType::Bool,    7,
    QMetaType::Void, QMetaType::Bool,    7,
    QMetaType::Void, QMetaType::Bool,    7,
    QMetaType::Void, QMetaType::Bool,    7,
    QMetaType::Void, QMetaType::Bool,    7,
    QMetaType::Void, QMetaType::Bool,    7,
    QMetaType::Void, QMetaType::Bool,    7,
    QMetaType::Void, QMetaType::Bool,    7,
    QMetaType::Void, QMetaType::Bool,    7,
    QMetaType::Void, QMetaType::Bool,    7,
    QMetaType::Void, QMetaType::Bool,    7,
    QMetaType::Void, QMetaType::Bool,    7,
    QMetaType::Void, QMetaType::Bool,    7,
    QMetaType::Void, QMetaType::Bool,    7,
    QMetaType::Void, QMetaType::Bool,    7,
    QMetaType::Void, QMetaType::Bool,    7,
    QMetaType::Void, QMetaType::Bool,    7,
    QMetaType::Void, QMetaType::Bool,    7,
    QMetaType::Void, QMetaType::Bool,    7,
    QMetaType::Void, QMetaType::Bool,    7,
    QMetaType::Void, QMetaType::Bool,    7,
    QMetaType::Void, QMetaType::Bool,    7,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int, QMetaType::Int,   48,   49,
    QMetaType::Void, QMetaType::Int,   51,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void tlinsWPilotShortcutsDefinitions::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<tlinsWPilotShortcutsDefinitions *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->on_selectionChanged((*reinterpret_cast< const QItemSelection(*)>(_a[1])),(*reinterpret_cast< const QItemSelection(*)>(_a[2]))); break;
        case 1: _t->jButtonUpSlot((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 2: _t->jButtonDownSlot((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 3: _t->jButtonLeftSlot((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 4: _t->jButtonRightSlot((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 5: _t->jButtonF01Slot((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 6: _t->jButtonF02Slot((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 7: _t->jButtonF11Slot((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 8: _t->jButtonF12Slot((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 9: _t->jButtonF13Slot((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 10: _t->jButtonF14Slot((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 11: _t->jButtonF21Slot((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 12: _t->jButtonF22Slot((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 13: _t->jButtonF23Slot((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 14: _t->jButtonF24Slot((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 15: _t->jButtonF32Slot((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 16: _t->jButtonLeftPadSlot((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 17: _t->jTypeKeyboard((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 18: _t->jTypeJoystick((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 19: _t->jSubTypeKeyboard((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 20: _t->jSubTypeJoystick((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 21: _t->buttonUpSlot((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 22: _t->buttonDownSlot((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 23: _t->buttonLeftSlot((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 24: _t->buttonRightSlot((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 25: _t->buttonOkSlot((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 26: _t->buttonF01Slot((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 27: _t->buttonF02Slot((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 28: _t->buttonF11Slot((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 29: _t->buttonF12Slot((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 30: _t->buttonF13Slot((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 31: _t->buttonF14Slot((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 32: _t->buttonF21Slot((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 33: _t->buttonF22Slot((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 34: _t->buttonF23Slot((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 35: _t->buttonF24Slot((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 36: _t->buttonF31Slot((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 37: _t->buttonF32Slot((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 38: _t->buttonF33Slot((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 39: _t->buttonF34Slot((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 40: _t->editingFinishedSlot(); break;
        case 41: _t->cursorPositionChangedSlot((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 42: _t->actionActivatedSlot((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 43: _t->buttonNewClickedSlot(); break;
        case 44: _t->buttonAddClickedSlot(); break;
        case 45: _t->buttonUpdateClickedSlot(); break;
        case 46: _t->buttonRemoveClickedSlot(); break;
        case 47: _t->buttonLoadClickedSlot(); break;
        case 48: _t->buttonStoreClickedSlot(); break;
        default: ;
        }
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        switch (_id) {
        default: *reinterpret_cast<int*>(_a[0]) = -1; break;
        case 0:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 1:
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QItemSelection >(); break;
            }
            break;
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject tlinsWPilotShortcutsDefinitions::staticMetaObject = { {
    &QWidget::staticMetaObject,
    qt_meta_stringdata_tlinsWPilotShortcutsDefinitions.data,
    qt_meta_data_tlinsWPilotShortcutsDefinitions,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *tlinsWPilotShortcutsDefinitions::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *tlinsWPilotShortcutsDefinitions::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_tlinsWPilotShortcutsDefinitions.stringdata0))
        return static_cast<void*>(this);
    return QWidget::qt_metacast(_clname);
}

int tlinsWPilotShortcutsDefinitions::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 49)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 49;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 49)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 49;
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
