#ifndef _PHYS_BUTTON_H
#define _PHYS_BUTTON_H
#include <Arduino.h>

enum class ButtonEvent : uint8_t // указываем тип элемента
{
	NONE,
	CLICK
};

enum class ButtonState {
	Released,
	Pressed,
};

class PhysButton
{
private:
	static const uint16_t kButtonCooldown = 200;
	uint8_t _pin;
	unsigned long _last_press_time = 0;
	bool _was_pressed_flag;
	bool _has_external_res;
	ButtonState _current_state = ButtonState::Released;
	bool _was_changed = false;

public:
	PhysButton(uint8_t pin, bool has_external_res = false);
	void setup();
	ButtonEvent check();
	bool check_();
	ButtonState get_state();
	bool get_state_changing();
	uint8_t get_pin();
};

extern ButtonEvent btn_st_up;
extern ButtonEvent btn_st_down;
extern ButtonEvent btn_st_left;
extern ButtonEvent btn_st_right;
extern ButtonEvent btn_st_center;
extern ButtonEvent btn_st_back;
extern ButtonEvent btn_st_command;
extern ButtonEvent btn_st_home;

#endif