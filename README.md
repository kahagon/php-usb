php-usb
===========
This extension is PHP bindings for libusb-1.0. There is no API documentation.  

libusb Homepage  
https://libusb.info/

Here is [PHP examples](examples)

HACKING
=======

There are two ways to modify an extension created using CodeGen_PECL:

1) you can modify the generated code as with any other PHP extension
  
2) you can add custom code to the CodeGen_PECL XML source and re-run pecl-gen

The 2nd approach may look a bit complicated but you have be aware that any
manual changes to the generated code will be lost if you ever change the
XML specs and re-run PECL-Gen. All changes done before have to be applied
to the newly generated code again.
Adding code snippets to the XML source itself on the other hand may be a 
bit more complicated but this way your custom code will always be in the
generated code no matter how often you rerun CodeGen_PECL.


BUILDING ON UNIX etc.
=====================

This extension depends on libusb-1.0.
Please make sure that libusb-1.0 has installed.

To compile your new extension, you will have to execute the following steps:

    ./phpize
    ./configure [--with-usb=/path/to/libusb-1.0-installed]
    make
    make test
    [sudo] make install

--with-usb is optional. You should use this option if you've installed 
libusb-1.0 to location where are not found by configure command.


TESTING
=======

You can now load the extension using a php.ini directive

  extension="usb.[so|dll]"

or load it at runtime using the dl() function

  dl("usb.[so|dll]");

The extension should now be available, you can test this
using the extension_loaded() function:

  if (extension_loaded("usb"))
    echo "usb loaded :)";
  else
    echo "something is wrong :(";

The extension will also add its own block to the output
of phpinfo();

