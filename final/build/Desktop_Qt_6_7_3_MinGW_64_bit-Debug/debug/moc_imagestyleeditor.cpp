/****************************************************************************
** Meta object code from reading C++ file 'imagestyleeditor.h'
**
** Created by: The Qt Meta Object Compiler version 68 (Qt 6.7.3)
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
#error "This file was generated using the moc from 6.7.3. It"
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
    "backToMainMenu",
    "",
    "uploadImage",
    "saveImage",
    "applyBorder",
    "removeBorder",
    "addText",
    "rotateSelectedText",
    "angle",
    "onRotationSliderChanged",
    "value",
    "undo",
    "redo",
    "uploadBorder",
    "removeText",
    "returnToMainMenu"
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
      13,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: name, argc, parameters, tag, flags, initial metatype offsets
       1,    0,   92,    2, 0x06,    1 /* Public */,

 // slots: name, argc, parameters, tag, flags, initial metatype offsets
       3,    0,   93,    2, 0x08,    2 /* Private */,
       4,    0,   94,    2, 0x08,    3 /* Private */,
       5,    0,   95,    2, 0x08,    4 /* Private */,
       6,    0,   96,    2, 0x08,    5 /* Private */,
       7,    0,   97,    2, 0x08,    6 /* Private */,
       8,    1,   98,    2, 0x08,    7 /* Private */,
      10,    1,  101,    2, 0x08,    9 /* Private */,
      12,    0,  104,    2, 0x08,   11 /* Private */,
      13,    0,  105,    2, 0x08,   12 /* Private */,
      14,    0,  106,    2, 0x08,   13 /* Private */,
      15,    0,  107,    2, 0x08,   14 /* Private */,
      16,    0,  108,    2, 0x08,   15 /* Private */,

 // signals: parameters
    QMetaType::Void,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,    9,
    QMetaType::Void, QMetaType::Int,   11,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
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
        // method 'backToMainMenu'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'uploadImage'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'saveImage'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'applyBorder'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'removeBorder'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'addText'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'rotateSelectedText'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<int, std::false_type>,
        // method 'onRotationSliderChanged'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<int, std::false_type>,
        // method 'undo'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'redo'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'uploadBorder'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'removeText'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'returnToMainMenu'
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
        case 0: _t->backToMainMenu(); break;
        case 1: _t->uploadImage(); break;
        case 2: _t->saveImage(); break;
        case 3: _t->applyBorder(); break;
        case 4: _t->removeBorder(); break;
        case 5: _t->addText(); break;
        case 6: _t->rotateSelectedText((*reinterpret_cast< std::add_pointer_t<int>>(_a[1]))); break;
        case 7: _t->onRotationSliderChanged((*reinterpret_cast< std::add_pointer_t<int>>(_a[1]))); break;
        case 8: _t->undo(); break;
        case 9: _t->redo(); break;
        case 10: _t->uploadBorder(); break;
        case 11: _t->removeText(); break;
        case 12: _t->returnToMainMenu(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (ImageStyleEditor::*)();
            if (_t _q_method = &ImageStyleEditor::backToMainMenu; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 0;
                return;
            }
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
        if (_id < 13)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 13;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 13)
            *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType();
        _id -= 13;
    }
    return _id;
}

// SIGNAL 0
void ImageStyleEditor::backToMainMenu()
{
    QMetaObject::activate(this, &staticMetaObject, 0, nullptr);
}
QT_WARNING_POP
