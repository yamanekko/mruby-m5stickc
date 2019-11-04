LCD = M5StickC::Display.new
LCD.rotation = 1
LCD.text_font = 4
LCD.clear

wifi = M5StickC::WiFi.new
wifi.begin_STA "(ssid)", "(password)"

ESP32::System.delay(5000)

M5StickC::NTP.config_time(0, 0, "ntp.jst.mfeed.ad.jp", "time.cloudflare.com", "ntp.nict.jp")

loop do
  LCD.cursor(0, 0)
  t=Time.now
  LCD.printf("%04d-%02d-%02d\n%02d:%02d:%02d", t.year, t.mon, t.mday, (t.hour+9) % 24, t.min, t.sec)
  puts "Time: #{Time.now}"
  ESP32::System.delay(1000)
end
