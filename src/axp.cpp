// axp(axp192) class for M5StickC
#include "mruby.h"
#include "mruby/variable.h"
#include "mruby/value.h"
#include "M5StickC.h"

#ifdef __cplusplus
extern "C" {
#endif

static mrb_value
mrb_mruby_m5stickc_axp_initialize(mrb_state *mrb, mrb_value self)
{ // M5クラスで行なっているのでいらないはず
  log_i("Axp new called");
	return self;
}

static mrb_value
mrb_mruby_m5stickc_axp_begin(mrb_state *mrb, mrb_value self)
{
  log_i("Axp begin called");
  M5.Axp.begin();
	return self;
}

static mrb_value
mrb_mruby_m5stickc_axp_screen_breath(mrb_state *mrb, mrb_value self)
{
  log_i("Axp screen breath called");
  mrb_int n;
  mrb_get_args(mrb, "i", &n);
  M5.Axp.ScreenBreath((uint8_t)n);
  return self;
}

static mrb_value
mrb_mruby_m5stickc_axp_enable_coulombcounter(mrb_state *mrb, mrb_value self)
{
  log_i("Axp enable coulomb counter called");
  M5.Axp.EnableCoulombcounter();
  return self;
}

static mrb_value
mrb_mruby_m5stickc_axp_disable_coulombcounter(mrb_state *mrb, mrb_value self)
{
  log_i("Axp disable coulomb counter called");
  M5.Axp.DisableCoulombcounter();
  return self;
}

static mrb_value
mrb_mruby_m5stickc_axp_stop_coulombcounter(mrb_state *mrb, mrb_value self)
{
  log_i("Axp stop coulomb counter called");
  M5.Axp.StopCoulombcounter();
  return self;
}

static mrb_value
mrb_mruby_m5stickc_axp_clear_coulombcounter(mrb_state *mrb, mrb_value self)
{
  log_i("Axp clear coulomb counter called");
  M5.Axp.ClearCoulombcounter();
  return self;
}

static mrb_value
mrb_mruby_m5stickc_axp_get_coulomb_charge_data(mrb_state *mrb, mrb_value self)
{
  log_i("Axp get coulomb charge data called");
  uint32_t val = M5.Axp.GetCoulombchargeData();
  return mrb_fixnum_value(val);
}

static mrb_value
mrb_mruby_m5stickc_axp_get_coulomb_discharge_data(mrb_state *mrb, mrb_value self)
{
  log_i("Axp get coulomb discharge data called");
  uint32_t val = M5.Axp.GetCoulombdischargeData();
  return mrb_fixnum_value(val);
}

static mrb_value
mrb_mruby_m5stickc_axp_get_coulomb_data(mrb_state *mrb, mrb_value self)
{
  log_i("Axp get coulomb data called");
  float fval = M5.Axp.GetCoulombData();
  return mrb_float_value(mrb, fval);
}

static mrb_value
mrb_mruby_m5stickc_axp_get_battery_voltage(mrb_state *mrb, mrb_value self)
{
  log_i("Axp get battery voltage called");
  uint16_t val = M5.Axp.GetVbatData();
  return mrb_fixnum_value(val);
}

static mrb_value
mrb_mruby_m5stickc_axp_get_Icharge_data(mrb_state *mrb, mrb_value self)
{
  log_i("Axp get I charge data called");
  uint16_t val = M5.Axp.GetIchargeData();
  return mrb_fixnum_value(val);
}

static mrb_value
mrb_mruby_m5stickc_axp_get_Idischarge_data(mrb_state *mrb, mrb_value self)
{
  log_i("Axp get I discharge data called");
  uint16_t val = M5.Axp.GetIdischargeData();
  return mrb_fixnum_value(val);
}

//--
static mrb_value
mrb_mruby_m5stickc_axp_get_temp_data(mrb_state *mrb, mrb_value self)
{
  log_i("Axp get temp data called");
  uint16_t val = M5.Axp.GetTempData();
  return mrb_fixnum_value(val);
}

static mrb_value
mrb_mruby_m5stickc_axp_get_power_battery_data(mrb_state *mrb, mrb_value self)
{
  log_i("Axp get power battery data called");
  uint32_t val = M5.Axp.GetPowerbatData();
  return mrb_fixnum_value(val);
}

static mrb_value
mrb_mruby_m5stickc_axp_get_V_in_data(mrb_state *mrb, mrb_value self)
{
  log_i("Axp get V in data called");
  uint16_t val = M5.Axp.GetVinData();
  return mrb_fixnum_value(val);
}

static mrb_value
mrb_mruby_m5stickc_axp_get_I_in_data(mrb_state *mrb, mrb_value self)
{
  log_i("Axp get I in data called");
  uint16_t val = M5.Axp.GetIinData();
  return mrb_fixnum_value(val);
}

static mrb_value
mrb_mruby_m5stickc_axp_get_V_usb_in_data(mrb_state *mrb, mrb_value self)
{
  log_i("Axp get V usb in data called");
  uint16_t val = M5.Axp.GetVusbinData();
  return mrb_fixnum_value(val);
}


static mrb_value
mrb_mruby_m5stickc_axp_get_I_usb_in_data(mrb_state *mrb, mrb_value self)
{
  log_i("Axp get I usb in data called");
  uint16_t val = M5.Axp.GetIusbinData();
  return mrb_fixnum_value(val);
}

//--
static mrb_value
mrb_mruby_m5stickc_axp_get_V_aps_data(mrb_state *mrb, mrb_value self)
{
  log_i("Axp get V aps data called");
  uint16_t val = M5.Axp.GetVapsData();
  return mrb_fixnum_value(val);
}

static mrb_value
mrb_mruby_m5stickc_axp_button_pressed(mrb_state *mrb, mrb_value self)
{ 
  // 0 not press, 0x01 long press, 0x02 press
  uint8_t val = M5.Axp.GetBtnPress();
  return mrb_fixnum_value(val);
}

static mrb_value
mrb_mruby_m5stickc_axp_set_sleep(mrb_state *mrb, mrb_value self)
{
  log_i("Axp set sleep called");
  M5.Axp.SetSleep();
  return self;
}

static mrb_value
mrb_mruby_m5stickc_axp_deep_sleep_us(mrb_state *mrb, mrb_value self)
{
  log_i("Axp deep sleep us called");
  mrb_int time;
  mrb_int n = mrb_get_args(mrb, "|i", &time);
  if (n < 1) {
    time = 0;
  }
  uint64_t time2 = (uint64_t)time;
  M5.Axp.DeepSleep(time2);
  return self;
}

static mrb_value
mrb_mruby_m5stickc_axp_deep_sleep_sec(mrb_state *mrb, mrb_value self)
{
  log_i("Axp deep sleep sec called");
  printf("Axp deep sleep sec called");
  mrb_int time;
  mrb_int n = mrb_get_args(mrb, "|i", &time);
  if (n < 1) {
    time = 0;
  }
  uint64_t time2 = (uint64_t)time*1000000;
  M5.Axp.DeepSleep(time2);
  return self;
}

static mrb_value
mrb_mruby_m5stickc_axp_light_sleep_us(mrb_state *mrb, mrb_value self)
{
  log_i("Axp light sleep us called");
  mrb_int time;
  mrb_int n = mrb_get_args(mrb, "|i", &time);
  if (n < 1) {
    time = 0;
  }
  uint64_t time2 = (uint64_t)time;
  M5.Axp.LightSleep(time2);
  return self;
}

static mrb_value
mrb_mruby_m5stickc_axp_light_sleep_sec(mrb_state *mrb, mrb_value self)
{
  log_i("Axp light sleep sec called");
  mrb_int time;
  mrb_int n = mrb_get_args(mrb, "|i", &time);
  if (n < 1) {
    time = 0;
  }
  uint64_t time2 = (uint64_t)time*1000000;
  M5.Axp.LightSleep(time2);
  return self;
}

static mrb_value
mrb_mruby_m5stickc_axp_get_warning_level(mrb_state *mrb, mrb_value self)
{
  log_i("Axp get warning level called");
  uint8_t val = M5.Axp.GetWarningLeve();
  return mrb_fixnum_value(val);
}


void
mrb_mruby_m5stickc_axp_gem_init(mrb_state* mrb)
{
	struct RClass * m5_class = mrb_module_get(mrb, "M5StickC");
	struct RClass * axp_class = mrb_define_class_under(mrb, m5_class, "Axp", mrb->object_class);
  //methods
	mrb_define_method(mrb, axp_class, "initialize", mrb_mruby_m5stickc_axp_initialize, MRB_ARGS_NONE());
	mrb_define_method(mrb, axp_class, "begin", mrb_mruby_m5stickc_axp_begin, MRB_ARGS_NONE());
	mrb_define_method(mrb, axp_class, "screen_breath", mrb_mruby_m5stickc_axp_screen_breath, MRB_ARGS_REQ(1));

	mrb_define_method(mrb, axp_class, "enable_coulombcounter", mrb_mruby_m5stickc_axp_enable_coulombcounter, MRB_ARGS_NONE());
	mrb_define_method(mrb, axp_class, "disable_coulombcounter", mrb_mruby_m5stickc_axp_disable_coulombcounter, MRB_ARGS_NONE());
	mrb_define_method(mrb, axp_class, "stop_coulombcounter", mrb_mruby_m5stickc_axp_stop_coulombcounter, MRB_ARGS_NONE());
	mrb_define_method(mrb, axp_class, "clear_coulombcounter", mrb_mruby_m5stickc_axp_clear_coulombcounter, MRB_ARGS_NONE());

	mrb_define_method(mrb, axp_class, "get_charge_data", mrb_mruby_m5stickc_axp_get_coulomb_charge_data, MRB_ARGS_NONE());
	mrb_define_method(mrb, axp_class, "get_discharge_data", mrb_mruby_m5stickc_axp_get_coulomb_discharge_data, MRB_ARGS_NONE());
	mrb_define_method(mrb, axp_class, "get_coulomb_data", mrb_mruby_m5stickc_axp_get_coulomb_data, MRB_ARGS_NONE());
	mrb_define_method(mrb, axp_class, "get_battery_voltage", mrb_mruby_m5stickc_axp_get_battery_voltage, MRB_ARGS_NONE());
	mrb_define_method(mrb, axp_class, "get_Icharge_data", mrb_mruby_m5stickc_axp_get_Icharge_data, MRB_ARGS_NONE());
	mrb_define_method(mrb, axp_class, "get_Idischarge_data", mrb_mruby_m5stickc_axp_get_Idischarge_data, MRB_ARGS_NONE());
	mrb_define_method(mrb, axp_class, "get_temp_data", mrb_mruby_m5stickc_axp_get_temp_data, MRB_ARGS_NONE());
	mrb_define_method(mrb, axp_class, "get_power_battery_data", mrb_mruby_m5stickc_axp_get_power_battery_data, MRB_ARGS_NONE());
	mrb_define_method(mrb, axp_class, "get_V_in_data", mrb_mruby_m5stickc_axp_get_V_in_data, MRB_ARGS_NONE());
	mrb_define_method(mrb, axp_class, "get_I_in_data", mrb_mruby_m5stickc_axp_get_I_in_data, MRB_ARGS_NONE());
	mrb_define_method(mrb, axp_class, "get_V_usb_in_data", mrb_mruby_m5stickc_axp_get_V_usb_in_data, MRB_ARGS_NONE());
	mrb_define_method(mrb, axp_class, "get_I_usb_in_data", mrb_mruby_m5stickc_axp_get_I_usb_in_data, MRB_ARGS_NONE());
	mrb_define_method(mrb, axp_class, "get_V_aps_data", mrb_mruby_m5stickc_axp_get_V_aps_data, MRB_ARGS_NONE());
	mrb_define_method(mrb, axp_class, "button_pressed?", mrb_mruby_m5stickc_axp_button_pressed, MRB_ARGS_NONE());

	mrb_define_method(mrb, axp_class, "set_sleep", mrb_mruby_m5stickc_axp_set_sleep, MRB_ARGS_NONE());
	mrb_define_method(mrb, axp_class, "deep_sleep_us", mrb_mruby_m5stickc_axp_deep_sleep_us, MRB_ARGS_OPT(1));
	mrb_define_method(mrb, axp_class, "deep_sleep_sec", mrb_mruby_m5stickc_axp_deep_sleep_sec, MRB_ARGS_OPT(1));
	mrb_define_method(mrb, axp_class, "light_sleep_us", mrb_mruby_m5stickc_axp_light_sleep_us, MRB_ARGS_OPT(1));
	mrb_define_method(mrb, axp_class, "light_sleep_sec", mrb_mruby_m5stickc_axp_light_sleep_sec, MRB_ARGS_OPT(1));
	mrb_define_method(mrb, axp_class, "get_warning_level", mrb_mruby_m5stickc_axp_get_warning_level, MRB_ARGS_NONE());

/*
  void  begin(void);
  void  ScreenBreath(uint8_t brightness);
  
  void  EnableCoulombcounter(void);
  void  DisableCoulombcounter(void);
  void  StopCoulombcounter(void);
  void  ClearCoulombcounter(void);
  
  uint32_t GetCoulombchargeData(void);
  uint32_t GetCoulombdischargeData(void);
  float GetCoulombData(void);

  uint16_t GetVbatData(void);

  uint16_t GetIchargeData(void); // ACIN voltage
  uint16_t GetIdischargeData(void);

  uint16_t GetTempData(void);

  uint32_t GetPowerbatData(void);

  uint16_t GetVinData(void);
  uint16_t GetIinData(void);

  uint16_t GetVusbinData(void);
  uint16_t GetIusbinData(void);

  uint16_t GetVapsData(void);
  uint8_t GetBtnPress(void);
  
  void SetSleep(void);
  
  // -- sleep
  void DeepSleep(uint64_t time_in_us = 0);
  void LightSleep(uint64_t time_in_us = 0);

  uint8_t GetWarningLeve(void);
*/
//---------coulombcounter_from_here---------
//enable: void EnableCoulombcounter(void); 
//disable: void DisableCOulombcounter(void);
//stop: void StopCoulombcounter(void);
//clear: void ClearCoulombcounter(void);
//get charge data: uint32_t GetCoulombchargeData(void);
//get discharge data: uint32_t GetCoulombdischargeData(void);
//get coulomb val affter calculation: float GetCoulombData(void);
//------------------------------------------

}

void
mrb_mruby_m5stickc_axp_gem_final(mrb_state* mrb)
{
}

#ifdef __cplusplus
}
#endif
