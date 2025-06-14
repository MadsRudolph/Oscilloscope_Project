# ⚡ Oscilloscope & Signal Generator — DTU 30082 Project

Welcome to the **Oscilloscope_Project**, developed for the DTU course **30082 – Projektarbejde i Digitalteknik**.  
This full-stack embedded system connects a **Basys 2 FPGA** signal generator, an **ATmega2560 oscilloscope**, and a **LabVIEW GUI**.  
It visualizes analog signals in real time and allows waveform control through a robust UART/SPI interface.

---

## 📂 Project Structure

```
Oscilloscope_Project/
├── Microcontroller/           # PlatformIO-based ATmega2560 codebase
│   ├── include/               # Header files
│   ├── src/                   # Source files (ADC, UART, SPI, main.c, etc.)
│   ├── lib/                   # Shared libs (if any)
│   ├── test/                  # Unit or hardware test code
│   └── platformio.ini         # PlatformIO build config
│
├── fpga/                      # VHDL projects for signal generation
│   ├── SignalGenerator/       # PWM and waveform logic
│   ├── SPI_Test/              # SPI slave & protocol decoder
│   ├── *.vhd, *.xise, *.gise  # Top-level ISE project and source files
│
├── docs/                      # Technical documentation and filter design
│   ├── Kicad/FilterDesign/    # Filter schematics and sim files
│   ├── LTspice/               # SPICE simulations for filter tuning
│   └── osciloscop_projekt...  # Maple worksheet for low-pass filter math
│
├── README.md
├── .gitignore
└── .gitkeep
```

---

## 🎯 Project Goal

Design and implement a digital oscilloscope system that:
- Samples analog waveforms with an ATmega2560
- Sends sampled data to a LabVIEW GUI over UART
- Receives waveform control commands via UART (shape, freq, amp)
- Forwards these settings to an FPGA-based signal generator via SPI
- Generates desired analog output through PWM + active low-pass filter

---

## 🧰 Technologies Used

| Platform       | Tech                     | Purpose                                |
|----------------|--------------------------|----------------------------------------|
| ATmega2560     | C / PlatformIO           | UART, ADC, SPI, Interrupts             |
| FPGA (Basys 2) | VHDL (Xilinx ISE 14.7)   | PWM waveform generation via SPI input |
| PC (Windows)   | LabVIEW 2014 + NI-VISA   | GUI and protocol management            |
| Docs           | KiCad / LTspice / Maple  | Active filter design + verification    |

---

## 📡 Communication Protocols

### UART (MCU ↔ LabVIEW)
- **Baudrate:** `115200`, 8N1
- **Protocol Format:**
  ```
  [0x55, 0xAA] + Length (2B) + Type (1B) + Data + Checksum (2B)
  ```
- **Types:**
  - `0x01` — Generator BTN pressed (with SW value)
  - `0x02` — Oscilloscope settings (sample rate, record length)
  - `0x03` — Start Bode plot

### SPI (MCU → FPGA)
- 4-byte packets with sync and checksum:
  ```
  [0x55][ADDR][DATA][CHKSUM]
  ADDR: 1 = Amplitude, 2 = Frequency, 3 = Shape
  ```

---

## 🔬 Subsystems

### 🟨 Microcontroller (ATmega2560)
- **ADC:** Timer1-triggered, 8-bit resolution (0–3.3V range)
- **UART0:** Debug output
- **UART1:** Full-duplex packet parser for LabVIEW GUI
- **SPI Master:** Sends shape/freq/amp to FPGA
- **Double buffer** system for uninterrupted sampling

### 🟦 FPGA (Basys 2)
- **PWM Generator:** Output shaped using lookup tables
- **SPI Slave:** Custom shift register receives waveform config
- **Waveform Types:** Sine, Square, Sawtooth
- **Low-pass filter** external circuit smooths PWM to analog

### 🟥 LabVIEW GUI
- **Tabs:** Generator, Oscilloscope, Bode Plot
- **Live Display:** ADC waveform, sample control
- **Checksum Algorithms:** ZERO16, LRC8, CRC16-CCITT
- **Built-in simulator:** Protocol testing without hardware

---

## 🔍 Filter Design

- Built with **KiCad** and **LTspice**
- Verified performance of 2nd and 4th order low-pass filters
- Adjusted for PWM ripple suppression and waveform fidelity
- Transfer functions derived in **Maple**

---

## ✅ Features Implemented

- [x] Timer-driven ADC (up to 10,000 sps)
- [x] UART protocol parsing with packet integrity checks
- [x] SPI communication with XOR checksums
- [x] Real-time waveform generation via PWM
- [x] Functional LabVIEW interface with return feedback
- [x] Active analog filtering validated with simulation

---

## 👥 Authors

**Embedded C (MCU, UART, SPI, ADC):**  
- Mads Rudolph  
- Sigurd Hestbech Christiansen  

**FPGA Design (PWM, LUTs, SPI Slave):**  
- Jonas Jensen  
- Andreas Jacobsen  
- Joakim Butenko

> All members have reviewed and understood the entire system.

---

## 🔐 License

This project was created for the **DTU 30082 course** and is released for **educational, non-commercial use only**.
