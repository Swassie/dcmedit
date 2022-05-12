#include "models/Dicom_files.h"

#include "Dicom_file.h"
#include "Exceptions.h"

#include <algorithm>

Dicom_files::Dicom_files()
    : m_current_file(nullptr) {}

void Dicom_files::create_new_file(const fs::path& path) {
    Dicom_file::create_new_file(path);
    open_file(path);
}

void Dicom_files::open_file(const fs::path& path) {
    auto replace_file = std::find_if(m_files.begin(), m_files.end(), [&](auto& file) {
        return file->get_path() == path;
    });

    if(replace_file != m_files.end() && (*replace_file)->has_unsaved_changes()) {
        throw DcmeditException("Failed to open file: " + path.string() +
                               "\nReason: it has unsaved changes.");
    }
    auto file = std::make_unique<Dicom_file>(path);

    if(replace_file != m_files.end()) {
        m_files.erase(replace_file);
    }
    m_files.push_back(std::move(file));
    set_current_file(m_files.back().get());
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

void Dicom_files::save_current_file_as(const fs::path& new_path) {
    bool same_path = m_current_file->get_path() == new_path;
    auto replace_file = std::find_if(m_files.begin(), m_files.end(), [&](auto& file) {
        return !same_path && file->get_path() == new_path;
    });

    if(replace_file != m_files.end() && (*replace_file)->has_unsaved_changes()) {
        throw DcmeditException("Failed to save file: " + new_path.string() +
                               "\nReason: it has unsaved changes.");
    }
    m_current_file->save_file_as(new_path);

    if(replace_file != m_files.end()) {
        m_files.erase(replace_file);
    }
    file_saved();
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
    file_saved();
    return ok;
}

void Dicom_files::set_current_file(Dicom_file* file) {
    m_current_file = file;
    current_file_set();
}
