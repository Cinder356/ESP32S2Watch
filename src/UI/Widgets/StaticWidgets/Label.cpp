#include "UI/Widgets/StaticWidgets/Label.h"

namespace UI::Widgets::Static
{
    Label::~Label() { delete[] _text_ptr; }

    Label::Label(uint8_t x, uint8_t y, const char *text_ptr, uint16_t text_color) : _x(x), _y(y), _text_color(text_color)
    {
        _text_ptr = new char[strlen(text_ptr) + 1];
        strcpy(_text_ptr, text_ptr);
    }

    void Label::draw()
    {
        screen.setCursor(_x, _y);
        screen.setTextColor(_text_color);
        screen.print(_text_ptr);
    }

    void Label::change_text(const char *new_text)
    {
        delete[] _text_ptr;
        uint8_t len = strlen(new_text);
        _text_ptr = new char[len + 1];
        strcpy(_text_ptr, new_text);
    }
}