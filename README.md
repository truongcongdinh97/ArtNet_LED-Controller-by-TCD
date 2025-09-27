# ArtNet LED Controller by TCD

Một bộ điều khiển LED đa năng, chuyên nghiệp dựa trên ESP32, được thiết kế cho các ứng dụng ánh sáng từ đơn giản đến phức tạp.

## Giới thiệu

Dự án này biến một bo mạch ESP32 thành một "bộ não" trung tâm cho hệ thống ánh sáng, có khả năng giao tiếp qua mạng bằng chuẩn Art-Net. Nó có thể nhận tín hiệu từ các phần mềm điều khiển chuyên nghiệp, điều khiển trực tiếp hàng ngàn đèn LED, ghi lại các buổi trình diễn để hoạt động độc lập, và thậm chí chuyển tiếp tín hiệu đến các thiết bị khác trong hệ thống.

## Tính năng nổi bật

- **Điều khiển đa năng:**
  - **Nhận Art-Net:** Lắng nghe tín hiệu Art-Net và điều khiển trực tiếp các dải LED WS2812B (hoặc tương tự) với thư viện FastLED.
  - **Gửi Art-Net:** Chuyển tiếp tín hiệu DMX (được đóng gói trong Art-Net) đến một địa chỉ IP khác trong mạng.
- **Ghi và Phát lại (Record & Playback):**
  - Ghi lại các luồng Art-Net vào thẻ nhớ SD.
  - Phát lại các file đã ghi một cách độc lập mà không cần kết nối với máy tính.
  - Sử dụng cơ chế đệm (buffering) để tối ưu hiệu năng, cho phép ghi nhiều universe một cách mượt mà.
- **Kết nối mạng linh hoạt:**
  - Hỗ trợ cả **Ethernet (W5500)** và **Wi-Fi**.
  - Ưu tiên Ethernet, nếu không thành công sẽ tự động chuyển sang kết nối Wi-Fi đã cấu hình (STA mode).
  - Nếu cả hai đều thất bại, thiết bị sẽ tự phát ra một mạng Wi-Fi Access Point (`LED_Controller-Setup`) để cấu hình ban đầu.
- **Cấu hình toàn diện qua Web:**
  - Giao diện web trực quan để cấu hình mọi thông số.
  - Cho phép bật/tắt output LED cục bộ, biến thiết bị thành một bộ chuyển đổi/ghi Art-Net thuần túy.
- **Giao diện vật lý:**
  - Màn hình LCD và núm xoay (Rotary Encoder) cho phép điều khiển trực tiếp các chế độ hoạt động.
- **Nâng cấp từ xa (OTA):** Cập nhật firmware của thiết bị qua giao diện web mà không cần kết nối vật lý.

## Giao diện điều khiển

### 1. Giao diện Web

Truy cập vào địa chỉ IP của thiết bị trên trình duyệt để vào giao diện quản lý.

- **Trang cấu hình chính (`/config.html`):**
  - Cấu hình Wi-Fi (SSID & Mật khẩu).
  - Cấu hình mạng (IP tĩnh, Subnet).
  - Cấu hình LED (Số output, số LED mỗi output, universe bắt đầu).
  - **Bật/Tắt LED cục bộ:** Cho phép chỉ chuyển tiếp tín hiệu Art-Net mà không điều khiển dải LED được gắn trực tiếp.

- **Trang cấu hình DMX (`/config_dmx.html`):**
  - Cấu hình cho chức năng gửi Art-Net đi.
  - **ArtNet IP:** Địa chỉ IP của thiết bị sẽ nhận tín hiệu.
  - **Số lượng Universe:** Số lượng universe DMX sẽ được gửi đi (tối đa 8).
  - **Packet Rate:** Tốc độ gửi gói tin (fps).

- **Trang cập nhật OTA (`/update`):**
  - Dùng để tải lên file firmware `.bin` mới.

### 2. Giao diện LCD & Núm xoay

Menu vật lý cho phép chuyển đổi nhanh giữa các chế độ:

