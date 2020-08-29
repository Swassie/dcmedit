#include "gui/Main_window.h"

#include "gui/studio/Dicom_studio.h"
#include "gui/studio/Start_studio.h"
#include "logging/Log.h"
#include "util/Filesystem.h"

#include <dcmtk/dcmdata/dctk.h>
#include <dcmtk/dcmimgle/dcmimage.h>
#include <QFileDialog>

Main_window::Main_window() {
    setMinimumSize(800, 600);
}

void Main_window::setup_start_studio() {
    if(m_studio) {
        removeToolBar(m_studio->get_tool_bar());
    }
    m_studio = std::make_unique<Start_studio>(*this);
    setMenuBar(m_studio->take_menu_bar().release());
    setCentralWidget(m_studio->take_central_widget().release());
}

void Main_window::setup_dicom_studio() {
    if(m_studio) {
        removeToolBar(m_studio->get_tool_bar());
    }
    m_studio = std::make_unique<Dicom_studio>(*this, *m_dicom_file.get());
    addToolBar(m_studio->get_tool_bar());
    setMenuBar(m_studio->take_menu_bar().release());
    setCentralWidget(m_studio->take_central_widget().release());
}

void Main_window::open_file() {
    std::string file_path = QFileDialog::getOpenFileName(this, "Open file").toStdString();
    if (file_path.empty()) {
        return;
    }
    auto file_format = std::make_unique<DcmFileFormat>();
    OFCondition status = file_format->loadFile(file_path.c_str());

    if(!status.good()) {
        Log::info("Could not load file: " + file_path +
                  ". Reason: " + status.text());
        return;
    }
    m_dicom_file = std::move(file_format);
    setup_dicom_studio();
}
