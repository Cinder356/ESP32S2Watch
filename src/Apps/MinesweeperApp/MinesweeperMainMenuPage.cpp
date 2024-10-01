#include "Apps/MinesweeperApp/MinesweeperAllPages.h"

namespace Apps::Minesweeper::Pages
{
    MinesweeperMainMenuPage::MinesweeperMainMenuPage(Window *window_ptr) : _window_ptr(window_ptr) {}

    void MinesweeperMainMenuPage::open()
    {
        const static uint16_t BTN_COLOR = ST7735_ORANGE;
        _window_ptr->add_widget(new UIButton(10, 16, "Start game 6x9x15", std::bind(&MinesweeperMainMenuPage::btn_open_game_page, this, 6, 9, 15), BTN_COLOR));
        _window_ptr->add_widget(new UIButton(10, 30, "Start game 7x7x13", std::bind(&MinesweeperMainMenuPage::btn_open_game_page, this, 7, 7, 13), BTN_COLOR));
        _window_ptr->add_widget(new UIButton(10, 44, "Start game 9x9x21", std::bind(&MinesweeperMainMenuPage::btn_open_game_page, this, 9, 9, 21), BTN_COLOR));
        _window_ptr->add_widget(new UIButton(10, 58, "Start game 12x12x38", std::bind(&MinesweeperMainMenuPage::btn_open_game_page, this, 12, 12, 38), BTN_COLOR));
        _window_ptr->add_widget(new UIButton(10, 72, "Start game 13x13x45", std::bind(&MinesweeperMainMenuPage::btn_open_game_page, this, 13, 13, 45), BTN_COLOR));
    }

    void MinesweeperMainMenuPage::update()
    {
    }

    void MinesweeperMainMenuPage::btn_open_game_page(uint8_t field_width, uint8_t field_height, uint8_t bomb_quantity)
    {
        _window_ptr->open_page(new MinesweeperGamePage(_window_ptr, field_width, field_height, bomb_quantity));
    }
}