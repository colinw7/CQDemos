/****************************************************************************
** Meta object code from reading C++ file 'CQGLFlocking.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.5.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../CQGLFlocking.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'CQGLFlocking.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.5.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_CQGLFlocking_t {
    QByteArrayData data[4];
    char stringdata0[41];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_CQGLFlocking_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_CQGLFlocking_t qt_meta_stringdata_CQGLFlocking = {
    {
QT_MOC_LITERAL(0, 0, 12), // "CQGLFlocking"
QT_MOC_LITERAL(1, 13, 11), // "controlSlot"
QT_MOC_LITERAL(2, 25, 0), // ""
QT_MOC_LITERAL(3, 26, 14) // "updateFlocking"

    },
    "CQGLFlocking\0controlSlot\0\0updateFlocking"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_CQGLFlocking[] = {

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

void CQGLFlocking::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        CQGLFlocking *_t = static_cast<CQGLFlocking *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->controlSlot(); break;
        case 1: _t->updateFlocking(); break;
        default: ;
        }
    }
    Q_UNUSED(_a);
}

const QMetaObject CQGLFlocking::staticMetaObject = {
    { &CQMainWindow::staticMetaObject, qt_meta_stringdata_CQGLFlocking.data,
      qt_meta_data_CQGLFlocking,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *CQGLFlocking::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *CQGLFlocking::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_CQGLFlocking.stringdata0))
        return static_cast<void*>(const_cast< CQGLFlocking*>(this));
    return CQMainWindow::qt_metacast(_clname);
}

int CQGLFlocking::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = CQMainWindow::qt_metacall(_c, _id, _a);
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
struct qt_meta_stringdata_CQGLFlockingCanvas_t {
    QByteArrayData data[1];
    char stringdata0[19];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_CQGLFlockingCanvas_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_CQGLFlockingCanvas_t qt_meta_stringdata_CQGLFlockingCanvas = {
    {
QT_MOC_LITERAL(0, 0, 18) // "CQGLFlockingCanvas"

    },
    "CQGLFlockingCanvas"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_CQGLFlockingCanvas[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       0,    0, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

       0        // eod
};

void CQGLFlockingCanvas::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    Q_UNUSED(_o);
    Q_UNUSED(_id);
    Q_UNUSED(_c);
    Q_UNUSED(_a);
}

const QMetaObject CQGLFlockingCanvas::staticMetaObject = {
    { &QGLWidget::staticMetaObject, qt_meta_stringdata_CQGLFlockingCanvas.data,
      qt_meta_data_CQGLFlockingCanvas,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *CQGLFlockingCanvas::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *CQGLFlockingCanvas::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_CQGLFlockingCanvas.stringdata0))
        return static_cast<void*>(const_cast< CQGLFlockingCanvas*>(this));
    return QGLWidget::qt_metacast(_clname);
}

int CQGLFlockingCanvas::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QGLWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    return _id;
}
QT_END_MOC_NAMESPACE
