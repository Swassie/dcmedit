#include "gui/studio/Dicom_studio.h"

#include "gui/View_factory.h"
#include "gui/Main_window.h"
#include "gui/View_manager.h"
#include "gui/menu/Menu.h"
#include "gui/menu/Tool_bar.h"

static std::unique_ptr<QMenuBar> create_menu_bar(Main_window& main_window,
                                                 View_manager& view_manager) {
    auto menu_bar = std::make_unique<QMenuBar>();

    auto file_menu = new Menu(menu_bar.get());
    file_menu->set_title_file();
    file_menu->add_open_file(main_window);
    file_menu->add_save_file(main_window);
    file_menu->add_save_file_as(main_window);
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

Dicom_studio::Dicom_studio(Main_window& main_window, DcmDataset& dataset) {
    auto view_manager = std::make_unique<View_manager>();
    m_tool_bar = std::make_unique<Tool_bar>(*view_manager);

    auto view_factory = std::make_unique<View_factory>(dataset,
                                                       *m_tool_bar,
                                                       *view_manager);

    view_manager->set_view_factory(std::move(view_factory));
    view_manager->show_default_layout();

    m_menu_bar = create_menu_bar(main_window, *view_manager);
    m_central_widget = std::move(view_manager);
}
