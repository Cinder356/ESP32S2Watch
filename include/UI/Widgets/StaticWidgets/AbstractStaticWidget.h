#ifndef _ABSTRACT_STATIC_WIDGET_H
#define _ABSTRACT_STATIC_WIDGET_H

#include "../AbstractWidget.h"

namespace UI::Widgets::Static
{
    class AbstractStaticWidget : public AbstractWidget
    {
        private:
            uint8_t x;
            uint8_t y;
        public:
            virtual void draw() override = 0;
    };
}

#endif