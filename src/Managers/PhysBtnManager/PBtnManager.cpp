#include "Managers/PhysBtnManager/PBtnManager.h"

namespace Managers::PhysBtnManager {
	std::unordered_map<PBtnManager::CallbackID, PBtnManager::Callback> PBtnManager::_callbacks;
	PBtnManager::CallbackID PBtnManager::_last_id = 0;

	void PBtnManager::trigger_callbacks() {
		for (auto it = _callbacks.begin(); it != _callbacks.end(); ++it)
			it->second();
	}

	void PBtnManager::setup() {
		PButtons::up_button.setup();
		PButtons::down_button.setup();
		PButtons::left_button.setup();
		PButtons::right_button.setup();
		PButtons::center_button.setup();
		PButtons::back_button.setup();
		PButtons::command_button.setup();
		PButtons::home_button.setup();
	}

	void PBtnManager::loop() {
		if (PButtons::up_button.check_() || PButtons::down_button.check_() || PButtons::left_button.check_() || PButtons::right_button.check_() ||
			PButtons::center_button.check_() || PButtons::back_button.check_() || PButtons::command_button.check_() || PButtons::home_button.check_())
			trigger_callbacks();

		// <<<<<<<<<<<<<<<<<<<<<<<  serial buttons  >>>>>>>>>>>>>>>>>>>>>>>

		if (Serial.available() > 0) {
			char incomingByte = Serial.read();

			Serial.print("Received: ");
			Serial.println(incomingByte);
		}
#if SERIAL_BUTTONS
#endif
	}

	PBtnManager::CallbackID PBtnManager::add_callback(const Callback& callback) {
		_callbacks.insert({ _last_id, callback });
		return _last_id++;
	}

	void PBtnManager::remove_callback(const CallbackID callback_id) {
		_callbacks.erase(callback_id);
	}

	// ButtonState PhysBtnManager::get_btn_state(uint8_t btn_pin) {
	// 	for (auto it = _buttons.begin(); it < _buttons.end(); it++) {
	// 		if (it->get_pin() == btn_pin)
	// 			return it->get_state();
	// 	}
	// } 


}