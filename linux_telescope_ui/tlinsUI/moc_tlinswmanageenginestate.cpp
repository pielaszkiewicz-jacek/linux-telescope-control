/****************************************************************************
** Meta object code from reading C++ file 'tlinswmanageenginestate.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.12.7)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "tlinswmanageenginestate.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'tlinswmanageenginestate.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.12.7. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_tlinsEngineStateModelModel_t {
    QByteArrayData data[3];
    char stringdata0[42];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_tlinsEngineStateModelModel_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_tlinsEngineStateModelModel_t qt_meta_stringdata_tlinsEngineStateModelModel = {
    {
QT_MOC_LITERAL(0, 0, 26), // "tlinsEngineStateModelModel"
QT_MOC_LITERAL(1, 27, 13), // "editCompleted"
QT_MOC_LITERAL(2, 41, 0) // ""

    },
    "tlinsEngineStateModelModel\0editCompleted\0"
    ""
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_tlinsEngineStateModelModel[] = {

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

void tlinsEngineStateModelModel::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<tlinsEngineStateModelModel *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->editCompleted((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (tlinsEngineStateModelModel::*)(const QString & );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&tlinsEngineStateModelModel::editCompleted)) {
                *result = 0;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject tlinsEngineStateModelModel::staticMetaObject = { {
    &QAbstractTableModel::staticMetaObject,
    qt_meta_stringdata_tlinsEngineStateModelModel.data,
    qt_meta_data_tlinsEngineStateModelModel,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *tlinsEngineStateModelModel::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *tlinsEngineStateModelModel::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_tlinsEngineStateModelModel.stringdata0))
        return static_cast<void*>(this);
    return QAbstractTableModel::qt_metacast(_clname);
}

int tlinsEngineStateModelModel::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
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
void tlinsEngineStateModelModel::editCompleted(const QString & _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
struct qt_meta_stringdata_tlinsWManageEngineState_t {
    QByteArrayData data[40];
    char stringdata0[738];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_tlinsWManageEngineState_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_tlinsWManageEngineState_t qt_meta_stringdata_tlinsWManageEngineState = {
    {
QT_MOC_LITERAL(0, 0, 23), // "tlinsWManageEngineState"
QT_MOC_LITERAL(1, 24, 10), // "notiStatus"
QT_MOC_LITERAL(2, 35, 0), // ""
QT_MOC_LITERAL(3, 36, 11), // "std::string"
QT_MOC_LITERAL(4, 48, 18), // "updateCurrentState"
QT_MOC_LITERAL(5, 67, 37), // "TlinsAstroBase::tlinsAstroEng..."
QT_MOC_LITERAL(6, 105, 5), // "state"
QT_MOC_LITERAL(7, 111, 17), // "updateGuiderRatio"
QT_MOC_LITERAL(8, 129, 2), // "ra"
QT_MOC_LITERAL(9, 132, 2), // "dc"
QT_MOC_LITERAL(10, 135, 16), // "updateCorrection"
QT_MOC_LITERAL(11, 152, 14), // "notiStatusSlot"
QT_MOC_LITERAL(12, 167, 3), // "str"
QT_MOC_LITERAL(13, 171, 22), // "updateCurrentStateSlot"
QT_MOC_LITERAL(14, 194, 21), // "updateGuiderRatioSlot"
QT_MOC_LITERAL(15, 216, 20), // "updateCorrectionSlot"
QT_MOC_LITERAL(16, 237, 19), // "on_selectionChanged"
QT_MOC_LITERAL(17, 257, 14), // "QItemSelection"
QT_MOC_LITERAL(18, 272, 8), // "selected"
QT_MOC_LITERAL(19, 281, 10), // "deselected"
QT_MOC_LITERAL(20, 292, 16), // "on_btAdd_clicked"
QT_MOC_LITERAL(21, 309, 19), // "on_btRemove_clicked"
QT_MOC_LITERAL(22, 329, 17), // "on_btSave_clicked"
QT_MOC_LITERAL(23, 347, 18), // "on_btStart_clicked"
QT_MOC_LITERAL(24, 366, 17), // "on_btStop_clicked"
QT_MOC_LITERAL(25, 384, 17), // "on_btLoad_clicked"
QT_MOC_LITERAL(26, 402, 24), // "on_btUploadState_clicked"
QT_MOC_LITERAL(27, 427, 26), // "on_btDownloadState_clicked"
QT_MOC_LITERAL(28, 454, 33), // "on_pbReadFromDeviceManual_cli..."
QT_MOC_LITERAL(29, 488, 31), // "on_pbUpdateDeviceManual_clicked"
QT_MOC_LITERAL(30, 520, 23), // "on_pbLoadGuider_clicked"
QT_MOC_LITERAL(31, 544, 31), // "on_pbUpdateDeviceGuider_clicked"
QT_MOC_LITERAL(32, 576, 34), // "on_pbSReadFromDeviceGuider_cl..."
QT_MOC_LITERAL(33, 611, 24), // "on_pbStoreGuider_clicked"
QT_MOC_LITERAL(34, 636, 17), // "slotViewSelection"
QT_MOC_LITERAL(35, 654, 3), // "val"
QT_MOC_LITERAL(36, 658, 16), // "slot_dialRARatio"
QT_MOC_LITERAL(37, 675, 17), // "slot_dialDECRatio"
QT_MOC_LITERAL(38, 693, 21), // "slot_dialRACorrection"
QT_MOC_LITERAL(39, 715, 22) // "slot_dialDECCorrection"

    },
    "tlinsWManageEngineState\0notiStatus\0\0"
    "std::string\0updateCurrentState\0"
    "TlinsAstroBase::tlinsAstroEngineState\0"
    "state\0updateGuiderRatio\0ra\0dc\0"
    "updateCorrection\0notiStatusSlot\0str\0"
    "updateCurrentStateSlot\0updateGuiderRatioSlot\0"
    "updateCorrectionSlot\0on_selectionChanged\0"
    "QItemSelection\0selected\0deselected\0"
    "on_btAdd_clicked\0on_btRemove_clicked\0"
    "on_btSave_clicked\0on_btStart_clicked\0"
    "on_btStop_clicked\0on_btLoad_clicked\0"
    "on_btUploadState_clicked\0"
    "on_btDownloadState_clicked\0"
    "on_pbReadFromDeviceManual_clicked\0"
    "on_pbUpdateDeviceManual_clicked\0"
    "on_pbLoadGuider_clicked\0"
    "on_pbUpdateDeviceGuider_clicked\0"
    "on_pbSReadFromDeviceGuider_clicked\0"
    "on_pbStoreGuider_clicked\0slotViewSelection\0"
    "val\0slot_dialRARatio\0slot_dialDECRatio\0"
    "slot_dialRACorrection\0slot_dialDECCorrection"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_tlinsWManageEngineState[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
      28,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       4,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,  154,    2, 0x06 /* Public */,
       4,    1,  157,    2, 0x06 /* Public */,
       7,    2,  160,    2, 0x06 /* Public */,
      10,    2,  165,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
      11,    1,  170,    2, 0x0a /* Public */,
      13,    1,  173,    2, 0x0a /* Public */,
      14,    2,  176,    2, 0x08 /* Private */,
      15,    2,  181,    2, 0x08 /* Private */,
      16,    2,  186,    2, 0x08 /* Private */,
      20,    0,  191,    2, 0x08 /* Private */,
      21,    0,  192,    2, 0x08 /* Private */,
      22,    0,  193,    2, 0x08 /* Private */,
      23,    0,  194,    2, 0x08 /* Private */,
      24,    0,  195,    2, 0x08 /* Private */,
      25,    0,  196,    2, 0x08 /* Private */,
      26,    0,  197,    2, 0x08 /* Private */,
      27,    0,  198,    2, 0x08 /* Private */,
      28,    0,  199,    2, 0x08 /* Private */,
      29,    0,  200,    2, 0x08 /* Private */,
      30,    0,  201,    2, 0x08 /* Private */,
      31,    0,  202,    2, 0x08 /* Private */,
      32,    0,  203,    2, 0x08 /* Private */,
      33,    0,  204,    2, 0x08 /* Private */,
      34,    1,  205,    2, 0x08 /* Private */,
      36,    1,  208,    2, 0x08 /* Private */,
      37,    1,  211,    2, 0x08 /* Private */,
      38,    1,  214,    2, 0x08 /* Private */,
      39,    1,  217,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Void, 0x80000000 | 3,    2,
    QMetaType::Void, 0x80000000 | 5,    6,
    QMetaType::Void, QMetaType::Double, QMetaType::Double,    8,    9,
    QMetaType::Void, QMetaType::Double, QMetaType::Double,    8,    9,

 // slots: parameters
    QMetaType::Void, 0x80000000 | 3,   12,
    QMetaType::Void, 0x80000000 | 5,    6,
    QMetaType::Void, QMetaType::Double, QMetaType::Double,    8,    9,
    QMetaType::Void, QMetaType::Double, QMetaType::Double,    8,    9,
    QMetaType::Void, 0x80000000 | 17, 0x80000000 | 17,   18,   19,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Bool,   35,
    QMetaType::Void, QMetaType::Int,    2,
    QMetaType::Void, QMetaType::Int,    2,
    QMetaType::Void, QMetaType::Int,    2,
    QMetaType::Void, QMetaType::Int,    2,

       0        // eod
};

