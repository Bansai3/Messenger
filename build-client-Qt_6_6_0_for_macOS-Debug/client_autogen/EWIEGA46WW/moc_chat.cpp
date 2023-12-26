/****************************************************************************
** Meta object code from reading C++ file 'chat.h'
**
** Created by: The Qt Meta Object Compiler version 68 (Qt 6.6.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../client/chat.h"
#include <QtCore/qmetatype.h>

#if __has_include(<QtCore/qtmochelpers.h>)
#include <QtCore/qtmochelpers.h>
#else
QT_BEGIN_MOC_NAMESPACE
#endif


#include <memory>

#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'chat.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 68
#error "This file was generated using the moc from 6.6.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

#ifndef Q_CONSTINIT
#define Q_CONSTINIT
#endif

QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
QT_WARNING_DISABLE_GCC("-Wuseless-cast")
namespace {

#ifdef QT_MOC_HAS_STRINGDATA
struct qt_meta_stringdata_CLASSchatENDCLASS_t {};
static constexpr auto qt_meta_stringdata_CLASSchatENDCLASS = QtMocHelpers::stringData(
    "chat",
    "on_lnIPAddress_textChanged",
    "",
    "arg1",
    "on_btnConnect_clicked",
    "device_connected",
    "device_disconnected",
    "device_stateChanged",
    "QAbstractSocket::SocketState",
    "device_errorOccurred",
    "QAbstractSocket::SocketError",
    "device_dataReady",
    "data",
    "on_btnSend_clicked"
);
#else  // !QT_MOC_HAS_STRING_DATA
struct qt_meta_stringdata_CLASSchatENDCLASS_t {
    uint offsetsAndSizes[28];
    char stringdata0[5];
    char stringdata1[27];
    char stringdata2[1];
    char stringdata3[5];
    char stringdata4[22];
    char stringdata5[17];
    char stringdata6[20];
    char stringdata7[20];
    char stringdata8[29];
    char stringdata9[21];
    char stringdata10[29];
    char stringdata11[17];
    char stringdata12[5];
    char stringdata13[19];
};
#define QT_MOC_LITERAL(ofs, len) \
    uint(sizeof(qt_meta_stringdata_CLASSchatENDCLASS_t::offsetsAndSizes) + ofs), len 
Q_CONSTINIT static const qt_meta_stringdata_CLASSchatENDCLASS_t qt_meta_stringdata_CLASSchatENDCLASS = {
    {
        QT_MOC_LITERAL(0, 4),  // "chat"
        QT_MOC_LITERAL(5, 26),  // "on_lnIPAddress_textChanged"
        QT_MOC_LITERAL(32, 0),  // ""
        QT_MOC_LITERAL(33, 4),  // "arg1"
        QT_MOC_LITERAL(38, 21),  // "on_btnConnect_clicked"
        QT_MOC_LITERAL(60, 16),  // "device_connected"
        QT_MOC_LITERAL(77, 19),  // "device_disconnected"
        QT_MOC_LITERAL(97, 19),  // "device_stateChanged"
        QT_MOC_LITERAL(117, 28),  // "QAbstractSocket::SocketState"
        QT_MOC_LITERAL(146, 20),  // "device_errorOccurred"
        QT_MOC_LITERAL(167, 28),  // "QAbstractSocket::SocketError"
        QT_MOC_LITERAL(196, 16),  // "device_dataReady"
        QT_MOC_LITERAL(213, 4),  // "data"
        QT_MOC_LITERAL(218, 18)   // "on_btnSend_clicked"
    },
    "chat",
    "on_lnIPAddress_textChanged",
    "",
    "arg1",
    "on_btnConnect_clicked",
    "device_connected",
    "device_disconnected",
    "device_stateChanged",
    "QAbstractSocket::SocketState",
    "device_errorOccurred",
    "QAbstractSocket::SocketError",
    "device_dataReady",
    "data",
    "on_btnSend_clicked"
};
#undef QT_MOC_LITERAL
#endif // !QT_MOC_HAS_STRING_DATA
} // unnamed namespace

Q_CONSTINIT static const uint qt_meta_data_CLASSchatENDCLASS[] = {

 // content:
      12,       // revision
       0,       // classname
       0,    0, // classinfo
       8,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags, initial metatype offsets
       1,    1,   62,    2, 0x08,    1 /* Private */,
       4,    0,   65,    2, 0x08,    3 /* Private */,
       5,    0,   66,    2, 0x08,    4 /* Private */,
       6,    0,   67,    2, 0x08,    5 /* Private */,
       7,    1,   68,    2, 0x08,    6 /* Private */,
       9,    1,   71,    2, 0x08,    8 /* Private */,
      11,    1,   74,    2, 0x08,   10 /* Private */,
      13,    0,   77,    2, 0x08,   12 /* Private */,

 // slots: parameters
    QMetaType::Void, QMetaType::QString,    3,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 8,    2,
    QMetaType::Void, 0x80000000 | 10,    2,
    QMetaType::Void, QMetaType::QByteArray,   12,
    QMetaType::Void,

       0        // eod
};

Q_CONSTINIT const QMetaObject chat::staticMetaObject = { {
    QMetaObject::SuperData::link<QDialog::staticMetaObject>(),
    qt_meta_stringdata_CLASSchatENDCLASS.offsetsAndSizes,
    qt_meta_data_CLASSchatENDCLASS,
    qt_static_metacall,
    nullptr,
    qt_incomplete_metaTypeArray<qt_meta_stringdata_CLASSchatENDCLASS_t,
        // Q_OBJECT / Q_GADGET
        QtPrivate::TypeAndForceComplete<chat, std::true_type>,
        // method 'on_lnIPAddress_textChanged'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<const QString &, std::false_type>,
        // method 'on_btnConnect_clicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'device_connected'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'device_disconnected'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'device_stateChanged'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<QAbstractSocket::SocketState, std::false_type>,
        // method 'device_errorOccurred'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<QAbstractSocket::SocketError, std::false_type>,
        // method 'device_dataReady'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<QByteArray, std::false_type>,
        // method 'on_btnSend_clicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>
    >,
    nullptr
} };

void chat::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<chat *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->on_lnIPAddress_textChanged((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1]))); break;
        case 1: _t->on_btnConnect_clicked(); break;
        case 2: _t->device_connected(); break;
        case 3: _t->device_disconnected(); break;
        case 4: _t->device_stateChanged((*reinterpret_cast< std::add_pointer_t<QAbstractSocket::SocketState>>(_a[1]))); break;
        case 5: _t->device_errorOccurred((*reinterpret_cast< std::add_pointer_t<QAbstractSocket::SocketError>>(_a[1]))); break;
        case 6: _t->device_dataReady((*reinterpret_cast< std::add_pointer_t<QByteArray>>(_a[1]))); break;
        case 7: _t->on_btnSend_clicked(); break;
        default: ;
        }
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        switch (_id) {
        default: *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType(); break;
        case 4:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType(); break;
            case 0:
                *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType::fromType< QAbstractSocket::SocketState >(); break;
            }
            break;
        case 5:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType(); break;
            case 0:
                *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType::fromType< QAbstractSocket::SocketError >(); break;
            }
            break;
        }
    }
}

const QMetaObject *chat::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *chat::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_CLASSchatENDCLASS.stringdata0))
        return static_cast<void*>(this);
    return QDialog::qt_metacast(_clname);
}

int chat::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 8)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 8;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 8)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 8;
    }
    return _id;
}
QT_WARNING_POP
