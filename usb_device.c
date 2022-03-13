#include "php_usb.h"

/* {{{ proto int usb_init(mixed &context)
   */
PHP_FUNCTION(usb_init)
{

	zval * context = NULL;
	int context_id = -1;
	libusb_context * res_context;
	int result = LIBUSB_SUCCESS;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "z/", &context) == FAILURE) {
		return;
	}
	if (Z_TYPE_P(context) == IS_RESOURCE) {
		phpusb_fetch_resource(res_context, libusb_context *, context, context_id, "usb_context", le_usb_context);
	}

	result = libusb_init(&res_context);
	phpusb_register_resource(context, res_context, le_usb_context);

	RETURN_LONG(result);
}
/* }}} usb_init */


/* {{{ proto void usb_exit(resource usb_context context)
   */
PHP_FUNCTION(usb_exit)
{
	zval * context = NULL;
	int context_id = -1;
	libusb_context * res_context;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "r", &context) == FAILURE) {
		return;
	}
	
	phpusb_fetch_resource(res_context, libusb_context *, context, context_id, "usb_context", le_usb_context);
	libusb_exit(res_context);
	
	zend_list_delete(PHPUSB_RES_P(context));
}
/* }}} usb_exit */


/* {{{ proto int usb_get_device_list(resource usb_context context, mixed &device_list)
   */
PHP_FUNCTION(usb_get_device_list)
{
	zval * context = NULL;
	int context_id = -1;
	libusb_context * res_context;

	zval * device_list = NULL;
	int i = 0;
	ssize_t len;
	libusb_device **devices;


	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "rz/", &context, &device_list) == FAILURE) {
		return;
	}
	phpusb_fetch_resource(res_context, libusb_context *, context, context_id, "usb_context", le_usb_context);
	
	array_init(device_list);
	
	len = libusb_get_device_list(res_context, &devices);
	if (len >= 0) {
		for (i = 0; i < len; i++) {
			zval zval_device;
			libusb_device *device = devices[i];
			add_next_index_resource(device_list, phpusb_register_resource(&zval_device, device, le_usb_device));
		}
	}
	
	free(devices);
	RETURN_LONG(len);
}
/* }}} usb_get_device_list */

/* {{{ proto void usb_free_device_list(array device_list)
   */
PHP_FUNCTION(usb_free_device_list)
{

	zval * device_list;
	zval *data;
	HashTable * device_list_hash;
	HashPosition pointer;
	int device_list_count = -1;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "a/", &device_list) == FAILURE) {
		return;
	}
	device_list_hash = Z_ARRVAL_P(device_list);
	device_list_count = zend_hash_num_elements(device_list_hash);
	
    zend_hash_internal_pointer_reset_ex(device_list_hash, &pointer);
    for(;; zend_hash_move_forward_ex(device_list_hash, &pointer)) 
    {
        if (NULL == (data = phpusb_hash_get_current_data_ex(device_list_hash, &pointer))) {
            break;
        }

        libusb_device * res_device;
        int device_id = -1;
        		
        phpusb_fetch_resource(res_device, libusb_device *, data, device_id, "usb_device", le_usb_device);
        libusb_unref_device(res_device);
        zend_list_delete(PHPUSB_RES_P(data));
    }
}
/* }}} usb_free_device_list */



#if 0
/* {{{ proto int usb_open(resource usb_device device, mixed &device_handle)
   */
PHP_FUNCTION(usb_open)
{
	zval * device = NULL;
	int device_id = -1;
	libusb_device * res_device;
	libusb_device_handle *res_handle;
	zval * device_handle = NULL;
	int result;


	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "rz", &device, &device_handle) == FAILURE) {
		return;
	}
	ZEND_FETCH_RESOURCE(res_device, libusb_device *, &device, device_id, "usb_device", le_usb_device);


	result = libusb_open(res_device, &res_handle);
	if (result == LIBUSB_SUCCESS) {
		ZVAL_RESOURCE(device_handle, res_handle);
		ZEND_REGISTER_RESOURCE(device_handle, res_handle, le_usb_device_handle);
	}

	RETURN_LONG(result);
}
/* }}} usb_open */


/* {{{ proto void usb_close(resource usb_device_handle device_handle)
   */
