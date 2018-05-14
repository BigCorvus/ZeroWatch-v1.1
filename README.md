# ZeroWatch-v1.1
![alt text](https://github.com/BigCorvus/ZeroWatch-v1.1/blob/master/Pics/20180513_183945.jpg)

**Replacement board for a cheap chinese U8/U80 watch.**
Based on the work of Dan Geiger.
Features:<br />
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
It's quite raw and buggy but demonstrates most features and is optimized for power consumption. With the 403030 lipo I can get 8 days of standby time with bluetooth constantly advertising and the ATSAMD21's inbuilt RTC running.<br />

**Some tips if you want to repeat the project:  **
-The cheapest versions of the U8 are so stripped-down that they are not useful anymore! They have their capacitive touch controller on the main PCB an not on a flex-rigid assembly. I found the U80 by NAIKU to be a good hacking victim. Search this on Aliexpress. Its design is slightly different to the U8 from the outside but from the inside everything fits. Note: the U8 by the same brand is useless.  
![alt text](https://github.com/BigCorvus/ZeroWatch-v1.1/blob/master/Pics/20180514_083215.jpg)  
The pic shows some useless variants on the right and some hackable ones on the left (with their 6pin FPC connectors desoldered for the most part). As you can see,on the useless variants there's no touch controller on the ribbon cable but a 15pin FPC connector with nothing but the traces to the glass. Also, v1.0 and v1.2's bare PCB are depicted ;)  

-Finding a proper screen might be a problem. 18 pin versions of the 1.44'' ST7735/ILI9163 screen with the right dimensions are rare. In fact I've only found one source: https://de.aliexpress.com/item/Maithoga-1-44-zoll-18-PIN-SPI-TFT-LCD-St7735-Stick-IC-128RGB-128/32843155779.html?spm=a2g0s.9042311.0.0.27424c4d3j1YYo. Some screens found in the cheap U8/U80 watches have weird controller settings and dispay inverted colors or don't show the small fonts so be aware. You might need to buy several differen variants. Note: only 14 of the 18 pins have to be soldered to the PCB.  
-some modifications on the enclosure are needed. In order to accommodate the v1.1 board you have to cut away the plastic brackets that surround the microphone. I decided to go with https://de.aliexpress.com/item/Free-shipping-100pcs-lot-4-10-MM-Ultra-Micro-Vibration-Motor-Rotor-motor-DC-Massager-motor/32748925343.html?spm=a2g0s.9042311.0.0.27424c4dg2oSdt as the vibration motor to save space for a bigger battery. This is best done usind electronics side cutters. Some other plastic tabs might need to be removed depending on the variant you have. But the enclosures are surprisingly similar with few variations between versions.  
-The button can be installed either using the native one or by installing a SW1256CT-ND switch (digikey). The latter requires some hacking to the enclosure  
-a small hole has to be drilled for the IR LED if you wish to use one.
-the HM-11 should be flashed with the newest firmware before installing on the v1.1 PCB.   



