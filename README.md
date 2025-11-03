# Smart Footwear Assistive Walking System

> *An IoT-powered assistive device for visually impaired individuals using ultrasonic sensing and haptic feedback*

[![Status](https://img.shields.io/badge/status-active-brightgreen)](#)
[![License: MIT](https://img.shields.io/badge/License-MIT-blue.svg)](#license)
[![Platform](https://img.shields.io/badge/platform-Arduino%20%7C%20IoT-orange)](#)
[![Made with Love](https://img.shields.io/badge/Made%20with-%E2%9D%A4%EF%B8%8F-red)](#)

---

## 📑 Table of Contents

- [🧠 Overview](#-overview)
- [🎯 Problem Statement](#-problem-statement)
- [⚙️ Working Principle](#️-working-principle)
- [🪫 Hardware Components](#-hardware-components)
- [💻 Software & Code](#-software--code)
- [🏗️ System Architecture](#️-system-architecture)
- [🔄 System Flow](#-system-flow)
- [👥 Team](#-team)
- [📂 Repository Structure](#-repository-structure)
- [🎓 Acknowledgments](#-acknowledgments)
- [📄 License](#-license)
- [🔗 Documentation Links](#-documentation-links)

---

## 🧠 Overview

**Smart Footwear Assistive Walking System** is an innovative IoT-based assistive technology designed to enhance mobility and safety for visually impaired individuals. The system integrates ultrasonic sensors, haptic feedback mechanisms, and intelligent processing to detect obstacles and provide real-time alerts during navigation.

This project combines **embedded systems**, **IoT connectivity**, and **assistive technology** to create an affordable, compact, and user-friendly solution that can be seamlessly integrated into everyday footwear.

### Key Highlights:
- ✅ Real-time obstacle detection using ultrasonic sensors
- ✅ Haptic feedback through vibration motors
- ✅ Arduino-based embedded control system
- ✅ Portable and wearable design
- ✅ Low-power consumption
- ✅ Scalable for future IoT enhancements

---

## 🎯 Problem Statement

Visually impaired individuals face significant challenges in detecting obstacles at ground level and mid-height during daily navigation. Traditional assistive devices like white canes have limitations:

- ❌ Limited detection range
- ❌ Inability to detect overhead or side obstacles
- ❌ Requires manual scanning
- ❌ Not hands-free

**Our Solution**: A smart, shoe-mounted assistive system that provides autonomous obstacle detection and real-time feedback without requiring manual input.

---

## ⚙️ Working Principle

The Smart Footwear system operates on the following principle:

1. **Ultrasonic sensors** mounted on the footwear continuously emit ultrasonic waves
2. When an obstacle is detected within the threshold range, the reflected waves are captured
3. The **Arduino Nano** processes the sensor data and calculates obstacle distance
4. Based on distance thresholds, the **vibration motor** is activated with varying intensity
5. **Closer obstacles** trigger stronger vibrations for immediate alert
6. The system operates continuously with low-power optimization

### Detection Zones:
- **Zone 1**: 0-30 cm → High-intensity vibration (Critical)
- **Zone 2**: 30-60 cm → Medium-intensity vibration (Warning)
- **Zone 3**: 60-100 cm → Low-intensity vibration (Caution)

---

## 🪫 Hardware Components

| Component | Model/Type | Quantity | Purpose |
|-----------|-----------|----------|----------|
| **Microcontroller** | Arduino Nano | 1 | Main processing unit |
| **Ultrasonic Sensor** | HC-SR04 | 2 | Obstacle detection (toe & knee level) |
| **Vibration Motor** | 3V DC Motor | 2 | Haptic feedback |
| **Power Supply** | Li-ion Battery (3.7V) | 1 | Power source |
| **Voltage Regulator** | LM7805 | 1 | Voltage regulation |
| **Transistor** | BC547 NPN | 2 | Motor driver |
| **Resistors** | 10kΩ, 1kΩ | As needed | Circuit protection |
| **Diode** | 1N4007 | 2 | Reverse polarity protection |
| **Connecting Wires** | Jumper Wires | - | Circuit connections |
| **PCB/Breadboard** | Custom PCB | 1 | Component mounting |
| **Enclosure** | 3D Printed/ABS | 1 | Waterproof housing |

---

## 💻 Software & Code

### Development Environment:
- **IDE**: Arduino IDE 2.x
- **Programming Language**: C/C++ (Arduino Framework)
- **Libraries Used**:
  - `NewPing.h` - Ultrasonic sensor control
  - `Wire.h` - I2C communication (if applicable)

### Code Structure:
```
Smart_Footwear_Assistive_Walking_System.ino
├── setup()          // Initialize sensors, motors, pins
├── loop()           // Main control logic
├── detectObstacle() // Ultrasonic distance measurement
├── activateVibration() // Haptic feedback control
└── powerManagement() // Battery optimization
```

### Key Features in Code:
- ⚡ Efficient polling mechanism
- 🔋 Low-power sleep mode implementation
- 🎚️ Adaptive vibration intensity based on distance
- 🛡️ Debounce filtering for stable readings
- 🔄 Continuous monitoring loop

---

## 🏗️ System Architecture

![System Architecture](https://user-gen-media-assets.s3.amazonaws.com/seedream_images/eb7e973b-ffe4-4714-acb0-f7592b99396d.png)

### Architecture Overview:

The system follows a modular architecture with three primary layers:

1. **Sensing Layer**: Ultrasonic sensors (HC-SR04) for obstacle detection
2. **Processing Layer**: Arduino Nano for signal processing and decision making
3. **Actuation Layer**: Vibration motors for haptic feedback

---

## 🔄 System Flow

### Operational Sequence:

1. **System Initialization**
   - Power ON
   - Initialize Arduino Nano
   - Configure sensor pins (Trigger/Echo)
   - Initialize vibration motor pins

2. **Continuous Monitoring**
   - Ultrasonic sensors emit pulse signals
   - Measure time for echo return
   - Calculate distance: `Distance = (Time × Speed of Sound) / 2`

3. **Distance Evaluation**
   - Compare measured distance with threshold values
   - Classify into danger zones (Critical/Warning/Caution)

4. **Feedback Generation**
   - If obstacle detected:
     - Zone 1 (0-30cm): High-intensity vibration
     - Zone 2 (30-60cm): Medium-intensity vibration
     - Zone 3 (60-100cm): Low-intensity vibration
   - If no obstacle: Motors OFF

5. **Loop Continuation**
   - Repeat monitoring cycle every 100ms
   - Implement power-saving delays

---

## 👥 Team

### Project Contributors:

| Name | Role | Responsibilities |
|------|------|------------------|
| **Sriram V** | Project Lead & Developer | System design, firmware development, integration |
| **Surothaaman R** | Hardware Engineer | Circuit design, PCB layout, component testing |
| **Pavithra M** | Documentation & Design | Technical documentation, project presentation, design |
| **Ms. V. Swedha** | Project Supervisor | Academic guidance, project mentorship, evaluation |

---

## 📂 Repository Structure

```
Smart-Footwear-Assistive-Walking-System/
│
├── src/
│   └── Smart_Footwear_Assistive_Walking_System.ino  # Main Arduino source code
│
├── docs/
│   ├── DESIGN AND MODELLING OF FOOTWEAR FOR VISUALLY IMPAIRED REPORT.pdf
│   ├── DESIGN AND MODELLING OF FOOTWEAR FOR VISUALLY IMPAIRED REPORT.docx
│   └── Project_Presentation.pptx                    # Project presentation slides
│
├── hardware_design/
│   ├── circuit_diagram.png                          # Circuit schematic
│   ├── architecture_diagram.png                     # System architecture diagram
│   ├── pcb_layout.pdf                               # PCB design files
│   └── component_list.xlsx                          # Bill of materials
│
├── media/
│   ├── demo_video.mp4                               # Working demonstration
│   ├── product_images/                              # Product photographs
│   └── prototype_images/                            # Prototype development images
│
├── test/
│   ├── sensor_calibration.ino                       # Sensor testing scripts
│   └── motor_feedback_test.ino                      # Vibration motor tests
│
├── README.md                                        # This file
├── LICENSE                                          # MIT License
└── .gitignore                                       # Git ignore rules
```

---

## 🎓 Acknowledgments

We would like to express our sincere gratitude to:

- **Ms. V. Swedha** - Project Supervisor, for her invaluable guidance and support throughout the project
- **Department of Electronics and Communication Engineering** - For providing resources and facilities
- **Our Institution** - For encouraging innovation and assistive technology research
- **Visually Impaired Community** - For their insights and feedback during user testing
- **Open Source Community** - For Arduino libraries and development tools

This project was developed as part of our **Final Year Engineering Project** in the academic year 2024-2025.

---

## 📄 License

This project is licensed under the **MIT License** - see below for details:

```
MIT License

Copyright (c) 2025 Sriram V, Surothaaman R, Pavithra M

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
```

---

## 🔗 Documentation Links

### 📄 Project Reports:
- [📕 Full Project Report (PDF)](./docs/DESIGN%20AND%20MODELLING%20OF%20FOOTWEAR%20FOR%20VISUALLY%20IMPAIRED%20REPORT.pdf)
- [📘 Project Report (DOCX)](./docs/DESIGN%20AND%20MODELLING%20OF%20FOOTWEAR%20FOR%20VISUALLY%20IMPAIRED%20REPORT.docx)

### 📊 Presentation:
- [🎞️ Project Presentation (PPT)](./docs/Project_Presentation.pptx)

### 💻 Source Code:
- [⚙️ Main Arduino Code](./src/Smart_Footwear_Assistive_Walking_System.ino)

---

## 🌟 Future Enhancements

- 🌐 **IoT Integration**: Real-time location tracking via GPS and cloud connectivity
- 📱 **Mobile App**: Companion app for configuration and emergency alerts
- 🗣️ **Voice Feedback**: Audio directions using TTS (Text-to-Speech)
- 🤖 **AI/ML**: Adaptive learning for different walking patterns
- 🔋 **Solar Charging**: Extended battery life with solar panels
- 🌧️ **Weather Resistance**: Enhanced waterproofing for all conditions

---

## 📞 Contact

For queries, suggestions, or collaboration:

- **Project Lead**: Sriram V
- **Hardware Engineer**: Surothaaman R
- **Documentation Lead**: Pavithra M
- **Supervisor**: Ms. V. Swedha

---

<div align="center">

### ⭐ If you find this project helpful, please consider giving it a star!

**Made with ❤️ by Team Smart Footwear**

*Empowering Independence Through Technology*

</div>
