#include "Apps/IRHubApp.h"

namespace Apps
{
    void IRHubApp::start() {}
    void IRHubApp::close() {}
    void IRHubApp::update(ButtonEvents button_events) {}
    uint16_t *IRHubApp::get_icon() const { return Managers::SDManager::read_bin_image(IR_HUB_ICON_PATH); }
}