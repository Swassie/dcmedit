#include "ui/open_folder_dialog/Open_folder_presenter.h"

#include "common/Scoped_defer.h"
#include "logging/Log.h"
#include "models/Dicom_files.h"
#include "ui/open_folder_dialog/IOpen_folder_view.h"

#include <exception>
#include <filesystem>
#include <string>

namespace fs = std::filesystem;

Open_folder_presenter::Open_folder_presenter(IOpen_folder_view& view, Dicom_files& dicom_files)
    : m_view(view),
      m_dicom_files(dicom_files) {}

void Open_folder_presenter::show_dialog() {
    const fs::path dir = m_view.show_dir_dialog();

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
