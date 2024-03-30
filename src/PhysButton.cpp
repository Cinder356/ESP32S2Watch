#include "PhysButton.h"

// ButtonEvents

// Button
Button::Button(uint8_t pin) : _pin(pin) {}

void Button::setup()
{
    pinMode(_pin, INPUT_PULLUP);
}

ButtonEvent Button::check()
{
    bool button_status = !digitalRead(_pin);
    if (button_status && !_was_pressed_flag && (millis() > _last_press_time)) //
    {
        _was_pressed_flag = true;
        _last_press_time = millis() + _BUTTON_COOLDOWN;
        return ButtonEvent::CLICK;
    }
    else if (_was_pressed_flag && !button_status)
    {
        _was_pressed_flag = false;
    }
    return ButtonEvent::NONE;
}
