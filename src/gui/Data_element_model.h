#pragma once
#include <QStandardItemModel>

class DcmFileFormat;

class Data_element_model : public QStandardItemModel
{
public:
    Data_element_model(DcmFileFormat&);

private:
    DcmFileFormat& m_dicom_file;
};
