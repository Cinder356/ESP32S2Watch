#ifndef _MENU_PAGE_H
#define _MENU_PAGE_H
#include "UI/Wrappers/AbstractPage.h"
#include "UI/Wrappers/Window.h"
// #include "AllPages.h"
#include "IRSendPage.h"

namespace Apps::IRHub::Pages
{
    class MainMenuPage : public AbstractPage
    {
    private:
        Window *_window;
    public:
        MainMenuPage(Window *window);
        void open() override;
        void update() override;
    };
}

#endif