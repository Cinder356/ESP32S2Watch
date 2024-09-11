#include "Apps/MinesweeperApp/MinesweeperApp.h"

namespace Apps::Minesweeper
{
    void MinesweeperApp::start()
    {
        _window_ptr = new Window();
        _window_ptr->open_page<Pages::MinesweeperMainMenuPage>();
    }
    void MinesweeperApp::close() { delete _window_ptr; }
    void MinesweeperApp::update() { _window_ptr->update(); }
    uint16_t *MinesweeperApp::get_icon() const { return Managers::SDManager::read_bin_image(MINESWEEPER_ICON_PATH); } // return Managers::SDManager::read_bin_image();
}