#include "gui/Test_studio.h"

#include "gui/Common_actions.h"
#include "gui/Test_view_factory.h"
#include "gui/Main_window.h"
#include "gui/Tool_bar.h"
#include "gui/Workspace_view.h"

static std::unique_ptr<QMenuBar> create_menu_bar(Main_window& main_window,
                                                 Workspace_view& workspace_view) {
    auto menu_bar = std::make_unique<QMenuBar>();

    QMenu* file_menu = Common_actions::add_file_menu(*menu_bar);
    Common_actions::add_open_file(*file_menu, main_window);

    QMenu* view_menu = Common_actions::add_view_menu(*menu_bar);
    Common_actions::add_view_counts(*view_menu, workspace_view);

    QMenu* studio_menu = Common_actions::add_studio_menu(*menu_bar);
    Common_actions::add_studios(*studio_menu, main_window, Common_actions::Studio::test);

    QMenu* extra_features_menu = menu_bar->addMenu("&Extra features");
    extra_features_menu->addAction("Feature 1", [] {});
    extra_features_menu->addAction("Feature 2", [] {});

    return menu_bar;
}

Test_studio::Test_studio(Main_window& main_window, DcmFileFormat& dicom_file) {
    auto workspace_view = std::make_unique<Workspace_view>();
    auto tool_bar = std::make_unique<Tool_bar>(*workspace_view);

    m_element_model = std::make_unique<Data_element_model>(dicom_file);
    auto view_factory = std::make_unique<Test_view_factory>(dicom_file,
                                                            *tool_bar,
                                                            *m_element_model,
                                                            *workspace_view);

    workspace_view->set_view_factory(std::move(view_factory));
    workspace_view->show_default_layout();

    m_menu_bar = create_menu_bar(main_window, *workspace_view);
    m_tool_bar = std::move(tool_bar);
    m_central_widget = std::move(workspace_view);
}
