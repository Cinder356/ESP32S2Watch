#ifndef _APP_H
#define _APP_H
#include <Arduino.h>
#include "Static/Screen.h"
#include "Button.h"

namespace Apps
{
    // enum AppType : uint8_t
    // {
    //     NOT_IMPLEMENTED,
    //     SETTINGS,
    //     NOTEPAD,
    // };

    class AbstractApp
    {
    private:
    public:
        // const AppType APP_TYPE = AppType::NOT_IMPLEMENTED;

        virtual void start() = 0;
        virtual void close() = 0;
        virtual void update(ButtonEvents button_events) = 0;
        virtual uint16_t *get_icon() const = 0;
    };
};
#endif

/*app sample:
.h

#include <Adafruit_ST7735.h>
#include "Apps/AbstractApp.h"
#include "Managers/SDManager.h"
#include "Static/SDPaths.h"
namespace Apps
{
    class ___ : public Apps::AbstractApp
    {
    private:
        Adafruit_ST7735 &_screen_ref;

    public:
        ___(Adafruit_ST7735 &screen_ref);
        // ~SettingsApp();
        void start() override;
        void close() override;
        void update(ButtonEvents button_events) override;
        uint16_t *get_icon() const override;
    };
}
.cpp

#include "Apps/___.h"
namespace Apps
{
    ___::___(Adafruit_ST7735 &screen_ref) : _screen_ref(screen_ref) {}

    void ___::start() {}
    void ___::close() {}
    void ___::update(ButtonEvents button_events) {}
    uint16_t *___::get_icon() const { return Managers::SDManager::read_bin_image(___); }
}
*/