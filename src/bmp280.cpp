// BMP280 class for M5StickC
#include "mruby.h"
#include "mruby/variable.h"
#include "mruby/value.h"
#include "mruby/string.h"
#include "mruby/class.h"
#include "mruby/data.h"
#include "M5StickC.h"

#include "Adafruit_BMP280.h"

#ifdef __cplusplus
extern "C" {
#endif

static TwoWire * wires[] = {&Wire, &Wire1};

static void
mrb_m5stickc_bmp_free(mrb_state *mrb, void *data)
{
  Adafruit_BMP280 *bmp = (Adafruit_BMP280 *)data;
  if (bmp) {
    delete bmp;
  }
}

static struct mrb_data_type mrb_m5stickc_bmp_type = {"Adafruit_BMP280", mrb_m5stickc_bmp_free};

static mrb_value
mrb_m5stickc_bmp280_init(mrb_state *mrb, mrb_value self)
{
  mrb_int num;
  Adafruit_BMP280 *bmp;
  mrb_int n = mrb_get_args(mrb, "|i", &num);
  if (n < 1) {
    num = 0; /* use Wire in default */
  }
  if (num < 0 || num > 1) {
    mrb_raisef(mrb, E_ARGUMENT_ERROR, "invalid bus number: %d", num);
  }

  bmp = (Adafruit_BMP280 *)DATA_PTR(self);
  mrb_m5stickc_bmp_free(mrb, bmp);
  mrb_data_init(self, NULL, &mrb_m5stickc_bmp_type);

  bmp = new Adafruit_BMP280(wires[num]);
  mrb_data_init(self, bmp, &mrb_m5stickc_bmp_type);

  mrb_iv_set(mrb, self, mrb_intern_lit(mrb, "@num"), mrb_fixnum_value(num));
  return self;
}

static Adafruit_BMP280*
m5stickc_get_bmp(mrb_state *mrb, mrb_value self)
{
  Adafruit_BMP280 *bmp = DATA_GET_PTR(mrb, self, &mrb_m5stickc_bmp_type, Adafruit_BMP280);
  if (!bmp) {
    mrb_raise(mrb, E_ARGUMENT_ERROR, "uninitialized BMP280 object");
  }
  return bmp;
}

static mrb_value
mrb_m5stickc_bmp280_begin(mrb_state *mrb, mrb_value self)
{
  mrb_int addr, chipid;
  bool result;
  mrb_int n = mrb_get_args(mrb, "|ii", &addr, &chipid);
  if (n < 1) {
    addr = BMP280_ADDRESS_ALT;
  }
  if (n < 2) {
    chipid = BMP280_CHIPID;
  }
  Adafruit_BMP280 *bmp = m5stickc_get_bmp(mrb, self);
  result = bmp->begin(addr, chipid);
  if (!result) {
    mrb_raise(mrb, E_RUNTIME_ERROR, "BMP280 stared failed");
  }

  return self;
}

static mrb_value
mrb_m5stickc_bmp280_set_sampling(mrb_state *mrb, mrb_value self)
{

  Adafruit_BMP280::sensor_mode mode;
  Adafruit_BMP280::sensor_sampling tempSampling;
  Adafruit_BMP280::sensor_sampling pressSampling;
  Adafruit_BMP280::sensor_filter filter;
  Adafruit_BMP280::standby_duration duration;

  mrb_int n = mrb_get_args(mrb, "|iiiii", &mode, &tempSampling, &pressSampling, &filter, &duration);
  if (n < 1) {
    mode = Adafruit_BMP280::MODE_NORMAL;
  }
  if (n < 2) {
    tempSampling = Adafruit_BMP280::SAMPLING_X16;
  }
  if (n < 3) {
    pressSampling = Adafruit_BMP280::SAMPLING_X16;
  }
  if (n < 4) {
    filter = Adafruit_BMP280::FILTER_OFF;
  }
  if (n < 5) {
    duration = Adafruit_BMP280::STANDBY_MS_1;
  }
  Adafruit_BMP280 *bmp = m5stickc_get_bmp(mrb, self);
  bmp->setSampling();

  return self;
}

static mrb_value
mrb_m5stickc_bmp280_read_pressure(mrb_state *mrb, mrb_value self)
{
  mrb_float result;
  Adafruit_BMP280 *bmp = m5stickc_get_bmp(mrb, self);
  result = bmp->readPressure();
  return mrb_float_value(mrb, result);
}

void
mrb_mruby_m5stickc_bmp280_gem_init(mrb_state* mrb)
{
	struct RClass * m5_module = mrb_module_get(mrb, "M5StickC");
	struct RClass * bmp280_class = mrb_define_class_under(mrb, m5_module, "BMP280", mrb->object_class);
    MRB_SET_INSTANCE_TT(bmp280_class, MRB_TT_DATA);

	mrb_define_method(mrb, bmp280_class, "initialize", mrb_m5stickc_bmp280_init, MRB_ARGS_OPT(1));
	mrb_define_method(mrb, bmp280_class, "begin", mrb_m5stickc_bmp280_begin, MRB_ARGS_OPT(2));
	mrb_define_method(mrb, bmp280_class, "set_sampling", mrb_m5stickc_bmp280_set_sampling, MRB_ARGS_OPT(5));
	mrb_define_method(mrb, bmp280_class, "read_pressure", mrb_m5stickc_bmp280_read_pressure, MRB_ARGS_NONE());
}

void
mrb_mruby_m5stickc_bmp280_gem_final(mrb_state* mrb)
{
}

#ifdef __cplusplus
}
#endif
