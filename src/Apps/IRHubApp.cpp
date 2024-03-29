#include "Apps/IRHubApp.h"

namespace Apps
{
    void IRHubApp::start()
    {

        auto f = [this](){Serial.println("hi");};

        _page = new UI::Wrappers::Page();
        _page->add_widget(new Label(20, 10, "lambda size"));
        _page->add_widget(new UIButton(20, 20, "first button", f));
        _page->add_widget(new UIButton(20, 30, "second", f));
        _page->add_widget(new UIButton(20, 40, "THIRT", f));
        _page->add_widget(new UIButton(20, 50, "Fourth btn", f));
        _page->draw();
    }
    void IRHubApp::close() { delete _page; }
    void IRHubApp::update(ButtonEvents button_events)
    {
        _page->update(button_events);
    }
    uint16_t *IRHubApp::get_icon() const { return Managers::SDManager::read_bin_image(IR_HUB_ICON_PATH); }
}