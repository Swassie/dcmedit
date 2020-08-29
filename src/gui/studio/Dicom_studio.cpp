#include "gui/studio/Dicom_studio.h"

#include "gui/Dicom_view_factory.h"
#include "gui/Main_window.h"
#include "gui/View_manager.h"
#include "gui/menu/File_menu.h"
#include "gui/menu/Menu_bar.h"
#include "gui/menu/Tool_bar.h"
#include "gui/menu/View_menu.h"

static std::unique_ptr<Tool_bar> create_tool_bar(View_manager& view_manager) {
    auto tool_bar = std::make_unique<Tool_bar>();
    tool_bar->add_default_layout(view_manager);
    tool_bar->add_pan();
    tool_bar->add_zoom();
    return tool_bar;
}

static std::unique_ptr<Menu_bar> create_menu_bar(Main_window& main_window,
                                                 View_manager& view_manager) {
    auto menu_bar = std::make_unique<Menu_bar>();

    auto file_menu = std::make_unique<File_menu>();
    file_menu->add_open_file(main_window);
    menu_bar->add_menu(std::move(file_menu));

    auto view_menu = std::make_unique<View_menu>();
    view_menu->add_view_counts(view_manager);
    menu_bar->add_menu(std::move(view_menu));

    return menu_bar;
}

Dicom_studio::Dicom_studio(Main_window& main_window, DcmFileFormat& dicom_file) {
    auto view_manager = std::make_unique<View_manager>();
    m_tool_bar = create_tool_bar(*view_manager);

    m_element_model = std::make_unique<Data_element_model>(dicom_file);
    auto view_factory = std::make_unique<Dicom_view_factory>(dicom_file,
                                                             *m_tool_bar,
                                                             *m_element_model,
                                                             *view_manager);

    view_manager->set_view_factory(std::move(view_factory));
    view_manager->show_default_layout();

    m_menu_bar = create_menu_bar(main_window, *view_manager);
    m_central_widget = std::move(view_manager);
}