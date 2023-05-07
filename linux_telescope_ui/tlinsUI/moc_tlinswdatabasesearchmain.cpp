/****************************************************************************
** Meta object code from reading C++ file 'tlinswdatabasesearchmain.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.12.7)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "tlinswdatabasesearchmain.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'tlinswdatabasesearchmain.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.12.7. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_tlinsWDatabaseSearchMain_t {
    QByteArrayData data[10];
    char stringdata0[167];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_tlinsWDatabaseSearchMain_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_tlinsWDatabaseSearchMain_t qt_meta_stringdata_tlinsWDatabaseSearchMain = {
    {
QT_MOC_LITERAL(0, 0, 24), // "tlinsWDatabaseSearchMain"
QT_MOC_LITERAL(1, 25, 18), // "buttonSearchPresed"
QT_MOC_LITERAL(2, 44, 0), // ""
QT_MOC_LITERAL(3, 45, 4), // "next"
QT_MOC_LITERAL(4, 50, 8), // "previous"
QT_MOC_LITERAL(5, 59, 23), // "on_selectButton_clicked"
QT_MOC_LITERAL(6, 83, 25), // "on_deselectButton_clicked"
QT_MOC_LITERAL(7, 109, 28), // "on_actualOffset_valueChanged"
QT_MOC_LITERAL(8, 138, 4), // "arg1"
QT_MOC_LITERAL(9, 143, 23) // "on_removeButton_clicked"

    },
    "tlinsWDatabaseSearchMain\0buttonSearchPresed\0"
    "\0next\0previous\0on_selectButton_clicked\0"
    "on_deselectButton_clicked\0"
    "on_actualOffset_valueChanged\0arg1\0"
    "on_removeButton_clicked"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_tlinsWDatabaseSearchMain[] = {

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
       1,    0,   49,    2, 0x08 /* Private */,
       3,    0,   50,    2, 0x08 /* Private */,
       4,    0,   51,    2, 0x08 /* Private */,
       5,    0,   52,    2, 0x08 /* Private */,
       6,    0,   53,    2, 0x08 /* Private */,
       7,    1,   54,    2, 0x08 /* Private */,
       9,    0,   57,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,    8,
    QMetaType::Void,

       0        // eod
};

void tlinsWDatabaseSearchMain::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<tlinsWDatabaseSearchMain *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->buttonSearchPresed(); break;
        case 1: _t->next(); break;
        case 2: _t->previous(); break;
        case 3: _t->on_selectButton_clicked(); break;
        case 4: _t->on_deselectButton_clicked(); break;
        case 5: _t->on_actualOffset_valueChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 6: _t->on_removeButton_clicked(); break;
        default: ;
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject tlinsWDatabaseSearchMain::staticMetaObject = { {
    &QWidget::staticMetaObject,
    qt_meta_stringdata_tlinsWDatabaseSearchMain.data,
    qt_meta_data_tlinsWDatabaseSearchMain,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *tlinsWDatabaseSearchMain::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *tlinsWDatabaseSearchMain::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_tlinsWDatabaseSearchMain.stringdata0))
        return static_cast<void*>(this);
    return QWidget::qt_metacast(_clname);
}

int tlinsWDatabaseSearchMain::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
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
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 7;
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
