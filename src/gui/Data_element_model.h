#pragma once
#include <QStandardItemModel>

class DcmFileFormat;

class Data_element_model : public QStandardItemModel
{
    Q_OBJECT
public:
    Data_element_model(DcmFileFormat&);

private:
    DcmFileFormat& m_dicom_file;
};
