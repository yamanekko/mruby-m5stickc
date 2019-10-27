// AWS IoT class for M5StickC
#include "M5StickC.h"
#include <WiFiClient.h>
#include <WiFiClientSecure.h>
#include <functional>
#include "PubSubClient.h"
#include "mruby.h"
#include "mruby/variable.h"
#include "mruby/value.h"
#include "mruby/string.h"
#include "mruby/data.h"
#include "mruby/class.h"

typedef struct aws_iot_t{
  WiFiClientSecure *httpsClient;
  PubSubClient *mqttClient;
} aws_iot_t;

static void
mrb_m5stickc_aws_iot_free(mrb_state *mrb, void *data)
{
  struct aws_iot_t *aws = (struct aws_iot_t *)data;
  if (aws) {
    mrb_free(mrb, aws);
  }
}

static struct mrb_data_type mrb_m5stickc_aws_iot_type = {"Time", mrb_m5stickc_aws_iot_free};

void mqttCallback2 (char* topic, byte* payload, unsigned int length, mrb_state *mrb, mrb_value self) {
printf("### mqttCallback function called!\r\n");

	mrb_value block = mrb_iv_get(mrb, self, mrb_intern_lit(mrb, "@block"));
  mrb_value args[2];
  args[0] = mrb_str_new_cstr(mrb, topic);
  args[1] = mrb_str_new(mrb, (const char *)payload, (size_t)length);
  mrb_yield_argv(mrb, block, 2, args);
}

struct aws_iot_t*
mrb_get_aws_iot(mrb_state *mrb, mrb_value self){
  struct aws_iot_t *p = DATA_GET_PTR(mrb, self, &mrb_m5stickc_aws_iot_type, struct aws_iot_t);
  if (!p) {
    mrb_raise(mrb, E_ARGUMENT_ERROR, "uninitialized Time object");
  }
  return p;
}

//---

static mrb_value
mrb_mruby_m5stickc_aws_iot_initialize(mrb_state *mrb, mrb_value self)
{
  struct aws_iot_t *p;
  p = (struct aws_iot_t *)DATA_PTR(self);
  if(p != NULL){
printf("## free 1\r\n");
    mrb_free(mrb, p);
printf("## free 2\r\n");
  }
  mrb_data_init(self, NULL, &mrb_m5stickc_aws_iot_type);
  p = (struct aws_iot_t*)mrb_malloc(mrb, sizeof(struct aws_iot_t));
  WiFiClientSecure *httpsClient = new WiFiClientSecure();
  p->mqttClient = new PubSubClient(*httpsClient);
  p->httpsClient = httpsClient;
  mrb_data_init(self, p, &mrb_m5stickc_aws_iot_type);
	return self;
}

