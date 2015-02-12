dnl
dnl $ Id: $
dnl

PHP_ARG_WITH(usb, for libusb-1.0 support, [  --with-usb              libusb-1.0 installed directory], [])

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

dnl  AC_CHECK_HEADER([libusb-1.0/libusb.h], [], AC_MSG_ERROR('libusb-1.0/libusb.h' header not found))

  PHP_LIBUSB_DIR=''
  HEADER_FILE="include/libusb-1.0/libusb.h"
  AC_MSG_CHECKING(libusb-1.0 installed directory)

  if test $PHP_USB = 'yes' ; then
    DEFAULT_PATH_LIST="/usr /usr/local"
    for TMP_PATH in $DEFAULT_PATH_LIST; do
      if test -r $TMP_PATH/$HEADER_FILE ; then
        PHP_LIBUSB_DIR=$TMP_PATH
      fi
    done
  else
    PHP_LIBUSB_DIR=$PHP_USB
  fi 

  if ! test -r $PHP_LIBUSB_DIR/$HEADER_FILE ; then
    AC_MSG_ERROR([not found])
  else
    AC_MSG_RESULT([found $PHP_LIBUSB_DIR])
  fi

  PHP_CHECK_LIBRARY(usb-1.0, libusb_init,
  [
    PHP_ADD_LIBRARY_WITH_PATH(usb-1.0, $PHP_LIBUSB_DIR/lib, USB_SHARED_LIBADD)
    AC_DEFINE(HAVE_USB, 1, [ ])
  ],[
    AC_MSG_ERROR([libusb-1.0 library not found])
  ])

  PHP_SUBST(USB_SHARED_LIBADD)

  PHP_NEW_EXTENSION(usb, usb.c usb_descriptor.c usb_device.c usb_misc.c usb_syncio.c, $ext_shared)

fi

