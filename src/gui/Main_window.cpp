#include "gui/Main_window.h"

#include "gui/Menu_bar.h"
#include "gui/Start_view.h"
#include "gui/Workspace_view.h"
#include "logging/Log.h"
#include "util/Filesystem.h"

#include <dcmtk/dcmdata/dctk.h>
#include <dcmtk/dcmimgle/dcmimage.h>
#include <QFileDialog>
#include <QMenuBar>

Main_window::Main_window() {
    setMinimumSize(QSize(800, 600));
}

void Main_window::setup_start() {
    auto start_view = new Start_view(*this);
    start_view->setup();

    setMenuBar(new QMenuBar(this));
    Menu_bar::create_file_menu(*this);

    setCentralWidget(start_view);
}

void Main_window::setup_workspace() {
    auto workspace_view = new Workspace_view(*m_dicom_file);
    workspace_view->setup();

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
