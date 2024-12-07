#ifndef _IR_READ_PAGE_H
#define _IR_READ_PAGE_H

#include "UI/Wrappers/AbstractPage.h"
#include "UI/Wrappers/Window.h"
#include "Managers/SDManager.h"
#include "Managers/IRManager/IRReceiver.h"
#include "Managers/IRManager/IRSender.h"
#include "Static/Pins.h"
#include "Static/SDPaths.h"

#define _IRP_BACKGROUND_COLOR 0x0000
#define _IRP_WARNING_LABEL_COLOR ST7735_RED
#define _IRP_LISTEN_STATUS_COLOR ST7735_RED
#define _IRP_IR_CODE_DESCRIPTION_X 24
#define _IRP_IR_CODE_DESCRIPTION_Y 108

using namespace Managers::IRManager;

namespace Apps::IRHub::Pages
{
    class IRReadPage : public AbstractPage
    {
    private:
        Window *_window_ptr;
        UIButton *_change_status_btn_ptr;
        Label *_warning_label_ptr;
        Label *_ir_code_label_ptr;
        Label *_ir_type_label_ptr;

        bool _is_listening = 0;
        bool _signal_is_available = 0;
        bool _signal_was_saved = 0;
        irsignal_t _ir_data = irsignal_t();

        void btn_change_status();
        void btn_try_send();
        void btn_save_current_ir();
        void start_listen();
        void stop_listen();
        void draw_listen_indicator();
        void raise_error();

    public:
        ~IRReadPage();
        IRReadPage(Window *window_ptr);
        void open() override;
        void update() override;
    };
}

#endif