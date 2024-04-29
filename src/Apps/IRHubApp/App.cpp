#include "Apps/IRHubApp/App.h"

namespace Apps::IRHub
{
    void IRHubApp::start()
    {
        _window_ptr = new Window();
        _window_ptr->open_page<Pages::MainMenuPage>();
    }
    void IRHubApp::close() { delete _window_ptr; }
    void IRHubApp::update()
    {
        _window_ptr->update();
    }
    uint16_t *IRHubApp::get_icon() const { return Managers::SDManager::read_bin_image(IR_HUB_ICON_PATH); }
}