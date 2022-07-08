#include "ui/open_files_dialog/Open_files_presenter.h"

#include "common/Defer_event.h"
#include "models/Dicom_files.h"
#include "ui/open_files_dialog/IOpen_files_view.h"

#include <filesystem>
#include <memory>
#include <string>
#include <vector>

namespace fs = std::filesystem;

Open_files_presenter::Open_files_presenter(IOpen_files_view& view, Dicom_files& dicom_files)
    : m_view(view),
      m_dicom_files(dicom_files) {}

void Open_files_presenter::show_dialog() {
    std::vector<fs::path> file_paths = m_view.show_file_dialog();

    if (file_paths.empty()) {
        return;
    }
    std::vector<std::string> file_errors;
    Defer_event defer(m_dicom_files.current_file_set);

    for(const fs::path& file_path : file_paths) {
        try {
            m_dicom_files.open_file(file_path);
        }
        catch(const std::exception& e) {
            file_errors.push_back(e.what());
        }
    }
    if(!file_errors.empty()) {
        m_view.show_error(file_errors);
    }
}
