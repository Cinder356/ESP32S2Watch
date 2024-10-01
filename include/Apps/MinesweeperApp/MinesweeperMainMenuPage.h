#ifndef _MINESWEEPER_MAIN_MENU_PAGE_H
#define _MINESWEEPER_MAIN_MENU_PAGE_H

#include "UI/Wrappers/AbstractPage.h"
#include "UI/Wrappers/Window.h"

namespace Apps::Minesweeper::Pages
{
    class MinesweeperMainMenuPage : public AbstractPage
    {
    private:
        Window *_window_ptr;

        void btn_open_game_page(uint8_t field_width, uint8_t field_height, uint8_t bomb_quantity);
    public:
        MinesweeperMainMenuPage(Window *window_ptr);
        void open() override;
        void update() override;
    };
}

#endif