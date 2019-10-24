M5StickC::Wire.begin(32, 33, 100000)

ESP32::System.delay(1000)

@bmp = M5StickC::BMP280.new()
@bmp.begin
@dht = M5StickC::DHT12.new()

ESP32::System.delay(1000)

puts "pressure: #{@bmp.read_pressure}"
puts "temperature: #{@dht.read_temperature}"
puts "humidity: #{@dht.read_humidity}"
