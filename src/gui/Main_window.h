#pragma once
#include "Dicom_file.h"
#include "gui/studio/Studio.h"

#include <memory>
#include <QMainWindow>

class Main_window : public QMainWindow
{
    Q_OBJECT
public:
    Main_window();

    void set_title();

    void setup_start_studio();
    void setup_dicom_studio();

    void open_file();
    void save_file();
    void save_file_as();

private:
    std::unique_ptr<Dicom_file> m_file;
    std::unique_ptr<Studio> m_studio;
};
