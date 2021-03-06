#include "mruby.h"
#include "mruby/variable.h"
#include "mruby/value.h"
#include "M5StickC.h"
#include "M5Display.h"

/* from M5Display
  void begin();
  void sleep();
  void setBrightness(uint8_t brightness);
  void drawBitmap(int16_t x0, int16_t y0, int16_t w, int16_t h, const uint16_t *data);
  void drawBitmap(int16_t x0, int16_t y0, int16_t w, int16_t h, const uint8_t *data);
  void drawBitmap(int16_t x0, int16_t y0, int16_t w, int16_t h, uint16_t *data);
  void drawBitmap(int16_t x0, int16_t y0, int16_t w, int16_t h, uint8_t *data);
  void drawBitmap(int16_t x0, int16_t y0, int16_t w, int16_t h, const uint16_t *data, uint16_t transparent);
  
  void qrcode(const char *string, uint16_t x = 5, uint16_t y = 45, uint8_t width = 70, uint8_t version = 7);
  void qrcode(const String &string, uint16_t x = 5, uint16_t y = 45, uint8_t width = 70, uint8_t version = 7);

１行クリアも必要？
TODO: beginはどうする？どこでする？
*/

#ifdef __cplusplus
extern "C" {
#endif

static mrb_value
mrb_m5stickc_display_init(mrb_state *mrb, mrb_value self)
{
  return self;
}

static mrb_value
mrb_m5stickc_display_begin(mrb_state *mrb, mrb_value self)
{
  M5.Lcd.begin();
  return self;
}

static mrb_value
mrb_m5stickc_display_print(mrb_state *mrb, mrb_value self)
{
	const char *msg;
	mrb_int len;
	mrb_get_args(mrb, "s", &msg, &len);

  M5.Lcd.print(msg);
  return self;
}

static mrb_value
mrb_m5stickc_display_println(mrb_state *mrb, mrb_value self)
{
	const char *msg;
	mrb_int len;
	mrb_get_args(mrb, "s", &msg, &len);

  M5.Lcd.println(msg);
  return self;
}

static mrb_value
mrb_m5stickc_display_fill_screen(mrb_state *mrb, mrb_value self)
{
	mrb_int color;
	mrb_get_args(mrb, "i", &color);

  M5.Lcd.fillScreen(color);
  return self;
}


static mrb_value
mrb_m5stickc_display_clear_screen(mrb_state *mrb, mrb_value self)
{
  M5.Lcd.fillScreen(ST7735_BLACK);
  return self;
}

static mrb_value
mrb_m5stickc_display_set_cursor(mrb_state *mrb, mrb_value self)
{
	mrb_int x, y;
	mrb_get_args(mrb, "ii", &x, &y);

  M5.Lcd.setCursor(x, y);
  return self;
}

static mrb_value
mrb_m5stickc_display_set_text_color(mrb_state *mrb, mrb_value self)
{ // back color is transparent
	mrb_int color;
	mrb_get_args(mrb, "i", &color);

  M5.Lcd.setTextColor(color);
  return self;
}


static mrb_value
mrb_m5stickc_display_set_text_color_with_back_color(mrb_state *mrb, mrb_value self)
{
	mrb_int text_color, back_color;
	mrb_get_args(mrb, "ii", &text_color, &back_color);

  M5.Lcd.setTextColor(text_color, back_color);
  return self;
}

static mrb_value
mrb_m5stickc_display_set_text_size(mrb_state *mrb, mrb_value self)
{
	mrb_int size;
	mrb_get_args(mrb, "i", &size);

  M5.Lcd.setTextSize(size);
  return self;
}

static mrb_value
mrb_m5stickc_display_set_text_font(mrb_state *mrb, mrb_value self)
{
	mrb_int font;
	mrb_get_args(mrb, "i", &font);

  M5.Lcd.setTextFont(font);
  return self;
}

static mrb_value
mrb_m5stickc_display_set_rotation(mrb_state *mrb, mrb_value self)
{
  mrb_int r;
  mrb_get_args(mrb, "i", &r);

  M5.Lcd.setRotation((uint8_t)r);
  return self;
}

extern const unsigned char gImage_logo[];

static mrb_value
mrb_m5stickc_display_draw_bitmap(mrb_state *mrb, mrb_value self)
{
	mrb_int x, y, w, h;
	mrb_get_args(mrb, "iiii", &x, &y, &w, &h);

  M5.Lcd.drawBitmap(x, y, w, h,(uint16_t *)gImage_logo);
  return self;
}

static mrb_value
mrb_m5stickc_display_draw_bitmap_transparent(mrb_state *mrb, mrb_value self)
{
//  void drawBitmap(int16_t x0, int16_t y0, int16_t w, int16_t h, const uint16_t *data, uint16_t transparent);  
  // x0, y0, with, height, const uint16_t *data(bitmapのアドレス？), transparent
  return self;
}

static mrb_value
mrb_m5stickc_display_fill_circle(mrb_state *mrb, mrb_value self)
{
  mrb_int x, y, r, color;
  mrb_get_args(mrb, "iiii", &x, &y, &r, &color);

  M5.Lcd.fillCircle(x, y, r, (uint32_t)color); // but actually color is uint16_t??
  return self;
}

static mrb_value
mrb_m5stickc_display_fill_rect(mrb_state *mrb, mrb_value self)
{
  mrb_int x, y, w, h, color;
  mrb_get_args(mrb, "iiiii", &x, &y, &w, &h, &color);

  M5.Lcd.fillRect(x, y, w, h, (uint32_t)color);
  return self;
}

void
mrb_mruby_m5stickc_display_gem_init(mrb_state* mrb)
{
  struct RClass * m5c = mrb_module_get(mrb, "M5StickC");
  struct RClass * display_class = mrb_define_class_under(mrb, m5c, "Display", mrb->object_class);

  //TFT Color from ST7735_Defins.h
  mrb_define_const(mrb, display_class, "BLACK", mrb_fixnum_value(ST7735_BLACK));
  mrb_define_const(mrb, display_class, "BLUE", mrb_fixnum_value(ST7735_BLUE));
  mrb_define_const(mrb, display_class, "GREEN", mrb_fixnum_value(ST7735_GREEN));
  mrb_define_const(mrb, display_class, "RED", mrb_fixnum_value(ST7735_RED));
  mrb_define_const(mrb, display_class, "WHITE", mrb_fixnum_value(ST7735_WHITE));
  mrb_define_const(mrb, display_class, "YELLOW", mrb_fixnum_value(ST7735_YELLOW));

  mrb_define_method(mrb, display_class, "initialize", mrb_m5stickc_display_init, MRB_ARGS_NONE());
  mrb_define_method(mrb, display_class, "print", mrb_m5stickc_display_print, MRB_ARGS_REQ(1));
  mrb_define_method(mrb, display_class, "puts", mrb_m5stickc_display_println, MRB_ARGS_REQ(1));
  mrb_define_method(mrb, display_class, "fill_screen", mrb_m5stickc_display_fill_screen, MRB_ARGS_REQ(1));
  mrb_define_method(mrb, display_class, "clear", mrb_m5stickc_display_clear_screen, MRB_ARGS_NONE());
  mrb_define_method(mrb, display_class, "cursor", mrb_m5stickc_display_set_cursor, MRB_ARGS_REQ(2));
  mrb_define_method(mrb, display_class, "text_color=", mrb_m5stickc_display_set_text_color, MRB_ARGS_REQ(1));
  mrb_define_method(mrb, display_class, "text_color_with_back_color", mrb_m5stickc_display_set_text_color_with_back_color, MRB_ARGS_REQ(1));
  mrb_define_method(mrb, display_class, "text_size=", mrb_m5stickc_display_set_text_size, MRB_ARGS_REQ(1));
  mrb_define_method(mrb, display_class, "text_font=", mrb_m5stickc_display_set_text_font, MRB_ARGS_REQ(1));
  mrb_define_method(mrb, display_class, "rotation=", mrb_m5stickc_display_set_rotation, MRB_ARGS_REQ(1));
  mrb_define_method(mrb, display_class, "draw_bitmap", mrb_m5stickc_display_draw_bitmap, MRB_ARGS_REQ(4));
//  mrb_define_method(mrb, display_class, "draw_bitmap_transparent", mrb_m5stickc_display_draw_bitmap_transparent, MRB_ARGS_REQ(2));
  mrb_define_method(mrb, display_class, "fill_circle", mrb_m5stickc_display_fill_circle, MRB_ARGS_REQ(4));
  mrb_define_method(mrb, display_class, "fill_rect", mrb_m5stickc_display_fill_rect, MRB_ARGS_REQ(5));
  mrb_define_method(mrb, display_class, "begin", mrb_m5stickc_display_begin, MRB_ARGS_NONE());
}

void
mrb_mruby_m5stickc_display_gem_final(mrb_state* mrb)
{
}

#ifdef __cplusplus
}
#endif