PHP_FUNCTION(usb_close)
{
	zval * device_handle = NULL;
	int device_handle_id = -1;
	libusb_device_handle * res_device_handle;




	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "r", &device_handle) == FAILURE) {
		return;
	}
	ZEND_FETCH_RESOURCE(res_device_handle, libusb_device_handle *, &device_handle, device_handle_id, "usb_device_handle", le_usb_device_handle);

	libusb_close(res_device_handle);
	zend_list_delete(Z_RESVAL_P(device_handle));

}
/* }}} usb_close */

/* {{{ proto int usb_get_bus_number(resource usb_device device)
   */
PHP_FUNCTION(usb_get_bus_number)
{
	zval * device = NULL;
	int device_id = -1;
	libusb_device * res_device;




	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "r", &device) == FAILURE) {
		return;
	}
	ZEND_FETCH_RESOURCE(res_device, libusb_device *, &device, device_id, "usb_device", le_usb_device);

	RETURN_LONG(libusb_get_bus_number(res_device));
}
/* }}} usb_get_bus_number */


/* {{{ proto int usb_get_device_address(resource usb_device device)
   */
PHP_FUNCTION(usb_get_device_address)
{
	zval * device = NULL;
	int device_id = -1;
	libusb_device * res_device;




	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "r", &device) == FAILURE) {
		return;
	}
	ZEND_FETCH_RESOURCE(res_device, libusb_device *, &device, device_id, "usb_device", le_usb_device);

	RETURN_LONG(libusb_get_device_address(res_device));
}
/* }}} usb_get_device_address */


/* {{{ proto int usb_get_device_speed(resource usb_device device)
   */
PHP_FUNCTION(usb_get_device_speed)
{
	zval * device = NULL;
	int device_id = -1;
	libusb_device * res_device;




	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "r", &device) == FAILURE) {
		return;
	}
	ZEND_FETCH_RESOURCE(res_device, libusb_device *, &device, device_id, "usb_device", le_usb_device);

	RETURN_LONG(libusb_get_device_speed(res_device));
}
/* }}} usb_get_device_speed */


/* {{{ proto int usb_get_max_packet_size(resource usb_device device, int endpoint)
   */
PHP_FUNCTION(usb_get_max_packet_size)
{
	zval * device = NULL;
	int device_id = -1;
	libusb_device * res_device;

	long endpoint = 0;



	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "rl", &device, &endpoint) == FAILURE) {
		return;
	}
	ZEND_FETCH_RESOURCE(res_device, libusb_device *, &device, device_id, "usb_device", le_usb_device);

	RETURN_LONG(libusb_get_max_packet_size(res_device, endpoint));
}
/* }}} usb_get_max_packet_size */

/* {{{ proto int usb_get_max_iso_packet_size(resource usb_device device, int endpoint)
   */
PHP_FUNCTION(usb_get_max_iso_packet_size)
{
	zval * device = NULL;
	int device_id = -1;
	libusb_device * res_device;

	long endpoint = 0;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "rl", &device, &endpoint) == FAILURE) {
		return;
	}
	ZEND_FETCH_RESOURCE(res_device, libusb_device *, &device, device_id, "usb_device", le_usb_device);

	RETURN_LONG(libusb_get_max_iso_packet_size(res_device, endpoint));
}
/* }}} usb_get_max_iso_packet_size */

/* {{{ proto resource usb_device usb_ref_device(resource usb_device device)
   */
PHP_FUNCTION(usb_ref_device)
{
	libusb_device * return_res;
	long return_res_id = -1;
	zval * device = NULL;
	int device_id = -1;
	libusb_device * res_device;
	
	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "r", &device) == FAILURE) {
		return;
	}
	ZEND_FETCH_RESOURCE(res_device, libusb_device *, &device, device_id, "usb_device", le_usb_device);

	libusb_ref_device(res_device);
	RETURN_ZVAL(device, 1, 0);
}
/* }}} usb_ref_device */


/* {{{ proto void usb_unref_device(resource usb_device device)
   */
PHP_FUNCTION(usb_unref_device)
{
	zval * device = NULL;
	int device_id = -1;
	libusb_device * res_device;
	
	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "r", &device) == FAILURE) {
		return;
	}
	ZEND_FETCH_RESOURCE(res_device, libusb_device *, &device, device_id, "usb_device", le_usb_device);

	libusb_unref_device(res_device);
}
/* }}} usb_unref_device */


/* {{{ proto resource usb_device_handle usb_open_device_with_vid_pid(resource usb_context context, int vendor_id, int product_id)
   */
