#ifndef _PAGE_H
#define _PAGE_H

#include <vector>
#include "Static/Screen.h"
#include "Button.h"

#pragma region WidgetsInclude
#include "UI/Widgets/StaticWidgets/AbstractStaticWidget.h"
#include "UI/Widgets/InteractiveWidgets/AbstractInteractiveWidget.h"
#include "UI/Widgets/StaticWidgets/Label.h"
#pragma endregion



namespace UI::Wrappers
{
    using namespace UI::Widgets::Static;
    using namespace UI::Widgets::Interactive;

    class Page
    {
        private:
            std::vector<AbstractStaticWidget*> _static_widgets_vector;
            std::vector<AbstractInteractiveWidget*> _interactive_widgets_vector;

            uint16_t _cursor;

        public:
            ~Page();
            Page();
            void update(ButtonEvents button_events);
            void draw();
            void add_widget(AbstractStaticWidget *widget);
            void add_widget(AbstractInteractiveWidget *widget);
    };
}

#endif