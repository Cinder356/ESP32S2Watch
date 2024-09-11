#ifndef _MINESWEEPER_GAME_PAGE_H
#define _MINESWEEPER_GAME_PAGE_H

#include "UI/Wrappers/AbstractPage.h"
#include "UI/Wrappers/Window.h"
#include "Assets/MinesweeperGameField.h"

namespace Apps::Minesweeper::Pages
{
    class MinesweeperGamePage : public AbstractPage
    {
    private:
        Window *_window_ptr;
        Assets::MinesweeperGameField _game_field = Assets::MinesweeperGameField(7, 7, 34);

        bool _is_flag_mode = 0;

    public:
        const static uint16_t BACKGROUND_COLOR = 0xCE79;

        ~MinesweeperGamePage();
        MinesweeperGamePage(Window *window_ptr);
        void open() override;
        void update() override;
        void draw_page();
    };
}

#endif