#pragma once
#include "common/Event.h"
#include "common/Progress_token.h"
#include "Dicom_file.h"

#include <filesystem>
#include <memory>
#include <vector>

namespace fs = std::filesystem;

class Dicom_files
{
public:
    Dicom_files();

    Event<> current_file_set;
    Event<> file_saved;
    Event<> all_files_edited;

    void create_new_file(const fs::path&);
    void open_file(const fs::path&);
    bool has_unsaved_changes() const;

    void clear_all_files();

    void save_current_file_as(const fs::path&);
    bool save_all_files(Progress_token&);

    Dicom_file* get_current_file() {return m_current_file;}
    void set_current_file(Dicom_file*);

    auto& get_files() {return m_files;}

private:
    Dicom_file* m_current_file;
    std::vector<std::unique_ptr<Dicom_file>> m_files;
};
