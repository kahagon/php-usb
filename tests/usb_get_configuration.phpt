--TEST--
usb_get_configuration() function
--SKIPIF--
<?php 

if(!extension_loaded('usb')) die('skip ');

 ?>
--FILE--
<?php
$context; $devices; $handle;
$result; $bConfigurationValue;

$result = usb_init($context);
if (USB_SUCCESS !== $result) {
    print('failed to usb_init()' . PHP_EOL);
    goto out;
}

$result = usb_get_device_list($context, $devices);
if (0 > $result) {
    print('failed to usb_get_device_list()' . PHP_EOL);
    goto out;
} else if (0 == count($devices)) {
    print('not found any usb devices.' . PHP_EOL);
    goto out;
}

$devices[0];
if (USB_SUCCESS != usb_open($devices[0], $handle)) {
    print('failed to usb_open()' . PHP_EOL);
    goto out;
}

if (USB_SUCCESS != usb_get_configuration($handle, $bConfigurationValue)) {
    print('failed to usb_get_configuration()' . PHP_EOL);
    goto out;
}

var_dump($bConfigurationValue);

out:

if ($handle) usb_close($handle);
if ($devices) usb_free_device_list($devices);
if ($context) usb_exit($context);
?>
--EXPECTF--
int(%d)