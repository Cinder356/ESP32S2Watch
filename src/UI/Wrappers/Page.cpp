#include "UI/Wrappers/Page.h"

namespace UI::Wrappers
{
    Page::~Page()
    {
        for (uint16_t i = 0; i < _static_widgets_vector.size(); i++)
            delete _static_widgets_vector[i];
        for (uint16_t i = 0; i < _interactive_widgets_vector.size(); i++)
            delete _interactive_widgets_vector[i];
    }

    Page::Page() {}

    void Page::update(ButtonEvents button_events)
    {
    }

    void Page::draw()
    {
        for (uint16_t i = 0; i < _static_widgets_vector.size(); i++)
            _static_widgets_vector[i]->draw();
        for (uint16_t i = 0; i < _interactive_widgets_vector.size(); i++)
            _interactive_widgets_vector[i]->draw();
    }

    void Page::add_widget(AbstractStaticWidget *widget) { _static_widgets_vector.push_back(widget); }
    void Page::add_widget(AbstractInteractiveWidget *widget) { _interactive_widgets_vector.push_back(widget); }
}