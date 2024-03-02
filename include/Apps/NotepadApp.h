#ifndef _NOTEPAD_APP_H
#define _NOTEPAD_APP_H

#include <Adafruit_ST7735.h>

#include "Button.h"
#include "Apps/AbstractApp.h"
#include "Static/SDPaths.h"
#include "Managers/SDManager.h"
#include "UISolutions/FileExplorer.h"

#define NOTEPAD_PATH_TEXT_COLOR 0xffff
#define NOTEPAD_BACKGROUND_COLOR 0x0000

namespace Apps
{
    enum AppStatus : uint8_t
    {
        NONE,
        EXPLORING
    };

    class NotepadApp : public Apps::AbstractApp
    {
    private:
        UISolutions::FileExplorer *_file_explorer_ptr;
        AppStatus _app_status;

    public:
        // ~SettingsApp();
        void start() override;
        void close() override;
        void update(ButtonEvents button_events) override;
        uint16_t *get_icon() const override;
    };
}
#endif