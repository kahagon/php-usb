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

foreach ($device_resources as $device) {
    $device_descriptor;
    $config_descriptor;
    usb_get_device_descriptor($device, $device_descriptor);
    var_dump($device_descriptor);
    usb_get_config_descriptor($device, $device_descriptor->bNumConfigurations - 1, $config_descriptor);
    var_dump($config_descriptor);
}

usb_free_device_list($device_resources);
usb_exit($context);
