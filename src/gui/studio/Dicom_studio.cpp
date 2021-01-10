#include "gui/studio/Dicom_studio.h"

#include "Dicom_file.h"
#include "gui/View_factory.h"
#include "gui/Main_window.h"
#include "gui/View_manager.h"
#include "gui/menu/Menu.h"
#include "gui/menu/Tool_bar.h"

#include <QMenuBar>

static std::unique_ptr<QMenuBar> create_menu_bar(Main_window& main_window,
                                                 View_manager& view_manager) {
    auto menu_bar = std::make_unique<QMenuBar>();

    auto file_menu = new Menu(menu_bar.get());
    file_menu->set_title_file();
    file_menu->add_open_file(main_window);
    file_menu->add_save_file(main_window);
    file_menu->add_save_file_as(main_window);
    file_menu->add_quit(main_window);
    menu_bar->addMenu(file_menu);

    auto view_menu = new Menu(menu_bar.get());
    view_menu->set_title_view();
    view_menu->add_view_counts(view_manager);
    menu_bar->addMenu(view_menu);

    auto help_menu = new Menu(menu_bar.get());
    help_menu->set_title_help();
    help_menu->add_about(main_window);
    menu_bar->addMenu(help_menu);

    return menu_bar;
}

Dicom_studio::Dicom_studio(Main_window& main_window, Dicom_file& file)
    : m_main_window(main_window),
      m_file(file) {
    m_view_manager = new View_manager();
    m_tool_bar = std::make_unique<Tool_bar>(*m_view_manager);

    auto view_factory = std::make_unique<View_factory>(m_file.get_dataset(), *m_tool_bar,
                                                       *m_view_manager, *this);

    m_view_manager->set_view_factory(std::move(view_factory));
    m_view_manager->show_default_layout();

    std::unique_ptr<QMenuBar> menu_bar = create_menu_bar(main_window, *m_view_manager);

    m_main_window.setMenuBar(menu_bar.release());
    m_main_window.addToolBar(m_tool_bar.get());
    m_main_window.setCentralWidget(m_view_manager);
}

void Dicom_studio::file_was_modified() {
    m_file.set_unsaved_changes(true);
    m_main_window.setWindowModified(true);
    m_view_manager->update_content_in_views();
}
