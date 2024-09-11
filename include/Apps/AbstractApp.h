#ifndef _APP_H
#define _APP_H
#include <Arduino.h>
#include "Static/Screen.h"
#include "PhysButton.h"

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
    public:
        // const AppType APP_TYPE = AppType::NOT_IMPLEMENTED;

        virtual void start() = 0;
        virtual void close() = 0;
        virtual void update() = 0;
        virtual uint16_t *get_icon() const = 0;
    };
};
#endif

/*app sample:
.h

#include "Apps/AbstractApp.h"
#include "Managers/SDManager.h"
#include "Static/SDPaths.h"
#include "Static/Screen.h"
namespace Apps
{
    class ___ : public Apps::AbstractApp
    {
    private:

    public:
        // ~___();
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
    void ___::start() {}
    void ___::close() {}
    void ___::update(ButtonEvents button_events) {}
    uint16_t *___::get_icon() const { return Managers::SDManager::read_bin_image(___); }
}
*/