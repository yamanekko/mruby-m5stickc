// DHT12 class for M5StickC
#include "mruby.h"
#include "mruby/variable.h"
#include "mruby/value.h"
#include "mruby/string.h"
#include "mruby/class.h"
#include "mruby/data.h"
#include "M5StickC.h"

#include "DHT12.h"

#ifdef __cplusplus
extern "C" {
#endif

// static TwoWire * wires[] = {&Wire, &Wire1};

static void
mrb_m5stickc_dht_free(mrb_state *mrb, void *data)
{
  DHT12 *dht = (DHT12 *)data;
  if (dht) {
    delete dht;
  }
}

static struct mrb_data_type mrb_m5stickc_dht_type = {"DHT12", mrb_m5stickc_dht_free};

static mrb_value
mrb_m5stickc_dht12_init(mrb_state *mrb, mrb_value self)
{
  DHT12 *dht;

  dht = (DHT12 *)DATA_PTR(self);
  mrb_m5stickc_dht_free(mrb, dht);
  mrb_data_init(self, NULL, &mrb_m5stickc_dht_type);

  dht = new DHT12();
  mrb_data_init(self, dht, &mrb_m5stickc_dht_type);

  return self;
}

static DHT12*
m5stickc_get_dht(mrb_state *mrb, mrb_value self)
{
  DHT12 *dht = DATA_GET_PTR(mrb, self, &mrb_m5stickc_dht_type, DHT12);
  if (!dht) {
    mrb_raise(mrb, E_ARGUMENT_ERROR, "uninitialized DHT12 object");
  }
  return dht;
}

static mrb_value
mrb_m5stickc_dht12_read_temperature(mrb_state *mrb, mrb_value self)
{
  mrb_int scale;
  mrb_float result;
  DHT12 *dht = m5stickc_get_dht(mrb, self);

  mrb_int n = mrb_get_args(mrb, "|i", &scale);
  if (n < 1) {
    scale = 1; /* CELSIUS */
  }
  if (scale < 1 || scale > 3) {
    mrb_raisef(mrb, E_ARGUMENT_ERROR, "invalid scale: %d (1..3)", scale);
  }

  result = (mrb_float)dht->readTemperature(scale);
  return mrb_float_value(mrb, result);
}

static mrb_value
mrb_m5stickc_dht12_read_humidity(mrb_state *mrb, mrb_value self)
{
  mrb_float result;
  DHT12 *dht = m5stickc_get_dht(mrb, self);
  result = (mrb_float)dht->readHumidity();
  return mrb_float_value(mrb, result);
}

void
mrb_mruby_m5stickc_dht12_gem_init(mrb_state* mrb)
{
	struct RClass * m5_module = mrb_module_get(mrb, "M5StickC");
	struct RClass * dht12_class = mrb_define_class_under(mrb, m5_module, "DHT12", mrb->object_class);
    MRB_SET_INSTANCE_TT(dht12_class, MRB_TT_DATA);

	mrb_define_method(mrb, dht12_class, "initialize", mrb_m5stickc_dht12_init, MRB_ARGS_NONE());
	mrb_define_method(mrb, dht12_class, "read_temperature", mrb_m5stickc_dht12_read_temperature, MRB_ARGS_OPT(1));
	mrb_define_method(mrb, dht12_class, "read_humidity", mrb_m5stickc_dht12_read_humidity, MRB_ARGS_NONE());
}

void
mrb_mruby_m5stickc_dht12_gem_final(mrb_state* mrb)
{
}

#ifdef __cplusplus
}
#endif
