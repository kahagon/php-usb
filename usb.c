/*
   +----------------------------------------------------------------------+
   | This source file is subject to version 3.0 of the PHP license,       |
   | that is bundled with this package in the file LICENSE, and is        |
   | available through the world-wide-web at the following url:           |
   | http://www.php.net/license/3_0.txt.                                  |
   | If you did not receive a copy of the PHP license and are unable to   |
   | obtain it through the world-wide-web, please send a note to          |
   | license@php.net so we can mail you a copy immediately.               |
   +----------------------------------------------------------------------+
   | Authors: Keng-ichi Ahagon <k.ahagon@n-3.so>                          |
   +----------------------------------------------------------------------+
*/

/* $ Id: $ */ 

#include "php_usb.h"

#if HAVE_USB

/* {{{ Resource destructors */
int le_usb_context;
void usb_context_dtor(zend_rsrc_list_entry *rsrc TSRMLS_DC)
{
	libusb_context * resource = (libusb_context *)(rsrc->ptr);

	do {
            /* call libusb_exit() here, causes dead-lock or double free. */
	} while (0);
}

int le_usb_device;
void usb_device_dtor(zend_rsrc_list_entry *rsrc TSRMLS_DC)
{
	libusb_device * resource = (libusb_device *)(rsrc->ptr);

	do {
	} while (0);
}

int le_usb_device_handle;
void usb_device_handle_dtor(zend_rsrc_list_entry *rsrc TSRMLS_DC)
{
	libusb_device_handle * resource = (libusb_device_handle *)(rsrc->ptr);

	do {
	} while (0);
}

int le_usb_device_descriptor;
void usb_device_descriptor_dtor(zend_rsrc_list_entry *rsrc TSRMLS_DC)
{
	struct libusb_device_descriptor * resource = (struct libusb_device_descriptor *)(rsrc->ptr);

	do {
	} while (0);
}

int le_usb_endpoint_descriptor;
void usb_endpoint_descriptor_dtor(zend_rsrc_list_entry *rsrc TSRMLS_DC)
{
	struct libusb_endpoint_descriptor * resource = (struct libusb_endpoint_descriptor *)(rsrc->ptr);

	do {
	} while (0);
}

int le_usb_interface_descriptor;
void usb_interface_descriptor_dtor(zend_rsrc_list_entry *rsrc TSRMLS_DC)
{
	struct libusb_interface_descriptor * resource = (struct libusb_interface_descriptor *)(rsrc->ptr);

	do {
	} while (0);
}

int le_usb_interface;
void usb_interface_dtor(zend_rsrc_list_entry *rsrc TSRMLS_DC)
{
	struct libusb_interface * resource = (struct libusb_interface *)(rsrc->ptr);

	do {
	} while (0);
}

int le_usb_config_descriptor;
void usb_config_descriptor_dtor(zend_rsrc_list_entry *rsrc TSRMLS_DC)
{
	struct libusb_config_descriptor * resource = (struct libusb_config_descriptor *)(rsrc->ptr);

	do {
	} while (0);
}

/* }}} */

/* {{{ usb_functions[] */
zend_function_entry usb_functions[] = {
	PHP_FE(usb_init            , usb_init_arg_info)
	PHP_FE(usb_exit            , usb_exit_arg_info)
	PHP_FE(usb_get_device_list , usb_get_device_list_arg_info)
	PHP_FE(usb_free_device_list, usb_free_device_list_arg_info)
	PHP_FE(usb_open            , usb_open_arg_info)
	PHP_FE(usb_close           , usb_close_arg_info)
	PHP_FE(usb_get_bus_number  , usb_get_bus_number_arg_info)
	PHP_FE(usb_get_device_address, usb_get_device_address_arg_info)
	PHP_FE(usb_get_device_speed, usb_get_device_speed_arg_info)
	PHP_FE(usb_get_max_packet_size, usb_get_max_packet_size_arg_info)
	PHP_FE(usb_get_max_iso_packet_size, usb_get_max_iso_packet_size_arg_info)
	PHP_FE(usb_ref_device      , usb_ref_device_arg_info)
	PHP_FE(usb_unref_device    , usb_unref_device_arg_info)
	PHP_FE(usb_open_device_with_vid_pid, usb_open_device_with_vid_pid_arg_info)
	PHP_FE(usb_get_device      , usb_get_device_arg_info)
	PHP_FE(usb_get_configuration, usb_get_configuration_arg_info)
	PHP_FE(usb_set_configuration, usb_set_configuration_arg_info)
	PHP_FE(usb_claim_interface , usb_claim_interface_arg_info)
	PHP_FE(usb_release_interface, usb_release_interface_arg_info)
	PHP_FE(usb_set_interface_alt_setting, usb_set_interface_alt_setting_arg_info)
	PHP_FE(usb_clear_halt      , usb_clear_halt_arg_info)
	PHP_FE(usb_reset_device    , usb_reset_device_arg_info)
	PHP_FE(usb_kernel_driver_active, usb_kernel_driver_active_arg_info)
	PHP_FE(usb_detach_kernel_driver, usb_detach_kernel_driver_arg_info)
	PHP_FE(usb_attach_kernel_driver, usb_attach_kernel_driver_arg_info)
	PHP_FE(usb_has_capability  , usb_has_capability_arg_info)
	PHP_FE(usb_error_name      , usb_error_name_arg_info)
	PHP_FE(usb_get_device_descriptor, usb_get_device_descriptor_arg_info)
	PHP_FE(usb_get_active_config_descriptor, usb_get_active_config_descriptor_arg_info)
	PHP_FE(usb_get_config_descriptor, usb_get_config_descriptor_arg_info)
	PHP_FE(usb_get_config_descriptor_by_value, usb_get_config_descriptor_by_value_arg_info)
	PHP_FE(usb_free_config_descriptor, usb_free_config_descriptor_arg_info)
	PHP_FE(usb_get_string_descriptor_ascii, usb_get_string_descriptor_ascii_arg_info)
	PHP_FE(usb_get_descriptor  , usb_get_descriptor_arg_info)
	PHP_FE(usb_get_string_descriptor, usb_get_string_descriptor_arg_info)
	PHP_FE(usb_control_transfer, usb_control_transfer_arg_info)
	PHP_FE(usb_bulk_transfer   , usb_bulk_transfer_arg_info)
	PHP_FE(usb_interrupt_transfer, usb_interrupt_transfer_arg_info)
	{ NULL, NULL, NULL }
};
/* }}} */


