<?php
$context = null;
if ($argc == 2) {
	$ids = explode(':', $argv[1]);
    $vendor_id = intval($ids[0], 16);
    $product_id = intval($ids[1], 16);
} else {
	printf('Usage: php %s vid:pid' . PHP_EOL, $argv[0]);
	exit(1);
}
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
// var_dump($context, $device_handle, $device);die();
usb_get_device_descriptor($device, $device_descriptor);
usb_get_active_config_descriptor($device, $config_descriptor);
var_dump($device_descriptor, $config_descriptor);

usb_get_string_descriptor_ascii($device_handle, $device_descriptor->iManufacturer, $str_iManufacturer);
usb_get_string_descriptor_ascii($device_handle, $device_descriptor->iProduct, $str_iProduct);
usb_get_string_descriptor_ascii($device_handle, $device_descriptor->iSerialNumber, $str_iSerialNumber);
usb_get_string_descriptor_ascii($device_handle, $config_descriptor->iConfiguration, $str_iConfiguration);
var_dump($str_iManufacturer, $str_iProduct, $str_iSerialNumber, $str_iConfiguration);

$fetched_configuration = null;
$transferred = usb_control_transfer(
        $device_handle, 
        USB_ENDPOINT_IN, 
        USB_REQUEST_GET_STATUS, 
        0, 0, $fetched_configuration, -1, 2000);

var_dump($transferred, $fetched_configuration);
if ($transferred < 0) print usb_error_name($transferred) . PHP_EOL;


out:
if ($device_handle) usb_close($device_handle);
if ($context) usb_exit($context);
