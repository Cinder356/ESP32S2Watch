#ifndef _ABSTRACT_INTERACTIVE_WIDGET_H
#define _ABSTRACT_INTERACTIVE_WIDGET_H

#include "../AbstractWidget.h"

namespace UI::Widgets::Interactive
{
    class AbstractInteractiveWidget : public AbstractWidget
    {
        private:
        public:
            virtual void draw() override = 0;
    };
}

#endif