#include "Recording.h"
#include <SD.h>

namespace Recording {
  // --- Buffering Configuration ---
  const size_t BUFFER_SIZE = 4096; // 4KB buffer
  static uint8_t recordBuffer[BUFFER_SIZE];
  static size_t bufferIndex = 0;
  // ---------------------------

  static File activeFile;
  static bool recording = false;

  // Helper function to write the buffer to the SD card
  void flushBuffer() {
    if (bufferIndex > 0 && activeFile) {
      activeFile.write(recordBuffer, bufferIndex);
    }
    bufferIndex = 0;
  }

  void begin() {
    // No initialization needed here
  }

  void loop() {
    // The buffer is flushed automatically when full or when stopping.
    // A time-based flush could be added here if needed, but is often unnecessary.
  }

  void start() {
    if (recording) {
        stop(); // Ensure previous recording is saved and stopped
    }

    int idx = 0;
    char fname[20];
    do {
      snprintf(fname, sizeof(fname), "/Show%03d.dat", idx);
      if (!SD.exists(fname)) break;
      idx++;
    } while (idx < 1000);

    activeFile = SD.open(fname, FILE_WRITE);
    if (activeFile) {
        recording = true;
        bufferIndex = 0; // Reset buffer for the new file
        Serial.print("[Recording] Started file: ");
        Serial.println(fname);
    } else {
        Serial.print("[Recording] Failed to start file: ");
        Serial.println(fname);
    }
  }

  void stop() {
    if (recording) {
        Serial.println("[Recording] Stopping...");
        flushBuffer(); // Write any remaining data
        if (activeFile) {
            activeFile.close();
        }
        recording = false;
        Serial.println("[Recording] Stopped.");
    }
  }

  void recordPacket(uint16_t universe, uint16_t length, const uint8_t* data) {
    if (!recording || !activeFile) return;

    size_t packetSize = sizeof(universe) + sizeof(length) + length;

    // If the packet doesn't fit in the remaining buffer, flush the buffer first.
    if (bufferIndex + packetSize > BUFFER_SIZE) {
        flushBuffer();
    }

    // Copy data into the buffer
    memcpy(recordBuffer + bufferIndex, &universe, sizeof(universe));
    bufferIndex += sizeof(universe);
    memcpy(recordBuffer + bufferIndex, &length, sizeof(length));
    bufferIndex += sizeof(length);
    memcpy(recordBuffer + bufferIndex, data, length);
    bufferIndex += length;
  }

  bool isRecording() {
    return recording;
  }
}