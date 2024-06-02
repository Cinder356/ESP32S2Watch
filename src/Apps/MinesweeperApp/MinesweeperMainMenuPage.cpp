#include "Apps/MinesweeperApp/MinesweeperAllPages.h"

namespace Apps::Minesweeper::Pages
{
    MinesweeperMainMenuPage::MinesweeperMainMenuPage(Window *window_ptr) : _window_ptr(window_ptr){}

    void MinesweeperMainMenuPage::open()
    {
        const uint16_t btn_color = ST7735_ORANGE;
        _window_ptr->add_widget(new UIButton(40, 30, "Start game", std::bind(&Window::open_page<MinesweeperMainMenuPage>, _window_ptr), btn_color));
    }

    void MinesweeperMainMenuPage::update()
    {
    }
}