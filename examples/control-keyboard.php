<?php
$vendor_id = 1455;//0x05af;
$product_id = 1287;//0x0507;
$context;
$result = usb_init($context);
if ($result != USB_SUCCESS) {
    die ('failed to usb_init(). ' . usb_error_name($result));
}

$handle = usb_open_device_with_vid_pid($context, $vendor_id, $product_id);
var_dump($handle);
if (!$handle) {
    goto out;
} else {
    usb_close($handle);
    var_dump($handle);
}

out:
usb_exit($context);