#pragma once
#include <Arduino.h>
#include <vector>

// SDManager provides a low-level interface to the SD card.
// It manages a single active file for reading.
namespace SDManager {
  void begin();
  bool isAvailable();
  std::vector<String> listFiles(const char* path = "/");

  // File operations
  bool openFile(const char* filename);
  void closeFile();
  int readData(uint8_t* buffer, size_t size);
  bool isFileOpen();
  size_t available();
}