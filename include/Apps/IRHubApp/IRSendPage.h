#ifndef _IR_SEND_PAGE_H
#define _IR_SEND_PAGE_H

#include "UI/Wrappers/AbstractPage.h"
#include "UI/Wrappers/Window.h"

namespace Apps::IRHub::Pages
{
    class IRSendPage : public AbstractPage
    {
    private:
        Window *_window;
    public:
        IRSendPage(Window *window);
        void open() override;
        void update() override;
    };
}

#endif