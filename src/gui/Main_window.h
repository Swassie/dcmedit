#pragma once
#include "gui/Studio.h"

#include <dcmtk/dcmdata/dctk.h>
#include <memory>
#include <QMainWindow>

class Main_window : public QMainWindow
{
    Q_OBJECT

public:
    Main_window();

    void setup_initial_studio();
    void setup_dicom_studio();

    void open_file();
private:

    std::unique_ptr<DcmFileFormat> m_dicom_file;
    std::unique_ptr<Studio> m_studio;
};
