/****************************************************************************
** Meta object code from reading C++ file 'tlinseditdatabaseobject.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.12.7)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "tlinseditdatabaseobject.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'tlinseditdatabaseobject.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.12.7. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_tlinsEditDatabaseObject_t {
    QByteArrayData data[9];
    char stringdata0[136];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_tlinsEditDatabaseObject_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_tlinsEditDatabaseObject_t qt_meta_stringdata_tlinsEditDatabaseObject = {
    {
QT_MOC_LITERAL(0, 0, 23), // "tlinsEditDatabaseObject"
QT_MOC_LITERAL(1, 24, 13), // "objectChanged"
QT_MOC_LITERAL(2, 38, 0), // ""
QT_MOC_LITERAL(3, 39, 37), // "TlinsAstroBase::tlinsAstroCat..."
QT_MOC_LITERAL(4, 77, 1), // "v"
QT_MOC_LITERAL(5, 79, 2), // "id"
QT_MOC_LITERAL(6, 82, 13), // "objectCreated"
QT_MOC_LITERAL(7, 96, 19), // "on_buttons_accepted"
QT_MOC_LITERAL(8, 116, 19) // "on_buttons_rejected"

    },
    "tlinsEditDatabaseObject\0objectChanged\0"
    "\0TlinsAstroBase::tlinsAstroCatalogItem\0"
    "v\0id\0objectCreated\0on_buttons_accepted\0"
    "on_buttons_rejected"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_tlinsEditDatabaseObject[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       4,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    2,   34,    2, 0x06 /* Public */,
       6,    1,   39,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       7,    0,   42,    2, 0x08 /* Private */,
       8,    0,   43,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Void, 0x80000000 | 3, QMetaType::Int,    4,    5,
    QMetaType::Void, 0x80000000 | 3,    4,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void tlinsEditDatabaseObject::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<tlinsEditDatabaseObject *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->objectChanged((*reinterpret_cast< TlinsAstroBase::tlinsAstroCatalogItem(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 1: _t->objectCreated((*reinterpret_cast< TlinsAstroBase::tlinsAstroCatalogItem(*)>(_a[1]))); break;
        case 2: _t->on_buttons_accepted(); break;
        case 3: _t->on_buttons_rejected(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (tlinsEditDatabaseObject::*)(TlinsAstroBase::tlinsAstroCatalogItem , int );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&tlinsEditDatabaseObject::objectChanged)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (tlinsEditDatabaseObject::*)(TlinsAstroBase::tlinsAstroCatalogItem );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&tlinsEditDatabaseObject::objectCreated)) {
                *result = 1;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject tlinsEditDatabaseObject::staticMetaObject = { {
    &QDialog::staticMetaObject,
    qt_meta_stringdata_tlinsEditDatabaseObject.data,
    qt_meta_data_tlinsEditDatabaseObject,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *tlinsEditDatabaseObject::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *tlinsEditDatabaseObject::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_tlinsEditDatabaseObject.stringdata0))
        return static_cast<void*>(this);
    return QDialog::qt_metacast(_clname);
}

int tlinsEditDatabaseObject::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 4)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 4;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 4)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 4;
    }
    return _id;
}

// SIGNAL 0
void tlinsEditDatabaseObject::objectChanged(TlinsAstroBase::tlinsAstroCatalogItem _t1, int _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void tlinsEditDatabaseObject::objectCreated(TlinsAstroBase::tlinsAstroCatalogItem _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
