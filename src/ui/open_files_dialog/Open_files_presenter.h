#pragma once
class Dicom_files;
class IOpen_files_view;

class Open_files_presenter
{
public:
    Open_files_presenter(IOpen_files_view&, Dicom_files&);

    void show_dialog();

protected:
    IOpen_files_view& m_view;
    Dicom_files& m_dicom_files;
};
