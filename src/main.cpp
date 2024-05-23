// при скобках "" сначала просматриваются локальные файлы, а при <> сначала просматриваются глобальные
#include <Arduino.h>
#include <vector>
#include <SPI.h>
#include <Adafruit_GFX.h>
#include <Adafruit_ST7735.h>

#include "Static/Pins.h"
#include "Static/Bitmaps.h"
#include "Static/IRreceiver.h"
#include "PhysButton.h"
#include "Managers/AppManager.h"
#include "Managers/SDManager.h"

#include "Apps/AbstractApp.h"
#include "Apps/SettingsApp/SettingsApp.h"
#include "Apps/NotepadApp/NotepadApp.h"
#include "Apps/IRHubApp/IRHubApp.h"

#include <esp32-hal-matrix.h>

IRrecv *ir_receiver_ptr;
Adafruit_ST7735 screen(TFT_CS, TFT_DC, TFT_RST);
Managers::AppManager app_manager;

#pragma region Buttons
PhysButton up_button = PhysButton(UP_BUTTON_PIN);
PhysButton down_button = PhysButton(DOWN_BUTTON_PIN);
PhysButton left_button = PhysButton(LEFT_BUTTON_PIN);
PhysButton right_button = PhysButton(RIGHT_BUTTON_PIN);
PhysButton center_button = PhysButton(CENTER_BUTTON_PIN);
PhysButton back_button = PhysButton(BACK_BUTTON_PIN);

ButtonEvent btn_st_up;
ButtonEvent btn_st_down;
ButtonEvent btn_st_left;
ButtonEvent btn_st_right;
ButtonEvent btn_st_center;
ButtonEvent btn_st_back;
#pragma endregion

#pragma region Apps

SettingsApp settings_app;
NotepadApp notepad_app;
IRHub::IRHubApp ir_hub_app;

AbstractApp *app_array[] = {
    &settings_app,
    &notepad_app,
    &ir_hub_app};

#pragma endregion

void check_buttons()
{
  btn_st_up = up_button.check();
  btn_st_down = down_button.check();
  btn_st_left = left_button.check();
  btn_st_right = right_button.check();
  btn_st_center = center_button.check();
  btn_st_back = back_button.check();
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
  check_buttons();
  app_manager.loop();
}