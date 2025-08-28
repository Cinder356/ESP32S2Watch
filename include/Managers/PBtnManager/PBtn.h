#pragma once

#include <Arduino.h>


namespace Managers::PBtnManager
{
    enum class PBtnEvent
    {
        NONE,
        DOWN,
        UP
    };

    class PBtn
    {
    private:
        static const int kDebounceDelay = 200;

        int _pin;
        bool _has_external_resistor;
        unsigned long _last_press_time = 0;
        bool _is_pressed;

    public:
        PBtn(int pin, bool has_external_resistor = false);
        int get_pin();
        void setup();
        PBtnEvent check();
    };
}