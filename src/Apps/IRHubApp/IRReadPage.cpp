#include "Apps/IRHubApp/IRHubAllPages.h"

namespace Apps::IRHub::Pages
{
    IRReadPage::~IRReadPage()
    {
        // ir_receiver_ptr->disableIRIn();
        // IRReceiver::disable(); !!!!!!!!!
    }

    IRReadPage::IRReadPage(Window *window_ptr) : _window_ptr(window_ptr) {}

    void IRReadPage::open()
    {
        // if (ir_receiver_ptr == nullptr)
        //     ir_receiver_ptr = new IRrecv(IR_RECEIVER_PIN);
        // ir_receiver_ptr->enableIRIn();
        _warning_label_ptr = new Label(24, 8, "", _IRP_WARNING_LABEL_COLOR);
        _window_ptr->add_widget(_warning_label_ptr);
        _change_status_btn_ptr = new UIButton(40, 35, "Start listen", std::bind(&IRReadPage::btn_change_status, this));
        _window_ptr->add_widget(_change_status_btn_ptr);
        _window_ptr->add_widget(new UIButton(40, 50, "Try send", std::bind(&IRReadPage::btn_try_send, this)));
        _window_ptr->add_widget(new UIButton(40, 65, "Save", std::bind(&IRReadPage::btn_save_current_ir, this)));
        _window_ptr->add_widget(new UIButton(40, 80, "Back", std::bind(&Window::open_page<IRMainMenuPage>, _window_ptr), ST7735_RED));
        _ir_code_label_ptr = new Label(_IRP_IR_CODE_DESCRIPTION_X, _IRP_IR_CODE_DESCRIPTION_Y, "");
        _window_ptr->add_widget(_ir_code_label_ptr);
        _ir_type_label_ptr = new Label(_IRP_IR_CODE_DESCRIPTION_X, _IRP_IR_CODE_DESCRIPTION_Y + 8, "");
        _window_ptr->add_widget(_ir_type_label_ptr);
        IRReceiver::begin();
    }

    void IRReadPage::update()
    {
        if (_is_listening && IRReceiver::decode(&_ir_data)) // && ir_receiver_ptr->decode(&_results)
        {
            _signal_is_available = 1;
            _signal_was_saved = 0;
            const char *f_code_str = "code: %8X";
            const char *f_type_str = "decode_type: %d";
            char code_str_buffer[20];
            char type_str_buffer[20];
            // sprintf(code_str_buffer, f_code_str, _results.value);
            // sprintf(type_str_buffer, f_type_str, _results.decode_type);
            Serial.println("data received");
            Serial.printf("raw len: %d\n", _ir_data.raw_len);

            _ir_code_label_ptr->change_text(code_str_buffer);
            _ir_type_label_ptr->change_text(type_str_buffer);
            _warning_label_ptr->change_text("");
            stop_listen();
        }
    }

    void IRReadPage::btn_change_status()
    {
        if (_is_listening)
            stop_listen();
        else
            start_listen();
    }

    void IRReadPage::btn_try_send()
    {
        if (!_signal_is_available)
        {
            raise_error();
            return;
        }

        // uint16_t raw_data[_results.rawlen];s
        // for (uint16_t i = 1; i < _results.rawlen; i++)
        //     raw_data[i - 1] = _results.rawbuf[i] * kRawTick;
        // _ir_sender.sendRaw(raw_data, _results.rawlen, 38);
        uint16_t raw_buf[_ir_data.raw_len];
        for (uint16_t i = 0; i < _ir_data.raw_len; i++)
        {
            raw_buf[i] = _ir_data.raw_data[i];
            Serial.print(_ir_data.raw_data[i]);
            Serial.print(", ");
        }
        IRSender::send_raw(raw_buf, _ir_data.raw_len);
    }

    void IRReadPage::btn_save_current_ir()
    {
        if (_signal_was_saved || !_signal_is_available)
        {
            raise_error();
            return;
        }

        uint16_t file_quantity = Managers::SDManager::get_files_amount(IR_FILES_FOLDER_PATH);
        const char *path_template_ptr = "%s/ir_%d.bin";
        char path_buff[strlen(IR_FILES_FOLDER_PATH) + strlen(path_template_ptr)];
        sprintf(path_buff, path_template_ptr, IR_FILES_FOLDER_PATH, file_quantity);
        Managers::SDManager::write_file(path_buff, (uint8_t *)_ir_data.raw_data, _ir_data.raw_len * sizeof(uint16_t));
        _signal_was_saved = 1;
    }

    void IRReadPage::start_listen()
    {
        _is_listening = 1;
        _change_status_btn_ptr->change_text("Stop listen");
        _window_ptr->draw();
        draw_listen_indicator();
        IRReceiver::enable();
        // ir_receiver_ptr->resume();
    }

    void IRReadPage::stop_listen()
    {
        _is_listening = 0;
        _change_status_btn_ptr->change_text("Start listen");
        _window_ptr->draw();
        // IRReceiver::disable();
        // ir_receiver_ptr->pause();
    }

    void IRReadPage::draw_listen_indicator()
    {
        screen.fillCircle(5, 5, 4, _IRP_LISTEN_STATUS_COLOR);
    }

    void IRReadPage::raise_error()
    {
        _warning_label_ptr->change_text("Error");
        _window_ptr->draw();
    }
}