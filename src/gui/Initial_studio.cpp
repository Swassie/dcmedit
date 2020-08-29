#include "gui/Initial_studio.h"

#include "gui/Main_window.h"
#include "gui/Initial_view.h"

static std::unique_ptr<QMenuBar> create_menu_bar(Main_window& main_window) {
    auto menu_bar = std::make_unique<QMenuBar>();

    QMenu* file_menu = menu_bar->addMenu("&File");
    file_menu->addAction("Open...", &main_window, &Main_window::open_file,
                         QKeySequence("Ctrl+O"));

    return menu_bar;
}

Initial_studio::Initial_studio(Main_window& main_window) {
    m_menu_bar = create_menu_bar(main_window);
    m_central_widget = std::make_unique<Initial_view>(main_window);
}
