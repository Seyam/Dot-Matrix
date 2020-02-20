#include <SPI.h>
#include "LedMatrix.h"

#define NUMBER_OF_DEVICES 1
#define CS_PIN 4 //it means GPIO4=D2
LedMatrix ledMatrix = LedMatrix(NUMBER_OF_DEVICES, CS_PIN);

void setup() {
  Serial.begin(9600); // For debugging output
  ledMatrix.init();
  ledMatrix.setIntensity(4); // range is 0-15
  ledMatrix.setText("Hello");
}

void loop() {
  ledMatrix.clear();
  ledMatrix.scrollTextLeft();
  ledMatrix.drawText();
  ledMatrix.commit(); // commit transfers the byte buffer to the displays
  delay(200);
}
