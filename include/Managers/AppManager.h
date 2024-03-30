#ifndef _APP_MANAGER_H
#define _APP_MANAGER_H

#include <Arduino.h>
#include <vector>

#include "PhysButton.h"
#include "Apps/AbstractApp.h"
#include "Managers/SDManager.h"
#include "Static/Bitmaps.h"

#define MENU_ICON_SIZE 32
#define MENU_BASIC_PADDING 8
#define MENU_PADDING 8
#define MENU_COLUMNS 3
#define MENU_ROWS 3
#define MENU_CURSOR_COLOR ST7735_CYAN
#define MENU_BACKGROUND_COLOR ST7735_BLACK

using namespace Apps;

namespace Managers
{
    struct MenuAppWidget
    {
        uint8_t x;
        uint8_t y;
        AbstractApp *app_ptr;
    };

    class AppManager
    {
    private:
        std::vector<MenuAppWidget> _apps_vector;

        int8_t _menu_cursor;
        AbstractApp *_current_app_ptr = nullptr;

        void start_menu();
        void update_menu();
        void draw_menu_cursor(uint16_t color);
        
        void open_app(AbstractApp* app);
    public:
        void start(AbstractApp* app_array[], uint8_t app_array_size);
        void loop();

        void close_current_app();
    };
};

#endif