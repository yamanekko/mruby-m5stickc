// Wire(I2C) class for M5StickC
#include "mruby.h"
#include "mruby/variable.h"
#include "mruby/value.h"
#include "mruby/string.h"
#include "M5StickC.h"

#include "esp32-hal-i2c.h"
#include "Wire.h"
#include "Arduino.h"

#define E_WIRE_ERROR (mrb_class_get(mrb, "M5StickC::Wire::Error"))

static const char ERROR_TEXT_UNKNOWN[] = "UNKNOWN";

#ifdef __cplusplus
extern "C" {
#endif

static TwoWire * wires[] = {&Wire, &Wire1};

static mrb_value
mrb_m5stickc_wire_init(mrb_state *mrb, mrb_value self)
{
  mrb_int num;
  mrb_get_args(mrb, "i", &num);
  if (num < 0 || num > 1) {
    mrb_raisef(mrb, E_ARGUMENT_ERROR, "invalid bus number: %d", num);
  }
  mrb_iv_set(mrb, self, mrb_intern_lit(mrb, "@num"), mrb_fixnum_value(num));
  return self;
}

static TwoWire*
m5stickc_get_wire(mrb_state *mrb, mrb_value self)
{
  mrb_int num = mrb_fixnum(mrb_iv_get(mrb, self, mrb_intern_lit(mrb, "@num")));
  if (num < 0 || num > 1) {
    mrb_raisef(mrb, E_ARGUMENT_ERROR, "invalid bus number: %d", num);
  }
  return wires[num];
}

static mrb_value
mrb_m5stickc_wire_begin(mrb_state *mrb, mrb_value self)
{
  mrb_int sda_pin, scl_pin, frequency;
  bool ret;
  TwoWire *wire = m5stickc_get_wire(mrb, self);

  mrb_get_args(mrb, "iii", &sda_pin, &scl_pin, &frequency);

  ret = wire->begin(sda_pin, scl_pin, frequency);
  if (!ret) {
    mrb_raise(mrb, E_WIRE_ERROR, "failed to start");
  }
  mrb_iv_set(mrb, self, mrb_intern_lit(mrb, "@sda"), mrb_fixnum_value(sda_pin));
  mrb_iv_set(mrb, self, mrb_intern_lit(mrb, "@scl"), mrb_fixnum_value(sda_pin));
  mrb_iv_set(mrb, self, mrb_intern_lit(mrb, "@frequency"), mrb_fixnum_value(frequency));

  return self;
}


static mrb_value
mrb_m5stickc_wire_set_timeout(mrb_state *mrb, mrb_value self)
{
  mrb_int millis;
  TwoWire *wire = m5stickc_get_wire(mrb, self);

  mrb_get_args(mrb, "i", &millis);
  wire->setTimeOut(millis);

  return self;
}

static mrb_value
mrb_m5stickc_wire_get_timeout(mrb_state *mrb, mrb_value self)
{
  mrb_int millis;
  TwoWire *wire = m5stickc_get_wire(mrb, self);

  millis = wire->getTimeOut();
  return mrb_fixnum_value(millis);
}

static mrb_value
mrb_m5stickc_wire_set_clock(mrb_state *mrb, mrb_value self)
{
  mrb_int freq;
  TwoWire *wire = m5stickc_get_wire(mrb, self);

  mrb_get_args(mrb, "i", &freq);
  wire->setClock(freq);

  return self;
}

static mrb_value
mrb_m5stickc_wire_get_clock(mrb_state *mrb, mrb_value self)
{
  mrb_int freq;
  TwoWire *wire = m5stickc_get_wire(mrb, self);

  freq = wire->getClock();
  return mrb_fixnum_value(freq);
}

static mrb_value
mrb_m5stickc_wire_write_transmission(mrb_state *mrb, mrb_value self)
{
  mrb_int address, size;
  uint8_t *buff;
  mrb_bool send_stop;
  mrb_int n;
  TwoWire *wire = m5stickc_get_wire(mrb, self);

  n = mrb_get_args(mrb, "iz|b", &address, &buff, &size, &send_stop);
  if (n < 3) {
    send_stop = true;
  }
  wire->writeTransmission(address, buff, size, send_stop);

  return self;
}

static mrb_value
mrb_m5stickc_wire_read_transmission(mrb_state *mrb, mrb_value self)
{
  mrb_int address;
  uint8_t *buff;
  size_t size;
  mrb_bool send_stop;
  i2c_err_t err;
  uint32_t read_count;
  TwoWire *wire = m5stickc_get_wire(mrb, self);

  mrb_get_args(mrb, "izb", &address, &buff, &size, &send_stop);
  err = wire->readTransmission(address, buff, size, send_stop, &read_count);
  if (err != I2C_ERROR_OK) {
    mrb_raisef(mrb, E_WIRE_ERROR, "read failed (code: %d)", err);
  }

  return mrb_fixnum_value((int32_t)read_count);
}

static mrb_value
mrb_m5stickc_wire_begin_transmission(mrb_state *mrb, mrb_value self)
{
  mrb_int address;
  TwoWire *wire = m5stickc_get_wire(mrb, self);

  mrb_get_args(mrb, "i", &address);
  wire->beginTransmission(address);
  return self;
}

static mrb_value
mrb_m5stickc_wire_end_transmission(mrb_state *mrb, mrb_value self)
{
  bool send_stop;
  i2c_err_t err;
  mrb_int n;
  TwoWire *wire = m5stickc_get_wire(mrb, self);

  n = mrb_get_args(mrb, "|b", &send_stop);
  if (n < 1) {
    send_stop = true;
  }
  err = (i2c_err_t)wire->endTransmission(send_stop);
  if (err != I2C_ERROR_OK) {
    mrb_raisef(mrb, E_WIRE_ERROR, "transmission error(%d)", err);
  }
  return self;
}

static mrb_value
mrb_m5stickc_wire_available(mrb_state *mrb, mrb_value self)
{
  mrb_int result;
  TwoWire *wire = m5stickc_get_wire(mrb, self);

  result = wire->available();
  return mrb_fixnum_value(result);
}

static mrb_value
mrb_m5stickc_wire_request_from(mrb_state *mrb, mrb_value self)
{
  mrb_int address;
  size_t size;
  mrb_bool send_stop;
  mrb_int n;
  mrb_int result;
  TwoWire *wire = m5stickc_get_wire(mrb, self);

  n = mrb_get_args(mrb, "ii|b", &address, &size, &send_stop);
  if (n < 3) {
    send_stop = true;
  }
  result = wire->requestFrom((int)address, (int)size, (int)send_stop);
  if (result == 0) {
    char *err_msg = wire->getErrorText(wire->lastError());
    if (!err_msg) {
      err_msg = (char*)&ERROR_TEXT_UNKNOWN;
    }
    mrb_raisef(mrb, E_WIRE_ERROR, "read failed(%s)", err_msg);
  }
  return mrb_fixnum_value(result);
}

static mrb_value
mrb_m5stickc_wire_write(mrb_state *mrb, mrb_value self)
{
  mrb_int len;
  mrb_value val;
  size_t result;
  mrb_int n;
  char *err_msg;
  TwoWire *wire = m5stickc_get_wire(mrb, self);

  n = mrb_get_args(mrb, "o|i", &val, &len);
  if (n < 2) {
    len = -1;
  }
  if (mrb_fixnum_p(val)) {
    mrb_int byte = mrb_fixnum(val);
    if (byte < 0 || byte > 0xff) {
      mrb_raise(mrb, E_ARGUMENT_ERROR, "invalid data; data should be in 0..255");
    }
    result = wire->write(byte);
    if (!result) {
      char *err_msg = wire->getErrorText(wire->lastError());
      if (!err_msg) {
        err_msg = (char*)&ERROR_TEXT_UNKNOWN;
      }
      mrb_raisef(mrb, E_WIRE_ERROR, "write failed(%s)", err_msg);
    }
    return self;

  } else {
    if (len == -1) {
      len = RSTRING_LEN(val);
    }
    result = wire->write((uint8_t*)RSTRING_PTR(val), len);
    if (result != len) {
      if (!err_msg) {
        err_msg = (char*)&ERROR_TEXT_UNKNOWN;
      }
      mrb_raisef(mrb, E_WIRE_ERROR, "write failed(%s)", err_msg);
    }
    return self;
  }
}

static mrb_value
mrb_m5stickc_wire_read(mrb_state *mrb, mrb_value self)
{
  mrb_int result;
  TwoWire *wire = m5stickc_get_wire(mrb, self);

  result = wire->read();
  return mrb_fixnum_value(result);
}

static mrb_value
mrb_m5stickc_wire_peek(mrb_state *mrb, mrb_value self)
{
  mrb_int result;
  TwoWire *wire = m5stickc_get_wire(mrb, self);

  result = wire->peek();
  return mrb_fixnum_value(result);
}

static mrb_value
mrb_m5stickc_wire_flush(mrb_state *mrb, mrb_value self)
{
  TwoWire *wire = m5stickc_get_wire(mrb, self);

  wire->flush();
  return self;
}

static mrb_value
mrb_m5stickc_wire_busy_p(mrb_state *mrb, mrb_value self)
{
  mrb_bool result;
  TwoWire *wire = m5stickc_get_wire(mrb, self);

  result = wire->busy();
  return mrb_bool_value(result);
}

void
mrb_mruby_m5stickc_wire_gem_init(mrb_state* mrb)
{
	struct RClass * m5_class = mrb_module_get(mrb, "M5StickC");
	struct RClass * button_class = mrb_define_class_under(mrb, m5_class, "TwoWire", mrb->object_class);

	mrb_define_method(mrb, button_class, "initialize", mrb_m5stickc_wire_init, MRB_ARGS_REQ(1));
	mrb_define_method(mrb, button_class, "begin", mrb_m5stickc_wire_begin, MRB_ARGS_REQ(3));
	mrb_define_method(mrb, button_class, "timeout=", mrb_m5stickc_wire_set_timeout, MRB_ARGS_REQ(1));
	mrb_define_method(mrb, button_class, "timeout", mrb_m5stickc_wire_get_timeout, MRB_ARGS_NONE());
	mrb_define_method(mrb, button_class, "clock=", mrb_m5stickc_wire_set_clock, MRB_ARGS_REQ(1));
	mrb_define_method(mrb, button_class, "clock", mrb_m5stickc_wire_get_clock, MRB_ARGS_NONE());
	mrb_define_method(mrb, button_class, "write_transmission", mrb_m5stickc_wire_write_transmission, MRB_ARGS_REQ(3)|MRB_ARGS_OPT(1));
	mrb_define_method(mrb, button_class, "read_transmission", mrb_m5stickc_wire_read_transmission, MRB_ARGS_REQ(3));
	mrb_define_method(mrb, button_class, "begin_transmission", mrb_m5stickc_wire_begin_transmission, MRB_ARGS_REQ(1));
	mrb_define_method(mrb, button_class, "end_transmission", mrb_m5stickc_wire_end_transmission, MRB_ARGS_OPT(1));
	mrb_define_method(mrb, button_class, "available", mrb_m5stickc_wire_available, MRB_ARGS_NONE());
	mrb_define_method(mrb, button_class, "request_from", mrb_m5stickc_wire_request_from, MRB_ARGS_REQ(2)|MRB_ARGS_OPT(1));
	mrb_define_method(mrb, button_class, "write", mrb_m5stickc_wire_write, MRB_ARGS_REQ(1)|MRB_ARGS_OPT(1));
	mrb_define_method(mrb, button_class, "read", mrb_m5stickc_wire_read, MRB_ARGS_NONE());
	mrb_define_method(mrb, button_class, "peek", mrb_m5stickc_wire_peek, MRB_ARGS_NONE());
	mrb_define_method(mrb, button_class, "flush", mrb_m5stickc_wire_flush, MRB_ARGS_NONE());
	mrb_define_method(mrb, button_class, "busy?", mrb_m5stickc_wire_busy_p, MRB_ARGS_NONE());
}

void
mrb_mruby_m5stickc_wire_gem_final(mrb_state* mrb)
{
}

#ifdef __cplusplus
}
#endif
