#include "Apps/SettingsApp/SettingsApp.h"

namespace Apps
{
    // SettingsApp::~SettingsApp() {}
    void SettingsApp::start()
    {
        screen.fillScreen(SETTINGS_BACKGROUND_COLOR);
        screen.setCursor(0, 0);
        screen.println("settings");
    }

    void SettingsApp::close() {}

    void SettingsApp::update()
    {
        if (btn_st_up == ButtonEvent::CLICK)
        {
            screen.fillScreen(SETTINGS_BACKGROUND_COLOR);
            screen.setCursor(0, 0);
            screen.println("up");
        }
        else if (btn_st_down == ButtonEvent::CLICK)
        {
            screen.fillScreen(SETTINGS_BACKGROUND_COLOR);
            screen.setCursor(0, 0);
            screen.println("down");
        }
        else if (btn_st_left == ButtonEvent::CLICK)
        {
            screen.fillScreen(SETTINGS_BACKGROUND_COLOR);
            screen.setCursor(0, 0);
            screen.println("left");
        }
        else if (btn_st_right == ButtonEvent::CLICK)
        {
            screen.fillScreen(SETTINGS_BACKGROUND_COLOR);
            screen.setCursor(0, 0);
            screen.println("right");
        }
        else if (btn_st_center == ButtonEvent::CLICK)
        {
            screen.fillScreen(SETTINGS_BACKGROUND_COLOR);
            screen.setCursor(0, 0);
            screen.println("center");
        }
        else if (btn_st_back == ButtonEvent::CLICK)
        {
            screen.fillScreen(SETTINGS_BACKGROUND_COLOR);
            screen.setCursor(0, 0);
            screen.println("back");
        }
        else if (btn_st_command == ButtonEvent::CLICK)
        {
            screen.fillScreen(SETTINGS_BACKGROUND_COLOR);
            screen.setCursor(0, 0);
            screen.println("command");
        }
    }

    uint16_t *SettingsApp::get_icon() const
    {
        return Managers::SDManager::read_bin_image(SETTINGS_ICON_PATH);
    }
}