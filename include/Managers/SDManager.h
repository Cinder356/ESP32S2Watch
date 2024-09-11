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
        SDManager() = delete;
        static void _on_sd();
        static void _off_sd();

    public:
        // SDManager();
        static bool setup();
        static size_t get_file_size(const char *file_path);
        // @brief return file by path and index
        static String get_filename_by_index(const char *dir_path, uint16_t start_index);
        // @brief returns files by path. @param start_index start file index @param end_index end file index @param all_path if enable returns all path of file
        static std::vector<String> get_files_by_path(const char *path, bool all_path = 1, uint16_t start_index = 0, uint16_t end_index = USHRT_MAX);
        // @brief returns files amount in directory by path
        static uint16_t get_files_amount(const char *path);
        // @brief creates file and writes data
        static void write_file(const char *path, uint8_t *text_buffer, size_t buffer_size);
        static char *read_file(const char *path, size_t start_byte = 0, size_t end_byte = 0);
        static uint16_t *read_bin_image(const char *path);
    };
};

#endif