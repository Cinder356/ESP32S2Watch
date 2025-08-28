#ifndef _SETTINGS_APP_H
#define _SETTINGS_APP_H

#include "Apps/AbstractApp.h"
#include "Static/SDPaths.h"
#include "Managers/SDManager.h"
#include "Managers/PBtnManager/PBtnManager.h"

using namespace Managers::PBtnManager;

namespace Apps
{
	class SettingsApp : public Apps::AbstractApp
	{
	private:
		static const uint16_t kBackgroundColor = 0x000F;
		static const uint16_t kTextColor = 0xFFFF;
		static const uint16_t kBorderColor = 0xF800;
		static const uint16_t kWidgetColor = 0x8410;

		BtnHandlerID _btn_handler_id;

	public:
		void start() override;
		void close() override;
		void update() override;
		uint16_t *get_icon() const override;
		void handle_button_event(int pin, PBtnEvent event);
	};
};
#endif