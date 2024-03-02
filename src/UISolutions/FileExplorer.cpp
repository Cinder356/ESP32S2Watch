#include "UISolutions/FileExplorer.h"

namespace UISolutions
{
    void FileExplorer::start(String start_dir)
    {
        change_dir(start_dir.c_str());
    };

    String FileExplorer::loop(ButtonEvents button_events)
    {
        if (button_events.center == ButtonEvent::CLICK)
        {
            return Managers::SDManager::get_filename_by_index(_current_dir.c_str(), _cursor);
        }

        if (button_events.up == ButtonEvent::CLICK && _cursor > 0)
        {
            if (_cursor <= _current_page * GET_MAX_TEXT_LINES(FE_TEXT_SIZE))
            {
                _cursor--;
                draw_page();
            }
            else
            {
                draw_cursor(FE_BACKGROUND);
                _cursor--;
            }
            draw_cursor(FE_CURSOR_COLOR);
        }

        if (button_events.down == ButtonEvent::CLICK && _cursor + 1 < _current_dir_files_amount)
        {
            if (_cursor >= (_current_page + 1) * GET_MAX_TEXT_LINES(FE_TEXT_SIZE) - 1)
            {
                _cursor++;
                draw_page();
            }
            else
            {
                draw_cursor(FE_BACKGROUND);
                _cursor++;
            }
            draw_cursor(FE_CURSOR_COLOR);
        }
        return "";
    }

    void FileExplorer::change_dir(String path)
    {
        _current_dir = path;
        _current_dir_files_amount = Managers::SDManager::get_files_amount(_current_dir.c_str());
        draw_page();
        draw_cursor(FE_CURSOR_COLOR);
    }

    void FileExplorer::draw_cursor(uint16_t color)
    {
        uint16_t y_top = _cursor % GET_MAX_TEXT_LINES(FE_TEXT_SIZE) * (GET_TEXT_HEIGHT(FE_TEXT_SIZE) + 2);
        screen.drawLine(1, y_top - 1, 1, y_top + 1 + GET_TEXT_HEIGHT(FE_TEXT_SIZE), color);
    }

    void FileExplorer::draw_page()
    {
        _current_page = _cursor / GET_MAX_TEXT_LINES(FE_TEXT_SIZE);
        uint8_t start_find_files_index = _current_page * GET_MAX_TEXT_LINES(FE_TEXT_SIZE);
        std::vector<String> filenames_vector = Managers::SDManager::get_files_by_path(_current_dir.c_str(), 0, start_find_files_index, start_find_files_index + GET_MAX_TEXT_LINES(FE_TEXT_SIZE));
        // _current_dir_files_amount
        Serial.print("start: ");
        Serial.println(_cursor);
        Serial.print("end: ");
        Serial.println(_cursor + GET_MAX_TEXT_LINES(FE_TEXT_SIZE));

        screen.fillScreen(FE_BACKGROUND);
        screen.setCursor(0, 0);
        screen.setTextSize(FE_TEXT_SIZE);
        for (uint8_t i = 0; i < filenames_vector.size(); i++)
        {
            String filename = filenames_vector[i];
            if (filename.length() > 18)
                filename = filename.substring(0, 16) + "..";
            screen.print(" ");
            screen.print(i + 1 + GET_MAX_TEXT_LINES(FE_TEXT_SIZE) * _current_page);
            screen.print(". ");
            screen.println(filename);
        }
    }
}