#include "PhysButton.h"

// ButtonEvents

// Button
PhysButton::PhysButton(uint8_t pin, bool has_external_res) : _pin(pin), _has_external_res(has_external_res) {}

void PhysButton::setup()
{
    if (_has_external_res)
    {
        pinMode(_pin, INPUT);
        return;
    }
    pinMode(_pin, INPUT_PULLUP);
}

ButtonEvent PhysButton::check()
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
