#ifndef _MINESWEEPER_GAME_FIELD_H
#define _MINESWEEPER_GAME_FIELD_H

#include "Static/Screen.h"
#include "MinesweeperFieldCell.h"

namespace Apps::Minesweeper::Assets
{
    class MinesweeperGameField
    {
    private:
        MinesweeperFieldCell *_cell_array_ptr;

        uint8_t _bomb_quantity;

    public:
        uint8_t field_width;
        uint8_t field_height;
        uint8_t cur_x = 0;
        uint8_t cur_y = 0;

        ~MinesweeperGameField();
        MinesweeperGameField(uint8_t field_width, uint8_t field_height, uint8_t y, uint8_t bomb_quantity);
        void draw();
        void select_current_cell();
        void deselect_current_cell();
        void flag_current_cell();
        void open_current_cell();
        void generate_field();

    };
}

#endif