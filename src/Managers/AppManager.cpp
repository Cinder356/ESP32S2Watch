#include "Managers/AppManager.h"

namespace Managers
{
    // app manager
    AppManager::AppManager(AbstractApp *app_array[], uint8_t app_array_size, Adafruit_ST7735 &screen_ref) : _screen_ref(screen_ref)
    {
        // заполнение вектора приложений
        for (uint8_t i = 0; i < app_array_size; i++)
        {
            _apps_vector.push_back({0, 0, app_array[i]});
        }

        // расстановка позиций
        for (uint8_t app_index = 0; app_index < _apps_vector.size(); app_index++)
        {
            uint8_t column = app_index % MENU_COLUMNS;
            uint8_t row = app_index / MENU_ROWS;
            _apps_vector[app_index].x = MENU_BASIC_PADDING + column * MENU_ICON_SIZE + column * MENU_PADDING;
            _apps_vector[app_index].y = MENU_BASIC_PADDING + row * MENU_ICON_SIZE + row * MENU_PADDING;
        }
    }

    void AppManager::start()
    {
        start_menu();
    }

    void AppManager::loop(ButtonEvents button_events)
    {
        if (_current_app_ptr == nullptr)
            update_menu(button_events);
        else
        {
            _current_app_ptr->update(button_events);
            if (button_events.back)
                close_current_app();
        }
    }

    void AppManager::open_app(AbstractApp *app)
    {
        if (_current_app_ptr != nullptr)
            close_current_app();

        _current_app_ptr = app;
        _current_app_ptr->start();
    }

    void AppManager::close_current_app()
    {
        _current_app_ptr->close();
        _current_app_ptr = nullptr;
        start_menu();
    }

    void AppManager::change_current_app()
    {
        
    }

    // ---menu---

    void AppManager::start_menu()
    {
        // отрисовка
        _screen_ref.fillScreen(ST7735_BLACK);
        for (uint8_t app_index = 0; app_index < _apps_vector.size(); app_index++)
        {
            uint16_t *icon = _apps_vector[app_index].app_ptr->get_icon();
            if (icon == nullptr)
            {
                _screen_ref.drawRGBBitmap(_apps_vector[app_index].x, _apps_vector[app_index].y, ERROR_ICON, MENU_ICON_SIZE, MENU_ICON_SIZE);
                continue;
            }
            _screen_ref.drawRGBBitmap(_apps_vector[app_index].x, _apps_vector[app_index].y, icon, MENU_ICON_SIZE, MENU_ICON_SIZE);
            delete[] icon;
        }
        draw_menu_cursor(MENU_CURSOR_COLOR);
    }

    void AppManager::update_menu(ButtonEvents button_events)
    {
        if (button_events.up)
        {
            draw_menu_cursor(MENU_BACKGROUND_COLOR);
            if (!(_menu_cursor - MENU_COLUMNS < 0))
                _menu_cursor -= MENU_COLUMNS;
            draw_menu_cursor(MENU_CURSOR_COLOR);
        }
        else if (button_events.down)
        {
            draw_menu_cursor(MENU_BACKGROUND_COLOR);
            if (!(_menu_cursor + MENU_COLUMNS >= _apps_vector.size()))
                _menu_cursor += MENU_COLUMNS;
            draw_menu_cursor(MENU_CURSOR_COLOR);
        }
        else if (button_events.left)
        {
            draw_menu_cursor(MENU_BACKGROUND_COLOR);
            if (_menu_cursor == 0)
                _menu_cursor = _apps_vector.size() - 1;
            else
                _menu_cursor--;
            draw_menu_cursor(MENU_CURSOR_COLOR);
        }
        else if (button_events.right)
        {
            draw_menu_cursor(MENU_BACKGROUND_COLOR);
            if (_menu_cursor == _apps_vector.size() - 1)
                _menu_cursor = 0;
            else
                _menu_cursor++;
            draw_menu_cursor(MENU_CURSOR_COLOR);
        }
        else if (button_events.center)
            open_app(_apps_vector[_menu_cursor].app_ptr);
    }

    void AppManager::draw_menu_cursor(uint16_t color)
    {
        uint8_t app_x = _apps_vector[_menu_cursor].x;
        uint8_t app_y = _apps_vector[_menu_cursor].y;

        uint8_t x_without_icon = app_x - 1;
        uint8_t x_with_icon = app_x + MENU_ICON_SIZE + 1;
        uint8_t y_without_icon = app_y - 1;
        uint8_t y_with_icon = app_y + MENU_ICON_SIZE + 1;

        // left top
        _screen_ref.drawPixel(x_without_icon - 1, y_without_icon, color);
        _screen_ref.drawPixel(x_without_icon, y_without_icon - 1, color);
        _screen_ref.drawPixel(x_without_icon, y_without_icon, color); // middle
        // right top
        _screen_ref.drawPixel(x_with_icon - 1, y_without_icon, color);
        _screen_ref.drawPixel(x_with_icon, y_without_icon + 1, color);
        _screen_ref.drawPixel(x_with_icon, y_without_icon, color); // middle
        // left bottom
        _screen_ref.drawPixel(x_without_icon, y_with_icon - 1, color);
        _screen_ref.drawPixel(x_without_icon + 1, y_with_icon, color);
        _screen_ref.drawPixel(x_without_icon, y_with_icon, color); // middle
        // right bottom
        _screen_ref.drawPixel(x_with_icon, y_with_icon - 1, color);
        _screen_ref.drawPixel(x_with_icon - 1, y_with_icon, color);
        _screen_ref.drawPixel(x_with_icon, y_with_icon, color); // middle
    }
}
