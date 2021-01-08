#include "gui/studio/Start_studio.h"

#include "gui/Main_window.h"
#include "gui/Start_screen.h"
#include "gui/menu/Menu.h"

static std::unique_ptr<QMenuBar> create_menu_bar(Main_window& main_window) {
    auto menu_bar = std::make_unique<QMenuBar>();

    auto file_menu = new Menu(menu_bar.get());
    file_menu->set_title_file();
    file_menu->add_open_file(main_window);
    menu_bar->addMenu(file_menu);

    auto help_menu = new Menu(menu_bar.get());
    help_menu->set_title_help();
    help_menu->add_about(main_window);
    menu_bar->addMenu(help_menu);

    return menu_bar;
}

Start_studio::Start_studio(Main_window& main_window) {
    m_menu_bar = create_menu_bar(main_window);
    m_central_widget = std::make_unique<Start_screen>(main_window);
}
