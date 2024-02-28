#ifndef _SD_MANAGER_H
#define _SD_MANAGER_H

#include <Arduino.h>
#include <SD.h>
#include <vector>
#include "Static/Pins.h"

namespace Managers
{
    class SDManager
    {
        private:
            static void _on_cd();
            static void _off_cd();

        public:
            // SDManager();
            static bool setup();
            static std::vector<String> get_files_by_path(const char* path, bool all_path = 1);
            static char* read_file(const char* path, size_t start_byte = 0, size_t end_byte = 0);
            static uint16_t* read_bin_image(const char* path);
    };
};

#endif