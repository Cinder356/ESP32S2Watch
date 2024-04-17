#ifndef _ABSTRACT_STATIC_WIDGET_H
#define _ABSTRACT_STATIC_WIDGET_H

#include "../AbstractWidget.h"

namespace UI::Widgets::Static
{
    class AbstractStaticWidget : public AbstractWidget
    {
    private:
    public:
        virtual ~AbstractStaticWidget() override = 0;
        virtual void draw() override = 0;
    };
}

#endif