/****************************************************************************
** Meta object code from reading C++ file 'proxyapp.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.13.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "stdafx.h"
#include "../../proxyapp.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'proxyapp.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.13.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_ProxyApp_t {
    QByteArrayData data[12];
    char stringdata0[150];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_ProxyApp_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_ProxyApp_t qt_meta_stringdata_ProxyApp = {
    {
QT_MOC_LITERAL(0, 0, 8), // "ProxyApp"
QT_MOC_LITERAL(1, 9, 20), // "onRequestButtonClick"
QT_MOC_LITERAL(2, 30, 0), // ""
QT_MOC_LITERAL(3, 31, 21), // "onResponseButtonClick"
QT_MOC_LITERAL(4, 53, 19), // "onSpiderButtonClick"
QT_MOC_LITERAL(5, 73, 17), // "onDumpButtonClick"
QT_MOC_LITERAL(6, 91, 4), // "exit"
QT_MOC_LITERAL(7, 96, 8), // "setAlert"
QT_MOC_LITERAL(8, 105, 11), // "std::string"
QT_MOC_LITERAL(9, 117, 9), // "setStatus"
QT_MOC_LITERAL(10, 127, 10), // "setRequest"
QT_MOC_LITERAL(11, 138, 11) // "setResponse"

    },
    "ProxyApp\0onRequestButtonClick\0\0"
    "onResponseButtonClick\0onSpiderButtonClick\0"
    "onDumpButtonClick\0exit\0setAlert\0"
    "std::string\0setStatus\0setRequest\0"
    "setResponse"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_ProxyApp[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       9,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       4,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,   59,    2, 0x06 /* Public */,
       3,    0,   60,    2, 0x06 /* Public */,
       4,    0,   61,    2, 0x06 /* Public */,
       5,    0,   62,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       6,    0,   63,    2, 0x08 /* Private */,
       7,    1,   64,    2, 0x08 /* Private */,
       9,    1,   67,    2, 0x08 /* Private */,
      10,    1,   70,    2, 0x08 /* Private */,
      11,    1,   73,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 8,    2,
    QMetaType::Void, QMetaType::QString,    2,
    QMetaType::Void, QMetaType::QString,    2,
    QMetaType::Void, QMetaType::QString,    2,

       0        // eod
};

void ProxyApp::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<ProxyApp *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->onRequestButtonClick(); break;
        case 1: _t->onResponseButtonClick(); break;
        case 2: _t->onSpiderButtonClick(); break;
        case 3: _t->onDumpButtonClick(); break;
        case 4: _t->exit(); break;
        case 5: _t->setAlert((*reinterpret_cast< std::string(*)>(_a[1]))); break;
        case 6: _t->setStatus((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 7: _t->setRequest((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 8: _t->setResponse((*reinterpret_cast< QString(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (ProxyApp::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&ProxyApp::onRequestButtonClick)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (ProxyApp::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&ProxyApp::onResponseButtonClick)) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (ProxyApp::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&ProxyApp::onSpiderButtonClick)) {
                *result = 2;
                return;
            }
        }
        {
            using _t = void (ProxyApp::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&ProxyApp::onDumpButtonClick)) {
                *result = 3;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject ProxyApp::staticMetaObject = { {
    &QMainWindow::staticMetaObject,
    qt_meta_stringdata_ProxyApp.data,
    qt_meta_data_ProxyApp,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *ProxyApp::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *ProxyApp::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_ProxyApp.stringdata0))
        return static_cast<void*>(this);
    return QMainWindow::qt_metacast(_clname);
}

int ProxyApp::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
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

// SIGNAL 0
void ProxyApp::onRequestButtonClick()
{
    QMetaObject::activate(this, &staticMetaObject, 0, nullptr);
}

// SIGNAL 1
void ProxyApp::onResponseButtonClick()
{
    QMetaObject::activate(this, &staticMetaObject, 1, nullptr);
}

// SIGNAL 2
void ProxyApp::onSpiderButtonClick()
{
    QMetaObject::activate(this, &staticMetaObject, 2, nullptr);
}

// SIGNAL 3
void ProxyApp::onDumpButtonClick()
{
    QMetaObject::activate(this, &staticMetaObject, 3, nullptr);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
