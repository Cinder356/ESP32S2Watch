#ifndef _MENU_PAGE_H
#define _MENU_PAGE_H
#include "UI/Wrappers/AbstractPage.h"
#include "UI/Wrappers/Window.h"

namespace Apps::IRHub::Pages
{
    class IRMainMenuPage : public AbstractPage
    {
    private:
        Window *_window_ptr;

    public:
        IRMainMenuPage(Window *window_ptr);
        void open() override;
        void update() override;
    };
}

#endif