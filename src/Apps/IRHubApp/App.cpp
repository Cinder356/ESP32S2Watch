#include "Apps/IRHubApp/App.h"

namespace Apps::IRHub
{
    void IRHubApp::start()
    {
        _window = new Window();
        _window->open_page<Pages::MainMenuPage>();
    }
    void IRHubApp::close() { delete _window; }
    void IRHubApp::update()
    {
        _window->update();
    }
    uint16_t *IRHubApp::get_icon() const { return Managers::SDManager::read_bin_image(IR_HUB_ICON_PATH); }
}