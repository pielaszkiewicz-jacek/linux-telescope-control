/****************************************************************************
** Meta object code from reading C++ file 'tlinswastrodatabasesearch.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.5.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "tlinswastrodatabasesearch.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'tlinswastrodatabasesearch.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.5.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_tlinsWAstroDatabaseSearch_t {
    QByteArrayData data[3];
    char stringdata0[47];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_tlinsWAstroDatabaseSearch_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_tlinsWAstroDatabaseSearch_t qt_meta_stringdata_tlinsWAstroDatabaseSearch = {
    {
QT_MOC_LITERAL(0, 0, 25), // "tlinsWAstroDatabaseSearch"
QT_MOC_LITERAL(1, 26, 19), // "updateConditionText"
QT_MOC_LITERAL(2, 46, 0) // ""

    },
    "tlinsWAstroDatabaseSearch\0updateConditionText\0"
    ""
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_tlinsWAstroDatabaseSearch[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       1,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   19,    2, 0x0a /* Public */,

 // slots: parameters
    QMetaType::Void,

       0        // eod
};

void tlinsWAstroDatabaseSearch::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        tlinsWAstroDatabaseSearch *_t = static_cast<tlinsWAstroDatabaseSearch *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->updateConditionText(); break;
        default: ;
        }
    }
    Q_UNUSED(_a);
}

const QMetaObject tlinsWAstroDatabaseSearch::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_tlinsWAstroDatabaseSearch.data,
      qt_meta_data_tlinsWAstroDatabaseSearch,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *tlinsWAstroDatabaseSearch::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *tlinsWAstroDatabaseSearch::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_tlinsWAstroDatabaseSearch.stringdata0))
        return static_cast<void*>(const_cast< tlinsWAstroDatabaseSearch*>(this));
    return QWidget::qt_metacast(_clname);
}

int tlinsWAstroDatabaseSearch::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
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
QT_END_MOC_NAMESPACE
