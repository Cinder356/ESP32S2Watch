#ifndef _MINESWEEPER_MAIN_MENU_PAGE_H
#define _MINESWEEPER_MAIN_MENU_PAGE_H

#include "UI/Wrappers/AbstractPage.h"
#include "UI/Wrappers/Window.h"

namespace Apps::Minesweeper::Pages
{
    class MinesweeperMainMenuPage : public AbstractPage
    {
    private:
        Window *_window_ptr;

    public:
        MinesweeperMainMenuPage(Window *window_ptr);
        void open() override;
        void update() override;
    };
}

#endif