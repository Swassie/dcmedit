#include "views/Open_files_view.h"

#include <QFileDialog>
#include <QMessageBox>

Open_files_view::Open_files_view(QWidget* parent)
    : m_parent(parent) {}

std::vector<std::string> Open_files_view::show_file_dialog() {
    const QStringList file_list = QFileDialog::getOpenFileNames(m_parent, "Open files");
    std::vector<std::string> file_paths;

    for(const auto& path : file_list) {
        file_paths.push_back(path.toStdString());
    }
    return file_paths;
}

void Open_files_view::show_error(const std::vector<std::string>& file_errors) {
    QMessageBox dialog(QMessageBox::Critical, "Failed to load files",
                       "At least one file failed to load.", QMessageBox::Ok, m_parent);

    QString details;
    for(const auto& error : file_errors) {
        details += QString::fromStdString(error) + "\n\n";
    }
    dialog.setDetailedText(details);
    dialog.exec();
}
