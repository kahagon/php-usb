dnl
dnl $ Id: $
dnl

PHP_ARG_WITH(usb, for libusb-1.0 support, [  --with-usb              Configure this ext for compiling default=yes], [])

if test "$PHP_USB" != "no"; then

  export OLD_CPPFLAGS="$CPPFLAGS"
  export CPPFLAGS="$CPPFLAGS $INCLUDES -DHAVE_USB"

  AC_MSG_CHECKING(PHP version)
  AC_TRY_COMPILE(
    [#include <php_version.h>], 
    [
      #if PHP_VERSION_ID < 50300
      #error  this extension requires at least PHP version 5.3.0
      #endif
    ],
    [AC_MSG_RESULT(ok)],
    [AC_MSG_ERROR([need at least PHP 5.3.0])]
  )

  AC_CHECK_PROG(PKG_CONFIG, pkg-config, pkg-config)

  if ! test -n "$PKG_CONFIG"; then
    AC_MSG_ERROR([not found])
  fi

  AC_CHECK_HEADER([libusb-1.0/libusb.h], [], AC_MSG_ERROR('libusb-1.0/libusb.h' header not found))

  AC_MSG_CHECKING(libusb-1.0 libdir)
  LIBUSB_LIBDIR=`$PKG_CONFIG libusb-1.0 --variable=libdir`
  LIBUSB_VERSION=`$PKG_CONFIG libusb-1.0 --modversion`

  if test $LIBUSB_LIBDIR = ''; then

    AC_MSG_ERROR([not found])

  else

    AC_MSG_RESULT([found $LIBUSB_LIBDIR])

    PHP_CHECK_LIBRARY(
      usb-1.0, 
      libusb_init,
      [
        PHP_ADD_LIBRARY_WITH_PATH(usb-1.0, $LIBUSB_LIBDIR, USB_SHARED_LIBADD)
        AC_DEFINE(HAVE_USB, 1, [ ])
      ],
      [
        AC_MSG_ERROR([libusb-1.0 library not found])
      ]
    )

    AC_MSG_CHECKING(libusb-1.0 version)
    ac_IFS=$IFS
    IFS="."
    set $LIBUSB_VERSION
    IFS=$ac_IFS
    LIBUSB_VERSION_NUMBER=`expr [$]1 \* 1000000 + [$]2 \* 1000 + [$]3`
    AC_MSG_RESULT([found $LIBUSB_VERSION])

    if ! test "$LIBUSB_VERSION_NUMBER" -ge "1000016"; then
      AC_MSG_ERROR([libusb-1.0 version 1.0.16 or greater required.])
    fi
  fi

  PHP_SUBST(USB_SHARED_LIBADD)

dnl  PHP_NEW_EXTENSION(usb, usb.c usb_descriptor.c usb_device.c usb_misc.c usb_syncio.c, $ext_shared)
  PHP_NEW_EXTENSION(usb, usb.c usb_descriptor.c usb_device.c, $ext_shared)

fi

