--TEST--
usb_kernel_driver_active() function
--SKIPIF--
<?php 
die('skip test is not implemented.');
if(!extension_loaded('usb')) die('skip ');

 ?>
--FILE--
<?php
echo 'OK'; // no test case for this function yet
?>
--EXPECT--
OK