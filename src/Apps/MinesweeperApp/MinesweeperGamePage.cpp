#include "Apps/MinesweeperApp/MinesweeperAllPages.h"

namespace Apps::Minesweeper::Pages
{
    MinesweeperGamePage::~MinesweeperGamePage() { _window_ptr->is_active = true; }
    MinesweeperGamePage::MinesweeperGamePage(Window *window_ptr) : _window_ptr(window_ptr) {}

    void MinesweeperGamePage::open()
    {
        const uint16_t btn_color = ST7735_ORANGE;
        _window_ptr->is_active = false;
        draw_page();
    }

    void MinesweeperGamePage::update()
    {
        if (btn_st_up == ButtonEvent::CLICK && _game_field.cur_y > 0)
        {
            _game_field.deselect_current_cell();
            _game_field.cur_y--;
            _game_field.select_current_cell();
        }
        else if (btn_st_right == ButtonEvent::CLICK && _game_field.cur_x < _game_field.field_width - 1)
        {
            _game_field.deselect_current_cell();
            _game_field.cur_x++;
            _game_field.select_current_cell();
        }
        else if (btn_st_down == ButtonEvent::CLICK && _game_field.cur_y < _game_field.field_height - 1)
        {
            _game_field.deselect_current_cell();
            _game_field.cur_y++;
            _game_field.select_current_cell();
        }
        else if (btn_st_left == ButtonEvent::CLICK && _game_field.cur_x > 0)
        {
            _game_field.deselect_current_cell();
            _game_field.cur_x--;
            _game_field.select_current_cell();
        }
        else if (btn_st_center == ButtonEvent::CLICK)
        {
            if (_is_flag_mode)
                _game_field.flag_current_cell();
            else
                _game_field.open_current_cell();
            _game_field.select_current_cell();
        }
        else if (btn_st_command == ButtonEvent::CLICK)
        {
            _is_flag_mode = !_is_flag_mode;
        }
    }

    void MinesweeperGamePage::draw_page()
    {
        screen.fillScreen(BACKGROUND_COLOR);
        _game_field.draw();
    }
}