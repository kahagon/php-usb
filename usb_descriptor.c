#include "php_usb.h"

/* {{{ proto int usb_get_device_descriptor(resource usb_device device, mixed &device_descriptor)
   */
PHP_FUNCTION(usb_get_device_descriptor)
{
	zval * device = NULL;
	int device_id = -1;
	libusb_device * res_device;

	zval * device_descriptor = NULL;
	struct libusb_device_descriptor res_device_descriptor;
	int result;


	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "rz/", &device, &device_descriptor) == FAILURE) {
		return;
	}
	phpusb_fetch_resource(res_device, libusb_device *, device, device_id, "usb_device", le_usb_device);
	
//	if ((res_device = (libusb_context *)zend_fetch_resource(Z_RES_P(device), "usb_device", le_usb_device)) == NULL) {
//		RETURN_FALSE;
//	}

	result = libusb_get_device_descriptor(res_device, &res_device_descriptor);
	if (result == LIBUSB_SUCCESS) {
		store_device_descriptor_to_zval(&res_device_descriptor, device_descriptor, INTERNAL_FUNCTION_PARAM_PASSTHRU);
	}
	
	RETURN_LONG(result);
}
/* }}} usb_get_device_descriptor */

/* {{{ proto int usb_get_active_config_descriptor(resource usb_device device, mixed &config_descriptor)
   */
PHP_FUNCTION(usb_get_active_config_descriptor)
{
	zval * device = NULL;
	int device_id = -1;
	libusb_device * res_device;

	zval * zval_class_instance_config_descriptor = NULL;
	libusb_config_descriptor *libusb_resource_config_descriptor;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "rz/", &device, &zval_class_instance_config_descriptor) == FAILURE) {
		return;
	}
	phpusb_fetch_resource(res_device, libusb_device *, device, device_id, "usb_device", le_usb_device);	

	int result = libusb_get_active_config_descriptor(res_device, &libusb_resource_config_descriptor);
	if (result != LIBUSB_SUCCESS) {
		// TODO: throw exception
		RETURN_FALSE;
	}
	
	zval zval_resource_instance_config_descriptor;
	phpusb_register_resource(&zval_resource_instance_config_descriptor, libusb_resource_config_descriptor, le_usb_config_descriptor);
	
	zval constructor_method_name;
	zval constructor_ret_val;
	zval *params[1];
	INIT_ZVAL(constructor_method_name);
	ZVAL_STRING(&constructor_method_name, ZEND_CONSTRUCTOR_FUNC_NAME, 1);
	params[0] = &zval_resource_instance_config_descriptor;
	object_init_ex(zval_class_instance_config_descriptor, ConfigDescriptor_ce_ptr);
	call_user_function(EG(function_table), &zval_class_instance_config_descriptor, &constructor_method_name, (zval *)&constructor_ret_val, 1, params TSRMLS_CC);


	
	RETURN_LONG(0);
}
/* }}} usb_get_active_config_descriptor */

#if 0
/* {{{ proto int usb_get_config_descriptor(resource usb_device device, int config_index, mixed &config_descriptor)
   */
PHP_FUNCTION(usb_get_config_descriptor)
{
	zval * device = NULL;
	int device_id = -1;
	libusb_device * res_device;

	long config_index = 0;
	zval * config_descriptor = NULL;
	struct libusb_config_descriptor *res_config_descriptor;
	int result;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "rlz", &device, &config_index, &config_descriptor) == FAILURE) {
		return;
	}
	ZEND_FETCH_RESOURCE(res_device, libusb_device *, &device, device_id, "usb_device", le_usb_device);

	result = libusb_get_config_descriptor(res_device, config_index, &res_config_descriptor);
	if (result == LIBUSB_SUCCESS) {
		store_config_descriptor_to_zval(res_config_descriptor, config_descriptor, INTERNAL_FUNCTION_PARAM_PASSTHRU);
		libusb_free_config_descriptor(res_config_descriptor);
	}

	RETURN_LONG(result);
}
/* }}} usb_get_config_descriptor */


/* {{{ proto int usb_get_config_descriptor_by_value(resource usb_device device, int bConfigurationValue, mixed &config_descriptor)
   */
PHP_FUNCTION(usb_get_config_descriptor_by_value)
{
	zval * device = NULL;
	int device_id = -1;
	libusb_device * res_device;

	long bConfigurationValue = 0;
	zval * config_descriptor = NULL;
	struct libusb_config_descriptor *res_config_descriptor;
	int result;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "rlz", &device, &bConfigurationValue, &config_descriptor) == FAILURE) {
		return;
	}
	ZEND_FETCH_RESOURCE(res_device, libusb_device *, &device, device_id, "usb_device", le_usb_device);

	result = libusb_get_config_descriptor_by_value(res_device, bConfigurationValue, &res_config_descriptor);
	if (result == LIBUSB_SUCCESS) {
		store_config_descriptor_to_zval(res_config_descriptor, config_descriptor, INTERNAL_FUNCTION_PARAM_PASSTHRU);
		libusb_free_config_descriptor(res_config_descriptor);
	}

	RETURN_LONG(result);
}
/* }}} usb_get_config_descriptor_by_value */


