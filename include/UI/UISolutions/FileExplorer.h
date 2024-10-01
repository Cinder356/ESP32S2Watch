#ifndef _FILE_EXPLORER_HSMALL_TEXT_SIZE
#define _FILE_EXPLORER_H

#include "Static/Screen.h"
#include "Managers/SDManager.h"
#include "Static/SDPaths.h"
#include "PhysButton.h"

#define FE_BACKGROUND 0xa00f
#define FE_CURSOR_COLOR 0xffaf
#define FE_TEXT_COLOR 0xffff
#define FE_LEFT_TEXT_MARGIN 5
#define FE_TEXT_SIZE SMALL_TEXT_SIZE
#define FE_PERMANENT_LABELS_QUANTITY 1
#define FE_MAX_FILENAMES_QUANTITY (GET_MAX_TEXT_LINES(FE_TEXT_SIZE) - FE_PERMANENT_LABELS_QUANTITY)

namespace UI::UISolutions
{
    class FileExplorer
    {
        private:
            String _current_dir;
            uint8_t _current_dir_files_amount;
            uint8_t _current_page = 0;
            uint8_t _cursor = 0;
            
            void change_dir(String path);
            void draw_cursor(uint16_t color);
            void draw_page();
        public:
            void start(String start_dir = BASE_DIR);
            // @brief On finding file returns full path. You must clear memory after path use!
            const char* loop();
    };
}

#endif  