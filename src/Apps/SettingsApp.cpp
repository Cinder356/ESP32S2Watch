#include "Apps/SettingsApp.h"



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

    void SettingsApp::update(ButtonEvents button_events) 
    {
        if (button_events.up == ButtonEvent::CLICK)
        {
            screen.fillScreen(SETTINGS_BACKGROUND_COLOR);
            screen.setCursor(0, 0);
            screen.println("up");
        }
        else if (button_events.down == ButtonEvent::CLICK)
        {
            screen.fillScreen(SETTINGS_BACKGROUND_COLOR);
            screen.setCursor(0, 0);
            screen.println("down");
        }
        else if (button_events.left == ButtonEvent::CLICK)
        {
            screen.fillScreen(SETTINGS_BACKGROUND_COLOR);
            screen.setCursor(0, 0);
            screen.println("left");
        }
        else if (button_events.right == ButtonEvent::CLICK)
        {
            screen.fillScreen(SETTINGS_BACKGROUND_COLOR);
            screen.setCursor(0, 0);
            screen.println("right");
        }
        else if (button_events.center == ButtonEvent::CLICK)
        {
            screen.fillScreen(SETTINGS_BACKGROUND_COLOR);
            screen.setCursor(0, 0);
            screen.println("center");
        }
        else if (button_events.back == ButtonEvent::CLICK)
        {
            screen.fillScreen(SETTINGS_BACKGROUND_COLOR);
            screen.setCursor(0, 0);
            screen.println("back");
        }
    }

    uint16_t *SettingsApp::get_icon() const
    {
        return Managers::SDManager::read_bin_image(SETTINGS_ICON_PATH);
    }
}