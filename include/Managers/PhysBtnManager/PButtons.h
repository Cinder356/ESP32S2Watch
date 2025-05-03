#ifndef _PHYS_BUTTONS_H
#define _PHYS_BUTTONS_H

#include <array>
#include "PhysButton.h"
#include "Static/Pins.h"

namespace Managers::PhysBtnManager::PButtons {
	inline PhysButton up_button = PhysButton(UP_BUTTON_PIN, 0);
	inline PhysButton down_button = PhysButton(DOWN_BUTTON_PIN, 0);
	inline PhysButton left_button = PhysButton(LEFT_BUTTON_PIN, 0);
	inline PhysButton right_button = PhysButton(RIGHT_BUTTON_PIN, 0);
	inline PhysButton center_button = PhysButton(CENTER_BUTTON_PIN, 0);
	inline PhysButton back_button = PhysButton(BACK_BUTTON_PIN, 0);
	inline PhysButton command_button = PhysButton(COMMAND_BUTTON_PIN, 1);
	inline PhysButton home_button = PhysButton(HOME_BUTTON_PIN, 1);

	// const PhysButton* btn_array[]{
	// 	&up_button, &down_button, &left_button, &right_button,
	// 	&center_button, &back_button, &command_button, &home_button
	// };
	// const uint8_t btn_array_size = sizeof(btn_array) / sizeof(PhysButton*);
}

#endif