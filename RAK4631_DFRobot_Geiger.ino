/*!
  @file geiger.ino
  @brief Adapted from the DFRobot code for RAK4631
  @copyright   Copyright (c) 2022 Kongduino
  @licence     The MIT License (MIT)
  @author Kongduino
  @version  V1.0
  @date  2022/03/21
  @get Geiger Counter from https://www.dfrobot.com
  @get RAK4631 from https://store.rakwireless.com
  @https://github.com/Kongduino/RAK4631_DFRobot_Geiger
*/

#include <Adafruit_TinyUSB.h>
#include <DFRobot_Geiger.h>

/*!
   @brief Constructor
   @param pin External interrupt pin
*/
#define detect_pin WB_IO1
DFRobot_Geiger geiger(detect_pin);
char buff[128];
double lastRecord;
#define DELAY 3000

void setup() {
  Serial.begin(115200);
  // Start measuring
  geiger.start();
  lastRecord = millis();
}

void loop() {
  double t0 = millis();
  if (t0 - lastRecord > DELAY) {
    // Get the current CPM. If measuring was suspended, CPM is the last value before suspension.
    // Predict CPM by falling edge pulse within 3 seconds, the error ratio is ±3 CPM.
    uint16_t cpm = geiger.getCPM();
    uint16_t nSvh = geiger.getnSvh();
    float uSvh = geiger.getuSvh();
    sprintf(buff, "CPM: %d nSvh: %d uSvh: ", cpm, nSvh);
    Serial.print(buff);
    Serial.println(uSvh);
    lastRecord = millis();
  }
}
