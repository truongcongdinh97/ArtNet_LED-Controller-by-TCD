#ifndef DMXSENDER_H
#define DMXSENDER_H

#include <Arduino.h>
#include <Udp.h> // Use the generic UDP class

class DMXSender {
public:
    /**
     * @brief Initializes the DMX sender.
     * @param udp Pointer to the active UDP instance (WiFi or Ethernet).
     * @param dmxReceiverIp The IP address of the ArtNet/DMX receiver.
     * @param packetRate The target packet rate (packets per second).
     */
    void begin(UDP* udp, const IPAddress& dmxReceiverIp, uint16_t packetRate);

    /**
     * @brief Sends a DMX packet for a specific universe.
     * @param universe The DMX universe number.
     * @param data Pointer to the 512-byte DMX data array.
     * @param length The number of channels to send (usually 512).
     */
    void sendPacket(uint16_t universe, const uint8_t* data, uint16_t length);

private:
    UDP* _udp = nullptr; // Pointer to the active UDP instance
    IPAddress _dmxReceiverIp;
    uint16_t _dmxPort = 6454; // Default ArtNet port
    uint16_t _packetRate;
    uint8_t _artnetPacket[530]; // Buffer for the ArtNet packet (18 header + 512 data)
};

extern DMXSender dmxSender;

#endif // DMXSENDER_H