#ifdef __cplusplus
extern "C" {
#endif

static mrb_value
mrb_mruby_m5stickc_aws_iot_setup(mrb_state *mrb, mrb_value self)
{
	mrb_value rootCA = mrb_iv_get(mrb, self, mrb_intern_lit(mrb, "@ca"));
	mrb_value certificate = mrb_iv_get(mrb, self, mrb_intern_lit(mrb, "@certificate"));
	mrb_value privateKey = mrb_iv_get(mrb, self, mrb_intern_lit(mrb, "@privatekey"));
	mrb_value awsEndpoint = mrb_iv_get(mrb, self, mrb_intern_lit(mrb, "@endpoint"));
	mrb_value awsPort_val = mrb_iv_get(mrb, self, mrb_intern_lit(mrb, "@port"));
  mrb_int awsPort;

  struct aws_iot_t *aws = mrb_get_aws_iot(mrb, self);
  if (!mrb_nil_p(rootCA)) aws->httpsClient->setCACert(RSTRING_PTR(rootCA));
  if (!mrb_nil_p(certificate)) aws->httpsClient->setCertificate(RSTRING_PTR(certificate));
  if (!mrb_nil_p(privateKey)) aws->httpsClient->setPrivateKey(RSTRING_PTR(privateKey));
  if (!mrb_nil_p(awsEndpoint)){
    if(!mrb_nil_p(awsPort_val)){
      awsPort = mrb_fixnum(awsPort_val);
      aws->mqttClient->setServer(RSTRING_PTR(awsEndpoint), awsPort);
    }
  }
  aws->mqttClient->setCallback(mqttCallback2);
  aws->mqttClient->setMrb_state(mrb);
  aws->mqttClient->setSelf(self);

  return self;
}

static mrb_value
mrb_mruby_m5stickc_aws_iot_set_ca(mrb_state *mrb, mrb_value self)
{
  const char *ca;
	mrb_int len;
	mrb_get_args(mrb, "s", &ca, &len);
  mrb_iv_set(mrb, self, mrb_intern_cstr(mrb, "@ca"), mrb_str_new_cstr(mrb, ca));

  return self;
}

static mrb_value
mrb_mruby_m5stickc_aws_iot_setcertificate(mrb_state *mrb, mrb_value self)
{
  const char *cert;
	mrb_int len;
	mrb_get_args(mrb, "s", &cert, &len);
  mrb_iv_set(mrb, self, mrb_intern_cstr(mrb, "@certificate"), mrb_str_new_cstr(mrb, cert));
  return self;
}

static mrb_value
mrb_mruby_m5stickc_aws_iot_set_privatekey(mrb_state *mrb, mrb_value self)
{
  const char *pkey;
	mrb_int len;
	mrb_get_args(mrb, "s", &pkey, &len);
  mrb_iv_set(mrb, self, mrb_intern_cstr(mrb, "@privatekey"), mrb_str_new_cstr(mrb, pkey));
  return self;
}

static mrb_value
mrb_mruby_m5stickc_aws_iot_set_endpoint(mrb_state *mrb, mrb_value self)
{
  const char *end;
	mrb_int len;
	mrb_get_args(mrb, "s", &end, &len);
  mrb_iv_set(mrb, self, mrb_intern_cstr(mrb, "@endpoint"), mrb_str_new_cstr(mrb, end));
  return self;
}

static mrb_value
mrb_mruby_m5stickc_aws_iot_set_port(mrb_state *mrb, mrb_value self)
{
	mrb_int port;
	mrb_get_args(mrb, "i", &port);
  mrb_iv_set(mrb, self, mrb_intern_lit(mrb, "@port"), mrb_fixnum_value(port));
  return self;
}

//TODO
static mrb_value
mrb_mruby_m5stickc_aws_iot_set_callback_function(mrb_state *mrb, mrb_value self)
{
printf("AWS set callback func called\r\n");
  return self;
}

static mrb_value
mrb_mruby_m5stickc_aws_iot_mqtt_client_connected(mrb_state *mrb, mrb_value self)
{
printf("AWS MQTT Client connected? called\r\n");
  struct aws_iot_t *aws = mrb_get_aws_iot(mrb, self);
  int status = aws->mqttClient->connected();
  if(status ==1){
    return mrb_true_value();
  }else{
    return mrb_false_value();
  }
}

static mrb_value
mrb_mruby_m5stickc_aws_iot_mqtt_client_conect(mrb_state *mrb, mrb_value self)
{
printf("AWS MQTT Client connect called\r\n");
  const char *clientID;
	mrb_int len;
	mrb_get_args(mrb, "s", &clientID, &len);

  struct aws_iot_t *aws = mrb_get_aws_iot(mrb, self);
  aws->mqttClient->connect(clientID);

  return self;
}

static mrb_value
mrb_mruby_m5stickc_aws_iot_mqtt_client_loop(mrb_state *mrb, mrb_value self)
{
  struct aws_iot_t *aws = mrb_get_aws_iot(mrb, self);
  bool ret = aws->mqttClient->loop();
  return mrb_bool_value(ret);
}

static mrb_value
mrb_mruby_m5stickc_aws_iot_mqtt_client_publish(mrb_state *mrb, mrb_value self)
{
printf("AWS publish called\r\n");
	const char *topic;
	const char *msg;
	mrb_int topic_len, msg_len;
	mrb_get_args(mrb, "ss", &topic, &topic_len, &msg, &msg_len);

  struct aws_iot_t *aws = mrb_get_aws_iot(mrb, self);
  bool ret = aws->mqttClient->publish(topic, msg);
  return mrb_bool_value(ret);
}

static mrb_value
mrb_mruby_m5stickc_aws_iot_on_recieved(mrb_state *mrb, mrb_value self)
{
printf("AWS MQTT Client connect called\r\n");
  mrb_value block;
  aws_iot_t *aws;
	mrb_get_args(mrb, "&", &block);
  mrb_iv_set(mrb, self, mrb_intern_lit(mrb, "@block"), block);

  return mrb_nil_value();
}


static mrb_value
mrb_mruby_m5stickc_aws_iot_mqtt_subscribe(mrb_state *mrb, mrb_value self)
{
printf("AWS subscribe called\r\n");
	const char *subTopic;
	mrb_int topic_len, qos;
	mrb_get_args(mrb, "si", &subTopic, &topic_len, &qos);
  struct aws_iot_t *aws = mrb_get_aws_iot(mrb, self);
  aws->mqttClient->subscribe(subTopic, qos);
  return self;
}

void
mrb_mruby_m5stickc_aws_iot_gem_init(mrb_state* mrb)
{
	struct RClass * m5_class = mrb_module_get(mrb, "M5StickC");
	struct RClass * aws_class = mrb_define_class_under(mrb, m5_class, "AWSIoT", mrb->object_class);
  MRB_SET_INSTANCE_TT(aws_class, MRB_TT_DATA);

  //methods
	mrb_define_method(mrb, aws_class, "initialize", mrb_mruby_m5stickc_aws_iot_initialize, MRB_ARGS_NONE());
	mrb_define_method(mrb, aws_class, "setup", mrb_mruby_m5stickc_aws_iot_setup, MRB_ARGS_NONE());
	mrb_define_method(mrb, aws_class, "aws_ca=", mrb_mruby_m5stickc_aws_iot_set_ca, MRB_ARGS_REQ(1));
	mrb_define_method(mrb, aws_class, "certificate=", mrb_mruby_m5stickc_aws_iot_setcertificate, MRB_ARGS_REQ(1));
	mrb_define_method(mrb, aws_class, "private_key=", mrb_mruby_m5stickc_aws_iot_set_privatekey, MRB_ARGS_REQ(1));
	mrb_define_method(mrb, aws_class, "aws_endpoint=", mrb_mruby_m5stickc_aws_iot_set_endpoint, MRB_ARGS_REQ(1));
	mrb_define_method(mrb, aws_class, "aws_port=", mrb_mruby_m5stickc_aws_iot_set_port, MRB_ARGS_REQ(1));
	mrb_define_method(mrb, aws_class, "callback_func", mrb_mruby_m5stickc_aws_iot_set_callback_function, MRB_ARGS_REQ(1));
	mrb_define_method(mrb, aws_class, "connected?", mrb_mruby_m5stickc_aws_iot_mqtt_client_connected, MRB_ARGS_NONE());
	mrb_define_method(mrb, aws_class, "connect", mrb_mruby_m5stickc_aws_iot_mqtt_client_conect, MRB_ARGS_REQ(1));
	mrb_define_method(mrb, aws_class, "loop", mrb_mruby_m5stickc_aws_iot_mqtt_client_loop, MRB_ARGS_NONE());
	mrb_define_method(mrb, aws_class, "publish", mrb_mruby_m5stickc_aws_iot_mqtt_client_publish, MRB_ARGS_NONE());
	mrb_define_method(mrb, aws_class, "on_recieved", mrb_mruby_m5stickc_aws_iot_on_recieved, MRB_ARGS_BLOCK());
	mrb_define_method(mrb, aws_class, "subscribe", mrb_mruby_m5stickc_aws_iot_mqtt_subscribe, MRB_ARGS_REQ(2));

}

void
mrb_mruby_m5stickc_aws_iot_gem_final(mrb_state* mrb)
{
}

#ifdef __cplusplus
}
#endif
