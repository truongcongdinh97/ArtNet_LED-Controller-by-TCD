#include <Arduino.h>
#include <WiFi.h>
#include <WiFiUdp.h>
#include <ArtnetWiFi.h>        // Only WiFi-based Art-Net
#include "ConfigManager.h"
#include "DMXSender.h"
#include "LEDController.h"
#include "SDManager.h"
#include "MenuManager.h"
#include "WebUI.h"
#include "PlaybackController.h"
#include "Recording.h"

static ArtnetWiFi artnet;
static OperatingMode lastMode;

void setup() {
    Serial.begin(115200);
    Serial.println("\nSystem starting...");

    // 1. Core modules
    ConfigManager::begin();
    LEDController::begin();

    // 2. SD card
    SDManager::begin();
    if (SDManager::isAvailable()) {
        auto files = SDManager::listFiles("/");
        MenuManager::setFileList(files);
        PlaybackController::setFiles(files);
    }
    Recording::begin();
    PlaybackController::begin();

    // 3. Network & Web UI
    WebUI::begin();
    // 3.1 DMX Sender init
    Config cfg = ConfigManager::getConfig();
    dmxSender.begin(WebUI::getUDP(), cfg.dmxReceiverIp, cfg.dmxPacketRate);

    // 4. Art-Net node over Wi-Fi
    artnet.begin();
    artnet.subscribeArtDmx([](const uint8_t* data,
                              uint16_t size,
                              const ArtDmxMetadata& metadata,
                              const ArtNetRemoteInfo& remote) {
        LEDController::updateFromArtnet(metadata.universe, size, data);
    });

    // 5. Menu & LCD
    MenuManager::begin();
    lastMode = MenuManager::getMode();
}

void loop() {
    MenuManager::loop();
    WebUI::loop();

    auto currentMode = MenuManager::getMode();

    if (currentMode == MODE_STREAMING || currentMode == MODE_RECORDING) {
        artnet.parse();
    }

    if (currentMode == MODE_PLAYBACK) {
        PlaybackController::loop();
    }

    if (currentMode != lastMode) {
        // Clear previous subscriptions to avoid conflicts
        if (lastMode == MODE_RECORDING || lastMode == MODE_STREAMING) {
            // Note: ArtnetWiFi doesn't have unsubscribe, so we handle this by mode checking
        }
        
        if (currentMode == MODE_RECORDING) {
            Serial.println("[Main] Entering RECORDING mode");
            artnet.subscribeArtDmx([](const uint8_t* data,
                                      uint16_t size,
                                      const ArtDmxMetadata& metadata,
                                      const ArtNetRemoteInfo&) {
                Recording::recordPacket(metadata.universe, size, data);
            });
        } else if (currentMode == MODE_STREAMING) {
            Serial.println("[Main] Entering STREAMING mode");
            artnet.subscribeArtDmx([](const uint8_t* data,
                                      uint16_t size,
                                      const ArtDmxMetadata& metadata,
                                      const ArtNetRemoteInfo&) {
                // Forward to DMX sender and update LEDs
                dmxSender.sendPacket(metadata.universe, data, size);
                LEDController::updateFromArtnet(metadata.universe, size, data);
            });
        }
        
        if (currentMode != MODE_PLAYBACK && lastMode == MODE_PLAYBACK) {
            Serial.println("[Main] Stopping PLAYBACK mode");
            PlaybackController::stop();
        }
        
        lastMode = currentMode;
    }
}