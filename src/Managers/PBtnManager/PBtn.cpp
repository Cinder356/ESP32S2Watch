#include "Managers/PBtnManager/PBtn.h"

namespace Managers::PBtnManager
{
    PBtn::PBtn(int pin, bool has_external_resistor) : _pin(pin), _has_external_resistor(has_external_resistor) {}

    int PBtn::get_pin() { return _pin; }

    void PBtn::setup()
    {
        if (_has_external_resistor)
        {
            pinMode(_pin, INPUT);
            return;
        }
        pinMode(_pin, INPUT_PULLUP);
    }

    PBtnEvent PBtn::check()
    {
        bool button_status = digitalRead(_pin);
        if (!button_status && !_is_pressed && (millis() > _last_press_time))
        {
            _is_pressed = true;
            _last_press_time = millis() + kDebounceDelay;
            return PBtnEvent::DOWN;
        }
        if (_is_pressed && button_status)
        {
            _is_pressed = false;
            return PBtnEvent::UP;
        }
        return PBtnEvent::NONE;
    }
}