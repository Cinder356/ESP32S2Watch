#ifndef _SETTINGS_APP_H
#define _SETTINGS_APP_H

#include <Adafruit_ST7735.h>

#include "Button.h"
#include "Apps/AbstractApp.h"
#include "Static/SDPaths.h"
#include "Managers/SDManager.h"

#include "Managers/AppManager.h"

#define SETTINGS_BACKGROUND_COLOR 0xF417 // pink

namespace Apps
{
    class SettingsApp : public Apps::AbstractApp
    {
    private:
        Adafruit_ST7735 &_screen_ref;

    public:
        SettingsApp(Adafruit_ST7735 &screen_ref);
        // ~SettingsApp();
        void start() override;
        void close() override;
        void update(ButtonEvents button_events) override;
        uint16_t *get_icon() const override;
    };
};
#endif