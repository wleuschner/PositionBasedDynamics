/****************************************************************************
** Meta object code from reading C++ file 'canvas.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.2.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../PBD_CG_Seminar/canvas.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'canvas.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.2.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_Canvas_t {
    QByteArrayData data[13];
    char stringdata[174];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    offsetof(qt_meta_stringdata_Canvas_t, stringdata) + ofs \
        - idx * sizeof(QByteArrayData) \
    )
static const qt_meta_stringdata_Canvas_t qt_meta_stringdata_Canvas = {
    {
QT_MOC_LITERAL(0, 0, 6),
QT_MOC_LITERAL(1, 7, 6),
QT_MOC_LITERAL(2, 14, 0),
QT_MOC_LITERAL(3, 15, 17),
QT_MOC_LITERAL(4, 33, 3),
QT_MOC_LITERAL(5, 37, 14),
QT_MOC_LITERAL(6, 52, 3),
QT_MOC_LITERAL(7, 56, 22),
QT_MOC_LITERAL(8, 79, 23),
QT_MOC_LITERAL(9, 103, 21),
QT_MOC_LITERAL(10, 125, 15),
QT_MOC_LITERAL(11, 141, 15),
QT_MOC_LITERAL(12, 157, 15)
    },
    "Canvas\0update\0\0changeSolverLoops\0num\0"
    "changePressure\0val\0changeStretchStiffness\0"
    "changeCompressStiffness\0changeBendingStifness\0"
    "scene1Triggered\0scene2Triggered\0"
    "scene3Triggered\0"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_Canvas[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       9,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   59,    2, 0x0a,
       3,    1,   60,    2, 0x0a,
       5,    1,   63,    2, 0x0a,
       7,    1,   66,    2, 0x0a,
       8,    1,   69,    2, 0x0a,
       9,    1,   72,    2, 0x0a,
      10,    0,   75,    2, 0x0a,
      11,    0,   76,    2, 0x0a,
      12,    0,   77,    2, 0x0a,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,    4,
    QMetaType::Void, QMetaType::Double,    6,
    QMetaType::Void, QMetaType::Double,    6,
    QMetaType::Void, QMetaType::Double,    6,
    QMetaType::Void, QMetaType::Double,    6,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void Canvas::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Canvas *_t = static_cast<Canvas *>(_o);
        switch (_id) {
        case 0: _t->update(); break;
        case 1: _t->changeSolverLoops((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 2: _t->changePressure((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 3: _t->changeStretchStiffness((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 4: _t->changeCompressStiffness((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 5: _t->changeBendingStifness((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 6: _t->scene1Triggered(); break;
        case 7: _t->scene2Triggered(); break;
        case 8: _t->scene3Triggered(); break;
        default: ;
        }
    }
}

const QMetaObject Canvas::staticMetaObject = {
    { &QGLWidget::staticMetaObject, qt_meta_stringdata_Canvas.data,
      qt_meta_data_Canvas,  qt_static_metacall, 0, 0}
};


const QMetaObject *Canvas::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *Canvas::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_Canvas.stringdata))
        return static_cast<void*>(const_cast< Canvas*>(this));
    return QGLWidget::qt_metacast(_clname);
}

int Canvas::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QGLWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 9)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 9;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 9)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 9;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
