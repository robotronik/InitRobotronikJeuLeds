# 🕹️ InitRobotronikJeuLEDs

A fast-paced, 2-player LED tug-of-war arcade game built on ESP32 and WS2812B addressable NeoPixel LED strips for Robotronik.

---

## 📖 Overview

Two players compete in a button-mashing duel. Each player rapidly mashes their button to push their beam of light across the strip. 
- **Player 1** starts from the beginning of the strip (Green).
- **Player 2** starts from the end of the strip (Red).

### Game Phases
1. **Advance Phase**: Both players race to meet in the middle (`nLeds1 + nLeds2 < TOTAL_LEDS`).
2. **Confrontation Phase (Tug-of-War)**: Once the beams collide, a tug-of-war begins. The faster player pushes back the opponent's light by the speed differential.
3. **Victory**: The first player to conquer the entire strip (240 LEDs) wins, triggering a celebratory flashing light animation.

---

## 🛠️ Hardware Requirements

| Component | Description | ESP32 GPIO |
|---|---|---|
| **Microcontroller** | NodeMCU-32S (ESP32) | — |
| **LED Strip** | WS2812B NeoPixel (240 LEDs) | `GPIO 16` |
| **Player 1 Button** | Normally-Open Push Button (Active LOW) | `GPIO 17` |
| **Player 2 Button** | Normally-Open Push Button (Active LOW) | `GPIO 5` |
| **Power Supply** | 5V external power supply (≥ 5A recommended for 240 LEDs) | — |

> [!IMPORTANT]
> **Electrical Precautions for NeoPixels:**
> - Connect a **1000 µF capacitor** across the `5V` and `GND` power leads of the strip.
> - Place a **300–500 Ω resistor** in series between `GPIO 16` and the `DIN` pin of the LED strip.
> - Ensure **common ground (`GND`)** is connected between the ESP32 and the external 5V power supply.

---

## ⚙️ Software Architecture

```
InitRobotronikJeuLEDs/
├── platformio.ini         # PlatformIO environment config (ESP32, NeoPixel lib)
├── include/
│   ├── main.h             # Pin assignments, game timing, debounce & LED count constants
│   └── functions.h        # Strip control & rendering function prototypes
└── src/
    ├── main.c             # Interrupt service routines, speed calculation & game loop
    └── functions.c        # NeoPixel rendering, color wheels & victory animations
```

### Key Technical Details

- **Hardware Interrupts**: Buttons are handled via hardware interrupts (`attachInterrupt(..., FALLING)`) with non-blocking software debouncing (`DEBOUNCE_DELAY = 50ms`), keeping the main loop responsive and ensuring no button presses are missed.
- **Speed Calculation**: Tapping speed is calculated using a rolling moving average buffer over a 1-second window (`MEAN_INTERVAL = 200ms`, 5 samples).
- **Tug-of-War Dynamics**: When beams meet, progress is determined by the speed difference (`speed1 - speed2`), with underflow clamping to protect unsigned LED counters.

---

## 🚀 Getting Started

### Prerequisites
- [PlatformIO](https://platformio.org/) (via VS Code Extension or CLI).

### Build and Upload

1. Clone the repository:
   ```bash
   git clone https://github.com/votre-compte/InitRobotronikJeuLEDs.git
   cd InitRobotronikJeuLEDs
   ```

2. Build the project:
   ```bash
   pio run
   ```

3. Upload to ESP32:
   ```bash
   pio run -t upload
   ```

4. Open Serial Monitor (optional, 9600 baud):
   ```bash
   pio device monitor -b 9600
   ```

---

## ⚙️ Configuration Parameters

All tunable parameters are located in [`include/main.h`](include/main.h):

| Constant | Default | Description |
|---|---|---|
| `TOTAL_LEDS` | `240` | Total number of LEDs on the strip |
| `MEAN_INTERVAL` | `200` | Loop calculation period in milliseconds (5 Hz) |
| `LED_PER_SPEED` | `1.0` | Sensitivity factor converting speed to LED increments |
| `DEBOUNCE_DELAY` | `50` | Button debounce window in milliseconds |
| `BT_1_PIN` | `17` | GPIO pin for Player 1 button |
| `BT_2_PIN` | `5` | GPIO pin for Player 2 button |
| `PIN` | `16` | GPIO pin for NeoPixel data line |
