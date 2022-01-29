#include "presenters/Open_files_presenter.h"

#include "models/Dicom_files.h"
#include "views/IOpen_files_view.h"

#include <memory>
#include <string>
#include <vector>

Open_files_presenter::Open_files_presenter(IOpen_files_view& view, Dicom_files& dicom_files)
    : m_view(view),
      m_dicom_files(dicom_files) {}

void Open_files_presenter::open_files() {
    auto file_paths = m_view.show_file_dialog();

    if (file_paths.empty()) {
        return;
    }
    std::vector<std::unique_ptr<Dicom_file>> files;
    std::vector<std::string> file_errors;

    for(const auto& file_path : file_paths) {
        try {
            files.push_back(std::make_unique<Dicom_file>(file_path));
        }
        catch(const std::exception& e) {
            file_errors.push_back(e.what());
        }
    }
    if(!file_errors.empty()) {
        m_view.show_error(file_errors);
    }
    m_dicom_files.add_files(std::move(files));
}
