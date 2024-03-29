#ifndef _ABSTRACT_INTERACTIVE_WIDGET_H
#define _ABSTRACT_INTERACTIVE_WIDGET_H

#include "../AbstractWidget.h"

typedef void (*Lambda)();

namespace UI::Widgets::Interactive
{
    class AbstractInteractiveWidget : public AbstractWidget
    {
        private:
        public:
            virtual void draw() override = 0;
            virtual void select() = 0;
            virtual void deselect() = 0;
            virtual void invoke() = 0;
    };
}

#endif