/* {{{ usb_module_entry
 */
zend_module_entry usb_module_entry = {
	STANDARD_MODULE_HEADER,
	"usb",
	usb_functions,
	PHP_MINIT(usb),     /* Replace with NULL if there is nothing to do at php startup   */ 
	PHP_MSHUTDOWN(usb), /* Replace with NULL if there is nothing to do at php shutdown  */
	PHP_RINIT(usb),     /* Replace with NULL if there is nothing to do at request start */
	PHP_RSHUTDOWN(usb), /* Replace with NULL if there is nothing to do at request end   */
	PHP_MINFO(usb),
	PHP_USB_VERSION, 
	STANDARD_MODULE_PROPERTIES
};
/* }}} */

#ifdef COMPILE_DL_USB
ZEND_GET_MODULE(usb)
#endif


/* {{{ PHP_MINIT_FUNCTION */
PHP_MINIT_FUNCTION(usb)
{
	REGISTER_LONG_CONSTANT("USB_REQUEST_GET_STATUS", LIBUSB_REQUEST_GET_STATUS, CONST_PERSISTENT | CONST_CS);
	REGISTER_LONG_CONSTANT("USB_REQUEST_CLEAR_FEATURE", LIBUSB_REQUEST_CLEAR_FEATURE, CONST_PERSISTENT | CONST_CS);
	REGISTER_LONG_CONSTANT("USB_REQUEST_SET_FEATURE", LIBUSB_REQUEST_SET_FEATURE, CONST_PERSISTENT | CONST_CS);
	REGISTER_LONG_CONSTANT("USB_REQUEST_SET_ADDRESS", LIBUSB_REQUEST_GET_DESCRIPTOR, CONST_PERSISTENT | CONST_CS);
	REGISTER_LONG_CONSTANT("USB_REQUEST_SET_DESCRIPTOR", LIBUSB_REQUEST_SET_DESCRIPTOR, CONST_PERSISTENT | CONST_CS);
	REGISTER_LONG_CONSTANT("USB_REQUEST_GET_CONFIGURATION", LIBUSB_REQUEST_GET_CONFIGURATION, CONST_PERSISTENT | CONST_CS);
	REGISTER_LONG_CONSTANT("USB_REQUEST_SET_CONFIGURATION", LIBUSB_REQUEST_SET_CONFIGURATION, CONST_PERSISTENT | CONST_CS);
	REGISTER_LONG_CONSTANT("USB_REQUEST_GET_INTERFACE", LIBUSB_REQUEST_GET_INTERFACE, CONST_PERSISTENT | CONST_CS);
	REGISTER_LONG_CONSTANT("USB_REQUEST_SET_INTERFACE", LIBUSB_REQUEST_SET_INTERFACE, CONST_PERSISTENT | CONST_CS);
	REGISTER_LONG_CONSTANT("USB_REQUEST_SYNCH_FRAME", LIBUSB_REQUEST_SYNCH_FRAME, CONST_PERSISTENT | CONST_CS);
	REGISTER_LONG_CONSTANT("USB_REQUEST_TYPE_STANDARD", LIBUSB_REQUEST_TYPE_STANDARD, CONST_PERSISTENT | CONST_CS);
	REGISTER_LONG_CONSTANT("USB_REQUEST_TYPE_CLASS", LIBUSB_REQUEST_TYPE_CLASS, CONST_PERSISTENT | CONST_CS);
	REGISTER_LONG_CONSTANT("USB_REQUEST_TYPE_VENDOR", LIBUSB_REQUEST_TYPE_VENDOR, CONST_PERSISTENT | CONST_CS);
	REGISTER_LONG_CONSTANT("USB_REQUEST_TYPE_RESERVED", LIBUSB_REQUEST_TYPE_RESERVED, CONST_PERSISTENT | CONST_CS);
	REGISTER_LONG_CONSTANT("USB_RECIPIENT_DEVICE", LIBUSB_RECIPIENT_DEVICE, CONST_PERSISTENT | CONST_CS);
	REGISTER_LONG_CONSTANT("USB_RECIPIENT_INTERFACE", LIBUSB_RECIPIENT_INTERFACE, CONST_PERSISTENT | CONST_CS);
	REGISTER_LONG_CONSTANT("USB_RECIPIENT_ENDPOINT", LIBUSB_RECIPIENT_ENDPOINT, CONST_PERSISTENT | CONST_CS);
	REGISTER_LONG_CONSTANT("USB_RECIPIENT_OTHER", LIBUSB_RECIPIENT_OTHER, CONST_PERSISTENT | CONST_CS);
	REGISTER_LONG_CONSTANT("USB_SUCCESS", LIBUSB_SUCCESS, CONST_PERSISTENT | CONST_CS);
	REGISTER_LONG_CONSTANT("USB_ERROR_IO", LIBUSB_ERROR_IO, CONST_PERSISTENT | CONST_CS);
	REGISTER_LONG_CONSTANT("USB_ERROR_INVALID_PARAM", LIBUSB_ERROR_INVALID_PARAM, CONST_PERSISTENT | CONST_CS);
	REGISTER_LONG_CONSTANT("USB_ERROR_ACCESS", LIBUSB_ERROR_ACCESS, CONST_PERSISTENT | CONST_CS);
	REGISTER_LONG_CONSTANT("USB_ERROR_NO_DEVICE", LIBUSB_ERROR_NO_DEVICE, CONST_PERSISTENT | CONST_CS);
	REGISTER_LONG_CONSTANT("USB_ERROR_NOT_FOUND", LIBUSB_ERROR_NOT_FOUND, CONST_PERSISTENT | CONST_CS);
	REGISTER_LONG_CONSTANT("USB_ERROR_BUSY", LIBUSB_ERROR_BUSY, CONST_PERSISTENT | CONST_CS);
	REGISTER_LONG_CONSTANT("USB_ERROR_TIMEOUT", LIBUSB_ERROR_TIMEOUT, CONST_PERSISTENT | CONST_CS);
	REGISTER_LONG_CONSTANT("USB_ERROR_OVERFLOW", LIBUSB_ERROR_OVERFLOW, CONST_PERSISTENT | CONST_CS);
	REGISTER_LONG_CONSTANT("USB_ERROR_PIPE", LIBUSB_ERROR_PIPE, CONST_PERSISTENT | CONST_CS);
	REGISTER_LONG_CONSTANT("USB_ERROR_INTERRUPTED", LIBUSB_ERROR_INTERRUPTED, CONST_PERSISTENT | CONST_CS);
	REGISTER_LONG_CONSTANT("USB_ERROR_NOT_SUPPORTED", LIBUSB_ERROR_NO_MEM, CONST_PERSISTENT | CONST_CS);
	REGISTER_LONG_CONSTANT("USB_ERROR_OTHER", LIBUSB_ERROR_OTHER, CONST_PERSISTENT | CONST_CS);
	REGISTER_LONG_CONSTANT("USB_CAP_HAS_CAPABILITY", LIBUSB_CAP_HAS_CAPABILITY, CONST_PERSISTENT | CONST_CS);
	REGISTER_LONG_CONSTANT("USB_SPEED_UNKNOWN", LIBUSB_SPEED_UNKNOWN, CONST_PERSISTENT | CONST_CS);
	REGISTER_LONG_CONSTANT("USB_SPEED_LOW", LIBUSB_SPEED_LOW, CONST_PERSISTENT | CONST_CS);
	REGISTER_LONG_CONSTANT("USB_SPEED_FULL", LIBUSB_SPEED_FULL, CONST_PERSISTENT | CONST_CS);
        REGISTER_LONG_CONSTANT("USB_SPEED_HIGH", LIBUSB_SPEED_HIGH, CONST_PERSISTENT | CONST_CS);
        REGISTER_LONG_CONSTANT("USB_SPEED_SUPER", LIBUSB_SPEED_SUPER, CONST_PERSISTENT | CONST_CS);
	REGISTER_LONG_CONSTANT("USB_CLASS_PER_INTERFACE", LIBUSB_CLASS_PER_INTERFACE, CONST_PERSISTENT | CONST_CS);
	REGISTER_LONG_CONSTANT("USB_CLASS_AUDIO", LIBUSB_CLASS_AUDIO, CONST_PERSISTENT | CONST_CS);
	REGISTER_LONG_CONSTANT("USB_CLASS_COMM", LIBUSB_CLASS_COMM, CONST_PERSISTENT | CONST_CS);
	REGISTER_LONG_CONSTANT("USB_CLASS_HID", LIBUSB_CLASS_HID, CONST_PERSISTENT | CONST_CS);
	REGISTER_LONG_CONSTANT("USB_CLASS_PHYSICAL", LIBUSB_CLASS_PHYSICAL, CONST_PERSISTENT | CONST_CS);
	REGISTER_LONG_CONSTANT("USB_CLASS_PRINTER", LIBUSB_CLASS_PRINTER, CONST_PERSISTENT | CONST_CS);
	REGISTER_LONG_CONSTANT("USB_CLASS_PTP", LIBUSB_CLASS_PTP, CONST_PERSISTENT | CONST_CS);
	REGISTER_LONG_CONSTANT("USB_CLASS_IMAGE", LIBUSB_CLASS_IMAGE, CONST_PERSISTENT | CONST_CS);
	REGISTER_LONG_CONSTANT("USB_CLASS_MASS_STORAGE", LIBUSB_CLASS_MASS_STORAGE, CONST_PERSISTENT | CONST_CS);
	REGISTER_LONG_CONSTANT("USB_CLASS_HUB", LIBUSB_CLASS_HUB, CONST_PERSISTENT | CONST_CS);
	REGISTER_LONG_CONSTANT("USB_CLASS_DATA", LIBUSB_CLASS_DATA, CONST_PERSISTENT | CONST_CS);
	REGISTER_LONG_CONSTANT("USB_CLASS_SMART_CARD", LIBUSB_CLASS_SMART_CARD, CONST_PERSISTENT | CONST_CS);
	REGISTER_LONG_CONSTANT("USB_CLASS_CONTENT_SECURITY", LIBUSB_CLASS_CONTENT_SECURITY, CONST_PERSISTENT | CONST_CS);
	REGISTER_LONG_CONSTANT("USB_CLASS_VIDEO", LIBUSB_CLASS_VIDEO, CONST_PERSISTENT | CONST_CS);
	REGISTER_LONG_CONSTANT("USB_CLASS_PERSONAL_HEALTHCARE", LIBUSB_CLASS_PERSONAL_HEALTHCARE, CONST_PERSISTENT | CONST_CS);
	REGISTER_LONG_CONSTANT("USB_CLASS_DIAGNOSTIC_DEVICE", LIBUSB_CLASS_DIAGNOSTIC_DEVICE, CONST_PERSISTENT | CONST_CS);
	REGISTER_LONG_CONSTANT("USB_CLASS_WIRELESS", LIBUSB_CLASS_WIRELESS, CONST_PERSISTENT | CONST_CS);
	REGISTER_LONG_CONSTANT("USB_CLASS_APPLICATION", LIBUSB_CLASS_APPLICATION, CONST_PERSISTENT | CONST_CS);
	REGISTER_LONG_CONSTANT("USB_CLASS_VENDOR_SPEC", LIBUSB_CLASS_VENDOR_SPEC, CONST_PERSISTENT | CONST_CS);
	REGISTER_LONG_CONSTANT("USB_DT_DEVICE", LIBUSB_DT_DEVICE, CONST_PERSISTENT | CONST_CS);
	REGISTER_LONG_CONSTANT("USB_DT_CONFIG", LIBUSB_DT_CONFIG, CONST_PERSISTENT | CONST_CS);
	REGISTER_LONG_CONSTANT("USB_DT_STRING", LIBUSB_DT_STRING, CONST_PERSISTENT | CONST_CS);
	REGISTER_LONG_CONSTANT("USB_DT_INTERFACE", LIBUSB_DT_INTERFACE, CONST_PERSISTENT | CONST_CS);
	REGISTER_LONG_CONSTANT("USB_DT_ENDPOINT", LIBUSB_DT_ENDPOINT, CONST_PERSISTENT | CONST_CS);
	REGISTER_LONG_CONSTANT("USB_DT_HID", LIBUSB_DT_HID, CONST_PERSISTENT | CONST_CS);
	REGISTER_LONG_CONSTANT("USB_DT_REPORT", LIBUSB_DT_REPORT, CONST_PERSISTENT | CONST_CS);
	REGISTER_LONG_CONSTANT("USB_DT_PHYSICAL", LIBUSB_DT_PHYSICAL, CONST_PERSISTENT | CONST_CS);
	REGISTER_LONG_CONSTANT("USB_DT_HUB", LIBUSB_DT_HUB, CONST_PERSISTENT | CONST_CS);
	REGISTER_LONG_CONSTANT("USB_ENDPOINT_IN", LIBUSB_ENDPOINT_IN, CONST_PERSISTENT | CONST_CS);
	REGISTER_LONG_CONSTANT("USB_ENDPOINT_OUT", LIBUSB_ENDPOINT_OUT, CONST_PERSISTENT | CONST_CS);
	REGISTER_LONG_CONSTANT("USB_TRANSFER_TYPE_CONTROL", LIBUSB_TRANSFER_TYPE_CONTROL, CONST_PERSISTENT | CONST_CS);
	REGISTER_LONG_CONSTANT("USB_TRANSFER_TYPE_ISOCHRONOUS", LIBUSB_TRANSFER_TYPE_ISOCHRONOUS, CONST_PERSISTENT | CONST_CS);
	REGISTER_LONG_CONSTANT("USB_TRANSFER_TYPE_BULK", LIBUSB_TRANSFER_TYPE_BULK, CONST_PERSISTENT | CONST_CS);
	REGISTER_LONG_CONSTANT("USB_TRANSFER_TYPE_INTERRUPT", LIBUSB_TRANSFER_TYPE_INTERRUPT, CONST_PERSISTENT | CONST_CS);
	REGISTER_LONG_CONSTANT("USB_ISO_SYNC_TYPE_NONE", LIBUSB_ISO_SYNC_TYPE_NONE, CONST_PERSISTENT | CONST_CS);
	REGISTER_LONG_CONSTANT("USB_ISO_SYNC_TYPE_ASYNC", LIBUSB_ISO_SYNC_TYPE_ASYNC, CONST_PERSISTENT | CONST_CS);
	REGISTER_LONG_CONSTANT("USB_ISO_SYNC_TYPE_ADAPTIVE", LIBUSB_ISO_SYNC_TYPE_ADAPTIVE, CONST_PERSISTENT | CONST_CS);
	REGISTER_LONG_CONSTANT("USB_ISO_SYNC_TYPE_SYNC", LIBUSB_ISO_SYNC_TYPE_SYNC, CONST_PERSISTENT | CONST_CS);
	REGISTER_LONG_CONSTANT("USB_ISO_USAGE_TYPE_DATA", LIBUSB_ISO_USAGE_TYPE_DATA, CONST_PERSISTENT | CONST_CS);
	REGISTER_LONG_CONSTANT("USB_ISO_USAGE_TYPE_FEEDBACK", LIBUSB_ISO_USAGE_TYPE_FEEDBACK, CONST_PERSISTENT | CONST_CS);
	REGISTER_LONG_CONSTANT("USB_ISO_USAGE_TYPE_IMPLICIT", LIBUSB_ISO_USAGE_TYPE_IMPLICIT, CONST_PERSISTENT | CONST_CS);
	le_usb_context = zend_register_list_destructors_ex(usb_context_dtor, 
						   NULL, "usb_context", module_number);
	le_usb_device = zend_register_list_destructors_ex(usb_device_dtor, 
						   NULL, "usb_device", module_number);
	le_usb_device_handle = zend_register_list_destructors_ex(usb_device_handle_dtor, 
						   NULL, "usb_device_handle", module_number);
	le_usb_device_descriptor = zend_register_list_destructors_ex(usb_device_descriptor_dtor, 
						   NULL, "usb_device_descriptor", module_number);
	le_usb_endpoint_descriptor = zend_register_list_destructors_ex(usb_endpoint_descriptor_dtor, 
						   NULL, "usb_endpoint_descriptor", module_number);
	le_usb_interface_descriptor = zend_register_list_destructors_ex(usb_interface_descriptor_dtor, 
						   NULL, "usb_interface_descriptor", module_number);
	le_usb_interface = zend_register_list_destructors_ex(usb_interface_dtor, 
						   NULL, "usb_interface", module_number);
	le_usb_config_descriptor = zend_register_list_destructors_ex(usb_config_descriptor_dtor, 
						   NULL, "usb_config_descriptor", module_number);

	/* add your stuff here */

	return SUCCESS;
}
/* }}} */


