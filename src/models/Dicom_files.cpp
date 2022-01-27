#include "models/Dicom_files.h"

#include "Dicom_file.h"

#include <algorithm>

Dicom_files::Dicom_files()
    : m_current_file(nullptr) {}

void Dicom_files::add_files(std::vector<std::unique_ptr<Dicom_file>> files) {
    if(files.empty()) {
        return;
    }
    for(auto& new_file : files) {
        auto new_file_path = new_file->get_path();
        bool duplicate_file = false;
        for(auto& file : m_files) {
            if(file->get_path() == new_file_path) {
                duplicate_file = true;
                break;
            }
        }
        if(!duplicate_file) {
            m_files.push_back(std::move(new_file));
        }
    }

    files_added();

    if(m_current_file == nullptr && m_files.size()) {
        set_current_file(m_files[0].get());
    }
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

void Dicom_files::save_current_file_as(const std::string& path) {
    m_current_file->save_file_as(path);
    files_saved();
}

bool Dicom_files::save_all_files() {
    bool ok = true;

    for(auto& file : m_files) {
        try {
            file->save_file();
        }
        catch(const std::exception&) {
            ok = false;
        }
    }

    files_saved();

    return ok;
}

void Dicom_files::set_current_file(Dicom_file* file) {
    m_current_file = file;
    current_file_set();
}
