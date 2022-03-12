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
   | Authors: Kenichi Ahagon <kahagon@tamana.dev>                         |
   +----------------------------------------------------------------------+
*/

/* $ Id: $ */ 

#include "php_usb.h"

#if HAVE_USB

#if PHP_VERSION_ID < 70000
int phpusb_register_resource(zval *rsrc_result, void *rsrc_pointer, int rsrc_type TSRMLS_DC) {
	ZVAL_RESOURCE(rsrc_result, rsrc_pointer);
	return ZEND_REGISTER_RESOURCE(rsrc_result, rsrc_pointer, rsrc_type);
}
#else
zend_resource * phpusb_register_resource(zval* rsrc_result, void *rsrc_pointer, int rsrc_type TSRMLS_DC) {
	zend_resource * r = zend_register_resource(rsrc_pointer, rsrc_type);
	ZVAL_RES(rsrc_result, r);
	return Z_RES_P(rsrc_result);
}
#endif

/* {{{ Resource destructors */
int le_usb_context;
void usb_context_dtor(phpusb_resource *rsrc TSRMLS_DC)
{
	libusb_context * resource = (libusb_context *)(rsrc->ptr);

	do {
		/* call libusb_exit() here, causes dead-lock or double free. */
	} while (0);
}

int le_usb_device;
void usb_device_dtor(phpusb_resource *rsrc TSRMLS_DC)
{
	libusb_device * resource = (libusb_device *)(rsrc->ptr);

	do {
	} while (0);
}

int le_usb_device_handle;
void usb_device_handle_dtor(phpusb_resource *rsrc TSRMLS_DC)
{
	libusb_device_handle * resource = (libusb_device_handle *)(rsrc->ptr);

	do {
	} while (0);
}

int le_usb_device_descriptor;
void usb_device_descriptor_dtor(phpusb_resource *rsrc TSRMLS_DC)
{
	struct libusb_device_descriptor * resource = (struct libusb_device_descriptor *)(rsrc->ptr);

	do {
	} while (0);
}

int le_usb_endpoint_descriptor;
void usb_endpoint_descriptor_dtor(phpusb_resource *rsrc TSRMLS_DC)
{
	struct libusb_endpoint_descriptor * resource = (struct libusb_endpoint_descriptor *)(rsrc->ptr);

	do {
	} while (0);
}

int le_usb_interface_descriptor;
void usb_interface_descriptor_dtor(phpusb_resource *rsrc TSRMLS_DC)
{
	struct libusb_interface_descriptor * resource = (struct libusb_interface_descriptor *)(rsrc->ptr);

	do {
	} while (0);
}

int le_usb_interface;
void usb_interface_dtor(phpusb_resource *rsrc TSRMLS_DC)
{
	struct libusb_interface * resource = (struct libusb_interface *)(rsrc->ptr);

	do {
	} while (0);
}

int le_usb_config_descriptor;
void usb_config_descriptor_dtor(phpusb_resource *rsrc TSRMLS_DC)
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
//	PHP_FE(usb_free_device_list, usb_free_device_list_arg_info)
//	PHP_FE(usb_open            , usb_open_arg_info)
//	PHP_FE(usb_close           , usb_close_arg_info)
//	PHP_FE(usb_get_bus_number  , usb_get_bus_number_arg_info)
//	PHP_FE(usb_get_device_address, usb_get_device_address_arg_info)
//	PHP_FE(usb_get_device_speed, usb_get_device_speed_arg_info)
//	PHP_FE(usb_get_max_packet_size, usb_get_max_packet_size_arg_info)
//	PHP_FE(usb_get_max_iso_packet_size, usb_get_max_iso_packet_size_arg_info)
//	PHP_FE(usb_ref_device      , usb_ref_device_arg_info)
//	PHP_FE(usb_unref_device    , usb_unref_device_arg_info)
//	PHP_FE(usb_open_device_with_vid_pid, usb_open_device_with_vid_pid_arg_info)
//	PHP_FE(usb_get_device      , usb_get_device_arg_info)
//	PHP_FE(usb_get_configuration, usb_get_configuration_arg_info)
//	PHP_FE(usb_set_configuration, usb_set_configuration_arg_info)
//	PHP_FE(usb_claim_interface , usb_claim_interface_arg_info)
//	PHP_FE(usb_release_interface, usb_release_interface_arg_info)
//	PHP_FE(usb_set_interface_alt_setting, usb_set_interface_alt_setting_arg_info)
//	PHP_FE(usb_clear_halt      , usb_clear_halt_arg_info)
//	PHP_FE(usb_reset_device    , usb_reset_device_arg_info)
//	PHP_FE(usb_kernel_driver_active, usb_kernel_driver_active_arg_info)
//	PHP_FE(usb_detach_kernel_driver, usb_detach_kernel_driver_arg_info)
//	PHP_FE(usb_attach_kernel_driver, usb_attach_kernel_driver_arg_info)
//	PHP_FE(usb_has_capability  , usb_has_capability_arg_info)
//	PHP_FE(usb_error_name      , usb_error_name_arg_info)
//	PHP_FE(usb_class_name      , usb_class_name_arg_info)
//	PHP_FE(usb_descriptor_type_name, usb_descriptor_type_name_arg_info)
	PHP_FE(usb_get_device_descriptor, usb_get_device_descriptor_arg_info)
