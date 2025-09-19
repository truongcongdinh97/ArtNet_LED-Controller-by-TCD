#include "ConfigManager.h"
#include <Preferences.h>

static Preferences prefs;
static Config config;

Config::Config() {
    wifiSSID      = "";
    wifiPass      = "";
    localIP       = IPAddress(0,0,0,0);
    outputs       = 4;
    ledsPerOutput = 170;
    startUniverse = 1;
    dmxReceiverIp = IPAddress(192,168,1,100);
    numDmxUniverses = 1; // Default to 1 universe
    dmxPacketRate  = 30;
    enableLocalLeds = true; // Default to enabled
}

void ConfigManager::begin() {
  prefs.begin("artnetcfg", false);

  config.wifiSSID = prefs.getString("ssid", "ESP32");
  config.wifiPass = prefs.getString("pass", "12345678");
  config.localIP.fromString(prefs.getString("localIP", "192.168.1.50"));

  config.outputs = prefs.getInt("outputs", 4);
  config.ledsPerOutput = prefs.getInt("leds", 680);
  config.startUniverse = prefs.getInt("startUni", 0);

  // Load DMX settings
  config.dmxReceiverIp.fromString(prefs.getString("dmxIp", "192.168.1.100"));
  config.numDmxUniverses = prefs.getInt("dmxUni", 1); // Key is dmxUni
  config.dmxPacketRate = prefs.getInt("dmxRate", 30);

  config.enableLocalLeds = prefs.getBool("enLeds", true);

  Serial.println("Config loaded.");
}

void ConfigManager::saveConfig(const Config& cfg) {
  prefs.putString("ssid", cfg.wifiSSID);
  prefs.putString("pass", cfg.wifiPass);
  prefs.putString("localIP", cfg.localIP.toString());
  prefs.putInt("outputs", cfg.outputs);
  prefs.putInt("leds", cfg.ledsPerOutput);
  prefs.putInt("startUni", cfg.startUniverse);
  
  // Save DMX settings
  prefs.putString("dmxIp", cfg.dmxReceiverIp.toString());
  prefs.putInt("dmxUni", cfg.numDmxUniverses); // Key is dmxUni
  prefs.putInt("dmxRate", cfg.dmxPacketRate);
  prefs.putBool("enLeds", cfg.enableLocalLeds);
}

Config ConfigManager::getConfig() {
  return config;
}