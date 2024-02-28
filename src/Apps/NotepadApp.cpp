#include "Apps/NotepadApp.h"

namespace Apps
{
    NotepadApp::NotepadApp(Adafruit_ST7735 &screen_ref) : _screen_ref(screen_ref) {}

    void NotepadApp::start()
    {
        Serial.println("start");

        std::vector<String> filenames = Managers::SDManager::get_files_by_path(TEXT_FOLDER, 0);

        _screen_ref.fillScreen(NOTEPAD_BACKGROUND_COLOR);
        _screen_ref.setCursor(0, 0);
        _screen_ref.setTextColor(NOTEPAD_PATH_TEXT_COLOR);

        for (uint8_t filename_index = 0; filename_index < filenames.size(); filename_index++)
        {
            String filename = filenames[filename_index];
            if (filename.length() > 18)
                filename = filename.substring(0, 18);
            _screen_ref.print(filename_index + 1);
            _screen_ref.print(". ");
            _screen_ref.println(filename);
        }
    }

    void NotepadApp::close()
    {
    }

    void NotepadApp::update(ButtonEvents button_events)
    {
    }

    uint16_t *Apps::NotepadApp::get_icon() const { return Managers::SDManager::read_bin_image(NOTEPAD_ICON_PATH); }
}