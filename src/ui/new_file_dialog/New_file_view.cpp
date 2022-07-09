#include "ui/new_file_dialog/New_file_view.h"

#include <QFileDialog>
#include <QMessageBox>

New_file_view::New_file_view(QWidget* parent)
    : m_parent(parent) {}

fs::path New_file_view::show_file_dialog() {
    QString file_path = QFileDialog::getSaveFileName(m_parent, "Create new file");
    return file_path.toStdString();
}

void New_file_view::show_error(const std::string& text) {
    QMessageBox::critical(m_parent, "Error", QString::fromStdString(text));
}
