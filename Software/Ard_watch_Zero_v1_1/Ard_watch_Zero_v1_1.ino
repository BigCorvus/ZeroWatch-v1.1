
#include "wiring_private.h" // pinPeripheral() function
#include <Wire.h>
#include <SPI.h>
#include <Adafruit_GFX.h>    // Core graphics library
#include <Adafruit_ST7735.h> // Hardware-specific library
#include <BL6280.h>
#include <SparkFunMPU9250-DMP.h>
#include <RTCZero.h>
#include <Adafruit_Sensor.h>
#include "Adafruit_BME680.h"
//#include "ClosedCube_BME680.h"
#include <IRLibSendBase.h>    // First include the send base
//Now include only the protocols you wish to actually use.
//The lowest numbered protocol should be first but remainder 
//can be any order.
#include <IRLib_P01_NEC.h>    
#include <IRLib_P02_Sony.h>   
#include <IRLibCombo.h>     // After all protocols, include this
// All of the above automatically creates a universal sending
// class called "IRsend" containing only the protocols you want.
// Now declare an instance of that sender.
#define SEALEVELPRESSURE_HPA (1013.25)


/* Create an rtc object */
RTCZero rtc;
/* Change these values to set the current initial time */
byte seconds = 0;
byte minutes = 00;
byte hours = 00;

/* Change these values to set the current initial date */
byte Day = 24;
byte Month = 5;
byte Year = 18;

// Color definitions
#define	BLACK   0x0000
#define	BLUE    0x001F
#define	RED     0xF800
#define	GREEN   0x07E0
#define CYAN    0x07FF
#define MAGENTA 0xF81F
#define YELLOW  0xFFE0
#define WHITE   0xFFFF

#define CS 4
#define DC 12
#define BACKLIGHT 6
#define CHARGE 13
#define BUTTON A4 //A4 is  7
#define TINT A5
#define SPKR 8
#define IR 9
#define AINT 7  //MPUinterrupt
#define VBAT A1
#define MOTOR PORT_PA11
#define TS_RST 10
#define BT_CTRL 2 //formerly SD_CS
#define BT_LED 5
#define BT_MOSFET 1


unsigned long stepCount = 0;
unsigned long stepTime = 0;
unsigned long lastStepCount = 0;

//create a new SPI for SD card
//SPIClass SD_SPI (&sercom2, 3, 5, 4, SPI_PAD_0_SCK_3, SERCOM_RX_PAD_1);
//create a new I2C for sensors
//TwoWire Sens_Wire(&sercom1, 11, 13);

const uint8_t maxApp =7;
char* const appName[] = {"Clock", "Remote", "Status", "Set T", "Bright", "Test S", "Tremor", "Compass"};
MPU9250_DMP imu;
//TFT_ILI9163C tft = TFT_ILI9163C(CS, DC);
Adafruit_ST7735 tft = Adafruit_ST7735(CS,  DC, -1);
BL6280 ctp = BL6280();
Adafruit_BME680 bme; // I2C
IRsend mySender;
//ClosedCube_BME680 bme680;

volatile boolean selButton; // the Select (side) button
volatile boolean Touched;
volatile uint8_t valBright = 100;
volatile int maxX, maxY, maxZ, minX, minY, minZ;

