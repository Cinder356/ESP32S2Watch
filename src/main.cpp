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

Adafruit_ST7735 screen = Adafruit_ST7735(TFT_CS, TFT_DC, TFT_RST);

#pragma region Buttons
Button up_button = Button(UP_BUTTON_PIN);
Button down_button = Button(DOWN_BUTTON_PIN);
Button left_button = Button(LEFT_BUTTON_PIN);
Button right_button = Button(RIGHT_BUTTON_PIN);
Button center_button = Button(CENTER_BUTTON_PIN);
Button back_button = Button(BACK_BUTTON_PIN);
#pragma endregion

#pragma region Apps

SettingsApp settings_app(screen);
NotepadApp notepad_app(screen);

AbstractApp *app_array[] =
    {
        &settings_app,
        &notepad_app
    };

#pragma endregion

Managers::AppManager app_manager(app_array, sizeof(app_array) / sizeof(AbstractApp *), screen);

ButtonEvents check_buttons()
{
  return {
    up_button.check(),
    down_button.check(),
    left_button.check(),
    right_button.check(),
    center_button.check(),
    back_button.check()
  };
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
  // while(!Serial);

  // buttons setup
  up_button.setup();
  down_button.setup();
  left_button.setup();
  right_button.setup();
  center_button.setup();
  back_button.setup();

  // sd manager setup
  Managers::SDManager::setup();

  // screen setup
  screen.initR(INITR_144GREENTAB);
  screen.setRotation(2);
  screen.fillScreen(MENU_BACKGROUND_COLOR);

  // app manager start
  app_manager.start();
}

void loop()
{
  ButtonEvents button_events = check_buttons();
  app_manager.loop(button_events);
}