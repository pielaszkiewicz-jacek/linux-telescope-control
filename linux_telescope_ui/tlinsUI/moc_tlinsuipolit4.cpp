/****************************************************************************
** Meta object code from reading C++ file 'tlinsuipolit4.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.15.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "tlinsuipolit4.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'tlinsuipolit4.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.15.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_tlinsUiPolit4_t {
    QByteArrayData data[21];
    char stringdata0[235];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_tlinsUiPolit4_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_tlinsUiPolit4_t qt_meta_stringdata_tlinsUiPolit4 = {
    {
QT_MOC_LITERAL(0, 0, 13), // "tlinsUiPolit4"
QT_MOC_LITERAL(1, 14, 12), // "setSignlMode"
QT_MOC_LITERAL(2, 27, 0), // ""
QT_MOC_LITERAL(3, 28, 11), // "displayMode"
QT_MOC_LITERAL(4, 40, 12), // "saveGeometry"
QT_MOC_LITERAL(5, 53, 15), // "restoreGeometry"
QT_MOC_LITERAL(6, 69, 11), // "setModeSlot"
QT_MOC_LITERAL(7, 81, 1), // "m"
QT_MOC_LITERAL(8, 83, 14), // "onInStepChange"
QT_MOC_LITERAL(9, 98, 5), // "state"
QT_MOC_LITERAL(10, 104, 11), // "onSpeedMode"
QT_MOC_LITERAL(11, 116, 9), // "upClicked"
QT_MOC_LITERAL(12, 126, 9), // "upRelised"
QT_MOC_LITERAL(13, 136, 11), // "downClicked"
QT_MOC_LITERAL(14, 148, 11), // "downRelised"
QT_MOC_LITERAL(15, 160, 11), // "leftClicked"
QT_MOC_LITERAL(16, 172, 11), // "leftRelised"
QT_MOC_LITERAL(17, 184, 12), // "rightClicked"
QT_MOC_LITERAL(18, 197, 12), // "rightRelised"
QT_MOC_LITERAL(19, 210, 11), // "stopPressed"
QT_MOC_LITERAL(20, 222, 12) // "abortPressed"

    },
    "tlinsUiPolit4\0setSignlMode\0\0displayMode\0"
    "saveGeometry\0restoreGeometry\0setModeSlot\0"
    "m\0onInStepChange\0state\0onSpeedMode\0"
    "upClicked\0upRelised\0downClicked\0"
    "downRelised\0leftClicked\0leftRelised\0"
    "rightClicked\0rightRelised\0stopPressed\0"
    "abortPressed"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_tlinsUiPolit4[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
      16,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       3,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   94,    2, 0x06 /* Public */,
       4,    0,   97,    2, 0x06 /* Public */,
       5,    0,   98,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       6,    1,   99,    2, 0x0a /* Public */,
       8,    1,  102,    2, 0x0a /* Public */,
      10,    1,  105,    2, 0x0a /* Public */,
      11,    0,  108,    2, 0x0a /* Public */,
      12,    0,  109,    2, 0x0a /* Public */,
      13,    0,  110,    2, 0x0a /* Public */,
      14,    0,  111,    2, 0x0a /* Public */,
      15,    0,  112,    2, 0x0a /* Public */,
      16,    0,  113,    2, 0x0a /* Public */,
      17,    0,  114,    2, 0x0a /* Public */,
      18,    0,  115,    2, 0x0a /* Public */,
      19,    0,  116,    2, 0x0a /* Public */,
      20,    0,  117,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void, 0x80000000 | 3,    2,
    QMetaType::Void,
    QMetaType::Void,

 // slots: parameters
    QMetaType::Void, 0x80000000 | 3,    7,
    QMetaType::Void, QMetaType::Int,    9,
    QMetaType::Void, QMetaType::Int,    9,
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

       0        // eod
};

void tlinsUiPolit4::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<tlinsUiPolit4 *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->setSignlMode((*reinterpret_cast< displayMode(*)>(_a[1]))); break;
        case 1: _t->saveGeometry(); break;
        case 2: _t->restoreGeometry(); break;
        case 3: _t->setModeSlot((*reinterpret_cast< const displayMode(*)>(_a[1]))); break;
        case 4: _t->onInStepChange((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 5: _t->onSpeedMode((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 6: _t->upClicked(); break;
        case 7: _t->upRelised(); break;
        case 8: _t->downClicked(); break;
        case 9: _t->downRelised(); break;
        case 10: _t->leftClicked(); break;
        case 11: _t->leftRelised(); break;
        case 12: _t->rightClicked(); break;
        case 13: _t->rightRelised(); break;
        case 14: _t->stopPressed(); break;
        case 15: _t->abortPressed(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (tlinsUiPolit4::*)(displayMode );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&tlinsUiPolit4::setSignlMode)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (tlinsUiPolit4::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&tlinsUiPolit4::saveGeometry)) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (tlinsUiPolit4::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&tlinsUiPolit4::restoreGeometry)) {
                *result = 2;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject tlinsUiPolit4::staticMetaObject = { {
    QMetaObject::SuperData::link<QWidget::staticMetaObject>(),
    qt_meta_stringdata_tlinsUiPolit4.data,
    qt_meta_data_tlinsUiPolit4,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *tlinsUiPolit4::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *tlinsUiPolit4::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_tlinsUiPolit4.stringdata0))
        return static_cast<void*>(this);
    return QWidget::qt_metacast(_clname);
}

int tlinsUiPolit4::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 16)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 16;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 16)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 16;
    }
    return _id;
}

// SIGNAL 0
void tlinsUiPolit4::setSignlMode(displayMode _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void tlinsUiPolit4::saveGeometry()
{
    QMetaObject::activate(this, &staticMetaObject, 1, nullptr);
}

// SIGNAL 2
void tlinsUiPolit4::restoreGeometry()
{
    QMetaObject::activate(this, &staticMetaObject, 2, nullptr);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