/* {{{ PHP_MSHUTDOWN_FUNCTION */
PHP_MSHUTDOWN_FUNCTION(usb)
{

	/* add your stuff here */

	return SUCCESS;
}
/* }}} */


/* {{{ PHP_RINIT_FUNCTION */
PHP_RINIT_FUNCTION(usb)
{
	/* add your stuff here */

	return SUCCESS;
}
/* }}} */


/* {{{ PHP_RSHUTDOWN_FUNCTION */
PHP_RSHUTDOWN_FUNCTION(usb)
{
	/* add your stuff here */

	return SUCCESS;
}
/* }}} */


/* {{{ PHP_MINFO_FUNCTION */
PHP_MINFO_FUNCTION(usb)
{
	php_printf("libusb wrapper\n");
	php_info_print_table_start();
	php_info_print_table_row(2, "Version",PHP_USB_VERSION " (alpha)");
	php_info_print_table_row(2, "Released", "2013-03-02");
	php_info_print_table_row(2, "CVS Revision", "$Id: $");
	php_info_print_table_row(2, "Authors", "Keng-ichi Ahagon 'k.ahagon@n-3.so' (lead)\n");
	php_info_print_table_end();
	/* add your stuff here */

}
/* }}} */


/* {{{ proto int usb_init(mixed &context)
   */
