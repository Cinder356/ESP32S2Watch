#include "Apps/IRHubApp.h"

namespace Apps
{
    void IRHubApp::start()
    {
        _selection_list = new UISolutions::SelectionList();
        const char *lines_array[] = {
            "Get",
            "Send",
            "Remove",
            "Hi",
            "Dris",
        };
        _selection_list->start(lines_array, sizeof(lines_array) / sizeof(const char *));
    }
    void IRHubApp::close() { delete _selection_list; }
    void IRHubApp::update(ButtonEvents button_events)
    {
        int16_t res = _selection_list->loop(button_events);
        if (res >= 0)
        {
            Serial.println(res);
        }
    }
    uint16_t *IRHubApp::get_icon() const { return Managers::SDManager::read_bin_image(IR_HUB_ICON_PATH); }
}