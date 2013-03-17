<?php
$context = null;
$vendor_id = 0x058f;
$product_id = 0x3831;
$result_init = usb_init($context);
if ($result_init != USB_SUCCESS) {
    die('failed to usb_init(). ' . usb_error_name($result_init));
}

$str_iManufacturer = null;
$str_iProduct = null;
$str_iSerialNumber = null;
$str_iConfiguration = null;
$device_descriptor = null;
$config_descriptor = null;
$device_handle = usb_open_device_with_vid_pid($context, $vendor_id, $product_id);
if ($device_handle === null) {
    printf('failed to open webcam(vid: 0x%04x, pid: 0x%04x)' . PHP_EOL, $vendor_id, $product_id);
    goto out;
}

$device = usb_get_device($device_handle);
usb_get_device_descriptor($device, $device_descriptor);
usb_get_active_config_descriptor($device, $config_descriptor);
var_dump($device_descriptor, $config_descriptor);

usb_get_string_descriptor_ascii($device_handle, $device_descriptor->iManufacturer, $str_iManufacturer);
usb_get_string_descriptor_ascii($device_handle, $device_descriptor->iProduct, $str_iProduct);
usb_get_string_descriptor_ascii($device_handle, $device_descriptor->iSerialNumber, $str_iSerialNumber);
usb_get_string_descriptor_ascii($device_handle, $config_descriptor->iConfiguration, $str_iConfiguration);
var_dump($str_iManufacturer, $str_iProduct, $str_iSerialNumber, $str_iConfiguration);

out:
if ($device_handle) usb_close($device_handle);
if ($context) usb_exit($context);
