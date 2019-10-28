// Button class for M5StickC
#include "mruby.h"
#include "mruby/variable.h"
#include "mruby/value.h"
#include "mruby/string.h"
#include "mruby/data.h"
#include "mruby/class.h"
#include "Arduino.h"
#include "M5StickC.h"
#include <WiFi.h>

#ifdef __cplusplus
extern "C" {
#endif

static mrb_value
mrb_mruby_m5stickc_ntp_config_time(mrb_state *mrb, mrb_value self)
{
  // void configTime(long gmtOffset_sec, int daylightOffset_sec, const char* server1, const char* server2, const char* server3)
  log_i("configTime called\r\n");
  const char *server1;
  const char *server2;
  const char *server3;
  mrb_int server1_len, server2_len, server3_len;
  mrb_int gmtOffset_sec;
  mrb_int daylightOffset_sec;

  mrb_get_args(mrb, "iisss", &gmtOffset_sec, &daylightOffset_sec, &server1, &server1_len, &server2, &server2_len, &server3, &server3_len);

  log_i("confg_val:%d, %d, %s, %s, %s", gmtOffset_sec, daylightOffset_sec, server1,server2,server3);
  configTime(gmtOffset_sec, daylightOffset_sec, server1,server2,server3);

  return self;
}

void
mrb_mruby_m5stickc_ntp_gem_init(mrb_state *mrb)
{
	struct RClass *m5_class = mrb_module_get(mrb, "M5StickC");
	struct RClass *ntp_module = mrb_define_module_under(mrb, m5_class, "NTP");

  //methods
	mrb_define_module_function(mrb, ntp_module, "config_time", mrb_mruby_m5stickc_ntp_config_time, MRB_ARGS_REQ(5));

}

void
mrb_mruby_m5stickc_ntp_gem_final(mrb_state* mrb)
{
}

#ifdef __cplusplus
}
#endif