PHP_FUNCTION(usb_open_device_with_vid_pid)
{
	libusb_device_handle * return_res;
	long return_res_id = -1;
	zval * context = NULL;
	int context_id = -1;
	libusb_context * res_context;

	long vendor_id = 0;
	long product_id = 0;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "rll", &context, &vendor_id, &product_id) == FAILURE) {
		return;
	}
	ZEND_FETCH_RESOURCE(res_context, libusb_context *, &context, context_id, "usb_context", le_usb_context);

	return_res = libusb_open_device_with_vid_pid(res_context, vendor_id, product_id);
	if (return_res == NULL) RETURN_NULL();
	
	ZEND_REGISTER_RESOURCE(return_value, return_res, le_usb_device_handle);
	//RETURN_RESOURCE(return_res);
}
/* }}} usb_open_device_with_vid_pid */


/* {{{ proto resource usb_device usb_get_device(resource usb_device_handle device_handle)
   */
PHP_FUNCTION(usb_get_device)
{
	libusb_device * return_res;
	long return_res_id = -1;
	zval * device_handle = NULL;
	int device_handle_id = -1;
	libusb_device_handle * res_device_handle;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "r", &device_handle) == FAILURE) {
		return;
	}
	ZEND_FETCH_RESOURCE(res_device_handle, libusb_device_handle *, &device_handle, device_handle_id, "usb_device_handle", le_usb_device_handle);

	return_res = libusb_get_device(res_device_handle);
	ZEND_REGISTER_RESOURCE(return_value, return_res, le_usb_device);
}
/* }}} usb_get_device */


/* {{{ proto int usb_get_configuration(resource usb_device_handle device_handle, mixed &config)
   */
PHP_FUNCTION(usb_get_configuration)
{
	zval * device_handle = NULL;
	int device_handle_id = -1;
	libusb_device_handle * res_device_handle;

	zval * config = NULL;
	int bConfigurationValue;
	int result;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "rz", &device_handle, &config) == FAILURE) {
		return;
	}
	ZEND_FETCH_RESOURCE(res_device_handle, libusb_device_handle *, &device_handle, device_handle_id, "usb_device_handle", le_usb_device_handle);

	result = libusb_get_configuration(res_device_handle, &bConfigurationValue);
	ZVAL_LONG(config, bConfigurationValue);

	RETURN_LONG(result);
}
/* }}} usb_get_configuration */


/* {{{ proto int usb_set_configuration(resource usb_device_handle device_handle, int configuration)
   */
PHP_FUNCTION(usb_set_configuration)
{
	zval * device_handle = NULL;
	int device_handle_id = -1;
	libusb_device_handle * res_device_handle;

	long configuration = 0;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "rl", &device_handle, &configuration) == FAILURE) {
		return;
	}
	ZEND_FETCH_RESOURCE(res_device_handle, libusb_device_handle *, &device_handle, device_handle_id, "usb_device_handle", le_usb_device_handle);

	RETURN_LONG(libusb_set_configuration(res_device_handle, configuration));
}
/* }}} usb_set_configuration */


/* {{{ proto int usb_claim_interface(resource usb_device_handle device_handle, int interface_number)
   */
PHP_FUNCTION(usb_claim_interface)
{
	zval * device_handle = NULL;
	int device_handle_id = -1;
	libusb_device_handle * res_device_handle;

	long interface_number = 0;
	
	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "rl", &device_handle, &interface_number) == FAILURE) {
		return;
	}
	ZEND_FETCH_RESOURCE(res_device_handle, libusb_device_handle *, &device_handle, device_handle_id, "usb_device_handle", le_usb_device_handle);

	RETURN_LONG(libusb_claim_interface(res_device_handle, interface_number));
}
/* }}} usb_claim_interface */


/* {{{ proto int usb_release_interface(resource usb_device_handle device_handle, int interface_number)
   */
PHP_FUNCTION(usb_release_interface)
{
	zval * device_handle = NULL;
	int device_handle_id = -1;
	libusb_device_handle * res_device_handle;

	long interface_number = 0;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "rl", &device_handle, &interface_number) == FAILURE) {
		return;
	}
	ZEND_FETCH_RESOURCE(res_device_handle, libusb_device_handle *, &device_handle, device_handle_id, "usb_device_handle", le_usb_device_handle);

	RETURN_LONG(libusb_release_interface(res_device_handle, interface_number));
}
/* }}} usb_release_interface */


