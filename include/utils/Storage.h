#ifndef CLOCK2_0_STORAGE_H
#define CLOCK2_0_STORAGE_H

#include <Preferences.h>

struct Event {
    uint8_t day;
    uint8_t month;
    uint16_t year;
    char message[24];
    uint8_t  is_valid;
};

class Storage {
public:
    Storage() : loaded(false), prefs(), config_size(sizeof(config)) {}
    void begin()    { prefs.begin(prefs_namespace, false); Serial.print("[Storage] Config size: "); Serial.println(config_size); }
    void load()     { prefs.getBytes(prefs_namespace, &config, config_size); loaded = true; }
    void save()     { prefs.putBytes(prefs_namespace, &config, config_size); }
    bool isLoaded() { return loaded; }
    bool isValid()  { return config.backlights.pattern < 255 && config.backlights.intensity < 8; } // Simple test for valid data
    // An un-written to Flash will return all 0xFF.  So if we haven't been written to, we should start up with defaults.

    const static uint8_t str_buffer_size = 32;

    enum Status {
        LOGS = 0,
        CLOCKS = 1,
        UNDEFINED = 2,
    };

    void setStatus(Status status);
    Status getStatus();

    struct Config {

        uint8_t status;

        struct Backlights {
            uint8_t  pattern;
            uint16_t color_phase;
            uint8_t  intensity;
            uint8_t  pulse_bpm;
            uint8_t  breath_per_min;
            uint8_t  is_valid;       // Write StoredConfig::valid here when valid data is loaded.
        } backlights;

        struct Clock {
            bool     twelve_hour;
            time_t   time_zone_offset;
            uint8_t  is_valid;       // Write StoredConfig::valid here when valid data is loaded.
        } uclock;

        struct Wifi {
            char     ssid[str_buffer_size];
            char     password[str_buffer_size];
            uint8_t retries;
            uint8_t  is_valid;       // Write StoredConfig::valid here when valid data is loaded.
        } wifi;

        struct Alarms {
            Event events[5];         // We can store up to 5 events. (Memory issue)
            uint8_t  is_valid;       // Write StoredConfig::valid here when valid data is loaded.
        } alarms;

    } config;

    const static uint8_t valid = 0x55;  // neither 0x00 nor 0xFF, signaling loaded config isn't just default data.

private:
    bool loaded;
    Preferences prefs;
    const static char prefs_namespace[];
    uint16_t config_size;
};


#endif //CLOCK2_0_STORAGE_H
