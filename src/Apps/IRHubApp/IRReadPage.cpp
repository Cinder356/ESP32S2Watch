#include "Apps/IRHubApp/IRHubAllPages.h"

namespace Apps::IRHub::Pages
{
    IRReadPage::~IRReadPage() { ir_receiver_ptr->disableIRIn(); }

    IRReadPage::IRReadPage(Window *window_ptr) : _window_ptr(window_ptr) {}

    void IRReadPage::open()
    {
        if (ir_receiver_ptr == nullptr)
            ir_receiver_ptr = new IRrecv(IR_RECEIVER_PIN);
        ir_receiver_ptr->enableIRIn();
        _ir_sender.begin();

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
    }

    void IRReadPage::update()
    {
        if (_is_listening && ir_receiver_ptr->decode(&_results))
        {
            _signal_is_available = 1;
            _signal_was_saved = 0;
            const char *f_code_str = "code: %8X";
            const char *f_type_str = "decode_type: %d";
            char code_str_buffer[20];
            char type_str_buffer[20];
            sprintf(code_str_buffer, f_code_str, _results.value);
            sprintf(type_str_buffer, f_type_str, _results.decode_type);
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

        uint16_t raw_data[_results.rawlen];
        for (uint16_t i = 1; i < _results.rawlen; i++)
            raw_data[i - 1] = _results.rawbuf[i] * kRawTick;
        _ir_sender.sendRaw(raw_data, _results.rawlen, 38);
    }

    void IRReadPage::btn_save_current_ir()
    {
        if (_signal_was_saved || !_signal_is_available)
        {
            raise_error();
            return;
        }

        uint16_t file_quantity = Managers::SDManager::get_files_amount(IR_FILES_FOLDER_PATH);
        const char *path_template = "%s/ir_%d.bin";
        char path_buff[strlen(IR_FILES_FOLDER_PATH) + strlen(path_template)];
        sprintf(path_buff, path_template, IR_FILES_FOLDER_PATH, file_quantity);
        uint16_t ir_code_buff[_results.rawlen];
        for (uint8_t i = 1; i < _results.rawlen; i++)
            ir_code_buff[i - 1] = _results.rawbuf[i] * kRawTick;
        Serial.printf("buff_len: %d\n", _results.rawlen);
        for (uint8_t i; i < 4; i++)
            Serial.printf("%d ", ir_code_buff[i]);
        Serial.println();
        Managers::SDManager::write_file(path_buff, (uint8_t *)ir_code_buff, _results.rawlen * sizeof(uint16_t));
        _signal_was_saved = 1;
    }

    void IRReadPage::start_listen()
    {
        _is_listening = 1;
        _change_status_btn_ptr->change_text("Stop listen");
        _window_ptr->draw();
        draw_listen_indicator();
        ir_receiver_ptr->resume();
    }

    void IRReadPage::stop_listen()
    {
        _is_listening = 0;
        _change_status_btn_ptr->change_text("Start listen");
        _window_ptr->draw();
        ir_receiver_ptr->pause();
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