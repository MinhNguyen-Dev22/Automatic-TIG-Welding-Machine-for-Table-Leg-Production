# Solar-Powered-Smart-Irrigation-System

An ESP8266-based solar-powered smart irrigation system with real-time environmental monitoring, Firebase integration, and automatic irrigation control.

![ESP8266 Blynk Firebase Arduino](https://img.shields.io/badge/ESP8266-Blynk-Firebase-green) ![License](https://img.shields.io/badge/license-MIT-blue)

An ESP8266-based solar-powered smart irrigation system featuring automatic watering, environmental monitoring, Firebase cloud storage, and remote control through the Blynk IoT mobile application.

![image](image)

## Table of Contents
- [Introduction](#introduction)
- [Features](#features)
- [Hardware](#hardware)
- [Software](#software)
- [Getting Started](#getting-started)
- [Results](#results)
- [Future Work](#future-work)
- [Contact](#contact)
- [License](#license)

## Introduction
This project presents a solar-powered smart irrigation system designed to automatically monitor environmental conditions and irrigate plants only when necessary.

The system is built around the ESP8266 microcontroller and integrates multiple sensors including soil moisture, temperature, humidity, light intensity, and CO₂ concentration. Sensor data are uploaded to Firebase Realtime Database while users can remotely monitor and manually control the irrigation process through the Blynk IoT mobile application.

The primary objective of this project is to reduce water consumption, enable renewable-energy-powered agriculture, and provide a low-cost IoT solution suitable for home gardens and small-scale farming.

## Features
- 🌞 **Solar Powered** – Operates entirely from a photovoltaic charging system with rechargeable Li-ion batteries.
- 💧 **Automatic Irrigation** – Automatically activates the water pump based on soil moisture conditions.
- 📱 **Remote Monitoring** – Monitor environmental parameters and manually control the irrigation system using the Blynk IoT mobile application.
- ☁️ **Cloud Data Logging** – Uploads sensor data to Firebase Realtime Database for cloud storage.
- 🌡️ **Environmental Monitoring** – Measures temperature, humidity, light intensity, soil moisture, and CO₂ concentration in real time.
- 🔋 **Battery Monitoring** – Estimates remaining battery voltage using a voltage divider circuit.
- 🛠️ **Open Source** – Complete hardware design, firmware source code, PCB files, and documentation are included.

## Hardware

### BOM
| Component                | Qty |
|--------------------------|-----|
| Solar panel 6V 10W       | 1   |
| ESP8266                  | 1   |
| DHT11                    | 1   |
| 18650 (4200mAh)          | 3   |
| TP4056                   | 1   |
| Relay                    | 1   |
| XL6009                   | 2   |
| LCD1602                  | 1   |
| Pump                     | 1   |

### Energy Consumption Analysis
The estimated daily energy consumption of the system is summarized in the table below.

| Component                | Operating Time                | Power    | Daily Energy Consumption      |
|--------------------------|-------------------------------|----------|-------------------------------|
| ESP8266 + LCD + DHT11    | 24 hours                      | ≈ 1.2 W  | 1.2 × 24 = 28.8 Wh            |
| Water Pump (12 V, 6 W)   | 5 cycles × 10 s = 50 s/day    | 6 W      | 6 × (50/3600) ≈ 0.085 Wh      |
| **Total**                |                               |          | **≈ 28.885 Wh/day**           |

Assuming the XL6009 boost converter has an efficiency of approximately 90%, the total energy drawn from the battery per day is:
