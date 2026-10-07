# CAN-Based Automotive Dashboard

A multi-ECU automotive dashboard simulation developed using the **PIC18F4580 microcontroller** and **CAN (Controller Area Network) communication**. The system demonstrates how different Electronic Control Units (ECUs) exchange vehicle information and display it on a central dashboard in real time.

## 📌 Project Overview

Modern vehicles use multiple ECUs to monitor and control different functions such as speed, engine RPM, gear position, and indicators. These ECUs communicate with each other using automotive communication protocols such as CAN.

This project simulates that architecture using multiple PIC18F4580-based ECUs connected through a CAN network.

The system consists of:

* **ECU1** – Reads vehicle speed and gear position and transmits the information through CAN.
* **ECU2** – Reads engine RPM and indicator inputs and transmits the information through CAN.
* **ECU3 / Dashboard ECU** – Receives CAN messages from the other ECUs and displays the received vehicle information on a Character LCD.

## ⚙️ Main Features

* PIC18F4580-based embedded system
* CAN-based communication between multiple ECUs
* ADC-based speed monitoring
* ADC-based RPM monitoring
* Matrix keypad-based gear selection
* Indicator switch monitoring
* Character LCD dashboard display
* Real-time transmission and reception of vehicle parameters
* Multi-ECU automotive system architecture
* Hardware and software integration
* Simulation and debugging using embedded development tools

## 🏗️ System Architecture

```text
                  ┌─────────────────────┐
                  │        ECU 1        │
                  │                     │
                  │ Speed → ADC         │
                  │ Gear  → Matrix Keypad│
                  │                     │
                  │ PIC18F4580          │
                  └──────────┬──────────┘
                             │
                             │ CAN
                             ▼
                    ┌─────────────────┐
                    │    CAN BUS      │
                    └───────┬─────────┘
                            │
              ┌─────────────┴─────────────┐
              │                           │
              ▼                           ▼
      ┌─────────────────┐        ┌─────────────────┐
      │      ECU 2      │        │      ECU 3      │
      │                 │        │    Dashboard    │
      │ RPM → ADC       │        │                 │
      │ Indicators      │        │ CAN Receiver    │
      │                 │        │ Character LCD   │
      │ PIC18F4580      │        │ PIC18F4580      │
      └─────────────────┘        └─────────────────┘
```

## 🔌 ECU Functions

### ECU1 – Speed & Gear

ECU1 is responsible for monitoring vehicle speed and gear position.

**Inputs:**

* Potentiometer / ADC – Speed
* Matrix keypad – Gear selection

**Processing:**

* Reads the ADC value
* Converts the ADC value into a speed value
* Detects gear changes from the matrix keypad
* Displays speed and gear locally

**CAN Output:**

* Speed
* Gear position

### ECU2 – RPM & Indicators

ECU2 monitors engine RPM and indicator inputs.

**Inputs:**

* Potentiometer / ADC – RPM
* Digital keypad/switches – Indicators

**Processing:**

* Reads the ADC value
* Converts the ADC value into RPM
* Monitors indicator switches
* Controls the corresponding indicator output

**CAN Output:**

* RPM
* Indicator status

### ECU3 – Dashboard

ECU3 acts as the central dashboard controller.

It receives CAN messages from ECU1 and ECU2 and displays the vehicle parameters on the Character LCD.

**Displayed parameters include:**

* Speed
* RPM
* Gear position
* Indicator status

## 📡 CAN Communication

The project uses **CAN communication** to exchange information between the ECUs.

The basic communication flow is:

```text
ECU1 ──────┐
           │
           ├── CAN BUS ──→ ECU3 Dashboard
           │
ECU2 ──────┘
```

Each ECU transmits its corresponding vehicle parameters using CAN messages.

### Example Data Flow

```text
ECU1
 │
 ├── Speed
 └── Gear
      │
      ▼
    CAN BUS
      │
      ▼
   ECU3 LCD


ECU2
 │
 ├── RPM
 └── Indicators
      │
      ▼
    CAN BUS
      │
      ▼
   ECU3 LCD
```

## 🧰 Hardware Used

* PIC18F4580 Microcontroller
* CAN transceiver / CAN interface
* Character LCD
* Matrix Keypad
* Digital Keypad / Switches
* Potentiometers
* LEDs
* Connecting wires
* Power supply
* PIC development board

## 💻 Software & Tools

* MPLAB X IDE
* MPLAB XC8 Compiler
* Embedded C
* Proteus (for circuit simulation)
* PIC18F4580 Device Family Pack
* CAN communication peripherals

## 📂 Project Structure

```text
CAN-Based-Automotive-Dashboard/
│
├── ecu1/
│   ├── main.c
│   ├── adc.c
│   ├── adc.h
│   ├── can.c
│   ├── can.h
│   ├── clcd.c
│   ├── clcd.h
│   ├── matrix_keypad.c
│   ├── matrix_keypad.h
│   └── ...
│
├── ecu2/
│   ├── main.c
│   ├── adc.c
│   ├── adc.h
│   ├── can.c
│   ├── can.h
│   ├── clcd.c
│   ├── clcd.h
│   └── ...
│
├── ecu3_dashboard/
│   ├── main.c
│   ├── can.c
│   ├── can.h
│   ├── clcd.c
│   ├── clcd.h
│   └── ...
│
├── schematics/
│   └── schematic.pdf
│
└── README.md
```

> The exact file structure may vary depending on the MPLAB X project version.

## 🔄 Working Principle

1. ECU1 reads the vehicle speed using its ADC input.
2. ECU1 reads the selected gear using the matrix keypad.
3. ECU1 transmits speed and gear information through CAN.
4. ECU2 reads the engine RPM through its ADC input.
5. ECU2 monitors the indicator switches.
6. ECU2 transmits RPM and indicator information through CAN.
7. ECU3 receives the CAN messages.
8. ECU3 processes the received data.
9. The dashboard LCD is updated with the latest vehicle information.

## 🚗 Example Dashboard

```text
--------------------
| SPEED : 080 km/h |
| RPM   : 3500     |
| GEAR  : 4        |
| IND   : LEFT     |
--------------------
```

## 🎯 Project Objectives

* Understand automotive ECU architecture.
* Implement CAN communication using PIC18F4580.
* Learn ADC-based sensor/parameter monitoring.
* Interface matrix keypad and digital switches.
* Implement real-time embedded communication.
* Develop a multi-ECU automotive system.
* Understand hardware-software integration in embedded systems.

## 🧠 Concepts Demonstrated

* Embedded C
* PIC18F4580
* ADC
* GPIO
* Timers
* Interrupts
* CAN Protocol
* CAN message transmission and reception
* Matrix keypad interfacing
* Character LCD interfacing
* Real-time data processing
* Multi-ECU communication
* Automotive embedded systems

## 🛠️ Future Improvements

Possible extensions include:

* Add vehicle temperature monitoring.
* Add fuel-level monitoring.
* Add battery-voltage monitoring.
* Add warning/error messages.
* Implement CAN error handling.
* Add CAN message filtering.
* Add EEPROM-based configuration.
* Add a graphical dashboard.
* Implement additional automotive ECUs.
* Add diagnostic communication.

## 👨‍💻 Author

**Vishnu Kalikal**

B.Tech – Electrical and Electronics Engineering

Interested in Embedded Systems, Embedded Firmware, Automotive Electronics, and Software Development.

## 📜 License

This project is intended for educational and learning purposes.
