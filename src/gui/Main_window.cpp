#include "Main_window.h"
#include <QMenuBar>
#include "View_area.h"

Main_window::Main_window() {
    setMinimumSize(QSize(800, 600));
}

void Main_window::setup_workspace() {
    View_area* view_area = new View_area;
    QMenu* view_menu = menuBar()->addMenu("&View");

    view_menu->addAction("1 view", [view_area] {
        view_area->set_view_count(1);
    }, QKeySequence("Ctrl+1"));

    view_menu->addAction("2 views", [view_area] {
        view_area->set_view_count(2);
    }, QKeySequence("Ctrl+2"));

    view_menu->addAction("3 views", [view_area] {
        view_area->set_view_count(3);
    }, QKeySequence("Ctrl+3"));

    view_menu->addAction("4 views", [view_area] {
        view_area->set_view_count(4);
    }, QKeySequence("Ctrl+4"));

    view_menu->addAction("5 views", [view_area] {
        view_area->set_view_count(5);
    }, QKeySequence("Ctrl+5"));

    view_menu->addAction("6 views", [view_area] {
        view_area->set_view_count(6);
    }, QKeySequence("Ctrl+6"));

    setCentralWidget(view_area);
}
