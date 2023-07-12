#pragma once
#include "models/Dicom_files.h"
#include "ui/open_folder_dialog/IOpen_folder_view.h"

class Open_folder_presenter
{
public:
    Open_folder_presenter(IOpen_folder_view&, Dicom_files&);

    void show_dialog();

private:
    IOpen_folder_view& m_view;
    Dicom_files& m_dicom_files;
};
