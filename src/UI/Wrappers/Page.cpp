#include "UI/Wrappers/Page.h"

namespace UI::Wrappers
{
    Page::~Page() {clear();}

    Page::Page(uint16_t background_color) : _background_color(background_color) {}

    void Page::update(ButtonEvents button_events)
    {
        if (button_events.center == ButtonEvent::CLICK)
            _interactive_widgets_vector[_cursor]->invoke();
        if (button_events.up == ButtonEvent::CLICK && _cursor > 0)
        {
            _interactive_widgets_vector[_cursor]->deselect();
            _cursor--;
            _interactive_widgets_vector[_cursor]->select();
        }
        if (button_events.down == ButtonEvent::CLICK && _cursor < _interactive_widgets_vector.size() - 1)
        {
            _interactive_widgets_vector[_cursor]->deselect();
            _cursor++;
            _interactive_widgets_vector[_cursor]->select();
        }
    }

    void Page::draw()
    {
        screen.fillScreen(_background_color);
        for (uint16_t i = 0; i < _static_widgets_vector.size(); i++)
            _static_widgets_vector[i]->draw();
        for (uint16_t i = 0; i < _interactive_widgets_vector.size(); i++)
            _interactive_widgets_vector[i]->draw();
        _interactive_widgets_vector[_cursor]->select();
    }

    void Page::add_widget(AbstractStaticWidget *widget) { _static_widgets_vector.push_back(widget); }
    void Page::add_widget(AbstractInteractiveWidget *widget) { _interactive_widgets_vector.push_back(widget); }

    void Page::clear()
    {
        for (uint16_t i = 0; i < _static_widgets_vector.size(); i++)
            delete _static_widgets_vector[i];
        for (uint16_t i = 0; i < _interactive_widgets_vector.size(); i++)
            delete _interactive_widgets_vector[i];
        _static_widgets_vector.clear();
        _interactive_widgets_vector.clear();
    }
}