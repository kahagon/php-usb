dnl
dnl $ Id: $
dnl

PHP_ARG_ENABLE(usb, whether to enable usb functions, [  --enable-usb Enable usb support])

if test "$PHP_USB" != "no"; then

  export OLD_CPPFLAGS="$CPPFLAGS"
  export CPPFLAGS="$CPPFLAGS $INCLUDES -DHAVE_USB"

  AC_MSG_CHECKING(PHP version)
  AC_TRY_COMPILE([#include <php_version.h>], [
#if PHP_VERSION_ID < 40000
#error  this extension requires at least PHP version 4.0.0
#endif
],
[AC_MSG_RESULT(ok)],
[AC_MSG_ERROR([need at least PHP 4.0.0])])

  AC_CHECK_HEADER([libusb-1.0/libusb.h], [], AC_MSG_ERROR('libusb-1.0/libusb.h' header not found))
  export CPPFLAGS="$OLD_CPPFLAGS"
  PHP_SUBST(USB_SHARED_LIBADD)

  AC_DEFINE(HAVE_USB, 1, [ ])

  PHP_NEW_EXTENSION(usb, usb.c , $ext_shared)

fi

