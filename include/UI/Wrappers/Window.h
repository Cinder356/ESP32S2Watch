#ifndef _WINDOW_H
#define _WINDOW_H

#include <vector>
#include "Static/Screen.h"
#include "PhysButton.h"
#include "AbstractPage.h"

#pragma region WidgetsInclude
#include "UI/Widgets/StaticWidgets/AbstractStaticWidget.h"
#include "UI/Widgets/InteractiveWidgets/AbstractInteractiveWidget.h"
#include "UI/Widgets/StaticWidgets/Label.h"
#include "UI/Widgets/InteractiveWidgets/UIButton.h"
#pragma endregion

using namespace UI::Widgets::Static;
using namespace UI::Widgets::Interactive;
using namespace UI::Wrappers;

namespace UI::Wrappers
{
    class Window
    {
    private:
        std::vector<AbstractStaticWidget *> _static_widgets_vector;
        std::vector<AbstractInteractiveWidget *> _interactive_widgets_vector;

        AbstractPage *_current_page_ptr = nullptr;
        uint16_t _background_color;
        uint16_t _cursor = 0;

    public:
        bool is_active = 1;

        ~Window();
        Window(uint16_t background_color = 0x0000);
        void update();
        void draw();
        void add_widget(AbstractStaticWidget *widget);
        void add_widget(AbstractInteractiveWidget *widget);
        void open_page(AbstractPage *page_ptr);
        template <typename PageClass>
        void open_page() { open_page(new PageClass(this)); }
        void clear();
    };
}

#endif