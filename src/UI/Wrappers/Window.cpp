#include "UI/Wrappers/Window.h"

namespace UI::Wrappers
{
    Window::~Window() { clear(); }

    Window::Window(uint16_t background_color) : _background_color(background_color) {}

    void Window::update()
    {
        if (btn_st_center == ButtonEvent::CLICK && is_active)
        {
            _interactive_widgets_vector[_cursor]->invoke();
            btn_st_center = ButtonEvent::NONE;
        }
        if (btn_st_up == ButtonEvent::CLICK && is_active && _cursor > 0)
        {
            _interactive_widgets_vector[_cursor]->deselect();
            _cursor--;
            _interactive_widgets_vector[_cursor]->select();
        }
        if (btn_st_down == ButtonEvent::CLICK && is_active && _cursor < _interactive_widgets_vector.size() - 1)
        {
            _interactive_widgets_vector[_cursor]->deselect();
            _cursor++;
            _interactive_widgets_vector[_cursor]->select();
        }
        _current_page_ptr->update();
    }

    void Window::draw()
    {
        screen.fillScreen(_background_color);
        for (uint16_t i = 0; i < _static_widgets_vector.size(); i++)
            _static_widgets_vector[i]->draw();
        for (uint16_t i = 0; i < _interactive_widgets_vector.size(); i++)
            _interactive_widgets_vector[i]->draw();
        if (_interactive_widgets_vector.size() > 0)
        {
            _interactive_widgets_vector[_cursor]->select();
        }
    }

    void Window::add_widget(AbstractStaticWidget *widget) { _static_widgets_vector.push_back(widget); }
    void Window::add_widget(AbstractInteractiveWidget *widget) { _interactive_widgets_vector.push_back(widget); }

    void Window::open_page(AbstractPage *page_ptr)
    {
        clear();
        _current_page_ptr = page_ptr;
        _current_page_ptr->open();
        if (is_active)
            draw();
    }

    void Window::clear()
    {
        for (auto widget : _static_widgets_vector)
            delete widget;
        for (auto widget : _interactive_widgets_vector)
            delete widget;
        _static_widgets_vector.clear();
        _interactive_widgets_vector.clear();

        if (_current_page_ptr != nullptr)
            delete _current_page_ptr;
        _cursor = 0;
    }
}