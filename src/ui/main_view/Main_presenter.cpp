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

#include <QCoreApplication>
#include <memory>

Main_presenter::Main_presenter(IMain_view& view, Dicom_files& files)
    : m_view(view),
      m_files(files) {
    show_dashboard_view();
}

void Main_presenter::setup_event_handlers() {
    m_files.file_saved += [this] {update_window_title();};
    m_view.open_files_clicked += [this] {open_files();};
    m_view.new_file_clicked += [this] {new_file();};
    m_view.save_file_clicked += [this] {save_file();};
    m_view.save_file_as_clicked += [this] {save_file_as();};
    m_view.save_all_files_clicked += [this] {save_all_files();};
    m_view.clear_all_files_clicked += [this] {clear_all_files();};
    m_view.quit_clicked += [this] {quit();};
    m_view.edit_all_files_clicked += [this] {edit_all_files();};
    m_view.about_clicked += [this] {about();};
}

void Main_presenter::on_dataset_changed() {
    if(m_state == Presenter_state::dashboard) {
        show_editor_view();
    }
    else if(m_files.get_current_file() == nullptr) {
        show_dashboard_view();
    }
    else {
        update_window_title();
    }
}

void Main_presenter::show_dashboard_view() {
    m_state = Presenter_state::dashboard;
    update_window_title();
    m_view.show_dashboard_view();
}

void Main_presenter::show_editor_view() {
    m_state = Presenter_state::editor;
    update_window_title();
    m_view.show_editor_view();
}

void Main_presenter::open_files() {
    std::unique_ptr<IOpen_files_view> view = m_view.create_open_files_view();
    Open_files_presenter presenter(*view, m_files);
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
    Status status = m_files.save_current_file_as(path);

    if(status.bad()) {
        m_view.show_error("Error", "Failed to save file: " + path.string() +
            "\nReason: " + status.text());
    }
}

void Main_presenter::save_all_files() {
    Status status = m_files.save_all_files();

    if(status.bad()) {
        m_view.show_error("Error", "At least one file failed to save.\n"
            "Reason: " + status.text());
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
    presenter.setup_event_handlers();
    presenter.show_dialog();
}

void Main_presenter::about() {
    m_view.show_about_dialog();
}

void Main_presenter::update_window_title() {
    if(m_state == Presenter_state::dashboard) {
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
