#include "Apps/IRHubApp/MainMenuPage.h"

namespace Apps::IRHub::Pages
{
    MainMenuPage::MainMenuPage(Window *window) {}

    void MainMenuPage::open()
    {
        _window->add_widget(new Label(20, 20, "hello from main menu page"));
        // _window->open_page<IRSendPage>();
        // std::function<void()> foo = std::bind(&Window::open_page<IRSendPage>, _window);
        // _window->add_widget(new UIButton(20, 30, "click me", foo));
    }

    void MainMenuPage::update()
    {
        uint8_t x = random(0, 128);
        uint8_t y = random(0, 128);
        uint16_t color = random(0x0000, 0xffff);
        screen.drawPixel(x, y, color);
    }
}