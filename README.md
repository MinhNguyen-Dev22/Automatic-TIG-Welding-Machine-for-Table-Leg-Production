# Automatic TIG Welding Machine for Table Leg Production

[![License: MIT](https://img.shields.io/badge/License-MIT-yellow.svg)](https://opensource.org/licenses/MIT)
[![PLC: Siemens S7-1200](https://img.shields.io/badge/PLC-Siemens%20S7--1200-blue)](https://www.siemens.com/global/en/products/automation/systems/industrial/plc/s7-1200.html)
[![Status: Completed](https://img.shields.io/badge/Status-Completed-brightgreen)]()

**4‑axis CNC‑controlled welding system** for automatic TIG welding of steel table legs, featuring PLC‑based motion control, stepper motor drives, and a dual‑station rotary fixture to double productivity.
<img width="491" height="674" alt="image" src="https://github.com/user-attachments/assets/bce189b9-3eb3-4034-a640-01e9c185b06c" />

---

## 1. Table of Contents
- [Introduction](#introduction)
- [Features](#features)
- [Hardware](#hardware)
  - [Bill of Materials (BOM)](#bill-of-materials-bom)
  - [Block Diagram](#block-diagram)
  - [Schematic](#schematic)
- [Software](#software)
  - [PLC Program](#plc-program)
  - [Simulation & Analysis](#simulation--analysis)
- [Getting Started](#getting-started)
  - [Prerequisites](#prerequisites)
  - [Installation & Setup](#installation--setup)
  - [Operation Modes](#operation-modes)
- [Results](#results)
- [Future Work](#future-work)
- [References](#references)
- [License](#license)
- [Acknowledgments](#acknowledgments)

---

## 2. Introduction

In the context of increasing automation in the furniture industry, manual welding of table legs is labour‑intensive and prone to quality inconsistencies. This project presents a **fully automatic TIG welding machine** designed to weld a steel tube onto a square base plate – the core process in manufacturing table legs.

The system uses a **Siemens S7‑1200 PLC** as the central controller, driving **four stepper motors** (two linear axes X‑Y and two rotary axes) via **TB6600 drivers**. The welding torch is positioned by the linear axes, while the workpiece is rotated 360° by the rotary tables to create a continuous seam. Two identical rotary stations allow loading/unloading of one workpiece while the other is being welded, effectively doubling output.

The machine handles tubes of **Ø20–60 mm**, heights from **100–300 mm**, and plates of **100×100×5 mm**, achieving a welding speed of ~3 mm/s and a cycle time of 260 seconds per leg.

---

## 3. Features

- 🤖 **4‑Axis Motion Control** – X‑Y linear axes (ball screws) + two rotary axes (worm‑gear rotary tables) enable precise positioning and continuous rotation.
- ⚙️ **PLC‑Based Automation** – Siemens S7‑1200 CPU 1214C DC/DC/DC ensures stable, industrial‑grade operation with 100 kHz PTO outputs for stepper drivers.
- 🔄 **Dual‑Station Rotary Fixture** – Two independent rotary chucks allow simultaneous welding and workpiece preparation, increasing throughput.
- 🛡️ **Safety & Protection** – Limit switches, emergency stop, and overload protection (MCB) ensure safe operation.
- 📐 **High Welding Quality** – TIG process with Argon shielding produces clean, spatter‑free seams; UV inspection lamp aids defect detection.
- 🧩 **Modular Design** – Steel frame construction, easily replaceable components, and expandable I/O for future upgrades.
- 📊 **Simulation‑Validated** – Trajectory simulations in MATLAB and structural analyses in ANSYS confirm kinematic and mechanical integrity.

---

## 4. Hardware

### Bill of Materials (BOM)

| Component | Qty | Specifications |
|-----------|-----|----------------|
| PLC Controller | 1 | Siemens S7‑1200 CPU 1214C DC/DC/DC |
| Stepper Motor (X‑Y axes) | 2 | NEMA 17 (42HS4013A4), 0.4 Nm, 1.8° step |
| Stepper Motor (Rotary axes) | 2 | PK545NB (Oriental Motor), 0.24 Nm, 0.72° step |
| Stepper Driver | 4 | TB6600, 0.5–4.0 A, micro‑step 1/16 |
| Ball Screw (X‑axis) | 1 | SFU1605, stroke 500 mm, C7 accuracy |
| Ball Screw (Y‑axis) | 1 | SFU1005, stroke 300 mm, C7 accuracy |
| Linear Guide Rails | 4 | HIWIN MGN12 with carriages |
| Rotary Table | 2 | AR‑0900‑3S (Misumi), 1:180 ratio, 90 mm table |
| TIG Welding Source | 1 | TIG 240S, 20–250 A, 220 VAC |
| Limit Switches | 4 | Omron SS‑5GL2 (SPDT, roller lever) |
| Power Supply | 1 | 24 VDC / 5 A for control circuits |
| MCB | 1 | Schneider A9F74216, 16 A, 2P |
| Steel Frame | 1 | 60×60 mm box steel, powder‑coated |
| Control Panel | 1 | With START, STOP, EMERGENCY, JOG, HOME buttons |
| UV Inspection Lamp | 1 | 24 VDC, 15 W |

### 5. Block Diagram


<img width="933" height="344" alt="image" src="https://github.com/user-attachments/assets/b552d11c-e458-4731-b787-d57fa23318fa" />


The system is powered by 220 VAC, distributed via MCB to the welding source, 24 VDC power supply, and control circuits. The PLC receives inputs from push‑buttons, limit switches, and home sensors, and outputs pulse/direction signals to four TB6600 drivers, which control the stepper motors for X, Y, and two rotary axes.

### Schematic

<img width="1494" height="1073" alt="image" src="https://github.com/user-attachments/assets/26b83d05-e4ff-48bf-a374-a99e1b615ee0" />

---

## 6. Software

### PLC Program
<img width="1487" height="1067" alt="image" src="https://github.com/user-attachments/assets/e7fc071c-5fb1-47cf-b14f-a5ed06c544d8" />

- **Development Environment**: Siemens TIA Portal V20
- **Programming Languages**: Ladder Diagram (LAD) for main logic, Structured Control Language (SCL) for motion sequences.
- **Motion Control**: Integrated technology objects (TO_Positioning) for each axis, configured with **pulse‑train output (PTO)** at 100 kHz.
- **Control Modes**:
  - **Manual Mode**: Jog each axis independently for setup and calibration.
  - **Home Mode**: Automated homing sequence using limit switches to reference all axes.
  - **Auto Mode**: Pre‑programmed welding cycle – moves torch to first station, rotates 360°, moves to second station, rotates 360°, then returns home.

# 7. Results

## Results

The Automatic TIG Welding Machine was successfully designed, fabricated, and rigorously tested. The following results validate that the system meets the initial technical requirements, achieving high precision, improved productivity, and consistent weld quality.

###  Technical Specifications Achieved

The final prototype operates within the following key parameters, fully meeting the design targets:

| Parameter | Value |
| :--- | :--- |
| **Machine Dimensions (L×W×H)** | 430 × 600 × 800 mm |
| **Total Weight** | 45 kg |
| **Power Supply** | 220 V / 50 Hz |
| **Total Power Consumption** | 3.5 – 5.5 kW (depending on welding current) |
| **Control System** | Siemens S7-1200 CPU 1214C DC/DC/DC |
| **Number of Controlled Axes** | 4 (X, Y, and 2 Rotary) |
| **X-Axis Stroke** | 0 – 500 mm |
| **Y-Axis Stroke** | 0 – 250 mm |
| **Rotary Axis Stroke** | 0 – 360° |
| **Welding Speed** | ~3 mm/s |
| **Full Cycle Time (2 stations)** | 260 seconds |
| **Positioning Accuracy** | ±0.5 mm |

---

###  Motion Control & Positioning Accuracy

To evaluate the precision of the open-loop stepper system, the torch was commanded to move 20 mm along the X and Y axes. Measurements were taken using a digital caliper against a fixed reference point on the machine frame.

- **X-Axis Test**: Achieved a measured displacement of **20.05 mm** (deviation of +0.05 mm).
- **Y-Axis Test**: Achieved a measured displacement of **19.95 mm** (deviation of -0.05 mm).

The results confirm that the combination of the PLC (PTO pulses at 100 kHz), TB6600 drivers (1/8 micro-stepping), and ball screw mechanisms (SFU1605/SFU1005) provides sufficient accuracy for TIG welding applications, where consistent torch-to-workpiece distance and uniform travel speed are critical.

---

###. Trajectory Simulation vs. Real-World Performance

The welding trajectory (defined as a 360° rotation around the tube while the torch remains stationary) was first simulated in MATLAB and then validated during physical testing.

- **Simulated Deviation**: The MATLAB kinematic model predicted a maximum trajectory deviation of **±0.58 mm**, primarily attributed to dynamic loads on the Y-axis during acceleration.
- **Actual Measured Deviation**: During practical operation, the actual welding path showed a maximum deviation of **±0.5 mm** from the ideal path.

This close correlation between simulation and reality confirms the correctness of the control logic and mechanical assembly. The slight difference is attributed to mechanical backlash and minor vibrations inherent in the stepper motor system, which are well within the acceptable tolerance for structural welding in furniture manufacturing.

---

###  Mechanical & Structural Integrity

Structural Finite Element Analysis (FEA) was performed in ANSYS to verify the rigidity of the machine components under operational loads.

| Component | Max Von-Mises Stress | Material Yield Strength | Safety Factor (FS) | Max Deformation |
| :--- | :--- | :--- | :--- | :--- |
| **Main Steel Frame** | 11.72 MPa | 620 MPa | **~52.9** | 0.0079 mm |
| **Base Mounting Plate** | 1.07 MPa | 27.6 MPa | **~25.7** | 0.0014 mm |
| **Rotary Fixture Plate** | 0.0014 MPa | 620 MPa | **~452,000** | 0.000056 mm |

With safety factors far exceeding the minimum requirement of 2.0 for static structures, the machine exhibits excellent stiffness and vibration damping—ensuring the welding arc remains stable and the final seam is uniform.

---

###  Productivity & Weld Quality

- **Productivity Gain**: The dual-station rotary fixture allows the operator to load/unload a new workpiece on one side while the TIG torch welds the other. This reduces idle time and effectively doubles the output compared to conventional single-station manual or semi-automatic setups. The machine reliably produces one finished table leg every ~4.3 minutes.

- **Weld Quality**: Using the TIG 240S power source with Argon shielding gas, the machine produced consistent, spatter-free seams on 2 mm thick steel tubes. The weld penetration and bead geometry were uniform across the entire circumference. A built-in UV inspection lamp allowed for immediate post-weld detection of surface defects (e.g., cracks, porosity), ensuring quality control directly on the production line.

- **Advantages over Manual Welding**:
    - **Independence from Operator Skill**: Weld quality is highly consistent, eliminating defects caused by human fatigue or inconsistent hand speed.
    - **Cost-Effective**: The total fabrication cost is significantly lower than purchasing a 6-axis industrial welding robot, making it accessible for small to medium-sized furniture workshops.

---

###  System Stability & Safety
The system has been verified to operate safely and reliably under typical workshop conditions. The combination of robust hardware design, comprehensive safety interlocks, and validated electrical architecture ensures that the machine can be deployed for production use with minimal risk to operators or equipment.


---

###  Summary of Achievements

1. Successfully automated a complex 4-axis welding process using a cost-effective PLC and stepper motor architecture.
2. Achieved ±0.5 mm positional accuracy, validating the design of the ball screw and linear guide systems.
3. Confirmed structural integrity through ANSYS FEA, with safety factors up to 52.9.
4. Verified kinematic trajectories via MATLAB simulation, correlating within 0.08 mm of real-world testing.
5. Delivered a functional prototype that produces high-quality TIG welds at a cycle time of 260 seconds, doubling productivity through a dual-station design.

# 8. Future Work

1. Accuracy & Control
Upgrade to closed-loop servo motors with encoders to eliminate missed steps and improve positioning accuracy to < ±0.05 mm.

Implement software backlash compensation for ball screws and gearboxes.

2. Expanded Geometry
Support square/rectangular tubes, U-shaped and V-shaped leg profiles.

Add a Z-axis with automatic height adjustment for tubes of varying lengths.

3. Automation & Operator Interface
Install HMI touch panel for intuitive parameter tuning and program management.

Integrate vision-based seam tracking for real-time joint detection and adaptive correction.

Develop pneumatic/servo clamping for automatic workpiece loading/unloading.

4. Industry 4.0 Integration
Enable production data logging and remote monitoring via Ethernet/IP or MQTT.

Upload data to cloud platforms for centralized quality control and predictive maintenance.

5. Material & Process Expansion
Adapt for aluminum and stainless steel welding (AC TIG capability).

Support multi-pass welding for thicker materials (> 3 mm).

6. Mechanical Improvements
Add vibration-damping mounts and safety enclosure.

Develop quick-change fixtures for faster size/geometry transitions.
# 9. Contact
👤 Nguyen Quang Minh

📧 minh.nguyenquangvnu@gmail.com

💻 https://github.com/MinhNguyen-Dev22

🔗 LinkedIn:  https://www.linkedin.com/in/minhvnu/

If you find this project useful, please consider giving it a ⭐ on GitHub.

# . License
This project is licensed under the MIT License.

