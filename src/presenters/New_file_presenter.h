#pragma once
#include "models/Dicom_files.h"
#include "views/INew_file_view.h"

class New_file_presenter
{
public:
    New_file_presenter(INew_file_view&, Dicom_files&);

    void show_dialog();

private:
    INew_file_view& m_view;
    Dicom_files& m_dicom_files;
};
