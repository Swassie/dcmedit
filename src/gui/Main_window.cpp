#include "gui/Main_window.h"

#include "gui/studio/Dicom_studio.h"
#include "gui/studio/Start_studio.h"

#include <QFileDialog>
#include <QMessageBox>

Main_window::Main_window() {
    setMinimumSize(800, 600);
}

void Main_window::setup_start_studio() {
    m_studio = std::make_unique<Start_studio>(*this);
    setMenuBar(m_studio->take_menu_bar().release());
    setCentralWidget(m_studio->take_central_widget().release());
}

void Main_window::setup_dicom_studio() {
    m_studio = std::make_unique<Dicom_studio>(*this, m_file->get_dataset());
    addToolBar(m_studio->get_tool_bar());
    setMenuBar(m_studio->take_menu_bar().release());
    setCentralWidget(m_studio->take_central_widget().release());
}

void Main_window::open_file() {
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
}
