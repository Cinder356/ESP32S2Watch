#ifndef _MINESWEEPER_FIELD_CELL_H
#define _MINESWEEPER_FIELD_CELL_H

#include "Static/Screen.h"
#include "Static/Bitmaps.h"

namespace Apps::Minesweeper::Assets
{
    class MinesweeperFieldCell
    {
    private:
        uint8_t _x;
        uint8_t _y;

    public:
        static const uint8_t CELL_WIDTH = 10;
        static const uint8_t CELL_HEIGHT = 10;
        static const uint16_t CELL_COLOR = 0xB576;
        static const uint16_t CELL_EDGE_COLOR= 0x4228;
        static const uint16_t FLAG_COLOR = 0xA1CB;
        static const uint16_t BOMB_COLOR = 0x0000;
        static const uint16_t OPENED_CELL_BACKGROUND_COLOR = 0xE6FA;
        static const uint16_t OPENED_CELL_TEXT_COLOR = 0xF94F;
        static const uint16_t SELECTED_CELL_EDGE_COLOR = 0x11CC;

        bool is_bomb = 0;
        bool is_flagged = 0;
        bool is_opened = 0;
        uint8_t bombs_around = 0;

        MinesweeperFieldCell();
        MinesweeperFieldCell(uint8_t x, uint8_t y);
        void draw();
        void deselect();
        void select();

    };
}

#endif