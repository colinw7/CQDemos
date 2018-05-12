/****************************************************************************
** Meta object code from reading C++ file 'CQGLWaterSurface.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.5.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../CQGLWaterSurface.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'CQGLWaterSurface.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.5.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_CQGLWaterSurface_t {
    QByteArrayData data[4];
    char stringdata0[47];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_CQGLWaterSurface_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_CQGLWaterSurface_t qt_meta_stringdata_CQGLWaterSurface = {
    {
QT_MOC_LITERAL(0, 0, 16), // "CQGLWaterSurface"
QT_MOC_LITERAL(1, 17, 11), // "controlSlot"
QT_MOC_LITERAL(2, 29, 0), // ""
QT_MOC_LITERAL(3, 30, 16) // "stepWaterSurface"

    },
    "CQGLWaterSurface\0controlSlot\0\0"
    "stepWaterSurface"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_CQGLWaterSurface[] = {

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

void CQGLWaterSurface::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        CQGLWaterSurface *_t = static_cast<CQGLWaterSurface *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->controlSlot(); break;
        case 1: _t->stepWaterSurface(); break;
        default: ;
        }
    }
    Q_UNUSED(_a);
}

const QMetaObject CQGLWaterSurface::staticMetaObject = {
    { &CQMainWindow::staticMetaObject, qt_meta_stringdata_CQGLWaterSurface.data,
      qt_meta_data_CQGLWaterSurface,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *CQGLWaterSurface::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *CQGLWaterSurface::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_CQGLWaterSurface.stringdata0))
        return static_cast<void*>(const_cast< CQGLWaterSurface*>(this));
    return CQMainWindow::qt_metacast(_clname);
}

int CQGLWaterSurface::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
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
struct qt_meta_stringdata_CQGLWaterSurfaceCanvas_t {
    QByteArrayData data[1];
    char stringdata0[23];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_CQGLWaterSurfaceCanvas_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_CQGLWaterSurfaceCanvas_t qt_meta_stringdata_CQGLWaterSurfaceCanvas = {
    {
QT_MOC_LITERAL(0, 0, 22) // "CQGLWaterSurfaceCanvas"

    },
    "CQGLWaterSurfaceCanvas"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_CQGLWaterSurfaceCanvas[] = {

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

void CQGLWaterSurfaceCanvas::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    Q_UNUSED(_o);
    Q_UNUSED(_id);
    Q_UNUSED(_c);
    Q_UNUSED(_a);
}

const QMetaObject CQGLWaterSurfaceCanvas::staticMetaObject = {
    { &QGLWidget::staticMetaObject, qt_meta_stringdata_CQGLWaterSurfaceCanvas.data,
      qt_meta_data_CQGLWaterSurfaceCanvas,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *CQGLWaterSurfaceCanvas::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *CQGLWaterSurfaceCanvas::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_CQGLWaterSurfaceCanvas.stringdata0))
        return static_cast<void*>(const_cast< CQGLWaterSurfaceCanvas*>(this));
    return QGLWidget::qt_metacast(_clname);
}

int CQGLWaterSurfaceCanvas::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QGLWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    return _id;
}
QT_END_MOC_NAMESPACE
