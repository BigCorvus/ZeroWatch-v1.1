void appTremor(){
   boolean exitOut = false;
  TS_Point p;
tft.fillScreen(BLACK);
  tft.setCursor(5, 10);
  tft.setTextColor(GREEN, BLACK);
  tft.setTextSize(1);
  tft.println(" ** Tremor **");

  int t=0;
while (!exitOut) {
    if (ctp.touched()) {
      p = ctp.getPoint();
      if (p.y > 128 & p.x > (tft.width() / 3)*2 ){ //the back button
       
        tone(SPKR, 500, 70);
       
        exitOut = true;
      }
    
  delay(10);
    }

}
  
}//Tremor