//	PHP_FE(usb_get_active_config_descriptor, usb_get_active_config_descriptor_arg_info)
//	PHP_FE(usb_get_config_descriptor, usb_get_config_descriptor_arg_info)
//	PHP_FE(usb_get_config_descriptor_by_value, usb_get_config_descriptor_by_value_arg_info)
//	PHP_FE(usb_free_config_descriptor, usb_free_config_descriptor_arg_info)
//	PHP_FE(usb_get_string_descriptor_ascii, usb_get_string_descriptor_ascii_arg_info)
//	PHP_FE(usb_get_descriptor  , usb_get_descriptor_arg_info)
//	PHP_FE(usb_get_string_descriptor, usb_get_string_descriptor_arg_info)
//	PHP_FE(usb_control_transfer, usb_control_transfer_arg_info)
//	PHP_FE(usb_bulk_transfer   , usb_bulk_transfer_arg_info)
//	PHP_FE(usb_interrupt_transfer, usb_interrupt_transfer_arg_info)
	{ NULL, NULL, NULL }
};
/* }}} */

static zend_class_entry * Descriptor_ce_ptr = NULL;
static zend_class_entry * DeviceDescriptor_ce_ptr = NULL;
static zend_class_entry * ConfigDescriptor_ce_ptr = NULL;
static zend_class_entry * InterfaceAltsetting_ce_ptr = NULL;
static zend_class_entry * InterfaceDescriptor_ce_ptr = NULL;
static zend_class_entry * EndpointDescriptor_ce_ptr = NULL;

void store_device_descriptor_to_zval(const struct libusb_device_descriptor *res_device_descriptor, zval * device_descriptor, INTERNAL_FUNCTION_PARAMETERS) {
	object_init_ex(device_descriptor, DeviceDescriptor_ce_ptr);
	zend_update_property_long(DeviceDescriptor_ce_ptr, device_descriptor, PROP_NAME("bLength"), res_device_descriptor->bLength TSRMLS_CC);
	zend_update_property_long(DeviceDescriptor_ce_ptr, device_descriptor, PROP_NAME("bDescriptorType"), res_device_descriptor->bDescriptorType TSRMLS_CC);
	zend_update_property_long(DeviceDescriptor_ce_ptr, device_descriptor, PROP_NAME("bcdUSB"), res_device_descriptor->bcdUSB TSRMLS_CC);
	zend_update_property_long(DeviceDescriptor_ce_ptr, device_descriptor, PROP_NAME("bDeviceClass"), res_device_descriptor->bDeviceClass TSRMLS_CC);
	zend_update_property_long(DeviceDescriptor_ce_ptr, device_descriptor, PROP_NAME("bDeviceSubClass"), res_device_descriptor->bDeviceSubClass TSRMLS_CC);
	zend_update_property_long(DeviceDescriptor_ce_ptr, device_descriptor, PROP_NAME("bDeviceProtocol"), res_device_descriptor->bDeviceProtocol TSRMLS_CC);
	zend_update_property_long(DeviceDescriptor_ce_ptr, device_descriptor, PROP_NAME("bMaxPacketSize0"), res_device_descriptor->bMaxPacketSize0 TSRMLS_CC);
	zend_update_property_long(DeviceDescriptor_ce_ptr, device_descriptor, PROP_NAME("idVendor"), res_device_descriptor->idVendor TSRMLS_CC);
	zend_update_property_long(DeviceDescriptor_ce_ptr, device_descriptor, PROP_NAME("idProduct"), res_device_descriptor->idProduct TSRMLS_CC);
	zend_update_property_long(DeviceDescriptor_ce_ptr, device_descriptor, PROP_NAME("bcdDevice"), res_device_descriptor->bcdDevice TSRMLS_CC);
	zend_update_property_long(DeviceDescriptor_ce_ptr, device_descriptor, PROP_NAME("iManufacturer"), res_device_descriptor->iManufacturer TSRMLS_CC);
	zend_update_property_long(DeviceDescriptor_ce_ptr, device_descriptor, PROP_NAME("iProduct"), res_device_descriptor->iProduct TSRMLS_CC);
	zend_update_property_long(DeviceDescriptor_ce_ptr, device_descriptor, PROP_NAME("iSerialNumber"), res_device_descriptor->iSerialNumber TSRMLS_CC);
	zend_update_property_long(DeviceDescriptor_ce_ptr, device_descriptor, PROP_NAME("bNumConfigurations"), res_device_descriptor->bNumConfigurations TSRMLS_CC);
}

