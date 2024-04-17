#include "Apps/IRHubApp/AllPages.h"

namespace Apps::IRHub::Pages
{
    MainMenuPage::MainMenuPage(Window *window) : _window(window) {}

    void MainMenuPage::open()
    {
        _window->add_widget(new Label(20, 20, "heyyyy"));
        _window->add_widget(new UIButton(20, 30, "click me", std::bind(&Window::open_page<IRSendPage>, _window)));
    }

    void MainMenuPage::update()
    {
    }
}