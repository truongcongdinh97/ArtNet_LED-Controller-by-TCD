# ArtNet LED Controller by TCD

[![PlatformIO CI](https://img.shields.io/badge/PlatformIO-Build-orange?logo=data:image/svg+xml;base64,PHN2ZyB3aWR0aD0iMjUwMCIgaGVpZ2h0PSIyNTAwIiB2aWV3Qm94PSIwIDAgMjU2IDI1NiIgeG1sbnM9Imh0dHA6Ly93d3cudzMub3JnLzIwMDAvc3ZnIiBwcmVzZXJ2ZUFzcGVjdFJhdGlvPSJ4TWlkWU1pZCI+PHBhdGggZD0iTTEyOCAwQzU3LjMwOCAwIDAgNTcuMzA4IDAgMTI4czU3LjMwOCAxMjggMTI4IDEyOCAxMjgtNTcuMzA4IDEyOC0xMjhTMTk4LjY5MiAwIDEyOCAwem0wIDIzOWMtNjEuMzM1IDAtMTExLTQ5LjY2NS0xMTEtMTExUzY2LjY2NSAxNyAxMjggMTdzMTExIDQ5LjY2NSAxMTEgMTExLTQ5LjY2NSAxMTEtMTExIDExMXoiIGZpbGw9IiNGRkYiLz48L3N2Zz4%3D)](https://github.com/truongcongdinh97/ArtNet_LED-Controller-by-TCD)
[![ESP32](https://img.shields.io/badge/ESP32-Platform-blue?logo=espressif)](https://www.espressif.com/en/products/socs/esp32)
[![Art-Net](https://img.shields.io/badge/Art--Net-Protocol-green)](https://art-net.org.uk/)
[![License: MIT](https://img.shields.io/badge/License-MIT-yellow.svg)](https://opensource.org/licenses/MIT)
[![Release](https://img.shields.io/github/v/release/truongcongdinh97/ArtNet_LED-Controller-by-TCD)](https://github.com/truongcongdinh97/ArtNet_LED-Controller-by-TCD/releases)

> **🎭 Bộ điều khiển LED chuyên nghiệp cho sân khấu và giải trí**  
> Một giải pháp hoàn chỉnh dựa trên ESP32 để điều khiển LED thông qua giao thức Art-Net

![ArtNet LED Controller](https://img.shields.io/badge/Status-Production%20Ready%20v1.2.4-brightgreen)
![Memory Usage](https://img.shields.io/badge/RAM-19.3%25%20(63KB)-success)
![Flash Usage](https://img.shields.io/badge/Flash-73.9%25%20(969KB)-orange)
![GPIO Optimized](https://img.shields.io/badge/GPIO-Boot%20Safe%20Optimized-blue)

## 📖 Giới thiệu

Dự án này biến một bo mạch ESP32 thành một **"bộ não" trung tâm** cho hệ thống ánh sáng chuyên nghiệp, có khả năng giao tiếp qua mạng bằng chuẩn **Art-Net**. Thiết bị có thể:

- 🎯 **Nhận tín hiệu** từ các phần mềm điều khiển chuyên nghiệp (QLC+, MadMapper, Resolume...)  
- 💡 **Điều khiển trực tiếp** hàng ngàn đèn LED WS2812B/WS2811
- 💾 **Ghi lại** các buổi trình diễn để hoạt động độc lập
- 🔄 **Chuyển tiếp** tín hiệu đến các thiết bị khác trong hệ thống

### 🎪 Ứng dụng thực tế
- **Sân khấu & Concert**: Điều khiển backdrop LED, wing LED
- **Kiến trúc**: Chiếu sáng tòa nhà, cầu, công trình
- **Sự kiện**: Wedding, conference, exhibition
- **Art Installation**: Tác phẩm nghệ thuật tương tác
- **Nightclub & Bar**: Hệ thống ánh sáng vũ trường

## ⭐ Tính năng nổi bật

### 🌐 **Kết nối mạng đa dạng**
- **🔌 Ethernet (W5500)**: Kết nối ổn định cho production
- **📶 Wi-Fi**: Kết nối linh hoạt, dự phòng cho Ethernet
- **🎯 Auto-fallback**: Tự động chuyển đổi giữa các kết nối
- **⚙️ Hotspot mode**: Setup dễ dàng qua AP `LED_Controller-Setup`

### 🎮 **Điều khiển Art-Net chuyên nghiệp**
- **📡 Art-Net Receiver**: Lắng nghe và xử lý tín hiệu Art-Net
- **🔄 Art-Net Sender**: Chuyển tiếp DMX đến thiết bị khác
- **🎭 Multi-universe**: Hỗ trợ nhiều universe (lên đến 8)
- **⚡ Real-time**: Xử lý tín hiệu với độ trễ thấp

### 💡 **Điều khiển LED mạnh mẽ**
- **🎯 4 Output channels**: Điều khiển đồng thời 4 dải LED
- **🌈 WS2812B/WS2811**: Hỗ trợ LED addressable phổ biến
- **📊 Dynamic mapping**: Mapping universe linh hoạt
- **💾 680 LEDs/channel**: Tổng cộng 2,720 LEDs đồng thời

### 🎬 **Recording & Playback**
- **📹 Record to SD**: Ghi show vào thẻ nhớ SD
- **▶️ Standalone playback**: Phát lại không cần máy tính
- **🔁 Loop modes**: Play once, loop single, loop all
- **⚡ Buffered recording**: Ghi nhiều universe mượt mà

### 🖥️ **Giao diện đa dạng**
- **💻 Web interface**: Cấu hình qua trình duyệt
- **📱 Responsive design**: Tương thích mobile
- **🖱️ LCD + Rotary**: Menu vật lý trực quan
- **🔧 OTA Update**: Nâng cấp firmware từ xa

## 🖼️ Screenshots & Demo

<table>
<tr>
<td align="center">
<img src="https://via.placeholder.com/300x200/1f1f1f/00ff00?text=Web+Interface" alt="Web Interface"/>
<br><b>🌐 Web Configuration</b>
</td>
<td align="center">
<img src="https://via.placeholder.com/300x200/1f1f1f/ff6600?text=LCD+Menu" alt="LCD Menu"/>
<br><b>🖱️ LCD Physical Menu</b>
</td>
</tr>
<tr>
<td align="center">
<img src="https://via.placeholder.com/300x200/1f1f1f/0099ff?text=Hardware+Setup" alt="Hardware"/>
<br><b>⚙️ Hardware Assembly</b>
</td>
<td align="center">
<img src="https://via.placeholder.com/300x200/1f1f1f/ff0099?text=LED+Demo" alt="LED Demo"/>
<br><b>💡 LED Control Demo</b>
</td>
</tr>
</table>

## 🎮 Giao diện điều khiển

### 💻 1. Web Interface

Truy cập qua địa chỉ IP của thiết bị để vào **dashboard điều khiển toàn diện**:

#### 🏠 **Main Config Page** (`/config.html`)
```
🌐 Network Settings:
  ├── 📶 WiFi Configuration (SSID & Password)
  ├── 🌍 Static IP Setup  
  └── 🔧 Network Diagnostics

💡 LED Settings:
  ├── 🎯 Number of Outputs (1-4)
  ├── 🌈 LEDs per Output (1-680)
  ├── 📊 Start Universe Mapping
  └── ⚡ Local LED Enable/Disable
```

#### 🎭 **DMX Config Page** (`/config_dmx.html`)
```
🔄 Art-Net Forwarding:
  ├── 🎯 Target IP Address
  ├── 📊 Universe Count (1-8)
  └── ⏱️ Packet Rate (1-60 fps)
```

#### 🔄 **OTA Update Page** (`/update`)
```
📦 Firmware Management:
  ├── 🚀 Upload .bin files
  ├── 📊 Progress tracking  
  └── ✅ Auto-restart after upload
```

### 🖱️ 2. Physical Control (LCD + Rotary Encoder)

**Menu cấp vật lý** cho điều khiển nhanh không cần mạng:

```
🏠 Main Menu
├── 📡 STREAMING Mode    ← Real-time Art-Net
├── 🎬 RECORDING Mode    ← Save show to SD
├── ▶️  PLAYBACK Mode    ← Play saved shows
└── ℹ️  ABOUT & SETTINGS ← Device info & reset
```

#### 🎬 **Recording Workflow:**
1. **Select Recording** → Press encoder to start
2. **Recording Status** → Red LED indicates active
3. **Stop Recording** → Press again to save

#### ▶️ **Playback Workflow:**
1. **Browse Files** → Rotate to select show
2. **Choose Loop Mode** → Once, Loop File, Loop All
3. **Start Playback** → Press to begin show

## 🚀 Quick Start Guide

### 📋 **Hardware Requirements**

| Component | Specification | Purpose |
|-----------|---------------|---------|
| **ESP32** | ESP32-WROOM-32 | Main controller |
| **W5500 Ethernet** | SPI interface | Primary network |
| **LCD 20x4** | I2C interface | Local display |
| **Rotary Encoder** | With push button | Menu navigation |
| **MicroSD Card** | Class 10+ recommended | Show recording |
| **LED Strips** | WS2812B/WS2811 | Light output |
| **Power Supply** | 5V, adequate current | System power |

### ⚡ **Installation & Setup**

#### 1️⃣ **Download & Build**
```bash
# Clone repository
git clone https://github.com/truongcongdinh97/ArtNet_LED-Controller-by-TCD.git
cd ArtNet_LED-Controller-by-TCD

# Build firmware (using PlatformIO)
platformio run -e esp32dev

# Upload firmware & web files
platformio run -e esp32dev -t upload -t uploadfs

# Monitor serial output
platformio device monitor -e esp32dev
```

#### 2️⃣ **Initial Configuration**
1. **🔌 Power on** the device and open Serial Monitor
2. **📶 Connect to WiFi hotspot**: `LED_Controller-Setup` (password: `12345678`)
3. **🌐 Open browser** to `http://192.168.4.1`
4. **⚙️ Configure settings**:
   - WiFi credentials for your network
   - LED output parameters
   - Art-Net universe mapping
5. **💾 Save & reboot** - device will connect to your network
6. **📝 Note the IP address** from Serial Monitor

#### 3️⃣ **Hardware Connections**
> 📌 **See detailed pinout diagram below**

```
🔌 Power: 5V to ESP32 + LED strips
🌐 Network: W5500 module via SPI
🖱️ Interface: LCD (I2C) + Rotary encoder  
💾 Storage: MicroSD card via SPI
💡 Outputs: 4x LED strip data lines
```

## 🔌 Hardware Pinout & Wiring

### 📊 **GPIO Assignment Table - OPTIMIZED v1.2.4**

> ✅ **Boot-safe optimization**: Tất cả GPIO assignments đã được tối ưu để tránh xung đột boot process

| **Function** | **GPIO** | **Notes** | **Module** |
|--------------|----------|-----------|------------|
| **🎵 I2S Audio (Reserved)** ||| *Future MAX98357* |
| BCLK | `26` | I2S Bit Clock | Audio expansion |
| LRCK | `25` | I2S Word Select | Audio expansion |  
| DATA | `27` | I2S Data Out | Audio expansion |
| **💡 LED Outputs** ||| *WS2812B/WS2811* |
| LED Strip 1 | `5` | Data line | FastLED |
| LED Strip 2 | `14` | Data line | FastLED |
| LED Strip 3 | `16` | Data line *(Boot-safe)* | FastLED |
| LED Strip 4 | `13` | Data line | FastLED |
| **🖱️ User Interface** ||| *Physical Controls* |
| LCD SDA | `21` | I2C Data | 20x4 Display |
| LCD SCL | `22` | I2C Clock | 20x4 Display |
| Encoder A | `32` | Rotation detect | Menu navigation |
| Encoder B | `33` | Rotation detect | Menu navigation |
| Encoder BTN | `0` | Push button *(Boot-safe)* | Menu select |
| Status LED | `19` | System status *(Boot-safe)* | Built-in LED |
| **🌐 Networking** ||| *W5500 Ethernet* |
| SPI MOSI | `23` | Shared SPI bus | Data out |
| SPI MISO | `19` | Shared SPI bus | Data in |
| SPI SCK | `18` | Shared SPI bus | Clock |
| W5500 CS | `4` | Chip select *(Boot-safe)* | Ethernet |
| W5500 RST | `2` | Reset control *(Boot-safe)* | Ethernet |
| **💾 Storage** ||| *MicroSD Card* |
| SD MOSI | `23` | Shared with Ethernet | Data out |
| SD MISO | `19` | Shared with Ethernet | Data in |
| SD SCK | `18` | Shared with Ethernet | Clock |
| SD CS | `17` | Chip select | Storage |

### 📐 **Wiring Diagram - OPTIMIZED**

```
ESP32-WROOM-32 [v1.2.4 - Boot-Safe GPIO]
┌─────────────────────────────────┐
│  ┌─────┐                       │
│  │ USB │  📶 WiFi + 🔌 Ethernet │
│  └─────┘                       │
├─[0]───────────────── Encoder BTN (Boot-safe)
├─[2]──── RST ─────── W5500 Module (Boot-safe)
├─[4]──── CS ──────── W5500 Module (Boot-safe)
├─[5]──────────────── LED Strip 1  
├─[13]─────────────── LED Strip 4
├─[14]─────────────── LED Strip 2
├─[16]─────────────── LED Strip 3 (Boot-safe)
├─[17]──── CS ──────── SD Card Module
├─[18]─ SCK ─────────  SPI Bus (Shared)
├─[19]─ MISO/Status──  SPI Bus + Status LED
├─[21]─ SDA ─────────  I2C LCD (20x4)
├─[22]─ SCL ─────────  I2C LCD (20x4)
├─[23]─ MOSI ────────  SPI Bus (Shared)
├─[25]─ I2S_LR ──────  Audio Reserved
├─[26]─ I2S_BCK ─────  Audio Reserved  
├─[27]─ I2S_DATA ────  Audio Reserved
├─[32]─ ENC_A ───────  Rotary Encoder
├─[33]─ ENC_B ───────  Rotary Encoder
└─────────────────────────────────┘

🎯 Key Improvements:
✅ GPIO 2,12,15 conflicts RESOLVED
✅ Boot-safe pin assignments
✅ Hardware SPI/I2C utilization
✅ I2S pins reserved for audio
```
├─[17]──── CS ──────── SD Card
├─[18]──── SCK ─────── SPI Bus (Shared)
├─[19]──── MISO ────── SPI Bus (Shared)  
├─[21]──── SDA ─────── LCD Display
├─[22]──── SCL ─────── LCD Display
├─[23]──── MOSI ────── SPI Bus (Shared)
├─[25]──── LRCK ───── 🔊 Audio (Future)
├─[26]──── BCLK ───── 🔊 Audio (Future)
├─[27]──── DATA ───── 🔊 Audio (Future)
├─[32]──── A ──────── Rotary Encoder
└─[33]──── B ──────── Rotary Encoder
```

### ⚡ **Power Requirements**

- **ESP32 Module**: 3.3V (regulated onboard)
- **LED Strips**: 5V DC (calculate: ~60mA per LED at full white)
- **Peripherals**: 3.3V-5V compatible
- **Recommended PSU**: 5V/10A+ for 300+ LEDs

> ⚠️ **Important**: Use adequate power supply and proper wiring for LED strips to avoid voltage drop and overheating.

## 🔧 Technical Specifications

### 📊 **System Performance - v1.2.4 Optimized**
- **Platform**: ESP32-WROOM-32 (240MHz, dual-core)
- **Memory Usage**: 19.3% RAM (63KB/328KB), 73.9% Flash (969KB/1.3MB)  
- **Art-Net**: Full protocol support, multi-universe with rate throttling
- **LED Control**: Up to 2,720 addressable LEDs (4×680)
- **Network**: Dual connectivity (Ethernet + WiFi) with auto-failover
- **Storage**: MicroSD for show recording/playbook with 4KB buffering
- **GPIO**: Boot-safe pin assignments, hardware SPI/I2C optimization

### 📚 **Dependencies & Libraries**

| Library | Version | Purpose |
|---------|---------|---------|
| [**FastLED**](https://github.com/FastLED/FastLED) | ^3.10.2 | LED strip control |
| [**ArtNet**](https://github.com/hideakitai/ArtNet) | ^0.8.3 | Art-Net protocol |
| [**ESPAsyncWebServer**](https://github.com/me-no-dev/ESPAsyncWebServer) | latest | Web interface |
| [**Ethernet**](https://github.com/arduino-libraries/Ethernet) | ^2.0.2 | W5500 support |
| [**LiquidCrystal_I2C**](https://github.com/johnrickman/LiquidCrystal_I2C) | latest | LCD display |
| [**Ai Esp32 Rotary Encoder**](https://github.com/igorantolic/ai-esp32-rotary-encoder) | ^1.7.0 | Encoder input |
| **ArduinoJson** | ^6.20.0 | Configuration |
| **AsyncTCP** | latest | Async networking |

### 🏗️ **Architecture Overview**

```
┌─────────────────────────────────────────────────────────┐
│                  🎭 Art-Net LED Controller               │
├─────────────────────────────────────────────────────────┤
│  📡 Network Layer                                       │
│  ├── Ethernet (W5500) ──┬── Art-Net Protocol           │
│  └── WiFi (ESP32)   ────┤                             │
├─────────────────────────────────────────────────────────┤  
│  🎮 Control Layer                                       │
│  ├── Web Interface ─────┬── Configuration              │
│  ├── LCD + Encoder ─────┤                             │
│  └── Serial Console ────┤                             │
├─────────────────────────────────────────────────────────┤
│  💡 Output Layer                                        │
│  ├── LED Controller ────┬── FastLED (4 outputs)        │
│  ├── DMX Sender ────────┤                             │
│  └── Status Indicators ─┤                             │
├─────────────────────────────────────────────────────────┤
│  💾 Storage Layer                                       │
│  ├── Configuration ─────┬── Flash (Preferences)        │
│  └── Show Recording ────┘── SD Card                    │
└─────────────────────────────────────────────────────────┘
```

## 🛠️ Development & Contributing

### 🧪 **Testing Checklist**
- [ ] **Hardware**: All GPIO connections verified
- [ ] **Network**: Ethernet & WiFi connectivity
- [ ] **Art-Net**: Multi-universe data reception  
- [ ] **LEDs**: All 4 outputs responding correctly
- [ ] **Web UI**: All configuration pages functional
- [ ] **Recording**: SD card read/write operations
- [ ] **Menu**: LCD display & rotary encoder navigation

### 📝 **Development Setup**
```bash
# Prerequisites
- PlatformIO IDE/CLI
- ESP32 development board
- Hardware components per requirements

# Development workflow
git clone <repository>
platformio run -e esp32dev         # Build
platformio run -e esp32dev -t upload   # Flash
platformio device monitor -e esp32dev  # Debug
```

### 🤝 **Contributing**
1. **Fork** the repository
2. **Create** feature branch (`git checkout -b feature/amazing-feature`)
3. **Commit** changes (`git commit -m 'Add amazing feature'`)
4. **Push** to branch (`git push origin feature/amazing-feature`)
5. **Open** a Pull Request

### 🐛 **Bug Reports & Issues**
Please use [GitHub Issues](https://github.com/truongcongdinh97/ArtNet_LED-Controller-by-TCD/issues) with:
- **Hardware** configuration details
- **Network** setup information  
- **Serial console** output
- **Steps to reproduce** the issue

## 📜 **Changelog**

### 🏷️ **v1.2.4** (Latest) - *Production-Ready Optimization*
- ✅ **CRITICAL**: Boot-safe GPIO assignments (resolved GPIO 2,12,15 conflicts)
- ✅ **PERFORMANCE**: Art-Net packet rate throttling implemented
- ✅ **RELIABILITY**: Playback timing optimization with config-based rates
- ✅ **ARCHITECTURE**: Main loop callback management improved
- ✅ **MEMORY**: 73.9% Flash usage (reduced 140 bytes)
- ✅ **GPIO**: Hardware SPI/I2C utilization optimized
- ✅ **STABILITY**: Boot reliability significantly improved
- ✅ **DOCS**: Comprehensive GPIO analysis and optimization guide

### 🏷️ **v1.2.3** - *GPIO Optimization & Critical Fixes*
- ✅ **Fixed**: GPIO pin conflicts resolved
- ✅ **Added**: I2S pins reserved for future audio expansion
- ✅ **Improved**: LED output assignments optimized
- ✅ **Fixed**: SD card initialization bug
- ✅ **Added**: Comprehensive GPIO documentation
- ✅ **Optimized**: Memory usage (19% RAM, 74% Flash)

### 🏷️ **v1.4.0** - *Enhanced DMX & Playback*
- ✅ Enhanced DMX streaming features
- ✅ Improved playbook functionality  
- ✅ Updated documentation

### 🏷️ **v1.0.3** - *Initial Release*
- ✅ Core Art-Net functionality
- ✅ Basic LED control
- ✅ Web configuration interface

## 📄 License

**MIT License** © 2025 [Truong Cong Dinh](https://github.com/truongcongdinh97)

```
Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software...
```

## 🙏 **Acknowledgments**

- **ESP32 Community** for excellent development resources
- **Art-Net** protocol creators for lighting industry standard
- **FastLED** team for powerful LED control library
- **PlatformIO** for streamlined development environment
- **Contributors** who helped improve this project

---

<div align="center">

### 🌟 **Support This Project**

If this project helps you, please give it a ⭐ on GitHub!

[![GitHub stars](https://img.shields.io/github/stars/truongcongdinh97/ArtNet_LED-Controller-by-TCD?style=social)](https://github.com/truongcongdinh97/ArtNet_LED-Controller-by-TCD/stargazers)
[![GitHub forks](https://img.shields.io/github/forks/truongcongdinh97/ArtNet_LED-Controller-by-TCD?style=social)](https://github.com/truongcongdinh97/ArtNet_LED-Controller-by-TCD/network)

**Made with ❤️ for the lighting community**

</div>