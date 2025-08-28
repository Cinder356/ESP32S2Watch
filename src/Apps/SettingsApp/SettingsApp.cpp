#include "Apps/SettingsApp/SettingsApp.h"

namespace Apps
{
	// SettingsApp::~SettingsApp() {}
	void SettingsApp::start()
	{
		screen.fillScreen(kBackgroundColor);
		screen.setCursor(0, 0);
		screen.print("settings");
		_btn_handler_id = PBtnManager::add_handler([this](int pin, PBtnEvent event)
												   { this->handle_button_event(pin, event); });
	}

	void SettingsApp::close()
	{
		PBtnManager::remove_handler(_btn_handler_id);
	}

	void SettingsApp::update()
	{
	}

	uint16_t *SettingsApp::get_icon() const
	{
		return Managers::SDManager::read_bin_image(SETTINGS_ICON_PATH);
	}

	void SettingsApp::handle_button_event(int pin, PBtnEvent event)
	{
		if (event != PBtnEvent::DOWN)
			return;
		screen.fillScreen(kBackgroundColor);
		screen.setCursor(10, 10);

		switch (pin)
		{
		case UP_BUTTON_PIN:
			screen.print("up");
			break;
		case DOWN_BUTTON_PIN:
			screen.print("down");
			break;
		case LEFT_BUTTON_PIN:
			screen.print("left");
			break;
		case RIGHT_BUTTON_PIN:
			screen.print("right");
			break;
		case CENTER_BUTTON_PIN:
			screen.print("center");
			break;
		case BACK_BUTTON_PIN:
			screen.print("back");
			break;
		case COMMAND_BUTTON_PIN:
			screen.print("command");
			break;
		}
	}
}