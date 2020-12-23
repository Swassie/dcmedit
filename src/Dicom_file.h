#pragma once
#include <dcmtk/dcmdata/dcfilefo.h>
#include <string>

class Dicom_file
{
public:
    Dicom_file(std::string&);
    DcmDataset& get_dataset() {return *m_file.getDataset();}

private:
    std::string m_path;
    DcmFileFormat m_file;
};
