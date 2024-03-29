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
}

// void animation_start()
// {
//   screen.fillScreen(0x0000);
//   uint16_t *img = Managers::SDManager::read_bin_image("/BaseDir/BinImages/h.bin");

//   const uint8_t s_x = 15;
//   const uint8_t s_y = 15;
//   const uint8_t w = 64;
//   const uint8_t h = 64;
//   // const float rotate_degree = 40;

//   uint16_t degree = 0;
//   while(1)
//   {
//     degree += 5;
//     if (degree >= 360)
//       degree = 0;
//     screen.fillScreen(0x0000);
//     screen.setCursor(100, 100);
//     screen.print(degree);
//     screen.setCursor(screen.getCursorX(), 95);
//     screen.print("o");

//     draw_rotated_img(s_x, s_y, img, w, h, degree);
//     delay(40);
//   }

//   delete[] img;
// }

void setup()
{
  Serial.begin(115200);
  // while (!Serial)
  //   ;
  // delay(200);

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