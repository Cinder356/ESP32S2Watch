#ifndef _SELECTION_LIST_H
#define _SELECTION_LIST_H

#include "Static/Screen.h"
#include "PhysButton.h"

#define SL_BASE_BACKGROUND_COLOR 0x0000
#define SL_BASE_TEXT_COLOR 0xffff
#define SL_CURSOR_COLOR ST7735_RED // orange
#define SL_TEXT_SIZE SMALL_TEXT_SIZE
#define SL_LINE_SPACING 7
#define SL_TEXT_HEIGHT (GET_TEXT_HEIGHT(SL_TEXT_SIZE) + SL_LINE_SPACING)
#define SL_MAX_TEXT_LINES (SCREEN_HEIGHT / SL_TEXT_HEIGHT)
#define SL_MAX_TEXT_COLUMNS GET_MAX_TEXT_COLUMNS(SL_TEXT_SIZE) - 1

namespace UI::UISolutions
{
    class SelectionList
    {
    private:
        uint16_t _background_color;
        uint16_t _text_color;
        char** _lines_array_ptr;
        uint8_t _arr_size;
        uint8_t _cursor = 0;
    public:
        ~SelectionList();
        void start(const char** lines_array_ptr, uint8_t arr_size, uint16_t background_color=SL_BASE_BACKGROUND_COLOR, uint16_t text_color=SL_BASE_TEXT_COLOR);
        //@brief on select returns selected item
        int16_t loop();
        void draw_cursor(uint16_t color);
        void draw_page();
    };
}

#endif