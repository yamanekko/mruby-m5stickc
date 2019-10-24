@mpu = M5StickC::MPU6886.new

100.times do

  ## 余計なRVALUEを生成しないパターン
  @mpu.read_accel_data
  puts "accel x:#{@mpu.x}, y:#{@mpu.y}, z:#{@mpu.z}"

  @mpu.read_gyro_data
  puts "gyro  x:#{@mpu.x}, y:#{@mpu.y}, z:#{@mpu.z}"

  @mpu.read_ahrs_data
  puts "gyro  x:#{@mpu.x}, y:#{@mpu.y}, z:#{@mpu.z}"

  ## 呼び出すごとにRVALUE(Array)を生成するパターン
  puts @mpu.accel_data
  puts @mpu.gyro_data
  puts @mpu.ahrs_data
end