#if 0
void store_config_descriptor_to_zval(const struct libusb_config_descriptor *res_config_descriptor, zval * config_descriptor, INTERNAL_FUNCTION_PARAMETERS) {
	int i = 0;
	zval *interface_array = NULL;
	ALLOC_INIT_ZVAL(interface_array);
	array_init(interface_array);

	object_init_ex(config_descriptor, ConfigDescriptor_ce_ptr);
	zend_update_property_long(ConfigDescriptor_ce_ptr, config_descriptor, PROP_NAME("bLength"), res_config_descriptor->bLength TSRMLS_CC);
	zend_update_property_long(ConfigDescriptor_ce_ptr, config_descriptor, PROP_NAME("bDescriptorType"), res_config_descriptor->bDescriptorType TSRMLS_CC);
	zend_update_property_long(ConfigDescriptor_ce_ptr, config_descriptor, PROP_NAME("wTotalLength"), res_config_descriptor->wTotalLength TSRMLS_CC);
	zend_update_property_long(ConfigDescriptor_ce_ptr, config_descriptor, PROP_NAME("bNumInterfaces"), res_config_descriptor->bNumInterfaces TSRMLS_CC);
	zend_update_property_long(ConfigDescriptor_ce_ptr, config_descriptor, PROP_NAME("bConfigurationValue"), res_config_descriptor->bConfigurationValue TSRMLS_CC);
	zend_update_property_long(ConfigDescriptor_ce_ptr, config_descriptor, PROP_NAME("iConfiguration"), res_config_descriptor->iConfiguration TSRMLS_CC);
	zend_update_property_long(ConfigDescriptor_ce_ptr, config_descriptor, PROP_NAME("bmAttributes"), res_config_descriptor->bmAttributes TSRMLS_CC);
	zend_update_property_long(ConfigDescriptor_ce_ptr, config_descriptor, PROP_NAME("MaxPower"), res_config_descriptor->MaxPower TSRMLS_CC);
	for (i = 0; i < res_config_descriptor->bNumInterfaces; i++) {
		const struct libusb_interface res_interface = res_config_descriptor->interface[i];
		zval *interface;
		zval *altsetting;
		int j = 0;
		
		//store_interface_to_zval(res_interface, interface, INTERNAL_FUNCTION_PARAM_PASSTHRU);
		//*
		ALLOC_INIT_ZVAL(interface);
		object_init_ex(interface, InterfaceAltsetting_ce_ptr);

		ALLOC_INIT_ZVAL(altsetting);
		array_init(altsetting);
		
		for (j = 0; j < res_interface.num_altsetting; j++) {
			const struct libusb_interface_descriptor res_interface_descriptor = res_interface.altsetting[j];
			zval *interface_descriptor = NULL;
			zval *endpoint_array = NULL;
			int k = 0;

			ALLOC_INIT_ZVAL(interface_descriptor);
			object_init_ex(interface_descriptor, InterfaceDescriptor_ce_ptr);

			ALLOC_INIT_ZVAL(endpoint_array);
			array_init(endpoint_array);

			zend_update_property_long(InterfaceDescriptor_ce_ptr, interface_descriptor, PROP_NAME("bLength"), res_interface_descriptor.bLength TSRMLS_CC);
			zend_update_property_long(InterfaceDescriptor_ce_ptr, interface_descriptor, PROP_NAME("bDescriptorType"), res_interface_descriptor.bDescriptorType TSRMLS_CC);
			zend_update_property_long(InterfaceDescriptor_ce_ptr, interface_descriptor, PROP_NAME("bInterfaceNumber"), res_interface_descriptor.bInterfaceNumber TSRMLS_CC);
			zend_update_property_long(InterfaceDescriptor_ce_ptr, interface_descriptor, PROP_NAME("bAlternateSetting"), res_interface_descriptor.bAlternateSetting TSRMLS_CC);
			zend_update_property_long(InterfaceDescriptor_ce_ptr, interface_descriptor, PROP_NAME("bNumEndpoints"), res_interface_descriptor.bNumEndpoints TSRMLS_CC);
			zend_update_property_long(InterfaceDescriptor_ce_ptr, interface_descriptor, PROP_NAME("bInterfaceClass"), res_interface_descriptor.bInterfaceClass TSRMLS_CC);
			zend_update_property_long(InterfaceDescriptor_ce_ptr, interface_descriptor, PROP_NAME("bInterfaceSubClass"), res_interface_descriptor.bInterfaceSubClass TSRMLS_CC);
			zend_update_property_long(InterfaceDescriptor_ce_ptr, interface_descriptor, PROP_NAME("bInterfaceProtocol"), res_interface_descriptor.bInterfaceProtocol TSRMLS_CC);
			zend_update_property_long(InterfaceDescriptor_ce_ptr, interface_descriptor, PROP_NAME("iInterface"), res_interface_descriptor.iInterface TSRMLS_CC);

			for (k = 0; k < res_interface_descriptor.bNumEndpoints; k++) {
				const struct libusb_endpoint_descriptor res_endpoint_descriptor = res_interface_descriptor.endpoint[k];
				zval *endpoint_descriptor = NULL;
				ALLOC_INIT_ZVAL(endpoint_descriptor);
				object_init_ex(endpoint_descriptor, EndpointDescriptor_ce_ptr);

				zend_update_property_long(EndpointDescriptor_ce_ptr, endpoint_descriptor, PROP_NAME("bLength"), res_endpoint_descriptor.bLength TSRMLS_CC);
				zend_update_property_long(EndpointDescriptor_ce_ptr, endpoint_descriptor, PROP_NAME("bDescriptorType"), res_endpoint_descriptor.bDescriptorType TSRMLS_CC);
				zend_update_property_long(EndpointDescriptor_ce_ptr, endpoint_descriptor, PROP_NAME("bEndpointAddress"), res_endpoint_descriptor.bEndpointAddress TSRMLS_CC);
				zend_update_property_long(EndpointDescriptor_ce_ptr, endpoint_descriptor, PROP_NAME("bmAttributes"), res_endpoint_descriptor.bmAttributes TSRMLS_CC);
				zend_update_property_long(EndpointDescriptor_ce_ptr, endpoint_descriptor, PROP_NAME("wMaxPacketSize"), res_endpoint_descriptor.wMaxPacketSize TSRMLS_CC);
				zend_update_property_long(EndpointDescriptor_ce_ptr, endpoint_descriptor, PROP_NAME("bInterval"), res_endpoint_descriptor.bInterval TSRMLS_CC);
				zend_update_property_long(EndpointDescriptor_ce_ptr, endpoint_descriptor, PROP_NAME("bRefresh"), res_endpoint_descriptor.bRefresh TSRMLS_CC);
				zend_update_property_long(EndpointDescriptor_ce_ptr, endpoint_descriptor, PROP_NAME("bSynchAddress"), res_endpoint_descriptor.bSynchAddress TSRMLS_CC);
				zend_update_property_stringl(EndpointDescriptor_ce_ptr, endpoint_descriptor, PROP_NAME("extra"), res_endpoint_descriptor.extra, res_endpoint_descriptor.extra_length TSRMLS_CC);
				zend_update_property_long(EndpointDescriptor_ce_ptr, endpoint_descriptor, PROP_NAME("extra_length"), res_endpoint_descriptor.extra_length TSRMLS_CC);

				add_next_index_zval(endpoint_array, endpoint_descriptor);
			}

			zend_update_property(InterfaceDescriptor_ce_ptr, interface_descriptor, PROP_NAME("endpoint"), endpoint_array TSRMLS_CC);
			zend_update_property_stringl(InterfaceDescriptor_ce_ptr, interface_descriptor, PROP_NAME("extra"), res_interface_descriptor.extra, res_interface_descriptor.extra_length TSRMLS_CC);
			zend_update_property_long(InterfaceDescriptor_ce_ptr, interface_descriptor, PROP_NAME("extra_length"), res_interface_descriptor.extra_length TSRMLS_CC);

			add_next_index_zval(altsetting, interface_descriptor);
		}
		zend_update_property(InterfaceAltsetting_ce_ptr, interface, PROP_NAME("altsetting"), altsetting TSRMLS_CC);
		zend_update_property_long(InterfaceAltsetting_ce_ptr, interface, PROP_NAME("num_altsetting"), res_interface.num_altsetting TSRMLS_CC);
		//*/
		add_next_index_zval(interface_array, interface);
	}
	zend_update_property(ConfigDescriptor_ce_ptr, config_descriptor, PROP_NAME("interface"), interface_array TSRMLS_CC);
	zend_update_property_stringl(ConfigDescriptor_ce_ptr, config_descriptor, PROP_NAME("extra"), res_config_descriptor->extra, res_config_descriptor->extra_length TSRMLS_CC);
	zend_update_property_long(ConfigDescriptor_ce_ptr, config_descriptor, PROP_NAME("extra_length"), res_config_descriptor->extra_length TSRMLS_CC);
}
#endif

