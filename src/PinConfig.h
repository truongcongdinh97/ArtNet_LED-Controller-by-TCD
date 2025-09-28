#pragma once

// ================================================================================================
// GPIO PIN CONFIGURATION FOR ARTNET LED CONTROLLER
// ================================================================================================
// Định nghĩa các chân GPIO sử dụng cho toàn bộ dự án
// Sửa đổi tại đây sẽ đồng bộ cho tất cả các module
//
// ⚠️  QUAN TRỌNG: Không được trùng lặp GPIO giữa các chức năng khác nhau
// ⚠️  ESP32 có một số chân có giới hạn đặc biệt, vui lòng tham khảo datasheet
// ================================================================================================

// I2S (MAX98357) - Dự phòng cho tương lai
// Các chân I2S chuyên dụng cho âm thanh (hiện chưa sử dụng)
#define GPIO_I2S_BCLK    26  // I2S bit clock
#define GPIO_I2S_LRCK    25  // I2S word select (left/right channel)
#define GPIO_I2S_DATA    27  // I2S data out

// LED Outputs - FastLED WS2812B/WS2811
// Hỗ trợ tối đa 4 output, mỗi output có thể điều khiển 680 LED
#define GPIO_LED_OUT_1   5
#define GPIO_LED_OUT_2   14
#define GPIO_LED_OUT_3   16  // Thay đổi từ GPIO 12 (tránh boot voltage selector)
#define GPIO_LED_OUT_4   13  // Thay thế cho GPIO 26 (để dành cho I2S)

// LCD I2C (20x4 Character Display)
// Sử dụng chân I2C chuẩn của ESP32
#define GPIO_LCD_SDA     21  // I2C data line (cố định)
#define GPIO_LCD_SCL     22  // I2C clock line (cố định)

// Rotary Encoder với nút nhấn
// Cho phép điều khiển menu và chọn chế độ hoạt động
#define GPIO_ROTARY_A    32  // Encoder channel A 
#define GPIO_ROTARY_B    33  // Encoder channel B
#define GPIO_ROTARY_BTN  0   // Encoder push button - Thay đổi từ GPIO 4 (tối ưu hóa)

// Status LED
// LED đơn hiển thị trạng thái hoạt động (xanh=streaming, đỏ=recording, v.v.)
#define GPIO_STATUS_LED  19  // Thay đổi từ GPIO 2 (tránh boot sensitive pin)

// W5500 Ethernet Module (SPI Interface)
// Kết nối mạng chính, ưu tiên cao hơn WiFi
#define GPIO_W5500_MOSI  23  // SPI Master Out Slave In
#define GPIO_W5500_MISO  19  // SPI Master In Slave Out  
#define GPIO_W5500_SCK   18  // SPI Clock
#define GPIO_W5500_CS    4   // Chip Select - Thay đổi từ GPIO 15 (tránh boot debug)
#define GPIO_W5500_RST   2   // Reset pin - Thay đổi từ GPIO 16 (tối ưu hóa)

// SD Card Module (SPI Interface)
// Chia sẻ bus SPI với Ethernet, chỉ khác CS
#define GPIO_SD_MOSI     23  // Chia sẻ với Ethernet
#define GPIO_SD_MISO     19  // Chia sẻ với Ethernet  
#define GPIO_SD_SCK      18  // Chia sẻ với Ethernet
#define GPIO_SD_CS       17  // Chip Select riêng biệt cho SD Card

// ================================================================================================
// BẢNG TỔNG KẾT SỬ DỤNG GPIO - PHIÊN BẢN TỐI ƯU
// ================================================================================================
// GPIO  | Chức năng        | Module           | Lưu ý
// ------|------------------|------------------|------------------------------------------
// 0     | Button           | RotaryEncoder    | Boot button (pullup) - Safe for input
// 2     | W5500 RST        | Ethernet         | Reset control - Safe for output
// 4     | W5500 CS         | Ethernet         | SPI Chip Select - Safe
// 5     | LED Output 1     | FastLED          | WS2812B data pin - Optimal
// 13    | LED Output 4     | FastLED          | WS2812B data pin - Safe
// 14    | LED Output 2     | FastLED          | WS2812B data pin - Safe
// 16    | LED Output 3     | FastLED          | WS2812B data pin - Safe (was PSRAM)
// 17    | SD Card CS       | SD Manager       | SPI Chip Select - Safe
// 18    | SPI SCK          | Ethernet + SD    | Hardware SPI clock - Optimal
// 19    | Status LED       | StatusLED        | LED + SPI MISO shared - Acceptable
// 21    | I2C SDA          | LCD              | Hardware I2C data - Optimal
// 22    | I2C SCL          | LCD              | Hardware I2C clock - Optimal
// 23    | SPI MOSI         | Ethernet + SD    | Hardware SPI MOSI - Optimal
// 25    | I2S LRCK         | MAX98357 (dự phòng) | Audio left/right - Reserved
// 26    | I2S BCLK         | MAX98357 (dự phòng) | Audio bit clock - Reserved
// 27    | I2S DATA         | MAX98357 (dự phòng) | Audio data out - Reserved
// 32    | Encoder A        | RotaryEncoder    | ADC capable - Good for encoder
// 33    | Encoder B        | RotaryEncoder    | ADC capable - Good for encoder
// ================================================================================================

// Các module khác có thể bổ sung tại đây

