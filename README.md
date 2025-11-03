# Smart Footwear – IoT Based Assistive Walking System

[![Status](https://img.shields.io/badge/status-active-brightgreen)](#) [![License: MIT](https://img.shields.io/badge/License-MIT-blue.svg)](#license) [![Platform](https://img.shields.io/badge/platform-Arduino%20%7C%20ESP8266%20%7C%20IoT-orange)](#software-components)

TS. Srinivasan Polytechnic College • Vanagaram, Chennai, Tamil Nadu 600095

Guide: Mrs. S. P. Chitra (HOD)

---

## 📘 About the Project

Smart Footwear is an IoT-based assistive walking system designed to enhance mobility and safety for visually impaired individuals. By integrating ultrasonic sensing, haptic feedback, and real-time alerts, the system helps users detect obstacles, avoid hazards, and navigate more confidently in indoor and outdoor environments.

- Problem Statement: Visually impaired users face difficulty detecting obstacles at foot level and above knee height, leading to accidents and reduced independence.
- Objective: Build a compact, wearable, and affordable system that detects obstacles and provides timely feedback using vibration and audio cues.
- Purpose: Improve safety, autonomy, and confidence during daily walking and navigation.

---

## ⚙️ Features

| # | Feature | Description |
|---|---|---|
| 1 | Multi-Zone Obstacle Detection | Dual ultrasonic sensors for near (toe) and mid-level (knee) detection |
| 2 | Haptic Feedback | Vibration motor intensity scales with obstacle proximity |
| 3 | Audio Alerts | Optional buzzer/earpiece feedback for critical warnings |
| 4 | Smart Thresholds | Configurable distance thresholds with debounce filtering |
| 5 | Low Power | Sleep mode and efficient power management |
| 6 | IoT Connectivity | ESP8266/ESP32 for logging and optional remote assistance |
| 7 | Environmental Sensing | Optional LDR/IMU for ambient light and tilt detection |
| 8 | Compact & Wearable | Lightweight, shoe-mounted enclosure |
| 9 | Safety First | Short-circuit and polarity protection |
| 10 | Open Source | Fully documented hardware and code for reproducibility |

---

## 🧩 System Architecture

```
+---------------------------------------------------------------+
|                        Smart Footwear                         |
+-------------------------+-------------------+-----------------+
|  Sensing Layer          |  Control Layer    |  Feedback Layer |
|-------------------------+-------------------+-----------------|
| - Ultrasonic (HC-SR04)  | - Arduino/ESP8266 | - Vibration     |
| - Optional IMU (MPU6050)| - Debounce/Logic  | - Buzzer        |
| - LDR (optional)        | - WiFi (MQTT/HTTP)| - LED Indicator |
+-------------------------+-------------------+-----------------+
|                Power Mgmt: 18650 Li-ion + 5V Regulator        |
+-------------------------+-------------------------------------+
|                Cloud/Companion App (optional)                 |
|   - Data Logs  - Alerts  - Remote Assist  - Calibration       |
+---------------------------------------------------------------+
```

---

## 🔩 Hardware Components

| Component | Specification | Qty | Notes |
|---|---|---:|---|
| Microcontroller | Arduino Nano / ESP8266 (NodeMCU) | 1 | Choose based on IoT need |
| Ultrasonic Sensor | HC-SR04 (2–400 cm, 40 kHz) | 1–2 | Toe and knee zones |
| Vibration Motor | 3V–5V ERM coin motor | 1 | PWM control for intensity |
| Buzzer (optional) | 5V passive/active | 1 | Audio warnings |
| Power Source | 18650 Li-ion + TP4056 + Boost 5V | 1 | With protection board |
| Regulator | AMS1117-5.0 / Buck module | 1 | Stable 5V output |
| Switch | SPDT toggle/slide | 1 | Master power |
| Enclosure | 3D printed/ABS case | 1 | Shoe-mounted |
| Wiring | DuPont/jumper wires | - | Secure with heat-shrink |

---

## 💻 Software Components

- Arduino IDE 2.x
- Core: AVR (Nano) or ESP8266/ESP32
- Libraries: NewPing (ultrasonic), ESP8266WiFi/ESP32 WiFi, PubSubClient (MQTT), Wire, I2Cdev (optional for IMU)
- Protocols: MQTT or HTTP (optional cloud logging)
- Version Control: Git + GitHub

---

## 🔌 Circuit & Arduino Code

Basic wiring (Arduino Nano example):
- HC-SR04 (Front): Trig → D3, Echo → D4, Vcc → 5V, GND → GND
- Vibration Motor: + → D9 (via NPN + diode), – → GND
- Buzzer (optional): + → D10, – → GND

```cpp
// Smart Footwear – Minimal Obstacle Alert (Arduino Nano)
// Uses NewPing for stable ultrasonic readings and PWM for haptics
#include <NewPing.h>

// Pins
const uint8_t TRIG_PIN = 3;
const uint8_t ECHO_PIN = 4;
const uint8_t VIBE_PIN = 9;
const uint8_t BUZZ_PIN = 10; // optional

// Ranges
const unsigned int MAX_DIST_CM = 200;   // sensor max range
const unsigned int WARN_DIST_CM = 80;   // start warning
const unsigned int DANGER_DIST_CM = 35; // strong feedback

NewPing sonar(TRIG_PIN, ECHO_PIN, MAX_DIST_CM);

uint16_t smooth(uint16_t prev, uint16_t curr, float a = 0.6) {
  return (uint16_t)(a * prev + (1 - a) * curr);
}

void setup() {
  pinMode(VIBE_PIN, OUTPUT);
  pinMode(BUZZ_PIN, OUTPUT);
}

void loop() {
  static uint16_t d = MAX_DIST_CM;
  delay(40); // ~25 Hz
  unsigned int cm = sonar.ping_cm();
  if (cm == 0) cm = MAX_DIST_CM; // no echo → assume far
  d = smooth(d, cm);

  uint8_t pwm = 0;
  if (d <= DANGER_DIST_CM) {
    pwm = 230;                // strong vibration
    tone(BUZZ_PIN, 2000, 60); // short beep
  } else if (d <= WARN_DIST_CM) {
    // map distance to PWM (nearer → stronger)
    pwm = map(d, WARN_DIST_CM, DANGER_DIST_CM, 90, 220);
    noTone(BUZZ_PIN);
  } else {
    pwm = 0;
    noTone(BUZZ_PIN);
  }
  analogWrite(VIBE_PIN, pwm);
}
```

---

## 🧭 Installation & Usage

1. Clone the repository and open the sketch in Arduino IDE.
2. Install libraries via Library Manager: "NewPing", optionally "ESP8266WiFi" and "PubSubClient".
3. Select the correct Board (Arduino Nano/ESP8266) and COM port.
4. Wire components as per the circuit and upload the code.
5. Calibrate thresholds (WARN_DIST_CM, DANGER_DIST_CM) for your environment.
6. Mount the enclosure on the shoe toe area; secure cables and ensure weather protection.
7. Power on, test vibration intensity versus distance, and iterate placement.

---

## 📊 Results & Analysis

| Test ID | Scenario | Thresholds (cm) | Avg. Detection (cm) | Latency (ms) | Outcome |
|---:|---|---:|---:|---:|---|
| T1 | Indoor corridor, static obstacles | 80/35 | 78 | 60 | Accurate warnings |
| T2 | Outdoor pavement, moving obstacles | 80/35 | 74 | 65 | Reliable, minimal false alarms |
| T3 | Bright sunlight (sensor glare) | 80/35 | 85 | 62 | Slight overrange handled by smoothing |
| T4 | Soft surfaces (cloth/curtain) | 80/35 | 70 | 68 | Detectable with reduced echo strength |

Notes: Results are illustrative; calibrate per user gait and environment.

---

## 🚀 Future Enhancements

- Dual-sensor fusion (toe + chest-level) with priority logic
- BLE audio feedback to bone-conduction headset
- Mobile app for calibration and analytics
- IMU-based step counting and terrain classification
- IP54-rated enclosure and flexible PCB design
- Battery fuel gauge and USB-C charging

---

## 👥 Team & Guide

- College: T.S. Srinivasan Polytechnic College, No.1, TVS School St, Vanagaram, Chennai, Tamil Nadu 600095
- Guide: Mrs. S. P. Chitra (HOD)
- Project Members:
  - V. Sriram (20700398)
  - R. Siranjeevee (20700397)
  - G. Varun (20700400)
  - J. C. Kuber (20700373)
  - V. Venkat Charan (20700401)
  - Yashwantha Sai G.K (20700406)

---

## 🙏 Acknowledgment

We sincerely thank our guide, Mrs. S. P. Chitra (HOD), for guidance and mentorship throughout this project. We also acknowledge the support of T.S. Srinivasan Polytechnic College for lab access and resources.

---

## 🪪 License

This project is licensed under the MIT License — see the License section below for details.

```
MIT License

Copyright (c) 2025 Smart Footwear Team

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
```

---

## 🏷️ Badges

- Status: Active — Project is under development and open for contributions
- License: MIT — Free to use and modify
- Platform: Arduino / ESP8266 / IoT
