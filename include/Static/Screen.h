#ifndef _SCREEN_H
#define _SCREEN_H

#include <Adafruit_ST7735.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 128

#pragma region TextSizes

#define TEXT_SPACING 1

#define SMALL_TEXT_SIZE 1
#define MIDDLE_TEXT_SIZE 2
#define BIG_TEXT_SIZE 3

#define GET_TEXT_WIDTH(text_size) \
    ((text_size) == (SMALL_TEXT_SIZE) ? 6 : ((text_size) == (MIDDLE_TEXT_SIZE) ? 12 : ((text_size) == (BIG_TEXT_SIZE) ? 18 : 0)))

#define GET_TEXT_HEIGHT(text_size) \
    ((text_size) == (SMALL_TEXT_SIZE) ? 8 : ((text_size) == (MIDDLE_TEXT_SIZE) ? 16 : ((text_size) == (BIG_TEXT_SIZE) ? 24 : 0)))

#define GET_MAX_TEXT_COLUMNS(text_size) (SCREEN_WIDTH / (GET_TEXT_WIDTH(text_size)))
#define GET_MAX_TEXT_LINES(text_size) (SCREEN_HEIGHT / (GET_TEXT_HEIGHT(text_size) ))
// #define GET_CHAR_WIDTH(text_size) (GET_TEXT_WIDTH(text_size) - TEXT_SPACING)
// #define GET_CHAR_HEIGHT(text_size) (GET_TEXT_HEIGHT(text_size) - TEXT_SPACING)


#pragma endregion


extern Adafruit_ST7735 screen;


// void draw_rotated_img(uint8_t s_x, uint8_t s_y, uint16_t *img, uint8_t w, uint8_t h, int16_t rotate_degree)
// {
//   const float radian = rotate_degree * PI / 180;

//   const int16_t half_w = w / 2;
//   const int16_t half_h = h / 2;

//   const float r_sin = sin(radian);
//   const float r_cos = cos(radian);

//   float transformation[] = {r_cos, -r_sin,
//                             r_sin, r_cos};

//   uint16_t i = 0;
//   for (int16_t column = 0; column < h; column++)
//   {
//     for (int16_t row = 0; row < w; row++)
//     {
//       int16_t in_x = row - half_w;
//       int16_t in_y = column - half_h;

//       int16_t out_x = in_x * transformation[0] + in_y * transformation[1];
//       int16_t out_y = in_x * transformation[2] + in_y * transformation[3];

//       screen.drawPixel(s_x + out_x + half_w, s_y + out_y + half_h, img[i]);
//       i++;
//     }
//   }
// }

#endif