#include "Apps/NotepadApp.h"

namespace Apps
{
    void NotepadApp::start()
    {
        _file_explorer_ptr = new UI::UISolutions::FileExplorer();
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

    void NotepadApp::update()
    {
        switch (_app_status)
        {
        case AppStatus::EXPLORING:
        {
            String res = _file_explorer_ptr->loop();
            if (res != "")
                open_txt(res);
            break;
        }

        case AppStatus::TEXT_VIEW:
        {
            if (btn_st_right == ButtonEvent::CLICK && _current_page < _file_pages_quantity)
            {
                _current_page++;
                draw_page();
            }
            if (btn_st_left == ButtonEvent::CLICK && _current_page > 0)
            {
                _current_page--;
                draw_page();
            }
            break;
        }
        }
    }

    uint16_t *NotepadApp::get_icon() const { return Managers::SDManager::read_bin_image(NOTEPAD_ICON_PATH); }

    void NotepadApp::open_txt(String path)
    {
        _file_path = path;
        _app_status = AppStatus::TEXT_VIEW;
        _current_page = 0;
        _file_pages_quantity = Managers::SDManager::get_file_size(_file_path.c_str()) / NOTEPAD_MAX_CHAR_QUANTITY;
        draw_page();
    }

    void NotepadApp::draw_page()
    {
        // Serial.println("page: " + String(_current_page));
        // uint8_t r = 0;
        // Serial.println("start: " + String((size_t)(r * GET_MAX_TEXT_COLUMNS(NOTEPAD_TEXT_SIZE) + NOTEPAD_MAX_CHAR_QUANTITY * _current_page)));
        // Serial.println("end: " + String((size_t)((r + 1) * GET_MAX_TEXT_COLUMNS(NOTEPAD_TEXT_SIZE) + NOTEPAD_MAX_CHAR_QUANTITY * _current_page)));
        // Serial.println("start: " +String(_current_page * NOTEPAD_MAX_CHAR_QUANTITY));
        // Serial.println("end: " + String((_current_page + 1) * NOTEPAD_MAX_CHAR_QUANTITY));
        screen.fillScreen(NOTEPAD_BACKGROUND_COLOR);
        screen.setTextColor(NOTEPAD_TEXT_COLOR);
        screen.setCursor(0, 0);
        char* text = Managers::SDManager::read_file(_file_path.c_str(), _current_page * NOTEPAD_MAX_CHAR_QUANTITY, (_current_page + 1) * NOTEPAD_MAX_CHAR_QUANTITY);
        screen.print(text);
        delete[] text;
        // for (uint8_t row; row < NOTEPAD_FILE_TEXT_LINES_QUANTITY; row++)
        // {
        //     char *line = Managers::SDManager::read_file(_file_path,
        //                                                 row * GET_MAX_TEXT_COLUMNS(NOTEPAD_TEXT_SIZE) + NOTEPAD_MAX_CHAR_QUANTITY * _current_page,
        //                                                 (row + 1) * GET_MAX_TEXT_COLUMNS(NOTEPAD_TEXT_SIZE) + NOTEPAD_MAX_CHAR_QUANTITY * _current_page);
        //     screen.print(line);
        //     delete[] line;
        // }
    }
}