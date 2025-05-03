#ifndef _PHYS_BTN_MANAGER_H
#define _PHYS_BTN_MANAGER_H

#include <functional>
#include <vector>
#include <unordered_map>
#include "./PButtons.h"
#include "Static/Config.h"

namespace Managers::PhysBtnManager {
	class PBtnManager {
	public:
		using Callback = std::function<void()>;
		using CallbackID = ulong;

	private:
		static std::unordered_map<CallbackID, Callback> _callbacks;
		static CallbackID _last_id;

		static void trigger_callbacks();

	public:
		PBtnManager() = delete;
		static void setup();
		static void loop();
		// @brief Adds a callback that triggers on changes to any button's status
		static CallbackID add_callback(const Callback& callback);
		static void remove_callback(const CallbackID callback_id);
		// static ButtonState get_btn_state(uint8_t btn_pin);
	};
}

#endif