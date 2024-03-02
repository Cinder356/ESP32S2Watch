#include "Apps/NotepadApp.h"

namespace Apps
{
    void NotepadApp::start()
    {
        _file_explorer_ptr = new UISolutions::FileExplorer();
        _file_explorer_ptr->start(TEXT_FILES_FOLDER);
        _app_status = AppStatus::EXPLORING;
    }

    void NotepadApp::close()
    {
        Serial.print("Free heap before: ");
        Serial.println(ESP.getFreeHeap());
        delete _file_explorer_ptr;
        Serial.print("Free heap after: ");
        Serial.println(ESP.getFreeHeap());
    }

    void NotepadApp::update(ButtonEvents button_events)
    {
        if (_app_status == AppStatus::EXPLORING)
        {
            String res = _file_explorer_ptr->loop(button_events);
            if (res != "")
                Serial.println(res);
        }
    }

    uint16_t *Apps::NotepadApp::get_icon() const { return Managers::SDManager::read_bin_image(NOTEPAD_ICON_PATH); }
}