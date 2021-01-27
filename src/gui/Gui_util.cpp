#include "gui/Gui_util.h"

#include "Dicom_file.h"

#include <QFileDialog>
#include <QMessageBox>
#include <QMouseEvent>

bool Gui_util::is_left_mouse_pressed(const QMouseEvent& event) {
    return event.buttons() & Qt::LeftButton;
}

bool Gui_util::should_unsaved_changes_be_discarded(QWidget* parent) {
    auto answer = QMessageBox::question(parent, "Discard unsaved changes?",
                                        "Do you really want to discard unsaved changes?");
    return answer == QMessageBox::Yes;
}

std::vector<std::unique_ptr<Dicom_file>> Gui_util::load_files(QWidget* parent) {
    std::vector<std::unique_ptr<Dicom_file>> files;
    QStringList file_paths = QFileDialog::getOpenFileNames(parent, "Open files");
    if (file_paths.isEmpty()) {
        return files;
    }
    QStringList file_errors;
    for(QString& file_path : file_paths) {
        try {
            files.push_back(std::make_unique<Dicom_file>(file_path.toStdString()));
        }
        catch(const std::exception& e) {
            file_errors.push_back(e.what());
        }
    }
    if(!file_errors.isEmpty()) {
        QString text = "At least one file ";
        if(files.empty()) {
            text = "All files ";
        }
        QMessageBox warning(QMessageBox::Warning, "Failed to load files",
                            text + "failed to load.", QMessageBox::Ok, parent);
        warning.setDetailedText(file_errors.join("\n\n"));
        warning.exec();
    }
    return files;
}
