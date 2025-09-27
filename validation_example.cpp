// EXAMPLE: Validation function cho WebUI
bool validateConfig(const Config& cfg, String& error) {
    if (cfg.outputs < 1 || cfg.outputs > 4) {
        error = "Outputs must be 1-4";
        return false;
    }
    if (cfg.ledsPerOutput < 1 || cfg.ledsPerOutput > 680) {
        error = "LEDs per output must be 1-680"; 
        return false;
    }
    if (cfg.startUniverse < 0 || cfg.startUniverse > 32767) {
        error = "Start universe must be 0-32767";
        return false;
    }
    if (cfg.dmxPacketRate < 1 || cfg.dmxPacketRate > 60) {
        error = "DMX rate must be 1-60 fps";
        return false;
    }
    return true;
}