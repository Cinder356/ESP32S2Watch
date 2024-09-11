#include "Apps/MinesweeperApp/Assets/MinesweeperGameField.h"

namespace Apps::Minesweeper::Assets
{
    MinesweeperGameField::~MinesweeperGameField()
    {
        delete[] _cell_array_ptr;
    }

    MinesweeperGameField::MinesweeperGameField(uint8_t field_width, uint8_t field_height, uint8_t y, uint8_t bomb_quantity) : field_width(field_width), field_height(field_height), _bomb_quantity(bomb_quantity)
    {
        uint8_t x = (SCREEN_WIDTH - (MinesweeperFieldCell::CELL_WIDTH * field_width)) / 2;

        uint16_t arr_size = field_width * field_height;
        _cell_array_ptr = new MinesweeperFieldCell[arr_size];
        for (uint8_t i = 0; i < arr_size; i++)
        {
            uint8_t cell_x = x + MinesweeperFieldCell::CELL_WIDTH * (i % field_height);
            uint8_t cell_y = y + MinesweeperFieldCell::CELL_HEIGHT * (i / field_width);
            // Serial.printf("x: %d y: %d\n", cell_x, cell_y);
            _cell_array_ptr[i] = MinesweeperFieldCell(cell_x, cell_y);
        }
    }

    void MinesweeperGameField::draw()
    {
        uint16_t arr_size = field_width * field_height;
        for (uint8_t i = 0; i < arr_size; i++)
        {
            _cell_array_ptr[i].draw();
        }
        select_current_cell();
    }

    void MinesweeperGameField::select_current_cell()
    {
        uint8_t cell_i = cur_y * field_height + cur_x;
        _cell_array_ptr[cell_i].select();
    }

    void MinesweeperGameField::deselect_current_cell()
    {
        uint8_t cell_i = cur_y * field_height + cur_x;
        _cell_array_ptr[cell_i].deselect();
    }

    void MinesweeperGameField::flag_current_cell()
    {
        uint8_t cell_i = cur_y * field_height + cur_x;
        _cell_array_ptr[cell_i].is_flagged = !_cell_array_ptr[cell_i].is_flagged;
        _cell_array_ptr[cell_i].draw();
    }

    void MinesweeperGameField::open_current_cell()
    {
        uint8_t cell_i = cur_y * field_height + cur_x;
        _cell_array_ptr[cell_i].is_opened = !_cell_array_ptr[cell_i].is_opened;
        _cell_array_ptr[cell_i].draw();
    }

    void MinesweeperGameField::generate_field()
    {
        // bomb placement
        uint8_t cell_quantity = field_width * field_height;
        bool is_unique;

        for (uint8_t i = 0; i < _bomb_quantity; i++)
        {
            do
            {
                is_unique = false;
                uint8_t rand_cell_i = random(0, cell_quantity - 1);
                if (!_cell_array_ptr[rand_cell_i].is_bomb)
                {
                    is_unique = true;
                    _cell_array_ptr[rand_cell_i].is_bomb = true;
                    uint8_t row = rand_cell_i / field_width + 1;
                    uint8_t column = rand_cell_i % field_width + 1;
                }
            } while (!is_unique);
        }
    }
}