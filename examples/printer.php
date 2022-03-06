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
    printf('failed to open printer(vid: 0x%04x, pid: 0x%04x)' . PHP_EOL, $vendor_id, $product_id);
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

$device_id = get_device_id($device_handle, 0, 0, 0);
$status = get_port_status($device_handle, 0);
var_dump($device_id, $status);

out:
if ($device_handle) usb_close($device_handle);
if ($context) usb_exit($context);

function get_port_status($device_handle, $interface_index) {
    /* Printer Class Specific Request GET_DEVICE_ID */
    $data = null;
    $bmRequestType = 0b10100001;
    $bRequest = 1;
    $wValue = 0;
    $wIndex = $interface_index;

    if (usb_kernel_driver_active($device_handle, $interface_index)) {
        $res = usb_detach_kernel_driver($device_handle, $interface_index);
        if ($res != USB_SUCCESS) {
            printf("failed to detach kernel driver. error: %s\n", usb_error_name($res));
            return null;
        }
    }
    $res = usb_control_transfer($device_handle, $bmRequestType, $bRequest, $wValue, $wIndex, $data, -1, 1000);

    if ($res < 1) {
        printf("failed to get_port_status(). error : %s\n", usb_error_name($res));
        return null;
    }


    return array(
        'paper_empty' => $data & (1<<5) ? true : false, 
        'select' => $data & (1<<4) ? true : false,
        'not_error' => $data & (1<<3) ? true : false);
}

function get_device_id($device_handle, $config_index, $interface_index, $alt_setting_index) {
    /* Printer Class Specific Request GET_DEVICE_ID */
    $device_id = null;
    $bmRequestType = 0b10100001;
    $bRequest = 0;
    $wValue = $config_index;
    $wIndex = ($interface_index<<4) & $alt_setting_index;

    if (usb_kernel_driver_active($device_handle, $interface_index)) {
        $res = usb_detach_kernel_driver($device_handle, $interface_index);
        if ($res != USB_SUCCESS) {
            printf("failed to detach kernel driver. error: %s\n", usb_error_name($res));
            return null;
        }
    }
    $res = usb_control_transfer($device_handle, $bmRequestType, $bRequest, $wValue, $wIndex, $device_id, -1, 1000);

    if ($res < 1) {
        printf("failed to get_device_id(). error : %s\n", usb_error_name($res));
        return null;
    }

    /* the first two bytes is length of device id string which include those. */
    return substr($device_id, 2, $res - 2);
}
