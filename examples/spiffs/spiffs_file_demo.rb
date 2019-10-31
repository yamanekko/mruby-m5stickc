LCD = M5StickC::Display.new
M5StickC::SPIFFS.format
M5StickC::SPIFFS.mount("/spiffs")

ex = File.exists?("/spiffs/hello.txt")
puts "File: #{ex}"

File.open("/spiffs/hello.txt", "w") do |f|
  f.write "Hello,"
end

File.open("/spiffs/hello.txt", "a") do |f2|
  f2.write " World!\n"
end

ex = File.exists?("/spiffs/hello.txt")
puts "File: #{ex}"

LCD.rotation = 1
LCD.text_size = 2
LCD.print(File.read("/spiffs/hello.txt"))

File.delete("/spiffs/hello.txt")

ex = File.exists?("/spiffs/hello.txt")
puts "File: #{ex}"
