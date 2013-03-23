--TEST--
usb_class_name() function
--SKIPIF--
<?php 

if(!extension_loaded('usb')) die('skip ');

 ?>
--FILE--
<?php
print usb_class_name(USB_CLASS_PER_INTERFACE);
?>
--EXPECT--
USB_CLASS_PER_INTERFACE