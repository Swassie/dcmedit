#include "gui/Menu_bar.h"

#include "gui/Main_window.h"
#include "gui/Workspace_view.h"

#include <QMenuBar>

void Menu_bar::create_file_menu(Main_window& main_window) {
    QMenu* file_menu = main_window.menuBar()->addMenu("&File");

    file_menu->addAction("Open...", &main_window, &Main_window::open_file,
                         QKeySequence("Ctrl+O"));
}

void Menu_bar::create_view_menu(Main_window& main_window, Workspace_view& workspace_view) {
    QMenu* view_menu = main_window.menuBar()->addMenu("&View");

    view_menu->addAction("1 view", [&workspace_view] {
        workspace_view.set_view_count(1);
    }, QKeySequence("Ctrl+1"));

    view_menu->addAction("2 views", [&workspace_view] {
        workspace_view.set_view_count(2);
    }, QKeySequence("Ctrl+2"));

    view_menu->addAction("3 views", [&workspace_view] {
        workspace_view.set_view_count(3);
    }, QKeySequence("Ctrl+3"));

    view_menu->addAction("4 views", [&workspace_view] {
        workspace_view.set_view_count(4);
    }, QKeySequence("Ctrl+4"));

    view_menu->addAction("5 views", [&workspace_view] {
        workspace_view.set_view_count(5);
    }, QKeySequence("Ctrl+5"));

    view_menu->addAction("6 views", [&workspace_view] {
        workspace_view.set_view_count(6);
    }, QKeySequence("Ctrl+6"));
}
