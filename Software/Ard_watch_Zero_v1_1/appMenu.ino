//----------------------------
// Draw the App Menu
//----------------------------

uint8_t appMenu(void) {

  uint8_t curSel = 0;
  TS_Point p;

  tft.fillScreen(BLACK);

  tft.drawFastVLine( 98, 0, 128, BLUE);
  tft.fillTriangle(104, 44, 104, 84, 127, 64, CYAN);

  showMenu(curSel);

  while (1) {

    if (ctp.touched()) {   
      //Touched = false;     
      p = ctp.getPoint();
       if (p.x > 96) return curSel;
     if (p.y > 64) {      
        curSel ++;
         if (curSel > maxApp) curSel = 0;         
      } 
      if (p.y < 64){
        if (curSel == 0) curSel = maxApp;
        else curSel --;  
      }
      // tft.drawCircle(p.x, p.y,15, ST7735_GREEN);      
      showMenu(curSel);      
    }
    delay(30); //delay otherwise
  }
}
    //{"Clock", "Remote", "Status", "Set T", "Bright", "Level"};
void showMenu(uint8_t mnuItem) {

  tft.fillRect(0, 0, 95, 127, BLACK);
  tft.fillRoundRect(5, 44, 91, 40,5, BLUE);
 tft.fillTriangle(82, 10, 73, 24, 92, 24, CYAN);
  tft.fillTriangle(82, 118, 73, 104, 92, 104, CYAN);
  
  tft.setCursor(10, 16);
  tft.setTextColor(GREEN, BLACK);
  tft.setTextSize(1);
  if (mnuItem == 0) tft.print(appName[maxApp]);
  else tft.print(appName[mnuItem - 1]);

  tft.setCursor(10, 110);
  if (mnuItem == maxApp) tft.print(appName[0]);
  else tft.print(appName[mnuItem + 1]);

  tft.setCursor(10, 54);
  tft.setTextColor(WHITE, BLUE);
  tft.setTextSize(2);
  tft.print(appName[mnuItem]);
}

