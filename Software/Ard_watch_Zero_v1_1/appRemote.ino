void appRemote() {
String content = "";
  char character;
  boolean exitOut = false;
  TS_Point p;
  //  accel.active();

  tft.fillScreen(BLACK);
  tft.setCursor(5, 10);
  tft.setTextColor(GREEN, BLACK);
  tft.setTextSize(1);
  tft.println(" ** Remote **");
  tft.fillRoundRect(2, 40, 40, 40, 5, GREEN);
  tft.fillTriangle(9, 50, 33, 50, 21, 70, ST7735_RED); //down button
   tft.fillRoundRect(43, 40, 40, 40, 5, GREEN);
   tft.fillTriangle(63, 50, 50, 70, 76, 70, ST7735_RED); //UP BUTTON
   tft.fillRoundRect(84, 40, 40, 40, 5, GREEN);

  tft.setTextColor(GREEN, BLACK);
  tft.setTextSize(1);

//Connect to another HM-10 with MAC 20CD398070B9, 1893D780814E is the new HM10
BTwake();
tft.setCursor(0, 85);
//Serial.print("AT+RENEW"); //"factory reset"
// delay(1000);

 Serial.print("AT+ROLE1");
  delay(500);  
Serial.print("AT+IMME1");
  delay(500);
  //Serial.print("AT+DISC?");
  //delay(2000);
  Serial.print("AT+CON1893D780814E");
  delay(500);
while (Serial.available() > 0) {
    character = Serial.read();
    content.concat(character);
  }
  tft.setTextColor(CYAN);
  if (content != "") {
    tft.println(content);
  }

  
  while (!exitOut) {
    if (ctp.touched()) {
      p = ctp.getPoint();
      if (p.y > 128 & p.x > (tft.width() / 3)*2 ){ //the back button
       
        tone(SPKR, 500, 70);
         BTwake(); //this also disconnects if connected
         Serial.print("AT+RESET"); 
         delay(1500);  
         Serial.print("AT+ROLE0");
  delay(500);  
  BTsetup();
        exitOut = true;
      }
      //down button
      if (p.y > 40 & p.y < 80 & p.x > 2 & p.x < 42 & !exitOut) {
        tft.fillRoundRect(2, 40, 40, 40, 5, BLUE);
        tone(SPKR, 2093, 70);
        tft.fillRoundRect(2, 40, 40, 40, 5, GREEN);
        tft.fillTriangle(9, 50, 33, 50, 21, 70, ST7735_RED);
         Serial.print("BTN1");
        delay(100);
      }
      //UP BUTTON
      if (p.y > 40 & p.y < 80 & p.x > 43 & p.x < 83 & !exitOut) {
        tft.fillRoundRect(43, 40, 40, 40, 5, BLUE);
        tone(SPKR, 2637, 70);
         tft.fillRoundRect(43, 40, 40, 40, 5, GREEN);
         tft.fillTriangle(63, 50, 50, 70, 76, 70, ST7735_RED);
         delay(100);
      }
      if (p.y > 40 & p.y < 80 & p.x > 84 & p.x < 126 & !exitOut) {
        tft.fillRoundRect(84, 40, 40, 40, 5, BLUE);
        tone(SPKR, 3136, 70);
        tft.fillRoundRect(84, 40, 40, 40, 5, GREEN);
        mySender.send(SONY,0xa8bca, 20);//Sony DVD power A8BCA, 20 bits
        vibrate();
        delay(100);
      }

    }
    delay(30);
  }
  //accel.standBy();
}

