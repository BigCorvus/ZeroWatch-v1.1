void appStatus() {
  String content = "";
  char character;

  tft.fillScreen(BLACK);
  tft.setCursor(0, 3);
  tft.setTextColor(GREEN);
  tft.setTextSize(1);
  tft.println("HM-11 MAC address:");
  while (Serial.available() > 0) Serial.read(); //empty buffer
  digitalWrite(BT_CTRL, LOW);
  delay(1100);
  digitalWrite(BT_CTRL, HIGH);

  Serial.print("AT+ADDR?");
  delay(100);
  while (Serial.available() > 0) {
    character = Serial.read();
    content.concat(character);
  }
  tft.setTextColor(CYAN);
  if (content != "") {
    tft.println(content.substring(8));
  }
  content = "";
  tft.setTextColor(GREEN);
  tft.println("HM-11 firmware ver.:");
  Serial.print("AT+VERR?");
  delay(100);
  while (Serial.available() > 0) {
    character = Serial.read();
    content.concat(character);
  }
  tft.setTextColor(CYAN);
  if (content != "") {
    tft.println(content);
  }


  delay(50);

  while (!ctp.touched()) {

  }

}

