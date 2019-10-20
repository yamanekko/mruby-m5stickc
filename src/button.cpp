// Button class for M5StickC
#include "mruby.h"
#include "mruby/variable.h"
#include "mruby/value.h"
#include "M5StickC.h"

/*    uint8_t read();
    uint8_t isPressed();
    uint8_t isReleased();
    uint8_t wasPressed();
    uint8_t wasReleased();
    uint8_t pressedFor(uint32_t ms);
    uint8_t releasedFor(uint32_t ms);
    uint8_t wasReleasefor(uint32_t ms);
    uint32_t lastChange();
*/

#ifdef __cplusplus
extern "C" {
#endif

static mrb_value
mrb_mruby_m5stickc_button_initialize(mrb_state *mrb, mrb_value self)
{
    mrb_int n;
    mrb_get_args(mrb, "i", &n);
    mrb_iv_set(mrb, self, mrb_intern_lit(mrb, "@num"), mrb_fixnum_value(n));
    if(n != BUTTON_A_PIN && n != BUTTON_B_PIN){
        Button btn = Button(BUTTON_A_PIN, true, DEBOUNCE_MS);
    }
	return self;
}

Button
button_get(mrb_state *mrb, mrb_int n)
{
    if (n == BUTTON_A_PIN) {
        return M5.BtnA;
    } else if (n == BUTTON_B_PIN) {
        return M5.BtnB;
    } else {
        mrb_raisef(mrb, E_ARGUMENT_ERROR, "invalid pin number");
    }
}

static mrb_value
mrb_mruby_m5stickc_button_ispressed(mrb_state *mrb, mrb_value self)
{
	mrb_int num = mrb_fixnum(mrb_iv_get(mrb, self, mrb_intern_lit(mrb, "@num")));
    Button button = button_get(mrb, num);
    uint8_t pressed = button.read();
	if (pressed){
	    return mrb_true_value();
	}else{
		return mrb_false_value();
	}
}


void
mrb_mruby_m5stickc_button_gem_init(mrb_state* mrb)
{
	struct RClass * m5_class = mrb_module_get(mrb, "M5StickC");
	struct RClass * button_class = mrb_define_class_under(mrb, m5_class, "Button", mrb->object_class);
  //methods
	mrb_define_method(mrb, button_class, "initialize", mrb_mruby_m5stickc_button_initialize, MRB_ARGS_REQ(1));
	mrb_define_method(mrb, button_class, "pressed?", mrb_mruby_m5stickc_button_ispressed, MRB_ARGS_NONE());
//	mrb_define_method(mrb, button_class, "wasPressed?", mrb_mruby_button_waspressed, MRB_ARGS_NONE());
//	mrb_define_method(mrb, button_class, "read", mrb_mruby_button_read, MRB_ARGS_NONE());
//	mrb_define_method(mrb, button_class, "pressed?", mrb_mruby_button_isreleased, MRB_ARGS_NONE());
//	mrb_define_method(mrb, button_class, "pressed?", mrb_mruby_button_wasreleased, MRB_ARGS_NONE());
//	mrb_define_method(mrb, button_class, "pressedFor", mrb_mruby_button_pressedfor, MRB_ARGS_NONE());
//	mrb_define_method(mrb, button_class, "pressed?", mrb_mruby_button_releaserdfor, MRB_ARGS_NONE());
//	mrb_define_method(mrb, button_class, "pressed?", mrb_mruby_button_wasreleasedfor, MRB_ARGS_NONE());
//	mrb_define_method(mrb, button_class, "pressed?", mrb_mruby_lastchange, MRB_ARGS_NONE());

}

void
mrb_mruby_m5stickc_button_gem_final(mrb_state* mrb)
{
}

#ifdef __cplusplus
}
#endif
