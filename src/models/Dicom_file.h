#pragma once
#include "common/Status.h"
#include <dcmtk/dcmdata/dcfilefo.h>
#include <filesystem>

namespace fs = std::filesystem;

class Dicom_file
{
public:
    Dicom_file();

    Status load_file(const fs::path&);

    DcmDataset& get_dataset() {return *m_file.getDataset();}
    fs::path get_path() {return m_path;}
    bool has_unsaved_changes() {return m_unsaved_changes;}
    void set_unsaved_changes(bool value) {m_unsaved_changes = value;}

    Status save_file();
    Status save_file_as(const fs::path&);

    static Status create_new_file(const fs::path&);

private:
    fs::path m_path;
    DcmFileFormat m_file;
    bool m_unsaved_changes;
};