/* {{{ Class Descriptor */
static zend_function_entry Descriptor_methods[] = {
  { NULL, NULL, NULL }
};

static void class_init_Descriptor(TSRMLS_D)
{
  zend_class_entry ce;
  INIT_NS_CLASS_ENTRY(ce, USB_NS, "Descriptor", Descriptor_methods);
  Descriptor_ce_ptr = zend_register_internal_class(&ce TSRMLS_CC);
  zend_declare_property_long(Descriptor_ce_ptr, PROP_NAME("bLength"), 0, ZEND_ACC_PUBLIC TSRMLS_CC);
  zend_declare_property_long(Descriptor_ce_ptr, PROP_NAME("bDescriptorType"), 0, ZEND_ACC_PUBLIC TSRMLS_CC);
}

/* }}} */


/* {{{ Class DeviceDescriptor */
static zend_function_entry DeviceDescriptor_methods[] = {
  { NULL, NULL, NULL }
};
static void class_init_DeviceDescriptor(TSRMLS_D)
{
  zend_class_entry ce;
  INIT_NS_CLASS_ENTRY(ce, USB_NS, "DeviceDescriptor", DeviceDescriptor_methods);
  DeviceDescriptor_ce_ptr = phpusb_register_internal_class_ex(&ce, Descriptor_ce_ptr, NULL TSRMLS_CC);
  zend_declare_property_long(DeviceDescriptor_ce_ptr, PROP_NAME("bcdUSB"), 0, ZEND_ACC_PUBLIC TSRMLS_CC);
  zend_declare_property_long(DeviceDescriptor_ce_ptr, PROP_NAME("bDeviceClass"), 0, ZEND_ACC_PUBLIC TSRMLS_CC);
  zend_declare_property_long(DeviceDescriptor_ce_ptr, PROP_NAME("bDeviceSubClass"), 0, ZEND_ACC_PUBLIC TSRMLS_CC);
  zend_declare_property_long(DeviceDescriptor_ce_ptr, PROP_NAME("bDeviceProtocol"), 0, ZEND_ACC_PUBLIC TSRMLS_CC);
  zend_declare_property_long(DeviceDescriptor_ce_ptr, PROP_NAME("bMaxPacketSize0"), 0, ZEND_ACC_PUBLIC TSRMLS_CC);
  zend_declare_property_long(DeviceDescriptor_ce_ptr, PROP_NAME("idVendor"), 0, ZEND_ACC_PUBLIC TSRMLS_CC);
  zend_declare_property_long(DeviceDescriptor_ce_ptr, PROP_NAME("idProduct"), 0, ZEND_ACC_PUBLIC TSRMLS_CC);
  zend_declare_property_long(DeviceDescriptor_ce_ptr, PROP_NAME("bcdDevice"), 0, ZEND_ACC_PUBLIC TSRMLS_CC);
  zend_declare_property_long(DeviceDescriptor_ce_ptr, PROP_NAME("iManufacturer"), 0, ZEND_ACC_PUBLIC TSRMLS_CC);
  zend_declare_property_long(DeviceDescriptor_ce_ptr, PROP_NAME("iProduct"), 0, ZEND_ACC_PUBLIC TSRMLS_CC);
  zend_declare_property_long(DeviceDescriptor_ce_ptr, PROP_NAME("iSerialNumber"), 0, ZEND_ACC_PUBLIC TSRMLS_CC);
  zend_declare_property_long(DeviceDescriptor_ce_ptr, PROP_NAME("bNumConfigurations"), 0, ZEND_ACC_PUBLIC TSRMLS_CC);
}
/* }}} */

