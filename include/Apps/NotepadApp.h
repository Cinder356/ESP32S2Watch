#ifndef _NOTEPAD_APP_H
#define _NOTEPAD_APP_H

#include <Adafruit_ST7735.h>

#include "Button.h"
#include "Apps/AbstractApp.h"
#include "Static/SDPaths.h"
#include "Managers/SDManager.h"
#include "UISolutions/FileExplorer.h"

#define NOTEPAD_TEXT_COLOR 0xffff
#define NOTEPAD_BACKGROUND_COLOR 0x0000
#define NOTEPAD_TEXT_SIZE SMALL_TEXT_SIZE
#define NOTEPAD_PERMANENT_LABELS_QUANTITY 1
#define NOTEPAD_FILE_TEXT_LINES_QUANTITY (GET_MAX_TEXT_LINES(NOTEPAD_TEXT_SIZE) - NOTEPAD_PERMANENT_LABELS_QUANTITY)
#define NOTEPAD_MAX_CHAR_QUANTITY (NOTEPAD_FILE_TEXT_LINES_QUANTITY * GET_MAX_TEXT_COLUMNS(NOTEPAD_TEXT_SIZE))


namespace Apps
{
    enum class AppStatus : uint8_t
    {
        NONE,
        EXPLORING,
        TEXT_VIEW
    };

    class NotepadApp : public Apps::AbstractApp
    {
    private:
        UISolutions::FileExplorer *_file_explorer_ptr;
        AppStatus _app_status = AppStatus::NONE;
        String _file_path;
        uint8_t _current_page;
        uint8_t _file_pages_quantity;

        void open_txt(String path);
        void draw_page();
    public:
        // ~SettingsApp();
        void start() override;
        void close() override;
        void update(ButtonEvents button_events) override;
        uint16_t *get_icon() const override;
    };
}
#endif