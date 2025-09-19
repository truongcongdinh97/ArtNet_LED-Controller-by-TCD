#include "ArtnetHandler.h"
#include "LEDController.h"
#include <Arduino.h>
#include "ConfigManager.h"  // for deviceName
#include <IPAddress.h>
#include "SendArtPollReply.h"  // add at top

// Art-Net opcodes
static const uint16_t OpPoll      = 0x2000;
static const uint16_t OpPollReply = 0x2100;

static UDP* udp = nullptr;

static const uint16_t ARTNET_PORT = 6454;
static uint8_t packetBuf[600]; // Art-Net tối đa 530 + chút dư
static ArtnetHandler::DmxPacketCallback dmxCallback = nullptr;

void ArtnetHandler::setDmxPacketCallback(DmxPacketCallback cb) {
  dmxCallback = cb;
}

void ArtnetHandler::begin(UDP* udp_instance) {
  udp = udp_instance;
  if (udp) {
    Serial.println("[ArtnetHandler] Started.");
  } else {
    Serial.println("[ArtnetHandler] Error: UDP instance is null.");
  }
}

void ArtnetHandler::loop() {
  if (udp == nullptr) return;

  int packetSize = udp->parsePacket();
  if (packetSize <= 0) return;
  if (packetSize > (int)sizeof(packetBuf)) packetSize = sizeof(packetBuf);

  int len = udp->read(packetBuf, packetSize);
  if (len <= 0) return;

  // Minimal Art-Net header check (allow Poll: len>=14)
  const char artHeader[] = "Art-Net";
  if (len < 14 || memcmp(packetBuf, artHeader, 7) != 0 || packetBuf[7] != 0) {
    return; // Not Art-Net packet
  }

  // opcode (little endian)
  uint16_t opcode = packetBuf[8] | (packetBuf[9] << 8);
  // Debug: log opcode of incoming packet
  Serial.printf("[ArtnetHandler] Packet received: size=%d, opcode=0x%04X\n", packetSize, opcode);

  // handle ArtPoll
  if (opcode == OpPoll) {
    sendArtPollReply(udp);
    return;
  }

  const uint16_t OpDmx = 0x5000;
  if (opcode != OpDmx) return;
  // Ensure DMX packet has full header (18 bytes)
  if (len < 18) return;

  // Extract universe and data length
  uint16_t universe = packetBuf[14] | (packetBuf[15] << 8);
  uint16_t dataLen = (packetBuf[16] << 8) | packetBuf[17];
  if (dataLen == 0 || dataLen > (len - 18)) dataLen = len - 18;
  uint8_t* dataPtr = packetBuf + 18;

  // Debug: log received packet
  Serial.printf("[ArtnetHandler] Received DMX packet: Universe=%u, Length=%u\n", universe, dataLen);

  // Gửi dữ liệu đến LEDController
  LEDController::updateFromArtnet(universe, dataLen, dataPtr);
  
  // Gọi callback nếu đã được set (dùng cho việc ghi file)
  if (dmxCallback) {
    dmxCallback(universe, dataLen, dataPtr);
  }
}