/****************************************************************************
** Meta object code from reading C++ file 'CQGLControl.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.5.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../CQGLControl.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'CQGLControl.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.5.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_CQGLControl_t {
    QByteArrayData data[9];
    char stringdata0[88];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_CQGLControl_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_CQGLControl_t qt_meta_stringdata_CQGLControl = {
    {
QT_MOC_LITERAL(0, 0, 11), // "CQGLControl"
QT_MOC_LITERAL(1, 12, 12), // "stateChanged"
QT_MOC_LITERAL(2, 25, 0), // ""
QT_MOC_LITERAL(3, 26, 9), // "depthSlot"
QT_MOC_LITERAL(4, 36, 8), // "cullSlot"
QT_MOC_LITERAL(5, 45, 9), // "lightSlot"
QT_MOC_LITERAL(6, 55, 11), // "outlineSlot"
QT_MOC_LITERAL(7, 67, 9), // "frontSlot"
QT_MOC_LITERAL(8, 77, 10) // "smoothSlot"

    },
    "CQGLControl\0stateChanged\0\0depthSlot\0"
    "cullSlot\0lightSlot\0outlineSlot\0frontSlot\0"
    "smoothSlot"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_CQGLControl[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       7,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,   49,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       3,    1,   50,    2, 0x08 /* Private */,
       4,    1,   53,    2, 0x08 /* Private */,
       5,    1,   56,    2, 0x08 /* Private */,
       6,    1,   59,    2, 0x08 /* Private */,
       7,    1,   62,    2, 0x08 /* Private */,
       8,    1,   65,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Void,

 // slots: parameters
    QMetaType::Void, QMetaType::Bool,    2,
    QMetaType::Void, QMetaType::Bool,    2,
    QMetaType::Void, QMetaType::Bool,    2,
    QMetaType::Void, QMetaType::Bool,    2,
    QMetaType::Void, QMetaType::Bool,    2,
    QMetaType::Void, QMetaType::Bool,    2,

       0        // eod
};

void CQGLControl::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        CQGLControl *_t = static_cast<CQGLControl *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->stateChanged(); break;
        case 1: _t->depthSlot((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 2: _t->cullSlot((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 3: _t->lightSlot((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 4: _t->outlineSlot((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 5: _t->frontSlot((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 6: _t->smoothSlot((*reinterpret_cast< bool(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (CQGLControl::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&CQGLControl::stateChanged)) {
                *result = 0;
            }
        }
    }
}

const QMetaObject CQGLControl::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_CQGLControl.data,
      qt_meta_data_CQGLControl,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *CQGLControl::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *CQGLControl::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_CQGLControl.stringdata0))
        return static_cast<void*>(const_cast< CQGLControl*>(this));
    return QObject::qt_metacast(_clname);
}

int CQGLControl::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
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

// SIGNAL 0
void CQGLControl::stateChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 0, Q_NULLPTR);
}
struct qt_meta_stringdata_CQGLControlToolBar_t {
    QByteArrayData data[3];
    char stringdata0[33];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_CQGLControlToolBar_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_CQGLControlToolBar_t qt_meta_stringdata_CQGLControlToolBar = {
    {
QT_MOC_LITERAL(0, 0, 18), // "CQGLControlToolBar"
QT_MOC_LITERAL(1, 19, 12), // "stateChanged"
QT_MOC_LITERAL(2, 32, 0) // ""

    },
    "CQGLControlToolBar\0stateChanged\0"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_CQGLControlToolBar[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       1,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,   19,    2, 0x06 /* Public */,

 // signals: parameters
    QMetaType::Void,

       0        // eod
};

void CQGLControlToolBar::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        CQGLControlToolBar *_t = static_cast<CQGLControlToolBar *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->stateChanged(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (CQGLControlToolBar::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&CQGLControlToolBar::stateChanged)) {
                *result = 0;
            }
        }
    }
    Q_UNUSED(_a);
}

const QMetaObject CQGLControlToolBar::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_CQGLControlToolBar.data,
      qt_meta_data_CQGLControlToolBar,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *CQGLControlToolBar::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *CQGLControlToolBar::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_CQGLControlToolBar.stringdata0))
        return static_cast<void*>(const_cast< CQGLControlToolBar*>(this));
    return QWidget::qt_metacast(_clname);
}

int CQGLControlToolBar::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
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

// SIGNAL 0
void CQGLControlToolBar::stateChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 0, Q_NULLPTR);
}
QT_END_MOC_NAMESPACE
