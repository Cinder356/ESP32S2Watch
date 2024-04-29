#ifndef _LABEL_H
#define _LABEL_H

#include "AbstractStaticWidget.h"

namespace UI::Widgets::Static
{
    class Label : public AbstractStaticWidget
    {
        private:
            char* _text_ptr;
            uint8_t _x;
            uint8_t _y;
            uint16_t _text_color;
        public:
            ~Label() override;
            Label(uint8_t x, uint8_t y, const char* text_ptr, uint16_t text_color=0xffff);
            void draw() override;
            void change_text(const char* new_text);
    };
}

#endif