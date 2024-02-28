#ifndef _NOTEPAD_APP_H
#define _NOTEPAD_APP_H

#include <Adafruit_ST7735.h>

#include "Button.h"
#include "Apps/AbstractApp.h"
#include "Static/SDPaths.h"
#include "Managers/SDManager.h"

#include "Managers/AppManager.h"

#define NOTEPAD_PATH_TEXT_COLOR 0xffff
#define NOTEPAD_BACKGROUND_COLOR 0x0000

namespace Apps
{
    class NotepadApp : public Apps::AbstractApp
    {
    private:
        Adafruit_ST7735 &_screen_ref;

    public:
        NotepadApp(Adafruit_ST7735 &screen_ref);
        // ~SettingsApp();
        void start() override;
        void close() override;
        void update(ButtonEvents button_events) override;
        uint16_t *get_icon() const override;
    };
}
#endif