#ifndef _SETTINGS_APP_H
#define _SETTINGS_APP_H

#include "PhysButton.h"
#include "Apps/AbstractApp.h"
#include "Static/SDPaths.h"
#include "Managers/SDManager.h"

#define SETTINGS_BACKGROUND_COLOR 0xF417 // pink

namespace Apps
{
    class SettingsApp : public Apps::AbstractApp
    {
    private:

    public:
        void start() override;
        void close() override;
        void update() override;
        uint16_t *get_icon() const override;
    };
};
#endif