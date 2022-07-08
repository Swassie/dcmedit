#pragma once
#include "models/Dicom_files.h"
#include "ui/open_files_dialog/IOpen_files_view.h"

class Open_files_presenter
{
public:
    Open_files_presenter(IOpen_files_view&, Dicom_files&);

    void show_dialog();

protected:
    IOpen_files_view& m_view;
    Dicom_files& m_dicom_files;
};
