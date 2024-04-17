#include "Apps/IRHubApp/AllPages.h"

namespace Apps::IRHub::Pages
{
    IRSendPage::IRSendPage(Window *window) : _window(window) {}
    void IRSendPage::open()
    {
        _window->add_widget(new Label(1, 8, "oops"));
        _window->add_widget(new UIButton(10, 10, "Back", std::bind(&Window::open_page<MainMenuPage>, _window)));
    }
    void IRSendPage::update() {}
}