#include "SDManager.h"
#include <SD.h>

// Static variables to manage the active file and SD card state.
static File activeFile;
static bool sdAvailable = false;

// Initializes the SD card.
void SDManager::begin() {
  if (!SD.begin()) {
    Serial.println("SD init failed!");
    sdAvailable = false;
    return;
  }
  Serial.println("SD initialized.");
  sdAvailable = true;
}

// Checks if the SD card was successfully initialized.
bool SDManager::isAvailable() {
  return sdAvailable;
}

// Lists all non-directory files in a given path.
std::vector<String> SDManager::listFiles(const char* path) {
  std::vector<String> files;
  if (!sdAvailable) return files;

  File dir = SD.open(path);
  if (!dir || !dir.isDirectory()) {
    return files;
  }
  File entry;
  while ((entry = dir.openNextFile())) {
    if (!entry.isDirectory()) {
      files.push_back(String(entry.name()));
    }
    entry.close();
  }
  dir.close();
  return files;
}

// Opens a file for reading.
bool SDManager::openFile(const char* filename) {
  if (!sdAvailable) return false;
  // Close any previously open file
  if (activeFile) {
    activeFile.close();
  }
  activeFile = SD.open(filename);
  return activeFile;
}

// Closes the currently active file.
void SDManager::closeFile() {
  if (activeFile) {
    activeFile.close();
  }
}

// Reads a chunk of data from the active file into a buffer.
int SDManager::readData(uint8_t* buffer, size_t size) {
  if (!activeFile) return -1;
  return activeFile.read(buffer, size);
}

// Checks if a file is currently open.
bool SDManager::isFileOpen() {
  return (bool)activeFile;
}

// Returns the number of bytes available to read from the current file position.
size_t SDManager::available() {
  if (!activeFile) return 0;
  return activeFile.available();
}