#include "Managers/SDManager.h"

namespace Managers
{
    // SDManager::SDManager()
    // {

    // }

    void SDManager::_on_cd()
    {
        digitalWrite(TFT_CS, 1);
        digitalWrite(SD_CS, 0);
    }

    void SDManager::_off_cd()
    {
        digitalWrite(TFT_CS, 0);
        digitalWrite(SD_CS, 1);
    }

    bool SDManager::setup()
    {
        _on_cd(); // turn on cd card
        if (!SD.begin(SD_CS))
        {
            _off_cd();
            return 0;
        }
        uint8_t cardType = SD.cardType();
        if (cardType == CARD_NONE)
        {
            _off_cd();
            return 0;
        }

        _off_cd(); // turn off cd card
        return 1;
    }

    size_t SDManager::get_file_size(const char *file_path)
    {
        _on_cd();

        File file = SD.open(file_path);
        size_t file_size = file.size();
        _off_cd();
        return file_size;
    }

    String SDManager::get_filename_by_index(const char *dir_path, uint16_t start_index)
    {
        _on_cd();

        File dir = SD.open(dir_path);
        for (uint16_t i = 0; i < start_index; i++)
            dir.getNextFileName();
        String filename = dir.getNextFileName();

        dir.close();
        _off_cd();
        return filename;
    }

    std::vector<String> SDManager::get_files_by_path(const char *path, bool all_path, uint16_t start_index, uint16_t end_index)
    {
        _on_cd();

        File dir = SD.open(path);
        std::vector<String> filenames;
        String filename;
        for (uint16_t i = 0; i < start_index; i++)
            dir.getNextFileName();

        for (uint16_t i = 0; i <= end_index - start_index; i++)
        {
            filename = dir.getNextFileName();
            if (filename == "")
                break;
            if (!all_path)
                filename = filename.substring(filename.lastIndexOf('/') + 1);
            filenames.push_back(filename);
        }
        dir.close();
        _off_cd();
        return filenames;
    }

    uint16_t SDManager::get_files_amount(const char *path)
    {
        _on_cd();

        File dir = SD.open(path);

        uint16_t files_amount = 0;
        while (dir.getNextFileName() != "")
            files_amount++;

        dir.close();
        _off_cd();
        return files_amount;
    }

    void SDManager::write_file(const char *path, uint8_t *text_buffer, size_t buffer_size)
    {
        _on_cd();

        File file = SD.open(path, FILE_WRITE);
        for (size_t i = 0; i < buffer_size; i++)
            file.write(text_buffer[i]);

        file.close();
        _off_cd();
    }

    char *SDManager::read_file(const char *path, size_t start_byte, size_t end_byte)
    {
        _on_cd();

        File file = SD.open(path, FILE_READ);

        Serial.println("read_file statistic: ");
        Serial.println("    path: " + String(path));
        Serial.println("    start_byte: " + String(start_byte));
        Serial.println("    end_byte: " + String(end_byte));
        Serial.println("    file_status: " + String(1 ? file : 0));
        Serial.println("    file_size: " + String(file.size()));
        // Serial.println("    : " + String());
        // Serial.println("    : " + String());

        if (!file || file.isDirectory())
        {
            file.close();
            _off_cd();
            return nullptr;
        }

        size_t file_size = file.size();
        if (end_byte == 0 || end_byte > file_size)
            end_byte = file_size;

        if (end_byte <= start_byte)
        {
            file.close();
            _off_cd();
            return nullptr;
        }

        // Serial.println("start: " + String(start_byte));
        // Serial.println("end: " + String(end_byte));

        size_t buffer_size = end_byte - start_byte + 1;
        char *buffer = new char[buffer_size];
        file.seek(start_byte);
        file.readBytes(buffer, buffer_size - 1);
        buffer[buffer_size - 1] = '\0';

        file.close();
        _off_cd();
        return buffer;
    }

    uint16_t *SDManager::read_bin_image(const char *path)
    {
        _on_cd();
        File file = SD.open(path, FILE_READ);

        if (!file || file.isDirectory())
        {
            file.close();
            _off_cd();
            return nullptr;
        }

        size_t file_size = file.size();
        size_t array_size = file_size / sizeof(uint16_t);
        uint16_t *img_array = new uint16_t[array_size];

        file.read((uint8_t *)img_array, file_size);

        file.close();
        _off_cd();
        return img_array;
    }
}
