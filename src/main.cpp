// при скобках "" сначала просматриваются локальные файлы, а при <> сначала просматриваются глобальные
#include <Arduino.h>
#include <vector>
#include <SPI.h>
#include <Adafruit_GFX.h>
#include <Adafruit_ST7735.h>

#include "Static/Pins.h"
#include "Static/Bitmaps.h"
#include "Button.h"
#include "Managers/AppManager.h"
#include "Managers/SDManager.h"

#include "Apps/AbstractApp.h"
#include "Apps/SettingsApp.h"
#include "Apps/NotepadApp.h"
#include "Apps/IRHubApp.h"

Adafruit_ST7735 screen(TFT_CS, TFT_DC, TFT_RST);
Managers::AppManager app_manager;

#pragma region Buttons
Button up_button = Button(UP_BUTTON_PIN);
Button down_button = Button(DOWN_BUTTON_PIN);
Button left_button = Button(LEFT_BUTTON_PIN);
Button right_button = Button(RIGHT_BUTTON_PIN);
Button center_button = Button(CENTER_BUTTON_PIN);
Button back_button = Button(BACK_BUTTON_PIN);
#pragma endregion

#pragma region Apps

SettingsApp settings_app;
NotepadApp notepad_app;
IRHubApp ir_hub_app;

AbstractApp *app_array[] = {
    &settings_app,
    &notepad_app,
    &ir_hub_app};

#pragma endregion

ButtonEvents check_buttons()
{
  return {
      up_button.check(),
      down_button.check(),
      left_button.check(),
      right_button.check(),
      center_button.check(),
      back_button.check()};
  // return ButtonEvents(
  //   up_button.check(),
  //   down_button.check(),
  //   left_button.check(),
  //   right_button.check(),
  //   center_button.check(),
  //   back_button.check()
  // );
}

void setup()
{
  Serial.begin(115200);

  // buttons setup
  up_button.setup();
  down_button.setup();
  left_button.setup();
  right_button.setup();
  center_button.setup();
  back_button.setup();

  // screen setup
  screen.initR(INITR_144GREENTAB);
  screen.setRotation(2);
  screen.fillScreen(MENU_BACKGROUND_COLOR);

  // sd manager setup
  Managers::SDManager::setup();

  // app manager start
  app_manager.start(app_array, sizeof(app_array) / sizeof(AbstractApp *));
}

void loop()
{
  ButtonEvents button_events = check_buttons();
  app_manager.loop(button_events);
}