/* {{{ proto int usb_set_interface_alt_setting(resource usb_device_handle device_handle, int interface_number, int alternate_setting)
   */
PHP_FUNCTION(usb_set_interface_alt_setting)
{
	zval * device_handle = NULL;
	int device_handle_id = -1;
	libusb_device_handle * res_device_handle;

	long interface_number = 0;
	long alternate_setting = 0;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "rll", &device_handle, &interface_number, &alternate_setting) == FAILURE) {
		return;
	}
	ZEND_FETCH_RESOURCE(res_device_handle, libusb_device_handle *, &device_handle, device_handle_id, "usb_device_handle", le_usb_device_handle);

	RETURN_LONG(libusb_set_interface_alt_setting(res_device_handle, interface_number, alternate_setting));
}
/* }}} usb_set_interface_alt_setting */


/* {{{ proto int usb_clear_halt(resource usb_device_handle device_handle, int endpoint)
   */
PHP_FUNCTION(usb_clear_halt)
{
	zval * device_handle = NULL;
	int device_handle_id = -1;
	libusb_device_handle * res_device_handle;

	long endpoint = 0;
	
	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "rl", &device_handle, &endpoint) == FAILURE) {
		return;
	}
	ZEND_FETCH_RESOURCE(res_device_handle, libusb_device_handle *, &device_handle, device_handle_id, "usb_device_handle", le_usb_device_handle);

	RETURN_LONG(libusb_clear_halt(res_device_handle, endpoint));
}
/* }}} usb_clear_halt */


/* {{{ proto int usb_reset_device(resource usb_device_handle device_handle)
   */
PHP_FUNCTION(usb_reset_device)
{
	zval * device_handle = NULL;
	int device_handle_id = -1;
	libusb_device_handle * res_device_handle;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "r", &device_handle) == FAILURE) {
		return;
	}
	ZEND_FETCH_RESOURCE(res_device_handle, libusb_device_handle *, &device_handle, device_handle_id, "usb_device_handle", le_usb_device_handle);

	RETURN_LONG(libusb_reset_device(res_device_handle));
}
/* }}} usb_reset_device */


/* {{{ proto int usb_kernel_driver_active(resource usb_device_handle device_handle, int interface_number)
   */
PHP_FUNCTION(usb_kernel_driver_active)
{
	zval * device_handle = NULL;
	int device_handle_id = -1;
	libusb_device_handle * res_device_handle;

	long interface_number = 0;



	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "rl", &device_handle, &interface_number) == FAILURE) {
		return;
	}
	ZEND_FETCH_RESOURCE(res_device_handle, libusb_device_handle *, &device_handle, device_handle_id, "usb_device_handle", le_usb_device_handle);

	RETURN_LONG(libusb_kernel_driver_active(res_device_handle, interface_number));
}
/* }}} usb_kernel_driver_active */


/* {{{ proto int usb_detach_kernel_driver(resource usb_device_handle device_handle, int interface_number)
   */
PHP_FUNCTION(usb_detach_kernel_driver)
{
	zval * device_handle = NULL;
	int device_handle_id = -1;
	libusb_device_handle * res_device_handle;

	long interface_number = 0;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "rl", &device_handle, &interface_number) == FAILURE) {
		return;
	}
	ZEND_FETCH_RESOURCE(res_device_handle, libusb_device_handle *, &device_handle, device_handle_id, "usb_device_handle", le_usb_device_handle);

	RETURN_LONG(libusb_detach_kernel_driver(res_device_handle, interface_number));
}
/* }}} usb_detach_kernel_driver */


/* {{{ proto int usb_attach_kernel_driver(resource usb_device_handle device_handle, int interface_number)
   */
PHP_FUNCTION(usb_attach_kernel_driver)
{
	zval * device_handle = NULL;
	int device_handle_id = -1;
	libusb_device_handle * res_device_handle;

	long interface_number = 0;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "rl", &device_handle, &interface_number) == FAILURE) {
		return;
	}
	ZEND_FETCH_RESOURCE(res_device_handle, libusb_device_handle *, &device_handle, device_handle_id, "usb_device_handle", le_usb_device_handle);

	RETURN_LONG(libusb_attach_kernel_driver(res_device_handle, interface_number));
}
/* }}} usb_attach_kernel_driver */

#endif