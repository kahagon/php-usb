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

#ifndef PHP_USB_H
#define PHP_USB_H

#ifdef  __cplusplus
extern "C" {
#endif

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include <php.h>

#ifdef HAVE_USB
#define PHP_USB_VERSION "0.0.1"


#include <php_ini.h>
#include <SAPI.h>
#include <ext/standard/info.h>
#include <Zend/zend_extensions.h>
#ifdef  __cplusplus
} // extern "C" 
#endif
#include <libusb.h>
#ifdef  __cplusplus
extern "C" {
#endif

extern zend_module_entry usb_module_entry;
#define phpext_usb_ptr &usb_module_entry

#ifdef PHP_WIN32
#define PHP_USB_API __declspec(dllexport)
#else
#define PHP_USB_API
#endif

PHP_MINIT_FUNCTION(usb);
PHP_MSHUTDOWN_FUNCTION(usb);
PHP_RINIT_FUNCTION(usb);
PHP_RSHUTDOWN_FUNCTION(usb);
PHP_MINFO_FUNCTION(usb);

#ifdef ZTS
#include "TSRM.h"
#endif

#define FREE_RESOURCE(resource) zend_list_delete(Z_LVAL_P(resource))

#define PROP_GET_LONG(name)    Z_LVAL_P(zend_read_property(_this_ce, _this_zval, #name, strlen(#name), 1 TSRMLS_CC))
#define PROP_SET_LONG(name, l) zend_update_property_long(_this_ce, _this_zval, #name, strlen(#name), l TSRMLS_CC)

#define PROP_GET_DOUBLE(name)    Z_DVAL_P(zend_read_property(_this_ce, _this_zval, #name, strlen(#name), 1 TSRMLS_CC))
#define PROP_SET_DOUBLE(name, d) zend_update_property_double(_this_ce, _this_zval, #name, strlen(#name), d TSRMLS_CC)

#define PROP_GET_STRING(name)    Z_STRVAL_P(zend_read_property(_this_ce, _this_zval, #name, strlen(#name), 1 TSRMLS_CC))
#define PROP_GET_STRLEN(name)    Z_STRLEN_P(zend_read_property(_this_ce, _this_zval, #name, strlen(#name), 1 TSRMLS_CC))
#define PROP_SET_STRING(name, s) zend_update_property_string(_this_ce, _this_zval, #name, strlen(#name), s TSRMLS_CC)
#define PROP_SET_STRINGL(name, s, l) zend_update_property_stringl(_this_ce, _this_zval, #name, strlen(#name), s, l TSRMLS_CC)


PHP_FUNCTION(usb_init);
#if (PHP_MAJOR_VERSION >= 5)
ZEND_BEGIN_ARG_INFO_EX(usb_init_arg_info, ZEND_SEND_BY_VAL, ZEND_RETURN_VALUE, 1)
  ZEND_ARG_INFO(1, context)
ZEND_END_ARG_INFO()
#else /* PHP 4.x */
#define usb_init_arg_info NULL
#endif

PHP_FUNCTION(usb_exit);
#if (PHP_MAJOR_VERSION >= 5)
ZEND_BEGIN_ARG_INFO_EX(usb_exit_arg_info, ZEND_SEND_BY_VAL, ZEND_RETURN_VALUE, 1)
  ZEND_ARG_INFO(0, context)
ZEND_END_ARG_INFO()
#else /* PHP 4.x */
#define usb_exit_arg_info NULL
#endif

PHP_FUNCTION(usb_get_device_list);
#if (PHP_MAJOR_VERSION >= 5)
ZEND_BEGIN_ARG_INFO_EX(usb_get_device_list_arg_info, ZEND_SEND_BY_VAL, ZEND_RETURN_VALUE, 2)
  ZEND_ARG_INFO(0, context)
  ZEND_ARG_INFO(1, device_list)
ZEND_END_ARG_INFO()
#else /* PHP 4.x */
#define usb_get_device_list_arg_info NULL
#endif

PHP_FUNCTION(usb_free_device_list);
#if (PHP_MAJOR_VERSION >= 5)
ZEND_BEGIN_ARG_INFO_EX(usb_free_device_list_arg_info, ZEND_SEND_BY_VAL, ZEND_RETURN_VALUE, 1)
#if (PHP_MINOR_VERSION > 0)
  ZEND_ARG_ARRAY_INFO(0, device_list, 1)
#else
  ZEND_ARG_INFO(0, device_list)
#endif
ZEND_END_ARG_INFO()
#else /* PHP 4.x */
#define usb_free_device_list_arg_info NULL
#endif

PHP_FUNCTION(usb_open);
#if (PHP_MAJOR_VERSION >= 5)
ZEND_BEGIN_ARG_INFO_EX(usb_open_arg_info, ZEND_SEND_BY_VAL, ZEND_RETURN_VALUE, 2)
  ZEND_ARG_INFO(0, device)
  ZEND_ARG_INFO(1, device_handle)
ZEND_END_ARG_INFO()
#else /* PHP 4.x */
#define usb_open_arg_info NULL
#endif

PHP_FUNCTION(usb_close);
#if (PHP_MAJOR_VERSION >= 5)
ZEND_BEGIN_ARG_INFO_EX(usb_close_arg_info, ZEND_SEND_BY_VAL, ZEND_RETURN_VALUE, 1)
  ZEND_ARG_INFO(0, device_handle)
ZEND_END_ARG_INFO()
#else /* PHP 4.x */
#define usb_close_arg_info NULL
#endif

PHP_FUNCTION(usb_get_bus_number);
#if (PHP_MAJOR_VERSION >= 5)
ZEND_BEGIN_ARG_INFO_EX(usb_get_bus_number_arg_info, ZEND_SEND_BY_VAL, ZEND_RETURN_VALUE, 1)
  ZEND_ARG_INFO(0, device)
ZEND_END_ARG_INFO()
#else /* PHP 4.x */
#define usb_get_bus_number_arg_info NULL
#endif

PHP_FUNCTION(usb_get_device_address);
#if (PHP_MAJOR_VERSION >= 5)
ZEND_BEGIN_ARG_INFO_EX(usb_get_device_address_arg_info, ZEND_SEND_BY_VAL, ZEND_RETURN_VALUE, 1)
  ZEND_ARG_INFO(0, device)
ZEND_END_ARG_INFO()
#else /* PHP 4.x */
#define usb_get_device_address_arg_info NULL
#endif

PHP_FUNCTION(usb_get_device_speed);
#if (PHP_MAJOR_VERSION >= 5)
ZEND_BEGIN_ARG_INFO_EX(usb_get_device_speed_arg_info, ZEND_SEND_BY_VAL, ZEND_RETURN_VALUE, 1)
  ZEND_ARG_INFO(0, device)
ZEND_END_ARG_INFO()
#else /* PHP 4.x */
#define usb_get_device_speed_arg_info NULL
#endif

PHP_FUNCTION(usb_get_max_packet_size);
#if (PHP_MAJOR_VERSION >= 5)
ZEND_BEGIN_ARG_INFO_EX(usb_get_max_packet_size_arg_info, ZEND_SEND_BY_VAL, ZEND_RETURN_VALUE, 2)
  ZEND_ARG_INFO(0, device)
  ZEND_ARG_INFO(0, endpoint)
ZEND_END_ARG_INFO()
#else /* PHP 4.x */
#define usb_get_max_packet_size_arg_info NULL
#endif

PHP_FUNCTION(usb_get_max_iso_packet_size);
#if (PHP_MAJOR_VERSION >= 5)
ZEND_BEGIN_ARG_INFO_EX(usb_get_max_iso_packet_size_arg_info, ZEND_SEND_BY_VAL, ZEND_RETURN_VALUE, 2)
  ZEND_ARG_INFO(0, device)
  ZEND_ARG_INFO(0, endpoint)
ZEND_END_ARG_INFO()
#else /* PHP 4.x */
#define usb_get_max_iso_packet_size_arg_info NULL
#endif

PHP_FUNCTION(usb_ref_device);
#if (PHP_MAJOR_VERSION >= 5)
ZEND_BEGIN_ARG_INFO_EX(usb_ref_device_arg_info, ZEND_SEND_BY_VAL, ZEND_RETURN_VALUE, 1)
  ZEND_ARG_INFO(0, device)
ZEND_END_ARG_INFO()
#else /* PHP 4.x */
#define usb_ref_device_arg_info NULL
#endif

PHP_FUNCTION(usb_unref_device);
#if (PHP_MAJOR_VERSION >= 5)
ZEND_BEGIN_ARG_INFO_EX(usb_unref_device_arg_info, ZEND_SEND_BY_VAL, ZEND_RETURN_VALUE, 1)
  ZEND_ARG_INFO(0, device)
ZEND_END_ARG_INFO()
#else /* PHP 4.x */
#define usb_unref_device_arg_info NULL
#endif

PHP_FUNCTION(usb_open_device_with_vid_pid);
#if (PHP_MAJOR_VERSION >= 5)
ZEND_BEGIN_ARG_INFO_EX(usb_open_device_with_vid_pid_arg_info, ZEND_SEND_BY_VAL, ZEND_RETURN_VALUE, 3)
  ZEND_ARG_INFO(0, context)
  ZEND_ARG_INFO(0, vendor_id)
  ZEND_ARG_INFO(0, product_id)
ZEND_END_ARG_INFO()
#else /* PHP 4.x */
#define usb_open_device_with_vid_pid_arg_info NULL
#endif

PHP_FUNCTION(usb_get_device);
#if (PHP_MAJOR_VERSION >= 5)
ZEND_BEGIN_ARG_INFO_EX(usb_get_device_arg_info, ZEND_SEND_BY_VAL, ZEND_RETURN_VALUE, 1)
  ZEND_ARG_INFO(0, device_handle)
ZEND_END_ARG_INFO()
#else /* PHP 4.x */
#define usb_get_device_arg_info NULL
#endif

PHP_FUNCTION(usb_get_configuration);
#if (PHP_MAJOR_VERSION >= 5)
ZEND_BEGIN_ARG_INFO_EX(usb_get_configuration_arg_info, ZEND_SEND_BY_VAL, ZEND_RETURN_VALUE, 2)
  ZEND_ARG_INFO(0, device_handle)
  ZEND_ARG_INFO(1, config)
ZEND_END_ARG_INFO()
#else /* PHP 4.x */
#define usb_get_configuration_arg_info NULL
#endif

PHP_FUNCTION(usb_set_configuration);
#if (PHP_MAJOR_VERSION >= 5)
ZEND_BEGIN_ARG_INFO_EX(usb_set_configuration_arg_info, ZEND_SEND_BY_VAL, ZEND_RETURN_VALUE, 2)
  ZEND_ARG_INFO(0, device_handle)
  ZEND_ARG_INFO(0, configuration)
ZEND_END_ARG_INFO()
#else /* PHP 4.x */
#define usb_set_configuration_arg_info NULL
#endif

PHP_FUNCTION(usb_claim_interface);
#if (PHP_MAJOR_VERSION >= 5)
ZEND_BEGIN_ARG_INFO_EX(usb_claim_interface_arg_info, ZEND_SEND_BY_VAL, ZEND_RETURN_VALUE, 2)
  ZEND_ARG_INFO(0, device_handle)
  ZEND_ARG_INFO(0, interface_number)
ZEND_END_ARG_INFO()
#else /* PHP 4.x */
#define usb_claim_interface_arg_info NULL
#endif

PHP_FUNCTION(usb_release_interface);
#if (PHP_MAJOR_VERSION >= 5)
ZEND_BEGIN_ARG_INFO_EX(usb_release_interface_arg_info, ZEND_SEND_BY_VAL, ZEND_RETURN_VALUE, 2)
  ZEND_ARG_INFO(0, device_handle)
  ZEND_ARG_INFO(0, interface_number)
ZEND_END_ARG_INFO()
#else /* PHP 4.x */
#define usb_release_interface_arg_info NULL
#endif

PHP_FUNCTION(usb_set_interface_alt_setting);
#if (PHP_MAJOR_VERSION >= 5)
ZEND_BEGIN_ARG_INFO_EX(usb_set_interface_alt_setting_arg_info, ZEND_SEND_BY_VAL, ZEND_RETURN_VALUE, 3)
  ZEND_ARG_INFO(0, device_handle)
  ZEND_ARG_INFO(0, interface_number)
  ZEND_ARG_INFO(0, alternate_setting)
ZEND_END_ARG_INFO()
#else /* PHP 4.x */
#define usb_set_interface_alt_setting_arg_info NULL
#endif

PHP_FUNCTION(usb_clear_halt);
#if (PHP_MAJOR_VERSION >= 5)
ZEND_BEGIN_ARG_INFO_EX(usb_clear_halt_arg_info, ZEND_SEND_BY_VAL, ZEND_RETURN_VALUE, 2)
  ZEND_ARG_INFO(0, device_handle)
  ZEND_ARG_INFO(0, endpoint)
ZEND_END_ARG_INFO()
#else /* PHP 4.x */
#define usb_clear_halt_arg_info NULL
#endif

PHP_FUNCTION(usb_reset_device);
#if (PHP_MAJOR_VERSION >= 5)
ZEND_BEGIN_ARG_INFO_EX(usb_reset_device_arg_info, ZEND_SEND_BY_VAL, ZEND_RETURN_VALUE, 1)
  ZEND_ARG_INFO(0, device_handle)
ZEND_END_ARG_INFO()
#else /* PHP 4.x */
#define usb_reset_device_arg_info NULL
#endif

PHP_FUNCTION(usb_kernel_driver_active);
#if (PHP_MAJOR_VERSION >= 5)
ZEND_BEGIN_ARG_INFO_EX(usb_kernel_driver_active_arg_info, ZEND_SEND_BY_VAL, ZEND_RETURN_VALUE, 2)
  ZEND_ARG_INFO(0, device_handle)
  ZEND_ARG_INFO(0, interface_number)
ZEND_END_ARG_INFO()
#else /* PHP 4.x */
#define usb_kernel_driver_active_arg_info NULL
#endif

PHP_FUNCTION(usb_detach_kernel_driver);
#if (PHP_MAJOR_VERSION >= 5)
ZEND_BEGIN_ARG_INFO_EX(usb_detach_kernel_driver_arg_info, ZEND_SEND_BY_VAL, ZEND_RETURN_VALUE, 2)
  ZEND_ARG_INFO(0, device_handle)
  ZEND_ARG_INFO(0, interface_number)
ZEND_END_ARG_INFO()
#else /* PHP 4.x */
#define usb_detach_kernel_driver_arg_info NULL
#endif

PHP_FUNCTION(usb_attach_kernel_driver);
#if (PHP_MAJOR_VERSION >= 5)
ZEND_BEGIN_ARG_INFO_EX(usb_attach_kernel_driver_arg_info, ZEND_SEND_BY_VAL, ZEND_RETURN_VALUE, 2)
  ZEND_ARG_INFO(0, device_handle)
  ZEND_ARG_INFO(0, interface_number)
ZEND_END_ARG_INFO()
#else /* PHP 4.x */
#define usb_attach_kernel_driver_arg_info NULL
#endif

PHP_FUNCTION(usb_has_capability);
#if (PHP_MAJOR_VERSION >= 5)
ZEND_BEGIN_ARG_INFO_EX(usb_has_capability_arg_info, ZEND_SEND_BY_VAL, ZEND_RETURN_VALUE, 1)
  ZEND_ARG_INFO(0, capability)
ZEND_END_ARG_INFO()
#else /* PHP 4.x */
#define usb_has_capability_arg_info NULL
#endif

PHP_FUNCTION(usb_error_name);
#if (PHP_MAJOR_VERSION >= 5)
ZEND_BEGIN_ARG_INFO_EX(usb_error_name_arg_info, ZEND_SEND_BY_VAL, ZEND_RETURN_VALUE, 1)
  ZEND_ARG_INFO(0, error_code)
ZEND_END_ARG_INFO()
#else /* PHP 4.x */
#define usb_error_name_arg_info NULL
#endif

PHP_FUNCTION(usb_class_name);
#if (PHP_MAJOR_VERSION >= 5)
ZEND_BEGIN_ARG_INFO_EX(usb_class_name_arg_info, ZEND_SEND_BY_VAL, ZEND_RETURN_VALUE, 1)
  ZEND_ARG_INFO(0, class_code)
ZEND_END_ARG_INFO()
#else /* PHP 4.x */
#define usb_class_name_arg_info NULL
#endif

PHP_FUNCTION(usb_get_device_descriptor);
#if (PHP_MAJOR_VERSION >= 5)
ZEND_BEGIN_ARG_INFO_EX(usb_get_device_descriptor_arg_info, ZEND_SEND_BY_VAL, ZEND_RETURN_VALUE, 2)
  ZEND_ARG_INFO(0, device)
  ZEND_ARG_INFO(1, device_descriptor)
ZEND_END_ARG_INFO()
#else /* PHP 4.x */
#define usb_get_device_descriptor_arg_info NULL
#endif

PHP_FUNCTION(usb_get_active_config_descriptor);
#if (PHP_MAJOR_VERSION >= 5)
ZEND_BEGIN_ARG_INFO_EX(usb_get_active_config_descriptor_arg_info, ZEND_SEND_BY_VAL, ZEND_RETURN_VALUE, 2)
  ZEND_ARG_INFO(0, device)
  ZEND_ARG_INFO(1, config_descriptor)
ZEND_END_ARG_INFO()
#else /* PHP 4.x */
#define usb_get_active_config_descriptor_arg_info NULL
#endif

PHP_FUNCTION(usb_get_config_descriptor);
#if (PHP_MAJOR_VERSION >= 5)
ZEND_BEGIN_ARG_INFO_EX(usb_get_config_descriptor_arg_info, ZEND_SEND_BY_VAL, ZEND_RETURN_VALUE, 3)
  ZEND_ARG_INFO(0, device)
  ZEND_ARG_INFO(0, config_index)
  ZEND_ARG_INFO(1, config_descriptor)
ZEND_END_ARG_INFO()
#else /* PHP 4.x */
#define usb_get_config_descriptor_arg_info NULL
#endif

PHP_FUNCTION(usb_get_config_descriptor_by_value);
#if (PHP_MAJOR_VERSION >= 5)
ZEND_BEGIN_ARG_INFO_EX(usb_get_config_descriptor_by_value_arg_info, ZEND_SEND_BY_VAL, ZEND_RETURN_VALUE, 3)
  ZEND_ARG_INFO(0, device)
  ZEND_ARG_INFO(0, bConfigurationValue)
  ZEND_ARG_INFO(1, config_descriptor)
ZEND_END_ARG_INFO()
#else /* PHP 4.x */
#define usb_get_config_descriptor_by_value_arg_info NULL
#endif

PHP_FUNCTION(usb_free_config_descriptor);
#if (PHP_MAJOR_VERSION >= 5)
ZEND_BEGIN_ARG_INFO_EX(usb_free_config_descriptor_arg_info, ZEND_SEND_BY_VAL, ZEND_RETURN_VALUE, 1)
  ZEND_ARG_INFO(0, config_descriptor)
ZEND_END_ARG_INFO()
#else /* PHP 4.x */
#define usb_free_config_descriptor_arg_info NULL
#endif

PHP_FUNCTION(usb_get_string_descriptor_ascii);
#if (PHP_MAJOR_VERSION >= 5)
ZEND_BEGIN_ARG_INFO_EX(usb_get_string_descriptor_ascii_arg_info, ZEND_SEND_BY_VAL, ZEND_RETURN_VALUE, 3)
  ZEND_ARG_INFO(0, device_handle)
  ZEND_ARG_INFO(0, desc_index)
  ZEND_ARG_INFO(1, data)
ZEND_END_ARG_INFO()
#else /* PHP 4.x */
#define usb_get_string_descriptor_ascii_arg_info NULL
#endif

PHP_FUNCTION(usb_get_descriptor);
#if (PHP_MAJOR_VERSION >= 5)
ZEND_BEGIN_ARG_INFO_EX(usb_get_descriptor_arg_info, ZEND_SEND_BY_VAL, ZEND_RETURN_VALUE, 4)
  ZEND_ARG_INFO(0, device_handle)
  ZEND_ARG_INFO(0, desc_type)
  ZEND_ARG_INFO(0, desc_index)
  ZEND_ARG_INFO(1, data)
ZEND_END_ARG_INFO()
#else /* PHP 4.x */
#define usb_get_descriptor_arg_info NULL
#endif

PHP_FUNCTION(usb_get_string_descriptor);
#if (PHP_MAJOR_VERSION >= 5)
ZEND_BEGIN_ARG_INFO_EX(usb_get_string_descriptor_arg_info, ZEND_SEND_BY_VAL, ZEND_RETURN_VALUE, 4)
  ZEND_ARG_INFO(0, device_handle)
  ZEND_ARG_INFO(0, desc_index)
  ZEND_ARG_INFO(0, langid)
  ZEND_ARG_INFO(1, data)
ZEND_END_ARG_INFO()
#else /* PHP 4.x */
#define usb_get_string_descriptor_arg_info NULL
#endif

PHP_FUNCTION(usb_control_transfer);
#if (PHP_MAJOR_VERSION >= 5)
ZEND_BEGIN_ARG_INFO_EX(usb_control_transfer_arg_info, ZEND_SEND_BY_VAL, ZEND_RETURN_VALUE, 8)
  ZEND_ARG_INFO(0, device_handle)
  ZEND_ARG_INFO(0, bmRequestType)
  ZEND_ARG_INFO(0, bRequest)
  ZEND_ARG_INFO(0, wValue)
  ZEND_ARG_INFO(0, wIndex)
  ZEND_ARG_INFO(1, data)
  ZEND_ARG_INFO(0, wLength)
  ZEND_ARG_INFO(0, timeout)
ZEND_END_ARG_INFO()
#else /* PHP 4.x */
#define usb_control_transfer_arg_info NULL
#endif

PHP_FUNCTION(usb_bulk_transfer);
#if (PHP_MAJOR_VERSION >= 5)
ZEND_BEGIN_ARG_INFO_EX(usb_bulk_transfer_arg_info, ZEND_SEND_BY_VAL, ZEND_RETURN_VALUE, 6)
  ZEND_ARG_INFO(0, device_handle)
  ZEND_ARG_INFO(0, endpoint)
  ZEND_ARG_INFO(1, data)
  ZEND_ARG_INFO(0, length)
  ZEND_ARG_INFO(1, transferred)
  ZEND_ARG_INFO(0, timeout)
ZEND_END_ARG_INFO()
#else /* PHP 4.x */
#define usb_bulk_transfer_arg_info NULL
#endif

PHP_FUNCTION(usb_interrupt_transfer);
#if (PHP_MAJOR_VERSION >= 5)
ZEND_BEGIN_ARG_INFO_EX(usb_interrupt_transfer_arg_info, ZEND_SEND_BY_VAL, ZEND_RETURN_VALUE, 6)
  ZEND_ARG_INFO(0, device_handle)
  ZEND_ARG_INFO(0, endpoint)
  ZEND_ARG_INFO(1, data)
  ZEND_ARG_INFO(0, length)
  ZEND_ARG_INFO(1, transferred)
  ZEND_ARG_INFO(0, timeout)
ZEND_END_ARG_INFO()
#else /* PHP 4.x */
#define usb_interrupt_transfer_arg_info NULL
#endif

#ifdef  __cplusplus
} // extern "C" 
#endif

#endif /* PHP_HAVE_USB */

#endif /* PHP_USB_H */


/*
 * Local variables:
 * tab-width: 4
 * c-basic-offset: 4
 * End:
 * vim600: noet sw=4 ts=4 fdm=marker
 * vim<600: noet sw=4 ts=4
 */
