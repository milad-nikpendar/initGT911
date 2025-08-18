#include <Wire.h>
#include "initGT911.h"

// I2C pins and frequency
#define I2C_SDA 21
#define I2C_SCL 22
#define I2C_FREQ 400000

// GT911 I2C address
#define TOUCH_ADDR GT911_I2C_ADDR_5D // or GT911_I2C_ADDR_28

// Reset and INT pins (set to -1 if unused)
#define RST_PIN  18
#define INT_PIN  -1  // not used in polling mode

// Create GT911 object
initGT911 Touchscreen(&Wire, TOUCH_ADDR);

void setup() {
  Serial.begin(115200);
  delay(100);

  // Initialize I2C
  Wire.begin(I2C_SDA, I2C_SCL, I2C_FREQ);

  // Initialize GT911 in polling mode
  if (Touchscreen.begin(INT_PIN, RST_PIN, I2C_FREQ)) {
    Serial.println("GT911 initialized in polling mode");
    Touchscreen.setupDisplay(800, 480, initGT911::Rotate::_0); // example resolution
  } else {
    Serial.println("Failed to initialize GT911");
  }
}

void loop() {
  // In polling mode, we pass GT911_MODE_POLLING
  uint8_t touchCount = Touchscreen.touched(GT911_MODE_POLLING);

  if (touchCount > 0) {
    for (uint8_t i = 0; i < touchCount; i++) {
      GTPoint p = Touchscreen.getPoint(i);
      Serial.printf("Touch %d: X=%d, Y=%d\n", i, p.x, p.y);
    }
  }

  delay(20); // Small delay to reduce bus load
}
