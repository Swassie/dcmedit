#include "gui/menu/Help_menu.h"

#include "gui/About_dialog.h"
#include "gui/Main_window.h"

Help_menu::Help_menu() {
    setTitle("&Help");
}

void Help_menu::add_about(Main_window& main_window) {
    addAction("About", [&main_window] {
        About_dialog dialog(&main_window);
        dialog.exec();
    });
}
