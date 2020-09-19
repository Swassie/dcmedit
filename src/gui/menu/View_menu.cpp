#include "gui/menu/View_menu.h"

#include "gui/View_manager.h"

View_menu::View_menu() {
    setTitle("&View");
}

void View_menu::add_view_counts(View_manager& view_manager) {
    addAction("1 view", [&view_manager] {
        view_manager.set_view_count(1);
    }, QKeySequence("Ctrl+1"));

    addAction("2 views", [&view_manager] {
        view_manager.set_view_count(2);
    }, QKeySequence("Ctrl+2"));

    addAction("3 views", [&view_manager] {
        view_manager.set_view_count(3);
    }, QKeySequence("Ctrl+3"));

    addAction("4 views", [&view_manager] {
        view_manager.set_view_count(4);
    }, QKeySequence("Ctrl+4"));
}
