#include "utils/Storage.h"

const char Storage::prefs_namespace[] = "configs";

void Storage::setStatus(Storage::Status status) {
    config.status = static_cast<uint8_t>(status);
}

Storage::Status Storage::getStatus() {
    switch(config.status) {
        case 0:
            return Storage::CLOCKS;
        case 1:
            return Storage::LOGS;
        default:
            return Storage::UNDEFINED;
    }
}

