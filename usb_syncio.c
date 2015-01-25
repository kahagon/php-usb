#include "php_usb.h"

/* {{{ proto int usb_control_transfer(resource usb_device_handle device_handle, int bmRequestType, int bRequest, int wValue, int wIndex, mixed &data, int wLength, int timeout)
   */
PHP_FUNCTION(usb_control_transfer)
{
	zval * device_handle = NULL;
	int device_handle_id = -1;
	libusb_device_handle * res_device_handle;

	long bmRequestType = 0;
	long bRequest = 0;
	long wValue = 0;
	long wIndex = 0;
	zval * data = NULL;
	long wLength = 0;
	long timeout = 0;
        int actual_transferred = 0;
        unsigned char *buffer = NULL;
        int buffer_length;
        int is_read;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "rllllzll", &device_handle, &bmRequestType, &bRequest, &wValue, &wIndex, &data, &wLength, &timeout) == FAILURE) {
		return;
	}
	ZEND_FETCH_RESOURCE(res_device_handle, libusb_device_handle *, &device_handle, device_handle_id, "usb_device_handle", le_usb_device_handle);

        is_read = bmRequestType & (1 << 7);
        if (wLength < 0) wLength = 4092;
        if (is_read) { // device to host, read.
            buffer_length = wLength;
            buffer = ecalloc(1, buffer_length);
        } else { // host to device, write.
            if (IS_NULL == Z_TYPE_P(data)) {
                buffer_length = 0;
                buffer = NULL;
            } else if (IS_STRING == Z_TYPE_P(data)) {
                buffer_length = Z_STRLEN_P(data);
                buffer = estrndup(Z_STRVAL_P(data), buffer_length);
            } else {
                php_error(E_WARNING, "6th parameter must be string when direction is host to device.");
                RETURN_LONG(LIBUSB_ERROR_INVALID_PARAM);
            }
        }
        
        actual_transferred = libusb_control_transfer(res_device_handle, bmRequestType, bRequest, wValue, wIndex, buffer, buffer_length, timeout);
        if (is_read && 0 < actual_transferred) {
            ZVAL_STRINGL(data, buffer, actual_transferred, 1);
        }
        
        if (buffer != NULL) efree(buffer);
        
	RETURN_LONG(actual_transferred);
}
/* }}} usb_control_transfer */


/* {{{ proto int usb_bulk_transfer(resource usb_device_handle device_handle, int endpoint, mixed &data, int length, mixed &transferred, int timeout)
   */
PHP_FUNCTION(usb_bulk_transfer)
{
	zval * device_handle = NULL;
	int device_handle_id = -1;
	libusb_device_handle * res_device_handle;

	long endpoint = 0;
	zval * data = NULL;
	long length = 0;
	zval * transferred = NULL;
	long timeout = 0;
        unsigned char *buffer = NULL;
        int buffer_length;
        int actual_transferred = 0;
        int result;
        int is_read;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "rlzlzl", &device_handle, &endpoint, &data, &length, &transferred, &timeout) == FAILURE) {
		return;
	}
	ZEND_FETCH_RESOURCE(res_device_handle, libusb_device_handle *, &device_handle, device_handle_id, "usb_device_handle", le_usb_device_handle);

        is_read = endpoint & (1 << 7);
        if (length < 0) length = 4092;
        if (is_read) { // device to host, read.
            buffer_length = length;
            buffer = ecalloc(1, buffer_length);
        } else { // host to device, write.
            if (IS_NULL == Z_TYPE_P(data)) {
                buffer_length = 0;
                buffer = NULL;
            } else if (IS_STRING == Z_TYPE_P(data)) {
                buffer_length = Z_STRLEN_P(data);
                buffer = estrndup(Z_STRVAL_P(data), buffer_length);
            } else {
                php_error(E_WARNING, "3rd parameter must be string when direction is host to device.");
                RETURN_LONG(LIBUSB_ERROR_INVALID_PARAM);
            }
        }

	result = libusb_bulk_transfer(res_device_handle, endpoint, buffer, buffer_length, &actual_transferred, timeout);

        if (is_read && 0 < actual_transferred) {
            ZVAL_STRINGL(data, buffer, actual_transferred, 1);
        }
        ZVAL_LONG(transferred, actual_transferred);
            
        if (buffer != NULL) efree(buffer);

	RETURN_LONG(result);
}
/* }}} usb_bulk_transfer */


/* {{{ proto int usb_interrupt_transfer(resource usb_device_handle device_handle, int endpoint, mixed &data, int length, mixed &transferred, int timeout)
   */
PHP_FUNCTION(usb_interrupt_transfer)
{
	zval * device_handle = NULL;
	int device_handle_id = -1;
	libusb_device_handle * res_device_handle;

	long endpoint = 0;
	zval * data = NULL;
	long length = 0;
	zval * transferred = NULL;
	long timeout = 0;
        unsigned char *buffer = NULL;
        int buffer_length;
        int actual_transferred = 0;
        int result;
        int is_read;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "rlzlzl", &device_handle, &endpoint, &data, &length, &transferred, &timeout) == FAILURE) {
		return;
	}
	ZEND_FETCH_RESOURCE(res_device_handle, libusb_device_handle *, &device_handle, device_handle_id, "usb_device_handle", le_usb_device_handle);

        is_read = endpoint & (1 << 7);
        if (length < 0) length = 4092;
        if (is_read) { // device to host, read.
            buffer_length = length;
            buffer = ecalloc(1, buffer_length);
        } else { // host to device, write.
            if (IS_NULL == Z_TYPE_P(data)) {
                buffer_length = 0;
                buffer = NULL;
            } else if (IS_STRING == Z_TYPE_P(data)) {
                buffer_length = Z_STRLEN_P(data);
                buffer = estrndup(Z_STRVAL_P(data), buffer_length);
            } else {
                php_error(E_WARNING, "3rd parameter must be string when direction is host to device.");
                RETURN_LONG(LIBUSB_ERROR_INVALID_PARAM);
            }
        }

	result = libusb_interrupt_transfer(res_device_handle, endpoint, buffer, buffer_length, &actual_transferred, timeout);
        if (is_read && 0 < actual_transferred) {
            ZVAL_STRINGL(data, buffer, actual_transferred, 1);
        }
        ZVAL_LONG(transferred, actual_transferred);
        
        if (buffer != NULL) efree(buffer);

	RETURN_LONG(result);
}
/* }}} usb_interrupt_transfer */

