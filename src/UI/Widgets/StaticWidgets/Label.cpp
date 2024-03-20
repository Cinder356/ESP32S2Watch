#include "UI/Widgets/StaticWidgets/Label.h"

namespace UI::Widgets::Static
{
    Label::~Label()
    {
        delete[] _text_ptr;
    }

    Label::Label(uint8_t x, uint8_t y, char *text_ptr) : _x(x), _y(y)
    {
        _text_ptr = new char[strlen(text_ptr) + 1];
        strcpy(_text_ptr, text_ptr);
    }

    void Label::draw()
    {
        screen.setCursor(_x, _y);
        screen.print(_text_ptr);
    }
}