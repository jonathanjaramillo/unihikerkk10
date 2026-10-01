// Prints joystick axes and button events from the I2C game controller.
// Copy into a PlatformIO project's src/ (or build via `pio ci`).
#include <Arduino.h>
#include <Wire.h>
#include <GameController.h>

GameController controller;

void setup() {
  Serial.begin(115200);
  // K10 shared I2C bus: SDA GPIO47, SCL GPIO48.
  Wire.begin(47, 48);
  controller.begin(Wire);  // default address 0x5A
}

void loop() {
  uint8_t x, y;
  if (controller.readAxes(x, y)) {
    Serial.printf("axes x=%u y=%u\n", x, y);
  } else {
    Serial.println("controller not responding");
  }

  for (uint8_t i = 0; i < GameController::BUTTON_COUNT; ++i) {
    uint8_t event;
    if (controller.readButtonEvent((GameController::Button)i, event) &&
        event != GameController::NONE_PRESS) {
      Serial.printf("button %u event %u\n", i, event);
    }
  }
  delay(50);
}
