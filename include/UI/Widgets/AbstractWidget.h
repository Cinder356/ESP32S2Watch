#ifndef _ASBTRACT_WIDGET_H
#define _ASBTRACT_WIDGET_H

#include "Static/Screen.h"

namespace UI::Widgets
{
    class AbstractWidget
    {
    private:
    public:
        virtual ~AbstractWidget() = 0;
        virtual void draw() = 0;
    };
}

#endif