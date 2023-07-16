#include "ui/edit_all_files_dialog/Edit_all_files_presenter.h"

#include "common/Dicom_util.h"
#include "common/Exceptions.h"
#include "models/Dicom_files.h"
#include "ui/edit_all_files_dialog/IEdit_all_files_view.h"

Edit_all_files_presenter::Edit_all_files_presenter(IEdit_all_files_view& view, Dicom_files& files)
    : m_view(view),
      m_files(files) {
    setup_event_callbacks();
}

void Edit_all_files_presenter::setup_event_callbacks() {
    m_view.ok_clicked.add_callback([this] {apply();});
    m_view.cancel_clicked.add_callback([this] {m_view.close_dialog();});
    m_view.mode_changed.add_callback([this] {on_mode_changed();});
}

void Edit_all_files_presenter::show_dialog() {
    m_view.show_dialog();
}

void Edit_all_files_presenter::apply() {
    std::string tag_path = m_view.tag_path();
    std::string value = m_view.value();

    if(tag_path.empty()) {
        m_view.show_error("Error", "Tag path must be set.");
        return;
    }
    std::vector<std::string> file_errors;
    const auto mode = m_view.mode();

    for(auto& file : m_files.get_files()) {
        try {
            if(mode == IEdit_all_files_view::Mode::add_edit) {
                Dicom_util::add_or_edit_element(tag_path, value, false, file->get_dataset());
            }
            else if(mode == IEdit_all_files_view::Mode::edit) {
                Dicom_util::add_or_edit_element(tag_path, value, true, file->get_dataset());
            }
            else {
                Dicom_util::delete_element(tag_path, file->get_dataset());
            }
        }
        catch(const Tag_path_not_found_error& e) {
            if(mode == IEdit_all_files_view::Mode::add_edit) {
                file_errors.push_back(file->get_path().string() +
                    "\nReason: " + std::string(e.what()));
            }
            continue;
        }
        catch(const std::exception& e) {
            file_errors.push_back(file->get_path().string() +
                "\nReason: " + std::string(e.what()));
        }
        file->set_unsaved_changes(true);
    }
    m_files.all_files_edited();

    if(file_errors.empty()) {
        m_view.close_dialog();
    }
    else {
        m_view.show_error_details(file_errors);
    }
}

void Edit_all_files_presenter::on_mode_changed() {
    const auto mode = m_view.mode();
    m_view.enable_value(mode != IEdit_all_files_view::Mode::remove);
}
