//----------------------------
// Draw the default clock face
//----------------------------

void appClock(void) {
 // time_t t ;//RTC.get();

  tft.fillScreen(BLACK);
  tft.setCursor(10, 10);
  tft.setTextColor(BLUE);
  tft.setTextSize(2);
  tft.println("Time");

  // Print Time
  tft.setCursor(10, 40);
  tft.setTextSize(3);
  tft.setTextColor(GREEN);
  if (rtc.getHours() < 10) tft.print(" ");
  tft.print(rtc.getHours());
  tft.print(":");
  if (rtc.getMinutes() < 10) tft.print("0");
  tft.print(rtc.getMinutes());

  // Print Date
  tft.setTextColor(GREEN);
  tft.setTextSize(1);
  tft.setCursor(30, 90);
  tft.print(rtc.getDay());
  tft.print(".");
  tft.print(rtc.getMonth());
  tft.print(".");
  tft.print(rtc.getYear());


  // Voltage
  tft.setCursor(10, 110);

  if (USBDevice.connected()) {
    if (digitalRead(CHARGE)) {
      tft.setTextColor(CYAN);
      tft.print("Charged");
    }
    else {
      tft.setTextColor(RED);
      tft.print("Charging...");
    }
  } 
  tft.setCursor(10, 120);
  tft.setTextColor(CYAN);
   // power_adc_enable();
    tft.print(analogRead(VBAT)*.0064886, 2);
    tft.print(" V  ");
   // power_adc_disable();
  

}
/*
time_t compileTime(void)
{
  char *compDate = __DATE__, *compTime = __TIME__, *months = "JanFebMarAprMayJunJulAugSepOctNovDec";
  char chMon[3], *m;
  int d, y;
  tmElements_t tm;
  time_t t;

  strncpy(chMon, compDate, 3);
  chMon[3] = '\0';
  m = strstr(months, chMon);
  tm.Month = ((m - months) / 3 + 1);

  tm.Day = atoi(compDate + 4);
  tm.Year = atoi(compDate + 7) - 1970;
  tm.Hour = atoi(compTime);
  tm.Minute = atoi(compTime + 3);
  tm.Second = atoi(compTime + 6);
  t = makeTime(tm);
  return t + 10;        //add fudge factor to allow for compile time
}
*/



