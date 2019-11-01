begin
  p "-- deep sleep sample -"

  LCD = M5StickC::Display.new
  axp = M5StickC::Axp.new
  buttonA = M5StickC::Button.new(M5StickC::BUTTON_A)
  buttonB = M5StickC::Button.new(M5StickC::BUTTON_B)

  LCD.rotation = 3
  LCD.fill_screen(M5StickC::Display::WHITE)
  LCD.text_color_with_back_color(M5StickC::Display::BLACK, M5StickC::Display::WHITE)

  LCD.cursor(60, 30)
  LCD.puts("SLEEP")

while true
  if buttonA.pressed?
    LCD.puts("plessed!")
    p "pressed!"
    while buttonA.pressed?
      # Will go to sleep 5s after cpu work
      LCD.puts("light sleep")
      p "light sleep"
        axp.light_sleep_sec(5)
      LCD.fill_screen(M5StickC::Display::WHITE)
      LCD.puts("SLEEP")
      ESP32::System.delay(6000)
      # Will enter sleep for 5s and wake up automatically
      LCD.puts("deep sleep")
      p "deep sleep"
      axp.deep_sleep_sec(5)
    end
  end
end

rescue Exception => e
  p e
  p $!
end
