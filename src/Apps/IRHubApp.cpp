#include "Apps/IRHubApp.h"

namespace Apps
{
    void IRHubApp::start()
    {
        // const char *lines_array[] = {
        //     "Get",
        //     "Send",
        //     "Remove",
        //     "Hi",
        //     "Dris",
        // };
        // _selection_list = new UI::UISolutions::SelectionList();
        // _selection_list->start(lines_array, sizeof(lines_array) / sizeof(const char *));

        // _page = new UI::Wrappers::Page();
        // _page->add_widget(new UI::Widgets::Static::Label(30, 30, "hello world"));
        // _page->draw();
    }
    void IRHubApp::close() { delete _page; }
    void IRHubApp::update(ButtonEvents button_events)
    {
        // int16_t res = _selection_list->loop(button_events);
        // if (res >= 0)
        // {
        //     Serial.println(res);
        // }
    }
    uint16_t *IRHubApp::get_icon() const { return Managers::SDManager::read_bin_image(IR_HUB_ICON_PATH); }
}