PHP_FUNCTION(usb_init)
{

	zval * context = NULL;
	int context_id = -1;
	libusb_context * res_context;
        int result = LIBUSB_SUCCESS;



	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "z", &context) == FAILURE) {
		return;
	}
        if (Z_TYPE_P(context) == IS_RESOURCE) {
            ZEND_FETCH_RESOURCE(res_context, libusb_context *, &context, context_id, "usb_context", le_usb_context);
        }

	result = libusb_init(&res_context);
        ZVAL_RESOURCE(context, res_context);
        ZEND_REGISTER_RESOURCE(context, res_context, le_usb_context);

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
	ZEND_FETCH_RESOURCE(res_context, libusb_context *, &context, context_id, "usb_context", le_usb_context);


	libusb_exit(res_context);
        zend_list_delete(Z_RESVAL_P(context));
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


	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "rz", &context, &device_list) == FAILURE) {
		return;
	}
	ZEND_FETCH_RESOURCE(res_context, libusb_context *, &context, context_id, "usb_context", le_usb_context);

        array_init(device_list);
        
        len = libusb_get_device_list(res_context, &devices);
        if (len >= 0) {
            for (i = 0; i < len; i++) {
                zval *zval_device;
                libusb_device *device = devices[i];
                int res_id = -1;
                
                ALLOC_INIT_ZVAL(zval_device);
                ZVAL_RESOURCE(zval_device, device);
                res_id = ZEND_REGISTER_RESOURCE(zval_device, device, le_usb_device);
                add_next_index_resource(device_list, res_id);
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
        zval **data;
	HashTable * device_list_hash;
        HashPosition pointer;
        int device_list_count = -1;



	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "a/", &device_list) == FAILURE) {
		return;
	}
	device_list_hash = Z_ARRVAL_P(device_list);
        device_list_count = zend_hash_num_elements(device_list_hash);
        
        for(
                zend_hash_internal_pointer_reset_ex(device_list_hash, &pointer); 
                zend_hash_get_current_data_ex(device_list_hash, (void**) &data, &pointer) == SUCCESS; 
                zend_hash_move_forward_ex(device_list_hash, &pointer)) 
        {
            libusb_device * res_device;
            int device_id = -1;
            
            ZEND_FETCH_RESOURCE(res_device, libusb_device *, (zval **)data, device_id, "usb_device", le_usb_device);
            libusb_unref_device(res_device);
            zend_list_delete(Z_RESVAL_PP(data));
        }

}
/* }}} usb_free_device_list */


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

        RETURN_LONG(libusb_get_iso_max_packet_size(res_device, endpoint));
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

