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
        public:
            ~Label();
            Label(uint8_t x, uint8_t y, char* text_ptr);
            void draw() override;
    };
}

#endif