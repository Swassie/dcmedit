#include "gui/menu/File_menu.h"

#include "gui/Main_window.h"

File_menu::File_menu() {
    setTitle("&File");
}

void File_menu::add_open_file(Main_window& main_window) {
    addAction("Open...", &main_window, &Main_window::open_file, QKeySequence::Open);
}