/* {{{ Class ConfigDescriptor */
static zend_function_entry ConfigDescriptor_methods[] = {
  { NULL, NULL, NULL }
};
static void class_init_ConfigDescriptor(TSRMLS_D)
{
  zend_class_entry ce;
  INIT_NS_CLASS_ENTRY(ce, USB_NS, "ConfigDescriptor", ConfigDescriptor_methods);
  ConfigDescriptor_ce_ptr = phpusb_register_internal_class_ex(&ce, Descriptor_ce_ptr, NULL TSRMLS_CC);
  zend_declare_property_long(ConfigDescriptor_ce_ptr, PROP_NAME("wTotalLength"), 0, ZEND_ACC_PUBLIC TSRMLS_CC);
  zend_declare_property_long(ConfigDescriptor_ce_ptr, PROP_NAME("bNumInterfaces"), 0, ZEND_ACC_PUBLIC TSRMLS_CC);
  zend_declare_property_long(ConfigDescriptor_ce_ptr, PROP_NAME("bConfigurationValue"), 0, ZEND_ACC_PUBLIC TSRMLS_CC);
  zend_declare_property_long(ConfigDescriptor_ce_ptr, PROP_NAME("iConfiguration"), 0, ZEND_ACC_PUBLIC TSRMLS_CC);
  zend_declare_property_long(ConfigDescriptor_ce_ptr, PROP_NAME("bmAttributes"), 0, ZEND_ACC_PUBLIC TSRMLS_CC);
  zend_declare_property_long(ConfigDescriptor_ce_ptr, PROP_NAME("MaxPower"), 0, ZEND_ACC_PUBLIC TSRMLS_CC);
  zend_declare_property_null(ConfigDescriptor_ce_ptr, PROP_NAME("interface"), ZEND_ACC_PUBLIC TSRMLS_CC);
  zend_declare_property_null(ConfigDescriptor_ce_ptr, PROP_NAME("extra"), ZEND_ACC_PUBLIC TSRMLS_CC);
  zend_declare_property_long(ConfigDescriptor_ce_ptr, PROP_NAME("extra_length"), 0, ZEND_ACC_PUBLIC TSRMLS_CC);
}
/* }}} */

