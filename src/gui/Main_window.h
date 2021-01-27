#pragma once
#include "Dicom_file.h"
#include "gui/studio/Studio.h"

#include <memory>
#include <QMainWindow>
#include <vector>

class Main_window : public QMainWindow
{
    Q_OBJECT
public:
    Main_window();

    void setup_start_studio();
    void setup_dicom_studio(std::vector<std::unique_ptr<Dicom_file>>);

    void maybe_quit();

protected:
    void closeEvent(QCloseEvent*) override;

private:
    std::unique_ptr<Studio> m_studio;
};
