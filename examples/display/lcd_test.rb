LCD = M5StickC::Display.new

100.times do |i|
  LCD.clear
  LCD.rotation = i%8
  LCD.cursor(0, 0)

  LCD.text_size = 1
  LCD.puts("Hello, World!")
  ESP32::System.delay(1000)

  LCD.text_size = 2
  LCD.puts("Hello, World!")
  ESP32::System.delay(1000)

  LCD.text_size = 3
  LCD.puts("Hello, World!")
  ESP32::System.delay(1000)
end
