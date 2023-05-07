/****************************************************************************
** Meta object code from reading C++ file 'tlinsuimainwindow.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.15.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "tlinsuimainwindow.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'tlinsuimainwindow.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.15.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_tlinsUIMainWindow_t {
    QByteArrayData data[22];
    char stringdata0[238];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_tlinsUIMainWindow_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_tlinsUIMainWindow_t qt_meta_stringdata_tlinsUIMainWindow = {
    {
QT_MOC_LITERAL(0, 0, 17), // "tlinsUIMainWindow"
QT_MOC_LITERAL(1, 18, 8), // "logEvent"
QT_MOC_LITERAL(2, 27, 0), // ""
QT_MOC_LITERAL(3, 28, 4), // "line"
QT_MOC_LITERAL(4, 33, 15), // "logInstallEvent"
QT_MOC_LITERAL(5, 49, 14), // "updatePosition"
QT_MOC_LITERAL(6, 64, 1), // "x"
QT_MOC_LITERAL(7, 66, 1), // "y"
QT_MOC_LITERAL(8, 68, 2), // "ra"
QT_MOC_LITERAL(9, 71, 3), // "dec"
QT_MOC_LITERAL(10, 75, 11), // "popupStatus"
QT_MOC_LITERAL(11, 87, 11), // "std::string"
QT_MOC_LITERAL(12, 99, 12), // "logEventSlot"
QT_MOC_LITERAL(13, 112, 19), // "logInstallEventSlot"
QT_MOC_LITERAL(14, 132, 18), // "updatePositionSlot"
QT_MOC_LITERAL(15, 151, 18), // "devSetPositionSlot"
QT_MOC_LITERAL(16, 170, 14), // "devInStepsSlot"
QT_MOC_LITERAL(17, 185, 1), // "v"
QT_MOC_LITERAL(18, 187, 15), // "popupStatusSlot"
QT_MOC_LITERAL(19, 203, 3), // "str"
QT_MOC_LITERAL(20, 207, 13), // "actionConnect"
QT_MOC_LITERAL(21, 221, 16) // "actionDisconnect"

    },
    "tlinsUIMainWindow\0logEvent\0\0line\0"
    "logInstallEvent\0updatePosition\0x\0y\0"
    "ra\0dec\0popupStatus\0std::string\0"
    "logEventSlot\0logInstallEventSlot\0"
    "updatePositionSlot\0devSetPositionSlot\0"
    "devInStepsSlot\0v\0popupStatusSlot\0str\0"
    "actionConnect\0actionDisconnect"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_tlinsUIMainWindow[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
      12,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       4,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   74,    2, 0x06 /* Public */,
       4,    1,   77,    2, 0x06 /* Public */,
       5,    4,   80,    2, 0x06 /* Public */,
      10,    1,   89,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
      12,    1,   92,    2, 0x0a /* Public */,
      13,    1,   95,    2, 0x0a /* Public */,
      14,    4,   98,    2, 0x0a /* Public */,
      15,    0,  107,    2, 0x0a /* Public */,
      16,    1,  108,    2, 0x0a /* Public */,
      18,    1,  111,    2, 0x0a /* Public */,
      20,    0,  114,    2, 0x0a /* Public */,
      21,    0,  115,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void, QMetaType::QString,    3,
    QMetaType::Void, QMetaType::QString,    3,
    QMetaType::Void, QMetaType::Long, QMetaType::Long, QMetaType::Double, QMetaType::Double,    6,    7,    8,    9,
    QMetaType::Void, 0x80000000 | 11,    2,

 // slots: parameters
    QMetaType::Void, QMetaType::QString,    3,
    QMetaType::Void, QMetaType::QString,    3,
    QMetaType::Void, QMetaType::Long, QMetaType::Long, QMetaType::Double, QMetaType::Double,    6,    7,    8,    9,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Bool,   17,
    QMetaType::Void, 0x80000000 | 11,   19,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void tlinsUIMainWindow::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<tlinsUIMainWindow *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->logEvent((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 1: _t->logInstallEvent((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 2: _t->updatePosition((*reinterpret_cast< const long(*)>(_a[1])),(*reinterpret_cast< const long(*)>(_a[2])),(*reinterpret_cast< const double(*)>(_a[3])),(*reinterpret_cast< const double(*)>(_a[4]))); break;
        case 3: _t->popupStatus((*reinterpret_cast< const std::string(*)>(_a[1]))); break;
        case 4: _t->logEventSlot((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 5: _t->logInstallEventSlot((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 6: _t->updatePositionSlot((*reinterpret_cast< const long(*)>(_a[1])),(*reinterpret_cast< const long(*)>(_a[2])),(*reinterpret_cast< const double(*)>(_a[3])),(*reinterpret_cast< const double(*)>(_a[4]))); break;
        case 7: _t->devSetPositionSlot(); break;
        case 8: _t->devInStepsSlot((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 9: _t->popupStatusSlot((*reinterpret_cast< const std::string(*)>(_a[1]))); break;
        case 10: _t->actionConnect(); break;
        case 11: _t->actionDisconnect(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (tlinsUIMainWindow::*)(const QString );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&tlinsUIMainWindow::logEvent)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (tlinsUIMainWindow::*)(const QString );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&tlinsUIMainWindow::logInstallEvent)) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (tlinsUIMainWindow::*)(const long , const long , const double , const double );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&tlinsUIMainWindow::updatePosition)) {
                *result = 2;
                return;
            }
        }
        {
            using _t = void (tlinsUIMainWindow::*)(const std::string & );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&tlinsUIMainWindow::popupStatus)) {
                *result = 3;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject tlinsUIMainWindow::staticMetaObject = { {
    QMetaObject::SuperData::link<QMainWindow::staticMetaObject>(),
    qt_meta_stringdata_tlinsUIMainWindow.data,
    qt_meta_data_tlinsUIMainWindow,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *tlinsUIMainWindow::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *tlinsUIMainWindow::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_tlinsUIMainWindow.stringdata0))
        return static_cast<void*>(this);
    return QMainWindow::qt_metacast(_clname);
}

int tlinsUIMainWindow::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 12)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 12;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 12)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 12;
    }
    return _id;
}

// SIGNAL 0
void tlinsUIMainWindow::logEvent(const QString _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void tlinsUIMainWindow::logInstallEvent(const QString _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void tlinsUIMainWindow::updatePosition(const long _t1, const long _t2, const double _t3, const double _t4)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t3))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t4))) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void tlinsUIMainWindow::popupStatus(const std::string & _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
