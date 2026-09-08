# Automatic TIG Welding Machine for Table Leg Production

A 4-axis CNC-controlled automatic TIG welding system designed for high-precision welding of steel table legs, featuring PLC-based motion control and automated welding sequence management.

**ESP8266 IoT** | **Blynk IoT** | **Firebase** | **Realtime Database** | **Arduino IDE** | **License MIT** | **Status Completed**

---

An ESP8266-based solar-powered smart irrigation system featuring automatic watering, environmental monitoring, Firebase cloud storage, and remote control through the Blynk IoT mobile application.
![Uploading image.png…]()

---

## Table of Contents

1. [Introduction](#1-introduction)
2. [Features](#2-features)
3. [Hardware](#3-hardware)
   - 3.1 [BOM](#31-bom)
   - [Energy Consumption Analysis](#energy-consumption-analysis)
   - [Solar Energy Estimation](#solar-energy-estimation)
   - [Battery Backup Estimation](#battery-backup-estimation)
   - 3.2 [Block Diagram](#32-block-diagram)
   - 3.3 [Schematic](#33-schematic)
4. [Software](#4-software)
5. [Getting Started](#5-getting-started)
6. [Results](#6-results)
7. [Future Work](#7-future-work)
8. [Contact](#8-contact)
9. [License](#9-license)

---

## 1. Introduction

This project presents a solar-powered smart irrigation system designed to automatically monitor environmental conditions and irrigate plants only when necessary.

The system is built around the ESP8266 microcontroller and integrates multiple sensors including soil moisture, temperature, humidity, light intensity, and CO₂ concentration. Sensor data are uploaded to Firebase Realtime Database while users can remotely monitor and manually control the irrigation process through the Blynk IoT mobile application.

The primary objective of this project is to reduce water consumption, enable renewable-energy-powered agriculture, and provide a low-cost IoT solution suitable for home gardens and small-scale farming.

---

## 2. Features

- 🌞 **Solar Powered** – Operates entirely from a photovoltaic charging system with rechargeable Li-ion batteries.
- 💧 **Automatic Irrigation** – Automatically activates the water pump based on soil moisture conditions.
- 📱 **Remote Monitoring** – Monitor environmental parameters and manually control the irrigation system using the Blynk IoT mobile application.
- ☁️ **Cloud Data Logging** – Uploads sensor data to Firebase Realtime Database for cloud storage.
- 🌡️ **Environmental Monitoring** – Measures temperature, humidity, light intensity, soil moisture, and CO₂ concentration in real time.
- 🔋 **Battery Monitoring** – Estimates remaining battery voltage using a voltage divider circuit.
- 🛠️ **Open Source** – Complete hardware design, firmware source code, PCB files, and documentation are included.

---

## 3. Hardware

### 3.1 BOM

| Component                | Qty |
|--------------------------|-----|
| Solar panel 6V 10W       | 1   |
| ESP8266 NodeMCU          | 1   |
| DHT11                    | 1   |
| 18650 (4200mAh)          | 3   |
| TP4056 charging module   | 1   |
| Relay module             | 1   |
| XL6009 boost converter   | 2   |
| LCD1602 I2C              | 1   |
| Water pump (12V, 6W)     | 1   |

---

### Energy Consumption Analysis

The estimated daily energy consumption of the system is summarized in the table below.

| Component                | Operating Time                | Power    | Daily Energy Consumption      |
|--------------------------|-------------------------------|----------|-------------------------------|
| ESP8266 + LCD + DHT11    | 24 hours                      | ≈ 1.2 W  | 1.2 × 24 = 28.8 Wh            |
| Water Pump (12 V, 6 W)   | 5 cycles × 10 s = 50 s/day    | 6 W      | 6 × (50/3600) ≈ 0.085 Wh      |
| **Total**                |                               |          | **≈ 28.885 Wh/day**           |

Assuming the XL6009 boost converter has an efficiency of approximately 90%, the total energy drawn from the battery per day is:

---

### Solar Energy Estimation

The system uses a 6 V, 10 W solar panel.

Assuming approximately 6 hours of effective sunlight per day, the theoretical harvested energy is:

Considering practical conditions such as sunlight angle, dust, and weather, the actual solar panel efficiency is assumed to be approximately 70%.

After accounting for the charging efficiency of the TP4056 charging module (approximately 90%), the actual energy stored in the battery becomes:

Therefore, the daily energy surplus is:

This surplus compensates for battery losses and helps maintain the battery at a safe operating level.

---

### Battery Backup Estimation

The system is powered by three 18650 Li-ion batteries connected in parallel.

- Battery capacity (per cell): 4200 mAh
- Nominal voltage: 3.7 V

Total stored battery energy:

During nighttime or in the absence of solar energy, the system is powered solely by the battery pack.

The estimated battery backup time is:

---

### 3.2 Block Diagram

---

### 3.3 Schematic

---

## 4. Software

The firmware is written in Arduino IDE. The system follows the flowchart below:

---

## 5. Getting Started

### Software Requirements

- Arduino IDE
- ESP8266 Board Package
- Blynk Library
- Firebase ESP Client
- DHT Library
- ArduinoJson

### Blynk Configuration

1. **Create a Template** on Blynk IoT Console.
2. **Create Datastreams** for each sensor parameter (soil moisture, temperature, humidity, light, CO₂, pump status, battery voltage).
3. **Copy** the following credentials from the Blynk template:
   - Template ID
   - Template Name
   - Authentication Token
4. Replace them in the firmware code:

```cpp
#define BLYNK_TEMPLATE_ID   "YOUR_TEMPLATE_ID"
#define BLYNK_TEMPLATE_NAME "YOUR_TEMPLATE_NAME"
#define BLYNK_AUTH_TOKEN    "YOUR_AUTH_TOKEN"
