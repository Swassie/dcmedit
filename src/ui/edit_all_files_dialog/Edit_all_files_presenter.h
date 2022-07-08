#pragma once
class Dicom_files;
class IEdit_all_files_view;

class Edit_all_files_presenter
{
public:
    Edit_all_files_presenter(IEdit_all_files_view&, Dicom_files&);

    void setup_event_handlers();
    void show_dialog();
    void apply();
    void on_mode_changed();

private:
    IEdit_all_files_view& m_view;
    Dicom_files& m_files;
};
