# Ruby version of Dices.ino
# https://github.com/m5stack/M5StickC/blob/master/examples/Games/Dices/Dices.ino

LCD = M5StickC::Display.new
IMU = M5StickC::MPU6886.new

LCD.rotation = 1
LCD.clear
LCD.brightness = 50
LCD.fill_screen(M5StickC::Display::GREEN)
LCD.text_color = M5StickC::Display::BLACK

LCD.cursor(1, 3)
LCD.text_size = 2
LCD.print("SHAKE ME")
ESP32::System.delay(1000)

DOT_SIZE = 6
DOT = [[[35,35]],
       [[15,15],[55,55]],
       [[15,15],[35,35],[55,55]],
       [[15,15],[15,55],[55,15],[55,55]],
       [[15,15],[15,55],[35,35],[55,15],[55,55]],
       [[15,15],[15,35],[15,55],[55,15],[55,35],[55,55]],
      ]

def draw_dice(x, y, n)
  print "dice: #{n}\n"
  LCD.fill_rect(x, y, 70, 70, M5StickC::Display::WHITE)
  6.times do |d|
    if DOT[n][d]
      LCD.fill_circle(x+DOT[n][d][0], y+DOT[n][d][1], DOT_SIZE, M5StickC::Display::BLACK)
    end
  end
end

10000.times do |i|
  while true
    x, y, z = IMU.accel_data
    if x > 1.5 || y > 1.5
      break
    end
    ESP32::System.delay(50)
  end

  LCD.fill_screen(M5StickC::Display::BLACK)
  LCD.cursor(1, 3)

  ## Draw first dice
  ESP32::System.delay(500)  ## A little delay to increase suspense :-D
  number = rand(6).to_i
  draw_dice(5, 5, number)

  ## Draw second dice
  ESP32::System.delay(500)
  number = rand(6).to_i
  draw_dice(85, 5, number)
end