static void store_device_descriptor_to_zval(const struct libusb_device_descriptor *res_device_descriptor, zval * device_descriptor, INTERNAL_FUNCTION_PARAMETERS) {
    object_init(device_descriptor);
    add_property_long(device_descriptor, "bLength", res_device_descriptor->bLength);
    add_property_long(device_descriptor, "bDescriptorType", res_device_descriptor->bDescriptorType);
    add_property_long(device_descriptor, "bcdUSB", res_device_descriptor->bcdUSB);
    add_property_long(device_descriptor, "bDeviceClass", res_device_descriptor->bDeviceClass);
    add_property_long(device_descriptor, "bDeviceSubClass", res_device_descriptor->bDeviceSubClass);
    add_property_long(device_descriptor, "bDeviceProtocol", res_device_descriptor->bDeviceProtocol);
    add_property_long(device_descriptor, "bMaxPacketSize0", res_device_descriptor->bMaxPacketSize0);
    add_property_long(device_descriptor, "idVendor", res_device_descriptor->idVendor);
    add_property_long(device_descriptor, "idProduct", res_device_descriptor->idProduct);
    add_property_long(device_descriptor, "bcdDevice", res_device_descriptor->bcdDevice);
    add_property_long(device_descriptor, "iManufacturer", res_device_descriptor->iManufacturer);
    add_property_long(device_descriptor, "iProduct", res_device_descriptor->iProduct);
    add_property_long(device_descriptor, "iSerialNumber", res_device_descriptor->iSerialNumber);
    add_property_long(device_descriptor, "bNumConfigurations", res_device_descriptor->bNumConfigurations);
}

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


	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "rz", &device, &device_descriptor) == FAILURE) {
		return;
	}
	ZEND_FETCH_RESOURCE(res_device, libusb_device *, &device, device_id, "usb_device", le_usb_device);

        result = libusb_get_device_descriptor(res_device, &res_device_descriptor);
        if (result == LIBUSB_SUCCESS) {
            store_device_descriptor_to_zval(&res_device_descriptor, device_descriptor, INTERNAL_FUNCTION_PARAM_PASSTHRU);
        }
        
	RETURN_LONG(result);
}
/* }}} usb_get_device_descriptor */