void setup(void) {
  delay(6000); //time to program the atsamd21 before it enters sleep mode

  Wire.begin();
  Serial.begin(9600); //serial port for communication with the BT module
  pinMode(BACKLIGHT, OUTPUT);
  digitalWrite(BACKLIGHT, LOW);
  //pinMode(MOTOR, OUTPUT);
 //digitalWrite(MOTOR, LOW);
 REG_PORT_DIRSET0 = PORT_PA11 ; // Direction set to OUTPUT
 //digitalWrite(MOTOR, LOW);
   REG_PORT_OUTCLR0 = PORT_PA11 ; // set state of pin(s) to LOW
  pinMode(BT_MOSFET, OUTPUT);
  digitalWrite(BT_MOSFET, LOW);
   pinMode(TS_RST, OUTPUT);
  digitalWrite(TS_RST, HIGH);
  pinMode(CHARGE, INPUT);
  pinMode(TINT, INPUT);
  pinMode(SPKR, OUTPUT);
  pinMode(BT_CTRL, OUTPUT);
  digitalWrite(BT_CTRL, HIGH);
  digitalWrite(SPKR, LOW);
  pinMode(AINT, INPUT_PULLUP);
pinMode(BUTTON, INPUT_PULLUP);
  attachInterrupt(BUTTON, btn_isr, LOW);//LOW is needed here in order to be able to wake the atsamd21 from deep sleep!!!!!!!!
  //attachInterrupt(AINT, mpu_isr, LOW);
 //attachInterrupt(TINT, touch_isr, CHANGE);//attachInterrupt(EXTERNAL_INT_6, ISR, FALLING);
  // Configure the regulator to run in normal mode when in standby mode
  // Otherwise it defaults to low power mode and can only supply 50 uA
  //SYSCTRL->VREG.bit.RUNSTDBY = 1;

  // Enable the DFLL48M clock in standby mode
  //SYSCTRL->DFLLCTRL.bit.RUNSTDBY = 1;
  // Set the EIC (External Interrupt Controller) to wake up the MCU
  // on an external interrupt from digital pin 0. (It's EIC channel 11)
  //EIC->WAKEUP.reg = EIC_WAKEUP_WAKEUPEN5;
  
  // Disable the USB device, this avoids USB interrupts
  // mainly the SOF every 1ms.
  // Note: you'll have to double tap the reset button to load new sketches
  //USBDevice.detach();
  rtc.begin(); //Start RTC library, this is where the clock source is initialized
  // Set the time
  rtc.setHours(hours);
  rtc.setMinutes(minutes);
  rtc.setSeconds(seconds);
  // Set the date
  rtc.setDay(Day);
  rtc.setMonth(Month);
  rtc.setYear(Year);
  rtc.setAlarmTime(00, 00, 10); //set alarm time to go off in 10 seconds
  //rtc.enableAlarm(rtc.MATCH_HHMMSS); //set alarm
  // rtc.attachInterrupt(ding); //creates an interrupt that wakes the SAMD21 which is triggered by a FTC alarm 
  tft.initR(INITR_GREENTAB);
  tft.setRotation(0);
  tft.setTextColor(WHITE, BLACK);
  backLight(0);
  selButton = false;
  Touched = false;
  BTwake();
  BTsetup();
 
//basicIMUsetup();
   
//basicBMEsetup();  
 
  
   ctp.begin();
   

  tone(SPKR, 1000, 200);
vibrate();


  //rtc.setAlarmTime(00, 00, 10); //set alarm time to go off in 10 seconds

  //following two lines enable alarm, comment both out if you want to do external interrupt
  // rtc.enableAlarm(rtc.MATCH_HHMMSS); //set alarm
  //rtc.attachInterrupt(ding); //creates an interrupt that wakes the SAMD21 which is triggered by a FTC alarm
  // attachInterrupt(BUTTON, ISR, LOW);
  //comment out the below line if you are using RTC alarm for interrupt
  //extInterrupt(A1); //creates an interrupt source on external pin
}

void loop() {

  modeSleep(); // Shutdown systems for sleep
  //  sleep_mode(); // go to sleep
 // rtc.standbyMode(); //library call
  samSleep();
  modeWake();

  delay(300); //debounce
  selButton = false;
  backLight(valBright);
  appClock();
  unsigned long timer1 = millis() + 5000; //Display stays on 5 seconds
  uint8_t sApp = 0;

  while (millis() < timer1) {
    if ( selButton == true) {
      tone(SPKR, 2000, 70);
      delay(100); //debounce
      selButton = false;
    }
    //Look for the gesture
    if (ctp.touched()) {
      //Touched = false;
      sApp = appMenu();
      //appName[] = {"Clock", "Remote", "Status", "Set T", "Bright", "Test S", "Tremor", "Compass"};
      switch (sApp) {
        case 0:
          timer1 = millis() + 5000;
          appClock();
          break;
        case 1:
          appRemote();
          break;
        case 2:
          appStatus();
          break;
        case 3:
          appSetTime();
          break;
        case 4:
          appSetBright();
          break;
        case 5:
          appTestS();
          break;
        case 6:
          appTremor();
          break;
        case 7:
          appCompass();
          break;
      }
    }
    if(digitalRead(TINT)==LOW){
      //tone(SPKR,1000,20);
    }
  }

  tft.fillScreen(BLACK);
  backLight(0);
  delay(5);

}

void btn_isr()
{
  selButton = true;
  //backLight(0);
  
}

void touch_isr()
{
  //tone(SPKR,1000,20);
  //if(ctp.touched())
  //Touched = true;
  //selButton = true;
  //backLight(0);
}

void mpu_isr()
{
   
}
