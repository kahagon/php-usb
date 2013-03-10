--TEST--
usb_get_config_descriptor() function
--SKIPIF--
<?php 

if(!extension_loaded('usb')) die('skip ');

 ?>
--FILE--
<?php
$context = null;
$devices = array();
$result;

$result = usb_init($context);
if (USB_SUCCESS != $result) {
    die('failed to usb_init(). ' . usb_error_name($result));
}


$result = usb_get_device_list($context, $devices);
if (0 > $result) {
    print('failed to usb_get_device_list()' . PHP_EOL . 'error: ' . usb_error_name($result_devices));
    goto out;
} else if (0 == $result) {
    print ('usb device does not exist.' . PHP_EOL);
    goto out;
}

//$device = $device_resources[0];
foreach ($devices as $device) {
    $device_descriptor;
    $config_descriptor;
    
    if (USB_SUCCESS != usb_get_device_descriptor($device, $device_descriptor)) {
        continue;
    }
    
    if (0 < $device_descriptor->bNumConfigurations) {
        usb_get_config_descriptor($device, $device_descriptor->bNumConfigurations - 1, $config_descriptor);
        var_dump($config_descriptor->bConfigurationValue);
        break;
    } else {
        continue;
    }
}

out:
usb_free_device_list($devices);
usb_exit($context);
?>
--EXPECTF--
int(%d)