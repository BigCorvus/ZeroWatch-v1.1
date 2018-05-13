// Utilities

// Check to see if the USB is powered
boolean usbDetected() {
 // return USBSTA >> VBUS & 1;
}

// Calculate Free RAM
int freeRam () {
 // extern int __heap_start, *__brkval;
 // int v;
 // return (int) &v - (__brkval == 0 ? (int) &__heap_start : (int) __brkval);
}

void backLight(uint8_t brLvl) {
  analogWrite(BACKLIGHT, brLvl);
}

void modeSleep() {
  // Turn off periphreals
  //accel.standBy();
  //power_adc_disable();
  //digitalWrite(BT_MOSFET, HIGH);
  BTsleep();
  tft.enterSleep();
 ctp.sleep();
 IMUsleep();
 //BToff();
//BTadvInt();
}

void modeWake() {
  // Turn on periphreals
  //accel.active();
 //BTwake();  //you don not really have to wake it up
 //digitalWrite(BT_MOSFET, LOW);
 digitalWrite(TS_RST, LOW);
 delay(30);
 digitalWrite(TS_RST, HIGH);
 ctp.wake();
 tft.exitSleep();

// BTon();
}

//function to show how to put the 
void samSleep()
{
 SCB->SCR |= SCB_SCR_SLEEPDEEP_Msk;
 __DSB();
  __WFI();
}

void BTsetup(){
  //Serial.print("AT+RENEW"); //"factory reset"
//delay(1000);
  Serial.print("AT+PWRM0");
  delay(500);
  Serial.print("AT+ADTY0"); //0 is advertising, scan response, connectable
  delay(500);
  Serial.print("AT+PIO11"); //LED mode: high if connected, otherwse LOW
  delay(500);
  Serial.print("AT+NAMEZeroWatch");
  delay(500);
  Serial.print("AT+POWE1"); //(0-3)
  delay(500);
   Serial.print("AT+UART1");  //cannot be awoken via uart (save power)
  delay(500);
  Serial.print("AT+ADVI5"); //0-9 100ms - 1285ms advertising interval
   delay(500);
   Serial.print("AT+RESET");
   delay(200);
}

void BTsleep(){
  Serial.print("AT+SLEEP");
  delay(100); //UART reception triggers an interrupt, therefore wait 
}

void BTwake(){
  digitalWrite(BT_CTRL, LOW);
  delay(1100);
  digitalWrite(BT_CTRL, HIGH);
  //if you disabled UART for lower power consumption you have to toggle the system KEY to wake the HM-11 up
  //for(int i=0; i<10; i++){
  //Serial.print("QWERTQWERT");
  //}
}

void BTadvInt(){
   Serial.print("AT+ADVI5"); //0-9 100ms - 1285ms advertising interval
   delay(100);
}

void BToff(){
  digitalWrite(BT_MOSFET, HIGH);
}

void BTon(){
  digitalWrite(BT_MOSFET, LOW);
}

void vibrate(){
REG_PORT_OUTSET0 = PORT_PA11 ;
 delay(100);
 REG_PORT_OUTCLR0 = PORT_PA11 ;

}

void doubleVibrate(){    
      REG_PORT_OUTSET0 = PORT_PA11 ;
 delay(100);
 REG_PORT_OUTCLR0 = PORT_PA11 ;
 delay(100);
 REG_PORT_OUTSET0 = PORT_PA11 ;
 delay(100);
 REG_PORT_OUTCLR0 = PORT_PA11 ;
}

void IMUsleep(){
//#define PWR_MGMT_1      0x6B // Device defaults to the Low-Noise mode (3.1 mA)
//#define MPU9250_ADDRESS 0x68 // Device address when ADO = 0
  Wire.beginTransmission(0x68);
  Wire.write(0x6B);
  Wire.write(0x40);
  Wire.endTransmission();
}

void basicIMUsetup(){

     // Call imu.begin() to verify communication and initialize
  if (imu.begin() != INV_SUCCESS)
  {

    doubleVibrate();
  }
  
  // Enable all sensors, and set sample rates to 4Hz.
  // (Slow so we can see the interrupt work.)
  imu.setSensors(INV_XYZ_GYRO | INV_XYZ_ACCEL | INV_XYZ_COMPASS);
  imu.setSampleRate(4); // Set accel/gyro sample rate to 4Hz
  imu.setCompassSampleRate(4); // Set mag rate to 4Hz

  // Use enableInterrupt() to configure the MPU-9250's 
  // interrupt output as a "data ready" indicator.
  imu.enableInterrupt();

  // The interrupt level can either be active-high or low.
  // Configure as active-low, since we'll be using the pin's
  // internal pull-up resistor.
  // Options are INT_ACTIVE_LOW or INT_ACTIVE_HIGH
  imu.setIntLevel(INT_ACTIVE_LOW);

  // The interrupt can be set to latch until data has
  // been read, or to work as a 50us pulse.
  // Use latching method -- we'll read from the sensor
  // as soon as we see the pin go LOW.
  // Options are INT_LATCHED or INT_50US_PULSE
  imu.setIntLatched(INT_LATCHED);
}

void basicBMEsetup(){
 if (!bme.begin()) {
    doubleVibrate();
  }

  // Set up oversampling and filter initialization
  bme.setTemperatureOversampling(BME680_OS_8X);
  bme.setHumidityOversampling(BME680_OS_2X);
  bme.setPressureOversampling(BME680_OS_4X);
  bme.setIIRFilterSize(BME680_FILTER_SIZE_3);
  bme.setGasHeater(320, 150); // 320*C for 150 ms
}


