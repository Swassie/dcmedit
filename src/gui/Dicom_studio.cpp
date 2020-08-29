#include "gui/Dicom_studio.h"

#include "gui/Main_window.h"
#include "gui/Tool_bar.h"
#include "gui/View_factory.h"
#include "gui/Workspace_view.h"

static std::unique_ptr<QMenuBar> create_menu_bar(Main_window& main_window,
                                                 Workspace_view& workspace_view) {
    auto menu_bar = std::make_unique<QMenuBar>();

    QMenu* file_menu = menu_bar->addMenu("&File");
    file_menu->addAction("Open...", &main_window, &Main_window::open_file,
                         QKeySequence("Ctrl+O"));

    QMenu* view_menu = menu_bar->addMenu("&View");
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

    return menu_bar;
}

Dicom_studio::Dicom_studio(Main_window& main_window, DcmFileFormat& dicom_file) {
    auto tool_bar = std::make_unique<Tool_bar>();

    m_element_model = std::make_unique<Data_element_model>(dicom_file);
    auto view_factory = std::make_unique<View_factory>(dicom_file,
                                                       *tool_bar,
                                                       *m_element_model);
    auto workspace_view = std::make_unique<Workspace_view>(std::move(view_factory));
    tool_bar->set_workspace_view(workspace_view.get());

    m_menu_bar = create_menu_bar(main_window, *workspace_view.get());
    m_tool_bar = std::move(tool_bar);
    m_central_widget = std::move(workspace_view);
}
