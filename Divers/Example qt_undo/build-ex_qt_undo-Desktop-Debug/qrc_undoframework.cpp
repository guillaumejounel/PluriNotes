/****************************************************************************
** Resource object code
**
** Created by: The Resource Compiler for Qt version 5.7.1
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

static const unsigned char qt_resource_data[] = {
  // /home/florentchehab/Dropbox/UTC/LO21/PluriNotes/Divers/Example qt_undo/ex_qt_undo/cross.png
  0x0,0x0,0x0,0x72,
  0x89,
  0x50,0x4e,0x47,0xd,0xa,0x1a,0xa,0x0,0x0,0x0,0xd,0x49,0x48,0x44,0x52,0x0,
  0x0,0x0,0x64,0x0,0x0,0x0,0x65,0x1,0x3,0x0,0x0,0x0,0x81,0x70,0xd4,0xb2,
  0x0,0x0,0x0,0x6,0x50,0x4c,0x54,0x45,0xff,0xff,0xff,0x0,0x0,0x0,0x55,0xc2,
  0xd3,0x7e,0x0,0x0,0x0,0x27,0x49,0x44,0x41,0x54,0x38,0xcb,0x63,0x60,0x0,0x83,
  0x4,0x6,0x64,0x30,0xca,0x1b,0xe5,0xd,0x4e,0x9e,0x3,0xa,0xef,0x3f,0x12,0xf8,
  0xc0,0x50,0x8f,0xc2,0x1b,0xd,0xb3,0x51,0xde,0x90,0xe1,0x1,0x0,0x74,0xe,0x3e,
  0xa9,0x99,0x6b,0x20,0x0,0x0,0x0,0x0,0x0,0x49,0x45,0x4e,0x44,0xae,0x42,0x60,
  0x82,
  
};

static const unsigned char qt_resource_name[] = {
  // images
  0x0,0x6,
  0x7,0x3,0x7d,0xc3,
  0x0,0x69,
  0x0,0x6d,0x0,0x61,0x0,0x67,0x0,0x65,0x0,0x73,
    // cross.png
  0x0,0x9,
  0x6,0xa6,0x82,0x67,
  0x0,0x63,
  0x0,0x72,0x0,0x6f,0x0,0x73,0x0,0x73,0x0,0x2e,0x0,0x70,0x0,0x6e,0x0,0x67,
  
};

static const unsigned char qt_resource_struct[] = {
  // :
  0x0,0x0,0x0,0x0,0x0,0x2,0x0,0x0,0x0,0x1,0x0,0x0,0x0,0x1,
  // :/images
  0x0,0x0,0x0,0x0,0x0,0x2,0x0,0x0,0x0,0x1,0x0,0x0,0x0,0x2,
  // :/images/cross.png
  0x0,0x0,0x0,0x12,0x0,0x0,0x0,0x0,0x0,0x1,0x0,0x0,0x0,0x0,

};

#ifdef QT_NAMESPACE
#  define QT_RCC_PREPEND_NAMESPACE(name) ::QT_NAMESPACE::name
#  define QT_RCC_MANGLE_NAMESPACE0(x) x
#  define QT_RCC_MANGLE_NAMESPACE1(a, b) a##_##b
#  define QT_RCC_MANGLE_NAMESPACE2(a, b) QT_RCC_MANGLE_NAMESPACE1(a,b)
#  define QT_RCC_MANGLE_NAMESPACE(name) QT_RCC_MANGLE_NAMESPACE2( \
        QT_RCC_MANGLE_NAMESPACE0(name), QT_RCC_MANGLE_NAMESPACE0(QT_NAMESPACE))
#else
#   define QT_RCC_PREPEND_NAMESPACE(name) name
#   define QT_RCC_MANGLE_NAMESPACE(name) name
#endif

#ifdef QT_NAMESPACE
namespace QT_NAMESPACE {
#endif

bool qRegisterResourceData(int, const unsigned char *, const unsigned char *, const unsigned char *);

bool qUnregisterResourceData(int, const unsigned char *, const unsigned char *, const unsigned char *);

#ifdef QT_NAMESPACE
}
#endif

int QT_RCC_MANGLE_NAMESPACE(qInitResources_undoframework)();
int QT_RCC_MANGLE_NAMESPACE(qInitResources_undoframework)()
{
    QT_RCC_PREPEND_NAMESPACE(qRegisterResourceData)
        (0x01, qt_resource_struct, qt_resource_name, qt_resource_data);
    return 1;
}

int QT_RCC_MANGLE_NAMESPACE(qCleanupResources_undoframework)();
int QT_RCC_MANGLE_NAMESPACE(qCleanupResources_undoframework)()
{
    QT_RCC_PREPEND_NAMESPACE(qUnregisterResourceData)
       (0x01, qt_resource_struct, qt_resource_name, qt_resource_data);
    return 1;
}

namespace {
   struct initializer {
       initializer() { QT_RCC_MANGLE_NAMESPACE(qInitResources_undoframework)(); }
       ~initializer() { QT_RCC_MANGLE_NAMESPACE(qCleanupResources_undoframework)(); }
   } dummy;
}
