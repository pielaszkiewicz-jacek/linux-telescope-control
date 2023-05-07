/****************************************************************************
** Meta object code from reading C++ file 'tlinsinfowidget.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.15.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "tlinsinfowidget.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'tlinsinfowidget.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.15.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_tlinsInfoWidget_t {
    QByteArrayData data[18];
    char stringdata0[253];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_tlinsInfoWidget_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_tlinsInfoWidget_t qt_meta_stringdata_tlinsInfoWidget = {
    {
QT_MOC_LITERAL(0, 0, 15), // "tlinsInfoWidget"
QT_MOC_LITERAL(1, 16, 8), // "updateCb"
QT_MOC_LITERAL(2, 25, 0), // ""
QT_MOC_LITERAL(3, 26, 8), // "reloadCb"
QT_MOC_LITERAL(4, 35, 7), // "storeCb"
QT_MOC_LITERAL(5, 43, 6), // "loadCb"
QT_MOC_LITERAL(6, 50, 11), // "downloadCfg"
QT_MOC_LITERAL(7, 62, 16), // "downloadCfgAstro"
QT_MOC_LITERAL(8, 79, 23), // "downloadCfgAstroService"
QT_MOC_LITERAL(9, 103, 9), // "uploadCfg"
QT_MOC_LITERAL(10, 113, 14), // "uploadCfgAstro"
QT_MOC_LITERAL(11, 128, 21), // "uploadCfgAstroService"
QT_MOC_LITERAL(12, 150, 14), // "downloadLogsCb"
QT_MOC_LITERAL(13, 165, 12), // "removeLogsCb"
QT_MOC_LITERAL(14, 178, 24), // "selectOutputDirForLogsCb"
QT_MOC_LITERAL(15, 203, 18), // "sofUpdatePerfomeCb"
QT_MOC_LITERAL(16, 222, 21), // "sofUpdateSelectFileCb"
QT_MOC_LITERAL(17, 244, 8) // "clearLog"

    },
    "tlinsInfoWidget\0updateCb\0\0reloadCb\0"
    "storeCb\0loadCb\0downloadCfg\0downloadCfgAstro\0"
    "downloadCfgAstroService\0uploadCfg\0"
    "uploadCfgAstro\0uploadCfgAstroService\0"
    "downloadLogsCb\0removeLogsCb\0"
    "selectOutputDirForLogsCb\0sofUpdatePerfomeCb\0"
    "sofUpdateSelectFileCb\0clearLog"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_tlinsInfoWidget[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
      16,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   94,    2, 0x0a /* Public */,
       3,    0,   95,    2, 0x0a /* Public */,
       4,    0,   96,    2, 0x0a /* Public */,
       5,    0,   97,    2, 0x0a /* Public */,
       6,    0,   98,    2, 0x0a /* Public */,
       7,    0,   99,    2, 0x0a /* Public */,
       8,    0,  100,    2, 0x0a /* Public */,
       9,    0,  101,    2, 0x0a /* Public */,
      10,    0,  102,    2, 0x0a /* Public */,
      11,    0,  103,    2, 0x0a /* Public */,
      12,    0,  104,    2, 0x0a /* Public */,
      13,    0,  105,    2, 0x0a /* Public */,
      14,    0,  106,    2, 0x0a /* Public */,
      15,    0,  107,    2, 0x0a /* Public */,
      16,    0,  108,    2, 0x0a /* Public */,
      17,    0,  109,    2, 0x0a /* Public */,

 // slots: parameters
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
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void tlinsInfoWidget::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<tlinsInfoWidget *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->updateCb(); break;
        case 1: _t->reloadCb(); break;
        case 2: _t->storeCb(); break;
        case 3: _t->loadCb(); break;
        case 4: _t->downloadCfg(); break;
        case 5: _t->downloadCfgAstro(); break;
        case 6: _t->downloadCfgAstroService(); break;
        case 7: _t->uploadCfg(); break;
        case 8: _t->uploadCfgAstro(); break;
        case 9: _t->uploadCfgAstroService(); break;
        case 10: _t->downloadLogsCb(); break;
        case 11: _t->removeLogsCb(); break;
        case 12: _t->selectOutputDirForLogsCb(); break;
        case 13: _t->sofUpdatePerfomeCb(); break;
        case 14: _t->sofUpdateSelectFileCb(); break;
        case 15: _t->clearLog(); break;
        default: ;
        }
    }
    (void)_a;
}

QT_INIT_METAOBJECT const QMetaObject tlinsInfoWidget::staticMetaObject = { {
    QMetaObject::SuperData::link<QWidget::staticMetaObject>(),
    qt_meta_stringdata_tlinsInfoWidget.data,
    qt_meta_data_tlinsInfoWidget,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *tlinsInfoWidget::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *tlinsInfoWidget::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_tlinsInfoWidget.stringdata0))
        return static_cast<void*>(this);
    return QWidget::qt_metacast(_clname);
}

int tlinsInfoWidget::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
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
QT_WARNING_POP
QT_END_MOC_NAMESPACE
