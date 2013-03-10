--TEST--
usb_init() function
--SKIPIF--
<?php 

if(!extension_loaded('usb')) die('skip ');

 ?>
--FILE--
<?php
$context;

if (USB_SUCCESS !== usb_init($context)) {
    goto out;
}

var_dump($context);

out:

if ($context) usb_exit($context);
?>
--EXPECTF--
resource(%d) of type (usb_context)