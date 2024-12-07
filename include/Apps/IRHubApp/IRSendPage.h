#ifndef _IR_SEND_PAGE_H
#define _IR_SEND_PAGE_H

#include "UI/Wrappers/AbstractPage.h"
#include "UI/Wrappers/Window.h"
#include "Managers/IRManager/IRSender.h"
#include "UI/UISolutions/FileExplorer.h"
#include "Static/Pins.h"
#include "Static/SDPaths.h"

namespace Apps::IRHub::Pages
{
    class IRSendPage : public AbstractPage
    {
    private:
        Window *_window;
        UI::UISolutions::FileExplorer _file_explorer;
        // bool _is_searching;
        // uint16_t *_ir_code_buff;
        // uint16_t _buff_len;

        // void btn_start_search();
        // void btn_send_ir();

    public:
        ~IRSendPage();
        IRSendPage(Window *window);
        void open() override;
        void update() override;
    };
}

#endif