static void store_config_descriptor_to_zval(const struct libusb_config_descriptor *res_config_descriptor, zval * config_descriptor, INTERNAL_FUNCTION_PARAMETERS) {
    int i = 0;
    zval *interface_array = NULL;
    ALLOC_INIT_ZVAL(interface_array);
    array_init(interface_array);

    object_init(config_descriptor);
    add_property_long(config_descriptor, "bLength", res_config_descriptor->bLength);
    add_property_long(config_descriptor, "bDescriptorType", res_config_descriptor->bDescriptorType);
    add_property_long(config_descriptor, "wTotalLength", res_config_descriptor->wTotalLength);
    add_property_long(config_descriptor, "bNumInterfaces", res_config_descriptor->bNumInterfaces);
    add_property_long(config_descriptor, "bConfigurationValue", res_config_descriptor->bConfigurationValue);
    add_property_long(config_descriptor, "iConfiguration", res_config_descriptor->iConfiguration);
    add_property_long(config_descriptor, "bmAttributes", res_config_descriptor->bmAttributes);
    add_property_long(config_descriptor, "MaxPower", res_config_descriptor->MaxPower);
    for (i = 0; i < res_config_descriptor->bNumInterfaces; i++) {
        const struct libusb_interface res_interface = res_config_descriptor->interface[i];
        zval *interface;
        zval *altsetting;
        int j = 0;
        
        //store_interface_to_zval(res_interface, interface, INTERNAL_FUNCTION_PARAM_PASSTHRU);
        //*
        ALLOC_INIT_ZVAL(interface);
        object_init(interface);

        ALLOC_INIT_ZVAL(altsetting);
        array_init(altsetting);
        
        for (j = 0; j < res_interface.num_altsetting; j++) {
            const struct libusb_interface_descriptor res_interface_descriptor = res_interface.altsetting[j];
            zval *interface_descriptor = NULL;
            zval *endpoint_array = NULL;
            int k = 0;

            ALLOC_INIT_ZVAL(interface_descriptor);
            object_init(interface_descriptor);

            ALLOC_INIT_ZVAL(endpoint_array);
            array_init(endpoint_array);

            add_property_long(interface_descriptor, "bLength", res_interface_descriptor.bLength);
            add_property_long(interface_descriptor, "bDescriptorType", res_interface_descriptor.bDescriptorType);
            add_property_long(interface_descriptor, "bInterfaceNumber", res_interface_descriptor.bInterfaceNumber);
            add_property_long(interface_descriptor, "bAlternateSetting", res_interface_descriptor.bAlternateSetting);
            add_property_long(interface_descriptor, "bNumEndpoints", res_interface_descriptor.bNumEndpoints);
            add_property_long(interface_descriptor, "bInterfaceClass", res_interface_descriptor.bInterfaceClass);
            add_property_long(interface_descriptor, "bInterfaceSubClass", res_interface_descriptor.bInterfaceSubClass);
            add_property_long(interface_descriptor, "bInterfaceProtocol", res_interface_descriptor.bInterfaceProtocol);
            add_property_long(interface_descriptor, "iInterface", res_interface_descriptor.iInterface);

            for (k = 0; k < res_interface_descriptor.bNumEndpoints; k++) {
                const struct libusb_endpoint_descriptor res_endpoint_descriptor = res_interface_descriptor.endpoint[k];
                zval *endpoint_descriptor = NULL;
                ALLOC_INIT_ZVAL(endpoint_descriptor);
                object_init(endpoint_descriptor);

                add_property_long(endpoint_descriptor, "bLength", res_endpoint_descriptor.bLength);
                add_property_long(endpoint_descriptor, "bDescriptorType", res_endpoint_descriptor.bDescriptorType);
                add_property_long(endpoint_descriptor, "bEndpointAddress", res_endpoint_descriptor.bEndpointAddress);
                add_property_long(endpoint_descriptor, "bmAttributes", res_endpoint_descriptor.bmAttributes);
                add_property_long(endpoint_descriptor, "wMaxPacketSize", res_endpoint_descriptor.wMaxPacketSize);
                add_property_long(endpoint_descriptor, "bInterval", res_endpoint_descriptor.bInterval);
                add_property_long(endpoint_descriptor, "bRefresh", res_endpoint_descriptor.bRefresh);
                add_property_long(endpoint_descriptor, "bSynchAddress", res_endpoint_descriptor.bSynchAddress);
                add_property_stringl(endpoint_descriptor, "extra", res_endpoint_descriptor.extra, res_endpoint_descriptor.extra_length, 1);
                add_property_long(endpoint_descriptor, "extra_length", res_endpoint_descriptor.extra_length);

                add_next_index_zval(endpoint_array, endpoint_descriptor);
            }

            add_property_zval(interface_descriptor, "endpoint", endpoint_array);
            add_property_stringl(interface_descriptor, "extra", res_interface_descriptor.extra, res_interface_descriptor.extra_length, 1);
            add_property_long(interface_descriptor, "extra_length", res_interface_descriptor.extra_length);

            add_next_index_zval(altsetting, interface_descriptor);
        }
        add_property_zval(interface, "altsetting", altsetting);
        add_property_long(interface, "num_altsetting", res_interface.num_altsetting);
        //*/
        add_next_index_zval(interface_array, interface);
    }
    add_property_zval(config_descriptor, "interface", interface_array);
    add_property_stringl(config_descriptor, "extra", res_config_descriptor->extra, res_config_descriptor->extra_length, 1);
    add_property_long(config_descriptor, "extra_length", res_config_descriptor->extra_length);
}

