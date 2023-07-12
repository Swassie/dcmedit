#include "ui/open_folder_dialog/Open_folder_view.h"

#include <QFileDialog>

Open_folder_view::Open_folder_view(QWidget* parent)
    : m_parent(parent) {}

fs::path Open_folder_view::show_dir_dialog() {
    return QFileDialog::getExistingDirectory(m_parent, "Open folder").toStdString();
}
