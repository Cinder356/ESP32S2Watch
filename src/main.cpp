#include <Arduino.h>
#include <vector>
#include <SPI.h>
#include <Adafruit_GFX.h>
#include <Adafruit_ST7735.h>

#include "Static/Config.h"
#include "Static/Pins.h"
#include "Static/Bitmaps.h"
#include "Managers/AppManager.h"
#include "Managers/SDManager.h"
#include "Managers/IRManager/IRReceiver.h"
#include "Managers/PhysBtnManager/PBtnManager.h"

#include "Apps/AbstractApp.h"
#include "Apps/SettingsApp/SettingsApp.h"
#include "Apps/NotepadApp/NotepadApp.h"
#include "Apps/IRHubApp/IRHubApp.h"
#include "Apps/MinesweeperApp/MinesweeperApp.h"

Adafruit_ST7735 screen(TFT_CS, TFT_DC, TFT_RST);
Managers::AppManager app_manager;

#pragma region Buttons
PhysButton up_button = PhysButton(UP_BUTTON_PIN, 0);
PhysButton down_button = PhysButton(DOWN_BUTTON_PIN, 0);
PhysButton left_button = PhysButton(LEFT_BUTTON_PIN, 0);
PhysButton right_button = PhysButton(RIGHT_BUTTON_PIN, 0);
PhysButton center_button = PhysButton(CENTER_BUTTON_PIN, 0);
PhysButton back_button = PhysButton(BACK_BUTTON_PIN, 0);
PhysButton command_button = PhysButton(COMMAND_BUTTON_PIN, 1);
PhysButton home_button = PhysButton(HOME_BUTTON_PIN, 1);

ButtonEvent btn_st_up;
ButtonEvent btn_st_down;
ButtonEvent btn_st_left;
ButtonEvent btn_st_right;
ButtonEvent btn_st_center;
ButtonEvent btn_st_back;
ButtonEvent btn_st_command;
ButtonEvent btn_st_home;
#pragma endregion

#pragma region Apps

SettingsApp settings_app;
NotepadApp notepad_app;
IRHub::IRHubApp ir_hub_app;
Minesweeper::MinesweeperApp minesweeper_app;

AbstractApp* app_array[] = { // надо бы const на всякий
	&settings_app,
	&notepad_app,
	&ir_hub_app,
	&minesweeper_app
};

#pragma endregion

void check_buttons()
{
	btn_st_up = up_button.check();
	btn_st_down = down_button.check();
	btn_st_left = left_button.check();
	btn_st_right = right_button.check();
	btn_st_center = center_button.check();
	btn_st_back = back_button.check();
	btn_st_command = command_button.check();
	btn_st_home = home_button.check();
}

void setup()
{
	Serial.begin(115200);
	Serial.setTimeout(50);
	// while (!Serial)
	//   ;
	// delay(200);
	pinMode(IR_SENDER_PIN, OUTPUT);

	// buttons manager setup
	Managers::PhysBtnManager::PBtnManager::setup();

	up_button.setup(); // ##########
	down_button.setup();
	left_button.setup();
	right_button.setup();
	center_button.setup();
	back_button.setup();
	command_button.setup();
	home_button.setup();

	// screen setup
	screen.initR(INITR_144GREENTAB);
	screen.setRotation(2);
	screen.fillScreen(MENU_BACKGROUND_COLOR);

	// sd manager setup
	Managers::SDManager::setup();

	// app manager start
	app_manager.start(app_array, sizeof(app_array) / sizeof(AbstractApp*));
}
void loop()
{
	check_buttons();
	app_manager.loop();
	Managers::PhysBtnManager::PBtnManager::loop();
}