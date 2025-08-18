#include <Wire.h>
#include "initGT911.h"

// I2C pins/frequency (adjust for your board)
#define I2C_SDA   21
#define I2C_SCL   22
#define I2C_FREQ  400000

// GT911 I2C address (choose one based on your wiring)
#define TOUCH_ADDR  GT911_I2C_ADDR_5D  // or GT911_I2C_ADDR_28

// GT911 pins
#define INT_PIN   19   // must be interrupt-capable
#define RST_PIN   18   // set to -1 if not connected

// Display resolution (match your panel)
#define TFT_HOR_RES  800
#define TFT_VER_RES  480

initGT911 Touchscreen(&Wire, TOUCH_ADDR);

void setup() {
  Serial.begin(115200);
  delay(50);

  // Init I2C
  Wire.begin(I2C_SDA, I2C_SCL, I2C_FREQ);

  // Init GT911 (interrupts are handled INSIDE the library)
  if (Touchscreen.begin(INT_PIN, RST_PIN, I2C_FREQ)) {
    Serial.println("GT911 initialized (interrupt mode).");
    Touchscreen.setupDisplay(TFT_HOR_RES, TFT_VER_RES, initGT911::Rotate::_0);
  } else {
    Serial.println("GT911 not found.");
  }
}

void loop() {
  // Library checks the internal IRQ flag; no external ISR/attachInterrupt needed
  uint8_t count = Touchscreen.touched(GT911_MODE_INTERRUPT);

  if (count > 0) {
    for (uint8_t i = 0; i < count; i++) {
      GTPoint p = Touchscreen.getPoint(i);
      Serial.printf("Touch %u: X=%u, Y=%u\n", i, p.x, p.y);
    }
  }

  // Light idle to avoid busy-waiting
  delay(5);
}
