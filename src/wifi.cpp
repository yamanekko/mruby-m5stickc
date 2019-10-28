// Button class for M5StickC
#include "mruby.h"
#include "mruby/variable.h"
#include "mruby/value.h"
#include "mruby/string.h"
#include "Arduino.h"
#include "M5StickC.h"
#include <WiFi.h>

#ifdef __cplusplus
extern "C" {
#endif

static mrb_value
mrb_mruby_m5stickc_wifi_initialize(mrb_state *mrb, mrb_value self)
{
  log_i("WiFi new called");
	return self;
}

static mrb_value
mrb_mruby_m5stickc_wifi_disconnect(mrb_state *mrb, mrb_value self)
{
  log_i("WiFi disConnect called");

  mrb_bool preserve_client; // defauit is false
  mrb_int n = mrb_get_args(mrb, "|b", &preserve_client);
  if (n < 1) {
    preserve_client = false;
  }
  WiFi.disconnect(preserve_client);

  return self;
}


static mrb_value
mrb_mruby_m5stickc_wifi_begin_sta_mode(mrb_state *mrb, mrb_value self)
{
	const char *ssid;
	const char *pass;
	mrb_int ssid_len, pass_len;

    mrb_get_args(mrb, "ss", &ssid, &ssid_len, &pass, &pass_len);
    log_i("STA ssid=%s, pass=%s", ssid, pass);

    WiFi.begin(ssid, pass);
    return self;
}


static mrb_value
mrb_mruby_m5stickc_wifi_status(mrb_state *mrb, mrb_value self)
{
  log_i("wifi status called");
  mrb_int status = (mrb_int)WiFi.status();
  return mrb_fixnum_value(status);
}

static mrb_value
mrb_mruby_m5stickc_wifi_localip(mrb_state *mrb, mrb_value self)
{
  IPAddress ip = WiFi.localIP();
  String sIP = ip.toString();
  const char *sIP2 = sIP.c_str();
  log_i("wifi localIP:%s", sIP2);
  mrb_value s = mrb_str_new_cstr(mrb, sIP2);
  return s;
}

void
mrb_mruby_m5stickc_wifi_gem_init(mrb_state* mrb)
{
	struct RClass * m5_class = mrb_module_get(mrb, "M5StickC");
	struct RClass * wifi_class = mrb_define_class_under(mrb, m5_class, "WiFi", mrb->object_class);

  mrb_define_const(mrb,wifi_class, "NO_SHIELD", mrb_fixnum_value(WL_NO_SHIELD));
  mrb_define_const(mrb,wifi_class, "IDLE_STATUS", mrb_fixnum_value(WL_IDLE_STATUS));
  mrb_define_const(mrb,wifi_class, "NO_SSID_AVAIL", mrb_fixnum_value(WL_NO_SSID_AVAIL));
  mrb_define_const(mrb,wifi_class, "SCAN_COMPLETED", mrb_fixnum_value(WL_SCAN_COMPLETED));
  mrb_define_const(mrb,wifi_class, "CONNECTED", mrb_fixnum_value(WL_CONNECTED));
  mrb_define_const(mrb,wifi_class, "CONNECT_FAILED", mrb_fixnum_value(WL_CONNECT_FAILED));
  mrb_define_const(mrb,wifi_class, "CONNECTION_LOST", mrb_fixnum_value(WL_CONNECTION_LOST));
  mrb_define_const(mrb,wifi_class, "DISCONNECTED", mrb_fixnum_value(WL_DISCONNECTED));

  //methods
	mrb_define_method(mrb, wifi_class, "initialize", mrb_mruby_m5stickc_wifi_initialize, MRB_ARGS_NONE());
	mrb_define_method(mrb, wifi_class, "disconnect", mrb_mruby_m5stickc_wifi_disconnect, MRB_ARGS_OPT(1));
	mrb_define_method(mrb, wifi_class, "begin_STA", mrb_mruby_m5stickc_wifi_begin_sta_mode, MRB_ARGS_REQ(2));
	mrb_define_method(mrb, wifi_class, "status", mrb_mruby_m5stickc_wifi_status, MRB_ARGS_REQ(1));
	mrb_define_method(mrb, wifi_class, "localIP", mrb_mruby_m5stickc_wifi_localip, MRB_ARGS_REQ(1));

}

void
mrb_mruby_m5stickc_wifi_gem_final(mrb_state* mrb)
{
}

#ifdef __cplusplus
}
#endif
