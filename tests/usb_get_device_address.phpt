--TEST--
usb_get_device_address() function
--SKIPIF--
<?php 

if(!extension_loaded('usb')) die('skip ');

 ?>
--FILE--
<?php
$context; $devices; $result;

$result = usb_init($context);
if (USB_SUCCESS !== $result) {
    goto out;
}

$result = usb_get_device_list($context, $devices);
if (0 > $result) {
    goto out;
}

var_dump(usb_get_device_address($devices[0]));

out:

if ($devices) usb_free_device_list($devices);
if ($context) usb_exit($context);
?>
--EXPECTF--
int(%d)