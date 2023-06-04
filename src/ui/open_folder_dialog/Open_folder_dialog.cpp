#include "ui/open_folder_dialog/Open_folder_dialog.h"

#include "common/Scoped_defer.h"
#include "logging/Log.h"

#include <QFileDialog>
#include <filesystem>
#include <system_error>

Open_folder_dialog::Open_folder_dialog(Dicom_files& dicom_files, QWidget& parent)
    : m_dicom_files(dicom_files),
      m_parent(parent) {}

void Open_folder_dialog::show() {
    const fs::path dir = show_dir_dialog();

    if (dir.empty()) {
        return;
    }
    Scoped_defer defer(m_dicom_files.current_file_set);

    for(const fs::directory_entry& entry : fs::recursive_directory_iterator(dir)) {
        try {
            if(entry.is_regular_file()) {
                m_dicom_files.open_file(entry);
            }
        }
        catch(const std::exception& e) {
            Log::error("Failed to open file: " + entry.path().string() +
                "\nReason: " + std::string(e.what()));
        }
    }
}

fs::path Open_folder_dialog::show_dir_dialog() {
    return QFileDialog::getExistingDirectory(&m_parent, "Open folder").toStdString();
}
