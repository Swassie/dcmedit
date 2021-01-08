#pragma once
#include <dcmtk/dcmdata/dcfilefo.h>
#include <string>

class Dicom_file
{
public:
    Dicom_file(std::string&);
    DcmDataset& get_dataset() {return *m_file.getDataset();}
    std::string get_path() {return m_path;}
    void save_file();
    void save_file_as(std::string);

private:
    std::string m_path;
    DcmFileFormat m_file;
};
