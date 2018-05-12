/****************************************************************************
** Meta object code from reading C++ file 'CQFireworks.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.5.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../CQFireworks.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'CQFireworks.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.5.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_CQFireworksTest_t {
    QByteArrayData data[5];
    char stringdata0[34];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_CQFireworksTest_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_CQFireworksTest_t qt_meta_stringdata_CQFireworksTest = {
    {
QT_MOC_LITERAL(0, 0, 15), // "CQFireworksTest"
QT_MOC_LITERAL(1, 16, 6), // "config"
QT_MOC_LITERAL(2, 23, 0), // ""
QT_MOC_LITERAL(3, 24, 4), // "quit"
QT_MOC_LITERAL(4, 29, 4) // "help"

    },
    "CQFireworksTest\0config\0\0quit\0help"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_CQFireworksTest[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       3,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   29,    2, 0x08 /* Private */,
       3,    0,   30,    2, 0x08 /* Private */,
       4,    0,   31,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void CQFireworksTest::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        CQFireworksTest *_t = static_cast<CQFireworksTest *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->config(); break;
        case 1: _t->quit(); break;
        case 2: _t->help(); break;
        default: ;
        }
    }
    Q_UNUSED(_a);
}

const QMetaObject CQFireworksTest::staticMetaObject = {
    { &QMainWindow::staticMetaObject, qt_meta_stringdata_CQFireworksTest.data,
      qt_meta_data_CQFireworksTest,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *CQFireworksTest::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *CQFireworksTest::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_CQFireworksTest.stringdata0))
        return static_cast<void*>(const_cast< CQFireworksTest*>(this));
    return QMainWindow::qt_metacast(_clname);
}

int CQFireworksTest::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 3)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 3;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 3)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 3;
    }
    return _id;
}
struct qt_meta_stringdata_CQFireworks_t {
    QByteArrayData data[4];
    char stringdata0[33];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_CQFireworks_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_CQFireworks_t qt_meta_stringdata_CQFireworks = {
    {
QT_MOC_LITERAL(0, 0, 11), // "CQFireworks"
QT_MOC_LITERAL(1, 12, 8), // "stepSlot"
QT_MOC_LITERAL(2, 21, 0), // ""
QT_MOC_LITERAL(3, 22, 10) // "updateSlot"

    },
    "CQFireworks\0stepSlot\0\0updateSlot"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_CQFireworks[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       2,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   24,    2, 0x08 /* Private */,
       3,    0,   25,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void CQFireworks::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        CQFireworks *_t = static_cast<CQFireworks *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->stepSlot(); break;
        case 1: _t->updateSlot(); break;
        default: ;
        }
    }
    Q_UNUSED(_a);
}

const QMetaObject CQFireworks::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_CQFireworks.data,
      qt_meta_data_CQFireworks,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *CQFireworks::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *CQFireworks::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_CQFireworks.stringdata0))
        return static_cast<void*>(const_cast< CQFireworks*>(this));
    if (!strcmp(_clname, "CFireworks"))
        return static_cast< CFireworks*>(const_cast< CQFireworks*>(this));
    return QWidget::qt_metacast(_clname);
}

int CQFireworks::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 2)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 2;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 2)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 2;
    }
    return _id;
}
struct qt_meta_stringdata_CQFireworksConfig_t {
    QByteArrayData data[3];
    char stringdata0[32];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_CQFireworksConfig_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_CQFireworksConfig_t qt_meta_stringdata_CQFireworksConfig = {
    {
QT_MOC_LITERAL(0, 0, 17), // "CQFireworksConfig"
QT_MOC_LITERAL(1, 18, 12), // "updateValues"
QT_MOC_LITERAL(2, 31, 0) // ""

    },
    "CQFireworksConfig\0updateValues\0"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_CQFireworksConfig[] = {

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
       1,    0,   19,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Void,

       0        // eod
};

void CQFireworksConfig::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        CQFireworksConfig *_t = static_cast<CQFireworksConfig *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->updateValues(); break;
        default: ;
        }
    }
    Q_UNUSED(_a);
}

const QMetaObject CQFireworksConfig::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_CQFireworksConfig.data,
      qt_meta_data_CQFireworksConfig,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *CQFireworksConfig::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *CQFireworksConfig::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_CQFireworksConfig.stringdata0))
        return static_cast<void*>(const_cast< CQFireworksConfig*>(this));
    return QDialog::qt_metacast(_clname);
}

int CQFireworksConfig::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
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
