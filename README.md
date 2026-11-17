# CoreWatch-Telemetry

A lightweight, zero-overhead external hardware telemetry and thermal warning monitor built with Python, Arduino, and an SSD1306 OLED display. Designed to track real-time system metrics without consuming on-screen real estate (OSD) or affecting system performance during heavy workloads and gaming.

## Key Features
* **100% Verified Hardware Metrics:** Filters out OS-level ACPI sensor locks and hybrid core clock reporting inaccuracies, streaming strictly reliable metrics (`GPU Temp`, `GPU Utilization`, `GPU Power Draw`, `CPU Load`, `RAM Usage`, and `Battery Level`).
* **Zero-Dependency Execution:** Requires no third-party background monitoring bridges (e.g., HWiNFO, RivaTuner). Polls hardware data directly via `nvidia-smi` and `psutil`.
* **Fault Tolerance (Watchdog Timer):** Includes a 3-second serial timeout mechanism. If the host Python agent stops or USB communication drops, the hardware automatically clears the screen and switches to a custom standby splash screen.
* **Analog PWM Thermal Feedback:** Modulates a Common Cathode RGB LED based on real-time GPU thermal thresholds:
  * **Green:** `< 50°C` (Idle / Optimal)
  * **Blue:** `50°C – 75°C` (Moderate Load)
  * **Red:** `> 75°C` (High Thermal Load Warning)

---

## Bill of Materials (Required Hardware)
* **1x** Arduino Uno (or ATmega328P compatible board)
* **1x** 0.96" SSD1306 I2C OLED Display (128x64 pixels, `0x3C` address)
* **1x** Common Cathode RGB LED (4-pin)
* **3x** 220Ω or 330Ω Resistors (for current limiting on RGB channels)
* **1x** Breadboard & Jumper Wires (Male-to-Male, Male-to-Female)
* **1x** USB Data Cable (Type-A to Type-B)

---

## Hardware Wiring & Pinout

| Component | Component Pin | Arduino Uno Pin | Notes |
| :--- | :--- | :--- | :--- |
| **SSD1306 OLED** | `VCC` | `5V` | Power |
| | `GND` | `GND` | Ground |
| | `SDA` | `A4` | I2C Data |
| | `SCL` | `A5` | I2C Clock |
| **RGB LED** | `Longest Pin` | `GND` | Common Cathode |
| *(Common Cathode)* | `Red` | `Pin 9` (PWM) | Via 220Ω resistor |
| | `Green` | `Pin 10` (PWM) | Via 220Ω resistor |
| | `Blue` | `Pin 11` (PWM) | Via 220Ω resistor |

---

## Software Installation & Setup

### 1. Microcontroller Setup (Arduino)
1. Install the **Arduino IDE** on your system.
2. Open the Library Manager (`Ctrl + Shift + I`) and install the following libraries:
   * `Adafruit GFX Library`
   * `Adafruit SSD1306`
3. Open `CoreWatch-Telemetry.ino`, select your board (**Arduino Uno**) and active **COM Port**, then click **Upload**.
4. Once uploaded, the OLED screen will display the standby monitor icon and `STANDBY...` text.

### 2. Host Agent Setup (Python)
1. Ensure **Python 3.x** is installed and added to your system PATH.
2. Open your terminal/command prompt and install the required dependencies:
   ```bash
   pip install pyserial psutil
