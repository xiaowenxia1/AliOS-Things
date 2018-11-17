/*----------------------------------------------------------------------------*/
/*
 * Copyright (C) Bosch Connected Devices and Solutions GmbH. 
 * All Rights Reserved. Confidential.
 *
 * Distribution only to people who need to know this information in
 * order to do their job.(Need-to-know principle).
 * Distribution to persons outside the company, only if these persons
 * signed a non-disclosure agreement.
 * Electronic transmission, e.g. via electronic mail, must be made in
 * encrypted form.
 */
/*----------------------------------------------------------------------------*/

/**
 * @file
 * @brief Add a brief description here.
 *
 * @details Put here the documentation of this header file. Explain the interface exposed
 * by this header, e.g. what is the purpose of use, how to use it, etc.
 */

#ifndef XDK_COMMONINFO_H_
#define XDK_COMMONINFO_H_

#include "BCDS_Retcode.h"

/**
 * @brief BCDS_MODULE_ID for common  C module of XDK
 * @info  usage:
 *      #undef BCDS_MODULE_ID
 *      #define BCDS_MODULE_ID BCDS_SENSORS_MODULE_ID_xxx
 */
enum XDK_Common_ModuleID_E
{
    XDK_COMMON_ID_BLE = 1,
    XDK_COMMON_ID_BUTTON,
    XDK_COMMON_ID_CAYENNELPPSERIALIZER,
    XDK_COMMON_ID_EXTENSIONPORTSPI,
    XDK_COMMON_ID_EXTERNAL_SENSOR,
    XDK_COMMON_ID_FOTA,
    XDK_COMMON_ID_GRIDEYESENSOR,
    XDK_COMMON_ID_GRIDEYESERVICE,
    XDK_COMMON_ID_HTTPRESTCLIENT,
    XDK_COMMON_ID_HTTPRESTCLIENTSECURITY,
    XDK_COMMON_ID_LED,
    XDK_COMMON_ID_LEMSENSOR,
    XDK_COMMON_ID_LWM2M,
    XDK_COMMON_ID_LWM2MDNSUTIL,
    XDK_COMMON_ID_LWM2MOBJECTACCELEROMETER,
    XDK_COMMON_ID_LWM2MOBJECTALERTNOTIFICATION,
    XDK_COMMON_ID_LWM2MOBJECTBAROMETER,
    XDK_COMMON_ID_LWM2MOBJECTCONNECTIVITYMONITORING,
    XDK_COMMON_ID_LWM2MOBJECTDEVICE,
    XDK_COMMON_ID_LWM2MOBJECTFIRMWAREUPDATE,
    XDK_COMMON_ID_LWM2MOBJECTGYROSCOPE,
    XDK_COMMON_ID_LWM2MOBJECTHUMIDITY,
    XDK_COMMON_ID_LWM2MOBJECTILLUMINANCE,
    XDK_COMMON_ID_LWM2MOBJECTLIGHTCONTROL,
    XDK_COMMON_ID_LWM2MOBJECTMAGNETOMETER,
    XDK_COMMON_ID_LWM2MOBJECTS,
    XDK_COMMON_ID_LWM2MOBJECTSENSORDEVICE,
    XDK_COMMON_ID_LWM2MOBJECTTEMPERATURE,
    XDK_COMMON_ID_LWM2MSENSORDEVICEACCELEROMETER,
    XDK_COMMON_ID_LWM2MSENSORDEVICEENVIRONMENTAL,
    XDK_COMMON_ID_LWM2MSENSORDEVICEGYROSCOPE,
    XDK_COMMON_ID_LWM2MSENSORDEVICEILLUMINANCE,
    XDK_COMMON_ID_LWM2MSENSORDEVICEMAGNETOMETER,
    XDK_COMMON_ID_LWM2MSENSORDEVICEUTIL,
    XDK_COMMON_ID_LWM2MUTIL,
    XDK_COMMON_ID_MQTT,
    XDK_COMMON_ID_NOISESENSOR,
    XDK_COMMON_ID_PPMPSERIALIZER,
    XDK_COMMON_ID_RETARGETSTDIO,
    XDK_COMMON_ID_SENSOR,
    XDK_COMMON_ID_SENSORHANDLE,
    XDK_COMMON_ID_SERVALPAL,
    XDK_COMMON_ID_SERVALPALWIFI,
    XDK_COMMON_ID_SNTP,
    XDK_COMMON_ID_STORAGE,
    XDK_COMMON_ID_SYSTEMSTARTUP,
    XDK_COMMON_ID_TIMESTAMP,
    XDK_COMMON_ID_WLAN,
    XDK_COMMON_ID_WLANHOSTPGM,
    XDK_COMMON_ID_UDP,
    XDK_COMMON_ID_USBRESETUTILITY,
	XDK_COMMON_ID_UTILS,
    XDK_COMMON_ID_VIRTUALSENSOR,
    XDK_COMMON_ID_WIFISTORAGE,
    XDK_COMMON_ID_XDKVERSION,

