#pragma once
#include "models/Dicom_files.h"
#include "ui/edit_all_files_dialog/IEdit_all_files_view.h"

class Edit_all_files_presenter
{
public:
    Edit_all_files_presenter(IEdit_all_files_view&, Dicom_files&);

    void setup_event_callbacks();
    void show_dialog();
    void apply();
    void on_mode_changed();

private:
    IEdit_all_files_view& m_view;
    Dicom_files& m_files;
};
