/****************************************************************************
** Meta object code from reading C++ file 'tiles_editor.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.4.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../editor/tiles/tiles_editor.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'tiles_editor.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.4.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_TilesEditor_t {
    QByteArrayData data[10];
    char stringdata[185];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_TilesEditor_t, stringdata) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_TilesEditor_t qt_meta_stringdata_TilesEditor = {
    {
QT_MOC_LITERAL(0, 0, 11), // "TilesEditor"
QT_MOC_LITERAL(1, 12, 23), // "on_actionOpen_triggered"
QT_MOC_LITERAL(2, 36, 0), // ""
QT_MOC_LITERAL(3, 37, 22), // "on_actionNew_triggered"
QT_MOC_LITERAL(4, 60, 26), // "on_actionSave_as_triggered"
QT_MOC_LITERAL(5, 87, 27), // "on_tTable_cellDoubleClicked"
QT_MOC_LITERAL(6, 115, 3), // "row"
QT_MOC_LITERAL(7, 119, 6), // "column"
QT_MOC_LITERAL(8, 126, 27), // "on_actionNew_tile_triggered"
QT_MOC_LITERAL(9, 154, 30) // "on_actionDelete_tile_triggered"

    },
    "TilesEditor\0on_actionOpen_triggered\0"
    "\0on_actionNew_triggered\0"
    "on_actionSave_as_triggered\0"
    "on_tTable_cellDoubleClicked\0row\0column\0"
    "on_actionNew_tile_triggered\0"
    "on_actionDelete_tile_triggered"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_TilesEditor[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       6,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   44,    2, 0x08 /* Private */,
       3,    0,   45,    2, 0x08 /* Private */,
       4,    0,   46,    2, 0x08 /* Private */,
       5,    2,   47,    2, 0x08 /* Private */,
       8,    0,   52,    2, 0x08 /* Private */,
       9,    0,   53,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int, QMetaType::Int,    6,    7,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void TilesEditor::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        TilesEditor *_t = static_cast<TilesEditor *>(_o);
        switch (_id) {
        case 0: _t->on_actionOpen_triggered(); break;
        case 1: _t->on_actionNew_triggered(); break;
        case 2: _t->on_actionSave_as_triggered(); break;
        case 3: _t->on_tTable_cellDoubleClicked((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 4: _t->on_actionNew_tile_triggered(); break;
        case 5: _t->on_actionDelete_tile_triggered(); break;
        default: ;
        }
    }
}

const QMetaObject TilesEditor::staticMetaObject = {
    { &QMainWindow::staticMetaObject, qt_meta_stringdata_TilesEditor.data,
      qt_meta_data_TilesEditor,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *TilesEditor::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *TilesEditor::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_TilesEditor.stringdata))
        return static_cast<void*>(const_cast< TilesEditor*>(this));
    return QMainWindow::qt_metacast(_clname);
}

int TilesEditor::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 6)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 6;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 6)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 6;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
