#pragma once
#include <dcmtk/dcmdata/dcfilefo.h>
#include <string>

class Dicom_file
{
public:
    Dicom_file(const std::string&);

    DcmDataset& get_dataset() {return *m_file.getDataset();}
    std::string get_path() {return m_path;}
    bool has_unsaved_changes() {return m_unsaved_changes;}
    void set_unsaved_changes(bool value) {m_unsaved_changes = value;}

    void save_file();
    void save_file_as(std::string);

private:
    std::string m_path;
    DcmFileFormat m_file;
    bool m_unsaved_changes;
};
