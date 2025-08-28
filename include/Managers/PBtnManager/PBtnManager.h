#ifndef _PHYS_BTN_MANAGER_H
#define _PHYS_BTN_MANAGER_H

#include <functional>
#include <vector>
#include <unordered_map>
#include "./PBtn.h"
#include "Static/Pins.h"
#include "Static/Config.h"

namespace Managers::PBtnManager
{
	using BtnHandler = std::function<void(int /*pin*/, PBtnEvent)>;
	using BtnHandlerID = ulong;

	class PBtnManager
	{
	private:
		static std::vector<PBtn> _buttons;
		static std::vector<BtnHandler> _handlers;
		static std::vector<BtnHandlerID> _free_indices;

		static void trigger_handlers(int pin, PBtnEvent event);

	public:
		PBtnManager() = delete;
		static void setup(std::vector<PBtn> &&button_vec);
		static void loop();
		// @brief Adds a handler that triggers on changes to any button's status
		static BtnHandlerID add_handler(const BtnHandler &&handler);
		static void remove_handler(const BtnHandlerID handler_id);
	};
}

#endif