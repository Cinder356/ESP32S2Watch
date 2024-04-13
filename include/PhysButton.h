#ifndef _BUTTON_H
#define _BUTTON_H
#include <Arduino.h>

enum class ButtonEvent : uint8_t // указываем тип элемента
{
    NONE,
    CLICK
};

class PhysButton
{
private:
    static const uint16_t _BUTTON_COOLDOWN = 200;
    uint8_t _pin;
    unsigned long _last_press_time = 0;
    bool _was_pressed_flag;

public:
    PhysButton(uint8_t pin);
    void setup();
    ButtonEvent check();
};

extern ButtonEvent btn_st_up;
extern ButtonEvent btn_st_down;
extern ButtonEvent btn_st_left;
extern ButtonEvent btn_st_right;
extern ButtonEvent btn_st_center;
extern ButtonEvent btn_st_back;

#endif