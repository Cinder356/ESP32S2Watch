#ifndef _FILE_EXPLORER_APP_H
#define _FILE_EXPLORER_APP_H

#include <Adafruit_ST7735.h>

#include "Button.h"
#include "Apps/AbstractApp.h"
#include "Static/SDPaths.h"
#include "Managers/SDManager.h"

#include "Managers/AppManager.h"

namespace Apps
{
    class FileExplorer : public Apps::AbstractApp
    {
    private:
        Adafruit_ST7735 &_screen_ref;

    public:
        FileExplorer(Adafruit_ST7735 &screen_ref);
        // ~SettingsApp();
        void start() override;
        void close() override;
        void update(ButtonEvents button_events) override;
        uint16_t *get_icon() const override;

        String explore(const char *start_path = "/")
        {
            return "h";
        }
    };
}

#endif