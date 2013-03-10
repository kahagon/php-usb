--TEST--
usb_get_device_speed() function
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
if (1 > $result) {
    goto out;
}

switch(usb_get_device_speed($devices[0])) {
    case USB_SPEED_LOW:
    case USB_SPEED_FULL:
    case USB_SPEED_HIGH:
    case USB_SPEED_SUPER:
    case USB_SPEED_UNKNOWN:
        print 'OK';
        break;
    default:
        print 'FAILED';
        break;
}

out:

if ($devices) usb_free_device_list($devices);
if ($context) usb_exit($context);
?>
--EXPECT--
OK