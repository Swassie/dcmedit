#include "gui/Main_window.h"

#include "gui/studio/Dicom_studio.h"
#include "gui/studio/Start_studio.h"

#include <QCloseEvent>
#include <QCoreApplication>

Main_window::Main_window() {
    setMinimumSize(800, 600);
}

void Main_window::setup_start_studio() {
    m_studio = std::make_unique<Start_studio>(*this);
}

void Main_window::setup_dicom_studio(std::vector<std::unique_ptr<Dicom_file>> files) {
    m_studio = std::make_unique<Dicom_studio>(*this, std::move(files));
}

void Main_window::maybe_quit() {
    if(!m_studio->is_ok_to_quit()) {
        return;
    }
    QCoreApplication::quit();
}

void Main_window::closeEvent(QCloseEvent* event) {
    if(!m_studio->is_ok_to_quit()) {
        event->ignore();
    }
    else {
        event->accept();
    }
}
