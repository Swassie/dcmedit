#include "gui/Main_window.h"

#include "gui/Gui_util.h"
#include "gui/studio/Dicom_studio.h"
#include "gui/studio/Start_studio.h"

#include <QCloseEvent>
#include <QCoreApplication>
#include <QFileDialog>
#include <QFileInfo>
#include <QMessageBox>

Main_window::Main_window() {
    setMinimumSize(800, 600);
    set_title();
}

void Main_window::set_title() {
    QString title;
    if(m_file) {
        std::string path = m_file->get_path();
        QFileInfo file_info(path.c_str());
        title += file_info.fileName() + "[*] - ";
    }
    title += QCoreApplication::applicationName();
    setWindowTitle(title);
}

void Main_window::maybe_quit() {
    if(isWindowModified() && !Gui_util::should_unsaved_changes_be_discarded(this)) {
        return;
    }
    QCoreApplication::quit();
}

void Main_window::setup_start_studio() {
    m_studio = std::make_unique<Start_studio>(*this);
}

void Main_window::setup_dicom_studio() {
    m_studio = std::make_unique<Dicom_studio>(*this, *m_file);
}

void Main_window::open_file() {
    if(isWindowModified() && !Gui_util::should_unsaved_changes_be_discarded(this)) {
        return;
    }
    std::string file_path = QFileDialog::getOpenFileName(this, "Open file").toStdString();
    if (file_path.empty()) {
        return;
    }
    try {
        m_file = std::make_unique<Dicom_file>(file_path);
    }
    catch(const std::exception& e) {
        QMessageBox::critical(this, "Failed to load file", e.what());
        return;
    }
    setup_dicom_studio();
    setWindowModified(false);
    set_title();
}

void Main_window::save_file() {
    try {
        m_file->save_file();
    }
    catch(const std::exception& e) {
        QMessageBox::critical(this, "Failed to save file", e.what());
    }
    setWindowModified(false);
}

void Main_window::save_file_as() {
    std::string file_path = QFileDialog::getSaveFileName(this, "Save file as").toStdString();
    if (file_path.empty()) {
        return;
    }
    try {
        m_file->save_file_as(file_path);
    }
    catch(const std::exception& e) {
        QMessageBox::critical(this, "Failed to save file", e.what());
    }
    setWindowModified(false);
}

void Main_window::closeEvent(QCloseEvent* event) {
    if(isWindowModified() && !Gui_util::should_unsaved_changes_be_discarded(this)) {
        event->ignore();
    }
    else {
        event->accept();
    }
}
