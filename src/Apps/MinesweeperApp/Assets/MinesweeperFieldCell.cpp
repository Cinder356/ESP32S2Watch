#include "Apps/MinesweeperApp/Assets/MinesweeperFieldCell.h"

namespace Apps::Minesweeper::Assets
{
    MinesweeperFieldCell::MinesweeperFieldCell() {}
    MinesweeperFieldCell::MinesweeperFieldCell(uint8_t x, uint8_t y) : _x(x), _y(y) {}

    void MinesweeperFieldCell::draw()
    {
        screen.drawRect(_x, _y, CELL_WIDTH, CELL_HEIGHT, CELL_EDGE_COLOR);
        uint8_t x = _x + 1;
        uint8_t y = _y + 1;
        uint8_t x1 = CELL_WIDTH - 2;
        uint8_t y1 = CELL_HEIGHT - 2;
        if (is_opened)
        {
            screen.fillRect(x, y, x1, y1, OPENED_CELL_BACKGROUND_COLOR);
            if (is_bomb)
            {
                screen.drawBitmap(x, y, MINESWEEPER_BOMB, MINESWEEPER_BOMB_W, MINESWEEPER_BOMB_H, BOMB_COLOR);
                return;
            }
            if (bombs_around > 0)
            {
                screen.setCursor(x, y);
                screen.setTextColor(OPENED_CELL_TEXT_COLOR);
                screen.print(bombs_around);
            }
        }
        else if (is_flagged)
            screen.drawBitmap(x, y, MINESWEEPER_FLAG, MINESWEEPER_FLAG_W, MINESWEEPER_FLAG_H, FLAG_COLOR);
        else
            screen.fillRect(x, y, x1, y1, CELL_COLOR);
    }

    void MinesweeperFieldCell::deselect()
    {
        screen.drawRect(_x, _y, CELL_WIDTH, CELL_HEIGHT, CELL_EDGE_COLOR);
    }

    void MinesweeperFieldCell::select()
    {
        screen.drawRect(_x, _y, CELL_WIDTH, CELL_HEIGHT, SELECTED_CELL_EDGE_COLOR);
    }
}