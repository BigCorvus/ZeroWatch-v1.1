# ZeroWatch-v1.1
![alt text](https://github.com/BigCorvus/ZeroWatch-v1.1/blob/master/Pics/20180513_183945.jpg)

Replacement board for a cheap chinese U8/U80 watch.
Based on the work of Dan Geiger.
Features:
-ATSAMD21 microcontroller with Arduino support via USB bootloader<br />
-capacitive touchscreen (based on the BL6280 controller)<br />
-HM11 bluetooth 4.0 module with amputated PCB antenna and primitive coax dipole instead<br />
-ST7735 128x128 18-pin SPI tft (the one that's inside the watch already)<br />
-MPU9250 9-DOF IMU<br />
-BME680 environmental sensor<br />
-vibration motor<br />
-infrared transmitter (APA3010F3C-GX LED)<br />
-piezo disc (optional)<br />
-I equipped mine with a QI inductive charging pad<br />

The software is based on Dan Geigers ingenious menu structure which enables you to add new apps easily.
It's quite raw and buggy but demonstrates most features and is optimized for power consumption. With the 403030 lipo I can get 8 days of standby time with bluetooth constantly advertising and the ATSAMD21's inbuilt RTC running.


