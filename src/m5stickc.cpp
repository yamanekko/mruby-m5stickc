#include "mruby.h"

#ifdef __cplusplus
extern "C" {
#endif

// TODO:センサー等のクラスを追加する
// void mrb_mruby_xxx_gem_init(mrb_state *mrb);
void mrb_mruby_m5stickc_button_gem_init(mrb_state *mrb);
void mrb_mruby_m5stickc_led_gem_init(mrb_state *mrb);
void mrb_mruby_m5stickc_display_gem_init(mrb_state *mrb);
void mrb_mruby_m5stickc_mpu6886_gem_init(mrb_state* mrb);
void mrb_mruby_m5stickc_wire_gem_init(mrb_state *mrb);
void mrb_mruby_m5stickc_bmp280_gem_init(mrb_state *mrb);
void mrb_mruby_m5stickc_dht12_gem_init(mrb_state *mrb);

static mrb_value
mrb_mruby_m5stickc_initialize(mrb_state *mrb, mrb_value self)
{
  return self;
}

void
mrb_mruby_m5stickc_gem_init(mrb_state* mrb)
{
  struct RClass * m5_class = mrb_define_module(mrb, "M5StickC");

  // constants
  mrb_define_const(mrb,m5_class, "BUTTON_A", mrb_fixnum_value(37));
  mrb_define_const(mrb,m5_class, "BUTTON_B", mrb_fixnum_value(39));

  // methods
  mrb_define_method(mrb, m5_class, "initialize", mrb_mruby_m5stickc_initialize, MRB_ARGS_NONE());

  // initialize under classes
  mrb_mruby_m5stickc_button_gem_init(mrb);
  mrb_mruby_m5stickc_led_gem_init(mrb);
  mrb_mruby_m5stickc_display_gem_init(mrb);
  mrb_mruby_m5stickc_mpu6886_gem_init(mrb);
  mrb_mruby_m5stickc_wire_gem_init(mrb);
  mrb_mruby_m5stickc_bmp280_gem_init(mrb);
  mrb_mruby_m5stickc_dht12_gem_init(mrb);
  // mrb_mruby_xxx_gem_init(mrb);

}

void
mrb_mruby_m5stickc_gem_final(mrb_state* mrb)
{
}
#ifdef __cplusplus
}
#endif
