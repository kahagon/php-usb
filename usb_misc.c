#include "php_usb.h"

/* {{{ proto int usb_has_capability(int capability)
   */
PHP_FUNCTION(usb_has_capability)
{

	long capability = 0;
        
	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "l", &capability) == FAILURE) {
		return;
	}

	RETURN_LONG(libusb_has_capability(capability));
}
/* }}} usb_has_capability */


/* {{{ proto string usb_error_name(int error_code)
   */
PHP_FUNCTION(usb_error_name)
{

	long error_code = 0;
	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "l", &error_code) == FAILURE) {
		return;
	}
        
	RETURN_STRING(libusb_error_name(error_code), 1);
}
/* }}} usb_error_name */

/* {{{ proto string usb_class_name(int class_code)
   */
PHP_FUNCTION(usb_class_name)
{
        char *class_name = NULL;
        long class_code = 0;
        if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "l", &class_code) == FAILURE) {
                return;
        }

        switch (class_code) {
            case LIBUSB_CLASS_PER_INTERFACE:
                class_name = "USB_CLASS_PER_INTERFACE";
                break;
            case LIBUSB_CLASS_AUDIO:
                class_name = "USB_CLASS_AUDIO";
                break;
            case LIBUSB_CLASS_COMM:
                class_name = "USB_CLASS_COMM";
                break;
            case LIBUSB_CLASS_HID:
                class_name = "USB_CLASS_HID";
                break;
            case LIBUSB_CLASS_PHYSICAL:
                class_name = "USB_CLASS_PHYSICAL";
                break;
            case LIBUSB_CLASS_PRINTER:
                class_name = "USB_CLASS_PRINTER";
                break;
            case LIBUSB_CLASS_IMAGE:
                class_name = "USB_CLASS_IMAGE";
                break;
            case LIBUSB_CLASS_MASS_STORAGE:
                class_name = "USB_CLASS_MASS_STORAGE";
                break;
            case LIBUSB_CLASS_HUB:
                class_name = "USB_CLASS_HUB";
                break;
            case LIBUSB_CLASS_DATA:
                class_name = "USB_CLASS_DATA";
                break;
            case LIBUSB_CLASS_SMART_CARD:
                class_name = "USB_CLASS_SMART_CARD";
                break;
            case LIBUSB_CLASS_CONTENT_SECURITY:
                class_name = "USB_CLASS_CONTENT_SECURITY";
                break;
            case LIBUSB_CLASS_VIDEO:
                class_name = "USB_CLASS_VIDEO";
                break;
            case LIBUSB_CLASS_PERSONAL_HEALTHCARE:
                class_name = "USB_CLASS_PERSONAL_HEALTHCARE";
                break;
            case LIBUSB_CLASS_DIAGNOSTIC_DEVICE:
                class_name = "USB_CLASS_DIAGNOSTIC_DEVICE";
                break;
            case LIBUSB_CLASS_WIRELESS:
                class_name = "USB_CLASS_WIRELESS";
                break;
            case LIBUSB_CLASS_MISCELLANEOUS:
                class_name = "USB_CLASS_MISCELLANEOUS";
                break;
            case LIBUSB_CLASS_APPLICATION:
                class_name = "USB_CLASS_APPLICATION";
                break;
            case LIBUSB_CLASS_VENDOR_SPEC:
                class_name = "USB_CLASS_VENDOR_SPEC";
                break;
            default:
                class_name = "UNKNOWN";
                break;
        }

        RETURN_STRING(class_name, 1);
}
/* }}} usb_class_name */

