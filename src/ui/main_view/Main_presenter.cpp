#include "ui/main_view/Main_presenter.h"

#include "common/App_info.h"
#include "models/Dicom_files.h"
#include "ui/edit_all_files_dialog/Edit_all_files_presenter.h"
#include "ui/edit_all_files_dialog/IEdit_all_files_view.h"
#include "ui/main_view/IMain_view.h"
#include "ui/new_file_dialog/INew_file_view.h"
#include "ui/new_file_dialog/New_file_presenter.h"
#include "ui/open_files_dialog/IOpen_files_view.h"
#include "ui/open_files_dialog/Open_files_presenter.h"
#include "ui/open_folder_dialog/Open_folder_presenter.h"

#include <QCoreApplication>
#include <memory>

Main_presenter::Main_presenter(IMain_view& view)
    : m_view(view),
      m_dataset_model(m_files),
      m_file_tree_model(m_files),
      m_split_presenter(m_view.get_split_view(), m_dataset_model, m_tool_bar),
      m_file_tree_presenter(m_view.get_file_tree_view(), m_file_tree_model) {
    set_startup_view();
    m_split_presenter.set_default_layout();
    setup_event_callbacks();
}

void Main_presenter::setup_event_callbacks() {
    m_view.new_file_clicked.add_callback([this] {new_file();});
    m_view.open_files_clicked.add_callback([this] {open_files();});
    m_view.open_folder_clicked.add_callback([this] {open_folder();});
    m_view.save_file_clicked.add_callback([this] {save_file();});
    m_view.save_file_as_clicked.add_callback([this] {save_file_as();});
    m_view.save_all_files_clicked.add_callback([this] {save_all_files();});
    m_view.clear_all_files_clicked.add_callback([this] {clear_all_files();});
    m_view.quit_clicked.add_callback([this] {quit();});
    m_view.edit_all_files_clicked.add_callback([this] {edit_all_files();});
    m_view.about_clicked.add_callback([this] {about();});
    m_view.set_view_count_clicked.add_callback([this] (int count) {m_split_presenter.set_view_count(count);});
    m_view.reset_layout_clicked.add_callback([this] {m_split_presenter.set_default_layout();});
    m_view.pan_tool_selected.add_callback([this] {m_tool_bar.set_selected_tool(Tool_bar::pan);});
    m_view.zoom_tool_selected.add_callback([this] {m_tool_bar.set_selected_tool(Tool_bar::zoom);});
    m_files.file_saved.add_callback([this] {update_window_title();});
    m_file_tree_presenter.file_activated.add_callback([this] (Dicom_file* file) {m_files.set_current_file(file);});
    m_dataset_model.dataset_changed.add_callback([this] {on_dataset_changed();});
}

void Main_presenter::on_dataset_changed() {
    m_file_tree_model.update_model();
    if(m_state == Presenter_state::startup) {
        set_editor_view();
    }
    else if(m_files.get_current_file() == nullptr) {
        set_startup_view();
    }
    else {
        update_window_title();
    }
}

void Main_presenter::set_startup_view() {
    m_state = Presenter_state::startup;
    update_window_title();
    m_view.set_startup_view();
}

void Main_presenter::set_editor_view() {
    m_state = Presenter_state::editor;
    update_window_title();
    m_view.set_editor_view();
}

void Main_presenter::open_files() {
    std::unique_ptr<IOpen_files_view> view = m_view.create_open_files_view();
    Open_files_presenter presenter(*view, m_files);
    presenter.show_dialog();
}

void Main_presenter::open_folder() {
    std::unique_ptr<IOpen_folder_view> view = m_view.create_open_folder_view();
    Open_folder_presenter presenter(*view, m_files);
    presenter.show_dialog();
}

void Main_presenter::new_file() {
    std::unique_ptr<INew_file_view> view = m_view.create_new_file_view();
    New_file_presenter presenter(*view, m_files);
    presenter.show_dialog();
}

void Main_presenter::save_file() {
    Dicom_file* file = m_files.get_current_file();
    save_file_as(file->get_path());
}

void Main_presenter::save_file_as() {
    fs::path file_path = m_view.show_save_file_dialog();

    if (!file_path.empty()) {
        save_file_as(file_path);
    }
}

void Main_presenter::save_file_as(const fs::path& path) {
    try {
        m_files.save_current_file_as(path);
    }
    catch(const std::exception& e) {
        m_view.show_error("Error", "Failed to save file: " + path.string() +
            "\nReason: " + std::string(e.what()));
    }
}

void Main_presenter::save_all_files() {
    bool ok = m_files.save_all_files();

    if(!ok) {
        m_view.show_error("Error", "At least one file failed to save.");
    }
}

void Main_presenter::clear_all_files() {
    if(m_files.has_unsaved_changes() && !m_view.show_discard_dialog()) {
        return;
    }
    m_files.clear_all_files();
}

void Main_presenter::quit() {
    if(m_files.has_unsaved_changes() && !m_view.show_discard_dialog()) {
        return;
    }
    QCoreApplication::quit();
}

void Main_presenter::edit_all_files() {
    std::unique_ptr<IEdit_all_files_view> view = m_view.create_edit_all_files_view();
    Edit_all_files_presenter presenter(*view, m_files);
    presenter.show_dialog();
}

void Main_presenter::about() {
    m_view.show_about_dialog();
}

void Main_presenter::update_window_title() {
    if(m_state == Presenter_state::startup) {
        m_view.set_window_modified(false);
        m_view.set_window_title(App_info::name);
    }
    else {
        Dicom_file* file = m_files.get_current_file();
        if(!file) {
            return;
        }
        m_view.set_window_modified(file->has_unsaved_changes());

        std::string title = file->get_path().string() + "[*] - " + App_info::name;
        m_view.set_window_title(title);
    }
}
