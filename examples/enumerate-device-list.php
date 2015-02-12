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

$options = getopt("v::");
$verbose = array_key_exists('v', $options);

foreach ($device_resources as $device) {
    $handle;
    $device_descriptor;
    $config_descriptor;

    usb_get_device_descriptor($device, $device_descriptor);
    usb_get_active_config_descriptor($device, $config_descriptor);
    $result_open = usb_open($device, $handle);
    if ($result_open == USB_SUCCESS) {
        usb_get_string_descriptor_ascii($handle, $device_descriptor->iManufacturer, $manufacturer);
        usb_get_string_descriptor_ascii($handle, $device_descriptor->iProduct, $product);
        printf("%04x:%04x %s %s\n", 
            $device_descriptor->idVendor, 
            $device_descriptor->idProduct, 
            $manufacturer,
            $product);
        if ($verbose) {
            var_dump($device_descriptor, $config_descriptor);
            print "\n"; 
        }
        usb_close($handle);
    } else {
        print 'failed to usb_open(). ' . usb_error_name($result_open) . PHP_EOL;
    }
}

usb_free_device_list($device_resources);
usb_exit($context);
