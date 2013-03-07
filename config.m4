dnl
dnl $ Id: $
dnl

PHP_ARG_WITH(usb, libusb install,[  --with-usb[=DIR]     With usb support])


if test "$PHP_USB" != "no"; then


  if test -r "$PHP_USB/libusb-1.0/libusb.h"; then
	PHP_USB_DIR="$PHP_USB"
  else
	AC_MSG_CHECKING(for usb in default path)
	for i in $HOME/include; do
	  if test -r "$i/libusb-1.0/libusb.h"; then
		PHP_USB_DIR=$i
		AC_MSG_RESULT(found in $i)
		break
	  fi
	done
	if test "x" = "x$PHP_USB_DIR"; then
	  AC_MSG_ERROR(not found)
	fi
  fi


  export OLD_CPPFLAGS="$CPPFLAGS"
  export CPPFLAGS="$CPPFLAGS $INCLUDES -DHAVE_USB"
  export CPPFLAGS="$OLD_CPPFLAGS"

  PHP_ADD_INCLUDE($PHP_USB_DIR/include)
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

  AC_CHECK_HEADER([libusb.h], [], AC_MSG_ERROR('libusb.h' header not found))
  export CPPFLAGS="$OLD_CPPFLAGS"
  PHP_SUBST(USB_SHARED_LIBADD)

  PHP_ADD_LIBRARY_WITH_PATH(usb-1.0, $PHP_USB_DIR/lib, USB_SHARED_LIBADD)


  PHP_SUBST(USB_SHARED_LIBADD)
  AC_DEFINE(HAVE_USB, 1, [ ])

  PHP_NEW_EXTENSION(usb, usb.c , $ext_shared)

fi

