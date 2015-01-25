#include "php_usb.h"

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
