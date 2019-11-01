begin
  p "-- Axp sample -"

LCD = M5StickC::Display.new
axp = M5StickC::Axp.new
# axp.begin #M5.beginですでに呼ばれてる
LCD.fill_screen(M5StickC::Display::BLACK)
axp.enable_coulombcounter()
axp.screen_breath(12)
ESP32::System.delay(1000)
axp.screen_breath(10)

while true
  LCD.cursor(0, 2)

  vbat      = axp.get_battery_voltage() * 1.1 / 1000
  LCD.puts(sprintf("vbat:%.3fV",vbat))  ## battery voltage

  charge    = axp.get_Icharge_data() / 2
  LCD.puts(sprintf("icharge:%dmA",charge))  ## battery charging current

  discharge = axp.get_Idischarge_data() / 2
  LCD.puts(sprintf("idischg:%dmA",discharge))  ## battery output current

  temp      =  -144.7 + axp.get_temp_data() * 0.1
  LCD.puts(sprintf("temp:%.1fC",temp))  ## axp192 inside temp

  bat_p     =  axp.get_power_battery_data() * 1.1 * 0.5 /1000
  LCD.puts(sprintf("pw:%.3fmW",bat_p))  ## battery power

  charge_data = axp.get_charge_data()
  LCD.puts(sprintf("CoIn :%d",charge_data))  ## coulomb in current

  discharge_data = axp.get_discharge_data()
  LCD.puts(sprintf("CoOut:%d",discharge_data))  ## coulomb out current

  coulomb_data = axp.get_coulomb_data()
  LCD.puts(sprintf("CoD:%.2fmAh",coulomb_data))  ## value of coulomb after calculate

  v_in = axp.get_V_in_data() * 1.7
  LCD.puts(sprintf("Vin:%.3fmV",v_in))  ## ACIN vin voltage

  I_in = axp.get_I_in_data() * 0.625
  LCD.puts(sprintf("Iin:%.3fmA",I_in)) ## ACIN vin current

  v_usb = axp.get_V_usb_in_data() * 1.7
  LCD.puts(sprintf("Vuin:%.3fmV",v_usb))  ## usb vin voltage

  i_usb = axp.get_I_usb_in_data() * 0.375
  LCD.puts(sprintf("Iuin:%.3fmA",i_usb))  ## usb vin current

  level = axp.get_warning_level()
  LCD.puts(sprintf("batLv:%d",level))

  ## 0x01 long press(1s), 0x02 press
  status = axp.button_pressed?
  if status == 2
    LCD.puts("pressd!")
  elsif status == 1
    LCD.puts("long pressd!")
  elsif status == 0
    LCD.puts("not pressd!")
  end
  
  ESP32::System.delay(200)
end

rescue Exception => e
  p e
  p $!
end

