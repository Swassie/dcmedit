#include "dcmedit.h"

#include "logging/Log.h"
#include "models/Dataset_model.h"
#include "models/Dicom_files.h"
#include "models/File_tree_model.h"
#include "models/Tool_bar.h"
#include "ui/View_factory.h"
#include "ui/dashboard_view/Dashboard_view.h"
#include "ui/file_tree_view/File_tree_view.h"
#include "ui/main_view/Main_presenter.h"
#include "ui/main_view/Main_view.h"
#include "ui/split_view/Split_presenter.h"
#include "ui/split_view/Split_view.h"

#include <QApplication>

int dcmedit::run(int argc, char** argv) {
    QApplication app(argc, argv);
    app.setApplicationName("dcmedit");

    Dicom_files dicom_files;
    Tool_bar tool_bar;
    Dataset_model dataset_model(dicom_files);
    dataset_model.setup_event_handlers();
    File_tree_model file_tree_model(dicom_files);
    file_tree_model.setup_event_handlers();

    // Setup GUI.
    auto dashboard_view = new Dashboard_view();

    View_factory view_factory(dataset_model, tool_bar);

    auto split_view = new Split_view();
    Split_presenter split_presenter(*split_view, view_factory);
    split_presenter.set_default_layout();

    auto file_tree_view = new File_tree_view(file_tree_model);

    Main_view main_view{std::unique_ptr<Dashboard_view>(dashboard_view),
        std::unique_ptr<Split_view>(split_view),
        std::unique_ptr<File_tree_view>(file_tree_view)};
    Main_presenter main_presenter(main_view, dicom_files);
    main_presenter.setup_event_handlers();
    main_presenter.show_dashboard_view();

    // Add event handlers.
    file_tree_view->file_activated += [&] (Dicom_file* file) {dicom_files.set_current_file(file);};
    dataset_model.dataset_changed += [&] {file_tree_model.update_model();};
    dataset_model.dataset_changed += [&] {main_presenter.update_window_title();};
    main_view.set_view_count_clicked += [&] (int count) {split_presenter.set_view_count(count);};
    main_view.reset_layout_clicked += [&] {split_presenter.set_default_layout();};
    main_view.pan_tool_selected += [&] {tool_bar.set_selected_tool(Tool_bar::pan);};
    main_view.zoom_tool_selected += [&] {tool_bar.set_selected_tool(Tool_bar::zoom);};

    main_view.show();

    return app.exec();
}
