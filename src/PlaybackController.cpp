#include "PlaybackController.h"
#include "LEDController.h"
#include "SDManager.h"
#include "DMXSender.h"
#include "ConfigManager.h"

// Static member initialization
std::vector<String> PlaybackController::files;
int PlaybackController::currentIndex = -1;
PlaybackMode PlaybackController::playbackMode = PLAY_ONCE;
bool PlaybackController::playing = false;
unsigned long PlaybackController::lastFrameTime = 0;

void PlaybackController::begin() {
    files.clear();
    currentIndex = -1;
    playing = false;
}

void PlaybackController::loop() {
    if (!playing) return;
    handlePlayback();
}

void PlaybackController::setFiles(const std::vector<String>& fileList) {
    files = fileList;
    currentIndex = files.empty() ? -1 : 0;
}

void PlaybackController::setMode(PlaybackMode mode) {
    playbackMode = mode;
}

void PlaybackController::playFile(const String& filename) {
    for (size_t i = 0; i < files.size(); i++) {
        if (files[i] == filename) {
            currentIndex = i;
            loadFile(files[currentIndex]); // Use the String from the vector
            return;
        }
    }
}

void PlaybackController::stop() {
    if (playing) {
        Serial.println("⏹️ Playback stopped.");
        playing = false;
        SDManager::closeFile();
    }
}

void PlaybackController::next() {
    if (files.empty()) return;
    currentIndex = (currentIndex + 1) % files.size();
    loadFile(files[currentIndex]);
}

void PlaybackController::previous() {
    if (files.empty()) return;
    currentIndex = (currentIndex - 1 + files.size()) % files.size();
    loadFile(files[currentIndex]);
}

bool PlaybackController::isPlaying() {
    return playing;
}

String PlaybackController::currentFile() {
    if (currentIndex >= 0 && currentIndex < (int)files.size()) {
        return files[currentIndex];
    }
    return "";
}

void PlaybackController::loadFile(const String& filename) {
    if (SDManager::openFile(filename.c_str())) {
        Serial.printf("▶️ Loading file: %s\n", filename.c_str());
        lastFrameTime = millis();
        playing = true;
    } else {
        Serial.printf("❌ Failed to open file: %s\n", filename.c_str());
        playing = false;
    }
}

void PlaybackController::handlePlayback() {
    if (!SDManager::isFileOpen()) {
        stop();
        return;
    }

    Config cfg = ConfigManager::getConfig();
    
    // Use configured packet rate instead of fixed 30fps
    uint16_t targetRate = cfg.dmxPacketRate > 0 ? cfg.dmxPacketRate : 30;
    uint16_t frameInterval = 1000 / targetRate;
    
    unsigned long now = millis();
    if (now - lastFrameTime >= frameInterval) {
        lastFrameTime = now;

        bool fileEnded = false;

        // In one "frame", process N universes worth of data from the file
        for (int i = 0; i < cfg.numDmxUniverses; i++) {
            // Check if there's enough data for the packet header (universe + length)
            if (SDManager::available() < 4) {
                fileEnded = true;
                break;
            }

            uint16_t universe, length;
            SDManager::readData(reinterpret_cast<uint8_t*>(&universe), sizeof(universe));
            SDManager::readData(reinterpret_cast<uint8_t*>(&length), sizeof(length));

            // Check if the rest of the packet data is available
            if (SDManager::available() < length) {
                fileEnded = true;
                break; // Incomplete frame data
            }

            uint8_t frameData[512];
            if (length > sizeof(frameData)) {
                // Safety check, shouldn't happen with standard DMX
                fileEnded = true;
                break;
            }
            SDManager::readData(frameData, length);

            // 1. Send packet to the DMX target IP (with rate throttling)
            dmxSender.sendPacket(universe, frameData, length);

            // 2. Update local LEDs
            LEDController::updateFromArtnet(universe, length, frameData);
        }

        if (fileEnded) {
            if (playbackMode == PLAY_ONCE) {
                stop();
            } else if (playbackMode == LOOP_ONE) {
                loadFile(files[currentIndex]); // Re-load current file
            } else if (playbackMode == LOOP_ALL) {
                next(); // Load next file
            }
        }
    }
}
