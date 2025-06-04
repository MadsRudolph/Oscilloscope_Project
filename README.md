# 🧪 Oscilloscope Project – DTU 30082

This repository contains the full codebase for the **Oscilloscope Project** developed in the course **30082 – Projektarbejde i Digitalteknik** at DTU, June 2025. The project integrates an **FPGA-based signal generator** with an **ATmega2560 microcontroller-based oscilloscope**, all controlled via a **LabVIEW GUI** running on a PC.

## 🚀 Project Overview

The system generates, samples, and visualizes analog signals through a low-cost, educational oscilloscope setup. It's split across two platforms:

- **FPGA (Basys 2 board):** Signal generation via PWM and SPI control
- **MCU (ATmega2560):** Analog sampling, RS232 communication, and SPI master
- **PC (LabVIEW):** Visualization and parameter control

### 🧱 Block Diagram

```
+-------------------+         SPI         +----------------+
|                   | <------------------ |                |
|   ATmega2560 MCU  |                    |     FPGA       |
|                   | -----------------> | (Signal Gen.)  |
+-------------------+     RS232 UART     +----------------+
         |                                     |
         |                                     |
         v                                     v
    LabVIEW GUI                          Low-pass Filter
         |
         v
     User Control
```

## 📦 Folder Structure

```
Oscilloscope_Project/
├── mcu/                    # C code for ATmega2560 (PlatformIO)
│   ├── main.c
│   ├── uart.c/h
│   ├── adc.c/h
│   ├── spi.c/h
│   └── ...
├── fpga/                   # VHDL code for signal generator (Xilinx ISE)
│   ├── top.vhd
│   ├── pwm.vhd
│   ├── spi_slave.vhd
│   ├── lookup_table.vhd
│   └── ...
├── labview/                # LabVIEW VI files
│   ├── LabviewOscilloscope.vi
│   └── LabviewOscilloscopeChecksum.vi
├── doc/                    # Reports, diagrams, etc.
│   ├── OscilloskopProjekt_Jun25.pdf
│   └── ...
└── README.md
```

## 🎯 Features

### Signal Generator (FPGA)
- PWM-based analog output
- Waveform selection: Sine, Square, Triangle
- Amplitude and Frequency control via SPI
- Low-pass filter integration

### Oscilloscope (MCU)
- 8-bit ADC sampling (0–3.3V)
- Sample rates: 10 – 10,000 sps
- Record length: 10 – 1000 samples
- Continuous sampling with double buffering
- RS232 communication with LabVIEW GUI

### LabVIEW GUI
- Visualizes ADC data in real time
- Allows control over:
  - Sample rate
  - Record length
  - Waveform settings

## 📡 Communication Protocols

### RS232 (UART)
- Baudrate: 115200
- Interrupt-driven RX
- Packet-based communication with the GUI

### SPI (MCU ↔ FPGA)
- Baudrate: 500 kbaud
- Byte-based protocol for SHAPE, AMPL, and FREQ
- Custom slave shift register on FPGA

## 🛠️ Getting Started

### FPGA
- Open in Xilinx ISE 14.7
- Compile and upload the VHDL design to the Basys 2 board

### MCU
- Build with [PlatformIO](https://platformio.org/)
- Flash code to ATmega2560 using USB or AVR programmer

### LabVIEW
- Requires LabVIEW with NI-VISA installed
- Run `LabviewOscilloscope.vi` and connect to the correct COM port

## ✅ Verification Checklist

- [x] Continuous ADC sampling at all rates
- [x] Functional SPI communication with protocol parsing
- [x] Signal generation with selectable waveform and frequency
- [x] Integration with LabVIEW GUI

## 🧠 Team & Responsibilities

- **MCU & RS232:** [Names]
- **FPGA & SPI:** [Names]

> Each team member is responsible for understanding the complete system.

## 📄 License

This project is part of a university course and is **not licensed for commercial use**. For academic use only.
