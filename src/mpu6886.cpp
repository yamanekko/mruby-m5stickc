// IMU(MPU6886) class for M5StickC
#include "mruby.h"
#include "mruby/variable.h"
#include "mruby/class.h"
#include "M5StickC.h"

#ifdef __cplusplus
extern "C" {
#endif

static mrb_value
mrb_m5stickc_mpu6886_init(mrb_state *mrb, mrb_value self)
{
  M5.MPU6886.Init();
  return self;
}

static mrb_value
mrb_m5stickc_mpu6886_read_accel_adc(mrb_state *mrb, mrb_value self)
{
  int16_t x, y, z;

  M5.MPU6886.getAccelAdc(&x, &y, &z);
  mrb_iv_set(mrb, self, mrb_intern_lit(mrb, "@x"), mrb_fixnum_value((mrb_int)x));
  mrb_iv_set(mrb, self, mrb_intern_lit(mrb, "@y"), mrb_fixnum_value((mrb_int)y));
  mrb_iv_set(mrb, self, mrb_intern_lit(mrb, "@z"), mrb_fixnum_value((mrb_int)z));

  return self;
}

static mrb_value
mrb_m5stickc_mpu6886_read_gyro_adc(mrb_state *mrb, mrb_value self)
{
  int16_t x, y, z;

  M5.MPU6886.getGyroAdc(&x, &y, &z);
  mrb_iv_set(mrb, self, mrb_intern_lit(mrb, "@x"), mrb_fixnum_value((mrb_int)x));
  mrb_iv_set(mrb, self, mrb_intern_lit(mrb, "@y"), mrb_fixnum_value((mrb_int)y));
  mrb_iv_set(mrb, self, mrb_intern_lit(mrb, "@z"), mrb_fixnum_value((mrb_int)z));

  return self;
}

static mrb_value
mrb_m5stickc_mpu6886_read_accel_data(mrb_state *mrb, mrb_value self)
{
  float x, y, z;

  M5.MPU6886.getAccelData(&x, &y, &z);
  mrb_iv_set(mrb, self, mrb_intern_lit(mrb, "@x"), mrb_float_value(mrb, (mrb_float)x));
  mrb_iv_set(mrb, self, mrb_intern_lit(mrb, "@y"), mrb_float_value(mrb, (mrb_float)y));
  mrb_iv_set(mrb, self, mrb_intern_lit(mrb, "@z"), mrb_float_value(mrb, (mrb_float)z));

  return self;
}

static mrb_value
mrb_m5stickc_mpu6886_read_gyro_data(mrb_state *mrb, mrb_value self)
{
  float x, y, z;

  M5.MPU6886.getGyroData(&x, &y, &z);
  mrb_iv_set(mrb, self, mrb_intern_lit(mrb, "@x"), mrb_float_value(mrb, (mrb_float)x));
  mrb_iv_set(mrb, self, mrb_intern_lit(mrb, "@y"), mrb_float_value(mrb, (mrb_float)y));
  mrb_iv_set(mrb, self, mrb_intern_lit(mrb, "@z"), mrb_float_value(mrb, (mrb_float)z));

  return self;
}

static mrb_value
mrb_m5stickc_mpu6886_read_ahrs_data(mrb_state *mrb, mrb_value self)
{
  float pitch, roll, yaw;

  M5.MPU6886.getAhrsData(&pitch, &roll, &yaw);
  mrb_iv_set(mrb, self, mrb_intern_lit(mrb, "@pitch"), mrb_float_value(mrb, (mrb_float)pitch));
  mrb_iv_set(mrb, self, mrb_intern_lit(mrb, "@roll"), mrb_float_value(mrb, (mrb_float)roll));
  mrb_iv_set(mrb, self, mrb_intern_lit(mrb, "@yaw"), mrb_float_value(mrb, (mrb_float)yaw));

  return self;
}

static mrb_value
mrb_m5stickc_mpu6886_temp_adc(mrb_state *mrb, mrb_value self)
{
  int16_t temp;

  M5.MPU6886.getTempAdc(&temp);
  return mrb_fixnum_value((mrb_int)temp);
}

static mrb_value
mrb_m5stickc_mpu6886_temp_data(mrb_state *mrb, mrb_value self)
{
  float temp;

  M5.MPU6886.getTempData(&temp);
  return mrb_float_value(mrb, (mrb_float)temp);
}

void
mrb_mruby_m5stickc_mpu6886_gem_init(mrb_state* mrb)
{
	struct RClass * m5_module = mrb_module_get(mrb, "M5StickC");
	struct RClass * mpu6886_class = mrb_define_class_under(mrb, m5_module, "MPU6886", mrb->object_class);
    MRB_SET_INSTANCE_TT(mpu6886_class, MRB_TT_DATA);

	mrb_define_method(mrb, mpu6886_class, "initialize", mrb_m5stickc_mpu6886_init, MRB_ARGS_NONE());
	mrb_define_method(mrb, mpu6886_class, "read_accel_adc", mrb_m5stickc_mpu6886_read_accel_adc, MRB_ARGS_NONE());
	mrb_define_method(mrb, mpu6886_class, "read_gyro_adc", mrb_m5stickc_mpu6886_read_gyro_adc, MRB_ARGS_NONE());
	mrb_define_method(mrb, mpu6886_class, "read_accel_data", mrb_m5stickc_mpu6886_read_accel_data, MRB_ARGS_NONE());
	mrb_define_method(mrb, mpu6886_class, "read_gyro_data", mrb_m5stickc_mpu6886_read_gyro_data, MRB_ARGS_NONE());
	mrb_define_method(mrb, mpu6886_class, "read_ahrs_data", mrb_m5stickc_mpu6886_read_ahrs_data, MRB_ARGS_NONE());
	mrb_define_method(mrb, mpu6886_class, "temp_adc", mrb_m5stickc_mpu6886_temp_adc, MRB_ARGS_NONE());
	mrb_define_method(mrb, mpu6886_class, "temp_data", mrb_m5stickc_mpu6886_temp_data, MRB_ARGS_NONE());
}

void
mrb_mruby_m5stickc_mpu6886_gem_final(mrb_state* mrb)
{
}

#ifdef __cplusplus
}
#endif

