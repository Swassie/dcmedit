#pragma once
#include "common/Event.h"
#include "Dicom_file.h"

#include <memory>
#include <vector>

class Dicom_files
{
public:
    Dicom_files();

    Event<> current_file_set;
    Event<> all_files_cleared;
    Event<> files_added;
    Event<> files_saved;

    void add_files(std::vector<std::unique_ptr<Dicom_file>>);
    bool has_unsaved_changes() const;

    void clear_all_files();

    void save_current_file_as(const std::string&);
    bool save_all_files();

    Dicom_file* get_current_file() {return m_current_file;}
    void set_current_file(Dicom_file*);

    auto& get_files() {return m_files;}

protected:
    Dicom_file* m_current_file;
    std::vector<std::unique_ptr<Dicom_file>> m_files;
};
