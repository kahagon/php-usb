<?php
if ($argc == 2) {
	$ids = explode(':', $argv[1]);
    $vendor_id = intval($ids[0], 16);
    $product_id = intval($ids[1], 16);
} else {
	printf('Usage: php %s vid:pid' . PHP_EOL, $argv[0]);
	exit(1);
}
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