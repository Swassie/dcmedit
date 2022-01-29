#include "dcmedit.h"

#include "logging/Log.h"
#include "models/Dataset_model.h"
#include "models/Dicom_files.h"
#include "models/File_tree_model.h"
#include "models/Tool_bar.h"
#include "presenters/Main_presenter.h"
#include "presenters/Open_files_presenter.h"
#include "presenters/Split_presenter.h"
#include "views/About_view.h"
#include "views/Dashboard_view.h"
#include "views/File_tree_view.h"
#include "views/Main_view.h"
#include "views/Open_files_view.h"
#include "views/Split_view.h"
#include "views/View_factory.h"

#include <QApplication>

int dcmedit::run(int argc, char** argv) {
    QApplication app(argc, argv);
    app.setApplicationName("dcmedit");

    Dicom_files dicom_files;
    Tool_bar tool_bar;
    Dataset_model dataset_model(dicom_files);
    dataset_model.setup_event_handlers();
    File_tree_model file_tree_model(dicom_files);
    file_tree_model.setup_event_handlers(dataset_model);

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
    Main_presenter main_presenter(main_view, dicom_files, dataset_model);
    main_presenter.setup_event_handlers();
    main_presenter.show_dashboard_view();

    Open_files_view open_files_view(&main_view);
    Open_files_presenter open_files_presenter(open_files_view, dicom_files);

    About_view about_view(&main_view);

    // Add event handlers.
    dashboard_view->open_files_clicked += [&] {open_files_presenter.open_files();};
    file_tree_view->file_activated += [&] (Dicom_file* file) {dicom_files.set_current_file(file);};
    main_view.open_files_clicked += [&] {open_files_presenter.open_files();};
    main_view.set_view_count_clicked += [&] (int count) {split_presenter.set_view_count(count);};
    main_view.about_clicked += [&] {about_view.show_about_dialog();};
    main_view.reset_layout_clicked += [&] {split_presenter.set_default_layout();};
    main_view.pan_tool_selected += [&] {tool_bar.set_selected_tool(Tool_bar::Tool::pan);};
    main_view.zoom_tool_selected += [&] {tool_bar.set_selected_tool(Tool_bar::Tool::zoom);};

    main_view.show();

    return app.exec();
}
