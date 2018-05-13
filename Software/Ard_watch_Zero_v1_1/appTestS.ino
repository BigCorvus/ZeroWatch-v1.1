//----------------------------
// Print BME680 and MPU9250 data
//----------------------------

void appTestS() {
  int dX, dY = 63;

  tft.fillScreen(BLACK);
tft.setCursor(0, 3);
  
  tft.setTextSize(1);
 // tft.drawRect(10, 10, 107, 107, BLUE);
 basicIMUsetup();
basicBMEsetup();
  delay(200);
  /*
myIMU.initAK8963(myIMU.factoryMagCalibration);
 // Get sensor resolutions, only need to do this once
    myIMU.getAres();
    myIMU.getGres();
    myIMU.getMres();

    // The next call delays for 4 seconds, and then records about 15 seconds of
    // data to calculate bias and scale.
    myIMU.magCalMPU9250(myIMU.magBias, myIMU.magScale);
    */
  while (!ctp.touched()) {
    /*
     tft.fillScreen(BLACK);
    tft.setCursor(0, 3);
    pressure = myPressure.readPressure();
  ipress = pressure;
  temperature = myPressure.readTemp();
  itemp = temperature;
  sprintf(pastring, "%3d", ipress);
  sprintf(tmpstring, "%3d", itemp);
  float altitude = myPressure.readAltitude();
  tft.print(" Altitude(m):");
  tft.println(altitude);
  tft.print("Pressure(Pa):");
  tft.println(pastring);
  tft.print(" Temp(C):");
  tft.println(tmpstring);
  delay(200);
  */
  
          tft.fillScreen(BLACK);
          tft.setTextColor(GREEN);
    tft.setCursor(0, 3);
   if (! bme.performReading()) {
   tft.println("Failed:");
    return;
  }
  tft.print("Temp=");
  tft.print(bme.temperature);
  tft.println("*C");

  tft.print("Pres=");
  tft.print(bme.pressure / 100.0);
  tft.println("hPa");

  tft.print("Hum=");
  tft.print(bme.humidity);
  tft.println("%");

  tft.print("Gas=");
  tft.print(bme.gas_resistance / 1000.0);
  tft.println("KOhm");

  tft.print("Alt=");
  tft.print(bme.readAltitude(SEALEVELPRESSURE_HPA));
  tft.println("m");

  //tft.println();
 
  

    /*
    stepCount = imu.dmpGetPedometerSteps();
  stepTime = imu.dmpGetPedometerTime();
  
  if (stepCount != lastStepCount)
  {
    lastStepCount = stepCount;
    
               tft.setTextSize(1);
  tft.setCursor(30, 20);
  tft.print("Walked " + String(stepCount) + 
                     " steps");
                     tft.print(" (" + 
              String((float)stepTime / 1000.0) + " s)");
            
  } 
   */

  
   
  if ( digitalRead(AINT) == LOW )
  {
    // Call update() to update the imu objects sensor data.
    imu.update(UPDATE_ACCEL | UPDATE_GYRO | UPDATE_COMPASS);
    printIMUData();
  }

  
  
  delay(500); 
/*
  byte c = myIMU.readByte(MPU9250_ADDRESS, WHO_AM_I_MPU9250);
tft.print("MPU9250 I AM 0x");
  tft.print(c);
  tft.print(" I should be 0x");
  tft.println("0x71"); */
  }//touched

}


void printIMUData(void)
{  
 // After calling update() the ax, ay, az, gx, gy, gz, mx,
  // my, mz, time, and/or temerature class variables are all
  // updated. Access them by placing the object. in front:

  // Use the calcAccel, calcGyro, and calcMag functions to
  // convert the raw sensor readings (signed 16-bit values)
  // to their respective units.
  float accelX = imu.calcAccel(imu.ax);
  float accelY = imu.calcAccel(imu.ay);
  float accelZ = imu.calcAccel(imu.az);
  float gyroX = imu.calcGyro(imu.gx);
  float gyroY = imu.calcGyro(imu.gy);
  float gyroZ = imu.calcGyro(imu.gz);
  float magX = imu.calcMag(imu.mx);
  float magY = imu.calcMag(imu.my);
  float magZ = imu.calcMag(imu.mz);
     // tft.setCursor(0, 64);
tft.setTextColor(CYAN);
  tft.println("Accel: ");
  tft.println(String(accelX) + "," + String(accelY) + "," + String(accelZ) + "g");
  tft.println("Gyro: ");
  tft.println(String(gyroX) + "," + String(gyroY) + "," + String(gyroZ) + "dps");
  tft.println("Mag: " );
  tft.println(String(magX) + "," + String(magY) + "," + String(magZ) + "uT");
  tft.println("Time: " + String(imu.time) + " ms");
  tft.println();
}




