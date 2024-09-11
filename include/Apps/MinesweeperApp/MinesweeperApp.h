#ifndef _MINESWEEPER_APP_H
#define _MINESWEEPER_APP_H

#include "Apps/AbstractApp.h"
#include "Managers/SDManager.h"
#include "Static/SDPaths.h"
#include "Static/Screen.h"
#include "UI/UISolutions/SelectionList.h"
#include "UI/Wrappers/Window.h"

#include "MinesweeperMainMenuPage.h"

namespace Apps::Minesweeper
{
    class MinesweeperApp : public Apps::AbstractApp
    {
    private:
        UI::Wrappers::Window *_window_ptr;

    public:
        void start() override;
        void close() override;
        void update() override;
        uint16_t *get_icon() const override;
    };
}

#endif