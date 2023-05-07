/****************************************************************************
** Meta object code from reading C++ file 'tlinswobservationplace.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.12.7)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "tlinswobservationplace.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'tlinswobservationplace.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.12.7. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_tlinsWObservationPlace_t {
    QByteArrayData data[12];
    char stringdata0[205];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_tlinsWObservationPlace_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_tlinsWObservationPlace_t qt_meta_stringdata_tlinsWObservationPlace = {
    {
QT_MOC_LITERAL(0, 0, 22), // "tlinsWObservationPlace"
QT_MOC_LITERAL(1, 23, 18), // "on_addItem_clicked"
QT_MOC_LITERAL(2, 42, 0), // ""
QT_MOC_LITERAL(3, 43, 21), // "on_updateItem_clicked"
QT_MOC_LITERAL(4, 65, 21), // "on_deleteItem_clicked"
QT_MOC_LITERAL(5, 87, 18), // "on_newItem_clicked"
QT_MOC_LITERAL(6, 106, 20), // "on_saveItems_clicked"
QT_MOC_LITERAL(7, 127, 22), // "on_reloadItems_clicked"
QT_MOC_LITERAL(8, 150, 19), // "on_selectionChanged"
QT_MOC_LITERAL(9, 170, 14), // "QItemSelection"
QT_MOC_LITERAL(10, 185, 8), // "selected"
QT_MOC_LITERAL(11, 194, 10) // "deselected"

    },
    "tlinsWObservationPlace\0on_addItem_clicked\0"
    "\0on_updateItem_clicked\0on_deleteItem_clicked\0"
    "on_newItem_clicked\0on_saveItems_clicked\0"
    "on_reloadItems_clicked\0on_selectionChanged\0"
    "QItemSelection\0selected\0deselected"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_tlinsWObservationPlace[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       7,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   49,    2, 0x0a /* Public */,
       3,    0,   50,    2, 0x0a /* Public */,
       4,    0,   51,    2, 0x0a /* Public */,
       5,    0,   52,    2, 0x0a /* Public */,
       6,    0,   53,    2, 0x0a /* Public */,
       7,    0,   54,    2, 0x0a /* Public */,
       8,    2,   55,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 9, 0x80000000 | 9,   10,   11,

       0        // eod
};

void tlinsWObservationPlace::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<tlinsWObservationPlace *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->on_addItem_clicked(); break;
        case 1: _t->on_updateItem_clicked(); break;
        case 2: _t->on_deleteItem_clicked(); break;
        case 3: _t->on_newItem_clicked(); break;
        case 4: _t->on_saveItems_clicked(); break;
        case 5: _t->on_reloadItems_clicked(); break;
        case 6: _t->on_selectionChanged((*reinterpret_cast< const QItemSelection(*)>(_a[1])),(*reinterpret_cast< const QItemSelection(*)>(_a[2]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        switch (_id) {
        default: *reinterpret_cast<int*>(_a[0]) = -1; break;
        case 6:
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

QT_INIT_METAOBJECT const QMetaObject tlinsWObservationPlace::staticMetaObject = { {
    &QWidget::staticMetaObject,
    qt_meta_stringdata_tlinsWObservationPlace.data,
    qt_meta_data_tlinsWObservationPlace,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *tlinsWObservationPlace::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *tlinsWObservationPlace::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_tlinsWObservationPlace.stringdata0))
        return static_cast<void*>(this);
    return QWidget::qt_metacast(_clname);
}

int tlinsWObservationPlace::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 7)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 7;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 7)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 7;
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
