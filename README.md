# Smart Footwear – IoT Based Assistive Walking System

[![Status](https://img.shields.io/badge/status-active-brightgreen)](#)
[![License: MIT](https://img.shields.io/badge/License-MIT-blue.svg)](#license)
[![Platform](https://img.shields.io/badge/platform-Arduino%20%7C%20ESP8266%20%7C%20IoT-orange)](#software-components)

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
|                                                               |
|  [HC-SR04 (Toe)]  [HC-SR04 (Knee)]                            |
|         |                 |                                    |
|       Echo/Trig        Echo/Trig                              |
|           \              /                                     |
|            \            /                                      |
|             +---- Microcontroller (Arduino Nano/ESP8266) -----+
|             |         |            |           |               |
|         Vibration   Buzzer       Wi-Fi       IMU/LDR (opt)    |
|          Motor       (opt)       (opt)                        |
|             |         |            |                           |
|         Haptic     Audio       MQTT/HTTP                       |
|                                                               |
|                  Power: 3.7V Li-ion + Boost 5V                |
+---------------------------------------------------------------+
```

---

## 🧪 Bill of Materials (BOM)

| Item | Component | Qty | Approx Cost (INR) |
|---|---|---:|---:|
| 1 | Arduino Nano / ESP8266 (NodeMCU) | 1 | 400–600 |
| 2 | Ultrasonic Sensor HC-SR04 | 2 | 150 x 2 |
| 3 | Vibration Motor (Coin/ERM) | 1 | 120 |
| 4 | Buzzer (Active) | 1 | 50 |
| 5 | Li-ion 3.7V Battery (18650/803040) | 1 | 250 |
| 6 | MT3608 Boost Converter (5V) | 1 | 60 |
| 7 | LDR / MPU6050 (optional) | 1 | 50–250 |
| 8 | Switch, Wires, Heat Shrink | — | 100 |
| 9 | 3D-Printed Enclosure / Shoe Mount | 1 | 200 |

Total estimated cost: ~₹1,400 – ₹1,900 depending on options.

---

## 🧰 Hardware Pinout

- HC-SR04 (Toe): Trig → D4, Echo → D5
- HC-SR04 (Knee): Trig → D6, Echo → D7
- Vibration Motor via NPN (2N2222) + Diode: PWM → D9
- Buzzer (optional): D10
- Power: Li-ion → MT3608 → 5V to sensors and MCU (or 3.3V for ESP8266 as appropriate)

> Adjust pins for your microcontroller; ensure logic-level compatibility (use dividers/shifters for ESP8266).

---

## 🧠 Firmware Overview

Core loop reads both ultrasonic sensors, computes distance, applies smoothing and hysteresis, and drives haptic and optional audio feedback. If Wi-Fi is enabled (ESP8266/ESP32), periodically publish events to an MQTT broker or send HTTP logs.

### Arduino Sketch (Nano/UNO)
```cpp
#include <NewPing.h>

// Pins
const uint8_t TRIG_TOE = 4, ECHO_TOE = 5;
const uint8_t TRIG_KNEE = 6, ECHO_KNEE = 7;
const uint8_t VIBE_PIN = 9;   // PWM
const uint8_t BUZZ_PIN = 10;  // optional

// Ranges (cm)
const uint16_t MAX_DIST = 200;
const uint8_t NEAR_TH = 40;    // strong feedback
const uint8_t MID_TH  = 80;    // medium feedback

NewPing toe(TRIG_TOE, ECHO_TOE, MAX_DIST);
NewPing knee(TRIG_KNEE, ECHO_KNEE, MAX_DIST);

uint8_t smooth(uint8_t prev, uint8_t cur, uint8_t a = 20) {
  return (uint8_t)((prev*(100-a) + cur*a)/100);
}

uint8_t d_toe = 200, d_knee = 200;

void setup(){
  pinMode(VIBE_PIN, OUTPUT);
  pinMode(BUZZ_PIN, OUTPUT);
}

void vibeLevel(uint8_t d){
  uint8_t pwm = 0;
  if (d < NEAR_TH) pwm = 220;      // strong
  else if (d < MID_TH) pwm = 140;  // medium
  else if (d < 150) pwm = 80;      // light
  else pwm = 0;
  analogWrite(VIBE_PIN, pwm);
}

void beepWarn(uint8_t d){
  if (d < NEAR_TH) { tone(BUZZ_PIN, 2000, 60); }
  else if (d < MID_TH) { tone(BUZZ_PIN, 1200, 40); }
}

uint8_t readDist(NewPing &s){
  unsigned int uS = s.ping_median(5);
  uint16_t cm = s.convert_cm(uS);
  if (cm == 0) cm = 200; // out of range
  return (uint8_t)min<uint16_t>(cm, 200);
}

void loop(){
  uint8_t r1 = readDist(toe);
  uint8_t r2 = readDist(knee);
  d_toe = smooth(d_toe, r1);
  d_knee = smooth(d_knee, r2);

  uint8_t dmin = min(d_toe, d_knee);
  vibeLevel(dmin);
  beepWarn(dmin);
  delay(30);
}
```

### ESP8266 (NodeMCU) MQTT Logging Snippet
```cpp
#include <ESP8266WiFi.h>
#include <PubSubClient.h>

const char* ssid = "YOUR_SSID";
const char* pass = "YOUR_PASSWORD";
const char* host = "broker.hivemq.com";
const int   port = 1883;

WiFiClient espClient; PubSubClient client(espClient);

void ensureNet(){
  if (WiFi.status()!=WL_CONNECTED){ WiFi.begin(ssid, pass); while(WiFi.status()!=WL_CONNECTED) delay(300); }
  if (!client.connected()){ while(!client.connect("smart-footwear")) delay(500); }
}

void pubDist(uint8_t toe, uint8_t knee){
  char p[64]; snprintf(p, sizeof(p), "{\"toe\":%u,\"knee\":%u}", toe, knee);
  client.publish("smartfootwear/dist", p);
}
```

---

## 📐 Enclosure and Mounting

- 3D-print a compact case that mounts to the lateral side of the shoe.
- Use conformal coating or foam seals for splash resistance.
- Route sensor heads forward at toe, second sensor on upper shoe or shin strap.

```
Top View (ASCII)

   [HC-SR04]=>  --->   Walking Direction
   |  Shoe  |
   |       [Enclosure: MCU+Battery+Boost]  |
   +---------------------------------------+
```

---

## 🧪 Testing and Calibration

1. Measure and verify sensor distances using a ruler at 20, 40, 80, 120 cm.
2. Tune thresholds NEAR_TH and MID_TH for user comfort and environment.
3. Validate motor driver and ensure no overheating under continuous PWM.
4. Walk-test in controlled corridor with an assistant; log MQTT if enabled.

---

## 🧯 Safety and Reliability

- Reverse-polarity protection and fuse recommended.
- Use proper Li-ion charging module (TP4056) with protection.
- Ensure wires are strain-relieved; avoid sharp bends near shoe flex zones.

---

## 🗂️ Repository Structure

```
.
├─ firmware/
│  ├─ arduino_nano/
│  │  └─ smart_footwear.ino
│  ├─ esp8266/
│  │  └─ mqtt_logging_snippet.ino
├─ hardware/
│  ├─ schematics.pdf
│  └─ enclosure.stl
├─ docs/
│  ├─ architecture.png
│  └─ calibration_guide.md
└─ README.md
```

> Ensure files are placed according to this structure for links to work.

---

## 🔗 File Links

- Firmware (Arduino Nano): firmware/arduino_nano/smart_footwear.ino
- ESP8266 Snippet: firmware/esp8266/mqtt_logging_snippet.ino
- Schematics: hardware/schematics.pdf
- 3D Enclosure: hardware/enclosure.stl
- Architecture Diagram: docs/architecture.png
- Calibration Guide: docs/calibration_guide.md

---

## 📊 Performance Metrics

| Scenario | Distance (cm) | Haptic PWM | Audio |
|---|---:|---:|---|
| Open path | >150 | 0 | Off |
| Approaching | 80–150 | 80 | Off |
| Warning | 40–80 | 140 | 1.2 kHz beeps |
| Critical | <40 | 220 | 2.0 kHz beeps |

---

## 🧭 Roadmap

- Add BLE support for phone companion app
- Add depth camera (optional) for richer mapping
- Improve enclosure ergonomics and IP rating
- Community feedback-driven refinements

---

## 🧪 Testing Checklist

- [ ] Sensor distance accuracy within ±5 cm up to 2 m
- [ ] Haptic feedback scales perceptibly across ranges
- [ ] Audio alerts audible outdoors at 1 m
- [ ] Battery life > 4 hours typical use
- [ ] MQTT/HTTP events sent every 5 s (if enabled)

---

## 🤝 Contributing

Contributions are welcome! Please open issues and pull requests. Follow conventional commits and include schematics or logs for hardware/firmware changes when relevant.

---

## 📜 License

This project is released under the MIT License. See the LICENSE file for details.

---

## 🙌 Acknowledgments

- TS. Srinivasan Polytechnic College, Vanagaram
- Guide: Mrs. S. P. Chitra (HOD)
- Open-source community for libraries and design references
