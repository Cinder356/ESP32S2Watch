#include "Apps/MinesweeperApp/Assets/MinesweeperGameField.h"

namespace Apps::Minesweeper::Assets
{
    MinesweeperGameField::~MinesweeperGameField() { delete[] _cell_array_ptr; }

    MinesweeperGameField::MinesweeperGameField(uint8_t field_width, uint8_t field_height, uint8_t bomb_quantity) : field_width(field_width), field_height(field_height), _bomb_quantity(bomb_quantity)
    {
        uint8_t x = (SCREEN_WIDTH - (MinesweeperFieldCell::CELL_WIDTH * field_width)) / 2;
        uint8_t y = (SCREEN_HEIGHT - (MinesweeperFieldCell::CELL_HEIGHT * field_height)) / 2;

        uint16_t arr_size = field_width * field_height;
        _cell_array_ptr = new MinesweeperFieldCell[arr_size];
        for (uint16_t i = 0; i < arr_size; i++)
        {
            uint8_t cell_x = x + MinesweeperFieldCell::CELL_WIDTH * (i % field_width);
            uint8_t cell_y = y + MinesweeperFieldCell::CELL_HEIGHT * (i / field_width);
            _cell_array_ptr[i] = MinesweeperFieldCell(cell_x, cell_y);
        }
    }

    uint8_t MinesweeperGameField::get_current_cell_i() { return cur_y * field_width + cur_x; }

    void MinesweeperGameField::draw()
    {
        uint8_t arr_size = field_width * field_height;
        for (uint8_t i = 0; i < arr_size; i++)
        {
            _cell_array_ptr[i].draw();
        }
        select_current_cell();
    }

    void MinesweeperGameField::select_current_cell()
    {
        _cell_array_ptr[get_current_cell_i()].select();
    }

    void MinesweeperGameField::deselect_current_cell()
    {
        _cell_array_ptr[get_current_cell_i()].deselect();
    }

    bool MinesweeperGameField::flag_current_cell()
    {
        uint8_t cell_i = get_current_cell_i();
        if (_cell_array_ptr[cell_i].is_flag)
        {
            _cell_array_ptr[cell_i].is_flag = false;
            if (_cell_array_ptr[cell_i].is_bomb)
                _win_points--;
            else
                _win_points++;
        }
        else
        {
            _cell_array_ptr[cell_i].is_flag = true;
            if (_cell_array_ptr[cell_i].is_bomb)
                _win_points++;
            else
                _win_points--;
        }
        _cell_array_ptr[cell_i].draw();
        if (_win_points == _bomb_quantity)
            return true;
        return false;
    }

    bool MinesweeperGameField::open_current_cell()
    {
        uint8_t cell_i = get_current_cell_i();;
        _cell_array_ptr[cell_i].is_open = !_cell_array_ptr[cell_i].is_open;
        _cell_array_ptr[cell_i].draw();
        if (_cell_array_ptr[cell_i].is_open)
        {
            if (_cell_array_ptr[cell_i].is_bomb)
                return true;
            if (_cell_array_ptr[cell_i].bombs_around == 0)
                open_nearby_empty_cells(cur_x, cur_y);
        }
        return false;
    }

    void MinesweeperGameField::open_nearby_empty_cells(uint8_t cell_x, uint8_t cell_y) // here may be a big recursion !!
    {
        uint8_t origin_cell_i = cell_y * field_width + cell_x;
        int16_t cell_i;

        cell_i = origin_cell_i - field_width;
        if (cell_y > 0 && !_cell_array_ptr[cell_i].is_open) // top
        {
            _cell_array_ptr[cell_i].is_open = true;
            _cell_array_ptr[cell_i].draw();
            if (_cell_array_ptr[cell_i].bombs_around == 0)
                open_nearby_empty_cells(cell_x, cell_y - 1);
        }
        cell_i = origin_cell_i + 1;
        if (cell_x + 1 < field_width && !_cell_array_ptr[cell_i].is_open) // right
        {
            _cell_array_ptr[cell_i].is_open = true;
            _cell_array_ptr[cell_i].draw();
            if (_cell_array_ptr[cell_i].bombs_around == 0)
                open_nearby_empty_cells(cell_x + 1, cell_y);
        }
        cell_i = origin_cell_i + field_width;
        if (cell_y + 1 < field_height && !_cell_array_ptr[cell_i].is_open) // bottom
        {
            _cell_array_ptr[cell_i].is_open = true;
            _cell_array_ptr[cell_i].draw();
            if (_cell_array_ptr[cell_i].bombs_around == 0)
                open_nearby_empty_cells(cell_x, cell_y + 1);
        }
        cell_i = origin_cell_i - 1;
        if (cell_x > 0 && !_cell_array_ptr[cell_i].is_open) // left
        {
            _cell_array_ptr[cell_i].is_open = true;
            _cell_array_ptr[cell_i].draw();
            if (_cell_array_ptr[cell_i].bombs_around == 0)
                open_nearby_empty_cells(cell_x - 1, cell_y);
        }
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

                    uint8_t x = rand_cell_i % field_width;
                    uint8_t y = rand_cell_i / field_width;

                    bool top_is_field = y > 0;
                    bool right_is_field = x + 1 < field_width;
                    bool bottom_is_field = y + 1 < field_height;
                    bool left_is_field = x > 0;

                    // top left
                    if (top_is_field && left_is_field)
                        _cell_array_ptr[rand_cell_i - field_width - 1].bombs_around++;
                    // top
                    if (top_is_field)
                        _cell_array_ptr[rand_cell_i - field_width].bombs_around++;
                    // top right
                    if (top_is_field && right_is_field)
                        _cell_array_ptr[rand_cell_i - field_width + 1].bombs_around++;
                    // right
                    if (right_is_field)
                        _cell_array_ptr[rand_cell_i + 1].bombs_around++;
                    // bottom right
                    if (bottom_is_field && right_is_field)
                        _cell_array_ptr[rand_cell_i + field_width + 1].bombs_around++;
                    // bottom
                    if (bottom_is_field)
                        _cell_array_ptr[rand_cell_i + field_width].bombs_around++;
                    // bottom left
                    if (bottom_is_field && left_is_field)
                        _cell_array_ptr[rand_cell_i + field_width - 1].bombs_around++;
                    // left
                    if (left_is_field)
                        _cell_array_ptr[rand_cell_i - 1].bombs_around++;
                }
            } while (!is_unique);
        }
    }
}