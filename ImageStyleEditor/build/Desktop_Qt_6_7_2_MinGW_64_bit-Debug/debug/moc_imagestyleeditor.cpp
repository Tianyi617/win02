/****************************************************************************
** Meta object code from reading C++ file 'imagestyleeditor.h'
**
** Created by: The Qt Meta Object Compiler version 68 (Qt 6.7.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../imagestyleeditor.h"
#include <QtGui/qtextcursor.h>
#include <QtCore/qmetatype.h>

#include <QtCore/qtmochelpers.h>

#include <memory>


#include <QtCore/qxptype_traits.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'imagestyleeditor.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 68
#error "This file was generated using the moc from 6.7.2. It"
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
struct qt_meta_stringdata_CLASSImageStyleEditorENDCLASS_t {};
constexpr auto qt_meta_stringdata_CLASSImageStyleEditorENDCLASS = QtMocHelpers::stringData(
    "ImageStyleEditor",
    "uploadImage",
    "",
    "saveImage",
    "applyBorder",
    "addText",
    "applyAIStyle",
    "applySimpleBorder",
    "QPixmap&",
    "pixmap",
    "applyDecorativeBorder",
    "applyRoundedBorder",
    "applyDoubleBorder",
    "applyGradientBorder",
    "applyShadowBorder",
    "removeBorder"
);
#else  // !QT_MOC_HAS_STRINGDATA
#error "qtmochelpers.h not found or too old."
#endif // !QT_MOC_HAS_STRINGDATA
} // unnamed namespace

Q_CONSTINIT static const uint qt_meta_data_CLASSImageStyleEditorENDCLASS[] = {

 // content:
      12,       // revision
       0,       // classname
       0,    0, // classinfo
      12,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags, initial metatype offsets
       1,    0,   86,    2, 0x08,    1 /* Private */,
       3,    0,   87,    2, 0x08,    2 /* Private */,
       4,    0,   88,    2, 0x08,    3 /* Private */,
       5,    0,   89,    2, 0x08,    4 /* Private */,
       6,    0,   90,    2, 0x08,    5 /* Private */,
       7,    1,   91,    2, 0x08,    6 /* Private */,
      10,    1,   94,    2, 0x08,    8 /* Private */,
      11,    1,   97,    2, 0x08,   10 /* Private */,
      12,    1,  100,    2, 0x08,   12 /* Private */,
      13,    1,  103,    2, 0x08,   14 /* Private */,
      14,    1,  106,    2, 0x08,   16 /* Private */,
      15,    0,  109,    2, 0x08,   18 /* Private */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 8,    9,
    QMetaType::Void, 0x80000000 | 8,    9,
    QMetaType::Void, 0x80000000 | 8,    9,
    QMetaType::Void, 0x80000000 | 8,    9,
    QMetaType::Void, 0x80000000 | 8,    9,
    QMetaType::Void, 0x80000000 | 8,    9,
    QMetaType::Void,

       0        // eod
};

Q_CONSTINIT const QMetaObject ImageStyleEditor::staticMetaObject = { {
    QMetaObject::SuperData::link<QMainWindow::staticMetaObject>(),
    qt_meta_stringdata_CLASSImageStyleEditorENDCLASS.offsetsAndSizes,
    qt_meta_data_CLASSImageStyleEditorENDCLASS,
    qt_static_metacall,
    nullptr,
    qt_incomplete_metaTypeArray<qt_meta_stringdata_CLASSImageStyleEditorENDCLASS_t,
        // Q_OBJECT / Q_GADGET
        QtPrivate::TypeAndForceComplete<ImageStyleEditor, std::true_type>,
        // method 'uploadImage'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'saveImage'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'applyBorder'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'addText'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'applyAIStyle'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'applySimpleBorder'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<QPixmap &, std::false_type>,
        // method 'applyDecorativeBorder'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<QPixmap &, std::false_type>,
        // method 'applyRoundedBorder'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<QPixmap &, std::false_type>,
        // method 'applyDoubleBorder'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<QPixmap &, std::false_type>,
        // method 'applyGradientBorder'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<QPixmap &, std::false_type>,
        // method 'applyShadowBorder'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<QPixmap &, std::false_type>,
        // method 'removeBorder'
        QtPrivate::TypeAndForceComplete<void, std::false_type>
    >,
    nullptr
} };

void ImageStyleEditor::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<ImageStyleEditor *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->uploadImage(); break;
        case 1: _t->saveImage(); break;
        case 2: _t->applyBorder(); break;
        case 3: _t->addText(); break;
        case 4: _t->applyAIStyle(); break;
        case 5: _t->applySimpleBorder((*reinterpret_cast< std::add_pointer_t<QPixmap&>>(_a[1]))); break;
        case 6: _t->applyDecorativeBorder((*reinterpret_cast< std::add_pointer_t<QPixmap&>>(_a[1]))); break;
        case 7: _t->applyRoundedBorder((*reinterpret_cast< std::add_pointer_t<QPixmap&>>(_a[1]))); break;
        case 8: _t->applyDoubleBorder((*reinterpret_cast< std::add_pointer_t<QPixmap&>>(_a[1]))); break;
        case 9: _t->applyGradientBorder((*reinterpret_cast< std::add_pointer_t<QPixmap&>>(_a[1]))); break;
        case 10: _t->applyShadowBorder((*reinterpret_cast< std::add_pointer_t<QPixmap&>>(_a[1]))); break;
        case 11: _t->removeBorder(); break;
        default: ;
        }
    }
}

const QMetaObject *ImageStyleEditor::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *ImageStyleEditor::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_CLASSImageStyleEditorENDCLASS.stringdata0))
        return static_cast<void*>(this);
    return QMainWindow::qt_metacast(_clname);
}

int ImageStyleEditor::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 12)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 12;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 12)
            *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType();
        _id -= 12;
    }
    return _id;
}
QT_WARNING_POP
