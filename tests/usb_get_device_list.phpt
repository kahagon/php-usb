--TEST--
usb_get_device_list() function
--SKIPIF--
<?php 

if(!extension_loaded('usb')) die('skip ');

 ?>
--FILE--
<?php
$context; $devices;

if (USB_SUCCESS !== usb_init($context)) {
    goto out;
}

// expect that existence of an usb device.
if (1 > usb_get_device_list($context, $devices)) {
    goto out;
}

var_dump($devices[0]);

out:
if ($devices) usb_free_device_list($devices);
if ($context) usb_exit($context);
?>
--EXPECTF--
resource(%d) of type (usb_device)