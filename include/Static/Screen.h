#ifndef _SCREEN_H
#define _SCREEN_H

#include <Adafruit_ST7735.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 128

#pragma region TextSizes

#define SMALL_TEXT_SIZE 1
#define MIDDLE_TEXT_SIZE 2
#define BIG_TEXT_SIZE 3

// #define LINE_SPACING 1
// #define COLUMN_SPACING 1

#define GET_TEXT_WIDTH(text_size) \
    ((text_size) == (SMALL_TEXT_SIZE) ? 6 : ((text_size) == (MIDDLE_TEXT_SIZE) ? 12 : ((text_size) == (BIG_TEXT_SIZE) ? 18 : 0)))

#define GET_TEXT_HEIGHT(text_size) \
    ((text_size) == (SMALL_TEXT_SIZE) ? 8 : ((text_size) == (MIDDLE_TEXT_SIZE) ? 16 : ((text_size) == (BIG_TEXT_SIZE) ? 24 : 0)))

#define GET_MAX_TEXT_COLUMNS(text_size) (SCREEN_WIDTH / (GET_TEXT_WIDTH(text_size)))
#define GET_MAX_TEXT_LINES(text_size) (SCREEN_HEIGHT / (GET_TEXT_HEIGHT(text_size) ))

// #define GET_MAX_TEXT_LINES(text_size) \
//     ((text_size) == (SMALL_TEXT_SIZE) ? SCREEN_HEIGHT / (GET_TEXT_HEIGHT(SMALL_TEXT_SIZE) + LINE_SPACING) : ((text_size) == (MIDDLE_TEXT_SIZE) ? SCREEN_HEIGHT / (GET_TEXT_HEIGHT(SMALL_TEXT_SIZE) + LINE_SPACING) : ((text_size) == (BIG_TEXT_SIZE) ? SCREEN_HEIGHT / GET_TEXT_HEIGHT(BIG_TEXT_SIZE) : 0)))

#pragma endregion

#define SCREEN_BACKGROUND 0xa009

extern Adafruit_ST7735 screen;

#endif