--TEST--
usb_get_device_descriptor() function
--SKIPIF--
<?php 

if(!extension_loaded('usb')) die('skip ');

 ?>
--FILE--
<?php
$context; $devices; $device_descriptor; $format;

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

$result = usb_get_device_descriptor($devices[0], $device_descriptor);
if (USB_SUCCESS != $result) {
    print('failed to usb_get_device_descriptor()' . PHP_EOL);
    print('error: ' . usb_error_name($result) . PHP_EOL);
    goto out;
}

$format =<<<EOF
bLength:            %d
bDescriptorType:    %d
bcdUSB:             0x%04x
bDeviceClass:       %d
bDeviceSubClass:    %d
bDeviceProtocol:    %d
bMaxPacketSize0:    0x%02x
idVendor:           0x%04x
idProduct:          0x%04x
bcdDevice:          0x%04x
iManufacturer:      0x%02x
iProduct:           0x%02x
iSerialNumber:      0x%02x
bNumConfiguration:  0x%02x

EOF;
printf($format, 
        $device_descriptor->bLength,
        $device_descriptor->bDescriptorType,
        $device_descriptor->bcdUSB,
        $device_descriptor->bDeviceClass,
        $device_descriptor->bDeviceSubClass,
        $device_descriptor->bDeviceProtocol,
        $device_descriptor->bMaxPacketSize0,
        $device_descriptor->idVendor,
        $device_descriptor->idProduct,
        $device_descriptor->bcdDevice,
        $device_descriptor->iManufacturer,
        $device_descriptor->iProduct,
        $device_descriptor->iSerialNumber,
        $device_descriptor->bNumConfigurations);


out:
if ($devices) usb_free_device_list($devices);
if ($context) usb_exit($context);
?>
--EXPECTF--
bLength:            %d
bDescriptorType:    %d
bcdUSB:             0x%x
bDeviceClass:       %d
bDeviceSubClass:    %d
bDeviceProtocol:    %d
bMaxPacketSize0:    0x%x
idVendor:           0x%x
idProduct:          0x%x
bcdDevice:          0x%x
iManufacturer:      0x%x
iProduct:           0x%x
iSerialNumber:      0x%x
bNumConfiguration:  0x%x