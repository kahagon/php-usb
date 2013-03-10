--TEST--
usb_get_active_config_descriptor() function
--SKIPIF--
<?php 

if(!extension_loaded('usb')) die('skip ');

 ?>
--FILE--
<?php
$context; $devices; $config_descriptor; $format;

if (USB_SUCCESS !== usb_init($context)) {
    goto out;
}

// expect that existence of an usb device.
$result = usb_get_device_list($context, $devices);
if (0 > $result) {
    print('failed to usb_get_device_list()' . PHP_EOL);
    goto out;
} else if (0 == count($devices)) {
    print('not found any usb devices.' . PHP_EOL);
    goto out;
}

$result = usb_get_active_config_descriptor($devices[0], $config_descriptor);
if (USB_SUCCESS != $result) {
    print('failed to usb_get_device_descriptor()' . PHP_EOL);
    print('error: ' . usb_error_name($result) . PHP_EOL);
    goto out;
}

var_dump($config_descriptor->bConfigurationValue);


out:
if ($devices) usb_free_device_list($devices);
if ($context) usb_exit($context);
?>
--EXPECTF--
int(%d)