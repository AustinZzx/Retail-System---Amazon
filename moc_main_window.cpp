/****************************************************************************
** Meta object code from reading C++ file 'main_window.h'
**
** Created by: The Qt Meta Object Compiler version 63 (Qt 4.8.6)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "main_window.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'main_window.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.6. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_MainWindow[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
      22,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      12,   11,   11,   11, 0x08,
      25,   11,   11,   11, 0x08,
      48,   38,   11,   11, 0x08,
      61,   11,   11,   11, 0x08,
      74,   11,   11,   11, 0x08,
      86,   11,   11,   11, 0x08,
      98,   11,   11,   11, 0x08,
     109,   11,   11,   11, 0x08,
     121,   11,   11,   11, 0x08,
     147,  134,   11,   11, 0x08,
     166,   11,   11,   11, 0x08,
     178,   11,   11,   11, 0x08,
     189,   11,   11,   11, 0x08,
     201,   11,   11,   11, 0x08,
     225,  215,   11,   11, 0x08,
     245,   11,   11,   11, 0x08,
     258,   11,   11,   11, 0x08,
     268,   11,   11,   11, 0x08,
     280,   11,   11,   11, 0x08,
     296,   11,   11,   11, 0x08,
     313,   11,   11,   11, 0x08,
     328,   11,   11,   11, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_MainWindow[] = {
    "MainWindow\0\0checklogin()\0createuser()\0"
    "userIndex\0setuser(int)\0selectuser()\0"
    "recommend()\0andsearch()\0orsearch()\0"
    "alphasort()\0ratingsort()\0productIndex\0"
    "showprodetail(int)\0addtocart()\0"
    "viewcart()\0addreview()\0closeamazon()\0"
    "itemIndex\0showitemdetail(int)\0"
    "removeitem()\0buycart()\0closecart()\0"
    "addthisreview()\0closeaddreview()\0"
    "savedatabase()\0donerecommend()\0"
};

void MainWindow::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        MainWindow *_t = static_cast<MainWindow *>(_o);
        switch (_id) {
        case 0: _t->checklogin(); break;
        case 1: _t->createuser(); break;
        case 2: _t->setuser((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 3: _t->selectuser(); break;
        case 4: _t->recommend(); break;
        case 5: _t->andsearch(); break;
        case 6: _t->orsearch(); break;
        case 7: _t->alphasort(); break;
        case 8: _t->ratingsort(); break;
        case 9: _t->showprodetail((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 10: _t->addtocart(); break;
        case 11: _t->viewcart(); break;
        case 12: _t->addreview(); break;
        case 13: _t->closeamazon(); break;
        case 14: _t->showitemdetail((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 15: _t->removeitem(); break;
        case 16: _t->buycart(); break;
        case 17: _t->closecart(); break;
        case 18: _t->addthisreview(); break;
        case 19: _t->closeaddreview(); break;
        case 20: _t->savedatabase(); break;
        case 21: _t->donerecommend(); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData MainWindow::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject MainWindow::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_MainWindow,
      qt_meta_data_MainWindow, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &MainWindow::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *MainWindow::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *MainWindow::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_MainWindow))
        return static_cast<void*>(const_cast< MainWindow*>(this));
    return QWidget::qt_metacast(_clname);
}

int MainWindow::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 22)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 22;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
