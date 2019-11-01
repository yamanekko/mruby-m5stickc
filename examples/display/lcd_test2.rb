
@button = M5StickC::Button.new(M5StickC::BUTTON_A)
M5StickC::LCD = M5StickC::Display.new()

=begin
M5StickC::LCD.fill_screen(M5StickC::Display::RED)
ESP32::System.delay(1000)
M5StickC::LCD.fill_screen(M5StickC::Display::BLACK)
ESP32::System.delay(1000)
M5StickC::LCD.fill_screen(M5StickC::Display::BLUE)
ESP32::System.delay(1000)
M5StickC::LCD.fill_screen(M5StickC::Display::GREEN)
ESP32::System.delay(1000)
M5StickC::LCD.fill_screen(M5StickC::Display::YELLOW)
ESP32::System.delay(1000)
M5StickC::LCD.fill_screen(M5StickC::Display::WHITE)
ESP32::System.delay(1000)
M5StickC::LCD.clear()
ESP32::System.delay(1000)
=end

M5StickC::LCD.fill_screen(M5StickC::Display::BLUE);
M5StickC::LCD.cursor_position(0, 10);
M5StickC::LCD.text_color = M5StickC::Display::WHITE;
M5StickC::LCD.text_size = 1;
M5StickC::LCD.puts("Bear Do 1!");
ESP32::System.delay(1000)

=begin
M5StickC::LCD.fill_screen(M5StickC::Display::WHITE);
M5StickC::LCD.cursor_position(0, 10);
M5StickC::LCD.text_color = M5StickC::Display::RED;
M5StickC::LCD.text_size = 3;
M5StickC::LCD.puts("Bear Do 2!");
ESP32::System.delay(1000)

M5StickC::LCD.fill_screen(M5StickC::Display::GREEN);
M5StickC::LCD.cursor_position(0, 10);
M5StickC::LCD.text_color = M5StickC::Display::WHITE;
M5StickC::LCD.text_size = 5;
M5StickC::LCD.puts("Bear Do 3!");
ESP32::System.delay(1000)
=end

M5StickC::LCD.clear()
M5StickC::LCD.draw_bitmap(0, 0, 80, 160)
ESP32::System.delay(2000)
M5StickC::LCD.clear()
M5StickC::LCD.draw_bitmap(10, 20, 80, 160)
ESP32::System.delay(3000)


while true
  if @button.pressed?
    M5StickC::LCD.puts("pressed!")
    p "pressed!"
  else
    M5StickC::LCD.puts("not pressed!")
    p "not pressed!"
  end
  ESP32::System.delay(1000)
end