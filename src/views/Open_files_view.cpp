#include "views/Open_files_view.h"

#include <QFileDialog>
#include <QMessageBox>

Open_files_view::Open_files_view(QWidget* parent)
    : m_parent(parent) {}

QStringList Open_files_view::show_file_dialog() {
    return QFileDialog::getOpenFileNames(m_parent, "Open files");
}

void Open_files_view::show_error(const QStringList& file_errors) {
    QMessageBox dialog(QMessageBox::Critical, "Failed to load files",
                       "At least one file failed to load.", QMessageBox::Ok, m_parent);
    dialog.setDetailedText(file_errors.join("\n\n"));
    dialog.exec();
}