    /* Define next module ID here in-case of new module added in common! */
    XDK_COMMON_ID_OVERFLOW,

};

enum XDK_Common_Retcode_E
{
    RETCODE_ADC_NULL_DMA_CALLBACK = RETCODE_FIRST_CUSTOM_CODE,
    RETCODE_ADC_SCAN_CHANNEL_ALREADY_ENABLED,
    RETCODE_ADC_SCAN_CHANNEL_NOT_ENABLED,
    RETCODE_ADC_REACHED_MAX_SCAN_CHANNELS,
    RETCODE_ADC_SINGLE_CHANNEL_NOT_READY,
    RETCODE_ADC_CENTRAL_USED_IN_SCAN,
    RETCODE_ADC_CENTRAL_ALREADY_INIT,
    RETCODE_ADC_CENTRAL_ALREADY_DEINIT,
    RETCODE_BATTERY_MONITOR_NOT_INIT,
    RETCODE_BLE_INVALID_EVENT_RECEIVED,
    RETCODE_BLE_START_FAILED,
    RETCODE_BLE_WAKEUP_FAILED,
    RETCODE_BLE_SEND_FAILED,
    RETCODE_BLE_NOT_CONNECTED,
    RETCODE_BLE_SEND_MUTEX_NOT_RELEASED,
    RETCODE_BLE_CUSTOM_CB_IS_NULL,
    RETCODE_BLE_INVALID_SERVICE_IS_SETUP,
    RETCODE_EXTENSIONPORTSPI_RX_ERROR,
    RETCODE_EXTENSIONPORTSPI_TX_ERROR,
    RETCODE_EXTENSIONPORTSPI_DATALOSS,
    RETCODE_EXTENSIONPORTSPI_NULL_HANDLE,
    RETCODE_FOTA_STATE_CHANGE_DISCARDED,
    RETCODE_FOTA_TIMER_START_TRIGGER_FAILED,
    RETCODE_FOTA_FILESYSTEM_ERROR,
    RETCODE_FOTA_SDCARD_NOT_INSERTED,
    RETCODE_FOTA_PARTITION_UNKNOWN,
    RETCODE_HTTP_INIT_REQUEST_FAILED,
    RETCODE_HTTP_PUSH_REQUEST_FAILED,
    RETCODE_HTTP_SET_REQ_URL_FAILED,
    RETCODE_HTTP_SET_HOST_FAILED,
    RETCODE_HTTP_POST_CB_NOT_RECEIVED,
    RETCODE_HTTP_POST_CB_STATUS_ERROR,
    RETCODE_HTTP_CLIENT_INIT_FAILED,
    RETCODE_HTTP_REQUEST_SEND_FAILED,
    RETCODE_HTTP_ENABLE_SERVAL_TLS_CLIENT,
    RETCODE_HTTP_SECURE_CERTIFICATE_PARSE_FAILED,
    RETCODE_LWM2M_INIT_FAILED,
    RETCODE_LWM2M_REGISTRATION_FAILED,
    RETCODE_LWM2M_TIMER_STOP_FAILED,
    RETCODE_LWM2M_TIMER_START_FAILED,
    RETCODE_LWM2M_TIMER_RESET_FAILED,
    RETCODE_LWM2M_IPCONFIG_FAILED,
    RETCODE_LWM2M_STACK_START_FAILED,
    RETCODE_LWM2M_CLOCK_GETTIME_FAILED,
    RETCODE_LWM2M_DNSRESOLVE_HOSTNAME_FAILED,
    RETCODE_MQTT_INIT_FAILED,
    RETCODE_MQTT_CONNECT_FAILED,
    RETCODE_MQTT_IPCONIG_FAIL,
    RETCODE_MQTT_INIT_INTERNAL_SESSION_FAILED,
    RETCODE_MQTT_PARSING_ERROR,
    RETCODE_MQTT_CONNECT_CB_NOT_RECEIVED,
    RETCODE_MQTT_CONNECT_STATUS_ERROR,
    RETCODE_MQTT_CONNECTION_CLOSED,
    RETCODE_MQTT_SUBSCRIBE_REMOVED,
    RETCODE_MQTT_SUBSCRIBE_CB_NOT_RECEIVED,
    RETCODE_MQTT_SUBSCRIBE_FAILED,
    RETCODE_MQTT_SUBSCRIBE_STATUS_ERROR,
    RETCODE_MQTT_PUBLISH_FAILED,
    RETCODE_SENSOR_NONE_IS_ENABLED,
    RETCODE_STORAGE_FILE_DOES_NOT_EXIST_WIFI_MEDIA,
    RETCODE_STORAGE_FILE_DOES_NOT_EXIST_SDCARD,
    RETCODE_STORAGE_WRONG_FILE_MODE,
    RETCODE_STORAGE_FILE_HAS_NOT_BEEN_CLOSE_CORRECTLY,
    RETCODE_STORAGE_ERROR_IN_FILE_WRITE,
    RETCODE_STORAGE_ERROR_IN_FILE_READ,
    RETCODE_STORAGE_ERROR_IN_FILE_CLOSE_WIFI_MEDIA,
    RETCODE_STORAGE_ERROR_IN_FILE_DELETE,
    RETCODE_STORAGE_ERROR_IN_GETTING_FILE_STATUS,
    RETCODE_STORAGE_SDCARD_NOT_INSERTED,
    RETCODE_STORAGE_SDCARD_MOUNT_FAILED,
    RETCODE_STORAGE_SDCARD_READ_FAILED,
    RETCODE_STORAGE_SDCARD_RENAME_FAILED,
    RETCODE_STORAGE_SDCARD_STAT_FAILED,
    RETCODE_STORAGE_SDCARD_UNINITIALIZED,
    RETCODE_STORAGE_SDCARD_NOT_AVAILABLE,
    RETCODE_STORAGE_WIFI_UNINITIALIZED,
    RETCODE_STORAGE_F_OPEN_FAILED,
    RETCODE_STORAGE_F_READ_FAILED,
    RETCODE_STORAGE_NOT_ENABLED,
    RETCODE_SNTP_CB_RECEIVED_AFTER_TIMEOUT,
    RETCODE_SNTP_INIT_FAILED,
    RETCODE_SNTP_START_FAILED,
    RETCODE_SNTP_GET_TIME_FAILED,
    RETCODE_SNTP_CB_NOT_RECEIVED,
    RETCODE_SNTP_SYSTEM_TIME_CALC_FAILED,
    RETCODE_SNTP_SEND_FAILED,
    RETCODE_TIMER_PEND_FAILED,
    RETCODE_WLAN_SETUP_IP_CONV_FAILED,
    RETCODE_WLAN_SETUP_GET_FAILED,
    RETCODE_WLAN_SETUP_ENTERPRISE_NW_CFG_GET_FAILED,
    RETCODE_WLAN_SL_SET_FAILED,
    RETCODE_WLAN_HOST_PGM_FS_OPEN_FAILED,
    RETCODE_WLAN_HOST_PGM_FS_WRITE_FAILED,
    RETCODE_WLAN_HOST_PGM_FS_CLOSE_FAILED,
    RETCODE_WLAN_HOST_PGM_SL_STOP_FAILED,
    RETCODE_WLAN_HOST_PGM_SL_START_FAILED,
    RETCODE_UDP_CLOSE_FAILED,
    RETCODE_UDP_SENDING_DATA_FAILED,
    RETCODE_UDP_OPEN_FAILED,
    RETCODE_USB_RECIEVE_FAILED,
    RETCODE_QUEUE_WRITE_FAILED,
    RETCODE_NO_DATA_ON_QUEUE,
    RETCODE_NOISE_SENSOR_ENABLE_FAILED,

    /* Define next common error code enum here in-case of new custom error is needed in common! */
    RETCODE_XDK_APP_FIRST_CUSTOM_CODE,
};

#endif /* XDK_COMMONINFO_H_ */
