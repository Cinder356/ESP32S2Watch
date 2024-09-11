#include "UI/UISolutions/SelectionList.h"

namespace UI::UISolutions
{
    SelectionList::~SelectionList()
    {
        for (uint8_t i; i < _arr_size; i++)
            delete[] _lines_array_ptr[i];
        delete[] _lines_array_ptr;
    }

    void SelectionList::start(const char **lines_array, uint8_t arr_size, uint16_t background_color, uint16_t text_color)
    {
        _lines_array_ptr = new char *[arr_size];
        for (uint8_t i = 0; i < arr_size; i++)
        {
            uint8_t line_length = strlen(lines_array[i]);
            if (line_length > SL_MAX_TEXT_COLUMNS)
                line_length = SL_MAX_TEXT_COLUMNS;
            _lines_array_ptr[i] = new char[line_length + 1];
            strncpy(_lines_array_ptr[i], lines_array[i], line_length);
            _lines_array_ptr[i][line_length] = '\0';
        }
        _arr_size = arr_size;
        _background_color = background_color;
        _text_color = text_color;
        draw_page();
        draw_cursor(SL_CURSOR_COLOR);
    }

    int16_t SelectionList::loop()
    {
        if (btn_st_center == ButtonEvent::CLICK)
            return _cursor;
        if (btn_st_up == ButtonEvent::CLICK && _cursor > 0)
        {
            if (_cursor % SL_MAX_TEXT_LINES == 0 && _cursor != 1)
            {
                _cursor--;
                draw_page();
            }
            else
            {
                draw_cursor(_background_color);
                _cursor--;
            }
            draw_cursor(SL_CURSOR_COLOR);
        }
        if (btn_st_down == ButtonEvent::CLICK && _cursor + 1 < _arr_size)
        {
            if ((_cursor + 1) % SL_MAX_TEXT_LINES == 0)
            {
                _cursor++;
                draw_page();
            }
            else
            {
                draw_cursor(_background_color);
                _cursor++;
            }
            draw_cursor(SL_CURSOR_COLOR);
        }
        return -1;
    }

    void SelectionList::draw_cursor(uint16_t color)
    {
        uint8_t line_length = strlen(_lines_array_ptr[_cursor]);
        uint8_t x = (SCREEN_WIDTH - GET_TEXT_WIDTH(SL_TEXT_SIZE) * line_length) / 2 - 3;
        uint8_t y;
        if (_arr_size < GET_TEXT_HEIGHT(SL_TEXT_SIZE))
            y = _cursor * SL_TEXT_HEIGHT + (SCREEN_HEIGHT - SL_TEXT_HEIGHT * (_arr_size + 1)) / 2 + SL_LINE_SPACING - 2;
        else
            y = _cursor % SL_MAX_TEXT_LINES * SL_TEXT_HEIGHT + SL_LINE_SPACING - 2;
        // screen.fillTriangle(x, y, x, y + GET_TEXT_HEIGHT(SL_TEXT_SIZE) - 1, x + 3, y + GET_TEXT_HEIGHT(SL_TEXT_SIZE) / 2, color);
        screen.drawFastVLine(x, y, GET_TEXT_HEIGHT(SL_TEXT_SIZE) + 3, color);
    }

    void SelectionList::draw_page()
    {
        screen.fillScreen(_background_color);
        screen.setTextColor(_text_color);
        screen.setTextSize(SL_TEXT_SIZE);
        if (_arr_size < SL_MAX_TEXT_LINES)
            screen.setCursor(0, (SCREEN_HEIGHT - SL_TEXT_HEIGHT * (_arr_size + 1)) / 2);
        else
            screen.setCursor(0, 0);
        uint8_t current_page = _cursor / SL_MAX_TEXT_LINES;
        for (uint8_t i = current_page * SL_MAX_TEXT_LINES; i < _arr_size && i < (current_page + 1) * SL_MAX_TEXT_LINES; i++)
        {
            char *line = _lines_array_ptr[i];
            uint8_t line_length = strlen(line);
            screen.setCursor((SCREEN_WIDTH - GET_TEXT_WIDTH(SL_TEXT_SIZE) * line_length) / 2, screen.getCursorY() + SL_LINE_SPACING);
            screen.println(line);
        }
    }
}