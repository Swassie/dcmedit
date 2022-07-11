#include "models/Dicom_files.h"

#include "Dicom_file.h"

#include <algorithm>

Dicom_files::Dicom_files()
    : m_current_file(nullptr) {}

Status Dicom_files::create_new_file(const fs::path& path) {
    Status status = Dicom_file::create_new_file(path);

    return status.good() ? open_file(path) : status;
}

Status Dicom_files::open_file(const fs::path& path) {
    auto replace_file = std::find_if(m_files.begin(), m_files.end(), [&](auto& file) {
        return file->get_path() == path;
    });

    if(replace_file != m_files.end() && (*replace_file)->has_unsaved_changes()) {
        return Status("file is already open and has unsaved changes");
    }
    auto file = std::make_unique<Dicom_file>();
    Status status = file->load_file(path);

    if(status.bad()) {
        return status;
    }
    if(replace_file != m_files.end()) {
        m_files.erase(replace_file);
    }
    m_files.push_back(std::move(file));
    set_current_file(m_files.back().get());

    return Status::ok;
}

bool Dicom_files::has_unsaved_changes() const {
    return std::any_of(m_files.begin(), m_files.end(), [] (auto& file) {
        return file->has_unsaved_changes();
    });
}

void Dicom_files::clear_all_files() {
    m_current_file = nullptr;
    m_files.clear();
    all_files_cleared();
}

Status Dicom_files::save_current_file_as(const fs::path& new_path) {
    bool same_path = m_current_file->get_path() == new_path;
    auto replace_file = std::find_if(m_files.begin(), m_files.end(), [&](auto& file) {
        return !same_path && file->get_path() == new_path;
    });

    if(replace_file != m_files.end() && (*replace_file)->has_unsaved_changes()) {
        return Status("file is already open and has unsaved changes");
    }
    Status status = m_current_file->save_file_as(new_path);

    if(status.bad()) {
        return status;
    }
    if(replace_file != m_files.end()) {
        m_files.erase(replace_file);
    }
    file_saved();

    return Status::ok;
}

Status Dicom_files::save_all_files() {
    Status result = Status::ok;

    for(auto& file : m_files) {
        Status status = file->save_file();

        if(status.bad()) {
            result = status;
        }
    }
    file_saved();
    return result;
}

void Dicom_files::set_current_file(Dicom_file* file) {
    m_current_file = file;
    current_file_set();
}
