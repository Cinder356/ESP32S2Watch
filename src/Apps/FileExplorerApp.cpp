#include "Apps/FileExplorerApp.h"

namespace Apps
{
    FileExplorer::FileExplorer(Adafruit_ST7735 &screen_ref) : _screen_ref(screen_ref) {}

    void FileExplorer::start() {}
    void FileExplorer::close() {}
    void FileExplorer::update(ButtonEvents button_events) {}
    uint16_t *FileExplorer::get_icon() const { return Managers::SDManager::read_bin_image(FILE_EXPLORER_ICON_PATH); }
}