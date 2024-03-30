#ifndef _PAGE_H
#define _PAGE_H

#include <vector>
#include "Static/Screen.h"
#include "PhysButton.h"

#pragma region WidgetsInclude
#include "UI/Widgets/StaticWidgets/AbstractStaticWidget.h"
#include "UI/Widgets/InteractiveWidgets/AbstractInteractiveWidget.h"
#include "UI/Widgets/StaticWidgets/Label.h"
#include "UI/Widgets/InteractiveWidgets/UIButton.h"
#pragma endregion

using namespace UI::Widgets::Static;
using namespace UI::Widgets::Interactive;

namespace UI::Wrappers
{

    class Page
    {
    private:
        std::vector<AbstractStaticWidget *> _static_widgets_vector;
        std::vector<AbstractInteractiveWidget *> _interactive_widgets_vector;

        uint16_t _background_color;
        uint16_t _cursor = 0;

    public:
        ~Page();
        Page(uint16_t background_color = 0x0000);
        void update();
        void draw();
        void add_widget(AbstractStaticWidget *widget);
        void add_widget(AbstractInteractiveWidget *widget);
        void clear();
    };
}

#endif