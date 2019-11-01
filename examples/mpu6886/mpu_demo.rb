LCD = M5StickC::Display.new
@mpu = M5StickC::MPU6886.new

p "-- RUBY START!! -"

100.times do
  LCD.clear
  LCD.cursor_position(0, 0)

  ## 呼び出すごとにRVALUE(Array)を生成するパターン
  x, y, z = @mpu.accel_data
  LCD.print(sprintf("ac x:%2.2f y:%2.2f, z:%2.2f\n", x, y, z))

  x, y, z = @mpu.gyro_data
  LCD.print(sprintf("gy x:%2.2f y:%2.2f, z:%2.2f\n", x, y, z))

  pitch, roll, yaw = @mpu.gyro_data
  LCD.print(sprintf("ah pitch:%2.2f roll:%2.2f, yaw:%2.2f\n", pitch, roll, yaw))

  ESP32::System.delay(1000)
end
