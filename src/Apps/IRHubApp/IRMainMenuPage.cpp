#include "Apps/IRHubApp/IRHubAllPages.h"

namespace Apps::IRHub::Pages
{
    IRMainMenuPage::IRMainMenuPage(Window *window_ptr) : _window_ptr(window_ptr) {}

    void IRMainMenuPage::open()
    {
        const uint16_t btn_color = ST7735_ORANGE;
        _window_ptr->add_widget(new UIButton(40, 30, "Send", std::bind(&Window::open_page<IRSendPage>, _window_ptr), btn_color));
        _window_ptr->add_widget(new UIButton(40, 45, "Read", std::bind(&Window::open_page<IRReadPage>, _window_ptr), btn_color));
    }

    void IRMainMenuPage::update()
    {
    }
}