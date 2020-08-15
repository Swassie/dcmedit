#include "gui/Main_window.h"

#include "gui/Menu_bar.h"
#include "gui/Start_view.h"
#include "gui/View_factory.h"
#include "gui/Workspace_view.h"
#include "logging/Log.h"
#include "util/Filesystem.h"

#include <dcmtk/dcmdata/dctk.h>
#include <dcmtk/dcmimgle/dcmimage.h>
#include <QFileDialog>
#include <QMenuBar>

Main_window::Main_window() {
    setMinimumSize(800, 600);
}

void Main_window::setup_start() {
    auto start_view = new Start_view(*this);

    setMenuBar(new QMenuBar(this));
    Menu_bar::create_file_menu(*this);

    setCentralWidget(start_view);
}

void Main_window::setup_workspace() {
    removeToolBar(m_tool_bar.get());
    m_tool_bar = std::make_unique<Tool_bar>();
    addToolBar(m_tool_bar.get());

    m_element_model = std::make_unique<Data_element_model>(*m_dicom_file);
    View_factory view_factory(*m_dicom_file, *m_tool_bar, *m_element_model);
    auto workspace_view = new Workspace_view(view_factory);

    setMenuBar(new QMenuBar(this));
    Menu_bar::create_file_menu(*this);
    Menu_bar::create_view_menu(*this, *workspace_view);

    setCentralWidget(workspace_view);
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
    setup_workspace();
}
