#include "Apps/SettingsApp/SettingsApp.h"

namespace Apps
{
	// SettingsApp::~SettingsApp() {}
	void SettingsApp::start()
	{
		screen.fillScreen(kBackgroundColor);
		screen.setCursor(0, 0);
		screen.print("settings");
		PBtnManager::add_callback([this] {this->on_button_event();});
	}

	void SettingsApp::close() {}

	void SettingsApp::update()
	{

	}

	uint16_t* SettingsApp::get_icon() const
	{
		return Managers::SDManager::read_bin_image(SETTINGS_ICON_PATH);
	}

	void SettingsApp::on_button_event() {
		screen.fillScreen(kBackgroundColor);
		screen.setCursor(0, 0);
		if (PButtons::back_button.get_state_changing() && PButtons::back_button.get_state() == ButtonState::Released)
			screen.println("back_button");
		if (PButtons::command_button.get_state_changing() && PButtons::command_button.get_state() == ButtonState::Released)
			screen.println("command_button");
		if (PButtons::up_button.get_state_changing() && PButtons::up_button.get_state() == ButtonState::Released)
			screen.println("up_button");
		if (PButtons::left_button.get_state_changing() && PButtons::left_button.get_state() == ButtonState::Released)
			screen.println("left_button");
		if (PButtons::center_button.get_state_changing() && PButtons::center_button.get_state() == ButtonState::Released)
			screen.println("center_button");
		if (PButtons::right_button.get_state_changing() && PButtons::right_button.get_state() == ButtonState::Released)
			screen.println("right_button");
		if (PButtons::down_button.get_state_changing() && PButtons::down_button.get_state() == ButtonState::Released)
			screen.println("down_button");
	}
}