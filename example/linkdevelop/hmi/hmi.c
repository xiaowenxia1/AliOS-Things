/*
 * Copyright (C) 2015-2017 Alibaba Group Holding Limited
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "iot_import.h"
#include "iot_export.h"
#include "iot_export_mqtt.h"
#include "aos/log.h"
#include "aos/yloop.h"
#include "aos/network.h"
#include <netmgr.h>
#include <aos/kernel.h>
#include <k_err.h>
#include <netmgr.h>
#include <aos/cli.h>
#include <aos/cloud.h>

#include "hal/hal.h"

#ifdef LITTLEVGL_DISPLAY
#include "chat_display.h"
#endif

#ifdef AOS_ATCMD
#include <atparser.h>
#endif

#define PRODUCT_KEY             "a1E31Zmhcxo"
#define DEVICE_NAME             "QSUvUO7V5lxwJsOHgyHc"
#define DEVICE_SECRET           "O6iyf0lnZXJQEyHdyMGPASkEamb5cDEi"

#define ALINK_BODY_FORMAT         "{\"id\":\"%d\",\"version\":\"1.0\",\"method\":\"%s\",\"params\":%s}"
#define ALINK_TOPIC_PROP_POST     "/sys/"PRODUCT_KEY"/"DEVICE_NAME"/thing/event/property/post"
#define ALINK_TOPIC_PROP_POSTRSP  "/sys/"PRODUCT_KEY"/"DEVICE_NAME"/thing/event/property/post_reply"
#define ALINK_TOPIC_PROP_SET      "/sys/"PRODUCT_KEY"/"DEVICE_NAME"/thing/service/property/set"
#define ALINK_METHOD_PROP_POST    "thing.event.property.post"

#define MSG_LEN_MAX             (1024)
/*
* Please check below item which in feature self-definition from "https://linkdevelop.aliyun.com/"
*/
#define PROP_SET_FORMAT_DOWN       "\"down\":"
#define PROP_SET_FORMAT_UP         "{\"up\":\"%s\"}"
int cnt = 0;
static int is_subscribed = 0;
void *gpclient;
char msg_pub[512];
iotx_mqtt_topic_info_t msg;
char *msg_buf = NULL, *msg_readbuf = NULL;
int mqtt_setup(void);
char str_output[256];

/*
 * MQTT Subscribe handler
 * topic: ALINK_TOPIC_PROP_SET
 */

/* @func handle_prop_set is to be used as subscribe handler.
* the messge from LD will be recevied and show on LCD.
*
*/
static void handle_prop_set(void *pcontext, void *pclient, iotx_mqtt_event_msg_pt msg)
{
    char *p_subscontx;
	char *p_subsrm;

    iotx_mqtt_topic_info_pt ptopic_info = (iotx_mqtt_topic_info_pt)msg->msg;
    memset(str_output, 0, sizeof(str_output));
    char *p_serch = strstr(ptopic_info->payload, PROP_SET_FORMAT_DOWN);
    if (p_serch != NULL) {
      p_subscontx = p_serch + strlen(PROP_SET_FORMAT_DOWN);
      p_subsrm = strchr(p_subscontx, '}');
	  if (p_subsrm != NULL) {
		  if (strlen(p_subscontx) - strlen(p_subsrm) < 256)
		     strncpy(str_output, p_subscontx, strlen(p_subscontx) - strlen(p_subsrm));
	  }
	  else
		  LOG("failed to get '}', wrong format topic!");
	} else
		LOG("get wrong format topic!");
    LOG("----");
    LOG("Topic: '%.*s' (Length: %d)", ptopic_info->topic_len,
                  ptopic_info->ptopic, ptopic_info->topic_len);
    LOG("Payload: '%.*s' (Length: %d)", ptopic_info->payload_len,
                  ptopic_info->payload, ptopic_info->payload_len);
    LOG("----");

    LOG(">>>>>>%s", str_output);

}

/*
* MQTT Subscribe handler
* topic: ALINK_TOPIC_PROP_POSTRSP
*/
static void handle_prop_postrsp(void *pcontext, void *pclient,
                                iotx_mqtt_event_msg_pt msg)
{
    iotx_mqtt_topic_info_pt ptopic_info = (iotx_mqtt_topic_info_pt)msg->msg;

#if 0
    // print topic name and topic message
    LOG("----");
    LOG("Topic: '%.*s' (Length: %d)", ptopic_info->topic_len,
        ptopic_info->ptopic, ptopic_info->topic_len);
    LOG("Payload: '%.*s' (Length: %d)", ptopic_info->payload_len,
        ptopic_info->payload, ptopic_info->payload_len);
    LOG("----");
#endif
}

