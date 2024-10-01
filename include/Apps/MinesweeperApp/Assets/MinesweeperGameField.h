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
        int16_t _win_points = 0;

        
        uint8_t get_current_cell_i();
    public:
        uint8_t field_width;
        uint8_t field_height;
        uint8_t cur_x = 0;
        uint8_t cur_y = 0;

        ~MinesweeperGameField();
        MinesweeperGameField(uint8_t field_width, uint8_t field_height, uint8_t bomb_quantity);
        void draw();
        void select_current_cell();
        void deselect_current_cell();
        // @brief returns true if all bombs were flagged.
        bool flag_current_cell();
        // @brief returns true if cell is bomb.
        bool open_current_cell();
        void open_nearby_empty_cells(uint8_t cur_x, uint8_t cur_y);
        void generate_field();
    };
}

#endif