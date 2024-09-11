#include "UI/UISolutions/FileExplorer.h"

namespace UI::UISolutions
{
    void FileExplorer::start(String start_dir)
    {
        change_dir(start_dir.c_str());
    };

    const char *FileExplorer::loop()
    {
        if (btn_st_center == ButtonEvent::CLICK)
        {
            String selected_path = Managers::SDManager::get_filename_by_index(_current_dir.c_str(), _cursor);
            if (selected_path.lastIndexOf('.') != -1)
            {
                btn_st_center = ButtonEvent::NONE;
                uint8_t len = selected_path.length();
                char *path_buff = new char[len + 1];
                strcpy(path_buff, selected_path.c_str());
                return path_buff;
            }
            change_dir(selected_path);
        }
        if (btn_st_left == ButtonEvent::CLICK)
        {
            uint8_t slash_index = _current_dir.lastIndexOf('/');
            if (slash_index == 0)
                slash_index = 1;
            change_dir(_current_dir.substring(0, slash_index));
        }

        if (btn_st_up == ButtonEvent::CLICK && _cursor > 0)
        {
            if (_cursor <= _current_page * FE_MAX_FILENAMES_QUANTITY)
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
        if (btn_st_down == ButtonEvent::CLICK && _cursor + 1 < _current_dir_files_amount)
        {
            if (_cursor >= (_current_page + 1) * FE_MAX_FILENAMES_QUANTITY - 1)
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

        return nullptr;
    }

    void FileExplorer::change_dir(String path)
    {
        _cursor = 0;
        _current_dir = path;
        _current_dir_files_amount = Managers::SDManager::get_files_amount(_current_dir.c_str());
        draw_page();
        draw_cursor(FE_CURSOR_COLOR);
    }

    void FileExplorer::draw_cursor(uint16_t color)
    {
        uint8_t y_top = _cursor % FE_MAX_FILENAMES_QUANTITY * GET_TEXT_HEIGHT(FE_TEXT_SIZE);
        screen.drawLine(1, y_top - 1, 1, y_top + 1 + GET_TEXT_HEIGHT(FE_TEXT_SIZE), color);
    }

    void FileExplorer::draw_page()
    {
        _current_page = _cursor / FE_MAX_FILENAMES_QUANTITY;
        uint8_t start_find_files_index = _current_page * FE_MAX_FILENAMES_QUANTITY;
        uint8_t end_fine_files_index = start_find_files_index + FE_MAX_FILENAMES_QUANTITY - 1;
        std::vector<String> filenames_vector = Managers::SDManager::get_files_by_path(_current_dir.c_str(), 0, start_find_files_index, end_fine_files_index);

        screen.fillScreen(FE_BACKGROUND);
        screen.setCursor(0, 0);
        screen.setTextSize(FE_TEXT_SIZE);
        screen.setTextColor(FE_TEXT_COLOR);
        // -filnames drawing-
        for (uint8_t i = 0; i < filenames_vector.size(); i++)
        {
            String filename = filenames_vector[i];
            if (filename.length() > 18)
                filename = filename.substring(0, 16) + "..";
            screen.setCursor(FE_LEFT_TEXT_MARGIN, screen.getCursorY());
            screen.print(i + 1 + FE_MAX_FILENAMES_QUANTITY * _current_page);
            screen.print(".");
            screen.setCursor(screen.getCursorX() + 3, screen.getCursorY());
            screen.println(filename);
        }
        // -permanent labels drawing-
        screen.fillRect(0, (SCREEN_HEIGHT - GET_TEXT_HEIGHT(FE_TEXT_SIZE)), SCREEN_WIDTH, SCREEN_HEIGHT - (SCREEN_HEIGHT - GET_TEXT_HEIGHT(FE_TEXT_SIZE)), FE_TEXT_COLOR);
        screen.setTextColor(FE_BACKGROUND);
        screen.setCursor(FE_LEFT_TEXT_MARGIN, (SCREEN_HEIGHT - GET_TEXT_HEIGHT(FE_TEXT_SIZE)));
        screen.print("<- cd ..");
        screen.setCursor(SCREEN_WIDTH - 35, screen.getCursorY());
        screen.print(String(_current_page) + '/' + String(_current_dir_files_amount / FE_MAX_FILENAMES_QUANTITY));
    }
}