#include "PhysButton.h"

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
	bool button_status = digitalRead(_pin);
	if (!button_status && !_was_pressed_flag && (millis() > _last_press_time)) //
	{
		_was_pressed_flag = true;
		_last_press_time = millis() + kButtonCooldown;
		return ButtonEvent::CLICK;
	}
	else if (_was_pressed_flag && button_status)
	{
		_was_pressed_flag = false;
	}
	return ButtonEvent::NONE;
}

bool PhysButton::check_() {
	bool button_status = digitalRead(_pin);
	if (!button_status && !_was_pressed_flag && (millis() > _last_press_time)) //
	{
		_was_pressed_flag = true;
		_last_press_time = millis() + kButtonCooldown;
		_current_state = ButtonState::Pressed;

		_was_changed = true;
		return _was_changed;
	}
	else if (_was_pressed_flag && button_status)
	{
		_was_pressed_flag = false;
		_current_state = ButtonState::Released;

		_was_changed = true;
		return _was_changed;
	}

	_was_changed = false;
	return _was_changed;
}

ButtonState PhysButton::get_state() {
	return _current_state;
}

bool PhysButton::get_state_changing() {
	return _was_changed;
};

uint8_t PhysButton::get_pin() {
	return _pin;
}