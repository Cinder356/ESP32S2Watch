#include "UI/Widgets/InteractiveWidgets/UIButton.h"

namespace UI::Widgets::Interactive
{
    UIButton::~UIButton() { delete[] _text_ptr; }

    UIButton::UIButton(uint8_t x, uint8_t y, const char *text, std::function<void()> func, uint16_t btn_color, uint16_t text_color)
        : _x(x), _y(y), _func(func), _btn_color(btn_color), _text_color(text_color)
    {
        uint8_t len = strlen(text);
        _text_ptr = new char[len + 1];
        strcpy(_text_ptr, text);
    }

    void UIButton::draw() // делема: считать w и h при отрисовке и выделении или один раз просчитать, но потратить 2 байта
    {
        uint8_t text_len = strlen(_text_ptr);
        uint8_t w = text_len * GET_TEXT_WIDTH(UIBUTTON_TEXT_SIZE) + UIBUTTON_TEXT_PADDING_X * 2 - TEXT_SPACING;
        uint8_t h = GET_TEXT_HEIGHT(UIBUTTON_TEXT_SIZE) - TEXT_SPACING + UIBUTTON_TEXT_PADDING_Y * 2;
        screen.fillRoundRect(_x, _y, w, h, UIBUTTON_ROUNDNESS, _btn_color);
        screen.setTextColor(_text_color);
        screen.setCursor(_x + UIBUTTON_TEXT_PADDING_X, _y + UIBUTTON_TEXT_PADDING_Y);
        screen.print(_text_ptr);
    }

    void UIButton::select()
    {
        uint8_t text_len = strlen(_text_ptr);
        uint8_t w = text_len * GET_TEXT_WIDTH(UIBUTTON_TEXT_SIZE) + UIBUTTON_TEXT_PADDING_X * 2 - TEXT_SPACING;
        uint8_t h = GET_TEXT_HEIGHT(UIBUTTON_TEXT_SIZE) - TEXT_SPACING + UIBUTTON_TEXT_PADDING_Y * 2;
        screen.drawRoundRect(_x, _y, w, h, UIBUTTON_ROUNDNESS, ~_btn_color);
    }

    void UIButton::deselect() { draw(); }

    void UIButton::invoke() { _func(); }

    void UIButton::change_text(const char *new_text)
    {
        delete[] _text_ptr;
        uint8_t len = strlen(new_text);
        _text_ptr = new char[len + 1];
        strcpy(_text_ptr, new_text);
    }
}
