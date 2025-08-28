#include "Managers/PBtnManager/PBtnManager.h"

namespace Managers::PBtnManager
{
	std::vector<PBtn> PBtnManager::_buttons;
	std::vector<BtnHandler> PBtnManager::_handlers;
	std::vector<BtnHandlerID> PBtnManager::_free_indices;

	void PBtnManager::trigger_handlers(int pin, PBtnEvent event)
	{
		Serial.printf("Handlers size: %d\n", _handlers.size());
		for (BtnHandler &handler : _handlers) // Problem: there must be triggered just old handlers.
			if (handler)
				handler(pin, event);
	}

	void PBtnManager::setup(std::vector<PBtn> &&button_vec)
	{
		_buttons = std::move(button_vec);

		for (PBtn &button : _buttons)
			button.setup();
	}

	void PBtnManager::loop()
	{
		for (PBtn &button : _buttons)
		{
			PBtnEvent event = button.check();
			if (event == PBtnEvent::NONE)
				continue;
			trigger_handlers(button.get_pin(), event);
		}
	}

	BtnHandlerID PBtnManager::add_handler(const BtnHandler &&handler)
	{
		if (_free_indices.empty())
		{
			_handlers.emplace_back(std::move(handler));
			return _handlers.size() - 1;
		}
		BtnHandlerID handler_id = _free_indices.back();
		_free_indices.pop_back();
		_handlers[handler_id] = std::move(handler);
		return handler_id;
	}

	void PBtnManager::remove_handler(const BtnHandlerID handler_id)
	{
		_handlers[handler_id] = nullptr;
		_free_indices.push_back(handler_id);
	}
}