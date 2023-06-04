#pragma once
#include "models/Dicom_files.h"

#include <QWidget>
#include <filesystem>
#include <string>

namespace fs = std::filesystem;

class Open_folder_dialog
{
public:
    Open_folder_dialog(Dicom_files&, QWidget& parent);
    virtual ~Open_folder_dialog() = default;

    void show();

private:
    virtual fs::path show_dir_dialog();

    Dicom_files& m_dicom_files;
    QWidget& m_parent;
};