/* {{{ Class InterfaceArray */
static zend_function_entry InterfaceAltsetting_methods[] = {
  { NULL, NULL, NULL }
};
static void class_init_InterfaceAltsetting(TSRMLS_D)
{
  zend_class_entry ce;
  INIT_NS_CLASS_ENTRY(ce, USB_NS, "InterfaceAltsetting", InterfaceAltsetting_methods);
  InterfaceAltsetting_ce_ptr = zend_register_internal_class(&ce TSRMLS_CC);
  zend_declare_property_null(InterfaceAltsetting_ce_ptr, PROP_NAME("altsetting"), ZEND_ACC_PUBLIC TSRMLS_CC);
  zend_declare_property_long(InterfaceAltsetting_ce_ptr, PROP_NAME("num_altsetting"), 0, ZEND_ACC_PUBLIC TSRMLS_CC);
}
/* }}} */

/* {{{ Class InterfaceDescriptor */
static zend_function_entry InterfaceDescriptor_methods[] = {
  { NULL, NULL, NULL }
};
static void class_init_InterfaceDescriptor(TSRMLS_D)
{
  zend_class_entry ce;
  INIT_NS_CLASS_ENTRY(ce, USB_NS, "InterfaceDescriptor", InterfaceDescriptor_methods);
  InterfaceDescriptor_ce_ptr = phpusb_register_internal_class_ex(&ce, Descriptor_ce_ptr, NULL TSRMLS_CC);
  zend_declare_property_long(InterfaceDescriptor_ce_ptr, PROP_NAME("bInterfaceNumber"), 0, ZEND_ACC_PUBLIC TSRMLS_CC);
  zend_declare_property_long(InterfaceDescriptor_ce_ptr, PROP_NAME("bAlternateSetting"), 0, ZEND_ACC_PUBLIC TSRMLS_CC);
  zend_declare_property_long(InterfaceDescriptor_ce_ptr, PROP_NAME("bNumEndpoints"), 0, ZEND_ACC_PUBLIC TSRMLS_CC);
  zend_declare_property_long(InterfaceDescriptor_ce_ptr, PROP_NAME("bInterfaceClass"), 0, ZEND_ACC_PUBLIC TSRMLS_CC);
  zend_declare_property_long(InterfaceDescriptor_ce_ptr, PROP_NAME("bInterfaceSubClass"), 0, ZEND_ACC_PUBLIC TSRMLS_CC);
  zend_declare_property_long(InterfaceDescriptor_ce_ptr, PROP_NAME("bInterfaceProtocol"), 0, ZEND_ACC_PUBLIC TSRMLS_CC);
  zend_declare_property_long(InterfaceDescriptor_ce_ptr, PROP_NAME("iInterface"), 0, ZEND_ACC_PUBLIC TSRMLS_CC);
  zend_declare_property_null(InterfaceDescriptor_ce_ptr, PROP_NAME("endpoint"), ZEND_ACC_PUBLIC TSRMLS_CC);
  zend_declare_property_null(InterfaceDescriptor_ce_ptr, PROP_NAME("extra"), ZEND_ACC_PUBLIC TSRMLS_CC);
  zend_declare_property_long(InterfaceDescriptor_ce_ptr, PROP_NAME("extra_length"), 0, ZEND_ACC_PUBLIC TSRMLS_CC);
}
/* }}} */

