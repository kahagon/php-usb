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


/* {{{ proto string usb_descriptor_type_name(int descriptor_type_code)
   */
PHP_FUNCTION(usb_descriptor_type_name)
{
	char *descriptor_type_name = NULL;
	long descriptor_type_code = 0;
	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "l", &descriptor_type_code) == FAILURE) {
		return;
	}

	switch (descriptor_type_code) {
		case LIBUSB_DT_DEVICE:
			descriptor_type_name = "USB_DT_DEVICE";
			break;
		case LIBUSB_DT_CONFIG:
			descriptor_type_name = "USB_DT_CONFIG";
			break;
		case LIBUSB_DT_STRING:
			descriptor_type_name = "USB_DT_STRING";
			break;
		case LIBUSB_DT_INTERFACE:
			descriptor_type_name = "USB_DT_INTERFACE";
			break;
		case LIBUSB_DT_ENDPOINT:
			descriptor_type_name = "USB_DT_ENDPOINT";
			break;
		case LIBUSB_DT_BOS:
			descriptor_type_name = "USB_DT_BOS";
			break;
		case LIBUSB_DT_DEVICE_CAPABILITY:
			descriptor_type_name = "USB_DT_DEVICE_CAPABILITY";
			break;
		case LIBUSB_DT_HID:
			descriptor_type_name = "USB_DT_HID";
			break;
		case LIBUSB_DT_REPORT:
			descriptor_type_name = "USB_DT_REPORT";
			break;
		case LIBUSB_DT_PHYSICAL:
			descriptor_type_name = "USB_DT_PHYSICAL";
			break;
		case LIBUSB_DT_HUB:
			descriptor_type_name = "USB_DT_HUB";
			break;
		case LIBUSB_DT_SUPERSPEED_HUB:
			descriptor_type_name = "USB_DT_SUPERSPEED_HUB";
			break;
		case LIBUSB_DT_SS_ENDPOINT_COMPANION:
			descriptor_type_name = "USB_DT_SS_ENDPOINT_COMPANION";
			break;
		default:
			descriptor_type_name = "USB_DT_UNKNOWN";
			break;
	}
	
	RETURN_STRING(descriptor_type_name, 1);
}
/* }}} usb_descriptor_type_name */