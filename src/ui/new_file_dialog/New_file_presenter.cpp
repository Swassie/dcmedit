#include "ui/new_file_dialog/New_file_presenter.h"

#include "models/Dicom_files.h"

#include <filesystem>

namespace fs = std::filesystem;

New_file_presenter::New_file_presenter(INew_file_view& view, Dicom_files& dicom_files)
    : m_view(view),
      m_dicom_files(dicom_files) {}

void New_file_presenter::show_dialog() {
    fs::path file_path = m_view.show_file_dialog();

    if(file_path.empty()) {
        return;
    }
    try {
        m_dicom_files.create_new_file(file_path);
    }
    catch(const std::exception& e) {
        m_view.show_error(e.what());
    }
}
