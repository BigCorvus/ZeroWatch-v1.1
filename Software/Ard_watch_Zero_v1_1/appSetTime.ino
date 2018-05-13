// This mode sets the current time

void appSetTime() {
  int tDigit = 0;
  int tHour = 0;
  int tMinute = 0;

  boolean exitOut = false;

  TS_Point p;

  tft.fillScreen(BLACK);
//button borders
  tft.drawFastVLine( 96, 0, 128, BLUE);
  tft.drawFastHLine( 96, 42, 32, BLUE);
  tft.drawFastHLine( 96, 84, 32, BLUE);
  //Arrows
  tft.fillRect(107, 21 , 10, 15, CYAN);
  tft.fillTriangle(112, 8, 103, 21, 121, 22, CYAN);
  tft.fillRect(107, 95 , 10, 15, CYAN);
  tft.fillTriangle(112, 120, 103, 105, 121, 105, CYAN);
  tft.fillTriangle(124, 63, 115, 48, 115, 78, CYAN);
  tft.fillRect(102, 58, 16, 10, CYAN);

  mSTdisplay(tDigit, tHour, tMinute);

  while (!exitOut) {
 while (Serial.available() > 0) {

    // look for the next valid integer in the incoming serial stream:
    hours = Serial.parseInt();
    // do it again:
    minutes = Serial.parseInt();
    // do it again:
    seconds = Serial.parseInt();
    Day = Serial.parseInt();
    // do it again:
    Month = Serial.parseInt();
    // do it again:
    Year = Serial.parseInt();
    mSTdisplay(tDigit, hours, minutes);
//    setTime(tHour, tMinute, 00, month(now()), day(now()), year(now()));
    //RTC.set(now());
    //SamD Rtc
//     rtc.setTime(hours, minutes, seconds); //set time
  //rtc.setDate(day, month, year); //set date
  rtc.setTime(hours, minutes, seconds);
  // Set the date
  rtc.setDay(Day);
  rtc.setMonth(Month);
  rtc.setYear(Year);
}
    if (ctp.touched()) {
      p = ctp.getPoint();
      
      if (p.y > 128) exitOut = true;

      if (p.y > 84 & p.x > 96 & !exitOut) {
        if (tDigit == 0) tHour -= 1;
        if (tDigit == 1) tMinute -= 1;
        if (tHour < 0) tHour = 23;
        if (tMinute < 0) tMinute = 59;
        mSTdisplay(tDigit, tHour, tMinute);
      }

      if (p.y < 42 & p.x > 96 & !exitOut) {
        if (tDigit == 0) tHour += 1;
        if (tDigit == 1) tMinute += 1;
        if (tDigit == 2) exitOut = true;

        if (tHour > 23) tHour = 0;
        if (tMinute > 59) tMinute = 0;
        mSTdisplay(tDigit, tHour, tMinute);
      }

      if (p.y >= 42 & p.y <= 84 & p.x > 96 & !exitOut) {
        tDigit += 1;
        if (tDigit > 1) tDigit = 0;
        mSTdisplay(tDigit, tHour, tMinute);
      }
    }

  }
}

void mSTdisplay(uint8_t tDig, uint8_t tH, uint8_t tM) {

  // Display current time

  tft.fillRect(0, 20, 96, 107, BLACK);
  tft.setCursor(5, 48);

  if (tDig == 0) tft.setTextColor(RED, BLACK);
  else tft.setTextColor(GREEN, BLACK);
  if (tH < 10) tft.print("0");
  tft.print(tH);
  tft.setTextColor(GREEN, BLACK);
  tft.print(":");
  if (tDig == 1) tft.setTextColor(RED, BLACK);
  else tft.setTextColor(GREEN, BLACK);
  if (tM < 10) tft.print("0");
  tft.print(tM);
  delay(200);
}


