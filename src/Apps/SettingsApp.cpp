#include "Apps/SettingsApp.h"



namespace Apps
{
    SettingsApp::SettingsApp(Adafruit_ST7735 &screen_ref) : _screen_ref(screen_ref) {}
    // SettingsApp::~SettingsApp() {}
    void SettingsApp::start()
    {
        _screen_ref.fillScreen(SETTINGS_BACKGROUND_COLOR);
        _screen_ref.setCursor(0, 0);
        _screen_ref.println("settings");
    }

    void SettingsApp::close() {}

    void SettingsApp::update(ButtonEvents button_events) 
    {
        if (button_events.up == ButtonEvent::CLICK)
        {
            _screen_ref.fillScreen(SETTINGS_BACKGROUND_COLOR);
            _screen_ref.setCursor(0, 0);
            _screen_ref.println("up");
        }
        else if (button_events.down == ButtonEvent::CLICK)
        {
            _screen_ref.fillScreen(SETTINGS_BACKGROUND_COLOR);
            _screen_ref.setCursor(0, 0);
            _screen_ref.println("down");
        }
        else if (button_events.left == ButtonEvent::CLICK)
        {
            _screen_ref.fillScreen(SETTINGS_BACKGROUND_COLOR);
            _screen_ref.setCursor(0, 0);
            _screen_ref.println("left");
        }
        else if (button_events.right == ButtonEvent::CLICK)
        {
            _screen_ref.fillScreen(SETTINGS_BACKGROUND_COLOR);
            _screen_ref.setCursor(0, 0);
            _screen_ref.println("right");
        }
        else if (button_events.center == ButtonEvent::CLICK)
        {
            _screen_ref.fillScreen(SETTINGS_BACKGROUND_COLOR);
            _screen_ref.setCursor(0, 0);
            _screen_ref.println("center");
        }
        else if (button_events.back == ButtonEvent::CLICK)
        {
            _screen_ref.fillScreen(SETTINGS_BACKGROUND_COLOR);
            _screen_ref.setCursor(0, 0);
            _screen_ref.println("back");
        }
    }

    uint16_t *SettingsApp::get_icon() const
    {
        return Managers::SDManager::read_bin_image(SETTINGS_ICON_PATH);
    }
}