static void wifi_service_event(input_event_t *event, void *priv_data)
{
    if (event->type != EV_WIFI) {
        return;
    }

    if (event->code != CODE_WIFI_ON_GOT_IP) {
        return;
    }
    LOG("wifi_service_event!");
    mqtt_setup();
}


/*
 * MQTT subscribe, from fixed topic, alink protocol format
 */
static void mqtt_subscribe(void *pclient)
{
    int rc = -1;
    /* Subscribe the specific topic */
    rc = IOT_MQTT_Subscribe(pclient, ALINK_TOPIC_PROP_SET, IOTX_MQTT_QOS0,
                            handle_prop_set, NULL);
    if (rc < 0) {
        LOG("subscribe ALINK_TOPIC_PROP_SET failed, rc = %d", rc);
    }
    rc = IOT_MQTT_Subscribe(pclient, ALINK_TOPIC_PROP_POSTRSP, IOTX_MQTT_QOS0,
                            handle_prop_postrsp, NULL);
    if (rc < 0) {
        LOG("subscribe ALINK_TOPIC_PROP_POSTRSP failed, rc = %d", rc);
    }
}

/*
 * MQTT publish, to fixed topic, alink protocol format
 */
static void mqtt_publish(void *pclient, char *payload)
{
    int  rc        = -1;
    char param[64] = { 0 };

    /* Initialize topic information */
    memset(&msg, 0x0, sizeof(iotx_mqtt_topic_info_t));

    msg.qos    = IOTX_MQTT_QOS0;
    msg.retain = 0;
    msg.dup    = 0;

    memset(param, 0, sizeof(param));
    memset(msg_pub, 0, sizeof(msg_pub));

    sprintf(param, PROP_SET_FORMAT_UP, payload);
    int msg_len =
      sprintf(msg_pub, ALINK_BODY_FORMAT, cnt, ALINK_METHOD_PROP_POST, param);
    if (msg_len < 0) {
        LOG("Error occur! Exit program");
    }

    msg.payload     = (void *)msg_pub;
    msg.payload_len = msg_len;

    rc = IOT_MQTT_Publish(pclient, ALINK_TOPIC_PROP_POST, &msg);
    if (rc < 0) {
        LOG("error occur when publish. %d", rc);
    }

    LOG("id: %u, publish msg: %s", (uint32_t)cnt, msg_pub);
    cnt++;
}

static void cmd_pub(char *pwbuf, int blen, int argc, char **argv)
{
    if (argc == 2) {
        mqtt_publish(gpclient, argv[1]);
    } else {
        printf("usage: %s [payload]\n", argv[0]);
    }
}

/*
 * customized command entry for cli
 */
static struct cli_command cli_cmd_pub = {
    .name     = "pub",
    .help     = "mqtt publish, usage: pub [msg payload]",
    .function = cmd_pub
};

void user_pub(char *usr_payload)
{
  mqtt_publish(gpclient, usr_payload);	
}

int g_mqtt_enabled_flag = 0;
/*
 * MQTT ready event handler
 */
static void mqtt_service_event(input_event_t *event, void *priv_data)
{
    char *pclient = priv_data;
    if (event->type == EV_SYS && event->code == CODE_SYS_ON_MQTT_READ) {
        LOG("mqtt service");
        mqtt_subscribe(pclient);
        aos_cli_register_command(&cli_cmd_pub);
		g_mqtt_enabled_flag = 1;
    } else {
        LOG("skip mqtt service");
    }
}

void event_handle_mqtt(void *pcontext, void *pclient, iotx_mqtt_event_msg_pt msg)
{
    uintptr_t packet_id = (uintptr_t)msg->msg;
    iotx_mqtt_topic_info_pt topic_info = (iotx_mqtt_topic_info_pt)msg->msg;

    switch (msg->event_type) {
        case IOTX_MQTT_EVENT_UNDEF:
            LOG("undefined event occur.");
            break;

        case IOTX_MQTT_EVENT_DISCONNECT:
            LOG("MQTT disconnect.");
            break;

        case IOTX_MQTT_EVENT_RECONNECT:
            LOG("MQTT reconnect.");
            break;

        case IOTX_MQTT_EVENT_SUBCRIBE_SUCCESS:
            LOG("subscribe success, packet-id=%u", (unsigned int)packet_id);
            break;

        case IOTX_MQTT_EVENT_SUBCRIBE_TIMEOUT:
            LOG("subscribe wait ack timeout, packet-id=%u", (unsigned int)packet_id);
            break;

        case IOTX_MQTT_EVENT_SUBCRIBE_NACK:
            LOG("subscribe nack, packet-id=%u", (unsigned int)packet_id);
            break;

        case IOTX_MQTT_EVENT_UNSUBCRIBE_SUCCESS:
            LOG("unsubscribe success, packet-id=%u", (unsigned int)packet_id);
            break;

        case IOTX_MQTT_EVENT_UNSUBCRIBE_TIMEOUT:
            LOG("unsubscribe timeout, packet-id=%u", (unsigned int)packet_id);
            break;

        case IOTX_MQTT_EVENT_UNSUBCRIBE_NACK:
            LOG("unsubscribe nack, packet-id=%u", (unsigned int)packet_id);
            break;

        case IOTX_MQTT_EVENT_PUBLISH_SUCCESS:
            LOG("publish success, packet-id=%u", (unsigned int)packet_id);
            break;

        case IOTX_MQTT_EVENT_PUBLISH_TIMEOUT:
            LOG("publish timeout, packet-id=%u", (unsigned int)packet_id);
            break;

        case IOTX_MQTT_EVENT_PUBLISH_NACK:
            LOG("publish nack, packet-id=%u", (unsigned int)packet_id);
            break;

        case IOTX_MQTT_EVENT_PUBLISH_RECVEIVED:
            LOG("topic message arrived but without any related handle: topic=%.*s, topic_msg=%.*s",
                topic_info->topic_len,
                topic_info->ptopic,
                topic_info->payload_len,
                topic_info->payload);
            break;

        default:
            LOG("Should NOT arrive here.");
            break;
    }
}

