#include "UI/Wrappers/Window.h"

namespace UI::Wrappers
{
    Window::~Window()
    {
        clear();
        PBtnManager::remove_handler(_btn_handler_id);
    }

    Window::Window(uint16_t background_color) : _background_color(background_color)
    {
        _btn_handler_id = PBtnManager::add_handler([this](int pin, PBtnEvent event)
                                                   { this->handle_button_event(pin, event); });
    }

    void Window::handle_button_event(int pin, PBtnEvent event)
    {
        if (event != PBtnEvent::DOWN && !is_active)
            return;

        switch (pin)
        {
        case CENTER_BUTTON_PIN:
            _interactive_widgets_vector[_cursor]->invoke();
            break;
        case UP_BUTTON_PIN:
            if (_cursor > 0)
            {
                _interactive_widgets_vector[_cursor]->deselect();
                _cursor--;
                _interactive_widgets_vector[_cursor]->select();
            }
            break;
        case DOWN_BUTTON_PIN:
            if (_cursor < _interactive_widgets_vector.size() - 1)
            {
                _interactive_widgets_vector[_cursor]->deselect();
                _cursor++;
                _interactive_widgets_vector[_cursor]->select();
            }
            break;
        }
    }

    void Window::update()
    {
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