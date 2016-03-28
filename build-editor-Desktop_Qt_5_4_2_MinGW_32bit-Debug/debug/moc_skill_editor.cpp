/****************************************************************************
** Meta object code from reading C++ file 'skill_editor.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.4.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../editor/skills/skill_editor.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'skill_editor.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.4.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_SkillEditor_t {
    QByteArrayData data[10];
    char stringdata[192];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_SkillEditor_t, stringdata) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_SkillEditor_t qt_meta_stringdata_SkillEditor = {
    {
QT_MOC_LITERAL(0, 0, 11), // "SkillEditor"
QT_MOC_LITERAL(1, 12, 23), // "on_actionOpen_triggered"
QT_MOC_LITERAL(2, 36, 0), // ""
QT_MOC_LITERAL(3, 37, 26), // "on_actionSave_as_triggered"
QT_MOC_LITERAL(4, 64, 27), // "on_actionNew_file_triggered"
QT_MOC_LITERAL(5, 92, 31), // "on_actionDelete_Skill_triggered"
QT_MOC_LITERAL(6, 124, 28), // "on_actionNew_Skill_triggered"
QT_MOC_LITERAL(7, 153, 27), // "on_sTable_cellDoubleClicked"
QT_MOC_LITERAL(8, 181, 3), // "row"
QT_MOC_LITERAL(9, 185, 6) // "column"

    },
    "SkillEditor\0on_actionOpen_triggered\0"
    "\0on_actionSave_as_triggered\0"
    "on_actionNew_file_triggered\0"
    "on_actionDelete_Skill_triggered\0"
    "on_actionNew_Skill_triggered\0"
    "on_sTable_cellDoubleClicked\0row\0column"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_SkillEditor[] = {

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
       5,    0,   47,    2, 0x08 /* Private */,
       6,    0,   48,    2, 0x08 /* Private */,
       7,    2,   49,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int, QMetaType::Int,    8,    9,

       0        // eod
};

void SkillEditor::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        SkillEditor *_t = static_cast<SkillEditor *>(_o);
        switch (_id) {
        case 0: _t->on_actionOpen_triggered(); break;
        case 1: _t->on_actionSave_as_triggered(); break;
        case 2: _t->on_actionNew_file_triggered(); break;
        case 3: _t->on_actionDelete_Skill_triggered(); break;
        case 4: _t->on_actionNew_Skill_triggered(); break;
        case 5: _t->on_sTable_cellDoubleClicked((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        default: ;
        }
    }
}

const QMetaObject SkillEditor::staticMetaObject = {
    { &QMainWindow::staticMetaObject, qt_meta_stringdata_SkillEditor.data,
      qt_meta_data_SkillEditor,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *SkillEditor::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *SkillEditor::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_SkillEditor.stringdata))
        return static_cast<void*>(const_cast< SkillEditor*>(this));
    return QMainWindow::qt_metacast(_clname);
}

int SkillEditor::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
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
