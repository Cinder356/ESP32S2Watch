#include "Apps/MinesweeperApp/MinesweeperAllPages.h"

namespace Apps::Minesweeper::Pages
{
    MinesweeperGamePage::~MinesweeperGamePage()
    {
        delete _game_field;
        _window_ptr->is_active = true;
    }
    MinesweeperGamePage::MinesweeperGamePage(Window *window_ptr, uint8_t field_width, uint8_t field_height, uint8_t bomb_quantity) : _window_ptr(window_ptr)
    {
        _game_field = new Assets::MinesweeperGameField(field_width, field_height, bomb_quantity);
    }

    void MinesweeperGamePage::open()
    {
        _window_ptr->is_active = false;
        _game_field->generate_field();
        draw_page();
    }

    void MinesweeperGamePage::show_end_game_window(const char *text)
    {
        uint8_t text_len = strlen(text);

        screen.fillRect(_END_GAME_WINDOW_X, _END_GAME_WINDOW_Y, _END_GAME_WINDOW_W, _END_GAME_WINDOW_H, _END_GAME_WINDOW_BACKGROUND_COLOR);
        screen.setTextColor(_END_GAME_WINDOW_TEXT_COLOR);
        screen.setCursor(_END_GAME_WINDOW_X + (_END_GAME_WINDOW_W - GET_TEXT_WIDTH(_TEXT_SIZE) * text_len) / 2, _END_GAME_WINDOW_Y + (_END_GAME_WINDOW_H - GET_TEXT_HEIGHT(_TEXT_SIZE)) / 2);
        screen.print(text);
    }

    void MinesweeperGamePage::lose_game()
    {
        delay(1000);
        show_end_game_window("Lose");
        delay(1000);
        _window_ptr->is_active = true;
        _window_ptr->open_page(new MinesweeperMainMenuPage(_window_ptr));
    }

    void MinesweeperGamePage::win_game()
    {
        delay(1000);
        show_end_game_window("Win");
        delay(1000);
        _window_ptr->is_active = true;
        _window_ptr->open_page(new MinesweeperMainMenuPage(_window_ptr));
    }

    void MinesweeperGamePage::update()
    {
        if (btn_st_up == ButtonEvent::CLICK && _game_field->cur_y > 0)
        {
            _game_field->deselect_current_cell();
            _game_field->cur_y--;
            _game_field->select_current_cell();
        }
        else if (btn_st_right == ButtonEvent::CLICK && _game_field->cur_x < _game_field->field_width - 1)
        {
            _game_field->deselect_current_cell();
            _game_field->cur_x++;
            _game_field->select_current_cell();
        }
        else if (btn_st_down == ButtonEvent::CLICK && _game_field->cur_y < _game_field->field_height - 1)
        {
            _game_field->deselect_current_cell();
            _game_field->cur_y++;
            _game_field->select_current_cell();
        }
        else if (btn_st_left == ButtonEvent::CLICK && _game_field->cur_x > 0)
        {
            _game_field->deselect_current_cell();
            _game_field->cur_x--;
            _game_field->select_current_cell();
        }
        else if (btn_st_center == ButtonEvent::CLICK)
        {
            bool is_bomb = _game_field->open_current_cell();
            _game_field->select_current_cell();
            if (is_bomb)
                lose_game();
        }
        else if (btn_st_command == ButtonEvent::CLICK)
        {
            bool is_win = _game_field->flag_current_cell();
            if (is_win)
                win_game();
        }
    }

    void MinesweeperGamePage::draw_page()
    {
        screen.fillScreen(BACKGROUND_COLOR);
        _game_field->draw();
    }
}