#ifndef _BUTTON_H
#define _BUTTON_H
#include <Arduino.h>

enum class ButtonEvent : uint8_t // указываем тип элемента
{
    NONE,
    CLICK
};

struct ButtonEvents // __attribute__((packed))
{
    ButtonEvent up;
    ButtonEvent down;
    ButtonEvent left;
    ButtonEvent right;
    ButtonEvent center;
    ButtonEvent back;
};

class Button
{
private:
    const uint16_t _BUTTON_COOLDOWN = 200;
    uint8_t _pin;
    unsigned long _last_press_time = 0;
    bool _was_pressed_flag;

public:
    Button(uint8_t pin);
    void setup();
    ButtonEvent check();
};

#endif