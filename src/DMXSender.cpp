#include "DMXSender.h"

void DMXSender::begin(UDP* udp, const IPAddress& dmxReceiverIp, uint16_t packetRate) {
    _udp = udp; // Store the pointer to the active UDP object
    _dmxReceiverIp = dmxReceiverIp;
    _packetRate = packetRate;
}

void DMXSender::sendPacket(uint16_t universe, const uint8_t* data, uint16_t length) {
    if (!_udp) return; // Don't send if UDP is not initialized

    // Art-Net packet structure
    // Header (18 bytes)
    memcpy(_artnetPacket, "Art-Net\0", 8);
    _artnetPacket[8] = 0x00; // OpCodeLo
    _artnetPacket[9] = 0x50; // OpCodeHi (OpDmx)
    _artnetPacket[10] = 0x00; // ProtVerHi
    _artnetPacket[11] = 14;   // ProtVerLo
    _artnetPacket[12] = 0x00; // Sequence (not used)
    _artnetPacket[13] = 0x00; // Physical (not used)
    _artnetPacket[14] = universe & 0xFF; // Sub-Uni
    _artnetPacket[15] = (universe >> 8) & 0xFF; // Net
    _artnetPacket[16] = (length >> 8) & 0xFF; // LengthHi
    _artnetPacket[17] = length & 0xFF;      // LengthLo

    // DMX Data (max 512 bytes)
    memcpy(_artnetPacket + 18, data, length);

    // Send UDP packet
    _udp->beginPacket(_dmxReceiverIp, _dmxPort);
    _udp->write(_artnetPacket, 18 + length);
    _udp->endPacket();
}

// Global instance of the DMXSender
DMXSender dmxSender;