void release_buff()
{
    if (NULL != msg_buf) {
        aos_free(msg_buf);
    }

    if (NULL != msg_readbuf) {
        aos_free(msg_readbuf);
    }
}

int mqtt_setup(void)
{
    int rc = 0;
    iotx_conn_info_pt pconn_info;
    iotx_mqtt_param_t mqtt_params;

    if (msg_buf != NULL) {
        return rc;
    }

    if (NULL == (msg_buf = (char *)aos_malloc(MSG_LEN_MAX))) {
        LOG("not enough memory");
        rc = -1;
        release_buff();
        return rc;
    }

    if (NULL == (msg_readbuf = (char *)aos_malloc(MSG_LEN_MAX))) {
        LOG("not enough memory");
        rc = -1;
        release_buff();
        return rc;
    }

    /* Device AUTH */
    if (0 != IOT_SetupConnInfo(PRODUCT_KEY, DEVICE_NAME, DEVICE_SECRET, (void **)&pconn_info)) {
        LOG("AUTH request failed!");
        rc = -1;
        release_buff();
        return rc;
    }

    /* Initialize MQTT parameter */
    memset(&mqtt_params, 0x0, sizeof(mqtt_params));
    mqtt_params.port = pconn_info->port;
    mqtt_params.host = pconn_info->host_name;
    mqtt_params.client_id = pconn_info->client_id;
    mqtt_params.username = pconn_info->username;
    mqtt_params.password = pconn_info->password;
    mqtt_params.pub_key = pconn_info->pub_key;
    mqtt_params.request_timeout_ms = 2000;
    mqtt_params.clean_session = 0;
    mqtt_params.keepalive_interval_ms = 60000;
    mqtt_params.pread_buf = msg_readbuf;
    mqtt_params.read_buf_size = MSG_LEN_MAX;
    mqtt_params.pwrite_buf = msg_buf;
    mqtt_params.write_buf_size = MSG_LEN_MAX;
    mqtt_params.handle_event.h_fp = event_handle_mqtt;
    mqtt_params.handle_event.pcontext = NULL;

    /* Construct a MQTT client with specify parameter */
    gpclient = IOT_MQTT_Construct(&mqtt_params);
    if (NULL == gpclient) {
        LOG("MQTT construct failed");
        rc = -1;
        release_buff();
    } else {
        aos_register_event_filter(EV_SYS,  mqtt_service_event, gpclient);
    }

    return rc;
}

int application_start(int argc, char *argv[])
{
#if AOS_ATCMD
    at.set_mode(ASYN);
    at.init(AT_RECV_PREFIX, AT_RECV_SUCCESS_POSTFIX,
            AT_RECV_FAIL_POSTFIX, AT_SEND_DELIMITER, 1000);
#endif

#ifdef WITH_SAL
    sal_init();
#endif

    printf("== Build on: %s %s ===\n", __DATE__, __TIME__);
    aos_set_log_level(AOS_LL_DEBUG);
    aos_register_event_filter(EV_WIFI, wifi_service_event, NULL);

    netmgr_init();
#ifdef ATSAME54_XPRO_BOARD
    same54brd_button0_irq_init();
#endif
#if 0
    netmgr_ap_config_t apconfig;
    memset(&apconfig, 0, sizeof(apconfig));
    strcpy(apconfig.ssid, "aliyuniot");
    strcpy(apconfig.pwd, "aliyuniot1688");
    netmgr_set_ap_config(&apconfig);
#endif
    netmgr_start(false);

#ifdef LITTLEVGL_DISPLAY
    sensor_display_init();
#endif
    aos_loop_run();

    return 0;
}
