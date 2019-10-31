LCD = M5StickC::Display.new

LCD.rotation = 0
LCD.text_size = 1

LCD.text_font = 1
LCD.print("Font-1\n")

LCD.text_font = 2
LCD.print("Font-2\n")

LCD.text_font = 4
LCD.print("Font-4\n")

LCD.text_font = 6
LCD.print("66\n")
LCD.text_font = 7
LCD.print("77\n")
