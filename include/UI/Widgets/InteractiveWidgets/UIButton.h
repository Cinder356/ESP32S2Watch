#ifndef _UI_BUTTON_H
#define _UI_BUTTON_H

#include "AbstractInteractiveWidget.h"

#define UIBUTTON_TEXT_SIZE 1
#define UIBUTTON_TEXT_PADDING_X 3
#define UIBUTTON_TEXT_PADDING_Y 2
#define UIBUTTON_ROUNDNESS 3

namespace UI::Widgets::Interactive
{
    class UIButton : public AbstractInteractiveWidget
    {
    private:
        uint8_t _x;
        uint8_t _y;
        char *_text_ptr;
        std::function<void()> _func;
        uint16_t _btn_color;
        uint16_t _text_color;

    public:
        ~UIButton() override;
        UIButton(uint8_t x, uint8_t y, const char *text, std::function<void()> func, uint16_t btn_color = 0xf00f, uint16_t text_color = 0xffff);
        void draw() override;
        void select() override;
        void deselect() override;
        void invoke() override;
        void change_text(const char* new_text);
    };
}
#endif