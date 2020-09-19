#include "gui/studio/Start_studio.h"

#include "gui/Main_window.h"
#include "gui/Start_screen.h"
#include "gui/menu/File_menu.h"
#include "gui/menu/Menu_bar.h"

static std::unique_ptr<Menu_bar> create_menu_bar(Main_window& main_window) {
    auto menu_bar = std::make_unique<Menu_bar>();

    auto file_menu = std::make_unique<File_menu>();
    file_menu->add_open_file(main_window);
    menu_bar->add_menu(std::move(file_menu));

    return menu_bar;
}

Start_studio::Start_studio(Main_window& main_window) {
    m_menu_bar = create_menu_bar(main_window);
    m_central_widget = std::make_unique<Start_screen>(main_window);
}