void tlinsWManageEngineState::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<tlinsWManageEngineState *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->notiStatus((*reinterpret_cast< std::string(*)>(_a[1]))); break;
        case 1: _t->updateCurrentState((*reinterpret_cast< const TlinsAstroBase::tlinsAstroEngineState(*)>(_a[1]))); break;
        case 2: _t->updateGuiderRatio((*reinterpret_cast< double(*)>(_a[1])),(*reinterpret_cast< double(*)>(_a[2]))); break;
        case 3: _t->updateCorrection((*reinterpret_cast< double(*)>(_a[1])),(*reinterpret_cast< double(*)>(_a[2]))); break;
        case 4: _t->notiStatusSlot((*reinterpret_cast< std::string(*)>(_a[1]))); break;
        case 5: _t->updateCurrentStateSlot((*reinterpret_cast< const TlinsAstroBase::tlinsAstroEngineState(*)>(_a[1]))); break;
        case 6: _t->updateGuiderRatioSlot((*reinterpret_cast< double(*)>(_a[1])),(*reinterpret_cast< double(*)>(_a[2]))); break;
        case 7: _t->updateCorrectionSlot((*reinterpret_cast< double(*)>(_a[1])),(*reinterpret_cast< double(*)>(_a[2]))); break;
        case 8: _t->on_selectionChanged((*reinterpret_cast< const QItemSelection(*)>(_a[1])),(*reinterpret_cast< const QItemSelection(*)>(_a[2]))); break;
        case 9: _t->on_btAdd_clicked(); break;
        case 10: _t->on_btRemove_clicked(); break;
        case 11: _t->on_btSave_clicked(); break;
        case 12: _t->on_btStart_clicked(); break;
        case 13: _t->on_btStop_clicked(); break;
        case 14: _t->on_btLoad_clicked(); break;
        case 15: _t->on_btUploadState_clicked(); break;
        case 16: _t->on_btDownloadState_clicked(); break;
        case 17: _t->on_pbReadFromDeviceManual_clicked(); break;
        case 18: _t->on_pbUpdateDeviceManual_clicked(); break;
        case 19: _t->on_pbLoadGuider_clicked(); break;
        case 20: _t->on_pbUpdateDeviceGuider_clicked(); break;
        case 21: _t->on_pbSReadFromDeviceGuider_clicked(); break;
        case 22: _t->on_pbStoreGuider_clicked(); break;
        case 23: _t->slotViewSelection((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 24: _t->slot_dialRARatio((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 25: _t->slot_dialDECRatio((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 26: _t->slot_dialRACorrection((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 27: _t->slot_dialDECCorrection((*reinterpret_cast< int(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        switch (_id) {
        default: *reinterpret_cast<int*>(_a[0]) = -1; break;
        case 8:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 1:
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QItemSelection >(); break;
            }
            break;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (tlinsWManageEngineState::*)(std::string );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&tlinsWManageEngineState::notiStatus)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (tlinsWManageEngineState::*)(const TlinsAstroBase::tlinsAstroEngineState & );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&tlinsWManageEngineState::updateCurrentState)) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (tlinsWManageEngineState::*)(double , double );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&tlinsWManageEngineState::updateGuiderRatio)) {
                *result = 2;
                return;
            }
        }
        {
            using _t = void (tlinsWManageEngineState::*)(double , double );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&tlinsWManageEngineState::updateCorrection)) {
                *result = 3;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject tlinsWManageEngineState::staticMetaObject = { {
    &QWidget::staticMetaObject,
    qt_meta_stringdata_tlinsWManageEngineState.data,
    qt_meta_data_tlinsWManageEngineState,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *tlinsWManageEngineState::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *tlinsWManageEngineState::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_tlinsWManageEngineState.stringdata0))
        return static_cast<void*>(this);
    return QWidget::qt_metacast(_clname);
}

int tlinsWManageEngineState::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 28)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 28;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 28)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 28;
    }
    return _id;
}

// SIGNAL 0
void tlinsWManageEngineState::notiStatus(std::string _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void tlinsWManageEngineState::updateCurrentState(const TlinsAstroBase::tlinsAstroEngineState & _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void tlinsWManageEngineState::updateGuiderRatio(double _t1, double _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void tlinsWManageEngineState::updateCorrection(double _t1, double _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