/* {{{ Class EndpointDescriptor */
static zend_function_entry EndpointDescriptor_methods[] = {
  { NULL, NULL, NULL }
};
static void class_init_EndpointDescriptor(TSRMLS_D)
{
  zend_class_entry ce;
  INIT_NS_CLASS_ENTRY(ce, USB_NS, "EndpointDescriptor", EndpointDescriptor_methods);
  EndpointDescriptor_ce_ptr = phpusb_register_internal_class_ex(&ce, Descriptor_ce_ptr, NULL TSRMLS_CC);
  zend_declare_property_long(EndpointDescriptor_ce_ptr, PROP_NAME("bEndpointAddress"), 0, ZEND_ACC_PUBLIC TSRMLS_CC);
  zend_declare_property_long(EndpointDescriptor_ce_ptr, PROP_NAME("bmAttributes"), 0, ZEND_ACC_PUBLIC TSRMLS_CC);
  zend_declare_property_long(EndpointDescriptor_ce_ptr, PROP_NAME("wMaxPacketSize"), 0, ZEND_ACC_PUBLIC TSRMLS_CC);
  zend_declare_property_long(EndpointDescriptor_ce_ptr, PROP_NAME("bInterval"), 0, ZEND_ACC_PUBLIC TSRMLS_CC);
  zend_declare_property_long(EndpointDescriptor_ce_ptr, PROP_NAME("bRefresh"), 0, ZEND_ACC_PUBLIC TSRMLS_CC);
  zend_declare_property_long(EndpointDescriptor_ce_ptr, PROP_NAME("bSynchAddress"), 0, ZEND_ACC_PUBLIC TSRMLS_CC);
  zend_declare_property_null(EndpointDescriptor_ce_ptr, PROP_NAME("extra"), ZEND_ACC_PUBLIC TSRMLS_CC);
  zend_declare_property_long(EndpointDescriptor_ce_ptr, PROP_NAME("extra_length"), 0, ZEND_ACC_PUBLIC TSRMLS_CC);
}
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
#if defined(LIBUSB_API_VERSION) && (LIBUSB_API_VERSION >= 0x01000108)
	REGISTER_LONG_CONSTANT("USB_CLASS_MISCELLANEOUS", LIBUSB_CLASS_MISCELLANEOUS, CONST_PERSISTENT | CONST_CS);
