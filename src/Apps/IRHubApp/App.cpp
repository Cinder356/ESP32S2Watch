#include "Apps/IRHubApp/App.h"

namespace Apps::IRHub
{
    void IRHubApp::start()
    {
        _window = new Window();
        Pages::MainMenuPage *m_p = new Pages::MainMenuPage(_window);
        _window->open_page(m_p);
        _window->draw();
    }
    void IRHubApp::close() { delete _window; }
    void IRHubApp::update()
    {
        _window->update();
    }
    uint16_t *IRHubApp::get_icon() const { return Managers::SDManager::read_bin_image(IR_HUB_ICON_PATH); }

    // pages

    // FirstPage::FirstPage()  {}

    // void FirstPage::redirect()
    // {
    //     SecondPage *sc_p = new SecondPage(_window);
    //     _window->open_page(sc_p);
    // }

    // void FirstPage::open()
    // {
    //     Serial.println(3);
    //     _window->add_widget(new Label(40, 5, "Ir hub app: first page"));
    //     std::function<void()> f = [this]()
    //     {
    //         _window->add_widget(new Label(40, 50, "clicked"));
    //     };
    //     Serial.println(4);
    //     _window->add_widget(new UIButton(10, 25, "Click me", f));
    //     Serial.println(5);
    //     _window->add_widget(new UIButton(10, 35, "Redirect", std::bind(&FirstPage::redirect, this)));
    //     Serial.println(6);
    // };
}