/* {{{ proto int usb_get_active_config_descriptor(resource usb_device device, mixed &config_descriptor)
   */
PHP_FUNCTION(usb_get_active_config_descriptor)
{
	zval * device = NULL;
	int device_id = -1;
	libusb_device * res_device;

	zval * config_descriptor = NULL;
        struct libusb_config_descriptor *res_config_descriptor;
        int result;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "rz", &device, &config_descriptor) == FAILURE) {
		return;
	}
	ZEND_FETCH_RESOURCE(res_device, libusb_device *, &device, device_id, "usb_device", le_usb_device);

        result = libusb_get_active_config_descriptor(res_device, &res_config_descriptor);
        if (result == LIBUSB_SUCCESS) {
            store_config_descriptor_to_zval(res_config_descriptor, config_descriptor, INTERNAL_FUNCTION_PARAM_PASSTHRU);
            libusb_free_config_descriptor(res_config_descriptor);
        }
        
	RETURN_LONG(0);
}
/* }}} usb_get_active_config_descriptor */


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
        unsigned char *buffer;
        int buffer_length;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "rllllzll", &device_handle, &bmRequestType, &bRequest, &wValue, &wIndex, &data, &wLength, &timeout) == FAILURE) {
		return;
	}
	ZEND_FETCH_RESOURCE(res_device_handle, libusb_device_handle *, &device_handle, device_handle_id, "usb_device_handle", le_usb_device_handle);

        if (wLength < 0) wLength = 4092;
        if (bmRequestType & 1) { // device to host, read.
            buffer_length = wLength;
            buffer = ecalloc(1, buffer_length);
        } else { // host to device, write.
            if (IS_STRING == Z_TYPE_P(data)) {
                buffer_length = Z_STRLEN_P(data);
                buffer = estrndup(Z_STRVAL_P(data), buffer_length);
            } else {
                buffer_length = wLength;
                buffer = ecalloc(1, buffer_length);
            }
        }
        
        actual_transferred = libusb_control_transfer(res_device_handle, bmRequestType, bRequest, wValue, wIndex, buffer, buffer_length, timeout);
        if (bmRequestType & 1 && 0 < actual_transferred) {
            ZVAL_STRINGL(data, buffer, actual_transferred, 1);
        }
        
        efree(buffer);
        
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



	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "rlzlzl", &device_handle, &endpoint, &data, &length, &transferred, &timeout) == FAILURE) {
		return;
	}
	ZEND_FETCH_RESOURCE(res_device_handle, libusb_device_handle *, &device_handle, device_handle_id, "usb_device_handle", le_usb_device_handle);



	php_error(E_WARNING, "usb_bulk_transfer: not yet implemented"); RETURN_FALSE;

	RETURN_LONG(0);
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



	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "rlzlzl", &device_handle, &endpoint, &data, &length, &transferred, &timeout) == FAILURE) {
		return;
	}
	ZEND_FETCH_RESOURCE(res_device_handle, libusb_device_handle *, &device_handle, device_handle_id, "usb_device_handle", le_usb_device_handle);



	php_error(E_WARNING, "usb_interrupt_transfer: not yet implemented"); RETURN_FALSE;

	RETURN_LONG(0);
}
/* }}} usb_interrupt_transfer */

#endif /* HAVE_USB */


/*
 * Local variables:
 * tab-width: 4
 * c-basic-offset: 4
 * End:
 * vim600: noet sw=4 ts=4 fdm=marker
 * vim<600: noet sw=4 ts=4
 */
