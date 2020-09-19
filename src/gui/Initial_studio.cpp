#include "gui/Initial_studio.h"

#include "gui/Main_window.h"
#include "gui/Initial_view.h"
#include "gui/menu/File_menu.h"
#include "gui/menu/Menu_bar.h"

static std::unique_ptr<Menu_bar> create_menu_bar(Main_window& main_window) {
    auto menu_bar = std::make_unique<Menu_bar>();

    auto file_menu = std::make_unique<File_menu>();
    file_menu->add_open_file(main_window);
    menu_bar->add_menu(std::move(file_menu));

    return menu_bar;
}

Initial_studio::Initial_studio(Main_window& main_window) {
    m_menu_bar = create_menu_bar(main_window);
    m_central_widget = std::make_unique<Initial_view>(main_window);
}
