#include "presenters/Main_presenter.h"

#include "models/Dataset_model.h"
#include "models/Dicom_files.h"
#include "presenters/Edit_all_files_presenter.h"
#include "views/IEdit_all_files_view.h"
#include "views/IMain_view.h"

#include <QCoreApplication>

Main_presenter::Main_presenter(IMain_view& view,
                               Dicom_files& files,
                               Dataset_model& dataset_model)
    : m_state(Presenter_state::dashboard),
      m_view(view),
      m_files(files),
      m_dataset_model(dataset_model) {}

void Main_presenter::setup_event_handlers() {
    m_files.current_file_set += [this] {
        if(m_state == Presenter_state::dashboard) {
            show_editor_view();
        }
    };
    m_files.all_files_cleared += [this] {show_dashboard_view();};
    m_files.files_saved += [this] {update_window_title();};
    m_view.save_file_clicked += [this] {save_file();};
    m_view.save_file_as_clicked += [this] {save_file_as();};
    m_view.save_all_files_clicked += [this] {save_all_files();};
    m_view.clear_all_files_clicked += [this] {clear_all_files();};
    m_view.quit_clicked += [this] {quit();};
    m_view.edit_all_files_clicked += [this] {edit_all_files();};
    m_dataset_model.dataset_changed += [this] {update_window_title();};
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

void Main_presenter::save_file() {
    Dicom_file* file = m_files.get_current_file();
    save_file_as(file->get_path());
}

void Main_presenter::save_file_as() {
    auto file_path = m_view.show_save_file_dialog();

    if (!file_path.empty()) {
        save_file_as(file_path);
    }
}

void Main_presenter::save_file_as(const std::string& file_path) {
    try {
        m_files.save_current_file_as(file_path);
    }
    catch(const std::exception& e) {
        m_view.show_error("Error", "Failed to save file.\n"
                          "Reason: " + std::string(e.what()));
    }
}

void Main_presenter::save_all_files() {
    bool ok = m_files.save_all_files();

    if(!ok) {
        m_view.show_error("Error", "Failed to save some files.");
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
    auto view = m_view.create_edit_all_files_view();
    Edit_all_files_presenter presenter(*view, m_files);
    presenter.setup_event_handlers();
    presenter.show_dialog();
}

void Main_presenter::update_window_title() {
    if(m_state == Presenter_state::dashboard) {
        m_view.set_window_modified(false);
        m_view.set_window_title(QCoreApplication::applicationName());
    }
    else {
        Dicom_file* file = m_files.get_current_file();
        if(!file) {
            return;
        }
        m_view.set_window_modified(file->has_unsaved_changes());

        QString title = QString::fromStdString(file->get_path() + "[*] - ");
        title += QCoreApplication::applicationName();
        m_view.set_window_title(title);
    }
}
