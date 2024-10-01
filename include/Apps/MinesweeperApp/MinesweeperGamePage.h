#ifndef _MINESWEEPER_GAME_PAGE_H
#define _MINESWEEPER_GAME_PAGE_H

#include <optional>

#include "UI/Wrappers/AbstractPage.h"
#include "UI/Wrappers/Window.h"
#include "Assets/MinesweeperGameField.h"

namespace Apps::Minesweeper::Pages
{
    class MinesweeperGamePage : public AbstractPage
    {
    private:
        const static uint8_t _END_GAME_WINDOW_W = 60;
        const static uint8_t _END_GAME_WINDOW_H = 20;
        const static uint8_t _END_GAME_WINDOW_X = (SCREEN_WIDTH - _END_GAME_WINDOW_W) / 2;
        const static uint8_t _END_GAME_WINDOW_Y = (SCREEN_HEIGHT - _END_GAME_WINDOW_H) / 2;
        const static uint16_t _END_GAME_WINDOW_BACKGROUND_COLOR = 0xffff;
        const static uint16_t _END_GAME_WINDOW_TEXT_COLOR = 0x0000;
        const static uint16_t _END_GAME_DELAY = 1500;
        const static uint8_t _TEXT_SIZE = SMALL_TEXT_SIZE;

        Window *_window_ptr;
        Assets::MinesweeperGameField *_game_field;

        void show_end_game_window(const char *text);
        void lose_game();
        void win_game();

    public:
        const static uint16_t BACKGROUND_COLOR = 0xCE79;

        ~MinesweeperGamePage();
        MinesweeperGamePage(Window *window_ptr, uint8_t field_width, uint8_t field_height, uint8_t bomb_quantity);
        void open() override;
        void update() override;
        void draw_page();
    };
}

#endif