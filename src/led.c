#include "mruby.h"
#include "mruby/variable.h"
#include "esp32-hal-ledc.h"

/* use first channel of 16 channels (started from zero) */
#define LEDC_CHANNEL_0     0

/* use 13 bit precission for LEDC timer */
#define LEDC_TIMER_BIT  13

/* use 5000 Hz as a LEDC base frequency */
#define LEDC_BASE_FREQ     5000


static mrb_value
mrb_m5stickc_led_init(mrb_state *mrb, mrb_value self)
{
  mrb_int channel, pin;
  mrb_int n = mrb_get_args(mrb, "i|i", &pin, &channel);
  if (n < 2) {
    channel = LEDC_CHANNEL_0;
  }
  mrb_iv_set(mrb, self, mrb_intern_lit(mrb, "@channel"), mrb_fixnum_value(channel));
  mrb_iv_set(mrb, self, mrb_intern_lit(mrb, "@pin"), mrb_fixnum_value(pin));
  ledcSetup(channel, LEDC_BASE_FREQ, LEDC_TIMER_BIT);
  ledcAttachPin(pin, channel);
  return self;
}

static mrb_value
mrb_m5stickc_led_on(mrb_state *mrb, mrb_value self)
{
  mrb_int val;
  uint32_t duty;
  mrb_int val_max = 1024;

  mrb_int n = mrb_get_args(mrb, "|i", &val);
  if (n < 1) {
    val = 1024;
  }
  if (val < val_max) {
    duty = (65536 * val / val_max);
  } else {
    duty = 65536;
  }
  /* printf("n:%d, val:%d, duty:%d\n", n, val, duty); */
  mrb_value ch_val = mrb_iv_get(mrb, self, mrb_intern_lit(mrb, "@channel"));
  ledcWrite(mrb_fixnum(ch_val), duty);
  mrb_iv_set(mrb, self, mrb_intern_lit(mrb, "@brightness"), mrb_fixnum_value(duty));
  return self;
}

static mrb_value
mrb_m5stickc_led_off(mrb_state *mrb, mrb_value self){
  mrb_value ch_val = mrb_iv_get(mrb, self, mrb_intern_lit(mrb, "@channel"));
  ledcWrite(mrb_fixnum(ch_val), 0);
  return self;
}

static mrb_value
mrb_m5stickc_led_channel(mrb_state *mrb, mrb_value self)
{
  return mrb_iv_get(mrb, self, mrb_intern_lit(mrb, "@channel"));
}

static mrb_value
mrb_m5stickc_led_pin(mrb_state *mrb, mrb_value self)
{
  return mrb_iv_get(mrb, self, mrb_intern_lit(mrb, "@pin"));
}

static mrb_value
mrb_m5stickc_led_brightness(mrb_state *mrb, mrb_value self)
{
  return mrb_iv_get(mrb, self, mrb_intern_lit(mrb, "@brightness"));
}

void
mrb_mruby_m5stickc_led_gem_init(mrb_state* mrb)
{
  struct RClass * m5c = mrb_module_get(mrb, "M5StickC");
  struct RClass * led_class = mrb_define_class_under(mrb, m5c, "LED", mrb->object_class);

  mrb_define_method(mrb, led_class, "initialize", mrb_m5stickc_led_init, MRB_ARGS_NONE());
  mrb_define_method(mrb, led_class, "on", mrb_m5stickc_led_on, MRB_ARGS_OPT(1));
  mrb_define_method(mrb, led_class, "off", mrb_m5stickc_led_off, MRB_ARGS_NONE());
  mrb_define_method(mrb, led_class, "pin", mrb_m5stickc_led_pin, MRB_ARGS_NONE());
  mrb_define_method(mrb, led_class, "channel", mrb_m5stickc_led_channel, MRB_ARGS_NONE());
  mrb_define_method(mrb, led_class, "brightness", mrb_m5stickc_led_brightness, MRB_ARGS_NONE());
}

void
mrb_mruby_m5stickc_led_gem_final(mrb_state* mrb)
{
}