/* {{{ proto void usb_free_config_descriptor(mixed &config_descriptor)
   */
PHP_FUNCTION(usb_free_config_descriptor)
{

	zval * config_descriptor = NULL;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "z", &config_descriptor) == FAILURE) {
		return;
	}

	php_error(E_WARNING, "usb_free_config_descriptor: not yet implemented"); RETURN_FALSE;

}
/* }}} usb_free_config_descriptor */


/* {{{ proto int usb_get_string_descriptor_ascii(resource usb_device_handle device_handle, int desc_index, mixed &data)
   */
PHP_FUNCTION(usb_get_string_descriptor_ascii)
{
#define buff_length 4096
	zval * device_handle = NULL;
	int device_handle_id = -1;
	libusb_device_handle * res_device_handle;

	long desc_index = 0;
	zval * data = NULL;
	int result;
	char buff[buff_length];

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "rlz", &device_handle, &desc_index, &data) == FAILURE) {
		return;
	}
	ZEND_FETCH_RESOURCE(res_device_handle, libusb_device_handle *, &device_handle, device_handle_id, "usb_device_handle", le_usb_device_handle);

	result = libusb_get_string_descriptor_ascii(res_device_handle, desc_index, buff, 256);
	if (0 <= result) {
		ZVAL_STRINGL(data, buff, result, 1);
	}
	
	RETURN_LONG(result);
}
/* }}} usb_get_string_descriptor_ascii */


/* {{{ proto int usb_get_descriptor(resource usb_device_handle device_handle, int desc_type, int desc_index, mixed &data)
   */
PHP_FUNCTION(usb_get_descriptor)
{
#define buff_length 4096
	zval * device_handle = NULL;
	int device_handle_id = -1;
	libusb_device_handle * res_device_handle;

	long desc_type = 0;
	long desc_index = 0;
	zval * data = NULL;
	char buff[buff_length];
	int result;
	
	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "rllz", &device_handle, &desc_type, &desc_index, &data) == FAILURE) {
		return;
	}
	ZEND_FETCH_RESOURCE(res_device_handle, libusb_device_handle *, &device_handle, device_handle_id, "usb_device_handle", le_usb_device_handle);

	if (LIBUSB_DT_DEVICE == desc_type 
		|| LIBUSB_DT_CONFIG == desc_type 
		|| LIBUSB_DT_INTERFACE == desc_type 
		|| LIBUSB_DT_ENDPOINT == desc_type 
		|| LIBUSB_DT_STRING == desc_type) 
	{
		result = libusb_get_descriptor(res_device_handle, desc_type, desc_index, buff, buff_length);
		if (result >= 0) {
		if (desc_type == LIBUSB_DT_DEVICE) {
			struct libusb_device_descriptor *res_device_descriptor = (struct libusb_device_descriptor *)estrndup(buff, result);
			store_device_descriptor_to_zval(res_device_descriptor, data, INTERNAL_FUNCTION_PARAM_PASSTHRU);
			efree(res_device_descriptor);
		} else if (desc_type == LIBUSB_DT_CONFIG) {
		} else if (desc_type == LIBUSB_DT_INTERFACE) {
		} else if (desc_type == LIBUSB_DT_ENDPOINT) {
		} else {
			ZVAL_STRINGL(data, buff, result, 1);
		}
		}
	} else {
		result = LIBUSB_ERROR_NOT_SUPPORTED;
	}

	RETURN_LONG(result);
}
/* }}} usb_get_descriptor */


/* {{{ proto int usb_get_string_descriptor(resource usb_device_handle device_handle, int desc_index, int langid, mixed &data)
   */
PHP_FUNCTION(usb_get_string_descriptor)
{
	zval * device_handle = NULL;
	int device_handle_id = -1;
	libusb_device_handle * res_device_handle;

	long desc_index = 0;
	long langid = 0;
	zval * data = NULL;



	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "rllz", &device_handle, &desc_index, &langid, &data) == FAILURE) {
		return;
	}
	ZEND_FETCH_RESOURCE(res_device_handle, libusb_device_handle *, &device_handle, device_handle_id, "usb_device_handle", le_usb_device_handle);



	php_error(E_WARNING, "usb_get_string_descriptor: not yet implemented"); RETURN_FALSE;

	RETURN_LONG(0);
}
/* }}} usb_get_string_descriptor */

#endif