/****************************************************************************
** Meta object code from reading C++ file 'persontable.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.14.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "persontable.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'persontable.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.14.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_PersonTable_t {
    QByteArrayData data[16];
    char stringdata0[134];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_PersonTable_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_PersonTable_t qt_meta_stringdata_PersonTable = {
    {
QT_MOC_LITERAL(0, 0, 11), // "PersonTable"
QT_MOC_LITERAL(1, 12, 8), // "rowCount"
QT_MOC_LITERAL(2, 21, 0), // ""
QT_MOC_LITERAL(3, 22, 11), // "QModelIndex"
QT_MOC_LITERAL(4, 34, 6), // "parent"
QT_MOC_LITERAL(5, 41, 11), // "columnCount"
QT_MOC_LITERAL(6, 53, 4), // "data"
QT_MOC_LITERAL(7, 58, 5), // "index"
QT_MOC_LITERAL(8, 64, 4), // "role"
QT_MOC_LITERAL(9, 69, 9), // "roleNames"
QT_MOC_LITERAL(10, 79, 21), // "QHash<int,QByteArray>"
QT_MOC_LITERAL(11, 101, 10), // "updateCell"
QT_MOC_LITERAL(12, 112, 3), // "val"
QT_MOC_LITERAL(13, 116, 7), // "setData"
QT_MOC_LITERAL(14, 124, 5), // "value"
QT_MOC_LITERAL(15, 130, 3) // "add"

    },
    "PersonTable\0rowCount\0\0QModelIndex\0"
    "parent\0columnCount\0data\0index\0role\0"
    "roleNames\0QHash<int,QByteArray>\0"
    "updateCell\0val\0setData\0value\0add"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_PersonTable[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
      10,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // methods: name, argc, parameters, tag, flags
       1,    1,   64,    2, 0x02 /* Public */,
       1,    0,   67,    2, 0x22 /* Public | MethodCloned */,
       5,    1,   68,    2, 0x02 /* Public */,
       5,    0,   71,    2, 0x22 /* Public | MethodCloned */,
       6,    2,   72,    2, 0x02 /* Public */,
       6,    1,   77,    2, 0x22 /* Public | MethodCloned */,
       9,    0,   80,    2, 0x02 /* Public */,
      11,    3,   81,    2, 0x02 /* Public */,
      13,    3,   88,    2, 0x02 /* Public */,
      15,    0,   95,    2, 0x02 /* Public */,

 // methods: parameters
    QMetaType::Int, 0x80000000 | 3,    4,
    QMetaType::Int,
    QMetaType::Int, 0x80000000 | 3,    4,
    QMetaType::Int,
    QMetaType::QVariant, 0x80000000 | 3, QMetaType::Int,    7,    8,
    QMetaType::QVariant, 0x80000000 | 3,    7,
    0x80000000 | 10,
    QMetaType::Void, QMetaType::Int, QMetaType::QVariant, QMetaType::Int,    7,   12,    8,
    QMetaType::Bool, 0x80000000 | 3, QMetaType::QVariant, QMetaType::Int,    7,   14,    8,
    QMetaType::Void,

       0        // eod
};

void PersonTable::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<PersonTable *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: { int _r = _t->rowCount((*reinterpret_cast< const QModelIndex(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        case 1: { int _r = _t->rowCount();
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        case 2: { int _r = _t->columnCount((*reinterpret_cast< const QModelIndex(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        case 3: { int _r = _t->columnCount();
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        case 4: { QVariant _r = _t->data((*reinterpret_cast< const QModelIndex(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])));
            if (_a[0]) *reinterpret_cast< QVariant*>(_a[0]) = std::move(_r); }  break;
        case 5: { QVariant _r = _t->data((*reinterpret_cast< const QModelIndex(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< QVariant*>(_a[0]) = std::move(_r); }  break;
        case 6: { QHash<int,QByteArray> _r = _t->roleNames();
            if (_a[0]) *reinterpret_cast< QHash<int,QByteArray>*>(_a[0]) = std::move(_r); }  break;
        case 7: _t->updateCell((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< QVariant(*)>(_a[2])),(*reinterpret_cast< int(*)>(_a[3]))); break;
        case 8: { bool _r = _t->setData((*reinterpret_cast< const QModelIndex(*)>(_a[1])),(*reinterpret_cast< const QVariant(*)>(_a[2])),(*reinterpret_cast< int(*)>(_a[3])));
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        case 9: _t->add(); break;
        default: ;
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject PersonTable::staticMetaObject = { {
    QMetaObject::SuperData::link<QAbstractTableModel::staticMetaObject>(),
    qt_meta_stringdata_PersonTable.data,
    qt_meta_data_PersonTable,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *PersonTable::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *PersonTable::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_PersonTable.stringdata0))
        return static_cast<void*>(this);
    return QAbstractTableModel::qt_metacast(_clname);
}

int PersonTable::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QAbstractTableModel::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 10)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 10;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 10)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 10;
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
