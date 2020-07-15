#pragma once
#include <memory>
#include <QMainWindow>
#include <dcmtk/dcmdata/dctk.h>

class Main_window : public QMainWindow
{
    Q_OBJECT

public:
    Main_window();

    void setup_start();
    void setup_workspace();

    void open_file();
private:

    std::unique_ptr<DcmFileFormat> m_dicom_file;
};
