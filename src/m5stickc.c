#include "mruby.h"

//TODO:センサー等のクラスを追加する
//void mrb_mruby_xxx_gem_init(mrb_state *mrb);

static mrb_value
mrb_mruby_m5stickc_initialize(mrb_state *mrb, mrb_value self)
{
	  return self;
}

void
mrb_mruby_m5stickc_gem_init(mrb_state* mrb)
{
	struct RClass * m5_class = mrb_define_class(mrb, "M5StickC", mrb->object_class);
  //methods
	mrb_define_method(mrb, m5_class, "initialize", mrb_mruby_m5stickc_initialize, MRB_ARGS_NONE();

  // initialize under classes
  //TODO:追加したクラスの初期化をここで
//    mrb_mruby_xxx_gem_init(mrb);

}

void
mrb_mruby_m5stickc_gem_final(mrb_state* mrb)
{
}
