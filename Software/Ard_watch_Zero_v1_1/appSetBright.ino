//----------------------------
// Set the brightness
//----------------------------

void appSetBright(void) {
  TS_Point p;
  boolean done = false;

  tft.fillScreen(BLACK);
  tft.setCursor(10, 50);
  tft.setTextColor(WHITE, BLACK);
  tft.setTextSize(3);
  tft.println("BRIGHT");
tft.setTextSize(0);
  while (!done) {
    if (ctp.touched()) {
      p = ctp.getPoint();
  
      if (p.y > 128) {
        done = true;
      } else {
        tft.setCursor(30,100);
        tft.print(p.x);
        tft.print(",");
        tft.print(p.y);
        valBright = map(p.x, 0, 120, 255, 25);
        backLight(valBright);
        tft.drawCircle(p.x, p.y,3, ST7735_GREEN);
      }
    }
    delay(30);
  }
}
