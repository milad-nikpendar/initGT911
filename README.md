# initGT911 v1.0.0 Touch Library

[![Arduino Library Manager](https://img.shields.io/badge/Arduino-Library_Manager-00979D.svg?logo=arduino&logoColor=white)](https://docs.arduino.cc/libraries/initGT911/)
[![License: MIT](https://img.shields.io/badge/License-MIT-yellow.svg)](https://opensource.org/licenses/MIT)
[![GitHub release](https://img.shields.io/github/v/release/milad-nikpendar/initMemory)](https://github.com/milad-nikpendar/initGT911/releases)
[![Author](https://img.shields.io/badge/Author-milad--nikpendar-blueviolet)](https://github.com/milad-nikpendar)

A complete Arduino-compatible driver for the **Goodix GT911 capacitive touch controller**, supporting **Arduino**, **ESP8266**, and **ESP32** boards.  
Includes functions for initialization, touch point reading, interrupt handling, and display configuration.

---

## 📦 Installation

1. Clone or download this repository:
   ```bash
   git clone https://github.com/milad-nikpendar/initGT911.git
   ```
2. Copy the folder to your Arduino `libraries` directory.
3. Restart the Arduino IDE.
4. Alternatively, use **Sketch → Include Library → Add .ZIP Library** if you downloaded the ZIP.

---

## ⚡ Hardware Setup

| GT911 Pin | Connects To |
|-----------|-------------|
| SDA       | SDA (I2C)   |
| SCL       | SCL (I2C)   |
| INT       | Digital pin for interrupt |
| RST       | Digital pin for reset     |
| VCC       | 3.3V        |
| GND       | GND         |

> **Note:** The GT911 operates at **3.3V** logic.

---

## 🛠 Usage

### 1. Include the library
```cpp
#include <Wire.h>
#include "initGT911.h"
```

### 2. Create an instance
```cpp
initGT911 touch(&Wire, GT911_I2C_ADDR_5D); // or GT911_I2C_ADDR_28
```

### 3. Initialize in `setup()`
```cpp
void setup() {
  Serial.begin(115200);
  if (touch.begin(INT_PIN, RST_PIN, 400000)) {
    Serial.println("GT911 Initialized!");
  } else {
    Serial.println("GT911 Not Found!");
  }
}
```

### 4. Read touch points
```cpp
void loop() {
  uint8_t touches = touch.touched(GT911_MODE_INTERRUPT);
  if (touches > 0) {
    for (uint8_t i = 0; i < touches; i++) {
      GTPoint p = touch.getPoint(i);
      Serial.printf("Touch %d: X=%d, Y=%d\n", i, p.x, p.y);
    }
  }
}
```

---

## 📚 Key Functions

| Function | Description |
|----------|-------------|
| `begin(intPin, rstPin, clk)` | Initializes the GT911 with interrupt and reset pins |
| `touched(mode)` | Returns the number of touch points detected |
| `getPoint(num)` | Returns coordinates of a specific touch point |
| `getPoints()` | Returns array of all detected touch points |
| `readConfig()` | Reads current configuration from GT911 |
| `updateConfig()` | Updates GT911 configuration |
| `setupDisplay(xRes, yRes, rotation)` | Sets display resolution and rotation |

---

## 📜 License

This project is licensed under the **MIT License** – see [LICENSE](LICENSE) for details.

---

## ✍️ Author

**Milad Nikpendar**  
GitHub: [milad-nikpendar/initGT911](https://github.com/milad-nikpendar/initGT911)  
Email: milad82nikpendar@gmail.com  
