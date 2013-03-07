<?php
$context = null;
$result_init = usb_init($context);
if ($result_init != USB_SUCCESS) {
    die('failed to usb_init(). ' . usb_error_name($result_init));
}

$device_resources = array();
$result_devices = usb_get_device_list($context, $device_resources);
if ($result_devices < 0) {
    die('failed to usb_get_device_list(). ' . usb_error_name($result_devices));
}

var_dump($device_resources);
foreach ($device_resources as $device) {
    $handle;
    $result_open = usb_open($device, $handle);
    if ($result_open == USB_SUCCESS) {
        var_dump($handle);
        usb_close($handle);
    } else {
        print 'failed to usb_open(). ' . usb_error_name($result_open) . PHP_EOL;
    }
}


usb_free_device_list($device_resources);
usb_exit($context);