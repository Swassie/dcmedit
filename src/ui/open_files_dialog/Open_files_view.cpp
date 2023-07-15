#include "ui/open_files_dialog/Open_files_view.h"

#include "ui/progressbar/Progress_view.h"

#include <QFileDialog>
#include <QMessageBox>

Open_files_view::Open_files_view(QWidget* parent)
    : m_parent(parent) {}

std::vector<fs::path> Open_files_view::show_file_dialog() {
    const QStringList file_list = QFileDialog::getOpenFileNames(m_parent, "Open files");
    std::vector<fs::path> file_paths;

    for(const QString& path : file_list) {
        file_paths.push_back(path.toStdString());
    }
    return file_paths;
}

void Open_files_view::show_error(const std::vector<std::string>& file_errors) {
    QMessageBox dialog(QMessageBox::Critical, "Failed to load files",
        "At least one file failed to load.", QMessageBox::Ok, m_parent);

    QString details;
    for(const std::string& error : file_errors) {
        details += QString::fromStdString(error) + "\n\n";
    }
    dialog.setDetailedText(details);
    dialog.exec();
}

std::unique_ptr<IProgress_view> Open_files_view::create_progress_view() {
    return std::make_unique<Progress_view>(m_parent);
}
