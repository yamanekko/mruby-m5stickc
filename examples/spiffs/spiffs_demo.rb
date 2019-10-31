LCD = M5StickC::Display.new
M5StickC::SPIFFS.format
M5StickC::SPIFFS.mount("/spiffs")

fd = IO.sysopen("/spiffs/hello.txt", "w")
IO.open(fd, "w") do |f|
  f.syswrite "Hello,"
end

fd = IO.sysopen("/spiffs/hello.txt", "a")
IO.open(fd, "a") do |f|
  f.syswrite " World!\n"
end

LCD.rotation = 1
LCD.text_size = 2
LCD.print(IO.read("/spiffs/hello.txt"))