#endif
	REGISTER_LONG_CONSTANT("USB_CLASS_APPLICATION", LIBUSB_CLASS_APPLICATION, CONST_PERSISTENT | CONST_CS);
	REGISTER_LONG_CONSTANT("USB_CLASS_VENDOR_SPEC", LIBUSB_CLASS_VENDOR_SPEC, CONST_PERSISTENT | CONST_CS);
	REGISTER_LONG_CONSTANT("USB_DT_DEVICE", LIBUSB_DT_DEVICE, CONST_PERSISTENT | CONST_CS);
	REGISTER_LONG_CONSTANT("USB_DT_CONFIG", LIBUSB_DT_CONFIG, CONST_PERSISTENT | CONST_CS);
	REGISTER_LONG_CONSTANT("USB_DT_STRING", LIBUSB_DT_STRING, CONST_PERSISTENT | CONST_CS);
	REGISTER_LONG_CONSTANT("USB_DT_INTERFACE", LIBUSB_DT_INTERFACE, CONST_PERSISTENT | CONST_CS);
	REGISTER_LONG_CONSTANT("USB_DT_ENDPOINT", LIBUSB_DT_ENDPOINT, CONST_PERSISTENT | CONST_CS);
	REGISTER_LONG_CONSTANT("USB_DT_BOS", LIBUSB_DT_BOS, CONST_PERSISTENT | CONST_CS);
	REGISTER_LONG_CONSTANT("USB_DT_DEVICE_CAPABILITY", LIBUSB_DT_DEVICE_CAPABILITY, CONST_PERSISTENT | CONST_CS);
	REGISTER_LONG_CONSTANT("USB_DT_HID", LIBUSB_DT_HID, CONST_PERSISTENT | CONST_CS);
	REGISTER_LONG_CONSTANT("USB_DT_REPORT", LIBUSB_DT_REPORT, CONST_PERSISTENT | CONST_CS);
	REGISTER_LONG_CONSTANT("USB_DT_PHYSICAL", LIBUSB_DT_PHYSICAL, CONST_PERSISTENT | CONST_CS);
	REGISTER_LONG_CONSTANT("USB_DT_HUB", LIBUSB_DT_HUB, CONST_PERSISTENT | CONST_CS);
	REGISTER_LONG_CONSTANT("USB_DT_SUPERSPEED_HUB", LIBUSB_DT_SUPERSPEED_HUB, CONST_PERSISTENT | CONST_CS);
	REGISTER_LONG_CONSTANT("USB_DT_SS_ENDPOINT_COMPANION", LIBUSB_DT_SS_ENDPOINT_COMPANION, CONST_PERSISTENT | CONST_CS);
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
		
	class_init_Descriptor(TSRMLS_C);
	class_init_DeviceDescriptor(TSRMLS_C);
	class_init_ConfigDescriptor(TSRMLS_C);
	class_init_InterfaceAltsetting(TSRMLS_C);
	class_init_InterfaceDescriptor(TSRMLS_C);
	class_init_EndpointDescriptor(TSRMLS_C);
		
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
	php_info_print_table_row(2, "Authors", "Kenichi Ahagon 'kahagon@tamana.dev'\n");
	php_info_print_table_end();
	/* add your stuff here */

}
/* }}} */

#endif /* HAVE_USB */


/*
 * Local variables:
 * tab-width: 4
 * c-basic-offset: 4
 * End:
 * vim600: noet sw=4 ts=4 fdm=marker
 * vim<600: noet sw=4 ts=4
 */
