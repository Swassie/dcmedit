#include "gui/studio/Start_studio.h"

#include "gui/Gui_util.h"
#include "gui/Main_window.h"
#include "gui/menu/Menu.h"
#include "gui/Start_screen.h"

#include <QCoreApplication>

Start_studio::Start_studio(Main_window& main_window)
    : m_main_window(main_window) {
    auto start_screen = new Start_screen(*this);

    main_window.setMenuBar(create_menu_bar().release());
    main_window.setCentralWidget(start_screen);
    main_window.setWindowModified(false);
    main_window.setWindowTitle(QCoreApplication::applicationName());
}

void Start_studio::open_files() {
    auto files = Gui_util::load_files(&m_main_window);
    if(files.empty()) {
        return;
    }
    m_main_window.setup_dicom_studio(std::move(files));
}

std::unique_ptr<QMenuBar> Start_studio::create_menu_bar() {
    auto menu_bar = std::make_unique<QMenuBar>();

    auto file_menu = new Menu(menu_bar.get());
    file_menu->set_title_file();
    file_menu->add_open_files(*this);
    file_menu->add_quit(m_main_window);
    menu_bar->addMenu(file_menu);

    auto help_menu = new Menu(menu_bar.get());
    help_menu->set_title_help();
    help_menu->add_about(m_main_window);
    menu_bar->addMenu(help_menu);

    return menu_bar;
}
