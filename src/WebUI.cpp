#include "WebUI.h"
#include "ConfigManager.h"
#include <WiFi.h>
#include <Ethernet.h>
#include <ESPAsyncWebServer.h>
#include <SPIFFS.h>
#include "PinConfig.h"
#include <EthernetUdp.h>
#include <WiFiUdp.h>
#include <Update.h>

// Network instances
static EthernetUDP ethUdp;
static WiFiUDP wifiUdp;
static UDP* activeUdp = nullptr;
static const uint16_t ARTNET_PORT = 6454;

// Web server
static AsyncWebServer server(80);

// Hàm private để khởi tạo mạng
static void initialize_network() {
    // Load and debug config
    Config cfg = ConfigManager::getConfig();
    Serial.print("[WebUI] Loaded WiFi SSID: '"); Serial.print(cfg.wifiSSID);
    Serial.print("' PASS: '"); Serial.print(cfg.wifiPass); Serial.println("'");

    // 1) Ethernet
    byte mac[] = {0xDE,0xAD,0xBE,0xEF,0xFE,0xED};
    Ethernet.init(GPIO_W5500_CS);
    if (Ethernet.begin(mac, 10000) && Ethernet.linkStatus()==LinkON) {
        Serial.print("[WebUI] Ethernet OK. IP="); Serial.println(Ethernet.localIP());
        if (ethUdp.begin(ARTNET_PORT)) { activeUdp = &ethUdp; return; }
    }
    Serial.println("[WebUI] Ethernet failed.");

    // 2) WiFi STA if configured
    if (cfg.wifiSSID.length() > 0) {
        Serial.print("[WebUI] Connecting STA to '"); Serial.print(cfg.wifiSSID); Serial.println("'");
        WiFi.mode(WIFI_STA);
        WiFi.begin(cfg.wifiSSID.c_str(), cfg.wifiPass.c_str());
        uint8_t to = 20;
        while (WiFi.status() != WL_CONNECTED && to--) { Serial.print("."); delay(500); }
        Serial.println();
        if (WiFi.status() == WL_CONNECTED) {
            Serial.print("[WebUI] STA OK. IP="); Serial.println(WiFi.localIP());
            if (wifiUdp.begin(ARTNET_PORT)) { activeUdp = &wifiUdp; return; }
        }
        Serial.println("[WebUI] STA failed.");
    } else {
        Serial.println("[WebUI] No SSID configured, skipping STA.");
    }

    // 3) AP fallback
    Serial.println("[WebUI] Starting AP mode in 5s...");
    for (int i = 5; i > 0; i--) { Serial.printf("[WebUI] AP in %d...\n", i); delay(1000); }
    WiFi.mode(WIFI_AP);
    WiFi.softAP("LED_Controller-Setup", "12345678");
    Serial.print("[WebUI] AP SSID=LED_Controller-Setup, IP="); Serial.println(WiFi.softAPIP());
    wifiUdp.begin(ARTNET_PORT);
    activeUdp = &wifiUdp;
}

void WebUI::begin() {
    // Khởi tạo mạng trước
    initialize_network();

    // Khởi động SPIFFS
    if (!SPIFFS.begin(true)) {
        Serial.println("[WebUI] SPIFFS Mount Failed");
    }

    // Cấu hình các route cho web server
    server.on("/", HTTP_GET, [](AsyncWebServerRequest *request){
        request->redirect("/config.html");
    });
    server.serveStatic("/", SPIFFS, "/");

    server.on("/config", HTTP_GET, [](AsyncWebServerRequest *request){
        Config cfg = ConfigManager::getConfig();
        String json = "{";
        json += "\"wifiSSID\":\"" + cfg.wifiSSID + "\",";
        json += "\"localIP\":\"" + cfg.localIP.toString() + "\",";
        json += "\"outputs\":" + String(cfg.outputs) + ",";
        json += "\"ledsPerOutput\":" + String(cfg.ledsPerOutput) + ",";
        json += "\"startUniverse\":" + String(cfg.startUniverse) + ",";
        json += "\"enableLocalLeds\": " + String(cfg.enableLocalLeds ? "true" : "false");
        json += "}";
        request->send(200, "application/json", json);
    });

    server.on("/config", HTTP_POST, [](AsyncWebServerRequest *request){
        Config cfg = ConfigManager::getConfig();
        if (request->hasParam("wifiSSID", true)) cfg.wifiSSID = request->getParam("wifiSSID", true)->value();
        if (request->hasParam("wifiPass", true)) cfg.wifiPass = request->getParam("wifiPass", true)->value();
        if (request->hasParam("localIP", true)) cfg.localIP.fromString(request->getParam("localIP", true)->value());
        if (request->hasParam("outputs", true)) cfg.outputs = request->getParam("outputs", true)->value().toInt();
        if (request->hasParam("ledsPerOutput", true)) cfg.ledsPerOutput = request->getParam("ledsPerOutput", true)->value().toInt();
        if (request->hasParam("startUniverse", true)) cfg.startUniverse = request->getParam("startUniverse", true)->value().toInt();
        
        // Handle checkbox: it's only present if checked
        cfg.enableLocalLeds = request->hasParam("enableLocalLeds", true);

        ConfigManager::saveConfig(cfg);
        String response = "Config saved. Rebooting...";
        request->send(200, "text/plain", response);
        delay(1000);
        ESP.restart();
    });

    // DMX config page
    server.on("/config_dmx", HTTP_GET, [](AsyncWebServerRequest *request){
        request->send(SPIFFS, "/config_dmx.html", "text/html");
    });
    server.on("/set_dmx", HTTP_POST, [](AsyncWebServerRequest *request){
        Config cfg = ConfigManager::getConfig();
        if (request->hasParam("dmx_ip", true)) cfg.dmxReceiverIp.fromString(request->getParam("dmx_ip", true)->value());
        if (request->hasParam("dmx_universe", true)) cfg.numDmxUniverses = request->getParam("dmx_universe", true)->value().toInt();
        if (request->hasParam("dmx_rate", true)) cfg.dmxPacketRate = request->getParam("dmx_rate", true)->value().toInt();
        ConfigManager::saveConfig(cfg);
        request->send(200, "text/plain", "DMX config saved. Rebooting...");
        delay(1000);
        ESP.restart();
    });

    // OTA firmware update handler
    server.on("/update", HTTP_POST,
      [](AsyncWebServerRequest *request){
        request->send(200, "text/plain", "OK");
        ESP.restart();
      },
      [](AsyncWebServerRequest *request, const String& filename, size_t index, uint8_t *data, size_t len, bool final){
        if (index == 0) {
          Serial.println("[WebUI] OTA Start");
          Update.begin(UPDATE_SIZE_UNKNOWN);
        }
        Update.write(data, len);
        if (final) {
          if (Update.end(true)) Serial.println("[WebUI] OTA Success");
          else Serial.printf("[WebUI] OTA Error %u\n", Update.getError());
        }
      }
    );

    // Khởi động server
    server.begin();
    Serial.println("[WebUI] Web server started.");
}

void WebUI::loop() {
    // Không cần làm gì ở đây
}

UDP* WebUI::getUDP() {
    return activeUdp;
}