- **Streaming:** Chế độ mặc định, nhận và hiển thị tín hiệu Art-Net theo thời gian thực.
- **Recording:** Bắt đầu hoặc dừng quá trình ghi dữ liệu Art-Net vào thẻ nhớ.
- **Playback:** Hiển thị danh sách các file đã ghi, cho phép chọn file để phát lại với các tùy chọn (phát một lần, lặp lại 1 file, lặp lại tất cả).

## Hướng dẫn cài đặt và sử dụng

### Yêu cầu phần cứng

- Bo mạch ESP32.
- Module Ethernet W5500.
- Màn hình LCD I2C.
- Núm xoay (Rotary Encoder).
- Khe đọc thẻ nhớ SD.
- Dải LED WS2812B hoặc tương tự.

### Cài đặt và nạp code

```sh
# Clone repository
git clone https://github.com/truongcongdinh97/ArtNet_LED-Controller-by-TCD.git
cd ArtNet_LED-Controller

# Build firmware
pio run -e esp32dev

# Nạp firmware và hệ thống file SPIFFS (cho giao diện web)
pio run -e esp32dev -t uploadfs -t upload

# Mở Serial Monitor để xem log và địa chỉ IP
pio device monitor -e esp32dev
```

### Cấu hình lần đầu

1.  Nạp code và mở Serial Monitor.
2.  Nếu thiết bị không thể kết nối Ethernet hoặc Wi-Fi đã lưu, nó sẽ tự phát ra một mạng Wi-Fi:
    - **SSID:** `LED_Controller-Setup`
    - **Mật khẩu:** `12345678`
3.  Kết nối máy tính của bạn vào mạng Wi-Fi này.
4.  Mở trình duyệt và truy cập địa chỉ `http://192.168.4.1`.
5.  Vào trang cấu hình, nhập thông tin mạng Wi-Fi của bạn và các thông số khác.
6.  Lưu cấu hình, thiết bị sẽ tự khởi động lại và kết nối vào mạng của bạn.
7.  Xem lại Serial Monitor để lấy địa chỉ IP mới của thiết bị trong mạng của bạn.

## Sơ đồ chân (Pinout)

```c
// Tham khảo trong src/PinConfig.h
// I2S (MAX98357) - Dự phòng cho tương lai
#define GPIO_I2S_BCLK    26
#define GPIO_I2S_LRCK    25  
#define GPIO_I2S_DATA    27

// LED Outputs
#define GPIO_LED_OUT_1   5
#define GPIO_LED_OUT_2   14
#define GPIO_LED_OUT_3   12  // Thay thế cho GPIO 27
#define GPIO_LED_OUT_4   13  // Thay thế cho GPIO 26

// LCD I2C
#define GPIO_LCD_SDA     21
#define GPIO_LCD_SCL     22

// Rotary Encoder
#define GPIO_ROTARY_A    32
#define GPIO_ROTARY_B    33
#define GPIO_ROTARY_BTN  4   // Thay thế cho GPIO 25

// Status LED
#define GPIO_STATUS_LED  2

// W5500 Ethernet (SPI)
#define GPIO_W5500_MOSI  23
#define GPIO_W5500_MISO  19
#define GPIO_W5500_SCK   18
#define GPIO_W5500_CS    15
#define GPIO_W5500_RST   16  // Thay thế cho GPIO 12

// SD Card (SPI) - Chia sẻ với Ethernet
#define GPIO_SD_MOSI     23  // Chia sẻ với Ethernet
#define GPIO_SD_MISO     19  // Chia sẻ với Ethernet
#define GPIO_SD_SCK      18  // Chia sẻ với Ethernet
#define GPIO_SD_CS       17  // Chân chọn chip riêng
```

## Thư viện chính

- [hideakitai/ArtNet](https://github.com/hideakitai/ArtNet)
- [FastLED](https://github.com/FastLED/FastLED)
- [ESPAsyncWebServer](https://github.com/me-no-dev/ESPAsyncWebServer)
- ArduinoJson
- Và các thư viện chuẩn của PlatformIO (Preferences, SPIFFS, WiFi, Ethernet...)

## License

MIT © 2025 Truong Cong Dinh