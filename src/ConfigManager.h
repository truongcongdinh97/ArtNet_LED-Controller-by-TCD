#pragma once
#include <Arduino.h>

struct Config {
  String wifiSSID;
  String wifiPass;
  IPAddress localIP;
  int outputs;
  int ledsPerOutput;
  int startUniverse; // Universe bắt đầu cho output 1
  IPAddress dmxReceiverIp; // Địa chỉ IP thiết bị nhận DMX
  int numDmxUniverses;    // Số lượng universe DMX để gửi đi
  uint16_t dmxPacketRate; // Gói DMX gửi mỗi giây
  bool enableLocalLeds;   // Bật/tắt output LED cục bộ
  // Tên thiết bị cố định
  static constexpr const char* deviceName = "LED_Controller";

  Config();  // default constructor declaration
};

namespace ConfigManager {
  void begin();
  void saveConfig(const Config& cfg);
  Config getConfig();
}
