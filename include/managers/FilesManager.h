//
// Created by axels on 17/02/2022.
//

#ifndef CLOCK2_0_FILESMANAGER_H
#define CLOCK2_0_FILESMANAGER_H
#include "Manager.h"
#include "bluetooth/UploadService.h"
#include <LITTLEFS.h>

class FilesManager: public Manager<nullptr_t>, public UploadService {
public:
    void begin(nullptr_t* config) override;
    void loop() override;
    void end() override {};
    void list_files();

private:
    void init_upload(const char* path) override;
    void handle_data(uint8_t *buf, size_t size) override;
    void close_upload() override;
    File fsUploadFile ;
};



#endif //CLOCK2_0_FILESMANAGER_H
