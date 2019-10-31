#include "mruby.h"
#include "mruby/variable.h"
#include "mruby/ext/io.h"
#include "Arduino.h"
#include "SPIFFS.h"

#ifdef __cplusplus
extern "C" {
#endif

#define SPIFFS_DEFAULT_MAX_OPEN_FILES 5

/**
 * Register and mount SPIFFS with given path prefix.
 *
 * call-seq:
 *
 *   SPIFFS.mount("/spiffs")
 *   SPIFFS.mount("/spiffs", 10)  ## max open files is 10
 */
mrb_value
mrb_m5stickc_spiffs_mount(mrb_state *mrb, mrb_value self)
{
  char *base_path;
  mrb_int max_open_files;
  mrb_bool result;

  mrb_int n = mrb_get_args(mrb, "z|i", &base_path, &max_open_files);
  if (n < 2) {
    max_open_files = SPIFFS_DEFAULT_MAX_OPEN_FILES;
  }

  result = SPIFFS.begin(false, base_path, max_open_files);
  if (!result) {
    /* E_IO_ERROR is defined in mruby-io */
    mrb_raisef(mrb, E_IO_ERROR, "mounting SPIFFS on %s failed", base_path);
  }
  mrb_iv_set(mrb, self, mrb_intern_lit(mrb, "@base_path"), mrb_str_new_cstr(mrb, base_path));
  log_i("mounted %s", base_path);

  return self;
}

/**
 * unmount SPIFFS
 */
mrb_value
mrb_m5stickc_spiffs_unmount(mrb_state *mrb, mrb_value self)
{
  SPIFFS.end();
  return self;
}

/**
 * format the file system
 */
mrb_value
mrb_m5stickc_spiffs_format(mrb_state *mrb, mrb_value self)
{
  mrb_bool result = SPIFFS.format();
  return mrb_bool_value(result);
}

/**
 * get size of the file system
 */
mrb_value
mrb_m5stickc_spiffs_total_size(mrb_state *mrb, mrb_value self)
{
  size_t total = SPIFFS.totalBytes();
  return mrb_fixnum_value(total);
}

/**
 * get current used bytes in the file system
 */
mrb_value
mrb_m5stickc_spiffs_used_size(mrb_state *mrb, mrb_value self)
{
  size_t used = SPIFFS.usedBytes();
  return mrb_fixnum_value(used);
}

void
mrb_mruby_m5stickc_spiffs_gem_init(mrb_state* mrb)
{
  struct RClass * m5c = mrb_module_get(mrb, "M5StickC");
  struct RClass * spiffs_class = mrb_define_class_under(mrb, m5c, "SPIFFS", mrb->object_class);

  /* mrb_define_class_method(mrb, spiffs_class, "initialize", mrb_m5stickc_spiffs_init, MRB_ARGS_NONE()); */
  mrb_define_class_method(mrb, spiffs_class, "mount", mrb_m5stickc_spiffs_mount, MRB_ARGS_REQ(1));
  mrb_define_class_method(mrb, spiffs_class, "format", mrb_m5stickc_spiffs_format, MRB_ARGS_NONE());
  mrb_define_class_method(mrb, spiffs_class, "unmount", mrb_m5stickc_spiffs_unmount, MRB_ARGS_NONE());
  mrb_define_class_method(mrb, spiffs_class, "total_size", mrb_m5stickc_spiffs_total_size, MRB_ARGS_NONE());
  mrb_define_class_method(mrb, spiffs_class, "used_size", mrb_m5stickc_spiffs_used_size, MRB_ARGS_NONE());
}

void
mrb_mruby_m5stickc_spiffs_gem_final(mrb_state* mrb)
{
}

#ifdef __cplusplus
}
#endif
