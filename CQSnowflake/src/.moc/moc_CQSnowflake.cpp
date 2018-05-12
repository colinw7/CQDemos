/****************************************************************************
** Meta object code from reading C++ file 'CQSnowflake.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.5.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../CQSnowflake.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'CQSnowflake.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.5.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_CQSnowflakeTest_t {
    QByteArrayData data[5];
    char stringdata0[34];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_CQSnowflakeTest_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_CQSnowflakeTest_t qt_meta_stringdata_CQSnowflakeTest = {
    {
QT_MOC_LITERAL(0, 0, 15), // "CQSnowflakeTest"
QT_MOC_LITERAL(1, 16, 6), // "config"
QT_MOC_LITERAL(2, 23, 0), // ""
QT_MOC_LITERAL(3, 24, 4), // "quit"
QT_MOC_LITERAL(4, 29, 4) // "help"

    },
    "CQSnowflakeTest\0config\0\0quit\0help"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_CQSnowflakeTest[] = {

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

void CQSnowflakeTest::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        CQSnowflakeTest *_t = static_cast<CQSnowflakeTest *>(_o);
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

const QMetaObject CQSnowflakeTest::staticMetaObject = {
    { &QMainWindow::staticMetaObject, qt_meta_stringdata_CQSnowflakeTest.data,
      qt_meta_data_CQSnowflakeTest,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *CQSnowflakeTest::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *CQSnowflakeTest::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_CQSnowflakeTest.stringdata0))
        return static_cast<void*>(const_cast< CQSnowflakeTest*>(this));
    return QMainWindow::qt_metacast(_clname);
}

int CQSnowflakeTest::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
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
struct qt_meta_stringdata_CQSnowflake_t {
    QByteArrayData data[4];
    char stringdata0[33];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_CQSnowflake_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_CQSnowflake_t qt_meta_stringdata_CQSnowflake = {
    {
QT_MOC_LITERAL(0, 0, 11), // "CQSnowflake"
QT_MOC_LITERAL(1, 12, 8), // "stepSlot"
QT_MOC_LITERAL(2, 21, 0), // ""
QT_MOC_LITERAL(3, 22, 10) // "updateSlot"

    },
    "CQSnowflake\0stepSlot\0\0updateSlot"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_CQSnowflake[] = {

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

void CQSnowflake::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        CQSnowflake *_t = static_cast<CQSnowflake *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->stepSlot(); break;
        case 1: _t->updateSlot(); break;
        default: ;
        }
    }
    Q_UNUSED(_a);
}

const QMetaObject CQSnowflake::staticMetaObject = {
    { &CQCanvas2D::staticMetaObject, qt_meta_stringdata_CQSnowflake.data,
      qt_meta_data_CQSnowflake,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *CQSnowflake::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *CQSnowflake::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_CQSnowflake.stringdata0))
        return static_cast<void*>(const_cast< CQSnowflake*>(this));
    if (!strcmp(_clname, "CSnowflake"))
        return static_cast< CSnowflake*>(const_cast< CQSnowflake*>(this));
    return CQCanvas2D::qt_metacast(_clname);
}

int CQSnowflake::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = CQCanvas2D::qt_metacall(_c, _id, _a);
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
struct qt_meta_stringdata_CQSnowflakeConfig_t {
    QByteArrayData data[3];
    char stringdata0[32];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_CQSnowflakeConfig_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_CQSnowflakeConfig_t qt_meta_stringdata_CQSnowflakeConfig = {
    {
QT_MOC_LITERAL(0, 0, 17), // "CQSnowflakeConfig"
QT_MOC_LITERAL(1, 18, 12), // "updateValues"
QT_MOC_LITERAL(2, 31, 0) // ""

    },
    "CQSnowflakeConfig\0updateValues\0"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_CQSnowflakeConfig[] = {

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

void CQSnowflakeConfig::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        CQSnowflakeConfig *_t = static_cast<CQSnowflakeConfig *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->updateValues(); break;
        default: ;
        }
    }
    Q_UNUSED(_a);
}

const QMetaObject CQSnowflakeConfig::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_CQSnowflakeConfig.data,
      qt_meta_data_CQSnowflakeConfig,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *CQSnowflakeConfig::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *CQSnowflakeConfig::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_CQSnowflakeConfig.stringdata0))
        return static_cast<void*>(const_cast< CQSnowflakeConfig*>(this));
    return QDialog::qt_metacast(_clname);
}

int CQSnowflakeConfig::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
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
